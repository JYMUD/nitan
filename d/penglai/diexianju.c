inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "���ɾ�");
        set("long",@LONG
һ�����������Ϯ������ϸһ������֪������������ø���
����������ɣ���ȷ�����������ɫ�ݺύ�㣬�ҷ�������������
�룬һ������ò�����������ڽ���ȥ�ĺ��������ɱ걾��������
�Ǵ�˵�еĵ����ˡ�
LONG);

        set("exits", ([        
                "north"    : __DIR__"diexiangu2",                
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/diexian" : 1,
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