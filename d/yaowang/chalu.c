inherit ROOM;

void create()
{
        set("short", "��·");
        set("long", @LONG
����һ��С��·�����治Զ���Ƽұ�����·�����ǻ��ܿ���
������ɫ�Ҵҵ��������������Ǹ��ʵ�ɽ�ڣ�һ����С·����
ɽ��������������Զ�����졣
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
        "northwest" : __DIR__"ycl1",
        "east" : __DIR__"gd2",
        "west" : __DIR__"syang",
        "south" : __DIR__"tuzai1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
