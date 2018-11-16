// Code of ShenZhou
// Ryu 4/17/97

inherit ITEM;
inherit F_AUTOLOAD;
#include <ansi.h>;
int is_container() { return 1; }
int do_put(string);
void create()
{
        set_name("���", ({"yu di", "flute", "di"}));
        set_weight(80);
        set_max_encumbrance(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
         set("long", "����Ѷ̵ó��棬ֻ�����ߴ�������ͨ���ף���Ө�ɰ���\n");
                set("unit", "֧");
                set("value", 1);
                set("no_sell", 1);
                set("fire_source", 30);
                set("no_drop", 1);
                set("no_get", 1);
                set("no_steal", 1);
        }
}
int query_autoload() { return 1; }
void init()
{
        add_action("do_blow", "blow");
        add_action("do_blow", "play");
        add_action("do_put", "put");
}
int do_blow(string arg)
{
        object ob, me=this_player();

        if (!arg && arg != "di" && arg != "yu di") return notify_fail("��Ҫ��ʲô��\n");
        
        if (me->is_busy())
        return notify_fail("��ǰһ��������û�����ꡣ\n");

        message_vision("$N����ѷŵ��ڱߣ�����һ����ֻ��һ�󼫼⼫ϸ��������ԶԶ���˳�ȥ��\n", me);

        if( !query("no_fight", environment(me) )
        && query("fire_source") > 0 && me->query_skill("poison", 1) > 99){        

        message_vision(HIR"�����������������ͻȻ�ɳ���ӡӡ��һ����ǣ����Ƕ���Ϩ���漴���������һ���죬�����գ�������������Ż������䡣\n"NOR, me);

        addn("fire_source", -1);
        ob=new("/d/xingxiu/obj/flute_fire");
        ob->move(environment(me));
        }
        return 1;
}
int do_put(string arg)
{
        object ob, obj, me = this_player();
        string item, target;
        int amount;

        if( !arg || sscanf(arg, "%s in %s", item, target) != 2 )
                return notify_fail("��Ҫ��ʲô�����Ž����\n");
        
        if( !objectp(obj = present(item, me)) )
                return notify_fail("��Ҫ��˭ʲô������\n");

        if (!id(target)) return 0;

        if( item == "all" ) {
                write("����һ��һ�����ɡ�\n");
                return 1;
        }
        if( query("id", obj) != "liu huang"){
                write(query("name", obj)+"����Ѷ���̫���ˡ�\n");
                return 1;
        }
                message_vision( sprintf(HIY "$N��һ%s%s�Ž�%s��\n" NOR,
                        query("unit", obj),obj->name(),
                        this_object()->name()),me );
                destruct(obj);
                addn("fire_source", 1);
        return 1;
}
