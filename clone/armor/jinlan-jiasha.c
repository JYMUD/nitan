

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIR "��" HIC "��" HIM "����" NOR, ({ "jinlan jiasha", "jinlan", "jiasha" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "���˴�˵����ɮ�������Ľ������ģ�ֻ�������ҫ�������������ۣ����������հ���͡�\n"
                            HIC "��ϸ��ȥ����������Լ���ּ������֣�" HIG "��׹�����������ֻ�\n" NOR);
                set("value", 800000);
                set("armor_prop/armor", 800);
                set("armor_prop/str", 7);
                set("armor_prop/dex", 7);
                set("armor_prop/int", 7);                                
                set("armor_prop/con", 7);
                set("limit", ([
                        "exp"  :   100000000,
                        "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
