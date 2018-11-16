 // task.c

#include <ansi.h>
int main(object me, string str)
{
        string output;

        if( me->is_busy() )
                return notify_fail("��������æ��\n");

        if( !wizardp(me) && (time()-query_temp("last_tasks", me)<5) )
                return notify_fail("ϵͳ�������̾���������� ....\n");  

        if( query("jing", me)<2 )
                return notify_fail("�����ھ���״̬���ѣ����ǵȻ��ٲ�ɡ�\n");

        addn("jing", -2, me);

        if (str && str == "count")
        {
                tell_object(me,"��Ŀǰ�Ѿ������ЧTASKʹ��"+query("task/count", me)+"����\n");
                return 1;
        }

    output = HIR"�� "HIW"��̶"HIR" ��"HIG" TASK���� ʹ����\n" NOR; 
    output += ""HIW"��������������������������������������������������������������������������\n"NOR"";   
        output += TASK_D->task_list();   
    output += ""HIW"��������������������������������������������������������������������������\n\n"NOR"";   

        me->start_more(output);
        set_temp("last_tasks", time(), me);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: task
ָ���ʽ: task count �鿴�Լ��Ѿ����TASKʹ���ĸ�����
����ļ�: help tasks

���ָ����������֪Ŀǰ������ʹ��.

HELP
        );
        return 1;
}
