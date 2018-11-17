inherit ROOM;

void create()
{
        set("short", "松樹林");
        set("long", @LONG
你走進了一片濃密的松樹林，前面已經沒有了道路，你必須不時
砍斷橫在你面前的枝椏。林內光線黑暗，靜的能聽到你自己的心跳聲，
只有你踩在地上厚厚的松針和枯枝上發出的沙沙聲。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"sl3",
                "southwest" : __DIR__"sl4",
                "west" : __DIR__"sl1",
                "southeast" : __DIR__"sl5",
        ]));

        setup();
        replace_program(ROOM);
}