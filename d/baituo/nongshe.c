inherit ROOM;

void create()
{
        set("short", "ũ��");
        set("long", @LONG
������һ��Сũ�ᣬ�Ҿߺ��¡��������˱Ƚϸ�ԣ��
LONG );
        set("exits", ([
                "west" : __DIR__"guangchang",
        ]));
        set("objects",([
                __DIR__"npc/woman" : 1,
        ]));
        set("coor/x", -49980);
        set("coor/y", 19980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}