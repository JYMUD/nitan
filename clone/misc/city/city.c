// Last Modified by sir on 4.10.2002
// Ҫ����ĳ�����У�����ʥּ������ְ������
// ����֪���⣬��ĸ���ֻ�ܿ���ĳ����ָ����
// ��������һЩѲ����ר�������̡�����ָ����
// ��Ȼ�ֺ����ƻ�����ָ����
// topten���ڳ�͢�������ۡ�
// title������ҡ�
// city : �ۺ�����    city_level  ���Ͷ���   ���Ͷ���  ���Ͷ���  С�Ͷ���
//         �˿�       people       800��      500��    300��     100��
//                   ����ָ�����   8000       5000     3000      1000
//         ũҵ       farming     ���� + ����   �����˿� ��������
//         �ΰ�       peace       �� + ��ʶ   �������� 
//         ˮ��       water       ���� + ����   �������� 
//         ��ҵ       business    ��Ե + ��ò   �����˿� ��������
//         ����       technology  ���� + ����   ���ӿ����ٶ�
//         ˰��       tax_rate    0-100 ֮��    
//                    0-15  ֮��   �ǳ����� �����˿� ��������
//                    15-30 ֮��    ����    �����˿� ���Ҳ���
//                    30-40 ֮��   ΢��Թ�� �˿ڲ���  �������� ũҵ,�ΰ��ܵ��ƻ� 
//                    40-60 ֮��   Թ���ص�  �˿ڼ��� �������� ũҵ,�ΰ�,��ҵ�ܵ��ƻ� 
//                    60-80 ֮��   ��Թ����  �˿ڴ�� ���ҿ� ����ָ�����ܵ��ƻ�
//                    80-100֮��   ��������  ���Ĳ��� ����ָ������� 
//         ����       fealty      0-100֮��
//    ��ò per  ���� str �� dex ��Ե kar ���� sta 
//    ���� int  ��ʶ cor ���� cps ���� con ���� spi

#ifndef CITYDATA
#define CITYDATA "/data/city/"  //�ļ���ŵ�ַ
#endif
#define NAMEOFCITY "yangzhou"  //Ҫ�����ĳ�����
#define CNAMEOFCITY "����"     //���ĳ�����
#define FILE_PATH CITYDATA + NAMEOFCITY
#define LEVEL_OF_CITY "���Ͷ���"  //�ۺ�����
#define LEVEL 500   //���е���ʼ��ģ
#define MAX_LEVEL 800  //���е�����ģ

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

int do_kaifa(string);

