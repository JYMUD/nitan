#include "herb.h"

void create()
{
        set_name(HIC "̫������" NOR, ({ "hy-ty", "Polygonatum hookeri", "herb_hy_ty" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�ٺϿ�ֲ������ƾ�(Polygonatum hookeri)�ĸ���������ϲ��������������.�ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

