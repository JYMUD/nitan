// woshi.c ����������

#include <room.h>
#include <ansi.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "����");
        set("long", @LONG
�������˵����ң���ʰ�þ����������ϴ�����һ�Ŵ󴲣�������һ��
���ӡ��ƿ��������Կ�������Ļ�԰�������ᵽ�����㣬�ǳ���⡣Զ
����һ��Ƭ���֡�
LONG );

        set("default_long", "�������˵����ң���ʰ�þ����������ϴ�����" /* EXAMPLE */
                            "һ�Ŵ󴲣�������һ�����ӡ��ƿ��������Կ�" /* EXAMPLE */
                            "������Ļ�԰�������ᵽ�����㣬�ǳ����" /* EXAMPLE */
                            "��Զ����һ��Ƭ���֡�");                   /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "down" : __DIR__"jusuo",
        ]));

//**    set("objects", ([
//**            "/adm/npc/obj/xiang" : 1,
//**    ]));

//**    set("sleep_room", 1);
//**    set("loving_room", 1);
        set("no_fight", 1);
        setup();
//**
//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
//**    add_action("do_findbaby", "xunzhao");
}

int do_findbaby(string arg)
{
        object me = this_player(), baby;
        string file;

//**    if (! arg || (arg != "baby" && arg != "child") ||
//**        ! is_room_owner(me)) 
                return 0;

        if( !query("couple/child_id", me) )
                return notify_fail("���ֻ�û�к��ӣ��������ʲô���ְ���\n");

        if( objectp(baby=find_living(query("couple/child_id", me)) )
        &&  environment(baby) && baby->is_baby())
                return notify_fail("���ǵĺ����Ѿ��ܳ�ȥ���ˣ��ú��Ĵ����Ұɣ�\n");

        if( query("gender", me) == "Ů��" )
                file=read_file("/data/baby/"+query("id", me)+".o");
        else file=read_file("/data/baby/"+query("couple/couple_id", me)+".o");

        if (stringp(file))
        {
                baby = new("/clone/user/baby");

                baby->load_baby(me);
                baby->move(environment(me));
                message_vision("���Ȼ����������" +
                        ({"̽��һ��С�Թ�", "���һ˫С��Ѿ", "���һ֧С��"})
                        [random(3)] + "������\n", me);

        } else
        {
                tell_object(me, MAG "���ǵĺ��Ӳ���ز���ˣ���ڰ��ɡ�\n" NOR);
                delete("couple/child_id", me);
                delete("couple/child_name", me);
        }
        return 1;
}      
