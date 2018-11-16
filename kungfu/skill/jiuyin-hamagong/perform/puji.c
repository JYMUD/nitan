// perform ����˻�

#include <ansi.h>
#include <armor.h>
#include <combat.h>

inherit F_SSERVER;
//void tie_result(object me, object target);
void tie_hit(object me, object target);
void pu_hit(object me, object target);

int perform(object me, object target)
{
        object armor,weapon;
        int damage;
        string *limb, type, result, str;


        type = "����";

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
        return notify_fail("�㲻��ս���У�����ʹ���Ļ���\n");

        if( userp(me) && !query("can_perform/jiuyin-hamagong/puji", me) )
                      return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n"); 

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("���ֱֳ������޷�ʩչ��󡹦���Ʒ�������\n");

        if( (int)me->query_skill("jiuyin-hamagong", 1) < 320 )
                return notify_fail("��ĸ�󡹦��Ϊ������\n");

        if ( me->query_skill_mapped("force") != "jiuyin-hamagong")
                return notify_fail("��������ʹ���ڹ����Ǹ�󡹦��\n");

        if (me->query_skill_mapped("unarmed") != "jiuyin-hamagong")
                return notify_fail("��û��׼��������󡹦������ʹ�á��˻�����\n");
        if( query("neili", me) <= 1000 )
                return notify_fail("�������������\n");

        if( query("jingli", me) <= 500 )
                return notify_fail("��ľ���������\n");

        delete_temp("puji_time", me);
        remove_call_out("pu_hit");
        pu_hit(me, target);

        return 1;
}

void pu_hit(object me, object target)
{
        object armor;
        int damage, time, ap, dp, pp, fap, hmg, force;
        string msg, *limb, type, result, str;
        object weapon;

        if( !target || !me->is_fighting(target) ) return;

        if( !living(me) || me->is_ghost() ) return;

        if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

        if( me->query_skill_mapped("force") != "jiuyin-hamagong" || me->query_skill_mapped("unarmed") != "jiuyin-hamagong") return;

        type = "����";

        hmg = (int)me->query_skill("jiuyin-hamagong", 1);
        force = (int)me->query_skill("force", 1);

        ap = COMBAT_D->skill_power(me, "unarmed", SKILL_USAGE_ATTACK);
        if( ap < 1 ) ap = 1;
        ap = ap*(1+time);

        dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);
        if( dp < 1 ) dp = 1;
        
        pp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);
        if( pp < 1 ) pp = 1;

        addn_temp("puji_time", 1, me);
        time=query_temp("puji_time", me);

        if( time == 1 ) msg = HIB "\n$N˫��һ�䣬�������������󡱵�һ����У������󡹦������˫���뷢����ǰ�Ƴ�����һ\n"
                                  "��ʵ��$P��������֮���ۣ�$n��Ȼ���ܵ�ɽ�麣Х��ľ���Ϯ����\n" NOR;
        else if( time == 2 ) msg = HIM "\n$N��һ�Ƹ��꣬�ڶ�������Ѹ���쳣�ĸϵ���ǰ��δ˥���󾢼������Ʒ�Խ�����ҡ�\n" NOR;
        else msg = HIR "\n$N�ۿ�ǰ����գ�ȴ���޻��ң�˳������һ�ƣ���"+chinese_number(time)+"�Ƶ��Ʒ�����ɳĮ�籩��һ���͹�һ�󣬺�Х����$n������\n"NOR;

        message_vision(msg , me,target);
        
        addn("neili", -hmg*2, me);
        addn("jingli", -hmg/2, me);

        fap = random(ap + dp);

        if( living(target) && fap < dp ) {

                if(time == 1) message_vision(HIY "$n�ۼ���һ���������ͣ����Ȳ��ܣ����ֲ��ɣ�����˫��һ�㣬Ծ���ĳߣ��㿪����һ�ơ�\nֻ�������ڵ�һ�����죬$N��һ�Ƶľ�������һ�ɿ����ˣ���ʱ����������˾������ѡ�\n\n" NOR, me, target);
        
                else message_vision(HIY "$n�ۼ���һ���������ڣ�����˫��һ�㣬��Ծ���ߣ��ֶ㿪����һ�ơ�\nֻ�����һ�����죬��󡹦�;����û�������������һƬ����������ƾ��ˡ�\n" NOR, me, target);
                target->start_busy(2);
                me->start_busy(5);
                if( me->query_skill("unarmed") > time*150 && time < 5)
                        call_out("pu_hit",2+random(2),me,target);
        }

        else if( random(ap+pp)<pp && random(5) == 0 && query("race", target) == "����" )
        {
                weapon=query_temp("weapon", target);
                if(weapon)
                {
                        weapon->unequip();
                        weapon->move(environment(target));
                        target->reset_action();
                        message_vision(HIR"$N�;��þ�����������֪�������"NOR + weapon->name() + HIR"���ַɳ����Ͻ�Ҳ��˫����ǰƽ�ơ���һ������Ӳ��Ӳ��ɲ��֮�䣬�����ﾹȻ��ס������\n"NOR, target );
                }
                else message_vision(HIR"$N�;�������������֪���Ҳ��˫����ǰƽ�ơ���һ������Ӳ��Ӳ��ɲ��֮�䣬�����ﾹȻ��ס������\n\n"NOR, target );

                message("vision", HIW BLK"���˱��Ǻ��ݺ��ܡ��������Ĳ�����ͻȻ�������߽�ʬ���ƣ�����ָҲ����һ�����ƺ���Ҳ����һ�ڡ�\n\n"NOR, environment(me), ({ me, target }) );

                addn("neili", -hmg, target);
                addn("jingli", -hmg, target);
                target->start_busy(3+random(2));
                me->start_busy(2+random(2));
                remove_call_out("tie_hit");
                call_out("tie_hit",3+random(2),me,target);
        }

        else {
                if( query_temp("armor/cloth", target) )
                        armor=query_temp("armor/cloth", target);

                if( (!living(target) || (!armor || (armor && query("armor_prop/armor", armor)<150))) && 
                    ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("unarmed") + 
                         random(me->query_skill("force"))*2/3)) && 
                     query("race", target) == "����" && 
                     random(2) == 1 &&
                     !query("no_nuoyi", target) )
                {
                        message_vision(HIR"ֻ��$Nһ���ҽУ���һ������С��������$nһ������ͻȻƽƽ�ɳ����ڵ�һ�죬���������������֮�⣬ֱͦͦ�����ڵ��£���Ҳ������\n\n"NOR, target,target );
                        target->receive_wound("qi",query("eff_qi", target),me);
                        target->receive_damage("qi",query("qi", target)+1,me);
                        addn("neili", -(query("jiali", me)+hmg/2), me);
                        addn("jingli", -(query("jiali", me)/2), me);
                }
                else
                {


            damage=(query("jiali", me)+query("age", me))*me->query_skill("force")/30+(random(hmg)+force)*time+query_temp("apply/damage", me);

                        if(damage > me->query_skill("unarmed")*(5+time) ) damage = me->query_skill("unarmed")*(5+time);
                        if(damage < me->query_skill("unarmed")*(1+time) ) damage = me->query_skill("unarmed")*(1+time);
                        addn("neili", -(query("jiali", me)+hmg), me);
                        addn("jingli", -(query("jiali", me)/2), me);

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", damage/2, me);

                        target->start_busy(1+random(3));
                        me->start_busy(5); 

                        limb=query("limbs", target);

                        if(random(2) ) type = "����";
                        result = COMBAT_D->damage_msg(damage, type);
                        result = replace_string( result, "$l", limb[random(sizeof(limb))]);
                        result = replace_string( result, "$p", target->name() );
                        message_vision(result, me, target);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_vision("( $N"+str+" )\n", target);
                        if(wizardp(me)) tell_object(me, "puji damage: "+damage+"\n");
                }
        }

        me->start_busy(4+random(3));
}

