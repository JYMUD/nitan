#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "���ֻ�˾��" NOR);
        set("long", HIR @LONG

                 ��        ��        ˾

    ������������֮������ΧһƬ�ڰ���ֻ��һ������֮�����·�ӿ����

LONG NOR );

        set("sleep_room", 1);

        set("sky", 1);
        // �ڴ�����lunhui-sword
        set("lunhui", 1);
        set("valid_startroom", 1);
        setup();
}
