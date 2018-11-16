// Code of ShenZhou
// Summer 9/12/96
#include "room.h"

inherit ROOM;
int do_pray();
int do_pour(string);

void create()
{
        set("short", "��������");
        set("long", @LONG
������ǹ���������ľ��������ĵط�������ǰ��һ��ľ��(mua
n)�������Ͽ̵������շ�Ͱ˴����������������̽�ͭ�ߣ���ʽ����
С�ɡ�
LONG );
        set("exits", ([
                "west" : "/d/xueshan/houdian",
        ]));
        set("item_desc", ([
                "muan" : "ľ���Ϸ����˺��־��ɱ��µļ�����������ˮ���������͵ơ�ͭ
�衢ͭյ�ȹ�����\n",
        ]));
        set("objects", ([
                "/d/xueshan/npc/xiangke" : 2,
                "/d/xueshan/obj/lamp" : 1,
        ]));
        set("cost", 2);
        setup();
        set("outdoors","qilian-shan");
}
void init()
{
        add_action("do_pray","pray");
}

int do_pray()
{
    object ob, me = this_player();
    int check, wait_time = 0;
    remove_call_out("open_up");
    message_vision("$N�ĳ�����ع�����ĬĬ����\n", me);
 
    if( query_temp("marks/��", me)){
    set_temp("marks/��", 1, me);
    delete_temp("marks/��", me);
        }
    if( query_temp("marks/��", me) && interactive(me) && !me->is_fighting()){
           call_out("open_up", random(300)+300, me);
        }
    return 1;
}

int open_up(object me)
{
                object lamp;
            /* make sure that only when lamp is lighted, the door opens */
                if ( objectp(lamp = present("lamp", this_object())) ) {
                   if( query("burning", lamp)){
              message_vision("$N�ĳ�������������ã�ͻȻ�������״���һ��С�š�\n", me);
              set_temp("marks/��", 1, me);
              set("exits/enter", "/d/xueshan/tadi");
              call_out("close_up", 8, me);
                   }
                }
        return 1; 
}

int close_up(object me)
{
        message_vision("С��������غ����ˡ�\n", me);
        delete("exits/enter");
        delete_temp("marks/��", me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( !query_temp("marks/��", me )
         && !query_temp("marks/��", me) && dir == "enter" )
           return notify_fail("�����ⲻ�ϣ����ܽ��뱦����\n");
        else if( query_temp("marks/��", me) && dir == "south"){
           remove_call_out("open_up");
        }

        return ::valid_leave(me, dir);
}

