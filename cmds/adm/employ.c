// employ.c

#include <ansi.h>
inherit F_CLEAN_UP;

#ifndef DB_D
#define DB_D      "/adm/daemons/dbd.c"
#endif

int main(object me, string arg)
{
        object ob;
        string old_status, new_status;
        int my_level, ob_level, level;
        string *tlist;

        mapping job = ([
                       "���ֵ�ʦ"  :  "teacher.c",
                       "��ҳά��"  :  "webmaster.c",
                       "��Ϸ����"  :  "presell.c",
        ]);

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s", arg, new_status) != 2)
                return notify_fail("ָ���ʽ��employ <ʹ����> <ְλ>\n");

        if (new_status != "���ֵ�ʦ" &&
            new_status != "��ҳά��" &&
            new_status != "��Ϸ����" &&
            new_status != "ȡ����Ӷ" )
                return notify_fail("û������ְλ��\n");

/*
        if (! objectp(ob = present(arg, environment(me))) ||
            ! playerp(ob))
*/
        ob = UPDATE_D->global_find_player(arg); 
        if (! objectp(ob)) 
                return notify_fail("��ֻ�ܸı�ʹ���ߵ�ְλ��\n");

        if( query("viremploy/job", ob) == new_status )
        {
                UPDATE_D->global_destruct_player(ob, 1); 
                return notify_fail("������Ѿ����θ�ְλ��\n");
        }

        if (new_status == "ȡ����Ӷ")
        {
                  if( !mapp(query("viremploy", ob)) )
                  {
                        UPDATE_D->global_destruct_player(ob, 1); 
                           return notify_fail("�����û�е����κ�ְλ��\n");
                  }

                  CHANNEL_D->do_channel(this_object(), "rumor",
                             ob->name()+"("+query("id", ob)+")������"
                             "��ְλ��"+query("viremploy/job", ob)+"��ȡ���ˣ�\n");

                // ���ֵ�ʦ��Ҫ�Ƴ���¼
                if( query("viremploy/job", ob) == "���ֵ�ʦ" )
                {
                        tlist = DB_D->query_data("virlist/teacher");
                        if (sizeof(tlist))
                        {
                                if( member_array(query("id", ob),tlist) != -1 )
                                {
                                        tlist-=({query("id", ob)});
                                        DB_D->set_data("virlist/teacher", tlist);
                                }
                        }
                }

                delete("viremploy", ob);
                delete("flowers", ob);
                SECURITY_D->remove_grant(query("id", ob),"home");
                tell_object(ob, HIG + me->name(1) + "�ջ����� home ��Ȩ�ޡ�\n" NOR);
                ob->save();
                UPDATE_D->global_destruct_player(ob, 1); 

                return 1;
        }

        CHANNEL_D->do_channel(this_object(), "rumor",
                             ob->name()+"("+query("id", ob)+")������Ϊ"+HIG+
                             new_status + NOR + "��\n");

        set("viremploy/job", new_status, ob);
        delete("flowers", ob);

        // ���ֵ�ʦ��Ҫ��¼
        if (new_status == "���ֵ�ʦ")
        {
                tlist = DB_D->query_data("virlist/teacher");
                if (sizeof(tlist))
                {
                        tlist+=({query("id", ob)});
                        DB_D->set_data("virlist/teacher", tlist);
                }
                else
                {
                        DB_D->set_data("virlist/teacher",({query("id", ob)}));
                }
        }

        set("viremploy/workroom", job[new_status], ob);
        SECURITY_D->grant(query("id", ob),"home");
        tell_object(ob, HIG + me->name(1) + "�������� home ��Ȩ�ޡ�\n" NOR);

        ob->save();
        UPDATE_D->global_destruct_player(ob, 1); 

        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : employ <ĳ��> (Ȩ�޵ȼ�)

��������Ȩ�޵ȼ�, [��ҳά������Ϸ���������ֵ�ʦ����ʦ����]

           employ <ĳ��> ȡ����Ӷ

ȡ�������⹤����Ա��ְλ��

HELP );
    return 1;
}
