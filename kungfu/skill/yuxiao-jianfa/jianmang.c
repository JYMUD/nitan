
// jianmang.c

/*
׿�����ڶ������У���־���֮�⣬��������־��£����ӵ�����Ĵ��˰��
Ȧ�ӣ�����һͦ��������ͻȻ����������²�������â��Ⱥ������ʮ��������
����������â����â�����ǽ�â���Ƴ��߰�����������׿������¶��Ц������
����һ����������âͻʢ���������ؿڴ�����

�����δ�������˵ı�������������â������Ⱥ�����ȣ�������һ�������书��
�Լ���Ȼ�Ը����ˣ��Ų�һ�����˿�ȥ��׿������һ������ȫ������;�޷�
���У�ˢ��һ���죬���������˴�ʯ���У�����������ʯ���˼���Ӳ�Ļ�
��ʯ���ƣ�����ĳ�����Ȼ����һ�����࣬�ɼ������ڽ����ϵ�����ʵ�Ƿ�ͬ
С�ɣ�

Maco��ע��
��â��һperform���������������һ�����Ȼ��Kane�����code����������Ҳ
���϶�Ϊ���｣����׼perform��Maco�ڴ˱㽫��ʹ�����ǰ�˽Ų��Լ���
չcode�仯�ԣ�����Щ��Ȥζ��

˫�ؽ�â���ã���춽�ʣ��Ľ�â��Чʱ��һ���ù⣬��Ϊһ�������������
�ߣ�Ȼ����âЧ�����̽�������ͨ��Ҳ�����̶��ѣ����Ǻ�ƽ����ͬ�ġ�ʣ��
ʱ��Խ��������Խ�󣬿�˵��ʹ����â������һ����

�֣������⡱�ߵͣ�Ӱ��˫�ؽ�â�������ҡ�
*/

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��â"; }

void checking(object me, object weapon,int damage);
void remove_effect1(object me, object weapon, int damage) ;

