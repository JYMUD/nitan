
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "�����±��ĺ�װ" NOR, ({ "moon gift" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "�����������׻������ر���Ʒ����ʹ��open moon giftָ��򿪡�\n"
                                                "ͬʱ�����е�����9.18�±�����������ʿ���������ܣ�\n"NOR);
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
                add_action("do_open", "open");
        }
}


int do_open(string arg)
{
                object me;
                object ob;

                me = this_player();


                if (! arg)return notify_fail("ָ���ʽ: open moon gift\n");

                if (arg != "moon gift")return notify_fail("ָ���ʽ: open moon gift\n");
                
                ob = new("/clone/fam/max/yuebinggift2");
                ob->move(me, 1);
                ob = new("/clone/fam/max/yuebinggift2");
                ob->move(me, 1);
                ob = new("/clone/fam/max/yuebinggift2");
                ob->move(me, 1);
                ob = new("/clone/fam/max/yuebinggift2");
                ob->move(me, 1);

                tell_object(me, HIG "��������±��ĺ�װ��\n" NOR);
                
                destruct(this_object());
                
                return 1;
}

int query_autoload()
{
         return 1;
}