void create()
{        set_name(HIY"�ٸ�ͨ��"NOR, ({ "guanfu tonggao", "tonggao"}) );
        set("long","����һ�ż�¼"+CNAMEOFCITY+"��������Ĺٸ�ͨ�档\n
��鿴Ŀǰ����������� help ms_city �˽���������\n");
        set("LAST_KAIFA_PLAYER","none of us"); //��󿪷������е����
        set("city_name", NAMEOFCITY); //������
        set("city_level", LEVEL_OF_CITY);// �ۺ�����
        set("fealty", LEVEL/10);  // ����
        set("tax_rate",LEVEL/10); // ˰��
        set("people", LEVEL*10000);        // �˿�
        set("water", LEVEL*10); // ˮ�� 
        set("water_pro", LEVEL*2); // ˮ��������  
        set("peace", LEVEL*10);  // �ΰ�
        set("peace_pro", LEVEL*2);
        set("farming", LEVEL*10); // �Ƿ�
        set("farming_pro", LEVEL*2);
        set("business", LEVEL*10); // ��ҵ
        set("business_pro", LEVEL*2);
        set("technology", LEVEL*10); // ����
        set("technology_pro", LEVEL*2);
        set("no_get", 1);
        set("unit", "��");
        restore();
}
        
        
        
string query_save_file()
{
        return FILE_PATH;        
}


void init()
{
        add_action("do_kaifa", "kaifa"); 
        add_action("do_chakan","chakan");
        add_action("do_tax","tax");                        
}
//int do_chakan()
string long()
{

        string msg;
        object ob;
        ob=this_object();
        msg=HIC"���һ�Źٸ�ͨ����������˱��ǵĿ������: \n"+
        HIY"��������������������������������������������������������������������������\n"NOR;
        msg+=sprintf(HIC"\n ����:" HIY "%8s" NOR HIC"\t\t���й�ģ: " HIY "%8s\n" NOR,
        CNAMEOFCITY,query("city_level", ob),);
        msg+=sprintf(HIC"\n ˰��:  " HIW "%5d" NOR HIC"\t\t�����˿�: " HIG "%8d\n" NOR,
        query("tax_rate", ob),query("people", ob),);
        msg+=sprintf(HIC"\n �ΰ�: " HIW "%8d" NOR HIC"\t\t�ΰ�ָ��: " HIG "%8d\n" NOR,
        query("peace", ob),query("peace_pro", ob),);
        msg+=sprintf(HIC"\n ��ҵ: " HIW "%8d" NOR HIC"\t\t��ҵָ��: " HIG "%8d\n" NOR,
        query("business", ob),query("business_pro", ob),);
        msg+=sprintf(HIC"\n ũҵ: " HIW "%8d" NOR HIC"\t\tũҵָ��: " HIG "%8d\n" NOR,
        query("farming", ob),query("farming_pro", ob),);
        msg+=sprintf(HIC"\n ˮ��: " HIW "%8d" NOR HIC"\t\tˮ��ָ��: " HIG "%8d\n" NOR,
        query("water", ob),query("water_pro", ob),);
        msg+=sprintf(HIC"\n ����: " HIW "%8d" NOR HIC"\t\t����ָ��: " HIG "%8d\n" NOR,
        query("technology", ob),query("technology_pro", ob),);
        msg+=HIY"��������������������������������������������������������������������������\n"NOR;
        return msg;
}

int do_kaifa(string arg)
{
        
        object ob = this_object();
        object me = this_player();
        string msg;
        int pro_num, lvl_num,add_num,me_score,me_balance;
        int ob_people,ob_taxrate,ob_technology,ob_fealty;
//        kaifa,money,i;

        me_score=query("score", me);
        me_balance=query("balance", me);
        ob_people=query("people", ob);
        ob_taxrate=query("tax_rate", ob);
        ob_technology=query("technology", ob)/100;
/*
        if( !query("CITY_KAIFA", me)) )
                return notify_fail("��û�еõ�����������ɣ��޷�Э��������͢�������̡�\n");
        if( query("CITY_KAIFA/name", me) != query("city_name", ob) )
                return notify_fail("��ҪЭ�������ĳ��к���������ɣ�\n");
*/
//��������С��1000�Ͳ��ü�������        
         
        if (me_score<1000)
                return notify_fail("��Ľ����������������Ƕ���۵�����������!\n");
//���С��100 gold �Ͳ��ü�������
        if(me_balance<1000000)
                return notify_fail("��Ĵ������޷����㿪������Ҫ���ʽ�Ҫ��!\n");
        if( query_temp("busy", ob) )
                return notify_fail("���˸��¹���������Ժ�........\n");
        if( !arg || ( arg!= "ˮ��" && arg!="ũҵ"
                  && arg!="�ΰ�" && arg!="��ҵ" && arg!="����"))
                return notify_fail("��Ҫ����ʲô��\n"); 
//   ��ҵ business    ��Ե + ��ò + ���Ǽ���ֵ  �����˿� ��������
        if( arg=="��ҵ")
           { 
              tell_object(me,"��˼��������������ʼЭ���ٸ�����"+CNAMEOFCITY+"����ҵ����Ⱥ����ɣ�\n");
              pro_num=query("business_pro", ob);
              lvl_num=query("business", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"����ҵ�Ѿ��㹻�����ˣ����������ȥ����������Ŀ�ˣ�\n"); 
                }
              else
              { 
                      add_num=query("per", me)+query("kar", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"�����š�"HIG+CNAMEOFCITY+"����ҵ��"+query("name", me)+"��Э�������±��Խ��Խ�����ˣ�\n"NOR,users());
                     ob_people=ob_people+lvl_num*(1+random(3));
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     }
//                 ob->set("people",ob_people);
//                 ob->set("fealty",ob_fealty);
                 set("business_pro", pro_num, ob);
                 set("business", lvl_num, ob);
                 message_vision( HIW"���е���ҵָ������ˡ�\n"NOR,me);
                } 
           }
