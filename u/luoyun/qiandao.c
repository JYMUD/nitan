//ǩ���򿨹���

#include <ansi.h>
#include <localtime.h>
#define QIANDAO "/data/qiandao.o"

inherit NPC;

int do_daka();
int do_query_time();

void create()
{
	set_name("ǩ��Ա", ({ "qiandao npc" }));
	set("gender", "����");
	set("age", 20);
	set("per", 100);
	set("con", 100);
	set("int", 100);
	set("dex", 100);
	set("str", 100);
	set("qi", 10000);
	set("max_qi", 10000);
	set("jing", 10000);
	set("neili", 10000);
	set("max_neili",10000);
	set("max_jingli",10000);
	set("max_jing",10000);
	set("combat_exp",100000000);
	set("no_suck", 1);
	set("title",HIG"��Ϸ����Ա"NOR);
	set("long","������̶6�Ĺ���Ա��ר�Ÿ�����ҵ�ǩ����¼������\n");
	set("no_kill",1);
	set("inquiry", ([
		"ǩ��" : (: do_daka :),
		"��ѯǩ��" : (: do_query_time :),
	]));
	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

int do_daka()
{
	object me, ob, env;
	mixed *localtime, *localtime2;
	string writeFile, ip, ip2, *meFilePach, meFile, item_max, id, room, target;
	int i, j, ok, day, month, size, data;
        int level;
	
	ob = this_object();
	me = this_player();
	
	if (query_temp("qiandao_time", ob) >time())
	{
		tell_object(me,CYN"ǩ��Ա˵���������������Ҵ�������\n"NOR);
		return 1;
	}
	
	data = query("dacard/time", me);
	localtime = localtime(data);
	localtime2 = localtime(time());
	
	if(data && localtime[LT_MDAY]  == localtime2[LT_MDAY])
	{
		tell_object(me, CYN"ǩ��Ա˵����������Ѿ�ǩ�����ˣ����������ɡ�\n"NOR);
		return 1;
	}
	
	if(localtime[LT_MON] + 1 != localtime2[LT_MON] + 1)//�·�
	{
		delete("dacard", me);
	}
	
	set_temp("qiandao_time", time() + 2, ob);//��÷�ʽ��ȡ��дӲ�̣�����������
	writeFile = QIANDAO;
	
	if(writeFile) 
	{
		meFile = read_file(writeFile);
		if(meFile) 
			meFilePach = explode(meFile,"\n");
			
		size = sizeof(meFilePach);
		ip = query_ip_number(me);
			
		item_max = sprintf("ID:%s$Ip:%s$Day:%d$Month:%d", query("id", me), ip, localtime2[LT_MON] + 1, localtime2[LT_MDAY]);
			
		for(i=0; i<size; i++)
		{
			sscanf(meFilePach[i], "ID:%s$Ip:%s$Day:%d$Month:%d", id, ip2, day, month);
									
			if (ip == ip2 && localtime2[LT_MON] + 1 == day && localtime2[LT_MDAY] == month)//��ͬ�ļ����ݱ�ʾ��IP�Ѿ�����ǩ��
			{
				ok =1;
				break;
			} else if (ip == ip2) {//ֻ��IP��ͬ����û��ǩ��
				ok =2;
				meFilePach[i] = "";
				break;
			} else
				ok =0;
		}
	}
	
	if (ok == 1)
	{
		tell_object(me, CYN"ǩ��Ա�����IP�����Ѿ�����ǩ�����ˡ�\n"NOR);
		return 1;
	} 
	if (ok == 2)
	{
		write_file(writeFile, "", 1);//��ʼ�����ļ�
		//��д�ļ�
		for(i=0; i<size; i++)
		{
			if(meFilePach[i] == "") continue;//ȥ��IP��ͬ������
			write_file(writeFile, sprintf("%s\n", meFilePach[i]));//��д��������
		}
	} 
	if (ok !=1) {
		write_file(writeFile, sprintf("%s\n", item_max));//�¼�¼�����ļ�
	} 
	if ( !objectp(env=environment(ob)) 
		|| !stringp(room=query("short",env)) ) 
	{
		::die();
		return;
	}
					
	i = 50000;
	
        level = query("level", me);
	//���޶��������ڽ�������
	if ( (CHINESE_D->chinese_time(7, ctime(time()))) == "2013/06/04" ||
		(CHINESE_D->chinese_time(7, ctime(time()))) == "2013/06/05" ||
		(CHINESE_D->chinese_time(7, ctime(time()))) == "2013/06/06" ||
		(CHINESE_D->chinese_time(7, ctime(time()))) == "2013/06/07" ||
		(CHINESE_D->chinese_time(7, ctime(time()))) == "2013/06/08" ||
		(CHINESE_D->chinese_time(7, ctime(time()))) == "2013/06/09" ||
		(CHINESE_D->chinese_time(7, ctime(time()))) == "2013/06/10"  )
		j = 5 + random(6);
	else //���ں����½�
		j = 3 + random(3);
	
        j = level / 10 * 10;
        if( j < 5 ) j = 5;
	target = query("id", me);
			
	if (MEMBER_D->is_member(target))
		MEMBER_D->db_pay_member(target, j);
	else
		MEMBER_D->db_create_member(target, j);

		addn("combat_exp", i, me);
		addn("potential", i, me);
		addn("dacard/cishu", 1, me);
		set("dacard/time", time(), me);
		message("party", (HIW + "��"+room+"��ǩ��Ա��" + NOR + query("name", me) 
									+ "����ǩ����� " + HIR + "" + j + " $NT"NOR"��\n"NOR), users() );	
		tell_object(me, sprintf(CYN + "�����˾���ֵ %d�㣬Ǳ�� %d�㡣\n"NOR, i, i));
		tell_object(me, sprintf(CYN"����ǩ���ɹ���ף����Ϸ��죡\n"NOR));
		
		return 1;
}

int do_query_time()
{
	int time;
	mixed *localtime;
	object me = this_player();
	
	time = query("dacard/time", me);
	localtime = localtime(time);
	tell_object(me, sprintf(CYN"�㱾�µ�ĿǰΪֹ�ܹ�ǩ�� %d�Ρ�\n"NOR, query("dacard/cishu", me)) );
	tell_object(me, sprintf(CYN"%s���ϴ�ǩ��ʱ���ǣ�%d��%d��%d��%dʱ%d��%d�롣\n"NOR, 
								query("name", me), localtime[LT_YEAR], localtime[LT_MON] + 1,
								localtime[LT_MDAY], localtime[LT_HOUR], localtime[LT_MIN], localtime[LT_SEC] ));
	return 1;
}

void die()
{
	object me, ob;
	
	me = this_object();
	
	set("eff_qi", 10000);
	set("qi", 10000);
	set("eff_jing", 10000);
	set("jing", 10000);
	set("neili", 90000);
	set("max_jingli",10000);
	
	say( me->name() + CYN "˵�������ǲ����ģ������Ϊ�Ѿ�����¼�ڰ���\n"NOR);
	return;
	
}
