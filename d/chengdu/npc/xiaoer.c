// xiaoer2.c �Ƶ�С��

#include <ansi.h>
inherit KNOWER;

void create()
{
        set_name("��С��", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "����" );
        set("age", 22);
        set("long",
                "��λ��С����Ц�����æ��������ʱ������ڲ����ϵ�Ĩ��������\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "С����");
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
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "��С��Ц�����˵������λ" + RANK_D->query_respect(ob)
                                + "�������ȱ��裬ЪЪ�Ȱɡ�\n");
                        break;
                case 1:
                        say( "��С���ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob)
                                + "����������\n");
                        break;
        }
}

int accept_object(object me, object ob)
{
        
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                tell_object(me, CYN "С��һ������˵������л���ϣ��͹�����¥ЪϢ��\n" NOR);
                set_temp("rent_paid", 1, me);
                return 1;
        }

        switch (random(6))
        {
        case 0:
                command("say �ã��ã�");
                break;
        case 1:
                command("say ����Ҫ�Ķ���ȫ���ң�");
                break;
        }

        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }
        return 1;
}
