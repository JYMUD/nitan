#include "herb.h"

void create()
{
        set_name(HIC "��ʯ����" NOR, ({ "hy-ys", "Chlamydoboea sinensis", "herb_hy_ys" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "����̦��ֲ�������̦(Chlamydoboea sinensis)��ȫ�ݡ��������������ʯ�����ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}
