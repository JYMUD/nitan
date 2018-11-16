// dian.c

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��" HIY "��" HIG "��" HIW "Ѩ" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, jp, lvl, xw, j, damage;

        if (! target) target = offensive_target(me);

        if( query_temp("weapon", me) )
                return notify_fail("������������ô��׼ȷ�ĵ��жԷ���Ѩ���أ�\n");

        if (!target || ! me->is_fighting(target))
             return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if((int)me->query_skill("dodge",1) < 200)
                return notify_fail("����Ṧ��Ϊ����, ����ʹ�ø��յ�Ѩ��\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("��û�м�����ָ��ͨ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("��û��׼����ָ��ͨ������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if((int)me->query_skill("tanzhi-shentong",1) < 200)
                return notify_fail("��ĵ�ָ��ͨ��Ϊ������ Ŀǰ����ʹ�ø��յ�Ѩ! \n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");

        if( query_temp("thd/tz", me) )
                return notify_fail("��յ���Ѩ��������Ϣһ�°ɡ�\n");

        lvl = me->query_skill("tanzhi-shentong",1);
        jp = me->query_skill("jingluo-xue", 1);

        //����������е�Ѩλ
        xw = (int)random(15);
        if (xw > 8)
        {
                xw = random(8);
        }

        msg = HIY "\n����$N" HIY "���ĵ�����$n���ߣ�ͻȻֻ����$N��һ��:�����һ�" NOR+name()+HIY"���� !\n" NOR;

        // ����Ѩ
        //if (xw == 1)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("dodge");
                dp = defense_power(target, "parry") + target->query_skill("dodge");

                msg += HIG "\n$N���������ʳָ��ٿ����$n���Ϸ���Ѩ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n�Ͻ����ţ���������һ�С�\n" NOR;
                else
                {
                        msg += HIR "$nһ�����У���һ�飬����ʱ�ٻ���������\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        addn_temp("apply/dodge", -lvl, target);
                        call_out("remove_effect_futu", 10, me, target, lvl);
                }
                message_combatd(msg, me, target);
        }

// ����Ѩ
        //else if (xw == 2)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                msg += HIG "\n$N���������ʳָ��ٿ����$n��������Ѩ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n�Ͻ���ת���󣬲űܿ�����һ�С�\n" NOR;
                else
                {
                        msg += HIR "$nһ�����У�����һ�飬����������ࡣ\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        addn_temp("apply/attack", -lvl, target);
                        call_out("remove_effect_shenmen", 10, me, target, lvl);
                }
                message_combatd(msg, me, target);
        }

// ��ԪѨ
        //else if (xw == 3)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("force");
                dp = defense_power(target, "parry") + target->query_skill("force");
                msg += HIG "\n$N���������ʳָ��ٿ����$n������ԪѨ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n�Ͻ�����һ���������˹�ȥ��\n" NOR;
                else
                {
                        msg += HIR "$nһ�����У�һ������ֱ�嵤����ڵ���������ɢ�˿�ȥ��\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -lvl*3, target);
                        addn("neili", -150, me);
                        call_out("remove_effect_all", 10, me);
                }
                message_combatd(msg, me, target);
        }

// ����Ѩ
        //else if (xw == 4)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("bibo-shengong", 1);
                dp = defense_power(target, "dodge") + target->query_skill("force", 1);
                msg += HIG "\n$N���������ʳָ��ٿ����$n�ؿ�����Ѩ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n��æ��������ֵ�Ϯ��ָ����һ�߼�æ����س���"
                                   "�������һ�С�\n" NOR;
                else
                {
                        msg += HIR "$nһ�����У����ڵ�������Ҳ������ת���磬�мܶ�ʱɢ�ҡ�\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        j = me->query_skill("bibo-shengong",1);
                        addn_temp("apply/parry", -j, target);
                        target->apply_condition("no_exert", j);
                        call_out("remove_effect_yutang", j, me, target);
                }
                message_combatd(msg, me, target);
        }

// ̴��Ѩ
        //else if (xw == 5)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("dodge");
                dp = defense_power(target, "parry") + target->query_skill("dodge");
                msg += HIG "\n$N���������ʳָ��ٿ����$n��ǰ̴��Ѩ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n������������������һ�С�\n" NOR;
                else
                {
                        msg += HIR "$nһ�����У���Ϣһ�ϣ�һʱ���Զ�����\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        if (!target->is_busy())
                                target->start_busy(ap /100 + 2);
                        call_out("remove_effect_tanzhong", lvl/10, me, target);
                }
                message_combatd(msg, me, target);
        }

