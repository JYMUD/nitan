#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����ŷ���˵����ң��ڲ����������Ȥ���ݽǰ���һ������������
����������¶�������(pen)������һЩ�����������Ǳ��˰��ȥɹ
̫��ʱ���µġ�
LONG );
        set("exits", ([
                "east" : __DIR__"huayuan",
        ]));
 
        set("item_desc", ([
                "pen" : WHT "\n����һ�����裬����ȥ�ǳ���̽�"
                        "ʵ������Ҳ�ܿ�������ϸ\n�۲��£����ѷ�"
                        "�ֵ�����Щ�������ƺ������ƶ�(move)����"
                        "�衣\n" NOR,
        ]));
        set("coor/x", -49990);
        set("coor/y", 20050);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me = this_player();

        if (arg != "pen")
                return notify_fail("��Ҫ��ʲô��\n");

        if( query("born_family", me) != "ŷ������" )
                return notify_fail("���ƶ���һ�»��裬ȴû����ʲô�ر�Ķ�����\n");

        if (! query("exits/down"))
        {
                set("exits/down", __DIR__"midao");
                message_vision(HIY "\n$N" HIY "�ƶ����裬ֻ����������"
                               "¶��һ�������ĵĶ��ڡ�\n\n" NOR, me);
        } else
        {
                delete("exits/down");
                message_vision(HIY "\n$N" HIY "�ѻ�����ԭλ�����ڶ�"
                               "ʱ����ס�ˡ�\n\n" NOR, me);
        }
        return 1;
}