// Room: /d/gumu/houting.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����Ҳ�ǿյ�����ûʲô���裬��ǰ��д��һ�д��֣�zi��������
���ڶ�����һ���������� (westpic)�Ļ���������Ů�ɣ����ǹ�Ĺ�ɵ�
ʦ���ֳ�Ӣ��ʦ�����ŵ�Ф�񣬶��� (eastpic)������ȴ��һ����ʿ��
���������룬�ڷ��ż��߹ײ�(coffin)������ֻ��һ�߹ײĵĹװ�û��
���ϣ��ײ��к���տ���Ҳ��
    ������Կ�����һ�Ȱ���(door)��
LONG    );

        set("exits", ([
                "east"  : __DIR__"mudao18",
//              "west"  : __DIR__"mudao06",
                "north" : __DIR__"mudao07",
                "south" : __DIR__"mudao19",
        ]));
        set("count", 1);
        set("item_desc", ([
                "door" : "һ�Ⱥ��ص�ʯ�ţ��������ȫû�а��֡������濴�˿��������űߵ�ʯ�����ƺ���ʲô��ť(niu)���Կ��š�\n",
                "westpic" : HIM"�����������һ����ʮ�����꣬���ڶԾ���ױ�����о���ӳ��Ů����ò��������ü���ޣ��۽�ȴ��������һ��ɱ�������ǹ�Ĺ��ʦ���ֳ�Ӣ����һ����ʮ�������Ѿ�ߣ��ֳ����裬�����ź򣬺�̬���䣬�������������������С��Ů
��ʦ����\n"NOR,
                "eastpic" : HIC"���е���������ߣ���������������ʳָָ�Ŷ����ǣ�ֻ�Ǳ������⣬��òȴ��������\n"NOR,
                "zi" : HIR"\t���ҹ�Ĺ�����������������񹦣�������ʦ��\n"NOR,
                "coffin" : WHT "\n�ú���ʯ�����ɵĹײģ��װ���Ϻ󣬾�û"
                           "��һ˿�ķ�϶�ˡ�\n" NOR
        ]));
        set("coor/x", -3180);
        set("coor/y", 10);
        set("coor/z", 90);
        if (random(10) > 8)
                set("getbook", 3);
        setup();
}

void init()
{
        add_action("do_ketou", "ketou");
        add_action("do_tuo", "tuo");
        add_action("do_an", "press");
        add_action("do_an", "an");
        add_action("do_tang", "tang");
        add_action("do_niu", "niu");
}

int do_ketou(string arg)
{
        mapping fam;
        object me = this_player();

        if ((!arg) || (arg != "westpic")) return 0;
                message_vision("$N�����򵹣�˫ϥ���أ�������������ʦ���ŵĻ������һ����ͷ��\n", me);
        addn_temp("marks/ketou", 1, me);
        me->receive_damage("qi", 5);
        if( query_temp("marks/tuo", me) == 2 && 
                query_temp("marks/ketou", me) == 4 && 
                (!(fam=query("family", me)) || 
                fam["family_name"] != "��Ĺ��") &&
                query("combat_exp", me)<10000 )
        {
                set("family_name", "��Ĺ��", me);
                set("title", HIW"��Ĺ����"NOR, me);
                me->create_family("��Ĺ��", 5, "����");
                set("class", "swordsman", me);
                write(HIR"��ϲ����Ը��Ϊһ����Ĺ���ӡ�\n"NOR);
                delete_temp("marks/tuo", me);
                delete_temp("marks/ketou", me);
                return 1;
        }
        if( query_temp("marks/ketou", me) == 15 )
        {
                delete_temp("marks/ketou", me);
                if (query("count") == 0)
                        return notify_fail("����¶��һ��С�ף�������տ���Ҳ������������������ˡ� \n");
                message_vision(HIY "$N��ǰ��ʯ��ͻȻ�³���¶��һ�ѽ�Կ�ף�$N��������������\n"NOR, me);
                set("count", 0);
                new(__DIR__"obj/goldkey")->move(me);
        }
        return 1;
}

int do_tuo(string arg)
{
        object me = this_player();

        me->receive_damage("qi", 5);
        if( query_temp("marks/tuo", me) == 2 )
                return notify_fail("���ٹ���û�У�\n");
        if ( arg=="eastpic")
        {
                message_vision("$N���������Ļ���ݺ�����һ�ڡ�\n", me);
                addn_temp("marks/tuo", 1, me);
                return 1;
        }
        return notify_fail("�㲻Ҫ������ٿ�ˮ����\n");
}