//    ũҵ       farming     ���� + ����+ ���Ǽ���ֵ   �����˿� ��������
        if( arg=="ũҵ")
           { 
              tell_object(me,"��˼��������������ʼЭ���ٸ�����"+CNAMEOFCITY+"��ũҵ����Ⱥ����ɣ�\n");
              pro_num=query("farming_pro", ob);
              lvl_num=query("farming", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"��ũҵ�Ѿ��㹻�����ˣ����������ȥ����������Ŀ�ˣ�\n"); 
                }
              else
              { 
                      add_num=query("str", me)+query("sta", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"�����š�"HIG+CNAMEOFCITY+"��ũ����"+query("name", me)+"��Э�������±��Խ��Խ�����ˣ�\n"NOR,users());
                     ob_people=ob_people+lvl_num*(1+random(3));
                     if(ob_fealty>=5) ob_fealty-=random(5);;
                     }
//                 ob->set("people",ob_people);
//                 ob->set("fealty",ob_fealty);
                 set("farming_pro", pro_num, ob);
                 set("farming", lvl_num, ob);
                 message_vision( HIY"���е�ũҵָ������ˡ�\n"NOR,me);
                }         
           }           
//   �ΰ�   peace   �� + ��ʶ+ ���Ǽ���ֵ   �������� 
        if( arg=="�ΰ�")
           { 
              tell_object(me,"��˼��������������ʼЭ���ٸ�����"+CNAMEOFCITY+"���ΰ�����Ⱥ����ɣ�\n");
              pro_num=query("peace_pro", ob);
              lvl_num=query("peace", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"���ΰ��Ѿ��㹻�����ˣ����������ȥ����������Ŀ�ˣ�\n"); 
                }
              else
              { 
                      add_num=query("dex", me)+query("cor", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"�����š�"HIG+CNAMEOFCITY+"���ΰ���"+query("name", me)+"��Э�������±��Խ��Խ�����ˣ�\n"NOR,users());
                     if(ob_fealty<100) ob_fealty+=random(5);
                     if(ob_fealty>100) ob_fealty=100;
                     }
//                 ob->set("fealty",ob_fealty);
                 set("peace_pro", pro_num, ob);
                 set("peace", lvl_num, ob);
                 message_vision( HIC"���е��ΰ�ָ������ˡ�\n"NOR,me);
                }         
           }         
//    ˮ��  water       ���� + ����+ ���Ǽ���ֵ   �������� 
        if( arg=="ˮ��")
           { 
              tell_object(me,"��˼��������������ʼЭ���ٸ�����"+CNAMEOFCITY+"��ˮ������Ⱥ����ɣ�\n");
              pro_num=query("water_pro", ob);
              lvl_num=query("water", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"��ˮ���Ѿ��㹻�����ˣ����������ȥ����������Ŀ�ˣ�\n"); 
                }
              else
              { 
                      add_num=query("con", me)+query("cps", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"�����š�"HIG+CNAMEOFCITY+"��ˮ����"+query("name", me)+"��Э�������±��Խ��Խ�����ˣ�\n"NOR,users());
                     if(ob_fealty<100) ob_fealty+=random(5);
                     if(ob_fealty>100) ob_fealty=100;
                     }
//                 ob->set("fealty",ob_fealty);
                 set("water_pro", pro_num, ob);
                 set("water", lvl_num, ob);
                 message_vision( HIC"���е�ˮ��ָ������ˡ�\n"NOR,me);
                }         
           }        
