// unknow.c δ���ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "����ɵ�" NOR, ({ "huohong xiandan", "dan", "xiandan" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ��԰԰�Ļ���ɵ�����˵���˿�����ǿ���������������������\n");
                set("value", 10000);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);
        if( query("gift/unknowdan", me) >= 5 || 
            query("gift/dex/succeed", me) >= 5 )
        {
                message_vision("$Nҡҡ�λεģ�ͻȻ��žડ�һ����ˤ�˸���ͷ��\n", me);
                tell_object(me, "����ó����Ժ�ͷ�ؽ���ġ�\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/dex/fail", 1, me);
                tell_object(me, "��������ú���ûʲô���á�\n");
        } else
        {
                tell_object(me, HIM "��ʱ��������ȹ����ѣ�һʱ��ʹ��"
                            "�̣��������˹�ȥ��\n" NOR);
                addn("dex", 1, me);
                addn("gift/dex/succeed", 1, me);
        }

        if( query("gift/unknowdan", me)<5 )
                addn("gift/unknowdan", 1, me);
        destruct(this_object());
        return 1;
}
