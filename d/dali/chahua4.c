//Room: /d/dali/chahua4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�軨԰");
        set("long", @LONG
����軨�ھ����£����������Ĳ軨��Ȼ���Ƿ�Ʒ����վ�ڲ軨
԰�У�������һƬ�������ٵĺ��档�����������£��м���軨����
�����ˣ�����԰�����Ĳ軨Χ�У��Խ�Ȼ��Ⱥ��
LONG );
        set("objects", ([
           "/d/dali/obj/chahua4": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/dali/chahua5",
            "northwest"  : "/d/dali/chahua2",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6871);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}