inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long", @LONG
�㿴�����ܷ������£�������һ�������˶����԰�ӣ���������
����ͻҳ���ʹ�˲��ɵ���Ȼ���ˡ�
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                  "south" : __DIR__"dongdajie2",
        ]));
        set("objects", ([
                "/d/jingzhou/npc/qigai" : 1,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7080);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
 