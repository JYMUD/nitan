inherit ROOM;

void create()
{
        set("short", "�﹡С��");
        set("long", @LONG
����һ���򶫵����С����������һƬƬ�����͵�ˮ������е�
��ͯ��
LONG);
        set("exits", ([
                "west" : __DIR__"cunkou",
                "east" : __DIR__"road",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");
        setup();

        replace_program(ROOM);
}