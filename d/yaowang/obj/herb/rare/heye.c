#include "herb.h"

void create()
{
        set_name(NOR + YEL "����һ��ˮ" NOR, ({ "diphylleia sinensis", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "�Ϸ�ɽ��Ҷ(Diphylleia sinensis)�ĸ�����������������ÿһ���ڴ���һ��״С����(����)����������ںӱ߸�ɽ�������ڵô�ҩ���ʵô�����������ƺ�ɫ ......\n" NOR);
                set("base_unit", "��");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

