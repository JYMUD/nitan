#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;

        if (! arg)
                return notify_fail("��Ҫ�ܻ�ʲô���ߵİ�����Ʒ��\n");

        if (me->is_busy())
                return notify_fail("��æ����������������������ɣ�\n");

        if (me->is_fighting())
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û���������ߡ�\n");

        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + CYN "��װ����˵��\n");

        if( !ob->is_item_make() && !query("unique", ob) )
                return notify_fail("������Ʒ���������ۡ�\n");

        if( !wizardp(me) && (ob->is_item_make() && ob->item_owner() != query("id", me)) )
                return notify_fail("�ⲻ�������Ʒ��\n");

        if( !query("armor_type", ob) && !query("skill_type", ob) )
                return notify_fail("������Ʒ���������ۡ�\n");

        if( !query("enchase/flute", ob) )
                return notify_fail("�⻹û�п��۹����ء�\n");

        if( !query("enchase/used", ob) )
                return notify_fail("������û����Ƕ��������\n");

        notify_fail(ob->name() + "�İ�����Ʒû�а취��������\n");

        return ob->do_wash(me);
}

int help(object me)
{
write(@HELP
ָ���ʽ : melt <��Ʒ����>

���ָ����������������������߰��������Ʒ�ܻ�����
HELP
    );
    return 1;
}
