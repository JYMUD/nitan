#include "herb.h"

void create()
{
        set_name(HIW "��ȼ�" NOR, ({ "dajiujia", "Chamaenerion angustifloium", "herb_jiujia" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "��Ҷ�˿�ֲ������(Chamaenerion angustifloium)�ĸ��������������л�Ѫɢ����ֹʹ�Ĺ�Ч�������Ƶ������ˡ����۵�֢����ҩЧ���ÿ죬�ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}

