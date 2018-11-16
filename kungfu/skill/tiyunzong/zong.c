// This program is a part of NITAN MudLIB
// zong.c

#include <ansi.h>

string name() { return "���־�"; }

void remove_effect(object me,int count);

int perform(object me, object target)
{
        int improve;

        if( (int)me->query_skill("tiyunzong",1) < 120 )
                return notify_fail("��������ݲ�����죬����ʹ�á����־�����\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 120 )
                return notify_fail("���̫���񹦵ȼ�����������ʹ�á����־�����\n");

        if (me->query_skill_mapped("force") != "taiji-shengong")
                return notify_fail("����ڹ����ԣ�����ʹ�á����־�����\n");

        if( (int)me->query_dex() < 28 )
                return notify_fail("�����̫�ͣ�����ʹ�á����־�����\n");

        if( (int)me->query_skill("dodge",1) < 120 )
                return notify_fail("��Ļ����Ṧ̫����屿׾������ʹ�á����־�����\n");

        if( query("neili", me)<600 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó������־�����\n");

        if (me->query_skill_mapped("dodge") != "tiyunzong")
                return notify_fail("�����ڼ�����������ʹ�á����־���������\n");

        if( query_temp("zong", me) )
                return notify_fail("������ʹ�������ݵ�������������־�����\n");

        message_combatd(HIY"$NͻȻ����һ������һ̧���͵İθ����ɣ����Ƹվ���˫�������߳���" +
                        "�������������������������������£�\n" NOR, me);

        improve = (int)me->query_skill("tiyunzong", 1);
        addn_temp("apply/defense", improve, me);
        set_temp("zong", improve, me);
        addn("neili", -(350-me->query_skill("tiyunzong",1)/10), me);
        call_out("remove_effect", improve/100, me, improve);
        return 1;
}

void remove_effect(object me, int count)
{
        int improve;
        if( !me ) return;
        if( !intp(improve=query_temp("zong", me)))return ;
        if( !me->is_fighting()
        ||  count < 1)
        {
                addn_temp("apply/defense", -improve, me);
                delete_temp("zong", me);
                tell_object(me, HIY"��ɢȥ�������۵������������������������������У��������ġ�\n"NOR);
                tell_room(environment(me), HIY + me->name()+"ȫ���ͷһ�����죬ɢȥ�˻���Ĺ�����\n"NOR,  ({ me }));
                return;
        }
        call_out("remove_effect", 1 , me ,count -1);
}

int help(object me)
{
        write(WHT"\n�����ݡ��ݡ��־���"NOR"\n");
        write(@HELP
        �䵱�Ṧ��������ν�������֣������Ṧ�޳����ң��ٵ�֮ʱʹ�����ݡ���
        ����������������������Լ����Ṧ��Ч�ȼ�������ʤ������ѻ��ʡ�

        Ҫ��  �����ݵȼ� 120 ���ϣ�
                ̫���񹦵ȼ� 120 ���ϣ�
                �����Ṧ�ȼ� 120 ���ϣ�
                ���� 600 ���ϣ�
                ������ 28 ���ϡ�
HELP
        );
        return 1;
}
