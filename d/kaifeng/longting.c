inherit ROOM;

void create()
{
        set("short", "��ͤ���");
        set("long", @LONG
��ͤ���ԭ���ǵ����й���������֮�󣬹����Ƿϣ������ڴ˵�
�����������䱦�ֳ¸���ֱ��������̾Ϊ��ֹ�����ϱ������
֮��ɡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"road5",
                  "west" : __DIR__"tinyuan",
        ]));

	set("coor/x", -5070);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}