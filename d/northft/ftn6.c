// Room: /d/northft/ftn6.c

inherit ROOM;

void create()
{
	set("short", "��ʯС·");
	set("long", @LONG
���Ƿ���Ǳ�����һ����ʯ�̳ɵ�С·��������Ƿ���ǵ�
�����ˡ�·��ϡ��ĳ���һЩ�Ĳݣ�·������ɳ�������󱱷��
Х������Խ������һ�������ĸо���
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"ftn5",
  "northeast" : __DIR__"ftn7",
]));

	set("outdoors", "northft");
	setup();
	replace_program(ROOM);
}