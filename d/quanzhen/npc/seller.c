#include <ansi.h>

inherit KNOWER;
inherit F_DEALER;

string ask_me();

void create()
{
        set_name("С��", ({ "xiao fan", "xiao", "fan" }));
        set("gender", "����" );
        set("age", 32);
        set("long", "���Ǹ�С����������������ʵʵ�������\n"
                    "������Ƕ��ͱ��ˡ�\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/stick",
                __DIR__"obj/bottle",
                __DIR__"obj/egg",
                "/d/xingxiu/obj/fire",
        }));
        set("inquiry", ([
                "ҩ��"   : (: ask_me :),
                "����"   : (: ask_me :),
                "������" : (: ask_me :),
        ]));

        set("count", 3);

        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        add_money("coin", 100);
}

void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy", "buy");
}

string ask_me()
{
        object me = this_player();

        if (query("count") < 1)
        {
                return "ʵ�ڶԲ�ס������������Ҳû���ˡ�\n";
        } else
        if( query_temp("tmark/ҩ", me) )
        {
                return "�����ϴ�����û��������ô���µ��ˡ�\n";
        } else
        {
                set_temp("tmark/ҩ", 1, me);
                return "�ҵ�����ɭ���в�ҩ������������һЩ��ҩ�ģ�Ҫ����Ƚ�Ǯ��\n";
        }
}

int accept_object(object who, object ob)
{
        object obj;

        if( !query("money_id", ob) )
        {
                write(CYN "С�������˵��������������ʲô��\n" NOR);
                return 0;
        }

        if (query("count") < 1)
        {
                write(CYN "С����Ǹ��˵����ʵ�ڶԲ�ס������������Ҳû���ˣ�\n" NOR);
                return 0;
        }

        if( !query_temp("tmark/ҩ", who) )
        {
                write(CYN "С���ɻ��˵�������ֲ�����ؤ����û�¸���Ǯ���\n" NOR);
                return 0;
        }

        if (ob->value() < 10000)
        {
                write(CYN "С����Ц��˵�����ٺ٣�������ô��Ǯ�ġ�\n" NOR);
                return 0;
        }

        obj = new(__DIR__"obj/shouwu");
        obj->move(this_object());

        addn("count", -1);
        command("giveheshouwuto"+query("id", who));
        write(CYN "С��˵������Ȼ���������Ǯ����ζҩ�ɾ͹����ˡ�\n" NOR);
        return 1;
}
