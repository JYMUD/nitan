inherit ROOM;

void create()
{
        set("short", "��ݮ��");
        set("long", @LONG
�����ǰ���ɽׯ�����һ���ݮ�أ��ʺ�Ĳ�ݮɢ�����̲��У�
���˸е��ǳ�������⡣
LONG );
        set("exits", ([
                "northeast" : __DIR__"shulin1",
        ]));

        set("objects" , ([
                __DIR__"obj/caomei" : random(7),
        ]));

        set("outdoors", "baituo");
        set("coor/x", -50010);
        set("coor/y", 19990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}