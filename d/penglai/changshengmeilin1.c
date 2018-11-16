inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "����÷��");
        set("long",@LONG
�˴��������ɵ���÷�֣������볤����ܽ�������ȡ��
Ϊ����÷�֡��ߵ����÷�����˱�֮�����ѽ�͸ȫ�����
���������泩�ޱȡ���˵�������÷��ÿ��һ��ʱ������
�ڵ��ϣ���Щ÷���������������������𽥳ɳ������ձ�
��һ�ֽ���÷�Ĺ�ʵ��������÷��������������ɵ���÷��
�����˼����Ʒ�������ġ�
LONG);

        set("exits", ([
                "southwest"    : __DIR__"caiyunjian2",        
                "northeast"    : __DIR__"changshengmeilin2",
                "east"         : __DIR__"changshengdao1",                
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        
        set("n_time", 20); 
        set("n_npc", 2); 
        set("n_max_npc", 10);
        set("s_npc", __DIR__"npc/xique");
                
        if (random(2) == 1)
        {
                if (random(2) == 1)
                        set("objects", ([
                                __DIR__"obj/meihua" : 1 + random(3),
                        ]));
                else
                        set("objects", ([
                                __DIR__"obj/qingmei" : 1 + random(4),
                        ]));                        
        }
        
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