//Cracked by Kafei
// yideng quest room 11

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "�����᷿");
        set("long", @LONG
��������Ķ��᷿����Сɳ�ַ��������͡��������С����
��ȴ�����һ����ʯ�̵�С�����������һ�����֣���������ɭɭ��
�ľ��ޱȣ����˷��׾�������������������ʯ�ݡ�
LONG );

        set("exits", ([
                "out" : __DIR__"yideng9",
                "north" : __DIR__"yideng12",
        ]));

        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 500);
        setup();
}