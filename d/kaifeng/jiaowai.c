inherit ROOM;

void create ()
{
          set ("short","����");
        set("long", @LONG
�˴��ǿ��ⱱ���������뿪��ܽ����ΰ�����ȶ����ɴ�ȥ��ɽ
����Ŀ������ﲻ����һ��̫ƽ����
LONG );
          set("outdoors", "kaifeng");
          set("exits", ([
                  "south" : __DIR__"xuandemen",
		"westup" : __DIR__"shanlu1",
        ]));
	set("coor/x", -5060);
	set("coor/y", 2270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}