inherit ROOM;

void create()
{
        set("short", "��ɽ");
        set("long", @LONG
����һ��޴���߷��������ﱻֱ���ݶ��Ĵ�ľ����ռ���ˣ�
����������һλ���ˡ�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"ycl9",
]));

        set("objects", ([
        "/kungfu/class/yaowang/shiwanchen" : 1,
]));
        setup();
        replace_program(ROOM);
}
