// quit.c

#include <ansi.h>
#include <command.h>
#include <config.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

#define QUITMSG                        "/adm/etc/quitmsg"

int confirm(string yn, object me);

void destruct_ob(object me)
{
        if( !objectp(me) ) return;
        destruct(me);
}

void create()
{
        seteuid(getuid());
        set("name", "����ָ��");
        set("id", "quit");
        set("channel_id", "���߾���");
}

int main(object me, string arg)
{
        int i;
        int find;
        int doing;
        object *inv, link_ob;
        object *users;

        if (LOGIN_D->get_madlock())
                return notify_fail("ʱ���Ѿ���գ�û�����ܹ��˳����ʱ���ˡ�\n");

        if( me->is_busy() && !query("doing", me) )
                return notify_fail("��������æ���������£������˳���Ϸ��\n");

        if (me->is_fighting())
                return notify_fail("���������ڴ�ܣ���ô��˵�߾��ߣ�\n");

        if (me->query_competitor())
                return notify_fail("�üһ�����ں��˱��䣬��ô�ܿ��\n");

        if (me->dps_count() > 0)
                return notify_fail("�üһ������˱��˾��뿪�\n");

        if (me->query_condition("killer"))
                return notify_fail("�üһ��ɱ���˾ͱ��뿪�\n");

        if( time()-query("combat/pktime", me)<28800 )
                return notify_fail("�üһ��ɱ���˾ͱ��뿪�\n");

        if (me->over_encumbranced())
                return notify_fail("�����ϱ��Ķ���̫���ˣ��޷��뿪������硣\n");

        if (me->run_override("quit"))
                return 1;

        if( time()-query("birthday", me)<1800 && !query("reborn", me) && !wizardp(me) )
        {
                write(HIG "\n����˺����½��ģ���վ�涨�½��˺ű����������߰�Сʱ���ܱ���Ч��\n"
                          "�����˳�����Ϸ��ɾ������˺ţ���ȷ��Ҫ�������ʺŶ��˳��𣿣�" HIR "y" HIG "/" HIY "n" HIG "��\n" NOR);
                input_to((: confirm :), me);
                return 1;
        }

        link_ob=query_temp("link_ob", me);

        // We might be called on a link_dead player, so check this.
        if (objectp(link_ob))
        {
                // Are we possessing in others body ?
                if (link_ob->is_character())
                {
                        write("��Ļ��ǻص�" + link_ob->name(1) + "�����ϡ�\n");
                        exec(link_ob, me);
                        link_ob->setup();
                        link_ob->write_prompt();
                        return 1;
                }

                if( query_temp("ip_number", link_ob) )
                {
                        set("last_on", time(), link_ob);
                        set("last_from",
                                     query_temp("ip_number", link_ob), link_ob);
                        set("registerd",
                                     query("registered", me), link_ob);
                        link_ob->save();
                }
                destruct(link_ob);
        }

        if( query("doing", me) )
        {
                if (! interactive(me))
                        return 1;

                write("����ʱ���ߣ����ﲻ�˳�...\n");
                message("vision", me->name() + "�����ˡ�\n",
                                  environment(me), ({ me }));
                me->save();
                link_ob = new(LOGIN_OB);
                exec(link_ob, me);
                destruct(link_ob);
#ifdef DB_SAVE
                DATABASE_D->db_set_player(query("id", me),"online",2);//��������
                DATABASE_D->db_set_user(query("id", me),"online",2);//��������
#endif
                return 1;
        }

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(me);
#endif

        if( me->in_team() )
                me->dismiss_team();

        me->log_command("quit");

/*
#ifndef NO_QUIT_DROP
        if (! wizardp(me))
        {
                int flag;
                flag = 0;
                inv = all_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                        if( !inv[i]->query_autoload() && !query("equipped", inv[i]) )
                                        flag += DROP_CMD->do_drop(me, inv[i], 1);
                if (flag)
                        message("vision", me->name() + "�����ϵĶ���������������\n",
                                environment(me), ({ me }));
        }
#else  // ���������Ʒ������ж�ĳЩ��Ʒ�Ǳ���ݻٵ�
*/
#ifdef NO_QUIT_DROP
        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
                if (userp(inv[i]) || inv[i]->query_unique() ||
                    query("maze_item", inv[i]) || 
                    (! clonep(inv[i]) &&
                    ! sscanf(base_name(inv[i]), "/data/%*s/%*s"))) // ���������ʾ����Ʒ�Ƿ� /data Ŀ¼�µ�ԭ��
                {
                        if( query("equipped", inv[i]) )
                                inv[i]->unequip();
                        if( query("no_drop", inv[i]) || query("unique", inv[i]) )
                                destruct(inv[i]);
                        else
                                DROP_CMD->do_drop(me, inv[i], 1);
                }
#endif

        // write("��ӭ�´�������\n");
        color_cat(QUITMSG);
        if (environment(me))
        {
                message("vision", me->name() + "�뿪��Ϸ��\n",
                        environment(me), ({ me }));
        }

        CHANNEL_D->do_channel(this_object(), "sys",
                me->name()+"("+query("id", me)+")�뿪��Ϸ�ˡ�");


        log_file("stat", sprintf("%-8s %-10s %-18s %-18s %-15s.\n",
                                 me->name(1),query("id", me),
                                 ctime(query_temp("logon_time", me)),
                                 ctime(time()),
                                 interactive(me) ? query_ip_number(me) : "unknow"));

        users=filter_array(users(),(:query_temp("tomud", $1):));
        message("system", REM2(me), users);

        if (me->start_room_srv())
                set("startroom", base_name(environment(me)), me);

        set("last_on", time(), me); 
        me->save();
        me->set_magic_move();
        me->end_log();
#ifdef DB_SAVE
        DATABASE_D->db_set_player(query("id", me),"online",0);
#endif
        call_out("destruct_ob", 0, me);
        return 1;
}

