
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIW "ˮ����" NOR, ({ "shuijing guan2", "shuijing", "guan2" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "��");
                set("long", HIM "����һ����ˮ���������ɵ�ͷ�ڣ��ֹ������ޱȣ��˼亱�С�\n" 
                            HIC "����������о���ѧϰ��������15%��\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 100);
                set("armor_prop/up_yanjiu_times", 15);
                set("special/desc", HIR "����������о���ѧϰ��������15%��" NOR);
                set("limit", ([
                        "int"             :  40,
                        "exp"             :  12000000,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}