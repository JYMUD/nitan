inherit ROOM;

void create()
{
        set("short", "ҩ�Ŀ�");
        set("long", @LONG
����һ��޴���߷��������ﱻֱ���ݶ��Ĵ�ľ����ռ���ˣ�
һ�����ŵ���ζ���˻���������ſڵ�����������һλ�����ˡ�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"yz_xiaoyuan",
]));

        set("objects", ([
        "/kungfu/class/yaowang/murong" : 1,
]));
        setup();
        replace_program(ROOM);
}
