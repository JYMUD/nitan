#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "��ͨ���š�" NOR);
        set("long", HIW @LONG
�����������������ããһƬ�ƺ�����ǰһ����ΰ�ĳ����Ĵ�
�ţ����ŵ�������������һλ���ӣ��ƺ�����ĵ����������⡣
LONG NOR );
        set("exits", ([
                "enter" : __DIR__"sky1",
]));
        set("sleep_room", 1);
        set("objects", ([
                __DIR__"npc/li": 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if ( dir == "enter" && objectp(present("li xunhuan", environment(me)))
             && me->query("sky12/floor") < 1)
        {
                write(HIG "��Ѱ��˵����Ҫ���������ȹ�����أ�\n" NOR);
                return notify_fail("��Ѱ����ס�����ȥ·��\n");
        }

        tell_object(me,  HIW "\n�������ʮ������֮��һ���졭��\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", HIM "��˵" + me->name() + HIM + "��������һ���졣\n\n" NOR);

        return ::valid_leave(me, dir);
}
void init()
{
        object me = this_player();
        
        if (! me->query("sky12/tianmen") && userp(me))
        {
                tell_object(me, HIG "��Ѱ������˵������û��ʹ�ù������ӣ�����ô��������ģ��ߣ�\n" NOR);

                me->delete("sky12");
                me->save();
                me->move("/d/city/wumiao");
                
                //destruct(me);                
        }
        return ;        
}
