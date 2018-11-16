// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define JING "��" HIW "����̫����" NOR "��"

inherit F_SSERVER;

string final1(object me, object target, int damage, object weapon, int lvl);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage, object weapon, int lvl, string msg);

int perform(object me, object target)
{
        int damage;
        string msg, sub_msg;
        int ap, dp;
        object weapon;
        int flag = 0;
        int lvl;

        if( userp(me) && !query("can_perform/taixuan-gong/jing", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (!objectp(weapon=query_temp("weapon", me))) || 
            (query("skill_type", weapon) != "sword"
             && query("skill_type", weapon) != "blade") )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" JING "��\n");

        if ((int)me->query_skill("force", 1) < 340)
                return notify_fail("���ڹ���Ϊ����������ʩչ" JING "��\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("��������Ϊ����������ʩչ" JING "��\n");

        lvl = (int)me->query_skill("taixuan-gong", 1);
        if (lvl < 340)
                return notify_fail("��̫������򲻹�������ʩչ" JING "��\n");

        if (me->query_skill_mapped("sword") != "taixuan-gong"
            && me->query_skill_mapped("blade") != "taixuan-gong")
                return notify_fail("��û�м���̫����Ϊ���򽣣�����ʩչ" JING "��\n");

        // �ֱ��жϼ�������ʱ��Ҫ�ĵ������ȼ���
        if (me->query_skill_mapped("sword") == "taixuan-gong")
        {               
                if (me->query_skill("sword", 1) < 340)
                        return notify_fail("��Ļ�����������㣬����ʩչ" JING "��\n");

                else 
                {
                        if( query("skill_type", weapon) == "sword" )
                                flag = 1; // ���ü���Ϊsword��־
                        sub_msg = "��";
                }
        }
        else // ����Ϊ��
        {
                if (me->query_skill("blade", 1) < 340)
                        return notify_fail("��Ļ�����������㣬����ʩչ" JING "��\n");
                else 
                {
                        flag = 0; // ���ü���Ϊblade��־
                        sub_msg = "��";
                }
        }

        if( query("neili", me)<850 )
                return notify_fail("��������������������ʩչ" JING "��\n");

        if (me->query_skill("martial-cognize", 1) < 260)
                return notify_fail("����ѧ�������㣬����ʩչ" JING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_combatd(sort_msg(HIM "\n$N" HIM "�鲻�Խ���������Х����ʱ֮�䣬ǧ������ʽ���������ӿ"
                     "����ͷ��$N" HIM "���ֻ��裬���ǲ������򣬵������ۺ�����ʽ������������"
                     "���Ȳ��ش�����Ϣ���಻�����������ʯ���ϵ�ǧ������ʽ����Ȼ��Ȼ�Ĵ���"
                     "�д������㣬����Ϯ��$n" HIM "��\n" NOR), me, target);


        if (flag)ap = attack_power(me, "sword") + me->query_str();
        else ap = attack_power(me, "blade") + me->query_str();

        // ��һ�У��ж϶Է�����
        dp = defense_power(target, "parry") + target->query_str();

        message_combatd(sort_msg(HIW "\n$N" HIW "ͻȻ��ֻ���������¡�ԨҺѨ����һ����һ���������š�����"
                     "�������������š����¡��������š���Ѩ��ȥ��һ�С�ʮ��ɱһ�ˡ���" + sub_msg + 
                     "��������ʹ����������ʽԴԴ��������$n" HIW "���֡�\n" NOR), me, target);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60 + random(10),
                                         (: final1, me, target, damage, weapon, lvl :));
        } else
        {
                msg = HIC "$n" HIC "����˫�ۣ������Զԣ�����$N" HIC "֮��жȥ��\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        if( flag)ap=attack_power(me,"sword")+me->query_int();
        else ap=attack_power(me,"blade")+me->query_int();
        // �ڶ��У��ж϶Է�����
        dp=defense_power(target,"parry")+target->query_int();

        message_combatd(sort_msg(HIW "\n$N" HIW "�����������ѣ���Ϣ�������������š��Կ��Ϻ�ӧ�����׾�����"
                     "��ͼ��ת����ͬʱ�����㵸�����Ǵ�ϲ�����ƴ���ա�\n" NOR), me);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 65 + random(10),
                                          HIY "$n" HIY "��Цһ��������$N" HIY "���з�ǳ֮������"
                                          "�������мܣ���Ȼ�䣬�����͡���һ����" + weapon->name() +
                                          HIY "�Ѵ�͸$n" HIY "�����ţ���Ѫ����ӿ����\n" NOR, me , target);
        } else
        {
                msg = HIC "$n" HIC "����һЦ������$N" HIC "�����е�����������ʩ�о������л�ȥ��\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        if (flag)ap = attack_power(me, "sword") + me->query_con();
        else ap = attack_power(me, "blade") + me->query_con();
        // �����У��ж϶Է�����
        dp = defense_power(target, "force") + target->query_con();

        message_combatd(sort_msg(HIW "\n���Կ��Ϻ�ӧ���ȱϣ�����ȥ���ǡ��⹳˪ѩ������$N" HIW "��"
                    "��˼����ʯ���ϵ�ͼ��һ�������Ժ�����Ȼӿ�����ԡ������հ���ֱ����˭������¡���"
                    "һ���ǳɵ�ʹ�˳�����\n" NOR), me);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70 + random(10),
                                           (: final2, me, target, damage :));
        } else
        {
                msg = HIC "$n" HIC "Ĭ���ڹ����ھ�����ȫ�������ֵ�ס$N" HIC "���С�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        // �����У��ж϶Է���

        if (flag)ap = attack_power(me, "sword") + me->query_dex();
        else ap = attack_power(me, "blade") + me->query_dex();        
        dp = defense_power(target, "dodge") + target->query_dex();

        message_combatd(HIW "\n���á�˭������¡����׹������꣬$N" HIW "ֻ����Ϣ��ת"
                     "������������Ӣ����ʹ��ȥ��\n" NOR, me);

        if (ap / 2 + random(ap) > dp)
        {
                if (flag) damage = damage_power(me, "sword") *2/3;
                else damage = damage_power(me, "blade") *2/3;
                damage += query("jiali", me);
                msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 75 + random(10),
                                          (: final3, me, target, damage, weapon, lvl, sub_msg :));
        } else
        {
                msg = HIC "$n" HIC "�������������ͣ����μ��ˣ�˲��Ʈ����"
                      "�ɣ����Ŷ��$N" HIC "���С�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        me->start_busy(3 + random(3));
        addn("neili", -400-random(400), me);
        return 1;
}

string final1(object me, object target, int damage, object weapon, int lvl)
{
        addn("neili", -(lvl+random(lvl)), target);

        return  HIY "$n" HIY "ȴ��$N" HIY "�������ƻֺ룬�������������ֵ�������������"
                "���������ˣ�$n" HIY "�ƺ�һ�������˼������پ���Ϣ��ɢ��" + weapon->name() + HIY 
                "������Ⱦ����Ѫ��\n" NOR;
}

string final2(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "����һ��������$N" HIY "�⼸�������ޱȣ���ʽ�仯Ī�⣬"
                "������ȴ��Ȼ����������ԥ�䣬$n" HIY "ȴ�����У��ٸо������ã���"
                "��������\n" NOR;
}

string final3(object me, object target, int damage, object weapon, int lvl, string msg)
{
   
        target->start_busy(4 + random(3));
  
        return  HIY "$N" HIY + msg + "�������ޱȣ�����" + weapon->name() + HIY "ʱ������������ʱ��"
                "�������裬���Ǽ�$n" HIY "�ѱ������ˣ�$N" HIY "��Ȼ������" + weapon->name() + HIY "һ"
                "ת�����ƶ�Ȼ�ӿ죬��$n" HIY "����Χס������һ˿��϶��\n" NOR;

}
