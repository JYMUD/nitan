inherit ROOM;
void create()
{
        set("short", "Ǯׯ");
        set("long", @LONG
����һ�����ֺŵ�Ǯׯ�����м��������ʷ����ȫ�����ض��з�
�ꡣ�����е���Ʊ�����ǳ��ã�ͨ��ȫ����
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"beidajie1",
        ]));
        set("objects", ([
                __DIR__"npc/qian" : 1
        ]));

        set("coor/x", -7110);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}