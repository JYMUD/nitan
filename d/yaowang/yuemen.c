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
        set("exits", ([ /* sizeof() == 3 */
        "east" : __DIR__"tulu1",
        "west" : __DIR__"gd4",
        "south" : __DIR__"liandan2",
        "north" : __DIR__"liandan1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
