inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG
�����������������������ɫɳ̲��һ��������������ˮ������
���Ž�⡣��˵��ԭ���������ˮ�峺�ޱȣ�������ˮ��������ɫ
ɳ̲�Ľ�ɳ�嵽�������£�����ˮ����˽�ɫ�������ˮ������ɫ
ɳ̲�ľ�����������ϴ�ӱ���˿������õĵ�ˮ���������������
������װһ����fill��������
LONG);

        set("exits", ([
                "west"     : __DIR__"wolongdao",
                "east"     : __DIR__"jinseshatan",                
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("resource/water", 1);    // ���Լ�ˮ

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