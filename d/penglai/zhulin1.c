inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "����");
        set("long",@LONG
���������ɵ���ڴ������֣���������ãã���������ˣ������ɾ���
LONG);

        set("exits", ([
                "north"   : __DIR__"haitan",
                "south"   : __DIR__"zhulin2",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        if (random(2) == 1)
        {
                set("objects", ([
                        __DIR__"obj/zhuye" : 1 + random(4),
                ]));
        }
        
        setup();
}

void init ()
{
        if (! this_player()->query_temp("apply/xianshu-lingwei"))
        {
                if (! this_player()->query("penglai/go_quest/ok"))
                {
                        this_player()->start_busy(3);
                        tell_object(this_player(), NOR + WHT "�㵽�˴˴�������������������һʱ�����Ա����\n" NOR);
                }
                else
                {
                        if (random(2))
                        {
                                this_player()->start_busy(1);
                                tell_object(this_player(), NOR + WHT "�㵽�˴˴�������������������һʱ�����Ա����\n" NOR);                
                        }
                }
        }
}