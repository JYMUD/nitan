// Room: /d/henshan/hsroad1.c ����·
// Modified By Java Feb.14.1998

inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
������һ����������Ļ���·�ϣ���������ɭɭ�����֡�������ͨ��
���ݣ����Ͼͽ�����ϵؽ��ˡ�
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northeast" : "/d/wudang/wdroad4",
                "south" : __DIR__"hsroad2",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -6860);
	set("coor/y", -5680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}