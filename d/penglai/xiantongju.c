inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "��ͯ��");
        set("long",@LONG
������ͯ���Ŵ���Ѿ�����Ϥ�ˣ���ͯ�ڴ˹����ʱ�ˡ�
������Խ��вֿ���Ʒ�Ĵ�ȡ���������ܽ����ҫ��������
�ƣ��ƺ�Ҫ�����ݲֿ���ɫ���١�
LONG);

        set("exits", ([
                "southwest"    : __DIR__"caiyunjian2",        
                "northeast"    : __DIR__"changshengmeilin1",                
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);

        set("objects", ([
                "/d/city/npc/xiantong" : 1,
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