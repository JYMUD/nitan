#include <ansi.h>
inherit ITEM; 

void create()
{
	      set_name(HIC"����"NOR, ({"fwar flag","flag"}) );
        set_weight(300);
        set("unit", "��");
        set("long", "һ�����������Ų�֪����ͼ�ڣ��������ƺ����Խ�������\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
        set("no_get", 1);
        setup();
}
void init()
{
	add_action("do_get","get");
	add_action("do_drop","drop");
}
int do_get(string arg) {
	object ob, me = this_player();
	if(!me) return 0;
	if(arg == "all" || !arg || !ob = present(arg, environment(me))) return 0;
	if(ob != this_object()) return 0;
	if(present("fwar flag", me)) return notify_fail("�������Ѿ���һֻ�����ˣ���ȥ��������ɡ�\n");
	if(ob->move(me)) {
		me->start_busy(2);
		FWAR_D->get_flag(me, ob);
	}
  return 1;
}
int do_drop(string arg) {
	object ob, me = this_player();
	if(!me) return 0;
	if(arg == "all" || !arg || !ob = present(arg, me)) return 0;
	if(ob != this_object()) return 0;
	if(ob->move(environment(me))) {
		FWAR_D->drop_flag(me, ob);
	}
  return 1;
}

int do_stab(object me)
{
	object room;
	if(!room = environment(me)) return 0;
	if(!room->query("stab_flag")) return notify_fail(name()+"ֻ�ܲ�����㡣\n");
	if(room->query("party") != me->query_temp("flag_war/party")) return notify_fail(name()+"ֻ�ܲ������Լ��Ķ�����㡣\n");
	FWAR_D->stab_flag(me, this_object());
	return 1;
}