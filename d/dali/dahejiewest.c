//Room: /d/dali/dahejiewest.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��ͽ�");
        set("long", @LONG
����һ����ʯ��·���������˲��ٰ������Ե�ׯ�����¡�������
����ǵ��ؾ�פ�أ���������������ʿ�ǲ����ĺ�������������˾
�����ǵ����̫������һ�����Ϯ���š�
LONG );
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "east"   : "/d/dali/shizilukou",
            "north"  : "/d/dali/tusifu",
            "south"  : "/d/dali/bingying",
            "west"   : "/d/dali/zsh_dldamen",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19140);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}