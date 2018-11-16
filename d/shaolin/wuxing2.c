// Room: /d/shaolin/wuxing2.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIB "���ж�" NOR);
        set("long", @LONG
[1��34m�������ж���һ�������������������ˮ��ŵ��Ǻ���
���࣬һ����ȥ�����ɵ�ɢ����������һ������ð��ˮ�档��ɲ�
����ˮ���ϲ�ʱƮ����һ���߽��÷��׵ĸ�ʬ����ֻ��������������
���£���ʬ��ҧ����ľȫ�ǡ��ı��ôֲڵ�Ƭ���ݶ���ɣ�һ�ſ�ˮ
������ǽ�ڹ�����������ˮ�У�[2��37��0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing1",
                "south" : __DIR__"wuxing4",
                "west" : __DIR__"wuxing0",
                "north" : __DIR__"wuxing3",
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
                if (dir == "east")
                {
//                        write("*ˮ��ľ*\n");
                        count=query_temp("wuxing/ľ", me);
                        count++;
                        set_temp("wuxing/ľ", count, me);
                        if (check_out(me))
                        {
                                write("��˳�����߳��������Թ���\n");
                                return 1;
                        }
                }
                else if (dir == "north")
                {
//                        write("*ˮ�˻�*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("��������أ�����ɮ�ࡣ\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
