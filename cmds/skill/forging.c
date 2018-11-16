// forging.c

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

        if (! item->is_item_make()) 
                return notify_fail("��ֻ�ܶ��������������ߣ�\n"); 

        if (! stringp(item->item_owner()) ||
              item->item_owner() != query("id", me) )
                return notify_fail("��ֻ�ܶ����Լ��ı�������ߣ�\n");

        if( query("equipped", item) )
                return notify_fail("���Ƚ��" + item->name() + "��װ����˵��\n"); 
                
        if (! objectp(obj = present("forging stone", me)))
                return notify_fail("������û�ж���ʯ�����������Ҫһ�����ʯ��\n");

        notify_fail(item->name() + "û�а취�����졣\n");

        return item->do_forging(me, obj);
}

int help(object me)
{
        write(@HELP
ָ���ʽ : forging <����>

���ָ��������������ߣ��Զ������ֵ��ߵĵȼ���ÿ������
����ʯһ�顣

HELP
        );
        return 1;
}
