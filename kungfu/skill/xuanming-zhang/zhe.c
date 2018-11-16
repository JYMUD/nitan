#include <ansi.h>
#include <combat.h>

#define ZHE "��" HIG "ֻ������" NOR "��"

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

string final(object me, object target, int lvl);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl, p;

        if( userp(me) && !query("can_perform/xuanming-zhang/zhe", me) )
                return notify_fail("�㻹û�о�����ָ�㣬����ʹ��"ZHE"��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHE "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < 150)
                return notify_fail("�����ڤ�񹦻�򲻹����޷�ʩչ" ZHE "��\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 150)
                return notify_fail("�����ڤ���Ʋ����������޷�ʩչ" ZHE "��\n");

        if (me->query_skill_mapped("force") != "xuanming-shengong")
                return notify_fail("��û�м�����ڤ��Ϊ�ڹ����޷�ʩչ" ZHE "��\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("��û��׼����ڤ���ƣ��޷�ʩչ" ZHE "��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ���㣬�޷�ʩչ" ZHE "��\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʩչ" ZHE "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "������ڤ�񹦣�ȫ���ֳ�һ����������Ȼ��˫�Ʒ��ڲ�Ϣ��ʩ"
                  "չ�����С�" HIG "ֻ������" HIW "����Я���������������֮�����ƾ�"
                  "����$n" HIW "��\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);

        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        me->start_busy(4);

        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                addn("neili", -300, me);
     
                // ��ڤ��������
                if( query("max_neili", target)*3/5>query("max_neili", me) )
                {
                        message_sort(msg, me, target);
                        message_sort(HIM "$N" HIM "һ�ƴ���$n" HIM "���ϣ���Ȼ����Ѫ���ڣ�һ������֮����"
                                     "���ɻ�����$N" HIM "������ס�������������ڡ�$N" HIM "�ƺ�һ����һ"
                                     "����Ѫ�³�����ɫ��ʱ���ϡ�" NOR, me, target);

                        me->receive_wound("qi",query("jiali", me)+random(query("jiali", me)/2));

                        p=query("qi", me)*100/query("max_qi", me);
                        msg = "( $N" + eff_status_msg(p) + " )\n\n";
                        message_vision(msg, me, target);

                        me->affect_by("xuanming_poison",
                                      (["level":query("jiali", me)+random(query("jiali", me)),
                                         "id":query("id", me),
                                         "duration" : lvl / 40 + random(lvl / 20) ]));

                        return 1;
                        
                } 

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                          (: final, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "����$N" HIY "������ӿ����æ����Ծ����\n" NOR;
                addn("neili", -180, me);
        }
        message_sort(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         (["level":query("jiali", me)*3,
                            "id":query("id", me),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "ֻ����ǰ��Ӱ�ζ���ͻȻ���ؿ�һ����֪����"
               "���ֻ���ؿڴ�һ�ɺ������𣬾�������������\n" NOR;
}
