inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG
�����ɽ��й涨���������˾����������뵺����Ҫ���������
��ʱ�����˷�����������Ҫ�������뷲�������߾���Ҫ�ɴ˴�������
������ʯɳ̲ϴ�������������ܽ��볾���䣬��ϴ������ͬʱ����
�����ߵķ���Ҳ��������
LONG);

        set("exits", ([
                "southeast"   : __DIR__"pantaoyuan2",
                "southwest"   : __DIR__"pantaoyuan3",
                "north"       : __DIR__"caishishatan",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("no_clean_up", 1); 

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