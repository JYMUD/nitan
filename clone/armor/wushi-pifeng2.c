
#include <armor.h>
#include <ansi.h>

inherit SURCOAT;

void create()
{
        set_name(HIR "ʥ��ʿ����" NOR, ({ "wushi pifeng2", "wushi", "pifeng2" }) );
        set_weight(200);
        set("long", HIR "��˵��ʥ�����ʿ���ܴ��������磬����ʥ��������\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "ʥ��ʿ�����������磬�̲��������������\n" NOR);
                set("material", "steel");
                set("value", 3000000);
                set("armor_prop/armor", 400);
                set("armor_prop/con", 3); // �������+1
                set("armor_prop/str", 2); // �������+1
        }
        setup();
}

int query_autoload()
{
        return 1;
}
