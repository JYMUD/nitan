#include <ansi.h>
inherit ROOM; 
void create()
{
        int i;
        set("short", "��ܶ�");
        set("long", @LONG
��ܶ��ϻ����˺���һ��ҳ�����ܶ��ͷ����������߶�ߵ�
�������ڲ�������ɨ�����ﲽ����֩��˿����ܶ��ĸ����ϻ�����ϡ
����һЩ�������µĺۼ���ʱ����ЩС��Ҳ��������������
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "down" : "/d/shaolin/cjlou1",
        ]));        

        set("bamboo_count", 1);
        // set("yijinjing_count", 1);
        setup();
}

void init()
{ 
        add_action("do_pull", "qingsao");
        add_action("do_pull", "clear");
}

int do_pull()
{
        object ob, *obs, me = this_player();
        
        if (me->is_busy())
                return notify_fail("����æ���أ�\n");
                
        message_vision("$N��ϸ�ش�ɨ����ܶ��ϵĻҳ�,����ȥ�ɾ����ˡ�\n", me);
        me->start_busy(5);
        
        // obs = filter_array(children("/clone/book/yijinjing.c"), (: clonep :));
        // if (query("bamboo_count") > 0 && sizeof(obs) < 3) 
        if (query("bamboo_count") > 0)
        {
                    ob = new("/clone/book/yijin_book"); 
                ob->move(me, 1);
                addn("bamboo_count", -1);
                CHANNEL_D->do_channel(this_object(),"rumor",sprintf("%s�㵽����������֮���׽�ؼ�����",query("name", me)));
        } else
        if (query("yijinjing_count") > 0)
        {
                if (random(2)) ob = new("/clone/book/yjj_book2");
                else ob = new("/clone/book/yijinjing");
                ob->move(me, 1);
                addn("yijinjing_count", -1);
                CHANNEL_D->do_channel(this_object(),"rumor",sprintf("%s�㵽����������֮���׽��������",query("name", me)));
        }
        return 1;
}

void reset()
{
        set("bamboo_count", 1);
        // set("yijinjing_count", 1);
}
