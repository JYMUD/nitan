// dian.c ��ʯ�ɽ�
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIC "��ʯ�ɽ�" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int i;

        if (time() - me->query("special2/dian") < 86400)
                return notify_fail("��ʯ�ɽ�һ��ֻ��ʩչһ�Σ�\n");

        message_vision(HIY "$N" HIY "ʩչ����ʯ�ɽ�ֻ���������㼸�£�ɲ�Ǽ���������\n"
                       "�����ƽ������� ������\n" NOR, me);
 
        i = 1600 + random(801);

        tell_object(me, HIG "��ʩչ��ʯ�ɽ�֮������� " + chinese_number(i) + " �ƽ��Ѵ������⡣\n" NOR);
 
        me->add("stocks/balance", i);

        me->set("special2/dian", time());

        log_file("static/special2", sprintf("%s(%s) ʩչ��ʯ�ɽ� at %s\n", 
                                    me->name(),
                                    me->query("id"),
                                    ctime(time())));
        me->save();

        return 1;
}
