inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ������ʵ���ʯ���̳ɵ�С·�����Ķ������죬·��
��������۲ݣ�·�����Ը���һ��С��̳�����濪�������Ļ��䡣
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"ssl4",
  "west" : __DIR__"ssl2",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
