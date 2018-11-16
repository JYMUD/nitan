// yuan.c ��Ԫ��
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIC "��Ԫ��" NOR; }

int perform(object me, string skill)
{
        mapping my;

        if (me->query_condition("pk"))
                return notify_fail("�������� PK �ͷ��׶Σ��޷�ʹ�ø��ؼ���\n");

        if (time() - me->query("special2/yuan") < 86400 / 2)
                return notify_fail("��Ԫ��12Сʱֻ��ʩչһ�Σ�\n");

        message_vision(HIC "$N" HIC "ʩչ����Ԫ�󷨣�����ͻ���澭�������ָ�����״̬��\n" NOR, me);
       
        me->set("special2/yuan", time());
        
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"] * 2;
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();

        me->clear_condition();

        log_file("static/special2", sprintf("%s(%s) ʩչ��Ԫ�� at %s", 
                                  me->name(),
                                  me->query("id"),
                                  ctime(time())));
        me->save();

        return 1;
}

