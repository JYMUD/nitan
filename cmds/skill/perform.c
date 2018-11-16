// perform.c

#include <ansi.h>

inherit F_CLEAN_UP;

protected int do_perform(object me, string arg);

int main(object me, string arg)
{
        string and;
        int result;
        int busy;
        int lvl;
        string msg;
        string *fams;

        seteuid(getuid());

        if (me->is_busy())
                return notify_fail("( ����һ��������û����ɣ�����ʩ���⹦��)\n");

        if (! arg) return notify_fail("��Ҫ���⹦��ʲ�᣿\n");

        if (query_temp("forget", me)) 
                return notify_fail(HIR "�㷢���Լ������˾������ʹ�á�\n" NOR);

        if (me->query_condition("no_perform"))
                return notify_fail(HIR "��ֻ��ȫ���������ƻ�ɢ��һ�㣬ȫȻ�޷����ơ�\n" NOR);

        if (query_temp("freeze", me) && time()-query_temp("last_perform_time", me) < 1)
                return notify_fail(HIR "�㴦�ڱ���������״̬�£������������޷���˿�������ʹ�þ��С�\n" NOR);

        if (sscanf(arg, "%s and %s", arg, and) == 2 ||
            sscanf(arg, "%s twice", arg) == 1 && (and = arg))
        {
                lvl = me->query_skill("zuoyou-hubo", 1);
                if (! lvl)
                        return notify_fail("��Ҫ��ʲô����Ϊ�Լ�����ͷ���۰���\n");

                if( me->query_skill("count",1) && !query("special_skill/capture", me) )
                        return notify_fail("����ѧ̫�࣬��ͷ���ң����Է��Ķ��á�\n");

                if (lvl <= 100)
                        return notify_fail("������һ�����Ϊ̫ǳ�����Է��Ķ��á�\n");

                if( query("int", me)>24 && query("int", me)<40 )
                        return notify_fail("����ͼ���Ķ��ã������־��ǲ���ʹ����\n");

                if( (!arrayp(fams = query("reborn/fams", me)) || 
                    (member_array("ȫ���", fams) == -1 &&
                    member_array("��Ĺ��", fams) == -1)) && 
                    (! me->query_family() ||
                    ( me->query_family() != "ȫ���" &&
                      me->query_family() != "��Ĺ��" )))
                        return notify_fail("����ͼ���Ķ��ã������־��ǲ���ʹ����\n");

                if (! me->is_fighting())
                        return notify_fail("ֻ��ս���в���ʩչ���һ�����\n");

                if (lvl < 360 && random(lvl) < 100)
                {
                        me->start_busy(1);
                        write("����ͼ���Ķ��ã������־��ǲ���ʹ����\n");
                        return 1;
                }
        }

        if (and) set_temp("use_hubo", 1, me);

        result = do_perform(me, arg);
        if (! and)
                return result;

        if (! result)
                write(query_notify_fail());
        else
        {
                switch (random(4))
                {
                case 0:
                        msg = HIY "$N" HIY "���һ����˫�ַ�"
                              "ʹ���У�һ�𹥳���\n" NOR;
                        break;

                case 1:
                        msg = HIY "$N" HIY "˫���������ʹ��"
                              "ͬ��ʽ�������ۻ����ҡ�\n" NOR;
                        break;

                case 2:
                        msg = HIY "$N" HIY "�����ַ�ʹ���У�"
                              "����ͣ�ͣ���������ͬʱ������\n" NOR;
                        break;

                case 3:
                        msg = HIY "$N" HIY "����һ�У�����һ"
                              "�У�������·���죬�������Ե͵���\n" NOR;
                        break;
                }

                message_combatd(msg, me);
        }

        busy = me->query_busy();
        me->interrupt_busy(0);

        result = do_perform(me, and);
        if (! result)
                write(query_notify_fail());

        if (intp(busy) && intp(me->query_busy()) &&
            busy > me->query_busy())
        {
                me->interrupt_busy(0);
                me->start_busy();
        }
        delete_temp("use_hubo", me);
        return 1;
}

protected int do_perform(object me, string arg)
{
        object weapon;
        string martial, skill;
        int result;

        if (sscanf(arg, "%s.%s", martial, arg) != 2)
        {
                if( weapon=query_temp("weapon", me) )
                        martial=query("skill_type", weapon);
                else
                        martial = "unarmed";
        }

        me->clean_up_enemy();
        if (stringp(skill = me->query_skill_mapped(martial)))
        {
                notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
                if (SKILL_D(skill)->perform_action(me, arg))
                {
                        set_temp("last_perform_time", time(), me);
                        if (random(120) < (int)me->query_skill(skill))
                                me->improve_skill(skill, 1, 1);
                        return 1;
                } else
                if (SKILL_D(martial)->perform_action(me, arg))
                {
                        set_temp("last_perform_time", time(), me);
                        if (random(120) < (int)me->query_skill(martial, 1))
                                me->improve_skill(martial, 1, 1);
                        return 1;
                }
                return 0;
        }

        return notify_fail("�����ڵ�" + to_chinese(martial)[4..7] +
                           "(" + martial + ")�в�û�������⹦��\n");
}

int help (object me)
{
        write(@HELP
ָ���ʽ��perform | yong [<�书����>.]<��ʽ����> [<ʩ�ö���>]
          perform | yong ��ʽ1 [<����1>] and ��ʽ2 [<����2>]
          perform | yong ��ʽ1 [<����1>] twice

�������ѧ���⹦(ȭ�š�����������....)��һЩ����Ĺ�����ʽ��
��ʽ�����������ָ����ʹ�ã���������� enable ָ��ָ����ʹ��
���书����ָ���书����ʱ�����ֵ��⹦��ָ���ȭ�Ź���ʹ����
��ʱ���Ǳ��е��书��

��������⹦�������಻ͬ��������ʽ������ͬ�ģ����߲����ȭ��
���������ܵ��书(���Ṧ)�������� <�书>.<��ʽ>  �ķ�ʽָ����
�磺

perform sword.chan

���仰˵��ֻҪ�� enable �е��书��������ʽ�ģ������������ָ
��ʹ�á�

����㾫ͨ���һ���������ͬʱʹ��������ʽ����ͬһ���ֻ���ֱ�
�������ˡ����һ���������Խ�Ǿ����ɹ���Խ�ߡ�

ʹ�� twice ������ʾ������ʹ��ͬ������ʽ��
HELP );
        return 1;
}
