// Room: /d/guiyun/road1.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "����С·");
        set("long", @LONG
һ�������Ļ�ҰС·�����̳������ݣ��������һ����ҡͷ���ԡ�
������Զ�����ƺ�����һ��С�ӡ�������������̩����
LONG);
        set("outdoors", "guiyun");
        set("objects",([
                __DIR__"npc/youke" : 1,
        ]));  
        set("exits", ([
                "east": "/d/wuxi/taibomiao",
                "west": __DIR__"rivere",
        ]) );
        set("coor/x", 330);
        set("coor/y", -860);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
