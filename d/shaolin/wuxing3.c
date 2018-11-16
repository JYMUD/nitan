// Room: /d/shaolin/wuxing3.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIR "���ж�" NOR);
        set("long", @LONG
[1��31m�������ж��������پ�һ�������������������������˹�ȥ��
����һƬͨ�죬������ð��˿˿�������ŵ׾��ҵ���ʹʹ�㼸������
��ס���ȷ����¡¡�������Ŷ��ģ�������������¯֮�У�ȫ��
��ˮ�ֶ��ڱ�һ�εεؿ��ɡ�ǽ���ϼ��߿ݲ��ĸ�ʬ��֤������һ
�㡣[2��37��0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing1",
                "south" : __DIR__"wuxing2",
                "west" : __DIR__"wuxing0",
                "north" : __DIR__"wuxing4",
        ]));
        set("no_clean_up", 0);
        setup();
}

int check_out(object me)
{
        int metal, wood, water, fire, earth;

        metal=query_temp("wuxing/��", me);
        wood=query_temp("wuxing/ľ", me);
        water=query_temp("wuxing/ˮ", me);
        fire=query_temp("wuxing/��", me);
        earth=query_temp("wuxing/��", me);

        if ( metal > 0 &&
                metal == wood && metal == water &&
                metal == fire && metal == earth )
        {
                delete_temp("wuxing", me);
                me->move(__DIR__"andao2");
                return (1);
        }
        return (0);
}

int valid_leave(object me, string dir)
{
        int count;

        if (member_array(dir, dirs) != -1)
        {
                if (dir == "north")
                {
//                        write("*������*\n");
                        count=query_temp("wuxing/��", me);
                        count++;
                        set_temp("wuxing/��", count, me);
                        if (check_out(me))
                        {
                                write("��˳�����߳��������Թ���\n");
                                return 1;
                        }
                }
                else if (dir == "west")
                {
//                        write("*��˽�*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("��������أ�����ɮ�ࡣ\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
