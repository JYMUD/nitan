// counter.h
//wsw��2004��2��20��
//��ҹ�̨
//����д˹�̨�󣬿ɰ���Ʒ���ڹ�̨�ϳ��ۣ�����������
//��������������Ʒ����Ʒ->set("changed",1)

#include <ansi.h>   
inherit F_SAVE;   
inherit ITEM;

void init () ;
void setup();
string query_save_file();
int save();
int do_sell(string arg);
int do_buy(string arg) ;
int do_look(string arg);
int do_qu(string arg);
object get_item(object ob,int place);
  
void init ()   
{   
  add_action ("do_sell","sell");   
  add_action ("do_buy","buy"); 
  add_action ("do_look","look"); 
  add_action ("do_qu","qu"); 

}

void setup()
{
        ::setup();
        restore();
}   
string query_save_file()  
{  
   string id;  

   id=file_name(this_object());
   id = id[strsrch(id,"/",-1)+1..strsrch(id,"#",1)-1] ;
   if( !id ) return 0;  
   return sprintf("/data/playercity/obj/counter/%s", id);  
}  
  
int save()  
{  
   return ::save();  
}  

int do_sell(string arg)  
{  
        object obj,newobj;  
        object me= this_player();  
        object ob= this_object();  
        string thing,str;  
        int place,price,j;  

        if(!arg)  
                return notify_fail("��׼����ʲô������<ָ��>:sell <��ƷID> at <λ�ú�> for <����>\n");  

        if(ob->query("owner_id")!=me->query("id")) 
                return notify_fail("�ⲻ����Ĺ�̨��\n");

        if(me->is_busy()) 
                return notify_fail("����æ���أ�\n");  

        if (sscanf(arg,"%s at %d for %d",thing,place,price)!=3)     
                return notify_fail("��Ҫ��ʲô��Ʒ���ڹ�̨���ĸ�λ�ã�<ָ��>:sell <��ƷID> at <λ�ú�> for <����>\n");    
              
        if (price<=0) return notify_fail("���������ĺ����ˣ����ڲ����ˣ�\n");

        if (!( obj=present (thing,me)))   
                return notify_fail("������û�������Ʒ��\n");   

        if (obj->is_character()
             || obj->query_max_encumbrance()  
            || obj->query("liquid")  
                || obj->query_unique())  
                return notify_fail("���������ɲ�������\n");  
                
        if (obj->query("equipped")) 
                return notify_fail("�����������ɡ�\n");  

        if (place <1 || place >ob->query("capacity"))  
                return notify_fail("�����ֻ̨�ܰ�"+ob->query("capacity")+"����Ʒ��\n");  

        if (ob->query("place_"+place+"/have")=="have")  
                return notify_fail("��̨��"+place+"��λ���Ѿ�����Ʒ�ˡ�\n");  

        ob->set("place_"+place+"/have","have");
        ob->set("place_"+place+"/file_name",base_name(obj));
        if (obj->query_amount()) ob->set("place_"+place+"/amount",obj->query_amount());
        else ob->set("place_"+place+"/amount",1);
        ob->set("place_"+place+"/price",price);
        ob->set("place_"+place+"/attribute",obj->query_entire_dbase());

        ob->save();  
        message_vision("$N��һ"+obj->query("unit")+obj->name()+NOR+"�ڽ���̨��\n",me);
        obj->move(VOID_OB);  
        destruct(obj);  
        me->start_busy(2); 
        return 1;
}     
 
int do_buy(string arg)  
{ 
        object newobj;  
        object me= this_player();  
        object ob= this_object(); 
        mapping attribute;  
        int place,afford,price;  
        if(!arg)  
                return notify_fail("��Ҫ��ʲô��<ָ��>:buy <���> from counter\n");  

        if(me->is_busy()) 
                return notify_fail("����æ���أ�n");    

        if (sscanf(arg,"%d from counter",place)!=1)     
                return notify_fail("��Ҫ��ʲôλ�õ���Ʒ��<ָ��>:na xxx from bag\n"); 

        if (place <1 || place >ob->query("capacity"))  
                return notify_fail("��ֻ̨��"+ob->query("capacity")+"���ռ䡣\n");  

        if (ob->query("place_"+place+"/have")!="have")  
                return notify_fail("��̨��"+place+"���ռ��ǿյġ�\n");  
         
       price=ob->query("place_"+place+"/price");
       if (me->query("stocks/balance") < price && ob->query("owner_id") != me->query("id")) 
                return notify_fail("���YSG������\n");
       newobj=get_item(ob,place);
       if(newobj && newobj->move(me)) 
       {             
          if(ob->query("owner_id") != me->query("id")) {
                  me->add("stocks/balance",-1*price);
                  ob->add("payment",price);
          }
          ob->add("place_"+place+"/amount",-1);
          if (ob->query("place_"+place+"/amount")<=0)
              ob->delete("place_"+place);
                  if(ob->query("owner_id") != me->query("id"))
                  message_vision("$N������һ"+newobj->query("unit")+newobj->name()+NOR+"��\n",me); 
          else message_vision("$N�ӹ�̨�ϳ�����һ"+newobj->query("unit")+newobj->name()+NOR+"��\n",me); 
          ob->save();
          me->save();
          me->start_busy(2);
                 return 1;
        }else{
                destruct(newobj);
                return notify_fail("����Ʒʧ�ܡ�\n");
        }
}

