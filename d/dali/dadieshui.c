//Room: /d/dali/dadieshui.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","���ˮ�ٲ�");
        set("long", @LONG
��ɽ��С·Խ���꣬����ׯ������Ұ��Լ�����������������
ˮ���ĺ�������ǰ������һƬ�µص�ǰ�ˣ����ֵ�Ѿ�������䣬�Ǿ�
��ĺ����������Ǵ����乵�ﴫ���ġ������ϵ�֮����С·���ٷ�ʯ
��ǰ��
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : "/d/dali/chahuashan6",
            "eastdown"   : "/d/dali/xiaojing",
            "southdown"  : "/d/dali/qingxi",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19110);
	set("coor/y", -6870);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}