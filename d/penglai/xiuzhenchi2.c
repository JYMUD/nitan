inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "�����");
        set("long",@LONG
�˴��ǵ������߻ָ�����������أ�����������ʢ�������ڴ�
�о�������̩�ޱȡ����ǿ�������ɡ�����Ϥ�Ѿõ������ƺ��ʹ�
�����������㲻����ȥ̽��������
LONG);

        set("exits", ([
                "west"      : __DIR__"xiuzhenchi3",
                "east"      : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("xiuzhenchi", 1);       // �������ڤ˼����
        set("no_fight", 1);
        set("sleep_room", 1);
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