inherit ROOM;

void create()
{
        set("short", "����¥");
        set("long", @LONG
����¥���Ĳ㣬�ߴ���ʮ���ף����������е�һ������Բ����������
������¥����˵�����˲�֪�����˲�����¥��Ϊ����¥�Ĵ������ǳ��Ŀ�
�㣬����˽ǣ���ש���أ��ò����ɡ���������һ̴ľ�ƽ���ֱͨ����¥
��¥�ϵ�������
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                "up" : __DIR__"zuixianlou2",
                "west" : __DIR__"nroad1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}