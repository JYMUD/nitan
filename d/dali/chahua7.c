//Room: /d/dali/chahua7.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�軨԰");
        set("long", @LONG
����軨�ھ����£����������Ĳ軨��Ȼ���Ƿ�Ʒ����վ�ڲ軨
԰�У�������һ��Сɽ��ɽ�������˳�����ľ�����ϳ���ί�أ�����
���ġ�������һ��ССͥԺ��������ȥ����һƬ����ǧ�졣
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "south"   : "/d/dali/chahua6",
            "northup" : "/d/dali/chahua9",
            "east"    : "/d/dali/chahua10",
            "west"    : "/d/dali/chahua8",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19071);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}