// Code of ShenZhou
// baihu.c �׻�������
// xQin 04/01

#include <ansi.h>

inherit ITEM;
int cure_ob(string);
void create()
{
   set_name(HIW"�׻�������"NOR, ({"baihu wan", "duoming wan", "wan"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("no_sell",1);
      set("no_get",1);
      set("no_drop",1);
      set("unit", "��");
      set("value", 100000);
   }
   setup();
}


int cure_ob(object me)
{
   
        if (me->query_condition("bonze_drug") > 0)
        {
        addn("max_neili", -1, me);
        message_vision(HIR"$N����һ��" + name() + HIR"��ֻ�������������ڷ��ڣ�ԭ����ʳҩ����࣬�ʵ��䷴��\n"NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);

   
       message_vision(HIW"$N����һ��" + name() + HIW"��ֻ��һ�������ӵ���������˲���������ȫ�����ع鵤�\n"NOR, me);
       me->apply_condition("bonze_drug", 60);
       destruct(this_object());
       return 1;
}