#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "\n\n                ��        ��        ��" NOR);
        set("long", HIG "\n"
"������ԭ��ӡ��Զ������֮һ������Ϊ�����������ͺö���\n"
"���񣬾�����������������ݡ����и�����û�е����е�˵��\n"
"ֻ�ǽ�����������У���˵�Ƕ�������ˣ���������̽�����\n"
"Ϊ�Ƶ����ϴ��������������С��������ˣ��·����ˡ�\n\n" NOR);

        set("objects", ([
                __DIR__"npc/xiuluodaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
