// liangong.c

inherit ROOM;

void create()
{
        set("short", "���䳡");
        set("long", @LONG
������һ����̫��Ժ�ӣ��Ƕ����书�ĵط����μ���Ȼ�������壬
���Ǻͽ���ȴ���Ÿ�ϵ���ϵ����˶μ�����������������֣���
��������������ĳ��ء����Ͼ���������Ժ��������ͨ����һ������
����
LONG );
        set("exits", ([
                "north" : "/d/dali/liangong2",
                "southeast" : "/d/dali/yongdao1",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren": 4,
        ]));
	set("coor/x", -19111);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}