// xiaofan.c С����

inherit KNOWER;
inherit F_DEALER;
#include <ansi.h>

void create()
{
        set_name("С����", ({ "xiao fan", "xiao", "fan" }) );
        set("gender", "����" );
        set("age", 34);
        set("long", "���Ǹ�С����������������ʵʵ�������������Ƕ��ͱ��ˡ�\n");
        set("combat_exp", 300);
        set("attitude", "peaceful");
        set("rank_info/respect", "С����");
        set("vendor_goods", ({
                "/d/mingjiao/obj/book",
                "/d/village/npc/obj/stick",
                "/d/village/npc/obj/shoes",
                "/d/village/npc/obj/bottle",
        }));
        setup();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch(random(2)){
          case 0:
          say(CYN"С����Ц�����˵������λ"+RANK_D->query_respect(ob)+"��Ҫ���̼�ʷ��\n"NOR);
          break;
          case 1:
          break;
        }
}
