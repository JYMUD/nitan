// xiandan.c �ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "�ɵ�" NOR, ({ "xian dan", "dan", "xiandan" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ��԰԰���ɵ�����˵���˿�����ǿ������"
                    "�����������������\n");
                set("value", 10000);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);
        if( query("gift/xiandan", me) >= 5 || 
            query("gift/int/succeed", me) >= 5 )
        {
                message_vision("$N��Ȼ�����ۡ�������һ�ء�\n", me);
                tell_object(me, "���������ǳ��Ŀࡣ\n");
        } else
        if (random(5) == 0)
        {
                addn("gift/int/fail", 1, me);
                tell_object(me, "��������ú���ûʲô���á�\n");
        } else
        {
                tell_object(me, HIG "һ�ɻ�����Ȼ����������"
                            "��ͷʹ���ѣ�ǡ�ڴ�ʱһ������֮��"
                            "��Ȼ���𣬶ٸ���̩�ޱȡ�\n");
                addn("int", 1, me);
                addn("gift/int/succeed", 1, me);
        }

        if( query("gift/xiandan", me)<5 )
                addn("gift/xiandan", 1, me);
        destruct(this_object());
        return 1;
}
