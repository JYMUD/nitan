#include "herb.h"

void create()
{
        set_name(HIC "�ӹǵ�" NOR, ({ "jiegudan", "Torricellia angulata", "herb_jgdan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "ɽ���ǿ�(�ʱ�ľ��)ֲ���Ҷ�ʱ�ľ(Torricellia angulata)�ĸ�����Ƥ��Ҷ�����������ƹ��۵Ĺ�Ч���ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}

