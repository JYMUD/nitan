#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name("�ߵ���", ({ "shedan fen", "shedan", "fen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", GRN "����һ���������˵��ߵ��ۡ�\n" NOR);
                set("value", 2000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("eff_qi", me) >= query("max_qi", me)-20 )
                return notify_fail("��������Ѫ��ӯ������Ҫ���ߵ��ۡ�\n");

        if (random(2) == 0)
        {
                message_vision(WHT "$N" WHT "����һ���ߵ��ۣ�����"
                               "���������ۣ������ϵ���\n" NOR, me);
                destruct(this_object());
                return 1;
        }
        addn("qi", 30, me);
        addn("eff_qi", 20, me);
        message_vision(HIY "$N" HIY "����һ���ߵ��ۣ��پ�������ӿ"
                       "���������Щ��\n" NOR, me);
        destruct(this_object());
        return 1;
}