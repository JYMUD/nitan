#include <ansi.h>

inherit F_SSERVER;
string name() { return "��������"; }

int perform(object me, object target)
{
        object weapon;
        int damage, club;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("���������ա�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("�������޹����������á��������ա�����\n");

        if( query_temp("sl_leidong", me) )
                return notify_fail("���ʹ�꡸�׶����졹��Ŀǰ��Ѫ��ӿ���޷��ٴ����ã�\n");

        if( (int)me->query_skill("weituo-chu", 1) < 120)
                return notify_fail("��Τ������Ϊ����������δ��ʹ�á��׶����졹��\n");

        if( me->query_skill("force", 1) < 120 )
                return notify_fail("����ڹ���Ϊ���δ����ʩչֻ���˼�����\n");

        if( query("max_neili", me) <= 1500 )
                return notify_fail("���������Ϊ���㣬����������ʩչ���׶����졹��\n");

        if( query("neili", me) <= 600 )
                return notify_fail("�����������������������ʩչ���׶����졹��\n");

        message_combatd(BLU "\nͻȻ$N���һ�������������ա�����ɫ৵ı��ͨ�죬�뷢�Էɣ���������" +
                           weapon->name() + BLU "���У����ˡ���һ��������" HIW " �������� " BLU "��\n " NOR, me);

        damage = me->query_skill("weituo-chu", 1) + me->query_skill("buddhism",1);
        damage /= 6;
        club = me->query_skill("staff") / 3;

        if ( userp(me) )
        {
                addn("neili", -300, me);
                if( damage>query("weapon_prop/damage", weapon)*2 )
                     damage=query("weapon_prop/damage", weapon)*2;
                else addn("rigidity", 1, weapon);
        }

        set_temp("sl_leidong", 1, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/attack", damage, me);

        call_out("remove_effect1", club/2, me, weapon, damage);
        call_out("remove_effect2", club * 2/3, me);
        me->start_exert(club * 2 / 6, "���������ա�");

        return 1;
}

void remove_effect1(object me, object weapon, int damage)
{
        if (!me) return;
        addn_temp("apply/attack", -damage, me);

        if (!weapon) {
                set_temp("apply/damage", 0, me);
                return;
        }
        addn_temp("apply/damage", -damage, me);
        message_vision(HIY "\n$Nһ�ס��������ա�ʹ�꣬����"NOR + weapon->name() + HIY"�ϵĹ�â����Ҳ��ʧ�ˡ�\n"NOR, me);
}

void remove_effect2(object me)
{
        if (!me) return;
        delete_temp("sl_leidong", me);
        tell_object(me, HIG "\n �㾭��һ��ʱ�������Ϣ���ֿ���ʹ�á��������ա��ˡ�\n"NOR);
}
