inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���Ǹ����ȣ����ȵķ����Ϲ���һ������Сͭ�壬������з���
��ද����������
LONG );
        set("exits", ([
                "north" : __DIR__"huayuan",
                "south" : __DIR__"liangong",
        ]));
        set("objects", ([
                __DIR__"npc/guanjia" : 1,
        ]));
        set("outdoors", "baituo");
        set("coor/x", -49980);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}