#include <ansi.h>
inherit ITEM; 

void create()
{
	      set_name(HIG"����ս - "HIW"���ӡ"NOR, ({"fwar five ghost seal","seal"}) );
        set_weight(300);
        set("unit", "��");
        set("long", "����սר��������Ʒ��ʹ��(apply)��ɽ����������ʱ��æµ״����\n");
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
	if(!me->query_temp("flag_war/move_busy")) return notify_fail("������û����Ϊ�������Ӷ�������æµ״����\n");
  message_vision("$N����$n�������૆��������������ڣ���ָ��$n���һ����š�\nͻȻ��$nð��΢΢�Ĺ�â��$N��������֪����������Щ��ͬ�ˡ�\n", me, ob);
	me->delete_temp("flag_war/move_busy");
  destruct(ob);
  return 1;
}