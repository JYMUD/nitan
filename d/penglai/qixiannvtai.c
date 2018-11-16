inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "����Ų̊");
        set("long",@LONG
������һ�����ʵ�ƽ̨����˵������Ů�������������ɷ�����
����ȥ�����֮����һ���ʺ绮�ն�������λ��ò�ޱȵ���Ů����
�����裬������ȣ������������������������
LONG);

        set("exits", ([
                "down"    : __DIR__"nanshanjiaoxia",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("no_fight", 1);
        set("sleep_room", 1);
        
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
        
        if (! this_player()->query("penglai/nanshan_quest/ok"))
        {
                tell_object(this_player(), HIG "\n�㱻һ����������ɽȥ ��������\n" NOR);
                this_player()->move(__DIR__"nanshanjiaoxia");
        }
        else // ��һ������Ų̊������ò1��
        {
                if (! this_player()->query("penglai/qixiannvtai_quest/ok") && this_player()->query("per") < 30)
                {
                        tell_object(this_player(), HIR "\n�㿴��������Ů�����ʢ�������治ǳ��\n" NOR);
                        tell_object(this_player(), HIC "��ġ���ò�������ˣ�\n\n" NOR);                        
                        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" HIY + this_player()->name() + "(" + 
                                                             this_player()->query("id") + ")" HIM "�������ɵ�"
                                                             "����������Ů�����ʢ�������治ǳ��\n" NOR);   
                        this_player()->add("per", 1);
                        this_player()->set("penglai/qixiannvtai_quest/ok", 1);
                        this_player()->save();
                }
        }
}
