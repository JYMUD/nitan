#include <ansi.h>;
inherit F_DEALER;
inherit NPC;

int ask_puti();
int ask_yuqing();
int ask_jinchuang();
int ask_yangjing();
int ask_jifeng();
int ask_jiuhua();
int ask_xieqi();
int ask_zhengqi();
int ask_longxi();
int ask_xiaoke();



void create()
{
    	set_name("����ţ", ({ "hu qingniu", "hu", "qingniu" }));
    	set("title", YEL"����ҽ��"NOR);
    	set("gender", "����");
    	set("long", "������ҽ���߳��ġ�����ҽ�ɡ�����ţ��\n");
    	set("age", 65);
    	set("int", 30);
    	set("qi", 1000);
    	set("max_qi", 1000);
    	set("jing", 1000);
    	set("max_jing", 1000);
    	set("shen_type", 0);
    	set("combat_exp", 500000);
    	set("attitude", "heroism");
    	set_skill("unarmed", 80);
    	set_skill("dodge", 80);
    	set_skill("parry", 60);
    	set_temp("apply/attack", 70);
    	set_temp("apply/defense", 70);
    	set_temp("apply/damage", 50);
       set("inquiry", 
	([
    		"������":(:ask_puti:),
    		"����ɢ":(:ask_yuqing:),
    		"��ҩ":(:ask_jinchuang:),
    		"������":(:ask_yangjing:),
		"�Ż���¶��":(:ask_jiuhua:),
		"�������굤":(:ask_jifeng:),
		"���˾��ӵ�":(:ask_zhengqi:),
		"�ĺ�������":(:ask_xieqi:),
		"��Ϭ�ٲݵ�":(:ask_longxi:),
		"����ֹ����":(:ask_xiaoke:),

       ]));
     	set("vendor_goods", 	({
     		__DIR__"axe",
     		__DIR__"blade",
     		__DIR__"yaochu",
     		__DIR__"dinglu",
                   __DIR__"bottle",
     		__DIR__"yao/huazhong",
     		__DIR__"yao/guozhong",

     	}));

    	setup();
    	carry_object("/clone/cloth/changpao")->wear();
} 
void init()
{
       add_action("do_list", "list");
       add_action("do_buy", "buy");
}

int accept_object(object who, object ob)
{
    
       if( !query("peifang", who) )
       	return notify_fail("����ţ��ü˵�����㲻�����̵��ӣ�����Ǯ���Ҿͻ�����β���\n");

    	if( query("money_id", ob) && ob->value()<100000 )
    	{
	       return notify_fail("����ţ��ü˵������ôһ���Ǯ������������ҩͯ�ӵ������أ�\n");
    	}

    	else if( query("money_id", ob) && ob->value() >= 100000 )
    	{
        	message_vision ("����ţ˵����"+RANK_D->query_respect(who)+"���ϴε��䷽����������û��ϵ���������ҩ���������ء�\n");
        delete("peifang", 	who);
        delete("mubiao", 	who);
        	return 1;
    	}
    	return 0;
}


int ask_puti()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬�������������ӡ�\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "putizi", 	who);

   	message_vision("$N¶����˼����ɫ����$n˵���������ӵ��䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"��"+query("name", hua)+"��"+query("name", guo)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_yuqing()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬������������ɢ��\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "yuqingsan", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵��������ɢ���䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"��"+query("name", hua)+"��"+query("name", guo)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_yangjing()
{
    	object gen, mu;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}

	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);

set("peifang", peifang, 	who);
set("mubiao", "yangjing", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵�������������䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	return 1;
}
int ask_jinchuang()
{
    	object gen, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	cao=new(__DIR__"/yao/caolei");

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}

	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", cao);

addn("peifang", peifang, 	who);
set("mubiao", "jinchuang", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵������ҩ���䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", cao)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(cao);
	return 1;
}

int ask_jiuhua()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬�������ƾŻ���¶�衣\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "jiuhuawan", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵�����Ż���¶����䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}

int ask_jifeng()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬�������Ƽ������굤��\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "jifengdan", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵�����������굤���䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}

int ask_zhengqi()
{
    	object gen, mu, cao, hua;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");

	if((int)who->query_skill("liandan-shu",1) < 100)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬�����������˾��ӵ���\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);

set("peifang", peifang, 	who);
set("mubiao", "zhengrendan", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵�������˾��ӵ����䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"��"+query("name", hua)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	return 1;
}
int ask_xieqi()
{
    	object gen, mu, cao, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 100)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬���������ĺ���������\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "xinhendan", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵�����ĺ����������䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"��"+query("name", guo)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(guo);
	return 1;
}

int ask_longxi()
{
    	object gen, mu, cao, hua, guo;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");
	hua=new(__DIR__"/yao/hualei");
	guo=new(__DIR__"/yao/guolei");

	if((int)who->query_skill("liandan-shu",1) < 200)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬����������Ϭ�ٲݵ���\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);
	peifang+=query("yaoxing", hua);
	peifang+=query("yaoxing", guo);

set("peifang", peifang, 	who);
set("mubiao", "longxidan", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵������Ϭ�ٲݵ����䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"��"+query("name", hua)+"��"+query("name", guo)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	destruct(hua);
	destruct(guo);
	return 1;
}

int ask_xiaoke()
{
    	object gen, mu, cao;
	int peifang;
	object who = this_player();
	object me = this_object();

	gen=new(__DIR__"/yao/genlei");
	mu=new(__DIR__"/yao/mulei");
	cao=new(__DIR__"/yao/caolei");

	if((int)who->query_skill("liandan-shu",1) < 50)
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"����������������㣬������������ֹ������\n",me);
		return 1;
	}

	if( query("peifang", who) )
	{
		message_vision ("$N˵����"+RANK_D->query_respect(who)+"�����ϴθ�����䷽��������\n",me);
		return 1;
	}


	peifang=query("yaoxing", gen);
	peifang+=query("yaoxing", mu);
	peifang+=query("yaoxing", cao);

set("peifang", peifang, 	who);
set("mubiao", "xiaokedan", 	who);


   	message_vision("$N¶����˼����ɫ����$n˵��������ֹ�������䷽��������������һ����������Ҫ"+query("name", gen)+"��"
	+query("name", mu)+"��"+query("name", cao)+"����ζҩ�Ĳ������ɡ�\n",me,who);
	destruct(gen);
	destruct(mu);
	destruct(cao);
	return 1;
}