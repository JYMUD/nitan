// Code of ShenZhou
// baodan.c ���ӵ�
// sdong 08/06/98
// modified by xQin 9/00 to fix the unlimited consumption bug

#include <ansi.h>

inherit ITEM;

int cure_ob(string);

void init();

void create()
{
                  set_name("���ӵ�", ({ "baozi dan", "dan" }) );
                  set_weight(1000);
                  if( clonep() )
                                         set_default_object(__FILE__);
                  else {
                                         set("unit", "��");
                                         set("long", CYN"����һ����ȭͷһ����ı��ӵ����ֺ����̡�\n"NOR);
                                         set("value", 10000);
                set("no_sell", 1);
                                         set("medicine", 1);
                  }
set("wposition", "/clone/drug/baodan.c");
                  setup();
}

int cure_ob(object me)
{
                  addn("food", 50, me);


                  if ( (int)me->query_condition("bonze_drug" ) > 0 ){
                                         addn("max_jingli", -1, me);
                                         addn("eff_jingli", -1, me);
                                         set("jingli", 0, me);
                                         me->apply_condition("bonze_drug", 30);
                                         message_vision(HIR "$N����һ�ű��ӵ���ֻ���øγ���ϣ��������ѣ�ԭ����ʳ̫��ҩ�ҩЧ�ʵ��䷴��\n" NOR, this_player());
                                         destruct(this_object());
                                         return 1;
                  }

                  if( !query_temp("qz/baozidan", me)){
                                         addn_temp("apply/attack", 100, me);
                                         set_temp("qz/baozidan", 1, me);
                                         if(random(2)) set("max_jingli",query("max_jingli",me)+2,me);
                                         me->start_call_out((:call_other,__FILE__,"remove_effect",me:),query("con", me)*10);
                  }

                  addn("neili", 500, me);
                  addn("jingli", 300, me);
                  me->apply_condition("bonze_drug",
                  me->query_condition("bonze_drug")+30);
                  message_vision(HIY "$N����һ�ű��ӵ���ֻ����ȫ�������������־��������о���\n" NOR, me);
                   destruct(this_object());
                  return 1;
}

void remove_effect(object me)
{
                  addn_temp("apply/attack", -100, me);
                  delete_temp("qz/baozidan", me);
                  tell_object(me, "����һ��������ӵ��������ྡྷ������ʧ�ˡ�\n");
}
