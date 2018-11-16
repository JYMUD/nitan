inherit ROOM;

#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"

void create()
{
        set("short", "��ɽ����");
        set("long",@LONG
����ͨ����������ɽ�ıؾ�֮·����˵��ɽ�����������ɷ���
�ط������ڽ��ء������˿��أ�����û�����˵�ָ��������������
��Ҳ�޷�����ġ�����ֲ�����������Χ�ƣ������������ˡ�̧ͷ
������ɽ��ɽ����ʣ��������ƣ���һϸ�����������֣���������
��ĥ��
LONG);

        set("exits", ([
                "north"    : __DIR__"xianrenzhilu",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);
        
        setup();
}

void init ()
{
        add_action("do_closeeye", "closeeye");
        
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
                tell_object(this_player(), HIG "\n������������ɽ��ȴ�����������û����ɽ֮·�����գ���\n" NOR);
        }
        else
        {
                tell_object(this_player(), HIG "\nҪ������ɽ����������۾�(closeeye)��Ĭ����·���˽̸�������\n" NOR);
        }
}

int do_closeeye(string arg)
{
        object me;
        int i;
        object *inv;
        object horse, person;
        
        
        me = this_player();
        
        if (me->is_busy())
                return notify_fail("����æ��\n");
                
        // ����������˱�������
        if (objectp(horse = me->query_temp("is_riding")))
        {
                if (objectp(person = horse->query_temp("is_rided_follow")))
                        person->delete_temp("is_riding_follow");

                horse->delete_temp("is_rided_follow");
                horse->delete_temp("is_rided_by");
                me->delete_temp("is_riding_follow");
                me->delete_temp("is_riding"); 

                message_vision(HIR "\n$N��" + horse->name() + HIR " �ƺ��ܵ��˾��ţ�ǰ��һ�������"
                               "����������\n\n" NOR, me);

                return 1;
        }
                        
        // �ѱ�����û�������
        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // ���˱�����û�
                inv[i]->move(__FILE__);                
        }

        if (this_player()->query("penglai/nanshan_quest/ok"))
        {
                i = 20;
                tell_object(this_player(), HIG "\n���������۾���Ĭ����·���˽̸��������...\n" NOR);
                if (! MEMBER_D->is_valib_member(this_player()->query("id")))
                        return notify_fail("�Բ�����ɽ��ͼֻ����Ч��Ա���š�\n");
                        
                me->move(__DIR__"nanshanzhong" + random(i));
        }
        else
        {
                return 0;
        }

        return 1;
}