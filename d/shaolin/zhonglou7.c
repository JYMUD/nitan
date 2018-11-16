// Room: /d/shaolin/zhonglou7.c
// Date: YZC 96/01/19

inherit ROOM;

string look_bell();
string look_out();

void create()
{
        set("short", "��¥�߲�");
        set("long", @LONG
���������¥֮����ֱ�������ı����ǿڴ��Ӻ�һ�����ҿ��е�
���ơ�ϸ�����ӣ��������������ߣ�ֱ��Ҳ����������������ͭ��
���������������������ӡ�Ĺ�׭������������ǧ����ƴֿɺϱ���
�ɰ�������һͷ���Ժ�Ƥ������������������ɽ�紵��������˭����
��ס��ײһ����(bell)���ԡ����⿴���и��ܴ�ĺ�����̨(out)��
�������վһ���ˡ�
LONG );
        set("exits", ([
                "down" : __DIR__"zhonglou6",
        ]));
        set("item_desc",([
                "bell"                :        (: look_bell :),
                "out"                :        (: look_out :),
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/qing-xiao" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_knock", "knock");
        add_action("do_out", "out");
}

int do_knock(string arg)
{
        object me;
        mapping mine;

        me = this_player();
        if ( !arg || ( arg != "bell" ) ) return notify_fail("��Ҫ��ʲ�᣿\n");

        addn("qi", -20, me);


        mine = me->query_entire_dbase();
        message_vision("$N����һ�´��ӣ����ۡ���������������������\n", me);
        write("������Ѹ�װ��������ը�죬��ͷ����һƬ��Ϳ��\n"
                "ȫ��ҡҡ��׹������֧���Ų����ڵ��ϡ�����һ��\n"
                "���������㣬�øϿ��뿪�����Ȼ��û���ˡ�\n");

        if( random(2) == 0)addn("combat_exp", 1, me);
        else addn("combat_exp", -2, me);
        return 1;
}

int do_out(string arg)
{
        object me;
        int i, ging_cost, qi_cost;

        me = this_player();
        i = (int)me->query_skill("dodge") + random(5);

        ging_cost=600/query("dex", me);
        qi_cost=500/query("dex", me);

        if( (query("jing", me)<ging_cost) || 
            (query("qi", me)<qi_cost) )
                i = 0;

        message_vision("$N���ϴ�̨��һ������������ȥ��\n", me);
        me->move(__DIR__"zhonglou");
        me->start_busy(5);
        message_vision("ֻ�����须��һ��$N����������������\n", me);
        if (i < 50)
        {
                set_temp("die_reason", "������ʧ���������ˤ����", me);
                me->die();
        } else
        if (i < 125)
                me->unconcious();
        else
        {
                message_vision("$N�����ȵ�վ�ڵ��ϡ�\n", me);
                if( i>175 && query("dodge", me)<200 )
                        me->improve_skill("dodge",1+random(query("dex", me)));
                me->receive_damage("jing", ging_cost);
                me->receive_damage("qi", qi_cost);
        }

        return 1;
}

string look_bell()
{
        return
        "����������������������������������������������\n"
        "����������������������������������������������\n"
        "������������������������Ի��������������������\n"
        "����������������������������������������������\n"
        "��������������һ����У�ײһ���ӡ�������������\n"
        "����������������������������������������������\n"
        "�����������������롡����죩������������\n"
        "����������������������������������������������\n"
        "����������������������������������������������\n";
}

string look_out()
{
        return  "��������¥����Ĵ�̨�����������ң����������ɽ����\n"
"�Լ��������Ƶ���ɽ�������̳��������۵ס���˵�ڴ˵�\n"
"������������ֱ�ӽ����������޴����洦��\n";
}
