//Room: /d/quanzhou/westbridge.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","���ŵ���");
        set("long",@LONG
����Ȫ�������һ�����ţ��Ӱ��Ž��������ĳ�¥����������
������άϵ���ճ����µ���������𡣹������������߿ɴ����Ϲ�
����
LONG);
        set("outdoors", "quanzhou");
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/foshan/road14",
            "east"  : __DIR__"westroad2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -930);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}