inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "��ȵ��");
        set("long",@LONG
��˵�������������ɵ��ķ�����������������Ƕ������뿪��
�壬���Ǳ����ϵ��������������ҽ��ȵ�Ὣ��Щ������������
���ܿ�������ɫ�����ΰ���Ҳ�ǳ��򵥣���ֵ������ﲢû����
��ҽ�β��˵�ҩ�ߡ� 
LONG);

        set("exits", ([        
                "south"    : __DIR__"diexiangu1",                
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/bianque" : 1,
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