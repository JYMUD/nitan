inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
����һ��������ֱ����������Ĵ�ٵ�������ݵ���ʮ���ۡ�����
ͨ���Դ������ǣ�������Զ���Ƕ��������ų��ˡ�
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"guandaos4",
                  "south" : __DIR__"guandaos6",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}