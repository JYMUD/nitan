inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "�λ�����");
        set("long",@LONG
����һ���ø�����ɫ�������̳ɵ�·�������Ĺ��͸��������
�����ֲ�ͬ��ɫ�ʣ���ҫ��������·���Ե������ξ�����á�����
������˼��
LONG);

        set("exits", ([
                "north"    : __DIR__"tianxiandao1",
                "south"    : __DIR__"nanshandao1",        
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

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