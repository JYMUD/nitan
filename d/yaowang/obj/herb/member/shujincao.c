#include "herb.h"

void create()
{
        set_name(RED "����" NOR, ({ "shujin cao", "Cucubalus baccifer", "herb_sjcao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "ʯ���ֲ�ﹷ����(Cucubalus baccifer)��ȫ�ݡ�����������繦Ч���ʵô�����\n" NOR);
                set("base_unit", "��");
                set("base_value", 50000);
                set("base_weight", 100);
        }
        setup();
}

