//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "ɽ��");
        set("long", @LONG
����һ������ɽ������ʱ�ɼ��������˱��Ű��������ŵ���������
ȥ����������೵������ĺۼ���
LONG );
        set("exits", ([
                "northeast"  : __DIR__"qingshilu2",
                "west"  : __DIR__"shangang",
        ]));
        set("outdoors", "jiangling");
        set("no_clean_up", 0);
        set("coor/x", -7130);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}