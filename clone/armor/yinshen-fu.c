
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(NOR + WHT "�����" NOR, ({ "yinshen fu", "yinshen", "fu" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIY "����һ�ŵ�������˵װ��������������١�\n" NOR);
                set("value", 10000);
                set("armor_prop/invisible", 1);
                set("special/desc", "װ������������٣������޷��鿴����Ĵ��ڡ�");
        }
        setup();
}

int query_autoload()
{
        return 1;
}