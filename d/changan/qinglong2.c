//Room: qinglong2.c

inherit ROOM;

void create ()
{
        set ("short", "������");
        set("long", @LONG
�������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·����
�˱ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء��������ǹʻʹ��Ľ�
ˮ���ˣ�������һ����·ͨ�򳤰������š�
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "north" : "/d/changan/bridge2",
                "south" : "/d/changan/nanan-dadao",
                "west" : "/d/changan/qinglong1",
                "east" : "/d/changan/qinglong3",
        ]));

        set("objects", ([ //sizeof() == 3
               "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}