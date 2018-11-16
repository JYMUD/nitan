#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��ƾ�"; }

int perform(object me, object target)
{
        string msg;
        int lvl;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ�ܹ������ˣ�\n");

        if (! target || ! target->is_character())
                return notify_fail("��Ҫ��˭ʩչ��ƾ���\n");

        if( query("not_living", target) )
                return notify_fail("��������ǲ��ǻ��ˡ�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ��������ʩչ��ƾ���\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 130)
                return notify_fail("���ǧ��������Ϊ���������ڻ��޷�ʩչ��ƾ���\n");

        if (me->query_skill_mapped("hand") != "qianzhu-wandushou")
                return notify_fail("��û�м���ǧ�����֣��޷�ʩչ��ƾ���\n");

        if( query("neili", me)<400 )
                return notify_fail("������������������޷�ʩչ��ƾ���\n");

        msg = HIB "$N" HIB "ʩ����ƾ���ֻ��һ�ƺ�����"
              "ָ��͸����ֻһ����û����$n" HIB "��ü�ģ�\n" NOR;

        ap = attack_power(me,"hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$p" HIR "ֻ����һ����ɽ�ľ���˳ָ����"
                                           "��������ֻ����ȫ������ܣ����ۡ���һ��"
                                           "�³�һ�ں�Ѫ��\n" NOR);
                target->affect_by("qianzhu_wandushou",
                                  ([ "level" : lvl / 2 + random(lvl / 2),
                                     "id":query("id", me),
                                     "duration" : lvl / 40 + random(lvl / 18) ]));
                addn("neili", -320, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�����������������ڹ�"
                       "��������һָ�Ķ�����\n" NOR;
                me->start_busy(3);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);
        /*
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        */
        return 1;
}