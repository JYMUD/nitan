#include <armor.h>
#include <ansi.h>

inherit CLOTH;
void check_color(); 
void create()
{
   set_name(YEL "��ɫ����" NOR, ({ "color skirt","skirt" }) );
   set_weight(20);
                set("long", "ȡ�ʺ���ɫ�������������ҹ������֯�ɡ� \n");
     set("material", "silk");
     set("unit", "��");
     set("armor_prop/armor",50 ); 
     set("armor_prop/per", 20);
     set("female_only", 100);  
   setup();
         call_out("check_color",3);
  }
 
int query_autoload(){ return 1;}

void init()
{
       object me;
       object ob = this_object();
  
       if (!environment(ob)||!interactive(environment(ob))) {
                 return;
                    }
       me = this_player();
       if (!geteuid(me)||geteuid(me)!="night")  {
       tell_object(me,"��ɫ���ѻ�Ϊһ��ѣĿ�Ĺ⻪����ʧ���˿����С�\n");  
                 destruct(ob);
                    } 
      return;
} 

void check_color()
{
     object ob = this_object(); 
  remove_call_out("check_color");
       switch ((int)random(7)) {
           case 0 : 
              set("name", HIG"��ɫ����"NOR, ob);
               break; 
           case 1 : 
              set("name", HIW"��ɫ����"NOR, ob);
               break;
           case 2 :
              set("name", HIR"��ɫ����"NOR, ob);
               break;
           case 3 :
              set("name", HIY"��ɫ����"NOR, ob);
               break;
           case 4 :
              set("name", HIM"��ɫ����"NOR, ob);
               break;
           case 5 :
              set("name", HIC"��ɫ����"NOR, ob);
               break; 
           case 6 :
              set("name", YEL"��ɫ����"NOR, ob);
               break;
           default:
                break;
                   } 
        call_out("check_color",3);
}
