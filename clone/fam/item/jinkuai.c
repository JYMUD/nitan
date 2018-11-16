
#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

void create()
{
        set_name(HIY "�׻ƽ��" NOR, ({ "yanhuang jinkuai", "yanhuang", "jinkuai" }) );
        set_weight(300);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "һ���ӲӵĽ�飬��������ǳ����ء�\n"
                            "ʹ�� changing ָ��׻ƽ����һ�Ϊһ����ƽ�YSG����\n" 
                            "�����ʱ��ʹ�ã���ý�������ֿ⣬���ⶪʧ��\n" NOR);
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
                
        if (! MEMBER_D->is_valib_member(me->query("id")) || 1)
        {
                me->add("stocks/balance", 1000000);
                write(HIG "�ɹ���һ���׻ƽ��һ�Ϊһ����YSG���������������⡣\n" NOR);
                // ���ڻ�ڼ����10W
                //me->add("stocks/balance", 100000);
                //write(HIR "����ͣ����ڻ�ڼ����10%��100000 YSG��ף���ڿ��֣�\n" NOR);
                write(HIY "��Ŀǰ���׻�������� " + HIC + me->query("stocks/balance") + HIY "YSG��\n" NOR);

        }/*
        else
        {
                me->add("stocks/balance", 110000);
                write(HIG "�ɹ���һ���׻ƽ����һ�Ϊʮһ��YSG���������������⡣\n" NOR);
                write(HIY "��Ŀǰ���׻�������� " + HIC + me->query("stocks/balance") + HIY "YSG��\n" NOR);
        }
*/
        destruct(this_object());
        me->save();

        return 1;
}

int query_autoload()
{
         return 1;
}
