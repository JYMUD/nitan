
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIW "ˮ����" NOR, ({ "shuijing guan", "shuijing", "guan" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "��");
                set("long", HIM "����һ����ˮ���������ɵ�ͷ�ڣ��ֹ������ޱȣ��˼亱�С�\n" 
                            HIC "����������о���ѧϰ��������10%��\n" NOR);
                set("value", 3500000);
                set("armor_prop/armor", 100);
                set("armor_prop/yanjiu_times", 10);
                set("special/desc", HIR "����������о���ѧϰ��������10%��" NOR);
                set("require", ([
                        "int"             :  30,
                        "exp"             :  5000000,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
