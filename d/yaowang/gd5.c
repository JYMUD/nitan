inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������һ�����Ĺ���������ש�̾͵ĵ���ǳ����࣬����
�Ǻ�����ĵ����ˣ�����Ļ���ÿ����������һ�����˴��
�������������ԣ�������������书�����ǵ���֮���������ڴˣ�
���˸о���Ī����ѹ����
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"myuan",
  "southwest" : __DIR__"gd6",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
