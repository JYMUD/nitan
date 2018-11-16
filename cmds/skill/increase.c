// increase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, item;

        if (! arg)
                return notify_fail("��Ҫ����ʲô��Ʒ��\n");

        if (me->is_busy())
                return notify_fail("��æ����������������������ɣ�\n");

        if (me->is_fighting())
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if (! objectp(item = present(arg, me)))
                return notify_fail("������û���������ߡ�\n");

        if (! objectp(obj = present("increase stone", me)))
                return notify_fail("������û�и���ʯ��\n");

        notify_fail(item->name() + "û�а취�����졣\n");

        return item->do_increase(me, obj);
}

int help(object me)
{
write(@HELP
ָ���ʽ : increase <��Ʒ����>

���ָ��������������ߣ��Զ������ֵ��߻��Ƿ�������������ÿ
�����ĸ���ʯһ�顣

HELP
    );
    return 1;
}