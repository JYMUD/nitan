// Room: /d/huangshan/shanmen.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "��ɽɽ��");
        set("long", @LONG
����һ��ʯ���ŷ�������ɽ�ź󣬱��ǻ�ɽ������������꣬�Ŵ�
��Ϊǭɽ����ɽɫ��ڣ�Զ������������������������š��Ƶ��ڴ˷�
���������Ը�Ϊ��ɽ��������Ⱥ�������������������ˡ���ɽ�ź�
������Ȫ��
LONG
        );
        set("exits", ([ 
                "northup"   : __DIR__"wenquan", 
                "southwest" : "/d/henshan/hsroad2",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -595);
        set("coor/y", -1110);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}