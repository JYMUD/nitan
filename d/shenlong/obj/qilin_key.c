inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIR "����Կ��" NOR, ({"qilin key", "key", "qilin"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
        	set("unit", "��");
		set("long", HIR "����һ��ͨ�����Կ�ף������ڼ�ɴ���ն��ѫ�����򿪻����붴�ķ�ӡ��\n");
		set("value", 1);
	}
        setup();
}