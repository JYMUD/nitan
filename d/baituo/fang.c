inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����ǰ���ɽ���ӵ��������������м������䣬�������ҡ�����
��������������գ����Բ��������˴����
LONG );
        set("exits",([
                "west" : __DIR__"liangong",
                "1"    : __DIR__"room1",
                "2"    : __DIR__"room2",
                "3"    : __DIR__"room3",
        ]));

        set("objects",([
                __DIR__"npc/trainer" : 1,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}