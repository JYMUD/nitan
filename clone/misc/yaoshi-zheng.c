#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(WHT "��ҩʦ֤" NOR, ({ "yaoshi zheng", "yaoshi", "zheng" }));
        set_weight(1);
        set("level", 1);
        set("long", WHT "����һö��׽�ߵ���ҩʦ֤���ȼ� "+query("level")+" Ʒ������ҩʦЭ��䷢��\n" NOR);
        set("unit", "ö");
        set("value", 5);
        set("material", "steal");
        set("no_sell", "����ͷ����ѳԷ��ļһ�Ҳ������Ǯ��");
        setup();
}

void enable()
{
        set_name(HIR+chinese_number(query("level"))+"Ʒ" WHT "��ҩʦ֤" NOR, ({ "yaoshi zheng", "yaoshi", "zheng" }));
        set("long", WHT "����һö��׽�ߵ���ҩʦ֤���ȼ� "+query("level")+" Ʒ������ҩʦЭ��䷢��\n" NOR);
}