int do_an(string arg)
{
        object room, me = this_player();

        if( !arg || arg != "niu" )
        {
                message_vision("����ʯ�����Ұ�һ��������һ�ֻң�ɶҲû���š�\n", me);
                return 1;
        }
        if( query("exits/west"))
        {
                return notify_fail("ʯ���Ѿ��ǿ��ŵģ��㻹����ɶ��\n");
        }
        if( me->query_skill("yunv-xinfa", 1) > 10)
        {
                message_vision("$Nվ��ʯ��ǰ��Ҳ��֪�����ﰴ��һ�£�ʯ��֨֨���ţ��������ˡ�\n", me);
                if( !(room = find_object(__DIR__"mudao06")) )
                        room = load_object(__DIR__"mudao06");
                set("exits/west", __DIR__"mudao06");
                set("exits/east", __DIR__"houting", room);
                tell_room(room,"ֻ����ʯ����֨֨���б������򿪡�\n");
                remove_call_out("close");
                call_out("close", 5, me);
        }
        else
                message_vision("$N������ʯ���ϰ�����ȥ������ʯ����˿������ֻ�ð��ˡ�\n", me);
        return 1;
}

void close(object me)
{
        object room;

        tell_room(this_object(), "ʯ�Ż����ع��ϣ��ָ���ԭ״��\n");
        delete("exits/west");
        if( !(room = find_object(__DIR__"mudao06")) )
                room = load_object(__DIR__"mudao06");
        delete("exits/east", room);
        tell_room(room,"��ǽ�İ��Ż����ع����ˡ�\n");
}

int do_tang(string arg)
{
        object ob, paper;
        object me = this_player();

        if (! arg || arg != "coffin")
                return notify_fail("��Ҫ�����Ķ���\n");

        if( query_temp("tmarks/��", me) )
                return notify_fail("�������Ѿ��ɽ��ײ��ˡ�\n");

        paper = present("paper", me);

        if (query("getbook") >= 1
           && objectp(paper)
            && query("can_draw", paper) >= 1 )
        {
                message_sort(HIW "\n$N" HIW "�ɽ��ײ��У��ѹװ���ϣ���ʱһƬ"
                             "�ڰ����ƺ���쳾�����ˣ�������$N" HIW "�����װ�"
                             "�ڱ��������֣�ϸϸ��������һͷд�š�" HIY "��Ů"
                             "�ľ�����ѹȫ�档����һ������������" HIW "��ʮ��"
                             "�����֣���һͷ������Щͼ����ķ��š�$N" HIW "��"
                             "֪���ԣ��������ϴ���ֽ�ţ���������������˵������"
                             "ϸϸ�ؽ���������ȫ��������������������֮�䣬����"
                             "�׽��Ͼ�����һ��͹��Ļ���(lock)��\n\n" NOR, me);
                ob = new("/clone/lonely/book/zhenjing3");
                ob->move(me, 1);

                tell_object(me, HIC "��õ���һ��" NOR + ob->name() +
                                HIC "��\n\n" NOR);

                addn("getbook", -1);
                destruct(paper);
        } else
        if (query("getbook") >= 1)
        {
                message_sort(HIW "\n$N" HIW "�ɽ��ײ��У��ѹװ���ϣ���ʱһƬ"
                             "�ڰ����ƺ���쳾�����ˣ�������$N" HIW "�����װ�"
                             "�ڱ��������֣�ϸϸ��������һͷд�š�" HIY "��Ů"
                             "�ľ�����ѹȫ�档����һ������������" HIW "��ʮ��"
                             "�����֣���һͷ������Щͼ����ķ��š�$N" HIW "��"
                             "Ȼ�Ķ�����������Χһ����ڣ������޷����壬ֻ����"
                             "�ա�ͻȻ�䣬�����׽��Ͼ�����һ��͹��Ļ���(lock)"
                             "��\n\n" NOR, me);
        } else
        {
                message_sort(HIW "\n$N" HIW "�ɽ��ײ��У��ѹװ���ϣ���ʱһƬ"
                             "�ڰ����ƺ���쳾�����ˣ�������$N" HIW "�����װ�"
                             "�ڱ��������֣�ϸϸ��������һͷд�š�" HIY "��Ů"
                             "�ľ�����ѹȫ�档����һ������������" HIW "��ʮ��"
                             "�����֣���һͷ������Щͼ������š������ּ��ѱ���"
                             "����ε���ͻȻ�䣬�����׽��Ͼ�����һ��͹��Ļ���"
                             "(lock)��\n\n", me);
        }

        set_temp("tmarks/��", 1, me);
        return 1;
}

int do_niu(string arg)
{
        object me = this_player();

        if( !arg || arg != "lock" || !query_temp("tmarks/��", me) )
                return notify_fail("��ҪŤ��ʲô��\n");

        message_sort(HIY "\n$N" HIY "���ջ��أ���������Ť������Ȼ"
                     "��׵�֨֨���죬�ѿ���һ���󶴣�$N" HIY "��"
                     "����������ȥ��\n\n" NOR, me);
        me->move(__DIR__"mishi2");

        delete_temp("tmarks/��", me);
        return 1;
}
void reset()
{
        if (random(10) > 8)
                set("getbook", 3);
        ::reset();
}