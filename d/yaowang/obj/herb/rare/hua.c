#include "herb.h"

void create()
{
         set_name(NOR + BLU "��Ҷһ֦��" NOR, ({ "qiye yizhihua","hua","herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIY "��Ҷһ֦��(Paris polyphylla)�ĸ������������Ҷ��Ϊ7��10Ƭ�����ھ����������������ҶƬ֮�ϣ��ʵô��������򻨵����ֻ���Ƭ�δ�.��Ҷ״�����ֻ���Ƭ�˻��ʳ���״ ......\n" NOR);
                set("base_unit", "��");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

