#include "herb.h"

void create()
{
        set_name(GRN "ת���" NOR, ({ "zhuanjin cao", "Pachysandra terminalis", "herb_zhjcao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�����ֲ�ﶥ����ʹ�(�ֳƸ����)(Pachysandra terminalis)�Ĵ���ȫ�ݡ������������繦Ч���ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 60000);
                set("base_weight", 100);
        }
        setup();
}
