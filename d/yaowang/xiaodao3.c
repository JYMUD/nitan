inherit ROOM;

void create()
{
        set("short", "����С��");
        set("long", @LONG
����һ��Ƨ���Ĵ���С����С�������ǿ�֦��Ҷ������ȥ��
���������ܾ����ĵģ�ż����������������
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"xiaodao2",
  "northwest" : __DIR__"xiaodao4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
