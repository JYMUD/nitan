// earth.c ����

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "����" NOR, ({ "yu sui", "earth" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", YEL "����һ�����裬�������켺�������Ӷ������ǣ�ɫ�ƣ���������\n" NOR);
                set("value", 2000);
                set("unit", "��");
                set("magic/element", "earth");
        }
        setup();
}
