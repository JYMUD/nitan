// pubu.c 
// Modified by Winder June.25 2000

inherit ROOM;

#include <ansi.h>
void create()
{
        set("short", "����ٲ�");
        set("long", @LONG
ѭС·ֱ����ɽ���������ˮ�����������¡¡�����糱ˮ����
һ�㣬̧ͷһ����ֻ�����������������ӵ�����һ�����ٲ��Ӹ�����ֱ
к���������֮ǰ���ǽ�������������������ȣ�������������������
ͷ��������
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "southdown" : "/d/wuliang/road6",
        ]));
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("coor/x", -71020);
        set("coor/y", -79870);
        set("coor/z", 110);
        setup();
}
 
void init()
{
        add_action("do_jump","jump");
}

int do_jump(string arg)
{
        object ob;
        int new_jing;
        ob = this_player();
        if( query_temp("marks/wuliang", ob) != 1 )
                return notify_fail("����׷ɱ�㰡����ô����Ҫ������ɱ��\n");
        new_jing=random(query("max_jing", ob)*3);
        if( new_jing>query("jing", ob))new_jing=query("jing", ob)+1;
        if( !arg || arg=="" ) return 0;
        if( arg != "down" )
                return notify_fail("����Ҫ������ɱ����ô�벻������\n");
        tell_object(ob, HIR"�㲻��˼��������һԾ�����������¡�������\n"NOR);
        message("vision",NOR"ֻ��"+query("name", ob)+"�����ң���������������֮�С�������\n"NOR,environment(ob),ob);
        if( (random(query("kar", ob))<5) && (ob->query_skill("dodge")<30) )
        {
                ob->die();
                return 1;
        }
        addn("jing", 0-new_jing, ob);
        ob->move(__DIR__"yanfeng");
        return 1;
}