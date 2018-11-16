// hit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, old_target;

        if( me->is_chatter() )
                return 0;

        if( query("no_fight", environment(me)) )
                return notify_fail("�����ֹս����\n");

        if( !arg || !objectp(obj = present(arg, environment(me))) )
                return notify_fail("���빥��˭��\n");

        if( !obj->is_character() )
                return notify_fail("�����һ�㣬�ǲ����������к��Ķ���\n");

        if( query_temp("apply/name", me) && playerp(obj) )
                return notify_fail("�㻹����ȡ����߰�!\n");

        if( !living(obj) )
                return notify_fail("�㻹Ҫ�򣿲���ɱ�����ˡ�\n");

        if( obj->is_fighting(me) )
                return notify_fail("���ͣ����ͣ����ͣ�\n");

        if( obj == me)
                return notify_fail("���Լ�������ô�벻����\n");

        if( query("age", obj) <= 17 && userp(obj) )
                return notify_fail("Ϊ����������ã��Ź�С���Ӱ�.\n");

        if( query("qi", me)<query("max_qi", me)*3/10 )
                return notify_fail("������û������ս���ˡ�\n");

        if( query("can_speak", obj) )
                message_vision("\n$N����$n���һ�������У�\n\n", me, obj);
        else
                message_vision("\n$N���һ������ʼ��$n����������\n\n", me, obj);

        notify_fail("���޴����֡�\n");
        switch( obj->accept_hit(me) )
        {
        case 0:
                return 0;
        case -1:
                return 1;
        default:
        }

        me->fight_ob(obj);
        if( query("can_speak", obj)){
                if( userp(obj) ) {
                        if( query("age", me)<18 )
                                me->want_kill(obj);
                        obj->fight_ob(me);
                        remove_call_out("do_hit");
                        call_out("do_hit", 1, me, obj);
                } else {
                        if( query("shen", obj)<-3000 )
                                obj->kill_ob(me);
                        else
                                obj->fight_ob(me);
                }
        } else
                obj->kill_ob(me);

        return 1;
}

void do_hit(object me, object obj)
{
        if( objectp(present(obj, environment(me))) ) {
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                COMBAT_D->do_attack(obj,me,query_temp("weapon", obj));
        }
        return;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : hit <����>

���ָ������ֱ����һ��������С���������ʽ��ս���Ǽ�ʱ�ģ�ֻҪ���һ
��������ս���ͻῪʼ��ֱ��ĳһ������50% ����Ϊֹ�����ָ�����Щ��
ϲ��fight��NPC�����ã���Ϊ�ܶ�ʱ����ı���Ҫ��ᱻ�ܾ�������ʹ�������
���п����⵽NPC ��ǿ�ҷ�Ӧ������ҪС��ʹ�á�

�������ָ��: fight, kill

HELP );
        return 1;
}

