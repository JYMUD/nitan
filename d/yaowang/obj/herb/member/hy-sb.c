#include "herb.h"

void create()
{
        set_name(HIC "��Ҷ�쾰��" NOR, ({ "hy-sb", "Rhodiola henryi", "herb_hy_sb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�����ֲ���㶹��(�ֳ���Ҷ�쾰��)(Rhodiola henryi)�Ĵ���ȫ�ݡ������л�Ѫ��ֹʹ������֮��Ч����ҩЧ���ÿ죬������ʮ���������͡���ȼݡ���\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

