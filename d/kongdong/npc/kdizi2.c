inherit NPC;


void create()
{
        set_name("�����ʿ", ({ "kanchai daoshi","daoshi" }) );
        set("title","��ἵ���");
        set("gender", "����" );
        set("age",24);
	create_family("�����", 2, "����");
	set_xiuwei("staff",200);
	set_xiuwei("dodge",300);
        set_wugong("dodge",20,20,1);
        set("combat_exp",2000);
        set("social_exp",2000);
        setup();    
        carry_object(__DIR__"obj/cloth2")->wear();
        carry_object(__DIR__"obj/chaidan")->wield();
}
