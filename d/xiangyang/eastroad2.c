// Room: /d/xiangyang/eastroad2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "���ڴ��");
        set("long", @LONG
����һ����ʯ�̾͵Ĵ�֡�������һ�¸��ź�ɫ�����ߵĸ�ǽ��
�����������سǴ�����ĸ�ۡ��Ժ������������������Ϊʮ��������
Ϊ�����������ֿ��ɹž������Զ����������ر�࣬ǰ����������
�����ﲻ����������һ��ʮ�ֵֽ���ֻ�������������ǳ����֣�����
������ʯ�̵Ľֵ���
LONG );
        set("outdoors", "xiangyang");

        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"zhonglie",
                "south" : __DIR__"eastroad1",
                "north" : __DIR__"jiekou2",
        ]));
        set("coor/x", -7800);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}