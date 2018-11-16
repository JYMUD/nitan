#include <ansi.h>
inherit ITEM;

void create()
{
        set_weight(100);
        set_name(HIW "���Ǻ��ķ�" NOR, ({"qixing-haitang fen", "qixing fen", "fen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIW "����һƿ��ɫ�ľ綾��ĩ����ɱ�������Ρ�\n" NOR);
                set("value", 50000);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                              "id"    : "yaowang", 
                        "name"  : "���Ǻ��ķ�",
                        "duration": 15,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$Nһ�����������Ǻ��ķ۵��������С�\n", me);
        set_temp("die_reason", "�������Ǻ��ķ�ȥ���ڰ��޳���", me);
        me->die();
        destruct(this_object());
        return 1;
}