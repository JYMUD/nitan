//Room: /d/dali/situ.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","˾ͽ��");
        set("long", @LONG
�����Ǵ����˾ͽ�á�������������������������Բ����ԡ�
�����������ֵ��ǵ��Ͻ��仹����Щ������������֮������¡�
LONG );
        set("objects", ([
            CLASS_D("dali")+"/huahegen" : 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/zonglichu",
        ]));
	set("coor/x", -19131);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}