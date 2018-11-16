#include <ansi.h>
inherit ITEM; 

void create()
{
	      set_name(HIG"����ս - "HIW"���׺䶥��"NOR, ({"fwar five thunder seal","seal"}) );
        set_weight(300);
        set("unit", "��");
        set("long", "����սר��������Ʒ��ʹ��(apply)����ٻ����׶��������ڵغ䶥��\n");
        set("value", 1);
        set("can_be_applied", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}

int do_apply(object me) {
	object ob;
	if(!me) return 0;
	ob = this_object();
  if(environment() != me) return notify_fail(name()+"���������ϡ�\n");
  if(!sizeof(me->query_temp("flag_war"))) return notify_fail(name()+"ֻ��������ս��ʱ��ʹ�á�\n");
  if(!sscanf(base_name(environment(me)), "/d/flagwar/%*s")) return notify_fail(name()+"ֻ��������ս��ʹ�á�\n");
  message_vision("$N����$n�������૆��������������ڣ���ָ��$n���һ����š�\nͻȻ��$nð��ҫ�۵Ĺ�â��$n��ʼȼ�ղ��ͷų�ǿ���������\n", me, ob);
  me->start_busy(3);
  ob->set("apply_room", base_name(environment(me)));
  SCHEDULE_D->set_event(1, 0, this_object(), "thunder_count", me, 1);

  return 1;
}

int thunder_count(object me, int num)
{
	int damage;
	string *color_str = ({ HIC,HIM,HIB,HIG });
	object ob = this_object();
	
	if(ob->query("apply_room") != base_name(environment(me))) {
		message_vision("$Nȼ�յ����ˡ�\n", ob, me);
		destruct(ob);
		return 1;
	}
	
	if(num >= 5) {
		message_vision(HIR"��ǿ���һ�����װ�����ǿ����������¡�\n"NOR, ob, me);		
    foreach(object ppl in all_inventory(environment(me))) {
    	if(ppl == me) continue;
    	if(ppl->query_temp("flag_war/guard")) {
    		ppl->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N���ϵ��������Ч������Ч�õֵ����׵ĺ����\n"NOR, ppl);
    	  continue;
    	}
    	damage = 5000*num;
      ppl->receive_damage("qi", damage, me);
      COMBAT_D->report_status(ppl);
      me->want_kill(ppl); 
      me->fight_ob(ppl); 
      ppl->kill_ob(me); 
      if(random(2)) ppl->unconcious();
    }		
		message_vision("$Nȼ�յ����ˡ�\n", ob, me);
		destruct(ob);
		me->start_busy(2);
	} else {
		message_vision(color_str[num-1]+"����������ܲ����·��ܵ�$N"+color_str[num-1]+"����������"+chinese_number(num)+color_str[num-1]+"�����׷������¡�\n"NOR, ob, me);
    foreach(object ppl in all_inventory(environment(me))) {
    	if(ppl == me) continue;
    	if(ppl->query_temp("flag_war/guard")) {
    		ppl->add_temp("flag_war/guard", -1);
    		message_vision(HIY"$N���ϵ��������Ч������Ч�õֵ����׵ĺ����\n"NOR, ppl);
    	  continue;
    	}
    	damage = 5000*num;
      ppl->receive_damage("qi", damage, me);
      COMBAT_D->report_status(ppl);
      me->want_kill(ppl); 
      me->fight_ob(ppl); 
      ppl->kill_ob(me); 
    }
		num++;
		SCHEDULE_D->set_event(1, 0, this_object(), "thunder_count", me, num);
	}
	me->start_busy(3);
	return 1;
}