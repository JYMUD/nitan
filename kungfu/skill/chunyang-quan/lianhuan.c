// Code of Shenzhou
///kungfu/skill/chunyang-quan/lianhuan.c ��������
// sdong 07/98
//
//����ʦ������(Sdong)��make lianhuan only add apply/attack
//����ʦ������(Sdong)��the style of qz perform should be high speed but not high damage
/*
**maco ������������Ӧ���ǽ����ȡ�**
��־ƽ��ƽ�̣�����������ͬʱ���Ⱥ�ɨ����������ȫ�����еġ������������С���־���������ţ��ӽ���������־ƽ�������֣������Է���ȥ���������١���һ����˫�������

������⼸��������ã��ѷǼ�֮��֪������������ȫ���亹���ۼ���־�����ڰ�գ�һ�����飬һ����ʵ������������Ҫ��������۹Ƕϡ���֪��־������������Σ���쳣֮�ʺ�Ȼ���з�������Ѱ�ɣ��������ɵ�����������
*/


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill;
        string weapon;
        int damage;
        string *limb, type, result, str;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");


        if( objectp(query_temp("weapon", me)) )
                return notify_fail("������������ֲ���ʩչ��\n");

        if( me->query_skill_mapped("cuff") != "chunyang-quan" )
                return notify_fail("�����õĲ��Ǵ���ȭ������ʩչ�������У�\n");

        if( me->query_skill_prepared("cuff") != "chunyang-quan" )
                return notify_fail("�������Ĳ��Ǵ���ȭ������ʩչ�������У�\n");

        if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("�����õĲ����������칦��ʩչ�����������У�\n");

        if( me->query_skill("force") < 140 )
                return notify_fail("����������칦���δ�����޷�ʩչ�������У�\n");

        if( me->query_skill("cuff") < 135 )
                return notify_fail("����������Ҫ��տ�Ĵ���ȭ������Чʩչ��\n");

        if( query("neili", me) <= 200 )
                return notify_fail("�����������ʹ���������У�\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("��ľ�������ʹ���������У�\n");


        message_vision(HIR "$Nŭ��һ�����վ�ȫ����ͻȻ����㹥��ȭ���ơ����������У�\n\n" NOR, me, target);

        skill = me->query_skill("strike")/2 + me->query_skill("cuff") / 8;
        if(skill>300)skill=300;
        addn_temp("apply/attack", skill, me);
        set_temp("lianhuan", 1, me);

        if( me->query_skill_prepared("strike") == "sanhua-juding" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("strike");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        if( query_temp("restore", me))me->prepare_skill("strike","sanhua-juding");
        if( me->query_skill_prepared("cuff") == "chunyang-quan" ) {
                set_temp("restore", 1, me);
                me->prepare_skill("cuff");
        }

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        if( query_temp("restore", me))me->prepare_skill("cuff","chunyang-quan");
        addn_temp("apply/attack", -skill, me);

        message_vision( "\n������$NͻȻ�ڿշ���ʹ��һ��ԧ�������ȣ����ȷ�۵糸��������$n\n",me,target);
        if( random(query("combat_exp", me))>query("combat_exp", target)/3 )
        {
                if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("cuff") + me->query_skill("force"))*2/3) )
                {
                        message_vision(HIR"ֻ��$Nһ���ҽУ����������������Ŀڡ�����$nһ������ͻȻƽƽ�ɳ����ڵ�һ�죬���������������֮�⣬ֱͦͦ�����ڵ��£���Ҳ������\n\n"NOR, target,target );
                        target->receive_wound("qi",query("qi", target)+1,me);
                        target->receive_damage("qi",query("qi", target)+1,me);
                        addn("neili", -query("jiali", me), me);
                        addn("jingli", -query("jiajin", me), me);
                }
                else
                {
                        damage=random((me->query_skill("cuff"))+query("jiali", me))*(1+random(query("jiajin", me)/5));
                        if(damage > 1500) damage = 1500;
                        if(damage < 300) damage = 300;
                        addn("neili", -query("jiali", me), me);
                        addn("jingli", -query("jiajin", me), me);

                        target->receive_damage("qi", damage,  me);
                        target->receive_wound("qi", (int)me->query_skill("strike"), me);

                        limb=query("limbs", target);
                        type = "����";
                        message_vision("ֻ��$Nһ���ҽУ���������������$P"+limb[random(sizeof(limb))]+"�������$P��ˤ�˸���ͷ��\n",target);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_vision("($N"+str+")\n", target);
                }
                me->start_busy(1+random(2));
        }
        else if( ( random( target->query_skill("dodge") ) >  me->query_skill("cuff")*2/3) && random(5) == 1 )
        {
                message_vision(HIR"$N�;��þ�����������֪�����æ���������$n���˸��գ��װ��Լ����ص���һ�ӡ�\n\n"NOR, target,me );
                me->receive_damage("qi", 30+random(50),  me);
                me->start_busy(1+random(3));
                str=COMBAT_D->status_msg(query("qi", me)*100/query("max_qi", me));
                message_vision("($N"+str+")\n", me);
        }
        else
        {
                message_vision( "$N�ۼ���һ���������ͣ�����˫��һ�㣬Ծ���ĳߣ��㿪��$n��һ�У�����Ҳ����һ���亹��\n\n" NOR,  target,me);
                me->start_busy(1);
        }

        delete_temp("lianhuan", me);

        addn("neili", -random(me->query_skill("cuff")/4)-100, me);
        addn("jingli", -100, me);
        me->start_busy( 1+random(2) );

        return 1;
}
