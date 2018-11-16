#include <ansi.h>

inherit ITEM; 

void create()
{
	      set_name(HIG"����ս - "HIW"̫�ų���"NOR, ({"fwar remote antiquity fire arrow","arrow"}) );
        set_weight(300);
        set("unit", "��");
        set("long", "����սר��������Ʒ��ʹ��(shoot arrow on <Ŀ��>)���л�����Ŀ��������\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}

void init() 
{
   add_action("do_shoot","shoot");
}
int do_shoot(string arg) {
	object me, ob, target;
	string id;
	int damage;
	me = this_player();
	if(!me) return 0;
	ob = this_object();
  if(environment() != me) return notify_fail(name()+"���������ϡ�\n");
  if(me->is_busy()) return notify_fail("����һ��������û����ɡ�\n");

  if(!sscanf(base_name(environment(me)), "/d/flagwar/%*s")) return notify_fail(name()+"ֻ��������ս��ʹ�á�\n");
  if(!sizeof(me->query_temp("flag_war"))) return notify_fail(name()+"ֻ��������ս��ʱ��ʹ�á�\n");
  if(!arg || sscanf(arg, "arrow on %s", id) != 1) return notify_fail("ָ���ʽ��shoot arrow on <Ŀ��>��\n");
  if(!target = present(id, environment(me))) return notify_fail("����û������ˡ�\n");
  if(target == me) return notify_fail("��ֻ������ˡ�\n");
  if(!target->query_temp("flag_war")) return notify_fail("��ֻ�ܶ�����ս����ʹ�á�\n");
  message_vision("$N����$n��׼"+target->name()+"��ͻȻ��ɫһ�����������\n$nЮ�����ȵĻ��׷ѭ"+target->name()+"��ȥ��\n", me, ob);
  me->want_kill(ob);
  damage = 1000+random(2000);
  target->receive_damage("qi", damage, me);
  COMBAT_D->report_status(target);
  me->fight_ob(target); 
  target->kill_ob(me);
  me->start_busy(5);
  if(random(3) >= 1) {
  message_vision(HIY"ͻȻ��$n�⻪��ʢ����Ȼɢ����������Ϣ����$N��\n", target, ob);
    	if(target->query_temp("flag_war/guard")) {
    		target->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N���ϵ��������Ч������Ч�õֵ�ס������Ϣ��\n"NOR, target);
    	} else target->unconcious();
  }
  destruct(ob);
  return 1;
}