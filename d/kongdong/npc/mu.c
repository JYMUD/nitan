// mu.c

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string leave_kongdong( object );



void create()
{
        seteuid(getuid());
        set_name("ľ����", ({ "mu lingzi", "mu","lingzi" }) );
        set("class","taoist");
        set("gender", "����" );
        set("age", 50);
        set("str", 30);
        set("cor", 30);
        set("cps", 30);
        set("int", 25);
        set("ker", 24);
        set("kar", 30);
        set("max_force", 1500);
        set("force", 1500);
        set("force_factor", 3);

        set("rank_info/respect", "������");

        set("long",
    "ľ���Ӻ�����棬һ�������޵��г�֮�ˣ�����Щ�ɷ����֮�ࡣ\n");

        create_family("�����", 1,"������");
        set("positive_score",30000);
        set("combat_exp", 1000000);
        set("social_exp", 200000);

	set_wugong("kongdong-xinfa",130);
    set_wugong("unarmed",100,100,0);
	set_wugong("shizi-zhan",100);
	set_wugong("dahong-quan",100);
	set_wugong("wulong-quan",100);
    set_wugong("qishang-quan",120,120,1);
	set_xiuwei_by_type("unarmed",2300);
	set_wugong("sword",100);
    set_wugong("fengyun-jian",100);
    set_wugong("qimen-bagua",300);
	set_wugong("kongling-jian",100);
	set_xiuwei_by_type("sword",900);
	set_wugong("jiben-qinggong",100);
	set_wugong("nieyun-bufa", 100,100,1);
	set_wugong("luofeng",100,100,1);
	set_xiuwei("dodge",900);
	
	set( "inquiry",([ /*sizeof() ==1 */
	    "��ʦ" : (: leave_kongdong :),
	]) );

    set("env/attack", 75);
    set("force_factor", 20);

    setup();
    carry_object(__DIR__"obj/cloth1")->wear();
}

void init()
{

	add_action("give_quest", "quest" );

}

void attempt_apprentice(object ob)
{
         //Hydra 19980507 for ��ʦ
        if( ob->query("hydra/��ʦ/�����") )
        {
            message_vision(CYN"$N��$n˵������������뿪ʦ�ţ���ô�ֻ���"
"���أ���\n"NOR,this_object(),ob);
            return 0;
        }
        if( (int)ob->query("PKS") > 10 ) 
        {
                command("hmm");
                command("say ������Ѫ��Ũ�أ���������õ���\n");
                return;
        }
        if ( ob->query("gender") == "����" )
        {
                command("heihei");
                command("say ����һ���˸�֮�ˣ���������õ���\n");
                return;
        }
        command("en");
        say("ľ����Ц��������λ"+RANK_D->query_respect(ob)+"���Ǹ�����֮��ѽ��\n"
            "�������ܷ������������ͥ��\n");
        command("recruit "+ob->query("id") );
        ob->delete("master");
        ob->set("class","taoist");
        ob->set_family("title","��ɽ�����");
}


//Hydra:add for ��ʦ 19980507
string leave_kongdong( object me )
{
    object this;
    me = this_player();
    this = this_object();

    if( me->query("hydra/��ʦ/�����"))
    {
        return "�㲻���Ѿ���ʦ����";
    }
    if( me->query("family/family_name") != "�����" )
    {
        command( "? "+me->query("id") );
        return "�����������������˰���";
    }
    if( me->query_temp("��ʦ�Ȼ�"))
    {
        return "�Ҳ��������ȸ��ұȻ�һ����";
    }
    
    if( me->query( "class_score/�����" ) < 1000 )
    {
        message_vision(CYN"$N��$n���������������¶��꣬Ϊʦ������"
"δ��̫����һЩ����\n"NOR,this,me );
        if(me->query("class_score/�����") > -50 )
            me -> add( "class_score/�����",-10);
        return "�㻹����Ϊ���ʦ�Ŷ�ɵ��°ɣ�\n";
    }

    if( me->query_jibie("qishang-quan") > 80 )
    {
        if( me->query("age") < 20 )
        {
            message_vision(CYN"$N��$n˵���������������ͳ�ȥ���˼һ���Ϊ�������"
"���˵ġ���\n"NOR,this,me);
            if(me->query("class_score/�����") > -50 )
                me -> add( "class_score/�����",-10);            
            return "��������˵�ɡ�\n";
        }
        else
        {
            me->set_temp("��ʦ�Ȼ�",1);
            return "���ȿ��ָ�Ϊʦ�Ȼ�һ�£����ҿ�����ȭ�Ź�������ˡ�";
        }
    }
    else
    {
        return "�������ڵ�ʵ���������ڽ����϶���һ�棬���Ǹ�Ϊʦ��ѧѧ�ɣ�";
    }
    return "";
}        

