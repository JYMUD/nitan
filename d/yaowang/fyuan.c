inherit ROOM;

void create()
{
        set("short", "ǰԺ");
        set("long", @LONG
������ǰԺ��С�㳡������ש�̾͵ĵ���ǳ����ࡣ
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"gd3",
  "south" : __DIR__"gd2",
  "east" : __DIR__"yanwu",
  "west" : __DIR__"keting",
]));

        set("objects", ([
        "/kungfu/class/yaowang/jiang" : 1,
]));
        set("valid_startroom", 1);
        set("no_fight", 1);
        set("outdoors", "yaowang");
        setup();
//�Ӹ�post��
}
