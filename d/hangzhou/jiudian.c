//Cracked by Roath
// /d/hangzhou/jiudian.c   ţ�Ҵ�Ƶ�
// by maco 99/12/22

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{        set("short", "�Ƶ�");
        set("long", @LONG
���������Ŷ�����С�Ƶ꣬���°������Ű������������ź��һ
��ҳ������װ��˸������С�Ƶ�������Ǹ����ӣ������������(f
ill)�������ƺ�Ҳûʲ���ɫ���޷���Щ�϶����������¾�֮�
LONG );

         set("exits", ([ /* sizeof() == 2 */
                   "west" : __DIR__"village",  
                 ])
         );

         set("objects", ([
                CLASS_D("taohua") + "/qusan" : 1  
         ]));

         set("cost", 1);
         set("outdoors", "hangzhou");

         set("coor/x", 3890);
        set("coor/y", -1800);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_fill", "fill");
}
int do_fill(string arg)
{
        object ob, obj, me = this_player();

        if (!objectp(obj = present("qu san", environment(me))))
        {        write("�ƹ�Ĳ��ڣ�\n");
                return 1;
        }

        if (!living(obj)){
                write("�㻹�ǵ��ƹ���ѹ�����˵�ɡ�\n");
                return 1;
        }

        if( !arg || !(ob=present(arg,this_player())) || !query("liquid", ob)){
                write("��Ҫ�Ѿ�װ���Ķ���\n");
                return 1;
        }

        switch (MONEY_D->player_pay(this_player(), 20)) {
        case 0: {
                write("��⵰��һ�ߴ���ȥ��\n");
                return 1;
                }
        case 2: {
                write("������Ǯ�����ˣ���Ʊ��û���ҵÿ���\n");
                return 1;
                }
        }

        if( query("liquid/remaining", ob) )
                message_vision("$N��"+ob->name()+"��ʣ�µ�"+query("liquid/name", ob)+
                "������\n", this_player());
        message_vision("$N��������ʮ��ͭ�塣\n������$N��"+ob->name()+"װ���վơ�\n", this_player());

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        set("liquid/type", "alcohol", ob);
        set("liquid/name", "�վ�", ob);
        set("liquid/remaining", query("max_liquid"), ob);
        set("liquid/drink_func", 0, ob);
        set("liquid/drunk_apply", 4, ob);
        return 1;
}