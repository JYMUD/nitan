
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��Ϣ��");
        set("long", @LONG
�����ǻش��õ���Ϣ�ң���������ҩ�����ú�ҽʦ��Ϣ�ĵط���
�����ڷ������ŵĴ��̣���������ˣ�����������˯һ�����
LONG );
        set("no_fight", 1);
        set("sleep_room", 1);
        set("exits", ([
                "east" : __DIR__"beiting",
        ]));

        create_door("east", "ľ��", "west", DOOR_CLOSED);
        setup();
}
