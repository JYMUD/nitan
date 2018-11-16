#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "�ҷ�����"; }

#include "/kungfu/skill/eff_msg.h";
string final(object me, object target, int lvl);

int perform(object me, object target)
{
        string msg;
        int ap, dp, flvl, add_lvl;
        int damage, add_dam;
        int is_jifa_beiming;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("���ҷ�����ֻ�ܿ��ֲ���ʩչ��\n");

        if (! me->is_fighting(target))
                return notify_fail("���ҷ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! target || ! target->is_character())
                return notify_fail("��Ҫ��˭ʩչ�ҷ�����\n");

        if (! living(target))
                return notify_fail("��������ǲ��ǻ��ˡ�\n");

        if (me->query_skill_prepared("strike") != "liuyang-zhang" )
                return notify_fail("�㻹û�н���ɽ����������ң��÷�ֻ������޷�ʩչ��\n");

        if (me->query_skill_prepared("hand") != "zhemei-shou" )
                return notify_fail("�㻹û�н���ɽ����������ң��÷�ֻ������޷�ʩչ��\n");

        if (me->query_skill_mapped("dodge") != "lingbo-weibu" )
                return notify_fail("�㻹û�м����貨΢�����޷�ʩչ��\n");

        if( query("neili", me)<2500 )
                return notify_fail("������������������޷�ʩչ�ҷ�����\n");

        msg = HIY "$N" HIY "���ֻ��ƣ����ֳɵ�����ͣ��ת��ǰ���Ʒ絽����һ������ϯ���������$n" HIY "���ܰ�Χ��\n" NOR;

        ap = attack_power(me, "strike") + me->query_skill("hand");
        dp = defense_power(target, "parry") + target->query_skill("unarmed");

        flvl=query("jiali", me);
        add_lvl = flvl * 3;

        add_dam = 300;

        // �Ƿ񼤷�beiming-shengongΪ�ڹ�
        is_jifa_beiming = me->query_skill_mapped("force") == "beiming-shengong" ? 1 : 0;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);

                // �缤��beiming-shengong ��20%���������ŷ�
                if (random(5) == 1)
                {
                        msg += HIW "ɲ�Ǽ䣬$N" HIW "ֻ�����ڱ�ڤ���������ɽ�緢����ӿ����������"
                                   "Ѩλ���ں���������ѧ���ֲ�ͬ���ɵ���������̼�ӿ����������˫��"
                                    "���������ȵİ׹� ����\n" NOR;
                        msg = sort_msg(msg);

                        add_dam = 400;
                }

                // �뿪��ң�ɺ���������
                if( !(query("family/family_name", me) ||
                    query("family/family_name", me) != "��ң��") && (!query("reborn/times", me) || 
                    member_array("��ң��", query("reborn/fams", me)) == -1) ) 
                {
                        damage /= 2;
                        add_dam /= 2;
                }

                if( random(10) == 1 && query("can_perform/liuyang-zhang/zhong", me) )
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, add_dam,
                                                   (: final, me, target, add_lvl :));
                }
                else
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, add_dam,
                                                   HIR "ֻ����ɳ����,����һ������$n" HIR "�ؿڣ��漴"
                                                   "�ƺ�һ������Ѫ���������\n" NOR);
                }

                addn("neili", -2500, me);
                if (me->query_skill("lingbo-weibu", 1) >= 1500 && random(100) < 15)
                {
                        message_combatd(HIW "$N" HIW "Ĭ���貨΢���ھ��������죬˿�����ܳ��е��谭��\n" NOR, me);
                }
                else
                {
                        me->start_busy(2);
                }
        } else
        {
                msg += CYN "����$p" CYN "��ͻ�䣬������������ܹ����С�\n" NOR;
                if (me->query_skill("lingbo-weibu", 1) >= 1500 && random(100) < 15)
                {
                        message_combatd(HIW "$N" HIW "Ĭ���貨΢���ھ��������죬˿�����ܳ��е��谭��\n" NOR, me);
                }
                else
                {
                        me->start_busy(3);
                }
                addn("neili", -2500, me);
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
          target->affect_by("ss_poison",
                       ([ "level"    : lvl,
                          "id":query("id", me),
                          "duration" : 120 + random(240)]));

          if( random(5) == 1)set("neili", 0, target);

          if (! target->is_busy()) target->start_busy(2 + random(5));

          return HIR "$n" HIR "ֻ����һ�ɺ���͸�Ķ������������д��ģ�����֮����\n" NOR;
   }
