//Cracked by Kafei
// yideng quest room 9

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "��ǰ");
        set("long", @LONG
��������ɽ�۷壬ƽ������һ��СС��Ժ����ǰ��һ��������һ
��С�ź�����ϡ��Ա߶��͵�ɽ������һ��������һЩ�˹��������
̨�ף��ƺ���һ������ɽ�Ľݾ���
LONG );

        set("exits", ([
                "south" : __DIR__"yideng8",
                "northup" : __DIR__"chanyuan",
                "down" : __DIR__"shanlu9",
        ]));

        set("invalid_startroom", 1);
        set("outdoors", "taoyuan");
        set("no_magic", 1);
        setup();
}