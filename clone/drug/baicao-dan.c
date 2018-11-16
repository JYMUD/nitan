// Code of ShenZhou
#include <ansi.h>

inherit ITEM;
void create()
{
   set_name("�ٲݵ�", ({"baicao dan", "dan"}));
   if (clonep())
      set_default_object(__FILE__);
   else
   {
      set("unit", "��");
      set("value", 4000);
      set("no_sell", 1);
      set("long", "����һ��ؤ��İٲݵ����������˱�����\n");
      set("medicine", 1);
      set("only_do_effect", 1); 
   }
   setup();
}

int do_effect(object me)  
{
   message_vision("$N����һ��" + name() + "��\n", me);
   
   if( query("eff_qi", me)<query("max_qi", me)/6
    || query("eff_jing", me)<query("max_jing", me)/6){
        write("�����ƹ��أ���ʳ��ҩ�����Ծ����£�\n");
   }
   else if( query("eff_qi", me) == query("max_qi", me )
    && query("eff_jing", me) == query("max_jing", me)){
        me->receive_wound("qi", 50);
        me->receive_wound("jing", 50);
        write( HIR "��û�˺��ҷ�ʳ��ҩ�����д󺦣�\n\n" NOR );
   }
   else {
        if( query("eff_qi", me)<query("max_qi", me)){
                me->receive_curing("qi", 50);
        }
        
        if( query("eff_jing", me)<query("max_jing", me)){
                me->receive_curing("jing", 50);
        }
        
        message_vision(YEL "$Nֻ�����ƴ�Ϊ��ת���ɼ��˵���Ч��\n\n" NOR, me);
   }
                
   destruct(this_object());
   return 1;
}
