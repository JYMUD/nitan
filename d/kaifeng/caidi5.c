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
                  "west" : __DIR__"caidi",
                  "east" : __DIR__"kongdi",
                  "south" : __DIR__"maofang",
                  "north" : __DIR__"jiaomen",
        ]));

        set("outdoors", "kaifeng");
	set("coor/x", -4990);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}