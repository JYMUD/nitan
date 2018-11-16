// mkdir.c
// updated by doing

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string dir;
        string grant;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg) return help(me);

        dir=resolve_path(query("cwd", me),arg);
        if (! me->is_admin()) 
        {
                grant = SECURITY_D->query_site_privilege("edit");
                if( !grant && !sscanf(dir, "/u/%*s") )
                        return notify_fail("��ֻ�������Լ���Ŀ¼�½���Ŀ¼��\n");
                        
                if( grant != "all" && !sscanf(dir, "/%s/%*s", grant) )
                        return notify_fail("��ֻ�������Լ�Ŀ¼���Լ�" + grant + "Ŀ¼�½���Ŀ¼��\n");
        }
        seteuid(geteuid(me));
        if (mkdir(dir))
                write("Ok.\n");
        else
                write("��û�������ｨ��Ŀ¼��Ȩ����\n");
        return 1;        
}

int help(object me)
{
        write(@HELP
ָ���ʽ : mkdir <��Ŀ¼��>

����һ����Ŀ¼��

see also: rm
HELP );
        return 1;
}
