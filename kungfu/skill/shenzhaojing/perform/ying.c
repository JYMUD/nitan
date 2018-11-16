// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "��Ӱ��ȭ" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "shenzhaojing")
                return notify_fail("��û�м������վ���Ϊ���ּ��ܣ��޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "shenzhaojing")
                return notify_fail("������û��׼��ʹ�����վ��񹦣��޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("shenzhaojing", 1) < 200)
                return notify_fail("������վ��񹦻�򲻹����޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("��Ļ���ȭ�Ż�򲻹����޷�ʩչ" + name() + "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("���������Ϊ���㣬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "ٿȻԾ����������Ӱ����һȭ��ȥ�ƿ켫��ȭӰ��"
              "�ص�����ֱϮ$n" HIR "��ȥ��\n"NOR;

        lvl = me->query_skill("shenzhaojing", 1);

        ap=attack_power(me,"force")+me->query_con()*10;
        dp=defense_power(target,"force")+target->query_con()*10;

        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "force");
                damage+= query("jiali", me);
                addn("neili", -400, me);
                target->affect_by("shenzhao", ([
                        "level":query("jiali", me)+random(query("jiali", me)),
                        "id":query("id", me),
                        "duration" : lvl / 50 + random(lvl / 20) ]));
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK,
                               damage, 80, HIR "$n" HIR "��ȭ�Ʊ任Ī�⣬ֻ��"
                               "΢΢һ㶣��ѱ�$N" HIR "һȭ�����ؿڣ����վ���"
                               "����\nʱ����ɽ�鱬��һ�㣬͸����롣\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
