inherit DEMONROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG       
�����˴�˵������֮һ���Ŵ���˵����������������Ϊ��
�飬��ë�ද��֮��������������˼��û�����Է���ҲҲ������
�������롣������һ�����ڣ�������ȥ�ǿ����Ĵ󺣣��򱱸��
���ȣ����з���Ҳ�������ư��С��żȻ���ɼ�����֮������Ӱ��
������֪�ǲ��Ǵ�˵�е������ޡ��ȵ�һƬ������ƣ����ƽ���
�ȵ������±�֮�ϣ���ҫ��ѣĿ�Ĺ�ʣ���˵����ȵײ���һֻǧ
�����󣬿������޳������˰ɡ���ͻȻ���û�����ƮƮ�ģ���һ��
�����������tiao����ȥ�ĳ嶯��
LONG);

        set("exits", ([
                "northdown"     : __DIR__"feilonggu2",                                
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

        set("n_time", 600 + random(180)); 
        set("n_npc", 1); 
        set("n_max_npc", 6);
        set("s_npc", __DIR__"npc/jinseqilin");
        
        setup();
}

void init ()
{
        add_action("do_tiao", "tiao");

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

int do_tiao(string arg)
{
        object me = this_player();

        message_vision(HIW "\n$N" HIW "����һ�������������������� ����\n", me);
        
        if (random(2))
        {
                tell_object(me, HIG "ͻȻ�䣬��ֻ���û���Ʈ������һ���������� ����\n" NOR);
                me->move(__DIR__"bianqueju");
                return 1;
        }
        tell_object(me, HIY "�������ϣ�����������ܹ�֧�����������������������Ʈ�䵽�ȵ� ����\n\n" NOR);
        
        me->move(__DIR__"gudi");

        return 1;         
}