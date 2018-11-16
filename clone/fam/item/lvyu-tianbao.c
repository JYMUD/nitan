
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�����챦" NOR, ({ "lvyu tianbao" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "����һ����ɫ��ʯ����˵ӵ������õ�������\n"
                                                "����ָ�� up9lv <��ı���ID> �ɽ���ı�������Ϊ9��������\n" NOR);
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
                add_action("do_up9lv", "up9lv");
        }
}

int do_up9lv(string arg)
{
                object me;
                object weapon;
                
                string result;

                me = this_player();

                if (! arg)return notify_fail("ָ���ʽ: up9lv <�������ID>\n");

                if (! objectp(weapon = present(arg, me)))
                        return notify_fail("������û���������ߡ�\n");
           
            if (! weapon->is_item_make())
                        return notify_fail("�޷��ڴ˵�������ɡ�\n");

            if (weapon->weapon_level() >= 50000)
                        return notify_fail("��ı����Ѿ��Ǿż������ˣ�����Ҫ�������ˡ�\n");

        // 
                weapon->set("owner/combat", 6000000);
                weapon->set("combat/MKS",100);
                weapon->set("combat/PKS", 100);
                if (weapon->query("owner/" + me->query("id")) < 4000000)
                        weapon->set("owner/" + me->query("id"), 4000000);

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
