#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "��Ѩͭ�ˡ������������ڹ�Ѩ" NOR, ({ "tongren t1", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + YEL "����һ����Ѩͭ�ˣ����������һЩ����Ѩλͼ�����Լ���Ѩʹ�÷�����\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "��������");
        set("xuewei_name", "�ڹ�Ѩ");
        set("chongxue_xiaoguo", "JING:50:NEI:50");
        set("neili_cost", "8000");
        setup();
}

