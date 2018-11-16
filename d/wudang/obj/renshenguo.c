#include <ansi.h>
inherit ITEM;

void init(object ob)
{
        if (find_call_out("destguo") != -1)
                return;

        remove_call_out("destguo");
        call_out("destguo", 10, ob);
}

void destguo(object ob)
{
        ob = this_object();

        message_vision(HIM "\nֻ��$N" HIM "��������ˮ����һ��͸��õ��ˡ�\n\n"
                       NOR, ob);
        destruct(ob);
}

void create()
{
        set_name(HIM "�˲ι�" NOR, ({"renshen guo", "renshen", "guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ֻ");
                set("long", HIM "����һֻ�Ѿ����͵��˲ι������������"
                            "�ܲ�����С����\n" NOR);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        addn("max_neili", 10, me);

        if( query("max_neili", me)>me->query_neili_limit() )
                set("max_neili", me->query_neili_limit(), me);

        set("neili",query("max_neili",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);

        message_vision(HIM "\n$N" HIM "����һö�˲ι���ֻ���þ���������"
                       "�����棬����ԴԴ��\n�����������ٸе������ɿʡ�\n\n", me);

        destruct(this_object());
        return 1;
}