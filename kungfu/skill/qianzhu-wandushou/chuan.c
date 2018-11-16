#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";
string final(object me, object target, int lvl);
string name() { return "�򶾴���"; }

int perform(object me, object target)
{
        string msg;
        int lvl;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("reborn/times", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("���򶾴��ġ�ֻ�ܿ��ֲ���ʩչ��\n");

        if (! me->is_fighting(target))
                return notify_fail("���򶾴��ġ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! target || ! target->is_character())
                return notify_fail("��Ҫ��˭ʩչ�򶾴��ģ�\n");

        if (! living(target))
                return notify_fail("��������ǲ��ǻ��ˡ�\n");

        if ((int)me->query_skill("wudu-qishu", 1 ) < 300)
                return notify_fail("����嶾�����������ʩչ�򶾴��ġ�\n");

        if ((int)me->query_skill("wudu-jing", 1 ) < 300)
                return notify_fail("����嶾��������ʩչ�򶾴��ġ�\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 800)
                return notify_fail("���ǧ��������Ϊ���������ڻ��޷�ʩչ�򶾴��ġ�\n");

        if (me->query_skill_prepared("hand") != "qianzhu-wandushou")
                return notify_fail("��û��׼��ǧ�����֣��޷�ʩչ�򶾴��ġ�\n");

        if( query("neili", me)<4000 )
                return notify_fail("������������������޷�ʩչ�򶾴��ġ�\n");

        msg = HIY "$N" HIY "˫����Ȼ��ת��ǰ���Ƽ�������������������ޱȣ��Ʒ絽��������"
              "�������������ֱ��$n" HIY "�ؿڡ�\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                damage *= 6;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 400,
                                           (: final, me, target, lvl :));

                addn("neili", -4000, me);
                me->start_busy(2 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "�����������������ڹ�"
                       "��������һָ�Ķ�����\n" NOR;
                me->start_busy(4);
                addn("neili", -3000, me);
        }

        message_combatd(msg, me, target);
        /*
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        */
        return 1;
}

string final(object me, object target, int lvl)
{
        if (! userp(target))
                target->affect_by("wandu_chuanxin",
                                    ([ "level" : lvl * 100,
                                       "id":query("id", me),
                                       "duration" : lvl / 10 + random(lvl / 10) ]));
        else
                target->affect_by("wandu_chuanxin",
                                    ([ "level" : lvl * 50,
                                       "id":query("id", me),
                                       "duration" : lvl / 10 + random(lvl / 10) ]));

        return HIR "$n" HIR "ֻ�������ɶ���͸�Ķ�����˵���������ܡ�\n" NOR;
}