//  ����   technology  ���� + ����   ���ӿ����ٶ�        
        if( arg=="����")
           { 
              tell_object(me,"��˼��������������ʼЭ���ٸ�����"+CNAMEOFCITY+"�ļ�������Ⱥ����ɣ�\n");
              pro_num=query("technology_pro", ob);
              lvl_num=query("technology", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"�ļ����Ѿ��㹻�����ˣ����������ȥ����������Ŀ�ˣ�\n"); 
                }
              else
              { 
                      add_num=query("int", me)+query("spi", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"�����š�"HIG+CNAMEOFCITY+"�ļ�����"+query("name", me)+"��Э���о��±��Խ��Խ�Ƚ��ˣ�\n"NOR,users());
                     }
                 set("technology_pro", pro_num, ob);
                 set("technology", lvl_num, ob);
                 message_vision( HIB"���еļ���ָ������ˡ�\n"NOR,me);
                 
                }         
           }                                   
//ÿ��ִ�п���ָ���Ҫ���ǵ�����˰�ʶԱ��ֿ�����Ӱ�� �����о����е㶯̬�� �Ǻ�
//         0-15  ֮��   �ǳ����� �����˿� ��������
//         15-30 ֮��    ����    �����˿� ���Ҳ���
//      30-40 ֮��   ΢��Թ�� �˿ڲ���  �������� ũҵ,�ΰ��ܵ��ƻ� 
//      40-60 ֮��   Թ���ص�  �˿ڼ��� �������� ũҵ,�ΰ�,��ҵ�ܵ��ƻ�
//      60-80 ֮��   ��Թ����  �˿ڴ�� ���ҿ� ����ָ�����ܵ��ƻ�
//      80-100֮��   ��������  ���Ĳ��� ����ָ������� 
       if( ob_taxrate>=0&&ob_taxrate<=15) 
           { 
             if(ob_fealty<100) ob_fealty+=random(5);
             if(ob_fealty>100) ob_fealty=100;
             if(ob_people<MAX_LEVEL*10000)
             ob_people=ob_people+(100-ob_taxrate)*(10+random(5));
             message_vision( MAG"���ڳ��е�˰�ʶ����൱�ͣ�������շǳ����⣬���кܶ���ص��˿�������ı����\n"NOR,me);
            }
           
       else if( ob_taxrate>=16&&ob_taxrate<=30)
            {  
             if(ob_people<MAX_LEVEL*10000)
             ob_people=ob_people+(100-ob_taxrate)*(10+random(5));
             message_vision( GRN"���ڳ��е�˰�ʶ�����Խϵͣ����ջ������⣬������һЩ��ص��˿�������ı����\n"NOR,me);
             }

       else if( ob_taxrate>=31&&ob_taxrate<=40)
             {
               if(ob_fealty>=5) ob_fealty-=random(5);
               pro_num=query("farming_pro", ob);
               lvl_num=query("farming", ob);
               if (pro_num > 100)
                   { 
                      pro_num = (int)pro_num-random(100);
                      set("farming_pro", pro_num, ob);
                    }                                      
               pro_num=query("peace_pro", ob);
               if (pro_num > 100)
                   { 
                      pro_num = (int)pro_num-random(100);
                      set("peace_pro", pro_num, ob);
                    }      
               message_vision( CYN"���е�һЩ����Ϊ�ٸ���˰�ʶ��Ĳ�̫����΢��Թ�ԣ������ڳ��﷢��С͵��һЩ��Ը�����ũ��\n"NOR,me);
               }
        else if( ob_taxrate>=41&&ob_taxrate<=60)
             {
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     ob_people=ob_people-ob_taxrate*(10+random(3));
                     pro_num=query("farming_pro", ob);
                     if (pro_num > 100)
                   { 
                      pro_num = (int)pro_num-random(100);
                      set("farming_pro", pro_num, ob);
                    }  
                 pro_num=query("peace_pro", ob);
                 if (pro_num > 100)
                    { 
                      pro_num = (int)pro_num-random(100);
                      set("peace_pro", pro_num, ob);
                     }    
                 pro_num=query("business_pro", ob);
                 if (pro_num > 100)
                     { 
                      pro_num = (int)pro_num-random(100);
                      set("business_pro", pro_num, ob);
                     }     
                     message_vision( YEL"���а���Թ���ص����󲿷�����Ҳ��Ϊ�ٸ��յ�˰̫���ˣ������ڳ��и���С�ƻ�������Թ�Թٸ��Ĳ�����\n"NOR,me);
                     }
         else if( ob_taxrate>=61&&ob_taxrate<=80)
             {
                     if(ob_fealty>=5) ob_fealty-=random(5); 
                     ob_people=ob_people-ob_taxrate*(10+random(6));                    
                     if( query("farming", ob)>5 && random(2) == 1 )
                          addn("farming", -1, ob);
                if( query("water", ob)>5 && random(2) == 1 )
                          addn("water", -1, ob);
                     if( query("business", ob)>5 && random(2) == 1 )
                          addn("business", -1, ob);
                     if( query("technology", ob)>5 && random(2) == 1 )
                          addn("technology", -1, ob);
                     if( query("peace", ob)>5 && random(2) == 1 )
                          addn("peace", -1, ob);
                     message_vision( BLU"������Թ���ڣ�����һ����Ϊ�ٸ��յ�˰̫���ˣ����𽥶�����ĵط���Աʧȥ���ġ�\n"NOR,me);
             }  
        else
             {
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     ob_people=ob_people-ob_taxrate*(10+random(9));                     
                     if( query("farming", ob)>5 && random(2) == 1 )
                          addn("farming", -2, ob);
                if( query("water", ob)>5 && random(2) == 1 )
                          addn("water", -2, ob);
                     if( query("business", ob)>5 && random(2) == 1 )
                          addn("business", -2, ob);
                     if( query("technology", ob)>5 && random(2) == 1 )
                          addn("technology", -2, ob);
                     if( query("peace", ob)>5 && random(2) == 1 )
                          addn("peace", -2, ob);
                     message_vision( RED"�������ڻ������а����޷����ܹٸ����̰����׷ױ������硣\n"NOR,me);
                     }  
