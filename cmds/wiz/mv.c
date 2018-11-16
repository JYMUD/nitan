// mv.c
// updated by doing
 
inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
        string src, dst;
        string dir;
 
        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        seteuid(geteuid(me));
        if (! arg || sscanf(arg, "%s %s", src, dst) != 2)
                return notify_fail("ָ���ʽ: mv <ԭ����> <Ŀ�굵��> \n");
 
        src=resolve_path(query("cwd", me),src);
        dst=resolve_path(query("cwd", me),dst);
 
        if (file_size(src) == -1)
        {
                write("Դ�ļ����ִ���\n");
                return 1;
        }
        if (! me->is_admin()) 
        {
                dir = SECURITY_D->query_site_privilege("edit");
                if( !dir && (!sscanf(src, "/u/%*s") || !sscanf(dst, "/u/%*s")) )
                        return notify_fail("��ֻ���ƶ����Լ���Ŀ¼���ļ���\n");
                        
                if( dir != "all" && (!sscanf(src, "/%s/%*s", dir) || !sscanf(dst, "/%s/%*s", dir)) )
                        return notify_fail("��ֻ���ƶ����Լ�Ŀ¼���Լ�" + dir + "Ŀ¼���ļ���\n");
        }
        SECURITY_D->backup_file(dst);
        if (rename(src, dst) == 0)
                write("Ok.\n");
        else
        {
                if (! SECURITY_D->valid_read(src, me, "ls"))
                {
                        write("Դ�ļ����ִ���\n");
                        return 1;
                }
                write("��û���㹻�Ķ�дȨ���ƶ��ļ���\n");
        }
        return 1;
}
 
int help(object me)
{
        write(@HELP
ָ���ʽ : mv <ԭ����> <Ŀ�굵��>
 
��ָ��������޸�ĳ��������Ŀ¼���ơ�

see also: cp, rm
HELP );
        return 1;
}
