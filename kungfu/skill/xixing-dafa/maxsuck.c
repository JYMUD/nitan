// maxsuck.c
// Last Modified by winder on Apl. 10 2000

#include <ansi.h>

inherit F_SSERVER;
int exert(object me, object target)
{
        int sp, dp;
        int my_max, tg_max;

/*  if ( userp(me) && !wizardp(me) && 
  !query("perform/maxsuck", me) && 
  !query("can_perform/xixing-dafa/maxsuck", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("����ʹ�õ��ڹ���û�����ֹ��ܡ�");
*/
        if( !target || !target->is_character() || target == me )
         target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        if( !objectp(target) ||
                query("id", target) == "zhangmen" || 
                query("id", target) == "gongpingzi" || 
                query("id", target) == "jinren" || 
                query("id", target) == "muren" || 
                query("id", target) == "shiren" || 
                query("id", target) == "jiguanren" || 
                query("id", target) == "xiangpiren" || 
                query("id", target) == "dujiangshi" )
                return notify_fail("��Ҫ��ȡ˭�ĵ�Ԫ��\n");

        notify_fail("������Ҫץ���ˣ���ʲô���֣�\n");
        if (!userp(target) && !target->accept_hit(me)) return 0;

        if( query("race", target) != "����" )
                return notify_fail("����ˣ�ֻ���˲����е�Ԫ��\n");

        my_max=query("max_neili", me);
        tg_max=query("max_neili", target);

        if( query_temp("sucked", me) )
                return notify_fail("��ո���ȡ����Ԫ��\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʩ�����Ǵ����˵�Ԫ��\n");

        if( !me->is_fighting() || !target->is_fighting())

        if( (int)me->query_skill("xixing-dafa",1) < 90 )
                return notify_fail("������Ǵ󷨹���������������ȡ�Է��ĵ�Ԫ���\n");
        if( (int)me->query_skill("kuihua-xinfa",1) < 90 )
                return notify_fail("��Ŀ����ķ�������������ȡ���Ǵ󷨣�\n");

        if( query("neili", me)<20 )
                return notify_fail("�����������������ʹ�����Ǵ󷨡�\n");

        if( query("neili", me)>2*query("max_neili", me) )
                return notify_fail(HIR"��ֻ��ȫ�������Ҵ�������Ҫ������Ϣ�ˡ�\n"NOR);

        if( me->query_skill("force")<query("max_neili", me)/10 )
                return notify_fail("����ڹ�̫���ˣ�����ȡҲ��ͽ�͡�\n");

        if( query("max_neili", target)<100 )
                return notify_fail( target->name() +
                        "��Ԫ��ɢ������δ�ۣ����޷�����������ȡ�κζ�����\n");

        if( query("max_neili", target)<query("max_neili", me)/10 )
                return notify_fail( target->name() +
                        "���ڹ���ΪԶ�����㣬���޷�����������ȡ��Ԫ��\n");

        message_combatd(
                HIY"$N�ֱ��͵س�����ץ��$n�������ϡ�ͻȻ֮�䣬$n�;������ڹء�����ء�����Ѩ��������ԴԴ��й��\n\n" NOR, me, target );

        if( living(target) && !query_temp("noliving", target) )
        {
                if( !target->is_killing(me) ) target->kill_ob(me);
        }

        sp = me->query_skill("force") + me->query_skill("dodge");
        dp = target->query_skill("force") + target->query_skill("dodge");

        set_temp("sucked", 1, me);

        if (( random(sp) > random(dp) ) ||
                !living(target) || query_temp("noliving", target) )
        {
                tell_object(target, HIR"��ֻ���������ϡ��ڹء�����ء�����Ѩ�����翪��������ȱ�ڣ���ʱȫ��������к�����������ˮ���̣���Ҳ���Զ½أ�\n" NOR);
                tell_object(me, HIG"�����" + target->name() + "�ĵ�Ԫ������ԴԴ���������˽�����\n" NOR);

                addn("max_neili", -1*(1+(me->query_skill("xixing-dafa",1)-90)/5), target);
                addn("max_neili", 1*(1+(me->query_skill("xixing-dafa",1)-90)/5), me);
                if( query("max_neili", target)<1)set("max_neili", 0, target);

                addn("potential", 3, me);
                addn("combat_exp", 10, me);

                me->start_busy(7);
                target->start_busy(random(7));
                addn("neili", -10, me);

                call_out("del_sucked", 10, me);
        }
        else
        {        
                message_combatd(HIY"����$p������$P����ͼ�������͵�һ�𣬽������˿�ȥ��\n" NOR, me, target);
                me->start_busy(7);
                call_out("del_sucked", 20, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}

int help(object me)
{
        write(WHT"\n���Ǵ�֮��ȡ��Ԫ��"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                ��ȡ�Է���Ԫ
                ��ǿ�Լ���������

        ����Ҫ��
                �����ķ�90��
                ���Ǵ�90��
                ����20
HELP
        );
        return 1;
}
