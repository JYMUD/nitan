inherit ROOM;

void create()
{
        set("short", "��¥");
        set("long", @LONG
һ��С�ɶ����ʵĸ�¥�����Ϻõ���ľ��������һ�ɵ��������㡣
¥�ϵ����Ӿ���һ���ǧ��ǵ�������¸�ɮ�������£���ʩ����
�ġ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"qianyuan",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}