// Room: /d/huangshan/taoyuan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "��Դͤ");
        set("long", @LONG
����λ���һ����ϣ���ΧϪ�����ƣ������ɾӣ��ʳ���Դͤ���˴�
���֮�����ڿ��Ծ������ͻ�ɽ������֮һ�ġ������١���Զ����ȥ��
�ٲ���й��ǡ���Ǹ����֣�ɷ����Ȥ��
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"ciguang",
        ]));
        set("objects", ([
                __DIR__"obj/ting" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -1090);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}