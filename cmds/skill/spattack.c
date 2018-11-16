// spattack.c

#include <ansi.h>

inherit F_CLEAN_UP;

mapping weapon_name = ([
        "sword" : "��",
        "blade" : "��",
        "staff" : "��",
        "whip"  : "��",
        "club"  : "��",
]);

void do_remote_fight(object me, object couple, object target, int n);
void do_here_fight(object me, object couple, object target, int n);

int main(object me, string arg)
{
        int same_place;
        string couple_id;
        string couple_name;
        object couple;
        object target;

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��ս����\n");

        if (! arg)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        } else
                target = present(arg, environment(me));

        if (! target || ! me->is_fighting(target))
                return notify_fail("����һ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !stringp(couple_id=query("couple/couple_id", me)) )
                return notify_fail("�㻹û�а��£�ʹʲô����һ����\n");

        couple_name=query("couple/couple_name", me);

        if (! objectp(couple = find_player(couple_id)))
                return notify_fail(couple_name + "������������ϣ��޷�������������\n");

        if (couple->is_ghost())
                return notify_fail(couple_name + "�����ǹ��һ������"
                                   "����Խ��������������\n");

        if (! living(couple))
                return notify_fail("������������޷���" + couple_name + "��ͨ��\n");

        if (target == couple)
                return notify_fail("���в�����\n");

        same_place = (environment(couple) == environment(me));

        if (! same_place)
                do_remote_fight(me,couple,target,query("sex/"+couple->name(1, me)));
        else
                do_here_fight(me,couple,target,query("sex/"+couple->name(1, me)));
        return 1;
}

void do_remote_fight(object me, object couple, object target, int n)
{
        object weapon;
        string chinese_type;
        int need, cost;
        int enhance, count;
        string msg;

        if (n > 500) n = 500;
        need = 300 - n / 2;
        cost = 300 - n / 3;

        if( query("jingli", me)<need )
        {
                write("����ͼ����İ��½��������ϵĹ�ͨ������"
                      "һʱ���þ������ã�������ϵ��\n");
                return;
        }

        if( query("jingli", couple)<need )
        {
                write("������ԼԼ�ĸо��������"
                      "�����������Ƿǳ�΢�������Ѳ�׽����\n");
                return;
        }

        if (me->is_busy())
        {
                write("( ����һ��������û����ɣ�����ʩչ����һ����)\n");
                return;
        }

        if (random(2))
                tell_object(me, HIM "������ĬĬ������" + couple->name(1) +
                            HIM "�����֣������е������������"
                            "�������͸���޾�����գ���������������\n\n" NOR);
        else
                tell_object(me, HIM "��������翵���գ���·𿴵�" + couple->name(1) +
                            HIM "�����������ϵĹ�����޾���������\n\n" NOR);

        if (random(2))
                tell_object(couple, HIM "���ƺ��о���" + me->name(1) +
                            HIM "�������������������֣�����֮"
                            "������������Ϭ����ĬĬ��Ϊ" +
                            gender_pronoun(query("gender", me))+
                            "ף����ȥ�ɣ��ҵİ��ˣ�\n" NOR);
        else
                tell_object(couple, HIM "ڤڤ��е���" + me->name(1) +
                            HIM "����ĺ�������һɲ�ǣ�������������"
                            "ȫȻ��ͨ����������ε�����ע����Է���������" +
                            gender_pronoun(query("gender", me))+"��\n"NOR);

        addn("jingli", -cost, me);
        addn("jingli", -cost, couple);
        weapon=query_temp("weapon", me);
        if (weapon && (chinese_type = weapon_name[query("skill_type", weapon)]))
        {
                if( query("gender", me) == "Ů��" )
                        msg = HIG "$N" HIG "��" + chinese_type +
                              "������������ݺ���ȣ�Ʈ����������е�" +
                              weapon->name() + HIG "��������ҹ�꣬����$n"
                              HIG "��\n" NOR;
                else
                        msg = HIC "$N��" + chinese_type + "��������Ȼ��$n" HIC "�����������" +
                              weapon->name() + HIC "�������磬������" +
                              chinese_type + "Ӱ����$p" HIC "���ڵ��С�\n" NOR;
        } else
        {
                if( query("gender", me) == "Ů��" )
                        msg = HIG "$N" HIG "����ǳЦ��ƮȻ������������"
                              "���ף�����������Ṳ̊��쳾������Ͷ��֮��û���κ�������\n" NOR;
                else
                        msg = HIC "$N" HIC "������Х��һ��ɱ����Ȼ������"
                              "�ص�ʱɫ�䣬$N" HIC "Ю�������֮�ƣ�ѹ��$n"
                              HIC "��\n" NOR;
        }

        message_combatd(msg, me, target);
        enhance = ((int)couple->query_skill("force") + n / 10) / 5;
        count = 1 + random(3 + n / 100);
        if (count > 3)
                count = 3;
        addn_temp("apply/attack", enhance, me);
        while (count--)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        }
        addn_temp("apply/attack", -enhance, me);
        me->start_busy(3);
        return;
}

void do_here_fight(object me, object couple, object target, int n)
{
        int need, cost;
        int enhance1, enhance2, count;
        string msg;

        if (n > 500) n = 500;
        need = 300 - n / 2;
        cost = 300 - n / 3;

        if (me->is_busy())
        {
                write("( ����һ��������û����ɣ�����ʩչ����һ����)\n");
                return;
        }

        if (couple->is_busy())
        {
                write("��İ���������æ���޷��������л���һ����\n");
                return;
        }

        if (! couple->is_fighting(target))
                couple->fight_ob(target);

        message_combatd(HIY "$N" HIY "��$n" HIY "��������һ����������"
                        "Ȼ��ͨ�����ɵĻ���һЦ��ֻ����������һ����ʱ\n"
                        "�Ѿ���" + target->name() + "�������У�\n" NOR,
                        me, couple);

        enhance1 = ((int)couple->query_skill("force") + n / 10) / 5;
        enhance2 = ((int)me->query_skill("force") + n / 10) / 5;
        count = 2 + random(5 + n / 50);
        if (count > 6)
                count = 6;
        addn_temp("apply/attack", enhance1, me);
        addn_temp("apply/attack", enhance2, couple);
        while (count--)
        {
                if (me->is_fighting(target) && (count % 2) == 0)
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                else
                if (couple->is_fighting(target))
                        COMBAT_D->do_attack(couple,target,query_temp("weapon", couple),0);
                else
                        break;
        }

        me->start_busy(2);
        couple->start_busy(2);
        addn_temp("apply/attack", -enhance1, me);
        addn_temp("apply/attack", -enhance2, couple);
        return;
}

int help (object me)
{
        write(@HELP
ָ���ʽ��spattack [<ʩ�ö���>]

��������ˣ��Ϳ���ʹ�û���һ�������ִ���������ڹ����Ķ��֣�
��ʹ��İ��²��������ߣ�Ҳ����������������ңԶ��ʱ�ո�����
֧�֣���Ȼ����Ҫ�ķѾ����������������ϵĴ���Խ�࣬�ķѵľ�
����Խ�١������İ��¾��������ߣ������һ��ʩչ����������
�֣�����Ҫ�ķѾ����������������������������ϵĴ����ڰ��µ�
�ڹ��ȼ���ء�
HELP );
        return 1;
}
