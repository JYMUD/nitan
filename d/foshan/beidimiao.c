inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������������ϡ�Ժ����һ����ˮ��������ʯ��ʯ�ߣ���Ȼ�̾ᡣ
�������ʯ����Ѫ����Ȼ�������������ڴ������С�
LONG );
        set("exits", ([
                "south"  : __DIR__"street1",
        ]));
	set("coor/x", -6590);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}