#include "herb.h"

void create()
{
        set_name(HIR "�������" NOR, ({ "longgu shenjin", "Smilax riparia var. acuminata", "herb_lgjin" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�ٺϿ�(���ֿ�)ֲ���Ҷţβ��(Smilax riparia var. acuminata)�ĸ������������������ǣ���Ӳ������������Ĺ�Ч���ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 50000);
                set("base_weight", 100);
        }
        setup();
}
