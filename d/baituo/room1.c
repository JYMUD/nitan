//room1.c

inherit ROOM;
void create()
{
        set("short","������");
        set("long", @LONG
�����ǰ���ɽ���ӵ������ҡ��м����������µ�ľ������������
LONG );
        set("exits",([
                "out" : __DIR__"fang",
        ]));

        set("objects",([
                "/clone/npc/mu-ren" : 4,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
}