// ���� huapu1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "����");
        set("long", @LONG
�����Ǻ����ȵĻ��ԣ��ǡ��������ȡ�����ţ�����ָ��ָ���ҩ
�ĵģ�������������㻨�ݡ�
LONG );

        set("outdoors", "������");

        set("exits", ([ 
                "west" : __FILE__,
                "east" : __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));

        setup();
}

void init()
{
        object ob;
        int jing, jing_cost;

        ob = this_player();
        jing=query("jing", ob);
        jing_cost=random(query("kar", ob))*2+10;

        addn("jing", -jing_cost, ob);
        if(jing < jing_cost)
         ob->unconcious();
}

int valid_leave(object me, string dir)
{
        if (random(10) > 5)
              addn_temp("mark/steps", 1, me);
        if (random(10) < 5)
              addn_temp("mark/steps", -1, me);
        
        if( query_temp("mark/steps", me) >= 5){
            me->move(__DIR__"caojing");
            delete_temp("mark/steps", me);
              return notify_fail("������һ������Ȼ��ǰһ��������һ���ݾ���\n");
        }  
        if( query_temp("mark/steps", me) <= 0){
            me->move(__DIR__"niupeng");
            delete_temp("mark/steps", me);
              return notify_fail("���۵ð�����ȴ��Ȼ�������߻���ţ�\n");
        }      
        return ::valid_leave(me, dir);
}