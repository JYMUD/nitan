// mccp.c
#include <ansi.h> 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
#ifdef MCCP_SUPPORT
        object *mccp, *user;
        
        user = filter_array(users(), (: interactive($1) :));
        mccp = filter_array(user, (: compressedp($1) :));
        
        write(sprintf("��� MCCP ״̬Ϊ��" HIR "%s\n" NOR, compressedp(me) ? "ON" : "OFF"));
        write(sprintf("���ڹ� " HIC "%d" NOR "/%d ��ʹ���߿��� MCCP��\n", sizeof(mccp), sizeof(user)));
#else
        write("��������Ŀǰ��֧����·����ѹ�����ܡ�\n");
#endif
        return 1;
}

int help(object me)
{
        write(@HELP
ָ��˵��:
    �����ҵĳ�ʽ�Ƿ������� MCCP(Mud Client Compression Protocol)����
�˹��ܿ��Լ�����·�����ٶ�

HELP );
    return 1;
}