#include "herb.h"

void create()
{
        set_name(HIC "���»���" NOR, ({ "hy-ly", "Sedum aizoon", "herb_hy_ly" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�����ֲ��Ѳ�(Sedum aizoon)��ȫ�ݻ����������6�¿�ʼ���������ʵô��������������л�Ѫ������ֹѪ�Ĺ�Ч�������Ϊ����Ч����ͬ���������������ֳƣ�Ϊ�������ߡ���\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}