int accept_fight( object ppl )
{
    object this;
    this = this_object();
    
    if( ppl-> query_temp( "��ʦ�Ȼ�" ))
    {
        if(this->is_fighting() )
        {
            return notify_fail( "����ľ���Ӳ��ܸ���Ȼ���\n");
        }    
        if(ppl->query_temp("weapon"))
            return notify_fail("ľ���ӵ������Ҳ���������ָ��ұȻ��𣿡�\n");
        this->set( "eff_kee",this->query("max_kee"));
        this->set( "kee",this->query("max_kee"));
        this->set( "eff_sen",this->query("max_sen"));
        this->set( "sen",this->query("max_sen"));
        this->set( "force",this->query("max_force"));
        this->set( "force_factor",100);
        this->set( "env/attack",90 );
        message_vision(CYN"$N�������ã����аɡ���\n",this);
        return 1;
     }
     return ::accept_fight( ppl );
}

int lose_bihua( object ppl)
{
    object this;
    this=this_object();
    if( ppl->query_temp("��ʦ�Ȼ�"))
    {
        command( "chat* haha" );
        command( "chat ���������Ҳ����һ���˲š�");
        command( "say �����������ʤ����������Ĺ����Ѿ���Ϊʦ�ĸ��ˡ�");
        command( "say ��ˣ������ı�߾�ȥ�ɡ�");  
        ppl -> delete_temp("��ʦ�Ȼ�");    
        ppl -> set("title","��ͨ����");
        ppl -> delete("family");
        ppl -> delete("class");
        ppl -> set("hydra/��ʦ/�����",1);
             LOG_D->do_log(ppl,sprintf("������ľ���ӵ���������ἳ�ʦ��\n"));
        log_file("chushi",sprintf("%s(%s)��%s˳������ἳ�ʦ��\n",ppl->query("name"),
            getuid(ppl),ctime(time()) ) );
        message_vision("$N���������ع�����������$n�����ĸ���ͷ��\n",ppl,this);
    }
    return 1;
}
        
int win_bihua( object ppl )
{
    object this;
    this=this_object();
    if( ppl->query_temp("��ʦ�Ȼ�"))
    {
        command("pat "+ppl->query("id"));
        command("say ����Ϊʦ�Ĺ����Ը���һЩ��������ѧһ��ġ�");
        ppl->delete_temp("��ʦ�Ȼ�");
        if(ppl->query("class_score/�����") > -50 )
            ppl->add("class_score/�����",-10);
    }
    return 1;
}
            
void heart_beat()
{
    object this,ob;
    string *bihua;
    this = this_object();
    bihua = this->query_bihua();
    
    foreach( string name in bihua )
    {
       if( objectp( ob=find_player(name)) && 
           ob->query_temp("��ʦ�Ȼ�") && 
           ob -> query_temp("weapon") )
       {
           if(ob->query("class_score/�����") > -50 )
               ob -> add( "class_score/�����",-100);
           command("heng "+ob->query("id"));
           command("say �Ҳ���������ָ��Ҵ���𣿾�Ȼ����ƭʦ������");
           command("stop");
        }
    }
    return ::heart_beat();
}
