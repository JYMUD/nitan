inherit NPC;
inherit F_VENDOR;
int get_reward();
void create()
{
        set_name("����ʹ��", ({ "jieri shizhe" }) );
        set("gender", "Ů��" );
        set("age", 14);
        set("title", "�绨����");
        set("long",
                "����ʹ�ߡ�����������������йؽ��������飨reward��\n");
        set("combat_exp", 500000);
        set("attitude", "friendly");
        set("per",30);
        set("vendor_goods", ([
                __DIR__"obj/white_towel":11,
        ]) );
        set("inquiry", ([
                "reward" : (: get_reward :),
        ]));
        setup();
        carry_object(__DIR__"obj/green_cloth")->wear();
} 
void init()
{       
        object ob; 
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_vendor_list", "list");
} 
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(3) ) {
                case 0:
                        message_vision("$N�ڰ�æ��̧��ͷ����$nһ�ۡ�\n",this_object(),ob);
                        break;
        }
}
int get_reward()
{
        object me;
        string ret;
        me =this_player();
        ret=FESTIVAL_D->get_reward(me);
        tell_object(me,ret);
        return 1;
}      

