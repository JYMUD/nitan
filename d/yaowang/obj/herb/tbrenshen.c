#include "herb.h"

void create()
{
        set_name(HIW "̫���˲�" NOR, ({ "taibai renshen", "Pedicularis decora", "herb_tbrenshen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "���ο�ֲ������������(Pedicularis decora)�ĸ�����������������˲Σ����������˲εĹ�Ч��̫��ɽ�в����ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 60000);
                set("base_weight", 100);
        }
        setup();
}
