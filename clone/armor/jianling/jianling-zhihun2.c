#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIG "����֮��" NOR, ({ "jianling zhihun2", "zhihun2" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIG "����һ�����������ӻû����ɲ������ڰ������ϵı��£���������ɫ��â������һֻ������\n" NOR);
                set("material", "steel");
                set("value", 80000000);
                set("armor_prop/parry", 300);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "��������װ������֮һ������֮ŭ������֮�ۡ�����֮��������֮�꣩��\n"
                                    "                  ���ڽ�����װ�Ĵ�˵�μ� help boss\n"
                                    "                  ��Ч�м����300����\n");
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
