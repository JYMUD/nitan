#include "herb.h"

void create()
{
        set_name(HIC "��˿����" NOR, ({ "hy-js", "herb_hy_js" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "�𷢼��ֲ���ɽ��޺��ȫ�ݡ�����ֲ���������ɫ�������˿���ʵô�������\n" NOR);
                set("base_unit", "��");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

