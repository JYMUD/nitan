// Room: /d/huangshan/shisun.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "ʯ���");
        set("long", @LONG
����ʯ����������ͬ����ǧ�˰�̬��ÿ���������������ն�����
��ϼ��ȾȺ�壬�����������֣�������������Ļ���ʹ��Ľ����������
���óϷ���
LONG
        );
        set("exits", ([ 
                "southwest" : __DIR__"sanhua",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -585);
        set("coor/y", -1010);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}