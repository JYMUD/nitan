inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long", @LONG
������һ���ľ��Ļ������ڣ�ż���������������д����������
����У�԰�������Ÿ�ʽ���������滨�ݡ����̾գ��������ž顢ĵ
������
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "out" : "/d/jingzhou/zizhulin1"
        ]));
        set("objects",([
                "/d/jingzhou/obj/lvju" : 3,
                "/d/jingzhou/npc/obj/juhua" : 1,
        ]));

        set("coor/x", -7091);
	set("coor/y", -2101);
	set("coor/z", -11);
	setup();
        replace_program(ROOM);
}