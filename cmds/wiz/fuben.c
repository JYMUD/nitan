// This program is a part of NITAN MudLIB
// Written by Lonely@nitan.org (16/05/2008)
// fuben.c ��������ָ��

#include <ansi.h>

inherit F_CLEAN_UP;

int help (object me);
int main(object me,string arg)
{
        int i, j;
        string cmd;
        string fbname;
        string owner;
        string *ks, *os;
        mapping all, data, temp;
        string msg = "";

        if( !SECURITY_D->valid_grant(me, "(wizard)") )
                return 0;

        if( !arg ) {
                help( me );
                return 1;
        }

        if( sscanf(arg,"%s %s %s",cmd, fbname, owner) != 3 &&
            sscanf(arg,"%s %s",cmd, fbname) != 2 )
                cmd = arg;

        all  = FUBEN_D->query_fuben_all();
        data = FUBEN_D->query_fuben_data();
        if( !stringp(fbname) ) {
                if( !all ) return notify_fail("��̶����û���κθ�����\n");
                msg += "��̶���ڿ����ĸ����ռ����£�\n";
                msg += "������������������������������������\n";
                ks = keys(all);
                for( i=0;i<sizeof(ks);i++ ) {
                        temp=all[ks[i]];
                        if( mapp(temp) && sizeof(temp) ) {
                                os = keys(temp);
                                for( j=0;j<sizeof(os);j++ )
                                        msg += sprintf("�������ƣ�%-33sʣ��ʱ�䣺%s\n",
                                                data[ks[i]]["name"]+"<"+ks[i]+">("+os[j]+")",
                                                appromix_time(temp[os[j]] - time()) );
                        }

                }
                me->start_more(msg);
                return 1;
        } else {
                if( cmd == "open" ) {
                        FUBEN_D->open_fuben(me, fbname);
                        return 1;
                } else if( cmd == "close" ) {
                        FUBEN_D->close_fuben(me, fbname);
                        return 1;
                }

                if( fbname != "all" && (undefinedp(data[fbname]) ||
                    undefinedp(all[fbname])) )
                        return notify_fail("��̶����û�����������\n");

                if( cmd == "list" ) {
                        msg += sprintf("��̶���ڿ�����%s�����ռ����£�\n", (fbname=="all")?"����":data[fbname]["name"]);
                        msg += "������������������������������������\n";
                        if( fbname == "all" ) {
                                ks = keys(data);
                                for( i=0;i<sizeof(ks);i++ ) {
                                        msg += sprintf("�������ƣ�%-26s���Ҫ��%-8s����ʱ�䣺%s\n",
                                               data[ks[i]]["name"]+"<"+ks[i]+">",
                                               (!undefinedp(data[ks[i]]["team"]))?"����":
                                               (!undefinedp(data[ks[i]]["single"])?"����":"����"),
                                               appromix_time(to_int(data[ks[i]]["time"])) );
                                }
                        } else {
                                temp = all[fbname];
                                ks = keys(temp);
                                for( i=0;i<sizeof(ks);i++ ) {
                                        msg += sprintf("�������ƣ�%-33sʣ��ʱ�䣺%s\n",
                                               data[fbname]["name"]+"<"+fbname+">("+ks[i]+")",
                                               appromix_time(temp[ks[i]] - time()) );
                                }
                        }
                        me->start_more(msg);
                        return 1;
                } else if( cmd == "dest" ) {
                        if( !stringp(owner) ) {
                                ks = keys(all[fbname]);
                                for( i=0;i<sizeof(ks);i++ )
                                        FUBEN_D->clear_fuben(fbname, ks[i]);
                                write("OK.\n");
                                return 1;

                        } else {
                                FUBEN_D->clear_fuben(fbname, owner);
                                write("OK.\n");
                                return 1;
                        }

                } else {
                        help(me);
                        return 1;
                }
        }
        return 1;
}

int help (object me)
{
                      write(@HELP
ָ���ʽ : fuben list [��������]
           fuben dest  ��������  [��������]

fuben list [all]              �鿴��ǰ��Ϸ�����еĸ�����ϸ��Ϣ
fuben list ��������           �鿴ָ����������ϸ��Ϣ
fuben open|dest all|��������  �鿴ָ����������ϸ��Ϣ
fuben dest ��������           ����ָ�����͸��������и���
fuben dest �������� ��������  ����ָ�����͸�����ĳ�˸���

HELP );
                      return 1;
}
