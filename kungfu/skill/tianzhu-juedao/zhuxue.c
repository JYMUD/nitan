/*
�������϶Է������Ĺ��������perform������������Ϊ�˱��ֶ��¾Ž���
��һ����ĵ�һ��λ���صضԷ�����һ�������������ڳ�����������������
ϣ���Ժ����ʦ��Ҫ������Щ�趨���Ͼ���weapon�书�У����ܳ�Խlonely-sword�ĵ�λ��
*/

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2,target,*inv;
        int skill, ap, dp, neili_wound, qi_wound,equip,skill1;
        int damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill  = me->query_skill("tianzhu-juedao",1);
        skill1 = me->query_skill("shaolin-xinfa",1);


        if( !(me->is_fighting() ))
            return notify_fail("��"+HIR"��ѩ����"NOR+"��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
            return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("buddhism",1) < 220)
                return notify_fail("�����Ϊ���㣬����ʹ�á�"+HIR"��ѩ����"NOR+"����\n");

        if( skill < 150)
            return notify_fail("������þ����ȼ�����, ����ʹ�á�"+HIR"��ѩ����"NOR+"����\n");
        if(me->query_skill("shaolin-xinfa",1)<150)
            return notify_fail("��������ķ��ȼ�����, ����ʹ�á�"+HIR"��ѩ����"NOR+"����\n");
 
        if( query("neili", me)<400 )
            return notify_fail("��������������޷����á�"+HIR"��ѩ����"NOR+"����\n");

        msg = HIY "$N����Ծ��,ʹ��"+HIR"����ѩ���ա�"NOR+""+HIY"������"NOR""+weapon->name()+ 
              NOR+HIY"�Ӱ���лӵ�ֱ��������\n��������������ߣ��������ǳ�ɳ����ܲ���Ҷ��"
              "���缤�����Ŷ��裬\n��$n�Ӷ��˱ܵĿ�϶�������ʵʵ��\n"NOR;
        message_vision(msg, me, target);

        ap = random(me->query_skill("blade") + skill);
        dp = target->query_skill("dodge")/2;
        damage = ap / 2 + random(ap / 2);

        if( dp < 10 )
            dp = 10;
        if( random(ap) > dp )
        {
            if(userp(me))
                 addn("neili", -250, me);
            msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60, 
                                       HIC"$n���޿ɱ�,ֻ��һ�ɸ���֮���ľ������������ʹ��ֱ����Ϣ��\n"
                                       "$n�������˸�����ȴֻ��"NOR""+weapon->name()+""HIC"����һ����"
                                       "����ͣϢ��һ���������š�\n"NOR); 

            me->start_busy(2+random(2)); 

       if( query("str", me) >= 20
        && objectp(weapon2=query_temp("weapon", target) )
       && me->query_str() >= 45                              
        && query("max_neili", me)>2500
        && !query("betrayer", me )
       && skill > 200                                           
       && skill1 > 200      
        && !query("no_drop", weapon2 )
        && !query("no_get", weapon2 )
        && !query("no_put", weapon2 )
        && !query("no_beg", weapon2 )
        && !query("no_steal", weapon2 )
        && !query("no_give", weapon2 )
       && random(2) == 1)        
       {
                inv = all_inventory(target);
                for(equip=0; equip<sizeof(inv); equip++)
                {
                          if( query("weapon_prop", inv[equip]) && (query("equipped", inv[equip]) == "wielded") )

                          {
                                 msg += HIW "$N����δ�������е��Ʋ���������$n����"NOR+
                                 query("name", inv[equip])+HIW"һ�����ϡ�\nֻ������һ"
                                 "����$n���ϵ�"NOR+query("name", inv[equip])+HIW"��"
                                 "���������룬�����˵��ϣ�\n"NOR;
                                  message_vision(msg, me,target);

                                  inv[equip]->unwield();
                                  inv[equip]->reset_action();
                                  inv[equip]->move(environment(target));
                                  set("name", "�ϵ���"+query("name", inv[equip]), inv[equip]);
                                  set("value", 0, inv[equip]);
                                  set("weapon_prop", 0, inv[equip]);
                                  set("long", "һ���������������жϿ����ƿ����룬�����Ǳ�����һ�������ġ�\n", inv[equip]);
                        }
                }

                return 1;
        }
        }
        else
        {
            if(userp(me))
                 addn("neili", -100, me);
            msg = HIW"����$n�������Ա�һ��,�չ���$N���ɱ��һ����\n"NOR;
            me->start_busy(2+random(2));
        }
        message_combatd(msg, me, target);

        return 1;
}

