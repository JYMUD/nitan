#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + WHT "\n\n                ��        ��        ��" NOR);
        set("long", WHT "\n"
"�·�̤�������ӵ����У����紳������Ҵ�Ժ����Ц��������\n"
"����ŭ�����໥���ӡ�ϲŭ���֡���Թ��������̬������\n"
"�ˡ������˼��������������������ϡ���ʹ���е���������\n"
"ʹ�������š��������ˣ��ǻ�ʵ�ࡣ�������ˣ��ǻ�ʵ�ࡣ\n\n" NOR);
        
        set("objects", ([
                __DIR__"npc/rendaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
