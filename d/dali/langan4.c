//Room: /d/dali/langan4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�����в�");
        set("long",@LONG
�����Ǹ������в㣬��¥��һ�������Ǽ�������گ���Ĵ���ŷ�
�Լ��������е��������Ҽһ������������谸����в�����෿��
��Ϊ���������ݿ�������һ����ɴ����
LONG);
        set("objects", ([
           __DIR__"npc/fangshanu": 1,
           __DIR__"obj/fangshaji": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "down"      : __DIR__"langan3",
        ]));
	set("coor/x", -19010);
	set("coor/y", -6900);
	set("coor/z", 20);
	setup();
}
void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/lg4", 1, me);
        }
}