int perform(object me, object target)
{
        object weapon;
        int i, damage, sword, jianyi;

        weapon=query_temp("weapon", me);

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("��âֻ�ܶ�ս���еĶ���ʹ�á�\n");

        // jianyi = (int)me->query("tianmo_jieti/times");
        jianyi = (int)me->query_skill("yuxiao-jianfa", 1) / 200;
        if (jianyi > 8) jianyi = 8;

        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("�������޽����������á���â������\n");

        if( query_temp("th_jianmang", me) )
        {
                if( jianyi < 1 )
                        return notify_fail("����Խ�������򣬽�âʩչ���������������Ǽ��ޣ�\n");
        }

        if( query_temp("th_wait_jianmang", me) && !query_temp("th_jianmang", me) )
                return notify_fail("����Ѫ��ӿ���޷����á���â����\n");

        if( query_temp("th_jianzhi", me) )
                return notify_fail("���������ý�ָ����Ĺ��ƣ����ܷ������á���â����\n");

        if( me->query_skill("yuxiao-jianfa",1) < 200 )
                return notify_fail("�����｣����Ϊ����������δ���򡸽�â����\n");

        if( me->query_skill("bibo-shengong", 1) < 150 )
                return notify_fail("��ı̲�����Ϊ���δ����ʩչ��âֻ���˼�����\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("�����õ��ڹ��޷�ʩչ���｣���ġ���â����\n");

        if( query("max_neili", me) <= 1200 )
                return notify_fail("���������Ϊ���㣬����������ʩչ��â��\n");

        if( query("neili", me) <= 600 )
                return notify_fail("�����������������������ʩչ��â��\n");

        if( query("jingli", me) <= 200 )
                return notify_fail("��ľ������ޣ�������ʩչ��â��\n");

        sword = me->query_skill("yuxiao-jianfa",1)/10;
        damage = me->query_skill("force") + me->query_skill("qimen-wuxing",1);

        if( query_temp("th_jianmang", me)){
                addn("neili", -150, me);
                addn("jingli", -50, me);
                set_temp("final_jianmang", 1, me);
                for (i =0;i < jianyi*2;i++)
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                delete_temp("final_jianmang", me);
                delete_temp("th_jianmang", me);
                me->start_busy(1);
                checking(me, weapon, damage);
        }
        else {
                addn("neili", -300, me);
                addn("jingli", -100, me);
                addn_temp("th_jianmang", sword/3, me);
                set_temp("th_wait_jianmang", 1, me);
                addn_temp("apply/defense", damage, me);
                addn_temp("apply/damage", damage, me);
                addn_temp("apply/attack", damage, me);
                me->start_busy(1);

                message_combatd(HIC
                        "$N����Ц������"+NOR+weapon->name()+HIG"������ɲұ̰�͸��ɫ��\n"+
                        "һ�����ɫ��â�ӽ�����ֱ�������� ......\n"+NOR+
                        weapon->name()+NOR+HIC"ǰ������������"+HIG"��â"NOR+
                        HIC"��������������²���������ȥ������ף�����\n"NOR,
                me);
                call_out("checking", 1, me, weapon, damage);
                call_out("remove_effect2", sword*2/3, me);
        }
        return 1;
}

void checking(object me, object weapon, int damage)
{
        if (!me) return;
        addn_temp("th_jianmang", -1, me);

        if( !living(me) || me->is_ghost() )
        {
                remove_effect1(me, weapon, damage);
                return ;
        }
        if( !me->is_fighting() )
        {
                message_combatd("\n$N��ս���ѱϣ��㼴�����˴߶���â��������\n", me);
                remove_effect1(me, weapon, damage);
                return ;
        }
        else if( !weapon || environment(weapon) != me || weapon != query_temp("weapon", me) )
        {
                message_combatd("\n$N���б�����ʧ����â������֮�߽⡣\n"NOR, me);
                remove_effect1(me, weapon, damage);
                return ;
        }
        else if( me->query_skill_mapped("sword") != "yuxiao-jianfa"
         || me->query_skill_mapped("force") != "bibo-shengong" )
        {
                remove_effect1(me, weapon, damage);
                message_combatd(HIG"\n$N�书·�����䣬"+
                        weapon->name()+HIG"����â���š�\n"NOR, me);
                return ;
        }
        else if( query_temp("th_jianmang", me) <= 0 )
        {
                tell_object(me,HIG"\n��â�����ѵ����ޣ�\n"NOR);
                remove_effect1(me, weapon, damage);
                return;
        }
        else call_out("checking", 1, me, weapon,damage);

        if (random(2))
                message_combatd(HIG"$N��"NOR+"$n"+NOR+HIG"������ɫ��â�������̣���˸����....\n"NOR,me,query_temp("weapon", me));
        return;
}

void remove_effect1(object me, object weapon, int damage)
{
        if (!me) return;
        addn_temp("apply/defense", -damage, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/attack", -damage, me);
        delete_temp("th_jianmang", me);

        if (!weapon) return;

        if( environment(weapon) != me || weapon != query_temp("weapon", me) )
                return;
        else if( query("weapon_prop/damage", weapon)<40){
                message_combatd(HIW"\nֻ����һ�����죬$N����"+weapon->name()+
                        HIW"����ס������������ѳ���Ƭ����\n"NOR,me);
                destruct(weapon);
        }
        else {
                message_combatd(HIY"\n$N����"+weapon->name()+HIY+
                        "��������һ�����죬���ڽ��ϵ���â����ʧ����Ӱ���١�\n"NOR, me);
        }
}

void remove_effect2(object me)
{
        if (!me) return;
        delete_temp("th_jianmang", me);
        delete_temp("th_wait_jianmang", me);
        tell_object(me, HIG"\n�㾭��һ��ʱ�������Ϣ��������Ѫ����ת�糣��\n"NOR);
}