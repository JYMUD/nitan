inherit ROOM;
 
void create()
{
        set("short", "�׻���");
        set("long", @LONG
�����Ǻ�ľ�µĵڶ����á��׻��á���������ש�̵أ����ں�ʬ
���ء�
LONG );
        set("exits", ([
            "north"   : __DIR__"baistep2",
            "south"      : __DIR__"chitang", 
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/shanggy": 1,
        ]));       
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}