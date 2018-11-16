// This program is a part of NT MudLIB

inherit NPC;
int look_ob();
int ask_letter();
int do_suan(string str);
int ask_suanming();
string ask_mimi();
void create()
{
        set_name("������", ({ "shensuan zi", "shensuan" }) );
        set("nickname", "������");
        set("gender", "����");
        set("age", 66);
        set("long",
                "�����������ڰ��ͷſ��������˯������Һһֱ���������ӵ��¡�\n");
        set("attitude", "peaceful");
        set_skill("taoism", 300);
        set_skill("force",200);
        set("max_neili",5000);
        set("max_jingli",3000);
        set("letter", 1);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 20);
        set("combat_exp", 500000);
        set("shen_type", 1);

        set("inquiry", ([
                "����": (: ask_suanming :),
                "����": (: ask_mimi :),
                "��": (: ask_letter :),
        ]));

        setup();
        carry_object("/clone/cloth/changpao")->wear();
}
void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("look_ob");
                call_out("look_ob", 6, ob);
        }
}

int look_ob()
{
        foreach (object player in all_inventory(environment()) )
                command("look "+query("id", player));
        return 1;
}

int ask_suanming()
{
        if( query_temp("knock", this_player())){
                command("whisper "+query("id", this_player())+"û����⣬�Ϸ�ˡ�Ѵ�����\n");
                set_temp("knock", 0, this_player());
                return 1;
        }
        return 0;
}

string ask_mimi()
{
        object me=this_player();
        if( !query_temp("mimi", me))return "�����Ҳ�֪��Ҳ��";
        delete_temp("mimi", me);
        set_temp("letter", 1, me);
        return "�ܶ���ǰ���ҵ�үү��үү��������һ���ţ���֪������������һ�������ܡ�";
}

int ask_letter()
{
        object ob,me=this_player();
        int p1;
        if (query("letter") < 1)
                say("�����Ӻ��ź���˵���������������Ѿ������ˡ�\n");
        if( query("passwd1", me) )
        {
                say("�����Ӻܲ��ͷ���˵�����Ұ���֪���Ķ��������ˣ�����ʲô�\n");
        }else
        if( query_temp("letter", me) )
        {
                say("�����Ӻٺٵļ�Ц�˼�������������Ҫ���������\n");
                write("��������ͷ���˻ᣬ˵�����ðɣ�\n");
                p1=random(6)+1;
                set("passwd1", p1, me);
                write("����ŵĺ����Ѿ��������ˣ�������Լ�ǵ�������ᵽ"+CHINESE_D->chinese_number(p1)+"��ʲô�����ġ�\n");
                write("�����ҾͰ�����Ž������ˣ��Ҷ�������Ѿ�ʧȥ��Ȥ�ˣ�������Ҫ���ذ�����\n");
                delete_temp("letter", me);
                addn("letter", -1);
                ob=present("letter",this_object());
                if (!ob)
                        ob=new("/d/changan/obj/letter.c");
                ob->move(me);
        } else {
                message("vision","�����Ӳ�֪������˵ʲôҲ����\n", me);
        }
        return 1;
}

int accept_object(object me, object ob)
{
        command("smile");
        command("say �ٺ٣���л��λ" + RANK_D->query_respect(me) + " ��");
        if( query("money_id", ob) && query("class", me) != "bonze" )
        {
                if(ob->value() < 1000000)
                {
                        command("say ���������������������ǲ������ٸ���...");
                        return 1;
                }else{
                        // command("smile shensuan");
                        command("say �����ң�" + RANK_D->query_respect(me) + "����Ҫ��(suan)�Լ���������˭��");
                        add_action("do_suan","suan");
                        set_temp("give_money", 1, me);
                        return 1;
                }
        }
        return 1;
}

int do_suan(string arg)
{
        object ob, me = this_player();
        string name;
        int str, ntg, dex, per, con, kar,str1, ntg1, dex1, per1, con1, kar1;

        if(!arg || sscanf(arg, "%s", name)!= 1 )   return 0;
        if( !query_temp("give_money", me))return 0;
        if(!objectp(ob = find_player(name)) )   return 0;
        if( !ob || wizardp(ob)) {
                command("tell "+query("id", me)+" �꣬С���㣬��������ô���㰡��");
                return 1;
        }

        delete_temp("give_money", me);
        str=query("str", ob);
        ntg=query("int", ob);
        dex=query("dex", ob);
        per=query("per", ob);
        con=query("con", ob);
        kar=query("kar", ob);
        str1 = ob->query_str();
        ntg1 = ob->query_int();
        dex1 = ob->query_dex();
        per1 = ob->query_per();
        con1 = ob->query_per();
        kar1 = ob->query_kar();


        switch(random(6)) {
                case 0 :
                if( str1+ntg1+dex1+per1+con1+kar1>(query("age", ob)+6)*6){
                        command("nod");
                        command("say ����"+ob->name()+"Ҳ���������з���");
                } else {
                        command("sigh");
                        command("say "+ob->name()+"��Ҫ�ڻ������϶��µ㹦��");
                }
                break;
                case 1 :
                if(kar > 22) {
                        command("smile");
                        command("say "+ob->name()+"��Ե��񣬼����������ࡣ");
                }else {
                        command("hmm");
                        command("say "+ob->name()+"��һ��������ע��Ҫ����ĥ���ˡ�");
                }
                break;
                case 2 :
                if( ntg>25 || ntg1>40+query("age", ob)){
                        command("nod");
                        command("say "+ob->name()+"���ʹ��ˣ����ܶ��Ŭ�����ض��ܳ���ͷ�ء�");
                } else {
                        command("shake");
                        command("say "+ob->name()+"���֪���������ȷɣ��ĵ��������л���ġ�");
                }
                break;
                case 3 :
                if(str > 25)
                        command("say "+ob->name()+"����������У���Ҳ���ѳ�Ϊһ��������");
                else    command("say "+ob->name()+"Ӧ��ר�������书��������̰�ࡣ");
                break;
                case 4 :
                if(per > 23 ) {
                        command("nod");
                        command("say "+ob->name()+"������ò�����ܼ����������ض��ܳ�������");
                }else {
                        command("shake");
                        command("say "+ob->name()+"��ò��Ȼ��ˣ�����ѰЩ��Ե�����ǿ������ݵġ�");
                }
                break;
                case 5 :
                if( dex1>(query("age", ob)+60)){
                        command("nod");
                        command("say "+ob->name()+"�������࣬�Ѵ�һέ�ɽ������������¿๦�����ɴ���");
                }else {
                        command("shake");
                        command("say "+ob->name()+"�������أ��ڽ���������������Ҫ�ģ������˰�!");
                }
                break;
        }
        set_temp("mimi", 1, me);
        return 1;
}
