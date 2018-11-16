inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG
�����ǳ����嶫�壬��Χ����������é�ݷ�����Ȯ���ţ�
�������ˣ���ʱ�м�ֻ��ë��ҡ��β�Ͷ�����м���������
�ڶ����ʾ��ӭ����Զ����λ�������ڸ����ţ��������
�ĺ������һȺ�׼�����һ��ũ��������������ũ�����µ�
��ʳ��ż�������Ⱥ��Сë���໥׷����Ϸ������˾���
���˺�����Ľ��
LONG);

        set("exits", ([
                "west"         : __DIR__"changshengcun",
                "east"         : __DIR__"changshengcuneast2",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);
        set("no_fight", 1);
        set("sleep_room", 1);

        set("objects", ([
                __DIR__"npc/wantong" : random(4),
                __DIR__"npc/nongfu1" : random(2),
                __DIR__"npc/nongfu2" : random(2),
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