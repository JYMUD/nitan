//Room: /d/dali/chahua8.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�軨԰����");
        set("long", @LONG
����軨�ھ����£����������Ĳ軨��Ȼ���Ƿ�Ʒ����վ�ڲ軨
԰���ſڣ�������԰��ɫ��������ϲ���������߾ͽ�԰�ˣ�������һ
��ʯ������
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "east"   : "/d/dali/chahua7",
            "west"   : "/d/dali/yongdao2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19081);
	set("coor/y", -6821);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}