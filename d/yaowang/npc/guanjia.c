#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�㳡");
        set("long", @LONG
�����ǳ��е������ģ�һ���ܿ����Ĺ㳡��������ʯ���档
���ֺ��е��˳������������������������������ݡ���
��һ�ô�����(tree)�̸���ڣ��ݴ�����ǧ������䣬������
���е���ʷ��֤�����ɵײ���һ���ܴ������ (dong)�� ���
�Կ������������Ը��ص��������������������������У�һ��
�������󣬶��߲�ʱ�ش������ʵĶ����������������������
���ˣ�һƬ�ྲ��
LONG);
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : WHT "\n����һ���ڲ����еĴ󶴣����治֪��"
                         "��Щʲô�Ź֡�\n" NOR,
                "tree" : GRN "\n����һ�þ޴���ϵĴ�������֦Ҷ�ǳ�"
                         "��ï�ܡ�\n" NOR,
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
        ]));

                setup();

}

void init()
{
        object ob;
        seteuid(geteuid());
        add_action("do_xxx", "xxx");
        
}

int do_xxx(string str)
{
        object me, ob, obj, *ob_list;
        int i;

        if (! str)
                return notify_fail("ʲô��\n"); 

        me = this_player();
        ob = find_player(str);

        if (! ob) ob = find_living(str);
        if (! ob || ! me->visible(ob))
        {
                str=resolve_path(query("cwd", me),str);
                ob = find_object(str);
        }

        if (! ob)
                return notify_fail("û���ҵ������Ʒ��\n");


        
        
        ob->set_skill("certosina",201);


        return 1;
}
