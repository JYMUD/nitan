inherit ROOM;

void create()
{
        set("short", "�Ǳ���");
        set("long", @LONG
���Ÿ߿��������Ǻ�֮�ϣ����ƷǷ���վ��������������ȥ��һ����
������Ļ��Ǻӽ�������Χ�ڵ��У������Ժ�������ͣ��������ֺܼ�̡�
���ϳ�ˮ������������Ϣ�����µĻ��Ǻ�ˮ�峺���ף�ʱ������Ծ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"beidoor",
                //"north" : __DIR__"guandaon1",
                "north" : __DIR__"road5",
        ]));

	set("coor/x", -6990);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}