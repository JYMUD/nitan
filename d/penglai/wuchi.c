inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "���");
        set("long",@LONG
�⵺�ϵ�������Դͷ��������أ��������в���ӿ����ɫ����
����Ȼ����Щ���������˵��ϵ�������Ϊ����������������������
������Ʈ�������ס������xi����һ�ڡ�
LONG);

        set("exits", ([
                "west"   : __DIR__"xianqimen",
                "east"   : __DIR__"tianxiandao1",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������

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

int do_xi()
{
        object me = this_player();
        
        if (! me->query("penglai/wuchi_quest/ok"))
        {
                message_vision(HIM "$N" HIM "���������һ������е����� ����\n" NOR, me);
                tell_object(me, HIG "��ϲ�㣬�����������ˡ�\n" NOR);
                me->set("penglai/wuchi_quest/ok", 1);
                me->add("magic_points", 5000);
                me->save();
                return 1;
        }
        tell_object(me, HIC "������һ�ڳ���������������̩�ޱȡ�\n" NOR);
        return 1;
}