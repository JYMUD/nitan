//Room: /d/dali/yanchi2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�سص̰�");
        set("long", @LONG
��ط羰���ˣ��ص̰�����������к��У����ϱ��Ա�ˮ������
�̲����ݺ�֮�࣬�����ڵ�أ����ֻ����£���������ɽ֮������
�к��У�ң������ɽɫ����ӳ�ز��䣬������ˮ��������̣���Ȼ��
ʤ��
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "westdown" : "/d/dali/yanchi1",
            "east"     : "/d/dali/yanchi3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19090);
	set("coor/y", -6860);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}