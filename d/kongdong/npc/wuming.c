//һ������ָ����ἵ����书��NPC�����Կ��������ɵĻ���
//�����޶������Һ��ٳ��֡�
// Qyz

inherit F_UNIQUE;
inherit NPC;



void create()
{
        set_name("��������", ({ "lao zhe","zhe", "old" }) );
        set("title","");
        set("gender", "����" );
        set("age", 110);
        set("cor", 40);
        set("cps", 40);
        set("per", 40);
        set("int", 40);
        set("chat_chance", 10);
        set("chat_msg", ({
                    (: random_move :)
                    }) );

        set("attitude", "friendly");
        set("can_teach",1); 
        set("max_gin", 1000);
        set("max_kee", 1000);
        set("max_sen", 1000);
        set("eff_gin", 1000);
        set("eff_kee", 1000);
        set("eff_sen", 1000);
        set("gin", 1000);
        set("kee", 1000);
        set("sen", 1000);
        set_wugong("hujia-dao",150,150,1);
        set_xiuwei_by_type("blade",5300);
        set("max_force", 10000);
        set("force", 10000);
        set("force_factor",1000);

        set("long",     "����һλ�ɷ���ǵ��ϵ��ˣ����ô�ü��Ŀ�����ǿ��ס�\n");
        set("chat_chance_combat", 20);      
        set("chat_msg_combat", ({
        (: SKILL_D("hujia-dao")->perform_action(this_object(), "weizhen-bafang") :),
           }) );  

        set("combat_exp", 99999999);
        set_wugong("kongdong-xinfa",1000,1000,1);

        set("positive_score",10000);
        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/bidao")->wield();
}

int valid_teach( object ppl, string skill )
{
	
   
    if (ppl->query("family/family_name") != "�����")      //���û��ѧ����ı��
    {
        command( "say ���Ǻǣ��þ�û�˺��Ϸ�˵��������" );
        return 0;
    }
   
    if (ppl->query("marks/kongdong/zhou") != 1) 
    {
        command( "say �������������ô����" );
        return 0;
    }
    if ( !query_jibie( skill ) )
        return 0;
     
     
    if( ppl->query("class_score/�����") < 500 )
        {
        command( "say ���������ɽס��ʮ���ˣ���ô���������㣿��" );
        return 0;
           
        }
    if( skill=="kongdong-xinfa")
    return 1;   
    if( skill=="hujia-dao"&&random( (int)ppl->query("kar") ) < 20 &&ppl->query_jibie("hujia-dao")<1) 
     {
        command( "say �������˿����������������Ҳ��ܽ��㣡��" );
        ppl->add("gin",-20);
        return 0;
    }
       if(skill=="hujia-dao"&& ppl->query_xiuwei_by_type("blade")<1500)
     {
        command( "say ����ϧ����Ϊ�������������ҼҴ��ĺ��ҵ�������" );
        return 0;
    }  
    command( "say �������ҵ�һ�����Է����Һ��ҵ����ĺ��ˡ���" );
    command( "haaa" );
    return 1; 

}


int zhongcheng( object ppl, string skill )  //������ҳ϶�
{
    return 1;
}

