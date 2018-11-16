
// jianzhi.c ��ָ���乥��
// �������(20)�����｣���뵯ָ������Թ���Ѩ��Ϊ������ָ���䣬��΢����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��ָ����"; }

void remove_effect(object me, object weapon, int speed, int damage);

int perform(object me, object target)
{
        object weapon;
        int speed, damage, sword;

        weapon=query_temp("weapon", me);

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("��ָ���乥��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("�������޽������̸���ϡ���ָ���䡹��\n");

        if( query_temp("secondary_weapon", me) )
                return notify_fail("�������Ŷ̱���û�����ܿճ�������ָ���䡹�ˡ�\n");

        if( query_temp("th_jianmang", me) )
                return notify_fail("��������ʹ������â���������ٷ����ˣ�\n");

        if( query_temp("th_jianzhi", me) )
                return notify_fail("���������ý�ָ����Ĺ��ƣ�\n");

        if( me->query_skill("yuxiao-jianfa",1) < 120 )
                return notify_fail("������｣����Ϊδ�������ܽ�ָ���乥�У�\n");

        if( me->query_skill("tanzhi-shentong",1) < 120 )
                return notify_fail("��ĵ�ָ��ͨ��Ϊδ�������ܽ�ָ���乥�У�\n");

        if( me->query_skill("bibo-shengong", 1) < 120 )
                return notify_fail("��ı���������Ϊ���㣬ǿʹ��ָ���䣬ͽȻ��ɢ������\n");

        if( me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("�㲢û��ʹ�����｣����\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("������ʹ���ڹ��޷��뽣ָ����֮�ķ�Э����\n");

        if( me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("����ʩչ��ָ�����ǵ�ָ��ͨ��\n");

        if( me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("�㻹û��׼����ʩչ��ָ��ͨ��\n");

        if( query("max_neili", me) <= 1200 )
                return notify_fail("���������Ϊ���㣬����ʩչ��ָ���䣬���������������������գ�\n");

        if( query("neili", me) <= 400 )
                return notify_fail("����������㣬������ʩչ��ָ���䣡\n");

        if( query("jingli", me) <= 400 )
                return notify_fail("��ľ������㣬������ʩչ��ָ���䣡\n");

        damage = me->query_skill("yuxiao-jianfa",1) + me->query_skill("tanzhi-shentong",1);
        sword = (me->query_skill("sword") + me->query_skill("finger") );
        addn("neili", -250, me);
        addn("jingli", -100, me);

        //����������
        addn_temp("apply/defense", damage, me);
        addn_temp("apply/attack", damage, me);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        message_combatd(HIG"$N����"+weapon->name()+HIG"һ�ڣ�������ȥ���������磬�������ǹ��ƣ�һ�в���$n���⿪ȥ���ڶ��е����������������\n"NOR, me,target);

        //�ڶ����Կ�
        addn_temp("apply/attack", damage/3, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        addn_temp("apply/attack", -damage/3, me);

        if(me->is_fighting(target) ){
        message_combatd(HIG"$N����δֹ������ָ�����̾�����������$n��·Ѩ����"+HIW"�����｣����"NOR+HIG"��"+HIW"����ָ��ͨ��"NOR+HIG"����Ϊ�ã�Խ����΢����仯���\n"NOR, me,target);

        weapon->unequip();
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        weapon->wield();
        }
        set_temp("th_jianzhi", sword/10, me);

        if( query_temp("th_jianzhi", me)>70 )
        set_temp("th_jianzhi", 70, me);

        call_out("checking", 1, me, weapon,speed,damage);

        return 1;
}

void checking(object me, object weapon,int speed, int damage)
{
        if (!me) return;
        if( !living(me) || me->is_ghost() )
        {
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        if( !me->is_fighting() )
        {
                message_combatd("\n$N��ս���ѱϣ��㼴�����˽�ָ����Ĺ�����\n", me);
                remove_effect(me, weapon, speed, damage);
                return ;
        }

        else if( environment(weapon) != me || weapon != query_temp("weapon", me) )
        {
                message_combatd("\n$N���б�����ʧ�������ջ��˽�ָ����Ĺ��ơ�\n"NOR, me);
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        else if( me->query_skill_mapped("sword") != "yuxiao-jianfa"
         || me->query_skill_mapped("finger") != "tanzhi-shentong"
         || me->query_skill_prepared("finger") != "tanzhi-shentong" )
        {
                remove_effect(me, weapon, speed, damage);
                message_combatd(HIG"\n$Nһ��"+weapon->name()+HIG"����Ȼ�任���������������｣���뵯ָ��ͨ�Ĵ��������\n"NOR, me);
                return ;
        }
        else if( query("neili", me)<500 || query("jingli", me)<500 )
        {
                tell_object(me, HIW "\n�㾪����Ϣ����������˿칥������̷��������²�����ɫ�������������֡���ָ��ͨ�����ơ�\n" NOR);
                remove_effect(me, weapon, speed, damage);
                return ;
        }
        else if( query_temp("th_jianzhi", me) <= 20 )
        {
                remove_effect(me, weapon, speed, damage);
                message_combatd(HIG"\n$Nһ��"+weapon->name()+HIG"������ʳ�ж�ָ���𽣾������������ʹ�������｣������\n"NOR, me);
                return;
        }

                else call_out("checking", 1, me, weapon,speed,damage);
                return;
}

void remove_effect(object me, object weapon, int speed, int damage)
{
        if (!me) return;
        addn_temp("apply/defense", -damage, me);
        addn_temp("apply/attack", -damage, me);

        delete_temp("th_jianzhi", me);
}