inherit ROOM;

void create()
{
        set("short", "ʯ��·");
        set("long", @LONG
����һ����ʯ���̵�С·��·�����Ի�����һ���Ͱ���ʯ��
�ˣ�������������۲ݵء�
LONG
        );
        set("outdoors", "yaowang");
        set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"lcd06",
  "east" : __DIR__"lcd04",
]));

        setup();
        replace_program(ROOM);
}
