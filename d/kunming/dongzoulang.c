inherit ROOM;

void create()
{
        set("short",  "������" );
        set("long", @LONG
������һ���ɾ������ȣ������濴ȥ���������͵���԰��
�ķ羰��ֻ�����ּ�ɽ��ʯ���滨��ݣ��������֮���ɡ�
LONG);
        set("exits", ([
                "west"   :__DIR__"wangfu1",
                "east"   :__DIR__"dongzoulang1"
        ]));

	set("coor/x", -16830);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);         
}