// seller.c

inherit KNOWER;
inherit F_DEALER;

string ask_me();

void create()
{
        set_name("С��", ({ "seller" }) );
        set("gender", "����" );
        set("age", 32);
        set("long",
                "���Ǹ�С����������������ʵʵ�������������Ƕ��ͱ��ˡ�\n");
        set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("count", 1);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/stick",
                __DIR__"obj/bottle",
                __DIR__"obj/egg",
                "/d/xingxiu/obj/fire",
        }) );
        set("inquiry", ([
                "ҩ" : (: ask_me :),
                "ҩ��" : (: ask_me :),
        ]) );
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
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
        object me=this_player();
        if( query_temp("tmark/ҩ", me)){
                return "�����ϴ�����û��������ô���µ��ˣ�\n";
        }
        else
        {
                set_temp("tmark/ҩ", 1, me);
                return "�����ҵ�����ɭ���в�ҩ������������һЩ��ҩ�ģ�Ҫ����Ƚ�
Ǯ��\n";
        }
}

int accept_object(object who, object ob)
{
        object obj;

        if( query("count", this_object())<0 )
        {
                write("С��˵��������Ȼ���������Ǯ������û����������û�ˡ���\n");
                return 1;
        }
        if( (query("money_id", ob)) && (ob->value() >= 10000) && 
                (query_temp("tmark/ҩ", who)) )
        {
                obj = new(VEGETABLE_DIR"heshouwu");
                obj->move(who);
                addn_temp("tmark/ҩ", 0, who);
                write("С��˵��������Ȼ���������Ǯ����ζҩ�ɾ͹����ˡ���\n");
                addn("count", -1);
                return 1;
        }
        else
                if( query("money_id", ob) )
                {
                        write("С����Цһ����˵�������ٺ٣�������ô��Ǯ�ġ���\n");
                        return 1;
                }
                else
                {
                        return notify_fail("С�������˵���������������ʲô����\n");
                }
}
