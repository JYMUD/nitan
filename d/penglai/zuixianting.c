inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "����ͤ");
        set("long",@LONG
��˵����ͤ�г��������ڴ��������֣����ٸ߸裬˳��������
һ·Ѱ��������һ������������ͤ�У����ٵ��࣬������������
���������������ľ���̩�ޱȡ�Ƭ���������ڵ���䲻��ȡ������
�ƺ���С�����ڣ��������֣���ȫû��ע�⵽���˵ĵ�����
LONG);

        set("exits", ([
                "south"     : __DIR__"xiuzhenchi",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);

        set("objects", ([
                __DIR__"npc/jiujianxian" : 1,
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