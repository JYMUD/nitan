#include <ansi.h>
#include <combat.h>

#define WSWD "��" HIR "��"BLU"˫"HIM"��"HIW"��" NOR "��"
#define WS "��" HIR "��"BLU"˫" NOR "��"
#define WD "��" HIM"��"HIW"��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill = (int)me->query_skill("kuihua-mogong", 1), i;
        int ap, dp;
        int damage;
        int x,a;
        string msg,nextmsg;
        object weapon=query_temp("weapon", me);

        if( !target || target == me ) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ׼��ܡ�\n");

        if( me->is_busy()) return notify_fail("����æ���ء�\n");

        if( userp(me) && !query("can_perform/kuihua-mogong/ws", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( !target || target==me || !target->is_character() )
                return notify_fail(WS"ֻ�ܶԶ���ʹ�á�\n");

        if( !weapon
         || query("skill_type", weapon) != "sword"
        ||      me->query_skill_mapped("sword") != "kuihua-mogong" )
                return  notify_fail("�������޷�ʹ�þ�����\n");

        if (skill < 200 || (int)me->query_skill("kuihua-mogong", 1) < 200)
                return notify_fail("����Ŀǰ����Ϊ������������������"WS"\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ��������"WS"���裡\n");

        if( query("neili", me)<500 )
                return notify_fail("���������������"WS"���裡\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->start_busy(1 + random(3));
        msg = HIM "$NͻȻ����һתգ�ۼ�ʹ�ÿ���ħ�����ռ�����----" NOR
                WSWD HIM "֮" NOR WS "\n" HIW "$N����ӨȻ�й⣬�ƺ�������ħ��֮�С�\n" +
                "$N����" + weapon->name() + "������˫��Ӱ����$n��\n";
        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*20+
                me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*10+
                target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if (ap / 2 + random(ap) < dp)
        {
            msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
                    "�Ĺ���һһ���⡣\n" NOR;
        } else
        {
            addn("neili", -560, me);
            damage = ap * 2 + random(ap * 3 / 4) - 60 - random(40);
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                    HIY "$n" BLU "ֻ�����Ѿ����������ħ��֮�У�" HIY
                    "$N����" + weapon->name() + WHT
                    "��ͬ�����еĹ��㣬�Ӹ�����λ���˹��������޿ɱܣ�\n" NOR);
        }
        message_sort(msg, me, target);

        if( query("neili", me)>2000
         && present(query("id", target),environment(me) )
        &&  me->is_fighting(target)
        &&  target->is_fighting()
        &&  living(target)
        &&  living(me)
        &&  !target->is_ghost()
        &&  !me->is_ghost()
        &&  me->query_skill_mapped("sword") == "kuihua-mogong"
         && query("skill_type", weapon) == "sword"
         && (userp(me) && query("can_perform/kuihua-mogong/wd", me )
                || !userp(me))
                )
        {
                remove_call_out("perform2");
                call_out("perform2",0, me);
        }
        else if( userp(me) && !query("can_perform/kuihua-mogong/wd", me))//ûѧ���޶�
        {
                remove_call_out("check_wd");
                call_out("check_wd",1,me);
        }
        return 1;
}

int perform2(object me)
{
        int ap, dp;
        string nextmsg;
        int damage;
        object target;
        object weapon=query_temp("weapon", me);

        if( !target ) target = offensive_target(me);
        if( !target || living(target) )     return 1;
        if(!objectp(weapon)) return 1;

        nextmsg = HIM "˵�ǳ���ʱ�죬$N������תʹ����" NOR WSWD "֮" WD HIM
                "ʽ��ɲ�Ǽ���������ܲ���\n" NOR HIM "$n�����༸��ֹͣ������������������$N\n" NOR;
        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*20+
        me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*8+
        target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if ( ap / 2 + random(ap) < dp && !(target->is_busy()) )
        {
                nextmsg += HIG "��ʱ$n��ס����" HIG "�ֵ��÷�����$N" HIG
                        "�Ĺ���һһ���⡣\n" NOR;
        } else
        {
                addn("neili", -260, me);
                damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
                nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                        HIY "$n" BLU "ֻ��������ͬ�򽣴���һ�㣬" HIY "$N"
                        WHT "��ͬ����һ�㣬�Ʊ�Ҫȡ$n������\n" NOR
                        HIM "��ʱ�˿�$N����������" + weapon->name() + HIM
                        "��˲��仯�˼������У�����$n�����޷��ҳ��ƽ�֮����\n" +
                        "˵ʱ����ʱ��" + weapon->name() + HIM
                        "�Ѿ��̽���$n�����ţ���Ѫ����һ�أ���\n" NOR);
        }
        message_vision(nextmsg, me, target);
        return 1;
}

int check_wd(object me)
{
        int x,a;
        object target;

        x=query("kar", me);
        a = x + random(70);

        if( !target ) target = offensive_target(me);
        if(living(target))  return 1;
        if (me->is_fighting())  return 1;

        if(a>=80){
                tell_object(me,
                        HIW "\n��ͻȻ�������򣬶Ըղ�ʹ�ù���ħ��֮" WS
                        HIW "ʽ������ĥ��\n���ˣ�����Ҳ����Ү����ѧ����" WSWD
                        HIW "֮" WD HIW "ʽ��\n" NOR);
                set("can_perform/kuihua-mogong/wd", 1, me);
        }
        return 1;
}
/*
    } else {
        msg += "$nаа�Ŀ���$N����֪������$n���ֳ���ֵĿ־塣\n"NOR;
        msg += HIM"\n$N��Ȼ�뵽��ʲô��$n���̿�ʼ����ʹ�������������\n\n"NOR;

        ap=me->query_skill("kuihua-mogong",1)*1+query("dex", me)*10+
        me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*20+
        target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -400, me);

        if (ap / 2 + random(ap) < dp)
        {
            msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
            "�Ĺ���һһ���⡣\n" NOR;
        } else
        {
            addn("neili", -260, me);
            damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
              HIY "$n" BLU "ֻ�����Ѿ����������ħ��֮�У�"HIY"$N"
              WHT "��ͬ��������һ�������㵸���ӾžŰ�ʮһ����λɱ�˹�ȥ��\n" NOR);
        }

        message_combatd(msg, me, target);

    }
    if(!me->is_fighting(target)) me->fight_ob(target);
    if(!target->is_fighting(me)) target->fight_ob(me);
    remove_call_out("checking");
    call_out("checking", 1, me);
    return 1;
}
*/
