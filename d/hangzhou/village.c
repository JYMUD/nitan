// This program is a part of NT MudLIB

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "ţ�Ҵ�");
        set("long", @LONG
Ǯ�����ƺƽ�ˮ������ҹҹ�������ݵĴ��ٰ�ţ�Ҵ���ƹ�����
���뺣������һ����ʮ���ڰ�����Ҷ���ƻ��հ�졣��ǰ����Ұ��
����ʼ��ƣ������˼��������������������Χ��һ�Ѵ�������Ů
Ů��ʮ����С�������Ծ۾����������һ������������˵�����嶫ͷ
����һ���ƾ��������ǾƵ�ģ����
LONG );

        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"jiudian",
                "west" : __DIR__"qiantang",
        ]));

        set("objects", ([
                __DIR__"npc/yang" : 1,
                __DIR__"npc/guo" : 1,
         ]));

         set("outdoors", "xihu");

         set("coor/x", 3900);
        set("coor/y", -1800);
        set("coor/z", 0);
        setup();

         replace_program(ROOM);
}