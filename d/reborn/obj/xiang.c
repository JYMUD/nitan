// xiang.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG "������" NOR, ({ "magic xiang" }) );
        set_weight(2000);
        if( clonep() ){
                set_default_object(__FILE__);
        } else {
                set("value", 10);
                set("unit", "֧");
                set("long", MAG "����һ֧�����㣬��˵������������̳�����ٻ����ɳ��֡�\n" NOR);
        }
        setup();
}

void start_borrowing()
{
        remove_call_out("destroy");
        call_out("destroy", 30 + random(20));
}

void destroy()
{
        if (environment())
                message("visoin", RED "�����㽥����Ϩ���ˣ�ֻ������һ��ҽ���\n" NOR,
                        environment());
        destruct(this_object());
}