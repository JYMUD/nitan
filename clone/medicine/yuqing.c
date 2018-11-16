// yuqing.c  ����ɢ   by sinb

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIC "����ɢ" NOR, ({"yuqing san", "san"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ������ɢ����˵���䵱�ɵ���ҩ������ǿ���壬�������١�\n");
                set("base_unit", "��");
                set("base_value", 140000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "chaihu"   : 1,
                                    "dangui"   : 1,
                                    "lurong"   : 1,
                                    "xiefen"   : 1,
                                    "honghua"  : 1,
                                    "taoxian"  : 1,
                                    "zzfen"    : 1,
                                    "heshouwu" : 1,
                                    "renshen"  : 1,
                                    "shengdi"  : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 120,
                        "medical" : 200,
                        "liandan-shu" : 600,
                ]));
        }
        setup();
}

int do_effect(object me)
{

        /*
        if( time()-query_temp("last_eat/yuqing", me)<320 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        set_temp("last_eat/yuqing", time(), me);
        */

        message_vision(YEL "$N" YEL "����һ��" + name() +
                       YEL "����Ϣ����һС���죬�о����巢����һЩ�仯��\n", me);

        addn("max_jingli", 5+random(2), me);
        if( query("max_jingli", me)>me->query_current_jingli_limit() )
                set("max_jingli", me->query_current_jingli_limit(), me);
        // me->start_busy(3);

        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 

        return 1;
}
