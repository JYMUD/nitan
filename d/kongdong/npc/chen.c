inherit NPC;


void create()
{
    set_name("�º���", ({ "chen hanjing","chen","jing" }) );
    set("title","����ɴ�ʦ��");
    set("gender", "����" );
    set("class","taoist");
    set("positive_score",8000);
    set("age",25);
	set_hp("sen", 600 );
	set_hp("kee", 600 );
	create_family("�����", 2, "����");
    set_wugong("jiben-qinggong",100,100);
    set_wugong("nieyun-bufa",60,65,1);
    set_wugong("luofeng",50,50,1);
	set_xiuwei_by_type("dodge",500);
    set_wugong("unarmed",100,100);
    set_wugong("dahong-quan",100,100);
    set_wugong("shizi-zhan",90,86,1);
    set_wugong("wulong-quan",60,60,1);
	set_xiuwei("unarmed",800);
    set("social_exp",2000);
    set("combat_exp",10000);
    set("force",200);
    set("max_force",200);
    set("force_factor",10);
    setup();
    carry_object(__DIR__"obj/cloth2")->wear();
}

void init()
{
        object ob;
        ob = this_player();
       ::init();
        if(interactive(ob=this_player()) && !is_fighting()){
            remove_call_out("say_hi");
            call_out("say_hi",1,ob);
            }
}

void say_hi(object ob)
{
        if(!ob||!present(ob,environment(this_object())))return;
        if(ob->query("family/family_name")!="�����")
        {
                message_vision("�º�����$Nһ���֣���λ"+RANK_D->query_respect(ob)+"��"
                "��ʦ�������棬������ɡ�\n",ob);
			return;
        }
        message_vision("�º���Ц������$N�ļ����ô���������г����𣿺ú����ɡ�\n",ob);
		return;
}

                
int accept_object( object ppl, object obj )
{
    object gold;

    if ( obj->query( "id" ) != "teng xia" ) 
        return 0;
    if ( query( "box" ) )               
    {
        message_vision( "�º�������$N��ȵ���������̫ү��ô��������������У���"
            + RANK_D->query_rude( ppl ) + "������ƭ�Ϸ򣡡�\n", ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        remove_call_out( "Dest" );
        call_out( "Dest", 1, obj );
        return 1;
    }

    if ( ppl->query( "mud_age" ) < 3600 * 24 * 2        //������������ʮ������
        && ppl->query( "combat_exp" ) < 50000           //���鲻��һ��
        && ppl->query( "max_force" ) < 1000 )            //�������������٣������
    {
        message_vision ( "�º������´�����$N��ã�ͻȻ�ٺ���Ц�������ߣ���ƾ��\n"
            + "��ô����У�Ҳ�����ڣ�������ô���ģ�������ʵ����������\n",
            ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        remove_call_out( "Dest" );
        call_out( "Dest", 1, obj );
        return 1;
    }
        
    message_vision( "�º�������$N��ͷ��Ц��Ц�������ܺã�����������̫ү����ʦ��\n"
        + "��Щ�������ڵı��꣬�ú�Ŷ����\n", ppl );
    call_out( "Dest", 1, obj );
    set( "box", 1 );                    
    gold = new( MONEY_DIR + "gold" );       
    gold->set_amount( 10 );
    gold->move( ppl );
    command("chat ��ϲ��"+ppl->query("name")+"("+ppl->query("id")+")"+"���ڳɹ������ʮ�����ӵı��ꡣ");
    return 1;
}

void Dest( object obj )
{
       destruct( obj );
}

