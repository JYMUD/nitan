#include "herb.h"

void create()
{
        set_name(HIB "��Ѫ��" NOR, ({ "huoxuezhu", "Pleione bulbocodioides", "herb_hxzhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "����ֲ�������(Pleione bulbocodioides)�ļ��۾���������۾��ײ�Բ�����飬������Ѫ��Ч���ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}
