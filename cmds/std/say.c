// say.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;
        mixed msg;

        if (me->ban_say(0))
                return 0;

        env = environment(me);
        if (! arg)
        {
                write("���������ﲻ֪����˵Щʲô��\n");
                message("sound", me->name() + "�������ﲻ֪����˵Щʲô��\n",
                        env, me);
                return 1;
        }

        if( msg=query("no_say", env) )
        {
                if (stringp(msg))
                {
                        write(msg);
                        return 1;
                }

                write("����ط����ܽ�����\n");
                return 1;
        }

        if( query("doing", me) == "scheme" )
        {
                if( query("jing", me)<100 )
                        return notify_fail("�����ڵľ��񲻼ã���һ����ɡ�\n");
                addn("jing", -50, me);
        }

        write(CYN "��˵����" + arg + "\n" NOR);
        message("sound", CYN + me->name() + "[" + capitalize(query("id", me))+ "]" + CYN "˵����" +  arg + "\n" NOR,
                env, me);

        // The mudlib interface of say
        all_inventory(env)->relay_say(me, arg);
        me->add_msg_log("say", "��˵��: "HIG+arg+NOR"\n");
        (all_inventory(env)-({ me }))->add_msg_log("say", me->query_idname()+"˵��: "HIG+arg+NOR"\n");

        me->ban_say(1);

        return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: say <ѶϢ>
 
˵�������и�����ͬһ��������˶���������˵�Ļ��������������
auto_say��������ôϵͳ���Զ��Ľ�������ķ�����ͱ��鶯����Ϊ
�㽲�Ļ����������������pure_say��������ô������������ '/'
�ַ���ͷ���������ϵͳ����������˵�Ļ�������
 
ע: ��ָ����� ' ȡ��.
 
HELP
        );
        return 1;
}
