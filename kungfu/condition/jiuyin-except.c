// qiankun-except.c

#include <ansi.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int limit;

        if (! living(me) && (me->query("eff_qi") < 100 || me->query("eff_jing") < 50))
        {
                me->set_temp("die_reason", "��Ϊǿ������������ķ����߻���ħ����");
                me->die();
                return 0;
        } else
        {
                me->receive_wound("qi", 100);
                me->receive_wound("jing", 50);
                tell_object(me, HIR "����õ��������䣬��������ȴ"
                            "������һ������֮����\n" NOR);
                message("vision", me->name() + "��ɫ������죬ǿ�����˹�������\n",
                        environment(me), me);
        }

        return 1;
}
