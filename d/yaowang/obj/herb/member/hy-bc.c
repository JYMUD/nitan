#include "herb.h"

void create()
{
        set_name(HIC "�˱�" NOR, ({ "hy-bc", "Sedum erythrostictum", "herb_hy_bc" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�����ֲ��˱�(�ֳƾ���)(Sedum erythrostictum)��ȫ�ݡ�����Ҷ�������Ҷ���ֳư��˻�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

