#include <ansi.h>

inherit ITEM;


void create()
{
        set_name(HIY "�����" NOR, ({"xiling hu", "xiling", "hu"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "����һ��ɢ�������ع�ʵ��������˵�������������ɹ����̺���������\n\n" NOR);
                set("unit", "��");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}
