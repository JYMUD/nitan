#include "herb.h"

void create()
{
        set_name(HIC "ѻȸ����" NOR, ({ "hy-yq", "Pholidota yunnanensis", "herb_hy_yq" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "����ֲ������ʯ����(Pholidota yunnanensis)�Ĵ����۾���ȫ�ݡ�������Ҷ����ϲȵ����.�ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

