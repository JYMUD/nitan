

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(NOR + WHT "�콵����Ƥ����" NOR, ({ "renpi baoyi", "renpi", "baoyi" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + WHT "��˵����һ������Ƥ�Ƴɵı��£������ƺ���¼��ĳ�����ص���ѧ��\n" NOR);
                set("material", "steel");
                set("value", 80000000);
                set("armor_prop/armor", 3000);
                set("armor_prop/parry", 200);
                set("special/desc", "��Ч�м����200����\n" +
                                    "���Ϻ��ʩչ��������֮�������ڡ�\n"
                );
                set("armor_prop/daojian_ben", 1);
                set("limit", ([
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
