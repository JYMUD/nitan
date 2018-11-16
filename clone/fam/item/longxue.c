
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "��Ѫ" NOR, ({ "dragon blood", "dragon", "blood" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "һƿ��֮ѪҺ�����������޸���Ƕ��(ָ�� rehab)��\n "
                            HIY "���߶�ʧ    ��   ��\n"NOR);
                set("value", 2000000);
                set("unit", "ƿ");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_rehab", "rehab");
        }
}

int do_rehab(string arg)
{
        object me;
        object ob;
        string enid, obid;

        me = this_player();

        if (! arg)return notify_fail("ָ���ʽ��rehab <��Ƕ��ƷID> in <����ID>\n");

        if (me->is_busy())
                return notify_fail("��æ����������������������ɣ�\n");

        if (me->is_fighting())
                return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

        if (sscanf(arg, "%s in %s", enid, obid) != 2)
                return notify_fail("ָ���ʽ��rehab <��Ƕ��ƷID> in <����ID>\n");

        if (! objectp(ob = present(obid, me)))
                return notify_fail("������û���������ߡ�\n");         
        
        if (! ob->query("enchase"))
                return notify_fail(ob->name() + "����û����Ƕʲô�ɣ�\n" NOR);

        if (! ob->query("enchase/" + enid))
                return notify_fail(ob->name() + "��û�������Ƕ��Ʒ��\n" NOR);

        if (ob->query("enchase/" + enid + "/cur_firm") >= 99)
                return notify_fail(ob->query("enchase/" + enid + "/name") + "Ŀǰ������Ҫ���Ӽ�̡�\n");

        // ��ʼΪ��Ƕ��Ʒ���Ӽ��
        ob->set("enchase/" + enid + "/cur_firm", 99);
        ob->save();

        tell_object(me, HIG + ob->query("enchase/" + enid + "/name") + "�ļ�������ˣ�\n" NOR);

        destruct(this_object());

        return 1;
}

int query_autoload()
{
         return 1;
}
