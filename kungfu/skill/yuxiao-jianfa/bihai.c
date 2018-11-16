#include <ansi.h>
#include <combat.h>

string name() { return HIW "�̺�����������" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;
        object ob;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(ob=query_temp("handing", me)) || !ob->valid_as_xiao() )
        {
                if( !objectp(ob=query_temp("weapon", me) )
                   || ! ob->valid_as_xiao())
                {
                        // ����ı���Ҳ������Ϊ��ʹ��
                        return notify_fail("������û������������ʩչ" + name() + "��\n");
                }
        }

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 180)
                return notify_fail("�����｣���ȼ�����, ����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 180)
                return notify_fail("��̲�����Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("bihai-chaosheng", 1) < 180)
                return notify_fail("��ı̺�������̫�ͣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("��û�м������｣��������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "sword") +
             me->query_skill("bihai-chaosheng", 1);
        dp = defense_power(target, "force") +
             target->query_skill("bihai-chaosheng", 1);

        damage = 0;

        msg = HIW "\nֻ��$N" HIW "�ְ������̤�����ķ�֮λ�����"
              "һ�����̺�����������������������������ٻ�������"
              "���˼����������������Ʈ��������͵Ķ���������\n" NOR;

        if (ap + random(ap) > dp)
        {
                msg += HIR "$n" HIR "ֻ����ͷһ�������鲻�Խ���¶"
                       "����һ˿΢Ц��\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "����������һ��������������Ӧ��"
                       "ԣ�硣\n" NOR;

        msg += HIW "\nͻȻ�����Ƕ���������Ʈ����������ת������һ��Ů"
               "��һ���̾Ϣ��һ�������������һ���ȴ�������´����"
               "���л���\n" NOR;

        if (ap + random(ap / 2) > dp)
        {
                msg += HIR "$n" HIR "ֻ��ȫ����Ѫ���ڣ���ֻ��������"
                       "�����Ҷ�һ����\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "����������һ��������������Ӧ��"
                       "ԣ�硣\n" NOR;

        msg += HIW "\n��������������󺣺��������޲���Զ����ˮ����"
               "�ƽ����������죬��������ӿ��������ɽ������ˮ����Ծ"
               "�����������ХŸ�ɣ�ˮ������ȺħŪ�����������֮����"
               "��\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "��ʱ��$n" HIR "ֻ����ͷ���ȣ�������"
                       "˵���������ܡ�\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "����������һ��������������Ӧ��"
                       "ԣ�硣\n" NOR;

        msg += HIW "\nʱ�����ȴ��������������ϸ�������������ţ���"
               "����󺣳��˺�ˮƽ�羵һ�㣬������ȴ���ǰ����ļ�����"
               "ӿ���ȡ�\n" NOR;

        if (ap / 2 + random(ap / 2) > dp)
        {
                msg += HIR "��ʱ$n" HIR "�����ݾ�����ȫ����Ѫ������"
                       "��Ҳ�޷�����\n" NOR;
                damage += damage_power(me, "sword");
        } else
                msg += HIC "$n" HIC "����������һ��������������Ӧ��"
                       "ԣ�硣\n" NOR;

        target->receive_damage("jing", damage * 2 / 3, me);
        target->receive_wound("jing", damage / 2, me);

        me->start_busy(2 + random(2));
        addn("neili", -200, me);

        message_combatd(sort_msg(msg), me, target);
        return 1;
}