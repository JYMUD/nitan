inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "���ݵ�");
        set("long",@LONG
����������ݵ���ζ�Ѿ������Ŀ�����������Ʈ�ŵ�������
�����������������������Եø�����������������˾��磬���ν
�򸴺���
LONG);

        set("exits", ([
                "north"    : __DIR__"tianxiandao3",
                "south"    : __DIR__"lancaodi3",        
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        if (random(3) == 1)
        {
                set("objects", ([
                        __DIR__"obj/lancao" : 3,
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