//Room: /d/dali/jianchuan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","������");
        set("long", @LONG
�����ǽ����������ģ����Ӳ��󣬾�����󲿷��������壬����
ȫ��������Ϊ��������ɽ�ߵغ�������ɽ�ֵ�Ұ�޴��Ƥ��ë����
����Ƥ����������͵������˽��ס�����ɽ��������������Ҳ����
��֮;���ϴ���ɽ��ɵִ�����½��
LONG );
        set("objects", ([
           "/d/dali/npc/lieren": 1,
           "/d/dali/npc/pihuoshang": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/jianchuankou",
            "south"      : "/d/dali/cangshanzhong",
        ]));
	set("coor/x", -19180);
	set("coor/y", -6810);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}