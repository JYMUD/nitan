#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "����֮��" NOR);
        set("long", @LONG
�����ǹŴ�������ģ�һ���ܿ����Ĺ㳡������������ʯ���档��
��һ�ô���(tree)�̸���ڣ��Ѿ����������������Ŷ��������ˣ���
���Ǵ�˵�е�����֮��������˵�����������������������ɫ������Ȼ
֮�档����վ��һ�����ߣ������ĵظ��������֡�

==== �������Ҫ����������ָ�� ask lao about here ====

LONG);
        set("item_desc", ([
                 "tree" : GRN "\n����һ�þ޴���ϵĴ�����֦Ҷ�ǳ�"
                         "��ï�ܡ�\n" NOR,
        ]));

        set("objects", ([
                __DIR__"npc/laocunzhang" : 1,
        ]));

        set("valid_startroom", 1);
        set("exits", ([
                "east"  :  __DIR__"road2",
                "west"  :  __DIR__"road",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");
        
        set("no_fight", 1);
        setup();

        "/clone/board/newbie_b"->foo();
        replace_program(ROOM); 
}
