inherit ROOM;

void create()
{
        set("short", "�ݴ�");
        set("long", @LONG
�������Ҳݴԡ��������ȹ�����С���š��������涼�������ߵ�
��ݣ������߳�û��
LONG );
        set("exits", ([
                "west" : __FILE__,
                "north" : __DIR__"cao2",
                "east" : __DIR__"ximen",
                "south" : __FILE__,
        ]));
        set("objects", ([
                "/clone/beast/jinshe" : random(2),
        ]));
        set("quarrys", ([
                "caihuashe"  : 100000,
                "dushe"      : 50000,
                "jinshe"     : 40000,
                "qingshe"    : 40000,
                "yanjingshe" : 5000,
                "mangshe"    : 3000,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -50000);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}