int force_quit(object me)
{
        int find;
        object *users;

        if (previous_object() != me ||
            ! playerp(me))
                return notify_fail("�㲻�ܴݻ��������\n");

        seteuid(getuid());

        if (me->query_condition("killer"))
                return notify_fail("�üһɱ���˾ͱ��뿪�\n");

        if( time()-query("combat/pktime", me)<28800 )
                return notify_fail("�üһ��ɱ���˾ͱ��뿪�\n");

        if( query("mud_age", me)<1800 && !query("reborn", me) )
        {
                UPDATE_D->remove_user(query("id", me));
                return 1;
        }

        if( me->in_team() )
                me->dismiss_team();

        me->save();
        if (environment(me) != find_object(VOID_OB))
                me->move(VOID_OB, 1);

        users=filter_array(users(),(:query_temp("tomud", $1):));
        message("system", REM2(me), users);

#ifdef DB_SAVE
             DATABASE_D->db_set_player(query("id", me),"online",0);//��������
#endif
        destruct(me);
        return 1;
}

int confirm(string yn, object me)
{
        object *users;
        if (upper_case(yn) == "Y")
        {
                seteuid(getuid());

                log_file("static/register",
                         sprintf("%s %s commits a suicide from %s\n",
                                    log_time(), log_id(me),
                                    query_ip_number(me)));

                write(HIW "��ѡ���˷������˺��˳���̶��������ɾ��������������\n" NOR);

                users=filter_array(users(),(:query_temp("tomud", $1):));
                message("system", REM2(me), users);

                UPDATE_D->remove_user(query("id", me), 1);
                return 1;
        } else
        {
                write(HIG "��ѡ���˷����˳�(quit)��������Ϸ��\n" NOR);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
ָ���ʽ : quit | exit

����(��)����ʱ�뿪ʱ, �����ô�һָ�
HELP );
    return 1;
}

