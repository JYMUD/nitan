inherit ROOM;

void create()
{
        set("short", "�ප");
        set("long", @LONG
������һ��СС�Ĳප������������ױ̨���ϱ����ҵİڷ���Щ
Ů�˵���Ʒ��
LONG );
        set("exits", ([
                "east" : __DIR__"dongnei",
        ]));
        set("objects", ([
                __DIR__"npc/jinhua" : 1,
        ]));
        set("coor/x", -49960);
        set("coor/y", 20050);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}