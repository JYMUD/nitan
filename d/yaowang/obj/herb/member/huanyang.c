#include "herb.h"

void create()
{
        set_name(HIC "���»���" NOR, ({ "huanyang5", "Sedum odontophyllum", "herb_5yhuanyang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�����ֲ���Ҷ����(Sedum odontophyllum)��ȫ�ݡ���������ֹʹ��Ч��ǿ��������һֲ��һ����5�¿���������Ҳ�ơ����»�������\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

