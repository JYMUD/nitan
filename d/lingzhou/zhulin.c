// Room: /d/lingzhou/zhulin.c

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����һƬ�����֣�����ȥ���󣬵���һ�߽���ȴ�·�����·������
�����ܵ�����������ڱ�����Ȼ����ô�ϵ����ӡ�
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"hut",
                "east" : __DIR__"garden",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");

        set("coor/x", -6285);
        set("coor/y", 2995);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}