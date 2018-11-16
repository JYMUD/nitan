inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG
�����˵������ߵ���Ҫ���������Ƿ��������ĵط�����˵��
ÿ���������߱����������ѡ�µķ�����˵���������Ѱ��֮��
��ͬ������Ҫ������Դ�ڽ�ɫɳ̲�Ľ�ɳ��ֻ��ιʵ��ɳ�������
������������ȥ����������һȺ���������У�׷����Ϸ��
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("n_time", 180); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/feima");
        
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
        
        if (userp(this_player()) && ! this_player()->query("penglai/nanshan_quest/ok"))
        {
                tell_object(this_player(), HIG "\n�㱻һ����������ɽȥ ��������\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // ��һ�η���������ridding 5LV
        {
                if (! this_player()->query("penglai/feimaya_quest/ok"))
                {
                        tell_object(this_player(), HIR "\n����ϸ�۲�����һ��һ���������������µ���⡣\n" NOR);
                        tell_object(this_player(), HIC "��ġ������������ˣ�\n\n" NOR);
                        this_player()->set_skill("riding", this_player()->query_skill("riding", 1) + 5);
                        this_player()->set("penglai/feimaya_quest/ok", 1);
                        this_player()->save();
                }
        }
}
