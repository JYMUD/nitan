#include "herb.h"

void create()
{
          set_name(NOR + CYN "����һ֧��" NOR, ({ "wenwang yizhibi", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIR "Ͳ������(Balanophora involucrata)������(BalanophoraJWjaponica)�ĸ���ȫ�ꡣ�����Ļ�������ִֵ�ë�ʣ���䴫˵������·����ũ�� ......\n" NOR);
                set("base_unit", "��");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

