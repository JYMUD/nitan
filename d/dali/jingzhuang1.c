//Room: /d/dali/jingzhuang1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��һ��");
        set("long", @LONG
���Ĵ������񣬸�Լ�ĳߣ����״��У��ֳָ��ᣬ����ׯ�ء���
����̤��ū��һ��ū���Ⱪ���������ߣ�����������ū��������
��ū���͡�һ�����������ˣ��м�һ������˫�ָ�������һ�㡣����
֮�������ķ𾭡�
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "up"    : "/d/dali/jingzhuang2",
            "out"   : "/d/dali/jinzhihe",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19091);
	set("coor/y", -6871);
	set("coor/z", 9);
	setup();
        replace_program(ROOM);
}