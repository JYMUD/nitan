inherit ROOM;

void create()
{
        set("short", "СϪ");
        set("long",@LONG
�������������ϵ�һ��СϪ��
LONG);

	set("exits", ([
		"north"  : __DIR__"lin1.16", 		
		"south" : __DIR__"xiaoxi2",

	]));

        set("outdoors", "shenlong");
        setup();
}
