inherit ROOM;

void create()
{
        set("short", "Сé��");
        set("long", @LONG
�ڿյ��ϴ����һ��Сé�������ڵ����Ŷ�û�С�����ƽ������
�˸���ӣ�������������ľ�塣���˵Ĳ�ӬΧ������ת��һ�ɳ�ζѬ
����ֱ���ӳ�ȥ��������Ƭ�˵أ������Ǹ���ѡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"caidi5",
                  "east" : __DIR__"fenjiao",
        ]));

	set("coor/x", -4990);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}