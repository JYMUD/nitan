//Room: /d/dali/yongdao1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��");
        set("long", @LONG
���������������������������ܵ����֣��紵����Ҷɳɳ����
ʯ������·�����࣬��������̲ݣ���׺��һ�ǰ���С������Χ
ʮ�ְ�����Ψ�������Ǵ���һ����򶷵������������׾��Ļ���Խ��
�������С�
LONG );
        set("outdoors", "daliwang");
        set("exits",([ /* sizeof() == 1 */
            "northeast" : "/d/dali/yongdao2",
            "northwest" : "/d/dali/liangong",
            "south"     : "/d/dali/tingfang",
        ]));
	set("coor/x", -19101);
	set("coor/y", -6831);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}