#include "herb.h"

void create()
{
        set_name(NOR + MAG "ͷ��һ����" NOR, ({ "trillium tschonoskii", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "ֲ�������(Trillium tschonoskii)�ĸ���������ʵ��������ֲ����3ƬҶ�����ھ��Ķ��ˣ�������������Ҷ֮�ϣ���������Բ���εĹ�ʵ����������ɫ ......\n" NOR);
                set("base_unit", "��");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

