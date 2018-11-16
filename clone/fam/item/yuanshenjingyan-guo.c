#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(HIR "Ԫ�����" NOR, ({"yuanshen guo", "yuanshen", "guo"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "\n����һ�Ż��ɫ���ɹ�����˵���ú�����ǿԪ���顣\n"
                                      "*����(eatysg yuanshen guo)��Ԫ��ɻ��20���顣\n" NOR);
                set("unit", "��");
                set("value", 1);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "eatysg");       
}

int do_use(string arg)
{
        int exp;
        object me = this_player();
        
        exp = 200000;
        
        if (environment(this_object()) != me)
                return notify_fail("������û�������Ʒ��\n");

        if (! me->query("thborn") ||
            ! me->query("yuanshen/status"))
                return notify_fail("�㻹û�л��Ԫ��\n");
        
        if (me->query("yuanshen/exp4") >= 1600000000)
                return notify_fail("���Ԫ������ߣ�������ʹ�þ�����ˣ�\n");

        if (me->query("yuanshen/exp") >= 2000000000)
        {
                if (me->query("yuanshen/exp2") >= 2000000000)
                {
                        if (me->query("yuanshen/exp3") >= 1800000000)
                        {
                                if (me->query("yuanshen/exp4") >= 1600000000)
                                {
                                        // ��������
                                }
                                else
                                {
                                        me->add("yuanshen/exp4", exp);
                                }
                        }
                        else
                        {
                                me->add("yuanshen/exp3", exp);
                        }
                }
                else
                {
                        me->add("yuanshen/exp2", exp);
                }
        }
        else
        {
                me->add("yuanshen/exp", exp);
        }

        me->save();

        tell_object(me, HIG "�����Ԫ�������Ԫ�������ӣ�" + sprintf("%d", exp) + "�㡣\n");
        
        log_file("yuanshen-guo", me->query("id") + " at " + ctime(time()) + " use yuanshen guo.\n");
        
        destruct(this_object());
        
        return 1;
}
