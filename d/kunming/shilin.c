inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
���ﴣ���Ÿ��ָ�����״�����ʯͷ���е����ˣ��е���
�����е����������߿�����������Ҳ�����Ƕ�������
���ģ�ǧ�˰�̬�������۾��������ˡ�
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "north" : __DIR__"xiaolu", 
                "south"  :__DIR__"shilin1",
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
	set("coor/x", -16770);
	set("coor/y", -7200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}