void tie_hit(object me, object target)
{
        int sum, n1, n2;
        string msg;

        if( !target || !me->is_fighting(target) ) return;

        if( !living(me) || me->is_ghost() ) return;

        if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

        sum = me->query_skill("force") + me->query_skill("unarmed") + target->query_skill("force") + target->query_skill("parry");
        n1=query("neili", me);
        n2=query("neili", target);

        addn("neili", -100*sum/(me->query_skill("force")+me->query_skill("unarmed")), me);
        if( query("neili", me)<0)set("neili", 0, me);

        addn("neili", -150*sum/(target->query_skill("force")+target->query_skill("parry")), target);
        if( query("neili", target)<0)set("neili", 0, target);

        if( n1 > 3000 && n2 > 3000) {
                msg = WHT"��ʱ˫����������ǿ��������ʤ������ʹ�Է��ش����ɡ�\n"NOR;

                if( n1 > n2 )
                msg += HIW"�����ֽ���һ�ᣬ$nͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n"NOR;
                else msg += HIW"�����ֽ���һ�ᣬ$Nͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n"NOR;
        }

        else {

                if( n1 > n2 ) msg = WHT"$N���ϴ߶���󡹦�;�������˥�Ǽ����Թ�Ƭ�̣�$n����ȫ������졣\n"NOR;
                else msg = WHT"$N���Ϻ�����ʢ������󡹦���ӵ��˼��¡��Թ�Ƭ�̣�$N����ȫ������졣$n�ƺ���Ȼ����ʮ�㣬ͷ�������������ϡ�\n"NOR;
                }

        message_vision(msg , me,target );


        if( query("neili", me)>0 && query("neili", target)>0 && me->is_busy() && target->is_busy() && living(me) && living(target) )
        {
                target->start_busy(3+random(2));
                me->start_busy(3+random(2));
                remove_call_out("tie_hit");
                call_out("tie_hit",2+random(2), me,target);
                return;
        }

        if( query("neili", target) <= 0 )
        {
                message_vision(HIR "\n$NͻȻ������������ȫ������ԭ��������ȫ���ľ���ͻ��ǰ��һƬ����֮�����ѱ�������󡹦һ�ƻ��У���Ҳ�߲���һ����������������˫�۽��գ������ֽ���˵����������ϡ�\n\n" NOR, target);
                target->receive_wound("qi",query("eff_qi", target),me);
                target->receive_damage("qi",query("eff_qi", target)+1,me);
                return;
        }

        if( query("neili", me) <= 0 )
        {
                message_vision(HIR "\n$N���Ϻ���������ͻȻ������������ȫ������ԭ��������ȫ���ľ�����󡹦��ʱȫ����������������ǰ��һƬ����֮������Ҳ�߲���һ�������������˫�۽��գ������ī���˵����������ϡ�\n\n" NOR, me);
                me->receive_wound("qi",query("eff_qi", me),target);
                me->receive_damage("qi",query("eff_qi", me)+1,target);
        }

//      remove_call_out("tie_result");
//      call_out("tie_result",1,me,target);
}
