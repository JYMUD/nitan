#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "���嵤" NOR, ({ "xiaoli dan", "xiaoli", "dan" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "һ����ɫ�ľ����浤���������񻰰�Ĺ�Ч����˵\n"
                                "���˺�������������������\n" NOR);
                set("value", 500000);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);
                       
        set("total_hatred", 0, me);
        
        write(HIM "��ֻ������̨һƬ�����������ޱȣ�������������ˡ�\n" NOR);
        destruct(this_object());
        return 1;
}
