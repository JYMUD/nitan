#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(YEL "����" NOR, ({"hua zhong", "hua", "zhong"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һö�޷�ȷ��Ʒ�ֵĻ��֡�\n");
                set("unit", "ֻ");
                set("value", 1);
                set("food_remaining", 1);
                set("food_supply", 10);
        }
}

void init()
{
        add_action("do_zhonghua", "zhonghua");
}

int do_zhonghua()
{
        object me, ob, where;
 
        me = this_player();
        ob = this_object();
        where = environment(me);

        if( query("short", where) != "��԰" )
                return notify_fail("�����ƺ����ʺ��ֻ��ɣ�\n");

        if( query("combat_exp", me)<8000 )
        {
                tell_object(me, "��ľ�����ǳ�������ȵ������߶��߶��ɡ�\n");
                return 1;
        }

        if( query("combat_exp", me)>30000 )
        {
                tell_object(me, "�������ݴ�Ų��ʺ��ֻ��˰ɡ�\n");
                return 1;
        }

        if( query_temp("zhonghua", me) == 1 )
        {
                tell_object(me, "�����Ѿ������ˣ����ڸ�����"
                                HIY "(peiyu)" NOR "�����ˡ�"
                                "\n");
                return 1;
        }

        message_vision(HIC "$N" HIC "�����ڵ�������һ��С"
                       "�ӣ��ѻ��ַ��˽�ȥ��\n" NOR, me);
        tell_object(me, "�����Ѿ������ˣ����ڸ�����" HIY
                        "(peiyu)" NOR "�����ˡ�\n");
        addn_temp("zhonghua", 1, me);
        destruct(ob);
        addn("jing", -50, me);
        return 1;
}