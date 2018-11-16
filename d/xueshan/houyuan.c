inherit ROOM;

void create()
{
        set("short", "后院");
        set("long", @LONG
 这里是雪山寺的后院，后院不大，栽了几株参天雪松，在白晃晃
的雪山背景下，竟是飘然出世的心动。南边便是的练武场了。
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "northdown" : __DIR__"dilao",
                "south"     : __DIR__"chang3",
        ]));
        setup();
        replace_program(ROOM);
}