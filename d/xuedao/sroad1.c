inherit ROOM;

void create()
{
        set("short","ɽ·");
        set("long", @LONG
�������ǳ�ɽ���룬��ͨ���㡣һ��ɽ·������ɽ�䣬�����Ų�
�ߺ���ԭ��
LONG );
        set("exits",([
                "north" : "/d/chengdu/nanheqiaos",
                "west"  : __DIR__"sroad2",
                "south" : "/d/tangmen/bdajie2",
                "northwest" : "/d/lingxiao/boot", 
        ]));
        set("outdoors", "xueshan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
