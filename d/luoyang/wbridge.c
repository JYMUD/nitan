inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���Ÿ߿��������Ǻ�֮�ϣ����ƷǷ���վ��������������ȥ��һ����
������Ļ��Ǻӽ�������Χ�ڵ��У������Ժ�������ͣ��������ֺܼ�̡�
���ϳ�ˮ������������Ϣ�����µĻ��Ǻ�ˮ�峺���ף�ʱ������Ծ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"xidoor",
                  "westdown" : __DIR__"guandaow1",
        ]));

	set("coor/x", -7060);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}