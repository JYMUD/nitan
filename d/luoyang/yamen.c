// Room: /u/a/agah/yamen.c

inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
���϶����������ס������һ������������������ϸ������ǽ������
һ�����ң����顰����������ĸ���������Ĵ��֡�֪���������İ�����
�����飬ʦү�����ں�һ���������������ԣ��ڴ���ʲôԩ�������ֱ
����֪��������˵��
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"neizhai",
  "south" : __DIR__"sting",
  "west" : __DIR__"yamendoor",
  "north" : __DIR__"bting",
]));

	set("coor/x", -6970);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}