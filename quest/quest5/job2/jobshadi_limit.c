#include <ansi.h>

#include <login.h>

int update_condition(object me, int duration)
{
        object room;
        object ob;
          object obb;
        object* inv;
        int i;
                
        ob=this_player();
        room = environment(ob);     

        if( query_temp("where", me)){
        if( query_temp("where", me) != environment(me)){
                message_vision(HIY"һ���α��ܹ�����$N˵���������سǣ���ȴ�����й䣬��ȥ��������ˣ�\n"NOR,me);
                set_temp("job_failed", 1, me);
                return 0;
        }
        }

        if( query_temp("start_job", me)){
        message_vision(HIY"$N��վ�ڳ�ǽ������ע���ų���"HIR"�ɹű�"HIY"��һ��һ����\n"NOR,ob);
        }
        me->apply_condition("jobshadi_limit", duration - 1);

        if(duration<1)
        {
                message_vision(CYN"\nһ���س��α��ܹ���˵�����ɹ�������ʱ�������ˣ�$N���Ի�ȥ�����ˣ�\n"NOR,ob);
        if( query_temp("start_job", me)){
                set_temp("job_over", 1, ob);
        }
                delete_temp("start_job", ob);
                inv=all_inventory(room);
                for (i = 0; i < sizeof(inv); i++) {
                     obb=inv[i];
                        if (obb->is_character()) {
                        if( query("ygjg", obb) == ob)destruct(obb);
                    }
                        continue;
                }
                return 0;
        }
        return 1;
}