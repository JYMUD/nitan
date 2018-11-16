inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "���԰");
        set("long",@LONG
�����������ɵ������԰�������һ���꿪�����ٹ�һ�����
�����ÿ����ҳ��ֵ�ʱ��Ⱥ�ɱ�����ڴ˾�����Ҵ�ᡣ��Ȼ
ͬ��һ��������ÿ��������Ⱥ�ɲŻ������Ҵ��ۻ�һ�Σ�����
������ơ�
LONG);

        set("exits", ([
                "northeast"   : __DIR__"pantaoyuan2",
                "northwest"   : __DIR__"pantaoyuan3",
                "south"       : __DIR__"huixiandao",        
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("n_time", 30); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/mihou");
        set("objects", ([ 
                "/clone/npc/walker": 1,
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