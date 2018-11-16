// Last Modified by winder on Nov. 17 2000

inherit NPC;

int ask_thd();
int ask_price();
int ask_qihang();

void create()
{
        set_name("���ϴ�", ({ "laoda" , "chuanlaoda" }) );
        set("gender", "����" );
        set("age", 42);
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "�ϴ�");
        set("inquiry", ([
                "name"  : "�Ҿ���������ϴ����Ƕ�����С��硣",
                "rumors": "��˵��ǰ��һ�Һ�ë���ӵĴ����Ѻ�Ư�������Ψһ�Ĵ�Ա�������Ǳߵ�С���",
                "here"  : "�����Ǹ���Ψһ�ĳ�������ˡ�",
                "chuhai": "�͹���Ҫ����ȥ���ﰡ���ѵ����һ�...",
                "����"  : "�͹���Ҫ����ȥ���ﰡ���ѵ����һ�...",
                "�ʹ�"  : "�͹���Ҫ����ȥ���ﰡ���ѵ����һ�...",
                "�һ���": (: ask_thd :),
                "taohuadao": (: ask_thd :),
                "��Ǯ": (: ask_price :),
                "price": (: ask_price :),
                "����": (: ask_qihang :),
                "qihang": (: ask_qihang :),
        ]) );
        setup();
}

int ask_thd()
{
        object ob=this_player();

        if( query("thd/x", ob) )
        {
                say("���ϴ�ɴ����۾����Ծ���˵���͹�Ҫȥ�Ǹ���ط�ô����˵��ǰȥ���˶�û�л�������\n��������Ҫȥ�Ļ��������Ǯ��...\n" );
                if( query("family/family_name", ob) != "�һ���" )
                        set_temp("thd_temp", 1, ob);
                else
                {
                        message_vision("$N���һ�������Ҿ����һ������ӣ���Ҳ��ҪǮ������\n", ob);
                        command("fear"+query("id", ob));
                        message_vision("���ϴ��������$N˵�����͹�Ϣŭ��С������Ҵ���������\n", ob);
                        if (query_temp("busy",get_object("/d/taohua/boat")))
                         {
                                command("say С���Ѿ������ˣ��͹������Ե�һ�����\n");
                                write("��������ʱҪ������(qihang)�ˡ�\n");
                                set_temp("thd_temp", 3, ob);
                        }
                        else {
                                say("���ϴ�һ���֣�����һ��������������λ�͹�ȥ�һ�����\n");
                                set_temp("thd_target", "thd", ob);
                                delete_temp("thd_temp", ob);
                                ob->move("/d/taohua/boat");
                        }
                }
        }
        else say("���ϴ�ҡҡͷ��˵��������ֻ��˵���һ�������˭Ҳ��֪�������\n");
        return 1;
}

int ask_price()
{
        object ob=this_player();
        int money = 30000;

        if( query("age", ob)<16 )
                money=(query("age", ob)-13)*1000;
        if( query_temp("thd_temp", ob) )
        {
                say("���ϴ���Ц��Ц��˵�����ҿ��͹����ƣ�������" + MONEY_D->price_str(money) + "�ɡ�\n" );
                command("hehe laoda");
                set_temp("thd_temp", 2, ob);
        }
        else {
                command("?"+query("id", ob));
                command("dunno"+query("id", ob));
        }
        return 1;
}

int accept_object(object who, object ob)
{
        int money = 30000;

        if( query("age", who)<16 )
                money=(query("age", who)-13)*1000;
        if( query("money_id", ob) && ob->value() >= money){
                if( query_temp("thd_temp", who)<2 )
                        say("���ϴ����ˣ�˵������������Ǯû����ô��\n");
                else {
                        if (query_temp("busy",get_object("/d/taohua/boat")))  {
                                command("say С���Ѿ������ˣ��͹������Ե�һ�����\n");
                                write("��������ʱҪ������(qihang)�ˡ�\n");
                                set_temp("thd_temp", 3, who);
                        }
                        else {
                                command("say ���ϴ�˵�����������ġ�\n");
                                say("���ϴ�һ���֣�����һ��������������λ�͹�ȥ�һ�����\n");
                                set_temp("thd_target", "thd", who);
                                delete_temp("thd_temp", who);
                                who->move("/d/taohua/boat");
                        }
                }
                return 1;
        }
        return 0;
}

int ask_qihang()
{
        object ob=this_player();

        if( query_temp("thd_temp", ob)<3 )
                say("���ϴ��������ʲô�������������\n" );
        else {
                if (query_temp("busy",get_object("/d/taohua/boat")))  
                        command("say С���Ѿ������ˣ��͹����ٵ�һ�����\n");
                else {
                        command("say ���ϴ�˵�����������ġ�\n");
                        say("���ϴ�һ���֣�����һ��������������λ�͹�ȥ�һ�����\n");
                        set_temp("thd_target", "thd", ob);
                        delete_temp("thd_temp", ob);
                        ob->move("/d/taohua/boat");
                }
        }
        return 1;
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        message_vision("���ϴ����$N�������ҵĵ�����Ҳ����Ұ������\n", ob);
        message_vision("$N��æ��Ц���������ң����ҡ���\n", ob);
}
