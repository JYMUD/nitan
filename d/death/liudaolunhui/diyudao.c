#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "\n\n                ��        ��        ��" NOR);
        set("long", HIR "\n"
"�������䣬�ܾ�������ĥ������ϲ��֮���������˼�Ƚϣ���\n"
"һ�����˼���ǧ�߰���ʮ��Ϊһ�꣬�ڴ�������һ���꣬�൱\n"
"���˼�һ����ʮ�����ꡣ�����˵�ʮ�˵�����������������Ϊ\n"
"��λ����˳��ڵ����̿�ν��������ʵ����ٲ�����\n\n" NOR);

        set("objects", ([
                __DIR__"npc/diyudaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
