//Room: yamen.c

inherit ROOM;

void create ()
{
        set ("short", "���Ŵ���");
        set("long", @LONG
���ǳ����ǵ����Ŵ��ţ�Ҳ�ǳ�������ߵ��������������︺��
�������Ĵ���С�顣������͵��������С�������ǷŻ�ɱ�˵�ǿ����
�����������ܵ�Ӧ�еĴ�����ǽ������һ�Ÿ�ʾ(gaoshi)
LONG );
        set("item_desc", ([
                "gaoshi": ""
        ]) );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/yamen-datang",
                "north" : "/d/changan/qinglong3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/yayi" : 4,
        ]));

        set("coor/x", -10710);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}