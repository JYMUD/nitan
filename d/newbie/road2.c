inherit ROOM;

void create()
{
        set("short", "��ʯС·");
        set("long", @LONG
����һ���򶫵���ʯ�����������һ���ŵ����С�ݡ�
LONG);

        set("exits", ([
                "east" : __DIR__"lianwuchang",
                "west" : __DIR__"shijiezhishu",
                "north": __DIR__"cunzhangjia",
                "south": __DIR__"zahuopu",
        ]));

        set("xinshoucun", 1); 
        set("outdoors", "newbie");
        setup();

        replace_program(ROOM);
}