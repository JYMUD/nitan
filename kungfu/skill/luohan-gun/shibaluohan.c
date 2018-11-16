// luohan-gun perform �޺�����

#include <ansi.h>

#define SHIBA HIY "��ʮ���޺�����" NOR

#define ME  "�����ڲ���ʹ��" + SHIBA + "��\n"
#define TAR  "�Է����ڲ���ʹ��" + SHIBA + "��\n"

int check_fight(object me, object target, int amount);
private int remove_effect(object me, object target, int amount);

int perform(object me, object target)
{
        object *enemy;
        int i,j,k,amount;
        object wep1, wep2;
        wep1=query_temp("weapon", me);

        if( !target || target == me) return notify_fail("��Ҫ��˭��ɹ���?\n");

        if( query_temp("gunzhen", me))return notify_fail(ME);
        if( query_temp("gunzhen", target))return notify_fail(TAR);
        if( query("jingli", me)<200)return notify_fail(ME);
        if( query("jingli", target)<200)return notify_fail(TAR);
        if( query("neili", me)<1500)return notify_fail(ME);
        if( query("neili", target)<1500)return notify_fail(TAR);
        if (!me->is_fighting()) return notify_fail( SHIBA "ֻ����ս����ʹ�á�\n");
        if (me->is_fighting(target)) return notify_fail("���Ѿ��ںͶԷ���ܣ�ʹ��" + SHIBA + "��ʲô?\n");
        if( (int)me->query_skill("luohan-gun", 1) < 120 ) return notify_fail(ME);
        if( (int)me->query_skill("club", 1) < 120 ) return notify_fail(ME);
        if( !wep1 || query("skill_type", wep1) != "club"
        || me->query_skill_mapped("club") != "luohan-gun")
                return notify_fail(ME);
        
        enemy = me->query_enemy();
        k = sizeof(enemy);
        while (k--)
        if (target->is_fighting(enemy[k])) break;
        if (k<0) return notify_fail(target->name()+"��û�к���Ķ����ڽ�ս��\n");

        if( (int)target->query_skill("luohan-gun", 1) < 120 )
                return notify_fail(TAR);
        if( (int)target->query_skill("club", 1) < 120 )
                return notify_fail(TAR);
        wep2=query_temp("weapon", target);
        if( target->is_busy() || !wep2 || query("skill_type", wep2) != "club"
        || target->query_skill_mapped("club") != "luohan-gun")
                return notify_fail(TAR);
                
        message_vision(HIY "\nֻ�����Ǽ��ˣ�����Э���������Ͻ�������һ�壬"+
                           "һ��һʽ�����Ʒ���ͬһ�ˣ�����������"+
                           "$n���ɿ��Ĵ���......\n" NOR, me, target);
        set_temp("gunzhen", 1, me);
        set_temp("bunzhen", 1, target);
        me->receive_damage("jingli", 100);
        target->receive_damage("jingli", 100);
        me->receive_damage("neili", 300);
        target->receive_damage("neili", 300);
        me->start_busy(1);
        target->start_busy(1);
        i = (int)me->query_skill("luohan-gun", 1);
        j = (int)target->query_skill("luohan-gun", 1);
        amount = ((i + j)/10 + (int)me->query_str() + (int)target->query_str())/5;
        if( amount > 20 ) amount = 20;
        addn_temp("apply/dex", amount, me);
        addn_temp("apply/str", amount, me);
        addn_temp("apply/dex", amount, target);
        addn_temp("apply/str", amount, target);
        enemy[k]->start_busy(amount/3);
        check_fight(me, target, amount);
        return 1;
}

int check_fight(object me, object target, int amount)
{  
        object wep1, wep2;
        if(!me && !target) return 0;
        if(!me && target){
           addn_temp("apply/dex", -amount, target);
           addn_temp("apply/str", -amount, target);
           delete_temp("gunzhen", target);
           return 0;
        }
        if( me && !target){
           addn_temp("apply/dex", -amount, me);
           addn_temp("apply/str", -amount, me);
           delete_temp("gunzhen", me);
           return 0;
        }
        wep1=query_temp("weapon", me);
        wep2=query_temp("weapon", target);
        if(!me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep1
         || !target->is_fighting()
         || !living(target)
         || target->is_ghost() 
         || !wep2
         || me->query_skill_mapped("club") != "luohan-gun" 
         || target->query_skill_mapped("club") != "luohan-gun"
         || environment(me) != environment(target))
              remove_effect(me, target, amount);
        else {
              call_out("check_fight", 1, me, target, amount);
        }
        return 1;
}

private int remove_effect(object me, object target, int amount)
{
        if(living(me)
         && !me->is_ghost()
         && living(target)
         && !target->is_ghost())
           message_vision(HIY "\n��ɮ�ڽ���ʩչ��ϣ��������С�\n" NOR, me, target);

        addn_temp("apply/dex", -amount, me);
        addn_temp("apply/str", -amount, me);
        addn_temp("apply/dex", -amount, target);
        addn_temp("apply/str", -amount, target);
        delete_temp("gunzhen", me);
        delete_temp("gunzhen", target);
        return 0;
}