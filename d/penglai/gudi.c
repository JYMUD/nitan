inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "�����µ�");
        set("long",@LONG
���ô˴�����ͷһ����ԭ�������¾����ͦ�Σ�ֱ����������
�˾�̾���µ׷羰����������������������������ֻ��ֻ���ķ���
����ͷ����������Զ����һ��Բ�ε�ʯͷ���߽�һ�������羵��һ
�㽫��ʴ��Ĺ�â����ڴˣ�Ͷ�䵽���ܡ���Զ����һ�����٣���
��˳������pa���������¡�
LONG);

        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 0);
                
        setup();
}

void init ()
{        
        add_action("do_pa", "pa");
        
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

int do_pa(string arg)
{
        object me = this_player();
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("������æ���ء�\n");
        
        message_vision(HIY "$N" HIY "ʩչ�Ṧ��˳�����ټ������ĸ��������ɵ����������� ����\n", me);
        
        me->move(__DIR__"qilinya");
        
        return 1;
                
}