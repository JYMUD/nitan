inherit ROOM;

void create()
{
        set("short", "��С·");
        set("long", @LONG
����һ���������۵�С·��������һСƬ�Ͱ������֣�����
�Ƕ��͵�ɽ�ڡ�����������ʯ�ӣ��еĻ��ܼ����������������
����������
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northwest" : __DIR__"ycl2",
  "southeast" : __DIR__"chalu",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
