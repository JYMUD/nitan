inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR + YEL "��ʦ���" NOR, ({"tianshi guifu", "tianshi", "guifu"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + YEL "����һ�ŵ�����������ʦΪ�˽�����ֶ��ơ�\n"  NOR);

                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
