//Room: /d/dali/shanlu8.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","ɽ·");
        set("long",@LONG
��·��ɽ�������Ѽ������������ɽ��ͨ����ĵ��ݵش�����
��ɽ�ƽ�Ϊƽ����ɽ����ż�����̣�͸�����ֵķ�϶������ȥ����
Լ�ɼ�һ����ˮ��Щ�����̡�
LONG);
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "eastdown"  : __DIR__"yangzong",
            "westdown"  : __DIR__"shanlu7",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19030);
	set("coor/y", -6880);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}