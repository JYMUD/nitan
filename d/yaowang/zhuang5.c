inherit __DIR__"zhuang";

void create()
{
        set("short", "÷��׮һ");
        set("long", @LONG
һ�˶�ߵ�÷��׮��������ȥ�������ľ�������
LONG
        );

        set("exits", ([
        "down" : __DIR__"lianwu",
        "northwest" : __DIR__"zhuang4",
        "east" : __DIR__"zhuang6",
]));
        setup();
}
