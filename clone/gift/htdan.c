// xiandan.c �ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "��Ϳ��" NOR, ({ "hutu dan", "dan", "hutu" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ��԰԰����ĵ�ҩ����˵���˿��Խ���������\n");
                set("value", 10000);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);

        if( query("gift/int/succeed", me)<1 )
        {
                tell_object(me, "��������ú���ûʲô���á�\n");
        } else
        {
                tell_object(me, HIG "һ�ɻ�����Ȼ����������"
                            "��ͷʹ���ѣ�ǡ�ڴ�ʱһ�ɻ���֮��"
                            "��Ȼ���𣬶ٸ����Ӳ���ʹ�ˡ�\n");
                addn("int", -1, me);
                addn("gift/int/succeed", -1, me);
                if( query("gift/int/all", me)>0 )
                addn("gift/int/all", -1, me);
                addn("gift/xiandan", -1, me);
        }

        destruct(this_object());
        return 1;
}

