// Room: /d/huangshan/ciguang.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "�ȹ��");
        set("long", @LONG
�����һ��嶥�����������Ȫ����ſ����飬ǶӳȺ�壬ǰ�����
����ţ����˵���һ�㶼Ҫ����ЪϢ�����Ǳ����������ȹ��
LONG
        );
        set("exits", ([ 
                "southdown" : __DIR__"wenquan",
                "northdown" : __DIR__"qingluan",
                "west"      : __DIR__"taoyuan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1090);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}