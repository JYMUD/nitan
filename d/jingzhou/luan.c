inherit ROOM;

void create()
{
        set("short", "�ҷظ�");
        set("long", @LONG
������һ���ҷظڣ����������˹��˸ߵĳ��ݣ���˵�����ֹ�
����û�˸�����һ�����������ŵ��������ë����
LONG );

        set("exits", ([
                "westup" : __DIR__"xiaoshan",
                "east" : __DIR__"luan2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7110);
	set("coor/y", -2010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}