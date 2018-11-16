#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("Ǯ��", ({ "qian bo", "qian", "bo" }));
        set("nickname", HIM "��������" NOR);
        set("title", "�ӻ����ϰ�");
        set("long", @LONG
һ�����ֵ��ϰ壬��һЩ��ͨ����Ʒ����ʹ�� list �鿴�ɹ������Ʒ��
LONG);
        set("gender", "����");
        set("age", 44);
        set("per", 24);
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_temp("apply/damage", 25);
        set("combat_exp", 800000);
        set("no_get", "1");
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/xingxiu/obj/fire",
                "/d/henshan/obj/mujian",
                "/d/city/obj/rrose",
                "/d/city/obj/yrose",
                "/clone/misc/wood",
        }));
        
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{        
        object ob; 

        ob = this_player();

        ::init(); 
        add_action("do_buy", "buy"); 
        add_action("do_list", "list"); 

        if( interactive(ob) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say(CYN "Ǯ��Ц��˵������λ" + RANK_D->query_respect(ob)+ "����"
            "��Щʲô������㿴������ָ�� list �鿴����\n" NOR);

        return;
}











