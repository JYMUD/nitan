//Room: /d/dali/wuding.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�䶨��");
        set("long",@LONG
������̨�ķ�֧¬¹�����������θ����������������䶨���⻹
ϽԪı��»�����򡣴��򲻴�����ɽ����������Եø������ġ�
¬¹���˵���¥��ɢ�ֲ��������С�
LONG);
        set("objects", ([
           __DIR__"npc/guniang": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalis");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"zhulou1",
            "northeast"  : __DIR__"zhulin",
            "west"       : __DIR__"qingzhulin",
            "south"      : __DIR__"nongtian1",
        ]));
	set("coor/x", -19150);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}