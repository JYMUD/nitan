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
        "northeast" : __DIR__"zhuang3",
        "southeast" : __DIR__"zhuang5",
]));
        setup();
}
