inherit ROOM;
void create()
{
        set("short", "ɽ��");
        set("long", @LONG
˳ɽ��Ư�����£���Ϫ�鲼��ϡ��ľ��Ȫʯ����ľ�����ݼ�����
�������ˡ����������۵���й���£�����ɽ�ȡ�
LONG );
        set("exits", ([
               "down"     : __DIR__"heishatan",
               "northup"  : __DIR__"fangguangsi",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6990);
	set("coor/y", -5560);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}