// This program is a part of NT MudLIB
// Master.c
//
// For ES II mudlib
// Original from Lil
// Rewritten by Annihilator (11/07/94)
// Modified by Xiang for XKX (12/15/95)
// Rewritten by Lonely@nitan.org

#pragma optimize
#pragma save_binary


#define BIG5_PORT                       6000
#define UTF8_PORT                       6666
#define TOMUD_PORT                      7000

//-----------------------------------------------------------------------------

#include "/adm/kernel/master/compile_object.c";        /* �������� MudOS ������� */
#include "/adm/kernel/master/crash.c";                 /* �������� Crash ʱ�Ľ������ */
#include "/adm/kernel/master/preload.c";               /* Ԥ�������ʼ������ */
#include "/adm/kernel/master/error.c";                 /* �������ѶϢ�ĺ�ʽ */
#include "/adm/kernel/master/file.c";                  /* ���� domain_file , author_file , privs_file */
#include "/adm/kernel/master/ed.c";                    /* �й� Edit ��һЩ�趨 */
#include "/adm/kernel/master/parse.c";                 /* �ķ�(������Mud�����ƺ�û���ô�?) */
#include "/adm/kernel/master/object.c";                /* �����⵽����ʱ, �����������������д˺�ʽ */

//-----------------------------------------------------------------------------

#include "/adm/kernel/master/valid_asm.c";
#include "/adm/kernel/master/valid_author.c";
#include "/adm/kernel/master/valid_bind.c";            /* ��麯ʽָ��������Ľ�� */
#include "/adm/kernel/master/valid_compile.c"          /* �ж�һ���ļ��Ƿ�ɱ����� */
#include "/adm/kernel/master/valid_compile_to_c.c";    /* �ж��Ƿ������ LPC->C ���� */
#include "/adm/kernel/master/valid_domain.c";
#include "/adm/kernel/master/valid_hide.c";            /* ����������� */
#include "/adm/kernel/master/valid_link.c";            /* ���� link �ⲿ��ʽ����; */
#include "/adm/kernel/master/valid_object.c";          /* �����ܿ����Ƿ�Ҫ����ĳ����� */
#include "/adm/kernel/master/valid_override.c";        /* ���� efun:: ����; */
#include "/adm/kernel/master/valid_seteuid.c";
#include "/adm/kernel/master/valid_readwrite.c";       /* ����Ƿ���Ȩ��ȡд�뵵�� */
#include "/adm/kernel/master/valid_save_binary.c";     /* ����һ������Ƿ���Դ�����������ĳ�ʽ */
#include "/adm/kernel/master/valid_shadow.c";          /* ������Щ������Ա�ͶӰ */
#include "/adm/kernel/master/valid_socket.c";          /* ���� socket �ⲿ��ʽ */
#include "/adm/kernel/master/valid_database.c";        /* ����mysql���ݿ������ */

//-----------------------------------------------------------------------------

//        connect() ���ص�������ᵱ����ʼʹ������� (initial user object)��
//        ��ע�⣬֮�������ʹ�� exec() �ⲿ��ʽ���ı�ʹ���������

object connect(int port)
{
        object login_ob;
        mixed err;

        err = catch(login_ob = new(LOGIN_OB));

        if( err )
        {
                write("�������������޸�ʹ�������߲��ݵĳ�ʽ�������������\n");
                write(err);
                destruct(this_object());
        }

        if( port == BIG5_PORT )
                set_temp("big5", 1, login_ob);

        else
        if( port == TOMUD_PORT )
                set_temp("tomud", 1, login_ob);

        //else
        //if( port == UTF8_PORT )
        //      set_encoding("utf-8", login_ob);

        return login_ob;
}

string get_root_uid()
{
        return ROOT_UID;
}

string get_bb_uid()
{
        return BACKBONE_UID;
}


string object_name(object ob)
{
        if( ob ) return ob->name();
}

// �Ƿ�ֱ������BINARY���������ļ���
int direct_run_binary(string file)
{
        object ob;
        object vob;

#ifndef BINARY_SUPPORT
        return 0;
#else
        if( sscanf(file, DATA_DIR "%*s") )
                // �����DATA������ļ�������ֱ������BIN���룬
                // ��Ҫ���г���İ汾��Ч��顣
                return 0;

        if( objectp(ob = find_object(CONFIG_D)) &&
            objectp(vob = find_object(VERSION_D)) ) {
                // �ҵ���CONFIG_D���鿴�����Ƿ��ǰ汾����վ
                // �㣬����ǣ���鿴�Ƿ��Ƿ�����Դ������
                // �򷵻ط񣬱�ʾ��Ҫ���BIN��
                return query("release server", ob) != "local" &&
                       !VERSION_D->is_need_release_source(file);
        }

        // û���ҵ�CONFIG_D && VERSION_D�������룬ֱ������
        // BIN���롣
        return 1;
#endif
}

void create()
{
        if( clonep() )   return;

        write("master: loaded successfully.\n");
}

void check_daemons()
{
        string *sp;
        int i;

        sp = epilog(0);
        if( !sp ) return;

        for (i = 0; i < sizeof(sp); i++)
                if( stringp(sp[i])) preload(sp[i]);
}

