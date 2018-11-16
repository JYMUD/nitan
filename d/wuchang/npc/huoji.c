//Edited by fandog, 02/15/2000

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("���", ({ "huo ji", "huo", "waiter" }) );
        set("gender", "����" );
        set("age", 17);
        set("long",
                "��λС�����Ц�����æ��������ʱ������ڲ����ϵ�Ĩ��������\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "С���");
        set("no_get", "1");
        set("vendor_goods", ({
                "/d/jingzhou/obj/donggua",
                "/d/jingzhou/obj/houtou",
                "/d/jingzhou/obj/longfeng",
                "/d/jingzhou/obj/tianma",
                "/d/jingzhou/obj/wuchangyu",
                "/d/jingzhou/obj/xianggu",
                "/d/jingzhou/obj/zzjiayu",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;
        mapping myfam;

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) {
                if( (myfam=query("family", ob) )
                && myfam["family_name"] == "ؤ��"
                && ob->query_skill("begging",1) > 10 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
                {
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say("С���Ц�����˵������λ" + RANK_D->query_respect(ob) + "������ȱ��裬ЪЪ�ņ~��\n");
                        break;
                case 1:
                        say("С����ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob) + "������ʲô�£�\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n��С�����һ���������Ҫ���Ľ�����ʲ�᣿ ���ҹ���ȥ��\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);

}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

  ob->move("/d/wuchang/hzjie1");
        message("vision","ֻ����ƹ����һ����"+query("name", ob)+"���˴��ļ�����һ�����˳������Ǳ���״���ӿ��ˡ�\n",environment(ob),ob);
}