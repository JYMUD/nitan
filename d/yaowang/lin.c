#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "Ũ������");
        set("long", @LONG
������һƬŨ�ܵ����֣�����Ĵ���������գ�ż���м���
����͸�������������ǿ�֦��Ҷ�����������������˲��������ա�
LONG
        );

        set("outdoors", "yaowang");
        setup();
}

void init()
{
        object me = this_player();

        if( (random(10) < 7)
        || !userp(me)
         || (query("family/family_name", me) == "yaowang" )
         || query_temp("been_recommend_to_yaowang", me) )
                return;

        call_out("do_ansuan", 2, me);
}

protected void do_ansuan(object me)
{
        int flag = random(10)<5?1:0, n;
        string *limbs;

        if( !me || (environment(me) != this_object()) )
                return;

        tell_object(me, sprintf(HIB"\nͻȻ��ಡ���һ�����������һֻ���ڡ�\n%s\n\n"NOR,
                flag?"��Ͻ�һ������˹�ȥ���³���һ���亹��":
                sprintf("һ�¶��������%s�ϡ�",(n=sizeof(limbs=query("limbs", me)))?
                limbs[random(n)]:"��")));

        if(!flag)
        {
                me->receive_damage("qi", 10);
                if(random(10) < 2)
                        me->apply_condition("yaowang_du", 2);
        }
}
