#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "�׻��̳Ǿ��ۿ�" NOR, ({"yhshop vipcard9"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "����һ�Żƽ������ɵĿ�Ƭ���׻��̳ǹ�������Żݡ���лл���Ĳ��롹\n" NOR);
                set("unit", "��");
                                set("no_drop", 1);
                                set("no_sell", 1);
                                set("no_give", 1);
                                //set("no_get", 1);
                                set("no_put", 1);
                                set("no_steal", 1);
                                set("no_store", 1);
                                set("no_hand", 1);
        }
}

int query_autoload()
{
        return 1;
}

