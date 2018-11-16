inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "��ɽ֮��");
        set("long",@LONG
��ɽ֮������ɽ��߷壬�������߳�������������ص�������
�ٽ��ɷ�����������վ�ڸ߷�֮�ϣ�Զ�������ɵ����侰����ʤ�գ�
ʵ���������˼��κ������������������ɽ����Ȼ��������أ���
�����֣�ʱ��ʱ�͡����׶��������£��������˳����޾�����˼��
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("n_time", 600 + random(180)); 
        set("n_npc", 1); 
        set("n_max_npc", 8);
        set("s_npc", __DIR__"npc/dacaishen");
        
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
        
        if (playerp(this_player()) && ! this_player()->query("penglai/nanshan_quest/ok"))
        {
                tell_object(this_player(), HIG "\n�㱻һ����������ɽȥ ��������\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // ��һ����ɽ֮�߻�ȡһЩ����
        {
                if (! this_player()->query("penglai/nanshanzhidian_quest/ok"))
                {
                        tell_object(this_player(), HIR "\n���ҵ���ɽ֮�߷岢�������������������������5���Ǳ�ܼ�10���ʵս��ά����\n\n" NOR);
                        this_player()->add("potential", 50000);
                        this_player()->add("experience", 100000);
                        this_player()->set("penglai/nanshanzhidian_quest/ok", 1);
                        this_player()->save();
                }                
        }
}
