inherit ROOM;

void create()
{
        set("short", "���С·");
        set("long", @LONG
����һ���򶫵���ʯ�����������һ���ŵ����С�ݡ�
LONG);

        set("exits", ([
                "west" : __DIR__"road1",
                "east" : __DIR__"shijiezhishu",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        setup();

        replace_program(ROOM);
}