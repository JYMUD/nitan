// Code of ShenZhou
// maze1.c

inherit ROOM;

int do_find(string);

void create()
{
        set("short", "������");
        set("long", @LONG
��������һƬ��ɭɭ��������ǰ��������ȥ����������Ķ�����
ľ�����Ҿ�����������Լ�ɼ���ЩС·��������������ϸ�۲죬����
����Ȼ�Ǹ�������Թ������а������а��ԣ����Ŷݼף��˵ķ�ͬС
�ɣ�ǧ��ҪðȻ��ȥ��
LONG );
        set("exits", ([
                "south" : __DIR__"maze2.c",
                "north" : __DIR__"shulinwai",
                ]));

        set("cost", 2);
        set("outdoors", "dalic");
        set("coor/x", -38000);
        set("coor/y", -71010);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir=="south") {
                if (! userp(me)) return 0;
                set_temp("mark/maze��", 1, me);
                set_temp("mark/mazeľ", 1, me);
                set_temp("mark/mazeˮ", 1, me);
                set_temp("mark/maze��", 1, me);
                set_temp("mark/maze��", 1, me);
                set_temp("mazepath", 11111+random(88889), me);
        }

        return ::valid_leave(me, dir);
}