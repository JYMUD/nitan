// Room: /d/xiangyang/eastroad1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "���ڴ��");
        set("long", @LONG
����һ����ʯ�̾͵Ĵ�֡�������һ�¸��ź�ɫ�����ߵĸ�ǽ��
�����������سǴ�����ĸ�ۡ��Ժ����������һ���ھ֣���������
��ʯ�̵Ĵ�ֵ���������һ�����ʮ�ֵֽ���ֻ�������������ǳ���
�֡�
LONG );
        set("outdoors", "xiangyang");

        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"biaoju",
                "south" : __DIR__"eastjie2",
                "north" : __DIR__"eastroad2",
        ]));
        set("coor/x", -7800);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}