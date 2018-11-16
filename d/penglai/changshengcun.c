inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG
������Ǵ�˵�г������ˣ�������֣�������˼���ͨ
��ׯ�����κ����𣬴��з��������Ҳ�뷲��������ͬ����
Զ�����������������ڵ���������Ȯ���ţ��ò�����ͷ
һ���Լ��ĺ�Ư�����˼����ģ�������Ȼ�п�����Զ������
���ˣ�ż���������������ţ�����������Ʒǳ�æµ����ʱ
�أ���ǰ�������д�������֮��������Ǵ��и�Ů��æ�ŷ�
֯�޲�����������Ȼ����Ҹо���Ȼ������
LONG);

        set("exits", ([
                "west"          : __DIR__"changshengcunwest1",
                "east"          : __DIR__"changshengcuneast1",
                "north"         : __DIR__"changshengcunnorth1",
                "south"         : __DIR__"changshengcunsouth1",
                "out"           : __DIR__"changshengdao1",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/shuzhongxian" : 1,
                __DIR__"npc/wantong" : random(4),
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