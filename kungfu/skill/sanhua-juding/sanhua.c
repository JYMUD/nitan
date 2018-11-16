//Cracked by Roath
//  /k  ungfu/skill/sanhua-juding/sanhua.c �����۶�
// sdong 07/98
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage,skill,wap,wdp;
        string *limb, type, result, str,msg;

        type = "����";

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("�����۶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("sanhua", me) )
                return notify_fail("������ʹ�������۶��ˣ�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("���ֲ���ʩչ�����۶���\n");

        if( me->query_skill_mapped("strike") != "sanhua-juding" )
                return notify_fail("�����õĲ��������۶��ƣ�����ʩչ�����۶���\n");

        if( me->query_skill_prepared("strike") != "sanhua-juding" )
                return notify_fail("�������Ĳ��������۶��ƣ�����ʩչ�����۶���\n");

        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("�����õĲ������칦��ʩչ���������۶���\n");

        if( me->query_skill("force") < 135 )
                return notify_fail("������칦���δ�����޷�ʩչ�����۶���\n");

        if( me->query_skill("strike") < 135 )
                return notify_fail("�����۶���Ҫ��տ�������۶��Ʒ�����Чʩչ��\n");

        if( query("neili", me) <= 300 )
                return notify_fail("�����������ʹ�������۶���\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("��ľ�������ʹ�������۶���\n");        
        if( query("jing", me) <= 200 )
                return notify_fail("��ľ�����ʹ�������۶���\n");


        msg = HIM"$N�����������칦�������鲼ȫ��ͷ��ð��˿˿��������Ȼ����������������������һ�ƣ�һ���������˳�һ����$nϮ����\n\n"NOR;
        message_vision(msg, me, target);

        set_temp("sanhua", 1, me);

        skill =  ( me->query_skill("sanhua-juding")
                + me->query_skill("force") ) / 2;

        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/damage", skill/6, me);
        addn_temp("apply/dodge", skill/2, me);
        addn_temp("apply/parry", skill/2, me);
        addn_temp("apply/defense", skill/2, me);

                weapon=query_temp("weapon", target);

                  if( objectp(weapon) )
                {
                        wap=query("force", me)/5
                        +query("sanhua-juding", me)/5
                        + (int)me->query_str()
                        +query("jiali", me);

                        wdp = (int)weapon->weight() / 500
                        +query("rigidity", weapon )
                        + (int)target->query_str()
                        +query("jiali", target )
                        + (int)target->query_skill("parry")/3;

                        wap = wap/2 + random(wap/2);

                        if( wap > 3 * wdp ) {
                                message_vision(HIY"ֻ��$N���ϵ�$n"+HIY+"�ѱ�һ����ϡ�\n"NOR, target, weapon);
                                weapon->unequip();
                                weapon->move(environment(target));
                                set("name", "�ϵ���"+query("name", weapon), weapon);
                                set("value", 0, weapon);
                                set("weapon_prop", 0, weapon);
                                target->reset_action();
                                addn("neili", -150, me);//tobreakweapontakesmoreneili

                        } else if( wap > 2 * wdp ) {
                                message_vision(HIW"$Nֻ��������" + weapon->name() + "��һ����ðѳֲ��������ַɳ���\n" NOR, target);
                                weapon->unequip();
                                weapon->move(environment(target));
                                target->reset_action();
                                addn("neili", -120, me);//tobreakweapontakesmoreneili

                        } else if( wap > wdp ) {
                                message_vision("$Nֻ��������" + weapon->name() + "һ����Щ���֣�\n", target);
                                addn("neili", -100, me);//tobreakweapontakesmoreneili
                        }
                }
                else{
                        addn_temp("apply/attack", skill/2, me);
                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        addn_temp("apply/attack", -skill/2, me);
                }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        addn("neili", -skill/2, me);
        addn("jingli", -100, me);
        addn("jing", -100, me);
        me->start_busy(random(2));

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/2 :), skill/15);

        return 1;
}

private int remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/damage", -amount/3, me);
        addn_temp("apply/parry", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        addn_temp("apply/defense", -amount, me);
        delete_temp("sanhua", me);
        message_vision(
        HIY "\n$N����һ�������������ջص��\n\n" NOR, me);

        return 0;
}