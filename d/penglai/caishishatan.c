inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "��ʯɳ̲");
        set("long",@LONG
��˵�����˳��������������ϴȥ���ϵ������Ͳ��ַ�����ɳ
̲�ϱ鲼���ֲ�ɫ����ʯ��Ͷ���������ʰ�쵵Ĺ�ʣ���Զ����
��ãã�Ĵ󺣡�
LONG);

        set("exits", ([
                "south"   : __DIR__"fanchendao",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("n_time", 40); 
        set("n_npc", 1); 
        set("n_max_npc", 8);
        set("s_npc", __DIR__"npc/xiaocaishen");
        
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