
inherit NPC;

#include <ansi.h>

#define TIME_TICK1 time()*60
string *list=({

"killer",

	});


int do_kill(string arg);

string do_quest1();
void create()
{
   int i;
   object *ob;
   
   set_name("��Ǯ����",({ "shashou","sha" }) );
   set("gender", "����" );
   set("nickname",HIR"����Ǯ�ƣ���������"NOR);
   set("age", 32);
   set("long", "���������������ɱ�ּ��Ŵ��ϰ塣\n");
       
   set("combat_exp", 10000000);
   set("str",30);
   set("per", 30);
   set("dex",30);
   
   set("max_gin",3000);
   set("max_kee",3000);
   set("max_sen",3000);
   set("force",3000);
   set("max_force",3000);
   
   set_skill("force",500);
   set_skill("dodge",500);
   set_skill("parry",500);
   set_skill("sword",200);
   
   set_skill("yingzi-jianfa",200);
   set_skill("huanmo-shenfa",200);
   set_skill("wanshi-jue",200);
 
   set("inquiry",([

	  "��ɱ": "�ðɣ����� cisha ����id  ��������ɱ˭��!\n",
        
	
	   ]));
   set("vocation","ɱ��");
   set("vocation_skill","yingzi-jianfa");
   set_temp("apply/armor",100);
   setup();
   ob=children(__DIR__"obj/qingfeng-jian");
   for(i=0;i<sizeof(ob);i++)
     if(environment(ob[i])&&userp(environment(ob[i]))){
     tell_object(environment(ob[i]),"�����е�"+ob[i]->query("name")+"�����������ջ�ȥ�ˣ�\n");
     if(ob[i]->query("equipped"))
      ob[i]->unequip();
     destruct(ob[i]);}
     else if(environment(ob[i])){
     tell_object(environment(ob[i]),ob[i]->query("name")+"��һ�������ˡ�\n");
     destruct(ob[i]);}
     else destruct(ob[i]);
   //carry_object(__DIR__"obj/qingfeng-jian")->wield();
  
}

void init()
{
	add_action("do_kill","cisha");
	
}

int do_kill(string arg)
{
	object *usr;object me,ob;int i,j;object victim;
	int vexp,gol;int money;
	me=this_player();
	ob=this_object();
	usr=users();
	if(!arg) return notify_fail("������ȥɱ˭����˵����!\n");
	j=0;
	if(me->query("id")==arg) return notify_fail("ɱ���Լ�������Ц�ɣ���\n");
	for(i=0;i<sizeof(usr);i++)
	{
	write("=====" + usr[i]->query("id")+ "=====\n");
		//if(usr[i]->query("id")==arg)
		//{ j=1;victim=usr[i];break;}
	}
	if(j==0) return notify_fail("�������ڵĽ�������������𣿺úÿ���!\n");
	if(victim->is_ghost())
	return notify_fail("������Ѿ����ˣ��㻹�ǻ������°ɣ�\n");
	vexp=victim->query("combat_exp");
	gol=vexp/1000+random(vexp/1000);
	if(gol<=0) return notify_fail("�ߣ��书��ô��΢����Ҳֵ������ɱ?\n");
	tell_object(me,"����ж�Ҫ������"+chinese_number(gol)+"���ƽ�!\n");
	money=gol*10000;
	switch(MONEY_D->player_pay(this_player(), money))
	{
	case 0: return notify_fail("�ߣ���ô��Ǯ��Ҳ�������ң�\n");
	case 2: return notify_fail("������Ǯ�����ˣ���Ʊ��û���ҵÿ���\n");
	default:
	tell_object(me,"��Ǯ�������ͷ����������Ǯ�ƣ��������֣�����ź��ˣ�\n");
	if(victim->query("combat_exp")>500000)
	ob->set("combat_exp",victim->query("combat_exp"));
	if(!objectp(victim)) return notify_fail("��ѽ�������ͻȻ���ˣ��´ΰ�!\n");
	victim->start_busy(2);
	message_vision("$N����һ�Σ��ټ�����!\n",ob);
	ob->move(environment(victim));
	message_vision(HIR"$N����$n�е������˹�����ɱ�㣬����������!\n"NOR,ob,victim);
	ob->kill_ob(victim);
log_file("killer_kill",sprintf("%s let yang kill %s\n",me->query("id"),victim->query("id")));
	call_out("yang_go",180,ob);
	return 1;
	}
	return 1;
}

void yang_go(object ob)
{
	string *dir=({"/d/luoyang/shanlu1"});
	if(!objectp(ob))
	{ remove_call_out("yang_go");return;}
	message_vision("$N���¿��˿�������һ�Σ��ټ�����!\n",ob);
	ob->move(dir[random(sizeof(dir))]);
	remove_call_out("yang_go");return;
}



int is_apprentice_of(object ob)
{
	return 1;
}
int recognize_apprentice(object ob)
{
         return 1;
}


