#include "herb.h"

void create()
{
        set_name(HIC "�����" NOR, ({ "hy-zhu", "Senecio goodianux", "herb_hy_zhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�տ�ֲ�ﵥͷǧ���(Senecio goodianux)��ȫ�ݡ�����Ҷ��������䣬�ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

