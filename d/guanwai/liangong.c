// liangong.c ������

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����������������������һЩ�����߳��õ�ľ�ˡ������ƺ�����
һ�䷿�ӡ�
LONG );
        set("exits", ([
                "east" : __DIR__"liangonge",
                "west" : __DIR__"houyuan",
                "south": __DIR__"liangongs",
        ]));
        set("for_family", "�������");
        setup();
        replace_program(ROOM);
}