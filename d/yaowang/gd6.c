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
  "northeast" : __DIR__"gd5",
  "southwest" : __DIR__"gd7",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
