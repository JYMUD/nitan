inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
������һ����ɽ��С·��С·�����ֳ�һ�������ɽ·��Χ����
�ž���������ɽ�������ѣ����������˳�û�ڴˡ�
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "north"     : __DIR__"dongkou",
                "southwest" : __DIR__"xiaolu3",
        ]));
        set("objects", ([
                __DIR__"npc/shanzei2" : 1,
        ]));
        set("coor/x", -49950);
        set("coor/y", 20030);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}