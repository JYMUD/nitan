inherit DEMONROOM;

#include <ansi.h>

int i = 20;

void create()
{
        set("short", "��ɽ��");
        set("long",@LONG
�����������ɵ����������ɷ��ĵط�����˵��ɽ�������ڣ���
������ʩ������ɡ�����������ʢ��ԭ����Ϊ��ɽ����ͨ��ɽ���죬
ȴ��֪��������֮����һ��������ɽ֮�У�Ψһ�ĳ�·���ǻص�
ɽ���£���վ�����òŷ��֣�����֮������һ�ɲ��䣬����������
������ʱ��ʱ�ͣ�ʱ��ʱ�֡���ʱ��������ܵ�����ʲô����������
��ʱȴ���Ŵ˴������ߣ����������������������¡���˵��������
���������������ϱ仯��ʱ�򣬿����ҵ�ȥ��ɽ֮�ߵ�·��������
�Ļ����ᷢ�ִ�˵�е�����̨�ͷ����¡�
LONG);

        set("exits", ([
                "xunlu"    : __DIR__"nanshanzhong0",
                "out"      : __DIR__"nanshanjiaoxia",
        ]));
        
        // ��ɽ֮��
        if (random(20) == 1)
                add("exits", ([ "nanshanzhidian" :  __DIR__"nanshanzhidian",]));
        
        // ����Ų̊�ͷ�����
        if (random(10) == 1)
                add("exits", ([ "qixiannvtai" :__DIR__"qixiannvtai",]));
        if (random(10) == 1)
                add("exits", ([ "feimaya" : __DIR__"feimaya",]));

        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("n_time", 60); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/nianshou");
        set("objects", ([ 
                "/clone/npc/walker": 6,
        ]));
        setup();
}

void init ()
{
        add_action("do_xunlu", "xunlu");
        
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

int do_xunlu()
{
        object me;
        
        me = this_player();
        
        if (me->is_busy())return notify_fail("����æ��\n");
        
        tell_object(this_player(), HIG "\n������ɽ���Ĵ��߶�Ѱ���µĵ�· ...\n\n" NOR);

        me->move(__DIR__"nanshanzhong" + random(i));

        return 1;
}