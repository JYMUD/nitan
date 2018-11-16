#include <ansi.h>
inherit ITEM;

string shop_id(){return "hz_shop";}
string shop_name(){return HIW "��ʸ�" NOR;}
string shop_string(){return "yuhuangge fangqi";}

void create()
{
        set_name(HIW "��" + shop_name() + HIW "������" NOR, ({ shop_string() }));        

        set_weight(1);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "��");
                set("long", HIY "����һ��" + shop_name() + HIY "�ķ����������Ʊ��ܡ�\n"
                            HIM        "ʹ�� deed register �ɳ�Ϊ" + shop_name() + HIM "�������ߡ�\n"
                            HIM "ʹ�� deed hide �ɽ��������ء�\n" NOR);
                set("no_sell", "���������˹��أ��ҿ��㻹��������Ұɣ�\n");
                set("material", "paper");
                set("can_paimai", 1);
        }
}

void init()
{
        add_action("do_deed", "deed");
}

int do_deed(string arg)
{
        object me;

        me = this_player();

        if (! arg)return notify_fail("��Ҫ�÷�����ʲô��\n");

        if (arg == "hide")
        {
                write("���" + shop_name() + "����������������\n");
                destruct(this_object());
                
                return 1;
        }        
        else if (arg == "register")
        {
                if (SHOP_D->is_shop_owner(shop_id(), me->query("id")))
                        return notify_fail("�㲻�Ѿ���" + shop_name() + "����������\n");

                write(HIC "����" + shop_name() + HIC"�ķ�����ǩ������Ĵ�����" + me->name() + "\n" NOR);
                write(HIG "��ϲ���Ϊ" + shop_name() + HIG "�����ˡ�\n" NOR);

                SHOP_D->change_owner(me, shop_id(), me->query("id"));
                log_file("shop", me->query("id") + " at " + ctime(time()) + " ��Ϊ"+ shop_id() + "�����ˡ�\n");

                return 1;
        }
        
        else
                return notify_fail("��Ҫ�÷�����ʲô��\n");

}




