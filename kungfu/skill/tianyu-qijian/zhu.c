// This program is a part of NITAN MudLIB
// zhu.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        int bonus, hits;
        object weapon;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
              || query("skill_type", weapon) != "sword" )
                return notify_fail("����Ҫһ�ѽ�����ʩչ�����������\n");

        if( query("neili", me)<400 )
                return notify_fail("���������ʣ�޼����޷�ʩչ�����������\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ���㣬�޷�ʩչ�����������\n");

        if ( me->query_skill("tianyu-qijian", 1) < 100 )
                return notify_fail("��������潣������죬����ʹ�á����������\n");

        if ( me->query_skill("sword", 1) < 100 )
                return notify_fail("��Ļ�������������죬����ʹ�á����������\n");

        if( query("jiali", me)<1 )
                return notify_fail("�����̫�٣��޷�ʹ�á����������\n");

        if( query("09g/ring", me) == "li" )
        {
                if ( me->query_skill("xiaowuxiang", 1) < 100 )
                        return notify_fail("���С���๦��Ϊ���㣬ʹ�������������������\n");
                if ( me->query_skill_mapped("force") != "xiaowuxiang" )
                        return notify_fail("��û��ʹ��С���๦���޷�ʹ�á��������������\n");
        }

        else
        {
                if ( me->query_skill("bahuang-gong", 1) < 100 )
                        return notify_fail("��İ˻�����Ω�Ҷ�����Ϊ���㣬ʹ�������������������\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("��û��ʹ�ð˻�����Ω�Ҷ��𹦣��޷�ʹ�á��������������\n");
        }

        if( query_temp("09_pfm/zhu", me) )
                return notify_fail("������ʹ�á����������\n");

        if( query_temp("09_pfm/yun_duzun", me) )
                return notify_fail("���������á�Ω�Ҷ����ķ����޷�ʹ�á����������\n");

        if( query_temp("09_pfm/zhu_over", me) )
                return notify_fail("��ո�ʹ�ù��������������ʱ��Ѫ���������ǵ�һ�����ðɡ�\n");

        bonus = me->query_skill("tianyu-qijian", 1) / 30;
        bonus += me->query_skill("sword", 1) /30;
        bonus += me->query_skill("piaomiao", 1) /35;

        addn_temp("apply/attack", bonus, me);
        addn_temp("apply/damage", bonus, me);
        addn_temp("apply/defense", bonus*2, me);

        message_combatd(HIR"\nֻ��һ�������ƿյ�����֮����$N���е�"+weapon->name()+HIR"��ʱ��˸��ҫ�۵Ĺ�â��һ�ɹɺ�����\n"+
                          "������������Ȼ$N��ʽͽȻһ�죬ʹ��һ�С�"HIW"��������"HIR"������ʱ�����콣Ӱ����ǵأ�\n"+
                          "�·�������Ķ�ë��ѩ���������ֱѹ��$n������Ҫ�����ٶȸ��ǿ�þ��ˣ�\n"NOR, me, target);

        hits = bonus/3;

        if ( hits < 3 )
                hits = 3;
        if ( hits > 9 )
                hits = 9;

        set_temp("09_pfm/zhu", hits, me);
        addn("neili", -200, me);

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);

        return 1;
}

void remove_effect(object me, int bonus)
{
        addn_temp("apply/attack", -bonus, me);
        addn_temp("apply/damage", -bonus, me);
        addn_temp("apply/defense", -bonus*2, me);
        delete_temp("09_pfm/zhu", me);
        delete_temp("09_pfm/zhu_hit_done", me);
        set_temp("09_pfm/zhu_over", 1, me);
        if ( me->is_fighting() )
                me->start_busy(3);

        remove_call_out("zhu_done");
        call_out("zhu_done", 12, me);
}

void zhu_done(object me)
{
        if ( !me )
                return;

        tell_object(me, HIY"����һ��ʱ�����Ϣ�����ֿ���ʹ�á���������ˣ�\n"NOR);
        delete_temp("09_pfm/zhu_over", me);
}

void check_fight(object me, object target, int bonus)
{
        if ( !me )
                return;

        if( !me->is_fighting() || !query_temp("09_pfm/zhu", me) || query_temp("09_pfm/zhu", me)<1
             || !target || !living(target) )
        {
                message_combatd(WHT"\n$N������һ���������еĽ���Ҳ�Բ�����ǰһ�������ˡ�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query("neili", me)<300 )
        {
                message_combatd(HIR"\n$N��ͷð�����������������棬�����ϵĹ�âһ����ʧ�����ˡ�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if ( me->query_skill_mapped("sword") != "tianyu-qijian" )
        {
                message_combatd(HIR"\n$N��Ȼ��ʽһ�ߣ����ϵĹ�â��ʱ��ʧ����Ӱ���١�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( !query_temp("weapon", me) )
        {
                tell_object(me, HIR"\n��ı��������ˣ��޷�����ʹ�á���������ˡ�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);
}

int help(object me)
{
        write(WHT"\n���������\n\n"CYN+
                 " ���������������������ʩչ����ʱ���������ëƮ����£������ݺ�\n"+
                 " ��Ӱ��ѩ��������ǰ����������Χס��ʹ����޿ɱܣ����޿��ˡ���һ��\n"+
                 " ������ʱֻ���������У�Ȼ���������г�֮ʱ�������������У�ǰ��һ\n"+
                 " ���ǳɣ����಻����������ѹ��һ������֮�£�ʵ������������\n\n"+

                 " "HIR"ע"WHT"�����в����롸Ω�Ҷ����ķ�ͬʱʹ�á�\n\n"+

              WHT" Ҫ�󣺰˻�����Ψ�Ҷ��𹦡�"HIR"100"WHT" ��\n"+
              WHT" ������С���๦          ��"HIR"100"WHT" ��\n"+
              WHT" �����������潣  ����������"HIR"100"WHT" ��\n"+
              WHT" ��������������������������"HIR"100"WHT" ��\n"+
              WHT" ��������ǰ����  �������� "HIR" 400"WHT" ��\n"+
              WHT" ����������������������� "HIR"1000"WHT" ��\n\n"+

              WHT" ս����ʹ�á�\n"NOR);

        return 1;
}