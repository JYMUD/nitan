#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "�峤��" NOR);
        set("long", @LONG
�����ǹŴ�峤�ļң�����ȴ����Ϊ���أ�ǽ�߿��ż���ũ�ߣ�
ǽ��һ���񴲣�����ͨ�����ûʲô����
LONG);

        set("exits", ([
                "north"  :  __DIR__"woshi",
                "west" :  __DIR__"chufang",
                "south"  :  __DIR__"road2",
        ]));
        set("xinshoucun", 1);
        set("outdoors", "newbie");
        
        set("no_fight", 1);
        setup();

        replace_program(ROOM); 
}
