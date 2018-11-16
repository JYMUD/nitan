#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","�Ⱥ�����");
        set("long",@LONG
�����������дУ����ﻨ�㣬���ߴ���Ҷ�ķ�϶����
���أ�΢�紵������Ӱһ����涡�����ȫ������һƬ��
ɫ���ڱ��̵ĺ����У��㽥������ʧ�˷���
LONG
        );
        set("exits",([
                "east":__FILE__,
                "west":__FILE__,
                "north":__FILE__,
                "south":__FILE__,
        ]));
        set("snake_count",5);
        set("outdoors", "jianzhong");
        set("coor/x", -400);
        set("coor/y", -420);
        set("coor/z", 0);
        setup();
}
void init()
{
        object ob1,ob2;
        object me=this_player();
        if( (random(10)<2) && (query("snake_count", this_object())>0) && (query_temp("dugu_visit", me) != 0) && (!present("pusi qushe",environment(this_player()))) )
        {        
                ob1=new(__DIR__"npc/pusiqushe");
                ob1->move(this_object());
                addn("snake_count", -1, this_object());
        }
}
int valid_leave(object me, string dir)
{
        int i;
        string msg;
        if( !query_temp("dugu_visit", me) )
        {
                if(dir=="north")
                {i=query_temp("zhongnan/tree", me);
                        if( (i>0) && (i<10))addn_temp("zhongnan/tree", -1, me);
                        if( (i>9) && (i<12))addn_temp("zhongnan/tree", 1, me);
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="south")
                {i=query_temp("zhongnan/tree", me);
                        if((i<4)||(i==14)) 
                       {        addn_temp("zhongnan/tree",1,me);} else addn_temp("zhongnan/tree",-1,me); 
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="east")
                {i=query_temp("zhongnan/tree", me);
                        if((i>3)&&(i<10))
                       {        addn_temp("zhongnan/tree",1,me);} else addn_temp("zhongnan/tree",-1,me); 
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if(dir=="west")
                {i=query_temp("zhongnan/tree", me);
                        if((i>11)&&(i<14))
                                addn_temp("zhongnan/tree", 1, me);
                        if( i<0)set_temp("zhongnan/tree", 0, me);
                }
                if( query_temp("zhongnan/tree", me) >= 15 )
                 {
                                 me->move(__DIR__"donghou");
                           delete_temp("zhongnan/tree", me);
                        message("vision",query("name", me)+"һ�����ݵش����������˳�����\n",environment(me),me);
                             return notify_fail("�����˰��죬�����߳�����Ƭ���֡�\n");
                 } else
                if( query_temp("zhongnan/tree", me)<i )
                {
                        message("vision",query("name", me)+"���ҵ���������������ȥ��\n",environment(me),me);
                        msg="�����˼������������߽������ֵĸ����\n";
                } else
                if( query_temp("zhongnan/tree", me) == i )
                {
                        message("vision",query("name", me)+"��������֣�����һ������߻���ԭ�ء�\n",environment(me),me);
                        msg="����������֣�����һ������߻���ԭ�ء�\n";
                } else
                {
                        message("vision",query("name", me)+"�ƺ����г��������������\n",environment(me),me);
                        msg="�����˼���������������ƺ������߹���\n";
                }
                return notify_fail(msg);//::valid_leave(me,dir);
        }else 
        if( query_temp("dugu_visit", me) == 1 )
        {        if(dir=="north")
                {
                        message("vision",query("name", me)+"���������ȥ����ʧ����֮�С���\n",environment(me),me);
                        me->move(__DIR__"qiaobi");
                        delete_temp("dugu_visit", me);
                        message("vision",query("name", me)+"�����������˹�����\n",environment(me),me);
                        return notify_fail("��������������������һ���ͱ�֮ǰ��\n");
                } else
                {
                        message_vision("$N���������Ų����У����߱����ͷ羰��\n",me);
                        return ::valid_leave(me,dir);
                }
        }
}
