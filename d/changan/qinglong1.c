//Room: qinglong1.c

inherit ROOM;

void create ()
{
        set ("short", "������");
        set("long", @LONG
�������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·����
�˱ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�������һ���ܾ߹�ģ
����Ժ��ż�����̾�֮��������
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "south" : "/d/changan/baoxiangsi",
                "west" : "/d/changan/fufeng5",
                "east" : "/d/changan/qinglong2",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10730);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}