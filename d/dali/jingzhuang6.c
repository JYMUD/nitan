//Room: /d/dali/jingzhuang6.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","������");
        set("long", @LONG
���������������е��з��񸡵�����������������ܣ���η�����
������죬����Э���������Ⱦ����������ɣ���������������������
�����ǵ���ʯ����������Ʒ���������ļҽ��ޡ������������˼�ƷҲ
����
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang7",
            "down"  : "/d/dali/jingzhuang5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 59);
	setup();
        replace_program(ROOM);
}