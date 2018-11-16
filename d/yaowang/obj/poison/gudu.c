// gudu.c

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + HIB "�ƶ�" NOR, ({ "gu du", "gu", "du", "gudu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB "����һ�����ٶ�֮�������ƶ��ɵĶ�ҩ����������֮����\n" NOR);
                set("base_unit", "��");
                set("base_value", 100);
                set("base_weight", 10);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 300,
                        "id"    : "yaowang",
                        "name"  : "�ƶ�",
                        "duration" : 20,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        message_vision("$Nһ�������ѹƶ�ȫ�����������С�\n", me);
        set_temp("die_reason", "���˹ƶ�����������", me);
        me->die();

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}

