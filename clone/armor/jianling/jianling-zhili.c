#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIG "����֮��" NOR, ({ "jianling zhili", "zhili"}) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIG "����һ�ŵ���ɫ�Ļ���������������������һ�㡣\n" NOR);
                set("value", 10000000);
                set("limit", ([
                        "exp"    :   50000000,
                ]));
                set("armor_prop/int", 50);              
                set("armor_prop/qy", 3);
                set("armor_prop/fy", 3);

                set("armor_prop/T_jianling", 1);
                set("special/desc", "��������װ������֮һ������֮ŭ������֮�ۡ�����֮��������֮�꣩��\n"
                                    "                  ���ڽ�����װ�Ĵ�˵�μ� help boss\n");

                set("limit", ([
                         "exp" : 100000000,
                         "thborn" : 1,
                         "jianling": 1, // equip.c�����ƣ�����Ҫ�����ɹ�����1�κ����װ��
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