// ÿ��ִ��ָ������50�Ľ������� ��һ���Ĵ��뱾�ǵ�˰���й� ���˰�ʴ�100�Ͳ���Ǯ��
        me_score = me_score-50;
        me_balance = me_balance-2000*(100-ob_taxrate);
        set("score", me_score, me);
        set("balance", me_balance, me);
//��ִֹ�й����г��ָ��˿� ������ֵ������Χ
        if( ob_people<0) ob_people=1;
        set("people", ob_people, ob);
        if (ob_fealty<0) ob_fealty=0;
        if (ob_fealty>100) ob_fealty=100;
        set("fealty", ob_fealty, ob);
        save();
        set_temp("busy", 1, ob);
        remove_call_out("enough_rest");
//1���ȡ��busy
        call_out("enough_rest", 1);
        return 1;
}
int do_tax(string arg)
{  int ob_taxrate,taxrate;
   object ob=this_object();
   if( query_temp("busy", ob) )
        return notify_fail("���˸��¹���������Ժ�........\n");
   if( !arg
        ||      !sscanf(arg, "%d", taxrate) )
      return notify_fail("���뽫˰�ʶ�Ϊ���٣�\n");
   if(taxrate>100||taxrate<0)
      return notify_fail("˰��ֻ����0��100֮�䣡\n");
   ob_taxrate=taxrate;
   set("tax_rate", ob_taxrate, ob);
   save();
   set_temp("busy", 1, ob);
   remove_call_out("enough_rest");
//1���ȡ��busy
   call_out("enough_rest", 1);
   return 1;
}
    
void enough_rest()
{
        delete_temp("busy");
}
