#include <ansi.h>

#include "tr.h"

int query_tongren() { return 1; }
void create()
{
        set_name(YEL "����Сͭ��" NOR, ({ "wuming tongren", "wuming", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("base_unit", "��"); 
                set("long", YEL "����һ���ƾɵ�ͭ�ˣ����������һЩͼ���������Ѿ��޷���ʶ��\n" NOR);
                //set("long", NOR + YEL "������һ����Ѩͭ�ˣ�������о���Ѩλͼ����ϰ�þ���ѧ��\n" NOR);
                set("value", 10000);
                set("material", "steal");
                set("no_identify", 1);

                set("skill", ([
                        "name"         : "jingluo-xue",
                        "exp_required" : 500000,
                        "jing_cost"    : 150,
                        "difficulty"   : 30,
                        "max_skill"    : 99,
                        "min_skill"    : 0
                ]));
        }
        setup();
}

