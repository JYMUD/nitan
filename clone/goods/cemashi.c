
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "����ʯ" NOR, ({ "cema shi", "cema", "shi", "stone" }) );
        set_weight(100);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "һ��⻬�����ʯͷ����Լ�ɼ���������һƥ��������Ȼ�γɡ�\n"
                            "ʹ�� loghorse �����ʹ������һ�������¼�㡣\n" 
                            "�����ʱ��ʹ�ã���ý�����ʯ����ֿ⣬���ⶪʧ��\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "��");
                set("auto_load", 1);
        }

        setup();
}

void init()
{
        add_action("do_changing", "loghorse");
}

int do_changing(string arg)
{
        object me;
        me = this_player();

        if( query("horse/stone", me) >= 5 )
                return notify_fail("��ֻ��ͨ������ʯ������ӵ����������¼�㡣\n");

        addn("horse/stone", 1, me);
        write(HIM "����ʯʹ�óɹ�����������¼�������ˣ�\n" NOR);
        me->save();
        destruct(this_object());

        return 1;
}

