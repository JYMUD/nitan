inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������һƬï�ܵľ����ԣ��м�����ԼԼ��һ��С��������
����һЩ��֪����С����������������һ�ִ̱ǵ�ζ����
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"shangpo1",
  "south" : __DIR__"jingji1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