// ��̨Ѩ
        //else if (xw == 6)
        {
                ap = attack_power(me, "finger") + jp+query("max_neili", me);
                dp = defense_power(target, "dodge")+target->query_skill("max_neili");
                msg += HIG "\n$N���������ʳָ��ٿ����$n������̨Ѩ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n��æ����������ǿ����������ס�Է���ָ����\n" NOR;
                else
                {
                        damage = damage_power(me, "finger");
                        msg += HIR "$nһ�����У�����ʱ��ʱ�ף������������ˡ�\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("neili", -150, me);
                        target->receive_wound("jing", damage / 2 );
                        call_out("remove_effect_all", 10, me);
                }
                message_combatd(msg, me, target);
        }

// �ٻ�Ѩ
        //else if (xw == 7)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                msg += HIG "\n$N���������ʳָ��ٿ����$nͷ���ٻ�Ѩ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$nһ��ͷ���Ŷ����һ�С�\n" NOR;
                else
                {
                        msg += HIR "$nһ�����У���ʱ������ת��ҡҡ��׹��\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn("qi", -(lvl+random(50)), target);
                        addn("neili", -150, me);
                        call_out("remove_effect_all", 10, me);
                }
                message_combatd(msg, me, target);
        }

// �縮Ѩ
        //else if (xw == 8)
        {
                ap = attack_power(me, "finger") + jp + me->query_skill("parry");
                dp = defense_power(target, "dodge") + me->query_skill("parry");
                msg += HIG "\n$N���������ʳָ��ٿ����$n���Է縮Ѩ��ȥ��\n" NOR;

                if (ap / 2 + random(ap) < dp)
                        msg += HIW "$n�Ͻ���ͷ����������һ�С�\n" NOR;
                else
                {
                        msg += HIR "$nһ�����У���ǰ��Ȼһ�ڣ������赹��\n" NOR;
                        set_temp("thd/tz", 1, me);
                        addn_temp("apply/defense", -lvl, target);
                        addn("neili", -150, me);
                        call_out("remove_effect_fengfu", ap/200 + random(2), me, target ,lvl);
                }
                message_combatd(msg, me, target);
        }
// δ��Ӧ
        //else return notify_fail("�����õ�ָ��ͨ�ҵ�һͨ���������Ǻ������á�\n");


        return 1;
}

int remove_effect_futu(object me, object target, int i)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        addn_temp("apply/dodge", i, target);
        if( !me ) return 1;
        delete_temp("thd/tz", me);
        msg = HIY"$n���ϵķ���ѨѪ���Ѿ��п������Ѹ���\n" NOR;
        message_combatd(msg, me, target);
        return 1;
}


int remove_effect_shenmen(object me, object target, int i)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        addn_temp("apply/attack", i, target);
        if( !me ) return 1;
        delete_temp("thd/tz", me);
        msg = HIY "$n���������ѨѪ���Ѿ��п��������ָ��ˡ�\n" NOR;
        message_combatd(msg, me, target);
        return 1;
}

int remove_effect_tanzhong(object me, object target)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        if( !me ) return 1;
        msg = HIY "$n�ؿڵ�̴��ѨѪ���Ѿ��п����ж��ָ��ˡ�\n" NOR;
        delete_temp("thd/tz", me);
        message_combatd(msg, me, target);
        return 1;
}

int remove_effect_yutang(object me, object target, int i)
{
        string msg;

        if (!target) {
        if( me )
        delete_temp("thd/tz", me);
                return 1;}
        if( !me ) return 1;
        msg = HIY "$n�ؿڵ�����ѨѪ���Ѿ��п�����Ϣ�ָ���������\n" NOR;
        delete_temp("thd/tz", me);
        addn_temp("apply/parry",-i, me);
        message_combatd(msg, me, target);
        return 1;
}


int remove_effect_fengfu(object me, object target, int i)
{
        string msg;

        if (!target) {
        delete_temp("thd/tz", me);
                return 1;}
        addn_temp("apply/defense", -i, target);
        if( !me ) return 1;
        delete_temp("thd/tz", me);
        msg = HIY "$n���Եķ縮ѨѪ���Ѿ��п������߸�ԭ�ˡ�\n" NOR;
        message_combatd(msg, me, target);
        return 1;
}

void remove_effect_all(object me)
{
        if( !me ) return;
        delete_temp("thd/tz", me);
}
