inherit ROOM;

void create()
{
        set("short", "�˵�");
        set("long", @LONG
��Ƭ��԰�Ӽ����������һЩʱ���߲ˡ������м���ľ׮�����
�˼��ӣ���һЩ���ٵ��߲��������������Ŀ��ȥ���ϴ��һƬ��԰
�ӣ���Ȼ���������û�м��òˡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"zoulang2",
                  "east" : __DIR__"caidi4",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5010);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}