
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIW "ˮ����" NOR, ({ "shuijing guan3", "shuijing", "guan3" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "��");
                set("long", HIM "����һ����ˮ���������ɵ�ͷ�ڣ��ֹ������ޱȣ��˼亱�С�\n" 
                            HIC "����������о���ѧϰ��������20%��\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 100);
                set("armor_prop/up_yanjiu_times", 20);
                set("special/desc", HIR "����������о���ѧϰ��������20%��" NOR);
                set("limit", ([
                        "int"             :  40,
                        "exp"             :  8000000,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}