int do_look(string arg)
{
    string str;
    object obj,ob;
    int place,j;
    
    ob=this_object();
    
    if (!arg) return 0;
    if (arg == "counter") {
            str=HIB"���֮�ǵĹ�̨��\n"NOR;
            str+="�鿴��Ʒ��ϸ���ϣ�look <���> in counter ��\n";
            str+="������Ʒ׼�����ۣ�sell <��ƷID> at <���> for <����>\n";
            str+="���¹�̨�����Ʒ��buy <���> from counter\n";
            str+="ȡ����̨��Ļ��qu <����> from counter\n";
            str+="��������������������������������������������������������������������������������\n";
            str+=   "�����   ��Ʒ����     ID                 ����        ����\n";  
            str+="��������������������������������������������������������������������������������\n";
            for (j = 1; j<ob->query("capacity")+1; j++) { 
            if (ob->query("place_"+j+"/have")=="have")
                    str+=sprintf("��%2d��%16' 's\t%16' 's\t%d\t%d\t\t\t��\n",j,ob->query("place_"+j+"/attribute/name"),
                    ob->query("place_"+j+"/attribute/id"),ob->query("place_"+j+"/amount"),
                    ob->query("place_"+j+"/price"));
            else  str+=sprintf("��%2d�� <��>\t\t\t\t\t\t\t\t��\n",j);
       }
        str+="��������������������������������������������������������������������������������\n";  
        str+="��ǰ���"+ob->query("payment")+"��\n"; 
        write(str);
        return 1;
    }
    
    if (sscanf(arg,"%d in %s",place,str)==2) {
            if (str!="counter") return 0;
            if (ob->query("place_"+place+"/have")=="have") {
                    obj=get_item(ob,place);
                    if (objectp(obj)) {
                            if (obj->query("changed")) 
                                    "/cmds/std/ll.c"->look_item(0,obj);
                            else "cmds/std/look.c"->look_item(this_player(),obj);
                            destruct(obj);
                            return 1;
                    }
            }else write("���λ���ǿյġ�\n");
            return 1;        
    } 
    return 0;
}

int do_qu(string arg)  
{  
        object obj,newobj;  
        object me= this_player();  
        object ob= this_object();  
        string thing,str;  
        int place,price,j; 
         
        if(ob->query("owner_id")!=me->query("id")) 
                return notify_fail("���뵱С͵����\n");        
        if(!arg)  
                return notify_fail("��Ҫȡ����Ǯ��<ָ��>:qu <����> from counter\n");  
        if(me->is_busy()) 
                return notify_fail("����æ���أ�\n");  
        if (sscanf(arg,"%d from counter",price)!=1)     
                return notify_fail("��Ҫȡ����Ǯ��<ָ��>:qu <����> from counter\n");
                  
        if (price <= 0) return notify_fail("��������أ�\n");

        if (ob->query("payment") < price) return notify_fail("��̨��û����ô����\n");

        ob->add("payment",-1 * price);
        me->add("stocks/balance", price);
        me->start_busy(2);
        message_vision("$N�ӹ�̨��ȡ��"+ price +" YSG�Ļ�������˹��С�\n",me); 
        
        ob->save();
        me->save();
        return 1;
        
}

object get_item(object ob,int place)
{
    object obj;
    mapping attribute;
    string *key;
    int j;
    
    obj=new(ob->query("place_"+place+"/file_name"));  
    if(!obj)  return 0; 
    attribute=ob->query("place_"+place+"/attribute");
    if (mapp(attribute)) {
             key=keys(attribute);
               key = sort_array(key, 0);
            for(j=0; j<sizeof(key); j++) {
                obj->set(key[j], attribute[key[j]]); 
            }                
    }
    return obj;        
        
}
