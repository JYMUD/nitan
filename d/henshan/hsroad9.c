inherit ROOM;

void create()
{
        set("short", "����ɽ��");
        set("long", @LONG
�����������һ��ɽ�ڡ����������ϵĴ����ɽ�������Ǻ��ϵ�
�ؽ硣���Ϲ㶫������ʢ�����к���֮ʿ��
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northdown" : __DIR__"hsroad5",
                "southdown" : "/d/foshan/nanling",
        ]));
	set("coor/x", -6930);
	set("coor/y", -5710);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}