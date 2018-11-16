// /kungfu/skill/dragon-strike/xianglong.c  perform ����һ��
// Rama 2001/11/11

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����һ��"; }

void remove_effect(object me, object target, int lvl);
void msg_display(object me, object target, int lvl);

int perform(object me, object target)
{
        object armor;
        int lvl;
        /*
        mixed my_exp;

        my_exp=query("combat_exp", me);
        */

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�㲻��ս���С�\n");

        if( query_temp("yield", me) )
                return notify_fail("�㲻���ƣ����ʹ������һ����\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�㲻�ǿ��֡�\n");

        if( query_temp("xianglong", me)){
                return notify_fail("������ʹ�ý���һ����\n");
        }

        if( query("max_jingli", me)<500 )
                return notify_fail("��ľ�����Ϊ����������ʩչ����һ����\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("���������Ϊ����������ʩչ����һ����\n");

        if( me->query_skill("force") < 550 )
                return notify_fail("��Ļ����������δ�����޷�ʩչ����һ����\n");

        if( (lvl = me->query_skill("strike")) < 550 )
                return notify_fail("��Ľ���ʮ������Ϊ������\n");

        if ( me->query_skill_mapped("force") != "huntian-qigong")
                                         return notify_fail("�������ڹ����ԣ�\n");

        if( query("neili", me) <= lvl*2 )
                                         return notify_fail("�������������\n");

        if( query("jingli", me) <= 500 )
                                         return notify_fail("��ľ���������\n");

        set_temp("xianglong", 1, me);
        message_combatd(HIR "$N���۵��˫����������ת�˸�ԲȦ������������ȫ������\n\n" NOR, me,target);
        addn("neili", -lvl/2, me);
        addn("jingli", -lvl/5, me);
        lvl = (int)(lvl / 5);

        addn_temp("apply/defense", lvl, me);
        me->start_busy(1+random(2));

        call_out("msg_display",1+(int)((me->query_skill("strike")-300)/50),me,target,lvl);

        return 1;
}

void msg_display(object me, object target, int lvl)
{
        string *circle, msg;

        if (!me) return;

        if (!target ||
            !target->is_character() ||
            !me->is_fighting(target) ||
            !living(me))
        {
                delete_temp("xianglong", me);
                addn_temp("apply/defense", -lvl, me);
                return;
        }


        circle = ({
                "$NͻȻ���һ����˫���������$p�����ͻ���ȥ��\n",
                "$N������������һ�������ֺ���һ�ƣ�����$p��ȥ��\n"
        });

        msg = HIG"\n"+ circle[random(sizeof(circle))] +"\n" NOR;

        circle = ({
                "����δ����$p�Ѹ��ؿں������������֮�䣬$N��������ŭ������ӿ������",
                "ֻһ˲֮�䣬$p�����Ϣ���ͣ�$N��������ŭ����ӿ���Ʋ��ɵ���������һ�����εĸ�ǽ����$p��ǰ���塣"
        });

        msg += HIG"\n"+ circle[random(sizeof(circle))] +"\n" NOR;

        if( target
            &&  target->is_character()
            &&  me->is_fighting(target) ) {
                message_combatd(msg, me, target);
                call_out("remove_effect",2,me,target,lvl);
        } else {
                delete_temp("xianglong", me);
                addn_temp("apply/defense", -lvl, me);
        }
        return 0;
}

void remove_effect(object me, object target, int lvl)
{
        int jiali, jianu, ap, dp, pp,dmg,damage;
        object weapon;
        string *limbs, limb, result, str, type;

        if (!me) return;

        if (!target ||
            !target->is_character() ||
            !me->is_fighting(target) ||
            !living(me))
        {
                delete_temp("xianglong", me);
                addn_temp("apply/defense", -lvl, me);
                return;
        }

        weapon=query_temp("weapon", target);
        jiali=query("jiali", me);
        jianu=query("jianu", me)*5;
        ap = me->query_skill("strike");
        ap += (jiali + jianu)/4;
        ap *= 2;
        if (living(target))
        {
            pp = target->query_skill("parry");
            dp = target->query_skill("dodge");
        }  else
        {
            pp = 0;
            dp = 0;
        }
        type = "����";

        if( target
        &&      target->is_character()
        &&      me->is_fighting(target) ) {

        if (wizardp(me))
                printf("ap=%d,pp=%d,dp=%d,query_temp(apply/defense, me)=%d,lvl=%d.\n",ap,pp,dp,query_temp("apply/defense", me),lvl);

        if( ap/2 + random(ap) > dp + pp ) {
            message_combatd(HIM"$N��˫���Ѹ��Ż��������һ���������ش���$p�ؿڣ����ſ������������߹Ƕ��˼�����\n"NOR, me, target);
            dmg = ap;
            dmg += jiali + jianu*5;
            dmg += random(dmg/2);

        if (wizardp(me))
                printf("damage = %d\n",dmg);

            target->receive_damage("qi", dmg,  me);
            target->receive_wound("qi", dmg/2+random(dmg/2), me);
            target->start_busy(1+random(2));

            addn("neili", -dmg/3, me);
            addn("jingli", -dmg/6, me);

            limbs=query("limbs", target);

            result = COMBAT_D->damage_msg(dmg, type);
            result = replace_string( result, "$l", limbs[random(sizeof(limbs))]);
            result = replace_string( result, "$p", target->name() );
            message_combatd(result, me, target);

            str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
            message_combatd("($N"+str+")\n", target);
        } else {
            if ( objectp(weapon) )
            {
                message_combatd(HIC "$n��֮�£�$p����������Բ��ס��ǰ��ͬʱ���������Ʈ����ˣ��ܿ���$N��һ�ơ�\n" NOR, me, target, weapon);
            }
            else {
                message_combatd(HIC "$n��֮�£�˫������������Բ��ס��ǰ��ͬʱ���������Ʈ����ˣ��ܿ���$N��һ�ơ�\n" NOR, me, target);
            }
        }
        }
        me->start_busy(2+random(2));
        delete_temp("xianglong", me);
        addn_temp("apply/defense", -lvl, me);
        return 0;
}
