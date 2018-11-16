// This program is a part of NITAN MudLIB
// tianmo.c ��ħʥѪ��

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIC "��ħʥѪ��" NOR, ({"tianmo shengxuegao", "tianmo", "shengxuegao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ����ħʥѪ�࣬��ħʥѪ����������˫�ľ�����ҩ��\n");
                set("base_unit", "��");
                set("base_value", 26000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ 
                                    "dangui"   : 1,
                                    "lurong"   : 6,
                                    "honghua"  : 3,
                                    "taoxian"  : 1,
                                    "zzfen"    : 1,
                                    "heshouwu" : 6,
                                    "renshen"  : 9,
                                    "shengdi"  : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 120,
                        "medical" : 200,
                        "liandan-shu" : 1900,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my; 

        my = me->query_entire_dbase(); 

        if( time()-query_temp("last_eat/tianmo", me) < 1800 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        set_temp("last_eat/tianmo", time(), me);

        message_vision(YEL "$N" YEL "����һ��" + name() +
                       YEL "����Ϣ����һС���죬�о����巢����һЩ�仯��\n", me);

        my["jing"]     = my["max_jing"];
        my["qi"]       = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["eff_qi"]   = my["max_qi"];
        my["neili"]    = my["max_neili"];
        my["jingli"]   = my["max_jingli"];
        me->start_busy(3);

        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 

        return 1;
}
