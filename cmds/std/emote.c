// emote.c (Mon  09-04-95)

#include <ansi.h>

inherit F_CLEAN_UP;
 
int main(object me, string str)
{
        string prefix;
        object env;
        mixed info;

        if (me->ban_say())
                return 0;

        env = environment(me);
        if( info=query("no_say", env) )
        {
                if (stringp(info))
                {
                        write(info);
                        return 1;
                }

                write("����ط���������������\n");
                return 1;
        }

        if( query("doing", me) == "scheme" )
        {
                if( query("jing", me)<100 )
                        return notify_fail("�����ڵľ��񲻼ã���һ����ɡ�\n");
                addn("jing", -50, me);
        }

        if (! str)
        {
                write(CYN"�㿴��������ḻ��\n"NOR);
                tell_room(env, CYN + (string)me->name()+
                          "����������ḻ��\n" + NOR, me);
                return 1;
        }

        prefix=query("env/no_prefix", me)?"":"~";
        write(CYN "��" + str + "\n" NOR);
        tell_room(env, CYN + prefix + (string)me->name() +
                  str + "\n" NOR, me);
        return 1;
}
 
int help(object me)
{
        write(@HELP
ָ���ʽ: emote <������>

���ָ�����������һ��ϵͳû��Ԥ��Ķ�����, ϵͳ�Ὣ��������
�����ּ��������������ʾ��������ͬһ���ط������￴��Ϊ�˱�����
������, ���������Ĵʾ�ǰ������ ~ �Թ�����

����: emote ����������
��ῴ��: ������������
�����˻ῴ��: ~��������������

����, ���Ӿ����������.

���ָ��: semote
HELP );
        return 1;
}