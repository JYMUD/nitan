// auth.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define SCAN_D  "/adm/daemons/broadcastd"

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string title, info;
        int delay, times;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! is_root(me) && ! SECURITY_D->valid_grant(me, "(admin)"))
                return notify_fail("��û��Ȩ�޷��ʰ�ȫϵͳ��\n");

        if (! arg)
                return notify_fail("ָ�pushmsg + ������\n" +
                                   "add ���� ���ʱ��(��) ѭ������ ���� �� ���PUSHMSG\n" +
                                   "list : ��ʾ��ǰ�㲥\n" +
                                   "del ����: ɾ��ָ���㲥\n");

        if (arg == "list")
                return SCAN_D->show_push_lish();

        if (sscanf(arg, "del %s", title) == 1)
                return SCAN_D->delete_push_msg(title);

        if (sscanf(arg, "add %s %d %d %s", title, delay, times, info) != 4)
                return notify_fail("ָ�pushmsg + ������\n" +
                                   "add ���� ���ʱ��(��) ѭ������ ���� �� ���PUSHMSG\n" +
                                   "list : ��ʾ��ǰ�㲥\n" +
                                   "del ����: ɾ��ָ���㲥\n");


        // ���
        return SCAN_D->add_push_msg(title, info, delay, times);
}
