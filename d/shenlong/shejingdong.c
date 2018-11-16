#include <ansi.h> 
#include <room.h>  
inherit CREATE_CHAT_ROOM; 
int is_chat_room() { return 1; }  

void create()
{
        set("short", "�߾���");
        set("long",@LONG
�˴����߾�������������ֲ����Ĵ��ɼ���ɫ�ĺ��ǣ���Χ����
���ߣ�������ʱ�ص��·�����Һ�壬����˵أ�������һ��Ī���Ŀ�
�壬��˵����ͷ�߾��Ͳ��ڴ˶����

LONG);


        set("exits", ([
                "out"  : __DIR__"shedong4.8",
        ]));

        set("no_rideto",1);
        set("no_flyto", 1);
        set("no_clean_up", 1);
        setup();

}

// �������Ƿ��Ѿ��μӹ��߾�ս
void init()
{
        object me = this_player();

        // 24Сʱֻ�ܲμ�һ��
        if (time() - query("boss/shejing", me) < 2 * 3600 && userp(me) && !wizardp(me)  || query("schedule", me) || query("doing", me) == "trigger")
        {
                tell_object(me, HIG "\n�Բ�����μ��߾��Կ�ս���ʱ����2Сʱ(Ҳ��׼�ƻ���������ȡ���ƻ������д���)��\n");
                tell_object(me, HIC "������ϴβμ��߾��Կ�ս����� " + HIY +
                                  sprintf("%d", (time() - query("boss/shejing", me)) / 3600) + HIC " Сʱ��\n\n" NOR);
                me->move(__DIR__"shedong4.8");
                return;
        }

        // ���òμ�ʱ��
        tell_object(me, HIG "\n������߾���׼���μӶԿ��߾�ս�����벻Ҫ�뿪������2Сʱ���޷��ٴν��롣\n" NOR);
        set("boss/shejing", time(), me);

        me->save();

        return;
}

void start_move()
{
        object *ob;
        int i;

        ob = all_inventory(this_object());

        // ����峡��־
        delete("doing");

        if (! sizeof(ob))return;

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character())
                {
                        destruct(ob[i]);
                        continue;
                }

                if( query("id", ob[i]) == "jiutoushejing" )
                        continue;

                ob[i]->move("/d/shenlong/shedong4.8");
        }

        return;
}

// �����߾��ļ��ĺ��У����߾��������ӳٽ����з����ڵ�ID
// �ƶ����߾����⣬��delay_time = 0 ���ӳ�
void move_all_player_out(int delay_time)
{
        if (! delay_time)
        {
                start_move();
        }
        else
        {
                remove_call_out("start_move");
                call_out("start_move", delay_time);
        }

        return;

}
