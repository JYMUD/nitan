inherit ROOM;

void create()
{
        set("short", "СϪ");
        set("long",@LONG
�������������ϵ�һ��СϪ��
LONG);

	set("exits", ([
		"north"  : __DIR__"xiaoxi1", 		
		"south" : __DIR__"guanlongting",

	]));

        set("outdoors", "shenlong");
        setup();
}
