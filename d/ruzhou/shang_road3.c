inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
С���Ե�һ��С·����Ϊƽʱ����֮�˲����Ե�ʣ���Χ��
�ѳ������Ӳݡ�ԶԶ��������ȥ���ƺ���һ����լ��
LONG);
        set("exits", ([
                //"west"  : __DIR__"shang_road2",
                "west"  : __DIR__"xiaozheng",
                "north"  : __DIR__"shang_men",
        ]));
        set("outdoors", "ruzhou");
	set("coor/x", -6750);
	set("coor/y", 1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}