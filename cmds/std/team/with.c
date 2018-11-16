// team command: with

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;

        if (! arg ||
            ! (ob = present(arg, environment(me))) ||
            ! living(ob) ||
            ! ob->is_character() ||
            ob == me)
                return notify_fail("�����˭��Ϊ��飿\n");

        if (! pointerp(me->query_team()) || me->is_team_leader())
        {
                if (sizeof(me->query_team()) >= 12)
                        return notify_fail("����������������ʵ����̫��"
                                           "�ˣ���Ҷ��չ˲������ˡ�\n");

                if( me == query_temp("pending/team", ob) )
                {
                        if (! pointerp(me->query_team()))
                        {
                                ob->add_team_member(me);
                                message_vision("$N��������$n�Ķ��顣\n", me, ob);
                                MYGIFT_D->check_mygift(me, "newbie_mygift/zudui"); 
                                MYGIFT_D->check_mygift(ob, "newbie_mygift/zudui"); 
                        } else
                        {
                                me->add_team_member(ob);
                                message_vision("$N������$n������顣\n", me, ob);
                                MYGIFT_D->check_mygift(me, "newbie_mygift/zudui"); 
                                MYGIFT_D->check_mygift(ob, "newbie_mygift/zudui"); 
                        }
                        delete_temp("pending/team", ob);
                        return 1;
                } else
                {
                        /*
                        if( query("level", ob)<query("level", me)-10 || 
                            query("level", ob)>query("level", me)+10 )
                                return notify_fail("���ǵĽ�ɫ�ȼ����ϴ��޷���ӡ�\n");
                        */
                                
                        message_vision("$N����$n����$P�Ķ��顣\n", me, ob);
                        tell_object(ob, YEL "�����Ը����룬���� team with " +
                                    query("id", me)+"��\n"NOR);
                        set_temp("pending/team", ob, me);
                        return 1;
                }
        } else
                return notify_fail("ֻ�ж����������������˼��롣\n");
}
