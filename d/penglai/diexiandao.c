inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "���ɵ�");
        set("long",@LONG
�����˴�����������λð�����磬��Χ����һֻ��ʰ�쵵�
����Χ������������Χ��ǰ�������ҫ��һ�����ֱͨɽ��֮�С�       
LONG);

        set("exits", ([
                "west"     : __DIR__"tianxiandao3",
                "east"     : __DIR__"diexiangu1",                        
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
                set("penglai", 1);           // ��ʾ��������

                set("objects", ([ 
                        "/clone/npc/walker": 1,
                ]));

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