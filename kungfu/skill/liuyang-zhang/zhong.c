// zhong.c ��������

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        int ap, dp, lvl;
        object obj;
        string msg;

        if (! target) target = offensive_target(me);

        if (! objectp(target) || target == me
         || query("id", target) == "muren" )
                return notify_fail("��Ҫ��˭��������������\n");

        lvl  = me->query_skill("liuyang-zhang", 1);

        if (! me->is_fighting() || ! target->is_fighting() || ! living(target))
                return notify_fail("�������ս���в�������������\n");

        if (! objectp(obj=present("jiudai", me)))
                return notify_fail("������û�оƴ������ܻ�ˮΪ����\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 150
                && (int)me->query_skill("beiming-shengong", 1) < 150)
                return notify_fail("�����ң���ڹ�������������������������\n");

        if (me->query_skill_mapped("force") != "bahuang-gong"
        &&  me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("��û��������ң���ڹ���\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 150)
                return notify_fail("�����ɽ�����ƹ������������������������\n");

        if( query("neili", me)<1000 )
                return notify_fail("���������������������������\n");

        message_combatd(
                WHT "$NͻȻ�ӱ����ͳ�һ���ƴ������Լ����ĵ���Щ��ˮ��"
                "$N���������а����ڹ�����ת������\n����ʱ�ѽ����о�ˮ�����߰�Ƭ����������"
                "�̳�һ�ư��ߣ��͵���$n���ؿ����˹�ȥ��\n\n" NOR,
                me, target );

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_con()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "$n" HIR "ֻ���ؿ�һ�ƣ�һ˿����ֱ��θ�������һƬ�հ�ãȻ��֪���룡\n" NOR;

                target->affect_by("ss_poison",
                                  ([ "level" : lvl * 2,
                                     "id":query("id", me),
                                     // "remain": -1,
                                     "duration" : lvl / 100 + random(lvl / 10) ,
                                  ]));

                if (! target->is_busy())
                                target->start_busy(2);
                me->start_busy(2);
        } else
        {
                me->start_busy(2);
                msg = CYN "����$n" CYN "���Ʋ����һ�����Ѱ��߱��˻�ȥ��\n" NOR;
                tell_object(me, HIG "�������ָһ�����������һ�����ã��Ͼ��˹��ֿ���\n" NOR);
        }
        message_combatd(msg, me, target);

        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);

        return 1;
}


