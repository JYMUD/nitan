//Room: baihu1.c

inherit ROOM;

void create ()
{
        set ("short", "�׻���");
        set("long", @LONG
�׻����ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·����
�˱ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء������Ƿ����������
������ɭɭ�Ĵ��Σ��м���������������Ĵ����ſڡ�
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "west" : "/d/changan/fufeng1",
                "east" : "/d/changan/baihu2",
        ]));

        set("objects", ([
                "/clone/npc/xunbu" : 2,
        ]));
        set("outdoors", "changan");
        set("no_fight", 1);
        set("coor/x", -10730);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}