#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", RED "������ͨ����" NOR);
       set("long", RED @LONG

                    ��     ��     ͨ     ��

    һ������˾��������Ľ��ݣ���֪��ͨ���η�����������ף���
����Զû��ֹ��һ�㡣

LONG NOR );
        set("exits", ([
                "up" : __DIR__"lunhuisi",
                "down" : __DIR__"diyin_road2",
        ]));

        set("no_sleep_room", 1);

        set("no_magic", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        if (dir == "down")
        {
                i=query_temp("long_road", me);
                i = i + 1;

                if (i == 10)
                {
                        delete_temp("long_road", me);
                        return 1;
                }
           else {
                        set_temp("long_road", i, me);
                        return notify_fail( RED "\n����������������׵Ľ��ݡ���"
                                            "ֻ�������ƺ����������죬��Զ���ﲻ�˾�ͷ"
                                            "һ�㡣\n" NOR);
                }
        }
   else {
                if (dir == "up")
                {
                        delete_temp("long_road", me);
                        return 1;
                }
        return 1;
        }
}