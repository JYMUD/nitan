// jia.c 

inherit NPC;

void create()
{
        set_name("���˴�", ({ "jia renda", "jia", "renda" }));
        set("gender", "����");
        set("age", 25);
        set("long", "�����ǡ�����ɡ�����Ϊͬ�Ų��ݡ����´�ļһ\n");

        set("combat_exp", 30000);
        set("shen_type", -1);

        set_skill("sword", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("strike", 30);
        set_skill("unarmed", 30);
        set_skill("force", 30);
        set_skill("bixie-sword", 30);
        set_skill("songfeng-jian", 30);
        set_skill("chuanhua", 30);
        set_skill("wuying-leg", 30);
        set_skill("cuixin-zhang", 30);
        set_skill("qingming-xuangong", 30);
        map_skill("force", "qingming-xuangong");
        map_skill("unarmed", "wuying-leg");
        map_skill("strike", "cuixin-zhang");
        map_skill("dodge", "chuanhua");
        map_skill("parry", "bixie-sword");
        map_skill("sword", "songfeng-jian");
        prepare_skill("unarmed", "wuying-leg");
        prepare_skill("strike", "cuixin-zhang");
        create_family("�����", 6, "����");
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/bluecloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( query("gender", ob) == "Ů��" )
                say("���˴���ƤЦ��������λ���������Ӳ��Ҫ�á�һ�������
ȴ�Ƕ�Ь̤���࣬��תʯ��Ƥ�������Ӻ�һ�Ŵ���Ƥ��\n");
        else say("���˴���˰��ۣ������ӵģ������ö�ү��˭��\n");
        return;
}
