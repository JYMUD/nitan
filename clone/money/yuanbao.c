// gold.c
#include <ansi.h>
inherit MONEY;

void create()
{
        set_name(HIY "��Ԫ��" NOR, ({"yuanbao", "yuanbao_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "yuanbao");
                set("long", HIY "һ����ɫ��Ԫ��������������������������ġ�\n" NOR);
                set("unit", "Щ");
                set("base_value", 1000000);
                set("base_unit", "��");
                set("base_weight", 1);
        }
        set_amount(1);
}

