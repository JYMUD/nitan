inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIC "����" NOR, ({"jiaozi"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "�����ǹŴ������ֽ�ң��������ѹ���Ƶ�֤�ݡ�\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
