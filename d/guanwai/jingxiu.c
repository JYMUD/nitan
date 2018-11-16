// jingxiu.c ������

inherit ROOM;

void init();
int close_men();
int force_open(object room);
int do_push(string arg);
int do_knock(string arg);
int valid_leave(object me, string dir);
string look_men();

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǿ����ң�������һЩ���ҵ������������������������һ
��С��(men)����������������������
LONG );
        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));

        set("item_desc",([
                "men"  : (: look_men :),
        ]));

        set("objects", ([
                "/clone/weapon/mudao" : 3,
        ]));

        setup();
}

void init()
{
        add_action("do_knock", "knock");
        add_action("do_push", "push");
        add_action("do_kick", "kick");
}

int close_men()
{
        object room;

        if (!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if (objectp(room))
        {
                delete("exits/south");
                message("vision", "��֨֨ѽѽ���Լ������ˡ�\n", this_object());
                delete("exits/north", room);
                message("vision", "��֨֨ѽѽ���Լ������ˡ�\n", room);
        } else message("vision", "ERROR: men not found(close).\n", room);

        return 1;
}

int do_knock(string arg)
{
        object room;

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("��Ҫ��ʲô��\n");

        if (query("exits/south"))
                return notify_fail("�����Ѿ��ǿ����ˡ�\n");

        if (!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if(objectp(room))
        {
                if( query_temp("sleeping_person", room)>0 )
                {
                        message_vision("$N�����������һ���ţ����������洫��һ���������������\n"
                                       "��Ȼ�������˯�ø������Ƶģ���ô�ö�û����\n",
                                       this_player());
                } else
                if( query_temp("person_inside", room)>0 )
                {
                        switch (random(2))
                        {
                        case 0:
                                message_vision("$N������������ţ�ֻ�����������˺ܲ��ͷ��غ𵽣�\n"
                                               "�����¾������ţ���˯���ˣ�������������\n",
                                               this_player());
                                break;
                        case 1:
                                message_vision("$N������������ţ�ֻ����������Щ�춯��\n"
                                               "����������������ȥ���ò��������Ƿ��š�\n",
                                               this_player());
                                break;
                        }
                } else
                {
                        delete_temp("sleeping_person", room);
                        message_vision("$N������������ţ��ˡ��ˡ��ˣ������ˡ��ˡ��ˣ�����\n",
                                       this_player());
                }
        }

        if (objectp(room))
                message("vision",  "���洫��һ��������������ŷ�����һ�ƣ���" +
                        this_player()->name() + "һ��������վ�����⣬\n"
                        "������Ҳ�������Ϣ��\n", room);
        return 1;
}

int do_kick(string arg)
{
        object me;
        object room;

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("��Ҫ��ʲô��\n");

        if (query("exits/south"))
                return notify_fail("���ſ��ţ����������𣿡�\n");

        if (!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        me = this_player();
        if(objectp(room))
        {
                if( query("qi", me)<40 )
                {
                        message_vision("$N����һ�ţ��ݺݵ����д��ţ�Ȼ��������˿������\n", me);
                        message("vision", "�������顱��һ�����죬�����ƺ����˷��������ˡ�\n", room);
                        tell_object(me, "����ý�ֺ������Ҫ���ˣ�\n");
                        me->unconcious();
                } else
                if( query("qi", me)<100 )
                {
                        message_vision("$N����һ�ţ��ݺݵ����д��ţ�Ȼ������ֻ�ǻ���һ�¡�\n", me);
                        message("vision", "�������顱��һ�����죬�����ƺ����˷��������ˡ�\n", room);
                        tell_object(me, "����ýŷǳ���ʹ��\n");
                        set("qi", 20, me);
                        me->receive_wound("qi", 20);
                } else
                {
                        message_vision("$N����һ�ţ��ݺݽ������߿���\n", me);
                        message("vision", "�������顱��һ�����죬�ź���һ���ӾͿ��ˣ�����"
                                "��һ������ϸһ����ԭ����" + me->name() +
                                "�������ڵ�վ���ſڡ�\n", room);
                        me->receive_damage("qi", 100);
                        delete_temp("person_inside", room);
                        set("exits/south", __DIR__"xiuxishi");
                        set("exits/north", __FILE__, room);
                        remove_call_out("close_men");
                        call_out("close_men", 10);
                }
        }

        return 1;
}

int do_push(string arg)
{
        object room;

        if (query("exits/south"))
                return notify_fail("���Ѿ��ǿ����ˡ�\n");

        if (!arg || (arg != "door" && arg != "men"))
                return notify_fail("��Ҫ��ʲô��\n");

        if (!(room = find_object(__DIR__"xiuxishi")))
                room = load_object(__DIR__"xiuxishi");

        if (objectp(room))
        {
                    if( query_temp("person_inside", room) <= 0 )
                    {
                        delete_temp("person_inside", room);
                        set("exits/south", __DIR__"xiuxishi");
                        message_vision("$N����ذ����ƿ���\n", this_player());
                        set("exits/north", __FILE__, room);
                        message("vision", "���˴���������ƿ��ˡ�\n", room);
                        remove_call_out("close_men");
                        call_out("close_men", 10);
                } else
                {
                        message_vision("$N������ƿ���ȴ�����ű��˴����������ˡ�\n",
                                       this_player());
                }
        }

        return 1;
}

string look_men()
{
        object room;

        if (!( room = find_object(__DIR__"xiuxishi")))
                room = load_object(__DIR__"xiuxishi");

        if( objectp(room) && query_temp("person_inside", room)>0 )
                return "���Ϲ��˸����ӣ���Ϣ�С��������\n";

        return "���Ϲ��˸����ӣ���Ϣ��\n";
}

int valid_leave(object me, string dir)
{

        object room;

        if (!( room = find_object(__DIR__"xiuxishi")) )
                room = load_object(__DIR__"xiuxishi");

        if (objectp(room) && dir == "south")
        {
                addn_temp("person_inside", 1, room);
                // will open the door if ppl inside stay too long
                remove_call_out("force_open");
                call_out("force_open", 599, room);
        }

        return ::valid_leave(me, dir);
}

int force_open(object room)
{
        if (! objectp(room)) return 0;
            if( query_temp("person_inside", room) <= 0)return 0;

        delete_temp("person_inside", room);
            set("exits/north", __DIR__"xiuxishi");
            set("exits/south", __FILE__, room);
            message("vision", "����ͻȻ������صĽŲ�������Զ����������ǰͣ������������\n"
                          "��������һ���Ӱ��Ŵ򿪣����ͷ�������������ֵ���ʲô����\n"
                          "������ĥĥ���ģ�\n", room);
            remove_call_out("close_men");
            call_out("close_men", 10);

            return 1;
}