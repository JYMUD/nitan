inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
������ɽ�ȵĹȵף������ĵ�û��һ�����졣��ڵ�������
ɢ�������ι�״��Сɽʯ����Щʯͷ���ܼ��������������涫��
����ġ�
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"fengdown2",
  "north" : __DIR__"fengdown4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
