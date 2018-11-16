// Room: /d/kunlun/kuhanlou2.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void init();
int do_duanmo(string arg);

void create()
{
        set("short", "�ຮ¥����");
        set("long", @LONG
ÿ��¥���϶������˽�ʵ��ľ¥�壬�˽��ε�ǽ�����������ȴ�
��������ǽ�������������������ź͸��ֵĻ��񣬲���ר�ŵ����ּ���
�����ǵ��¼�������������������ֻ�ܿ���Χ�����ܵ��������ѵ���ɼ
�֣�����ͨ�������̼��ͺ������Ĺ����İ취����ö���ѧ���β����
׷��
LONG );
        set("exits", ([
                "up"   : __DIR__"kuhanlou3",
                "down" : __DIR__"kuhanlou1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -119980);
        set("coor/y", 40130);
        set("coor/z", 100);
        setup();
}

void init()
{
        set("times", random(20));
        set("item_count", 2);

        add_action("do_duanmo", "duanmo");
        add_action("do_duanmo", "see");
}

int do_duanmo(string arg)
{
        object ob, me = this_player();

        if( query("kar", me)<20 )
                return notify_fail("��Ҫ��ʲô��\n");

        if ( !arg && (arg != "huaxiang") && (arg != "wall") )
                return notify_fail("����Ҫ��Ħʲô������\n");

        if ( query("item_count") < 1 ||
                query_temp("count", me) <= query("times") )
        {
                addn_temp("count", 1, me);
                me->receive_damage("jing", 10);
                me->receive_damage("qi", 10);
                return notify_fail("����ϸ��Ħ������ǰ�����˵Ļ����������ǵ����ݺὭ����������𣬲��������������п���\n");
        }

        if ( query("item_count") > 0)
                switch( random(2) )
                {
                        case 0:
                                addn("item_count", -1);
                                ob = new("/d/kunlun/obj/weiqi");
                                ob->move(me);
                                delete_temp("count", ob);
                                break;
                        case 1:
                                addn("item_count", -1);
                                ob = new("/d/kunlun/obj/guzheng");
                                ob->move(me);
                                delete_temp("count", ob);
                                break;
                }
        return 1;
}

int valid_leave(object me, string dir)
{

        if( dir == "up")addn_temp("count", 1, me);
        else addn_temp("count", -1, me);
        return ::valid_leave(me, dir);
}
