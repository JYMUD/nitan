// xiucai.c
inherit NPC;

void create()
{
        set_name("�����", ({ "lao xiucai", "lao" }));
        set("long", "һ�������ʵ��������ţ������￪���ڿ�Ϊ����\n");
        set("gender", "����");
        set("age", 65);

        set_skill("literate", 100);
        set_skill("taoism", 100);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 40000);
        set("shen_type", 1);
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/��", ob) )
                return 0; 
        addn_temp("mark/��", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        if( !query_temp("mark/��", who) )
                set_temp("mark/��", 0, who);
        if( query("money_id", ob) && ob->value() >= 5000){
                message_vision("�����ͬ��ָ��$NһЩ���⡣\n", who);
                addn_temp("mark/��", ob->value()/250, who);
                return 1;
        }
        return 0;
}