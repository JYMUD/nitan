#include "herb.h"

void create()
{
        set_name(HIY "�������" NOR, ({ "wugong", "Aralia chinensis", "herb_wugong" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "��ӿ�ֲ��Bľ(Aralia chinensis)�ĸ�����Ƥ����Ƥ������С֦�ܱ�����ɫ��̣����������죬�ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}

