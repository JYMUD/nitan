// Room: /d/wuxi/chongandadian.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "�簲�´��");
        set("long", @LONG
�������й����ܽ����ɮ���о�֮�������ڶ��������������
��ʮ�ֵ��ϣ�����һȦ�����ִ�ط��񡣸߸ߵĵ�������Ʈ��
������ƣ��Ե��ر�����ء������˶�˵����������Ըʮ�ֵ����顣
LONG );
        set("no_beg", 1);
        set("exits", ([
                "out"  : __DIR__"chongansi",
        ]));
        set("objects", ([
                __DIR__"npc/laoheshang": 1,
        ]));
        set("coor/x", 1049);
	set("coor/y", -721);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}