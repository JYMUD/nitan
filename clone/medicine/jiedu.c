// jiedu.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIY "ţ�ƽⶾ��" NOR, ({"jiedu wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "����һ����ɫ��ҩ�裬��ţ�Ƹ���ԭ���Ƴɣ����в�"
                            "��ĽⶾЧ����\n" NOR);
                set("base_unit", "��");
                set("base_value", 3000);
                set("base_weight", 55);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "yjhua"  : 1,
                                    "juhua"  : 1,
                                    "xuejie" : 1,
                                    "chenpi" : 1,
                                    "xiefen" : 1,
                                    "shengdi": 1,
                                    "lanhua" : 1,
                                    "gsliu"  : 1, ]),
                        "neili" : 80,
                        "jing"  : 30,
                        "time"  : 3,
                        "min_level" : 80,
                        "medical" : 100,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat/jiedu", me)<20 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        if (! me->query_skill_mapped("force"))
        {
                write("��û�м����κ��ڹ�����ô����ҩ������������\n");
                return 1;
        }

        set_temp("last_eat/jiedu", time(), me);

        message_vision(HIY "$N" HIY "��������һ������������" + name() +
                       HIY "����ϥ���£���ʼ�˹��ƶ���\n" NOR, me);

        // �˹�����
        addn_temp("apply/dispel_poison", 100, me);
        SKILL_D("force")->exert_function(me, "dispel");
        addn_temp("apply/dispel_poison", -100, me);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
