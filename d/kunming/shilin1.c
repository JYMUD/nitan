inherit ROOM;

void create()
{
        set("short", "��ʫ��");
        set("long", @LONG
������ʯ�������İ�ʫ��壬�ഫ�ܾ���ǰ�������Ĺ���
����ﰢʫ���ڴ˵Ⱥ����İ��ڸ磬Ȼ������ȴ�������ϲ�ɱ
���ˣ���ʫ��Ȱ��ȣ�ʼ��û�е����İ������ɣ��վ�������
һ��ʯ�壬��Զ���غ���ȥ��
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "north" : __DIR__"shilin", 
                "west"  :__DIR__"shilin2",
        ]));
        set("objects", ([
                "/d/wudu/npc/youngboy" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}