// Room: wangjianglou.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "����¥");
        set("long", @LONG
����¥�����������������Ľǣ�������˽ǣ��������ߣ��̽�
�����������������������ϣ�Զ�����Ϻӣ�������棬�ۻ���ʵ
Ϊʤ����¥�����⣬����ǧ�����죬ÿ�������뵣��������䣬����
�������������ǡ�¥ǰѦ�ξ�����˵��ΪѦ��Ưϴһ�ֺ�ɫʫ�����
��ǧ�ţ� �޲��ž������أ���ɫ�ż�����䡣��Ҳ����һ��Ů�Ĵ���
��Ψһ����
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northwest"  : __DIR__"eastroad3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15190);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}