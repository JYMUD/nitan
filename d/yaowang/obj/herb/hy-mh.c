#include "herb.h"

void create()
{
        set_name(HIC "÷������" NOR, ({ "hy-mh", "Rhodobryum giganteum", "herb_hy_mh" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "��Ϳ�ֲ��ů�ش�Ҷ޺(Rhodobryum giganteum)��ȫ�ݡ����䶥Ҷ��.�����绨��״������÷�����ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}
