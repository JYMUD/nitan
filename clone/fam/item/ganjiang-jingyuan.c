
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "�ɽ���Ԫ" NOR, ({ "ganjiang jingyuan" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "����һ�ž�Ө��覵ı�ʯ����˵ӵ������õ�������\n"
                                "����ָ�� use <��ľż�����ID> �ɽ��ż���������������Ƕ״̬��\n"
                                "ֻҪ�������һ����Ƕ���ɽ���ľż���������Ϊʮ��������        ʮ����\n"
                                "��ӵ���ų�����������\n"
                                "�й����һ����Ƕ��ʮ������������μ������ļ� help weapon | help enchase\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "��");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_use", "use");
        }
}

int do_use(string arg)
{
                object me;
                object weapon;
                
                string result;

                me = this_player();

                if (! arg)return notify_fail("ָ���ʽ: use <��ż�������ID>\n");

                if (! objectp(weapon = present(arg, me)))
                        return notify_fail("������û���������ߡ�\n");

            if (! weapon->is_item_make())
                        return notify_fail("�޷��ڴ˵�������ɡ�\n");

            if (weapon->weapon_level() < 12000)
                        return notify_fail("ֻ�ܾż��������ܽ��и��������\n");

                weapon->set("magic/imbue_ok", 1);
                weapon->set("owner/" + weapon->item_owner(), 5000000);
                
                weapon->save();
            
        tell_object(me, HIC "�����" + weapon->name() + HIC "������"
                    "���������ı仯��\n" NOR);


                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}
