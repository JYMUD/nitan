//xunlei.c Ѹ�׽�

#include <ansi.h>

inherit F_SSERVER;

string name() { return "Ѹ�׽�"; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
        int speed, attack, lv, damage;

        lv = (int)me->query_skill("shenlong-jian", 1);
        damage = lv + random(lv/2) + (int)me->query_skill("sword",1);
        attack = lv + random(lv/2);
        speed = me->query_skill("sword")/80;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
             return notify_fail("��Ѹ�׽���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("xunlei_yushi", me) || query_temp("xunlei", me) )
             return notify_fail("�㽣��δ����������ʩչ��Ѹ�׽�����\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
             return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("neili", me)<300 )
             return notify_fail("�������������\n");

        if( me->query_skill("shenlong-jian", 1) < 100 )
             return notify_fail("��ġ�����������δ�����磬�޷�ʹ�á�Ѹ�׽�����\n");

        msg=HIR"\n$N����"+query("name", weapon)+HIR"����ָ���Լ��ؿڣ�����бб���⣬����֮�������ƻؽ�����һ�㣡\n\n"NOR;
        message_combatd(msg, me,target);
        me->start_busy(1);
        ob = me->select_opponent();
        set_temp("xunlei", 4, me);
            addn("neili", -5, me);
        me->set_temp("xunlei_yushi");
        call_out("checking", 1, me, target);
        return 1;
}


  void checking(object me, object target, int speed, int damage, int attack)
{

        object weapon;
        if ( !objectp( me ) ) return;
        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"){
                tell_object(me, "\n�������޽�������ֹͣ��Ѹ�׽��ļ��ơ�\n" NOR);
                delete_temp("xunlei", me);
                return;
        }
        else if( query("weapon_prop", weapon) == 0){
                tell_object(me, "\n���"+weapon->name()+"�ѻ٣��޷�����Ѹ�׽��Ĺ��ƣ�\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
          else if( query("neili", me)<300){
                  message_combatd(HIR"$N���ھ�������������ò�ֹͣѸ�׽��Ĺ��ƣ�\n" NOR, me,target);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if ( me->query_skill_mapped("sword") != "shenlong-jian" ) {
                tell_object(me, HIR "\n��ת��ʩչ�����������޷�����Ѹ�׽����У�\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if ( me->is_busy() ) {
                tell_object(me, HIR "\n�����ڶ����������޷�����ά��Ѹ�׽����ƣ�\n\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else if (!me->is_fighting() || !objectp(target)) {
                tell_object(me,  "\n������û�к��˹��У������ջ���Ѹ�׽��Ĺ��ơ�\n" NOR);
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        if( environment(target) != environment(me) ) {
                tell_object(me, "����Է��Ѿ������������ֹͣ��Ѹ�׽��Ĺ��ơ�\n");
                    call_out("xunlei_end", 6, me);
                delete_temp("xunlei", me);
                return;
        }
        else{
                addn_temp("apply/damage", damage*2, me);
                addn_temp("apply/attack", attack*2, me);

                if( query_temp("xunlei", me) == 4)message_combatd(HIY"\n$N�����ǰ��"+weapon->name()+HIY"��Ȼ���䵯��������ֱ��$n������֮������Ϊ�κν�����������\n"NOR,me,target);
                if( query_temp("xunlei", me) == 3)message_combatd(HIW"\n$N��ָ��"+weapon->name()+HIW"��һ�����������ˣ�����������"+weapon->name()+HIW"�������������������޷���\n"NOR,me,target);
                if( query_temp("xunlei", me) == 2)message_combatd(HIG"\n$N��Ȼ����һ����"+weapon->name()+HIG"�Ϻ����������ȵ�����"+target->name()+HIG"����С���ˣ���\n"NOR,me,target);
                if( query_temp("xunlei", me) == 1)message_combatd(HIR"\n����$N���ֻӽ���"+weapon->name()+HIR"������ǰ�����ң�˲Ϣ֮���ѹ���������һʮ���У�\n"NOR,me,target);
                addn("neili", -30, me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                addn_temp("apply/damage", -damage*2, me);
                addn_temp("apply/attack", -attack*2, me);
                if( query_temp("xunlei", me) == 1){
                        message_combatd(HIY "\n$N˳��Ȧת����"+weapon->name()+HIY"��һʮ���֡�Ѹ�׽�����Ȼ����ʹ����\n" NOR, me, weapon);
                        call_out("xunlei_end", 12, me);
                        me->start_busy(2);
                }
                else {
                        me->set_temp("xunlei_attack");
                        set_temp("xunlei",query_temp("xunlei",  me)-1, me);
                        call_out("checking", 1, me, target);
                }
        }
}

void xunlei_end(object me)
{
        object weapon;
        if ( !objectp( me ) )
                return;
        weapon=query_temp("weapon", me);

        tell_object(me, HIR "\n�㰵�Ե�Ϣ������ƽ����ӿ��������\n\n" NOR);

        delete_temp("xunlei", me);
        delete_temp("xunlei_yushi", me);

}
