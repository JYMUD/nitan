// Room: /d/huangshan/guanpu.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "����ͤ");
        set("long", @LONG
����һ�������̽ǣ�����������Сͤ�������������Զ�ۻ�ɽ��
������֮һ�ġ�����Ȫ�����ɴ˿�����Ȫ��ֻ����̶�����ƶ����з�Ȫ
��й�����������콵������ʱ������ɴ��������ʱ����ǧƥ��������
����ʣ�ʵ������ʤ�ա�
LONG
);
        set("exits", ([ 
                "westdown" : __DIR__"wenquan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1100);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}