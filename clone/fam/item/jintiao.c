
#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

void create()
{
        set_name(HIY "�׻ƽ���" NOR, ({ "yhhero goldbar", "yhhero", "goldbar" }) );
        set_weight(300);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "һ����ӲӵĽ���������������Ϊ���ʡ�\n"
                            "ʹ�� changing ָ��׻ƽ����һ�Ϊʮ��YSG����Ա�ɶһ�ʮһ��YSG��\n" 
                            "�����ʱ��ʹ�ã���ý���������ֿ⣬���ⶪʧ��\n" NOR);
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
                add_action("do_changing", "changing");
        }
}

int do_changing(string arg)
{
        object me;
        object ob;
        string enid, obid;
        int point, cur_firm;

        me = this_player();
                
        if (! MEMBER_D->is_valib_member(me->query("id")))
        {
                me->add("stocks/balance", 100000);
                write(HIG "�ɹ���һ���׻ƽ����һ�Ϊʮ��YSG���������������⡣\n" NOR);
                write(HIY "��Ŀǰ���׻�������� " + HIC + me->query("stocks/balance") + HIY "YSG��\n" NOR);

        }
        else
        {
                me->add("stocks/balance", 110000);
                write(HIG "�ɹ���һ���׻ƽ����һ�Ϊʮһ��YSG���������������⡣\n" NOR);
                write(HIY "��Ŀǰ���׻�������� " + HIC + me->query("stocks/balance") + HIY "YSG��\n" NOR);
        }

        destruct(this_object());
        me->save();

        return 1;
}

int query_autoload()
{
         return 1;
}
