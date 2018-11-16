// lian.c ���־�

#include <ansi.h>

string name() { return "���־�"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i;
        int time;
        int count;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��" + name() + "��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("�����ý�����ʩչ��" + name() + "����\n");

        if( query("neili", me)<1000 )
                return notify_fail("��������������޷�ʩչ��" + name() + "����\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 200)
                return notify_fail("���̫���񹦻�򲻹�������ʩչ��" + name() + "����\n");

        if ((int)me->query_skill("taiji-jian", 1) < 200)
                return notify_fail("���̫�����������ң��޷�ʹ�á�" + name() + "����\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("��û�м���̫���������޷�ʹ�á�" + name() + "����\n");

        time = me->query_skill("taiji-jian") / 20;
        if (time > 10) time = 10;
        if (time < 1) time = 1;

        msg = HIC "$N" HIC "һ����Х����̨�����������Ԫ��ʹ��̫�����еġ�" + name() + "����\n"
              HIY "����" + weapon->name() + HIY "��ʽ��Ȼ��������ޱȣ�һת��"
              HIY "����Ȼ����" + chinese_number(time) + "�У�\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("taiji-jian", 1) / 2;
        addn("apply/attack", skill, me);
        addn("apply/damage", skill, me);
        addn("neili", -(time*100), me);

        for (i = 0; i < (time); i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn("apply/attack", -skill, me);
        addn("apply/damage", -skill, me);
        me->start_busy(1+ random(3));
        return 1;
}
