//Room: /d/dali/hole.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��С֥�ƶ�");
        set("long", @LONG
���Ż��۽��붴�ڣ��ػ����У����ã�����һ����Ȼ���ʣ�ʯ��
�飬ʯ��ʯ����������͸��������ʤ�����ձ�Ӱ�����´����ң�Ϫ
�ƽ�ˮ�������ֺ���ʯ��δ䣬���Ŀɰ���
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "out"      : "/d/dali/changhu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19161);
	set("coor/y", -6801);
	set("coor/z", 29);
	setup();
        replace_program(ROOM);
}