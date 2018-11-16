// This program is a part of NT MudLIB
// suxing.c ���ľ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "���ľ�"; }

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        string msg;
        object weapon;
        int damage,ap,dp,married;

        if( query("gender", me) != "Ů��" )
                return notify_fail("��Ů����ֻ����Ů���ã�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ľ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_skill_mapped("force") != "yunv-xinfa" )
                return notify_fail("�����õĲ�����Ů�ķ����޷�ʩչ���ľ���\n");

        if( me->query_skill("yunv-xinfa", 1) < 200 )
                return notify_fail("�����Ů�ķ����δ�����޷�ʩչ���ľ���\n");

        if( me->query_skill("yunv-jian", 1) < 200 )
                return notify_fail("�����Ů���Ľ������δ�����޷�ʩչ���ľ���\n");

        if( !(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õı������ԡ�\n");

        if( !stringp(me->query_skill_mapped("sword")) ||
            me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("����뼤����Ů���Ľ���Ϊ�������ܹ�ʹ�����ľ���\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����������ʹ����Ů���ģ�\n");

        if( query("jingli", me)<500 )
                return notify_fail("��ľ�������ʹ����Ů���ģ�\n");

        message_combatd(HIW "$NͻȻ��ɫׯ�أ�˫Ŀ��Σ�����" +
                       query("name", weapon)+HIW+"������һ���˪���������ˣ�\n\n"NOR,me);
        message_combatd(HIW "$N���������̬�ޱ����Ʈ�ݣ��ӽ���$nֱ�̹�ȥ���������ǣ�\n\n"NOR,me,target);

        ap = attack_power(me, "sword") + me->query_skill("force");
        dp = defense_power(target, "parry") + me->query_skill("force");

        if( mapp(query("family", target)) && query("family/family_name", target) == "ȫ���" )
                ap += ap/3;

        if( query("can_learn/yunv-xinfa/wall", me) )
                ap *= 2;

        if (ap/2 + random(ap) > dp || !living(target))
        {
                damage = damage_power(me, "sword");
                if( query("can_learn/yunv-xinfa/wall", me) ) damage *= 2;
                //�жϽ������ͷ�������Ϊ�Ĵ���
                if( !mapp(query("couple", me)))married=1;
                else married=query("couple/married", me);
                if( mapp(query("sex", me)))married+=query("sex/times", me);
                damage -= (damage/5) * (married - 1);
                if (damage < 10) damage = 10;
/*
                target->receive_damage("qi", damage/2 + random(damage/2), me);
                target->receive_wound("qi", damage, me);
*/
                msg=HIR"ֻ��$nһ���Һ�����Ȼ��$N��"+NOR+query("name", weapon)+HIR+
                      "���صĴ��У���������������һ���ɫ��˪�����ɪɪ������\n"NOR;
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200, msg);
                if (!target->is_busy())
                        target->start_busy(1+random(2));
                me->start_busy(2);
        } else
        {
                msg = HIY "$n��״��ʧɫ��˫���أ������ˣ������ܹ�$N��������ľ������Ǵ����졣\n"NOR;
                me->start_busy(2+random(4));
        }
        message_combatd(msg, me, target);
        return 1;
}
