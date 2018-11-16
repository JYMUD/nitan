#include <ansi.h>;

inherit KNOWER;
inherit F_DEALER;

void create()
{
        set_name("��·����", ({ "milu shangren", "milu", "shangren" }));
        set("gender", "����" );
        set("age", 43);
        set("long", "����һλ��·�����ˣ��˳���Ϊ��Ѱ�������ɵ�����·�ġ�\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        
        set("inquiry", ([
                "���"       :   "�Ҿ���Ϊ����Ҷ�������ϧ���û�ҵ���ȴ��·�ˣ��� ������\n",
                "�����ɵ�"   :   "��Ϊ��Ѱ�Ҵ�˵�е���ң��������ȴ��·�� ������\n",
        ]));
                
        set("vendor_goods", ({
                "/d/city/obj/jitui",
                "/d/city/obj/jiudai",
                "/d/city/obj/baozi",
                "/d/city/obj/kaoya",
                "/clone/fam/pill/food",
                "/clone/fam/pill/water",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob;

        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        switch(random(2))
        {
        case 0:
                say(CYN "��·����Ц�����˵������λ" + RANK_D->query_respect(ob) +
                    CYN "��������ʲô��Ҫ�ģ�����ѡ��\n" NOR);
                break;
        case 1:
                say(CYN "��·����ߺ�ȵ�����λ" +
                    RANK_D->query_respect(ob) + CYN "����Ҫʲô����˵��������۸񹫵���\n" NOR);
                break;
        }
}
int accept_object(object me, object obj)
{                                
        object ob;
        
        if (obj->query("id") == "penglai pantao" &&
            base_name(obj) == "/d/penglai/obj/pantao")
        {
                command("nod");
                message_vision(HIC "$N" HIC "�ӹ�" + obj->name() + HIC "��һ�����ȵ����� ���� 󴡭����ҡ���ʵ��̫��л�ˡ���\n" NOR, this_object());
                message_vision(NOR + CYN "\n$N" NOR "�ó�ʮ��������" + me->name() + NOR + CYN "��\n" NOR, this_object(), me);
                ob = new("/clone/money/silver");
                ob->set_amount(10);
                ob->move(me, 1);
                destruct(obj);
                return 1;
        }
        return 0;        

}