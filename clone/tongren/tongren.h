#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "ͭ��NAME" NOR, ({ "ͭ��ID", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + YEL "����һ����Ѩͭ�ˣ����������һЩ����Ѩλͼ�����Լ���Ѩʹ�÷�����\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "JINGMAI_NAME");
        set("xuewei_name", "XUEWEI_NAME");
        set("chongxue_xiaoguo", "CHONGXUE_XIAOGUO");
        set("neili_cost", "NEILI_COST");
        setup();
}

