// room: /d/xingxiu/tianroad3.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void init();
int do_jump(string arg);

void create()
{
        set("short", "��ɽɽ·");
        set("long", @LONG
��������ɽ��´��ɽ���ɽ�ϴ����������ɪɪ������·����һƬ
��ԭ������һ���(valley)��ס����ɽ��·��
LONG );
        set("exits", ([
                "northup"  : __DIR__"xxroad4",
                "eastdown" : __DIR__"xxh",
        ]));
        set("item_desc", ([
                "valley" : "������ɶ����֪���ܲ�����(jump)��ȥ��\n"
        ]) );
        set("objects", ([
                CLASS_D("xingxiu")+"/azi" : 1
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -51000);
        set("coor/y", 20100);
        set("coor/z", 20);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if( arg=="valley" )
        {
/*                if (present("horse", me)) { */
                if( query_temp("marks/��", me) )
                {
                        message("vision", me->name() + "�͵�һ�����������µ�������һ����˻Խ�������\n", environment(me), ({me}) );
                        write("���͵�һ�����������µ�������һ����˻Խ�������\n");
                        me->move("/d/xingxiu/tianroad4");
                        message("vision","ֻ����������һ����˻��" + me->name() + "������Ƕ��������˹��������Ƶ�������\n̴Ϫ�����¹���\n", environment(me), ({me}) );
                        write( "ֻ����������һ����˻���������Ƕ��������˹��������ǿ���ˡ�\n���ֵô����Ϲ���������\n");
                        set_temp("marks/��", 0, me);
                        return 1;
                }
                else
                {
                        write("�������ԣ���������Ǳ߱���߸ߣ�����������������ȥ�ġ�\n");
                        return 1;
                }
        }
}
/*
int do_jump(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg != "valley")
                return notify_fail("��Ҫ��������\n");

        message_vision(HIY "\n$N" HIY "ԥ��һ�£��������������Ŷ����ɽ�����˹�"
                       "ȥ��\n\n" NOR, me);

        if ((int)me->query_skill("dodge", 1) < 100 )
        {
                me->move(__DIR__"shanjiao");
                me->receive_wound("qi", 300);
                me->unconcious();
                message("vision", HIR "\nͻȻ���á��项��һ����ֻ��һ���˴�����"
                                  "��ɽ����׹������������׳�ۡ�\n" NOR,
                                  environment(me), ({me}));
        } else
        {
                me->move(__DIR__"tianroad4");
                message("vision", HIY "\nֻ��" + me->name() + HIY "�Ӷ����ɽ��"
                                  "�����˹�����\n" NOR, environment(me), ({me}));
        }
        return 1;
}

*/