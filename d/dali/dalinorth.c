//Room: /d/dali/dalinorth.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","����Ǳ�");
        set("long", @LONG
�����Ǹ���·�ڡ��ϱ߾��Ǵ���ǵı����ˣ���·������ֲ�
��ȥ�ɵ�̫�ͳǣ�����ͨ���¹سǣ�Ҳͨ��ɽ����ȥ�β�ɽ�ͳ�ʥ��
�ıؾ�֮·��
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/taihecheng",
            "south"      : "/d/dali/northgate",
            "northwest"  : "/d/dali/ershuiqiao",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6850);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}