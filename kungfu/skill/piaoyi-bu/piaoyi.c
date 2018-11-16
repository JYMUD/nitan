// piaoyi.c Ʈ�ݲ��� ����Ʈ��

#include <ansi.h>
#include <combat.h> 

#define PIAOYI HIG "������Ʈ�ݡ�" NOR 

inherit F_SSERVER;

void remove_effect(object me, int aamount, int damount);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int d_count, count, qi, maxqi, skill;

        if( query_temp("piaoyi", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        if ( userp(me) 
         && me->query_skill("piaoyi-bu", 1) < 150
          && !query("can_perform/piaoyi-bu/piaoyi", me) )
                return notify_fail( "����ʹ�õ��⹦��û�������Ĺ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail( PIAOYI + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʩչ" + PIAOYI + "��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ����������ʹ��" + PIAOYI + "��\n");

        if ((int)me->query_skill("dodge") < 150)
                return notify_fail("��Ļ����Ṧ�������ң��޷�ʹ��" + PIAOYI + "��\n");

        if (me->query_skill_mapped("dodge") != "piaoyi-bu") 
                return notify_fail("��û�м���Ʈ�ݲ������޷�ʹ��" + PIAOYI + "��\n");

        msg = HIG "$N" HIG "�߶��Լ��������˾���˫�ȣ�ʹ��Ʈ�ݲ����ľ���" + 
              PIAOYI + HIG "�����ζ�ʱ������һ�㣡\n" NOR;
        
        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = (int) (me->query_skill("piaoyi-bu", 1) / 3);
        count = (int)me->query_skill("dodge",1) / 4;
        d_count = (int)me->query_skill("parry",1) / 2;

        if (qi > (maxqi * 0.4))
        {       
                message_combatd(msg, me, target);
                
                addn_temp("apply/dodge", count*2, me);
                addn_temp("apply/parry", -d_count, me);
                set_temp("piaoyi", 1, me);
                me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 2, d_count :), skill);
                addn("neili", -500, me);
        } else
        {
                msg = HIR "$N" HIR "ȫ���߶���������ͼ���Լ��������ƶ���ߵ�����"
                      ", ˫�ȹ���һ���죡\n" NOR;
                msg = HIR "$N" HIR "�����Լ��߶���������˫�ȵľ����������, ��Ҳվ����ס, һͷ�Ե��ڵأ�\n" NOR;
                message_combatd(msg, me, target);
                set("neili", 0, me);
                addn("max_neili", -10, me);

                me->unconcious();
        }
        return 1;
}

void remove_effect(object me, int aamount, int damount)
{
        if( query_temp("piaoyi", me) )
        {
                addn_temp("apply/dodge", -aamount, me);
                addn_temp("apply/parry", damount, me);
                delete_temp("piaoyi", me);
                tell_object(me, HIG "���" + PIAOYI + HIG "�˹���ϣ�˫��һ�����顣\n");
        }
}