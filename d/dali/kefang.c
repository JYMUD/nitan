//Room: /d/dali/kefang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�ͷ�");
        set("long",@LONG
����һ��ͷ�����ǽ����һ����ľ�󴲣�����ı��쾡����
�壬�������ס����з���һ�Ű���������������������ڸ�̸��
�ۡ�
LONG);
        set("objects", ([
           __DIR__"npc/peicong": 3,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "out"      : __DIR__"zoulang2",
        ]));
	set("coor/x", -19162);
	set("coor/y", -6912);
	set("coor/z", 8);
	setup();
        replace_program(ROOM);
}