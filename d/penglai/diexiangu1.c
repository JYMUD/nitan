inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG
��������ȣ���Ⱥ�Ĳʵ������������ܣ����������˱Ƕ�����
��ʵĹ⻷�����Ͷ�����������������÷������������������
��������������з������¶�����֮�Ժ�    
LONG);

        set("exits", ([
                "west"     : __DIR__"diexiandao",
                "east"     : __DIR__"diexiangu2",        
                "north"    : __DIR__"bianqueju",                
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("n_time", 45); 
        set("n_npc", 1); 
        set("n_max_npc", 7);
        set("s_npc", __DIR__"npc/xiaodiexian");
        
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