inherit ITEM;

#include <ansi.h>

#define LINE_COUNT 5
#define MEMBER_D "/adm/daemons/memberd"
#define LINE HIM "------------------------------------------------------------------------------------------" NOR

mapping trans = ([
// ����
"beijing"   : "/d/beijing/majiu",
"luoyang"   : "/d/luoyang/majiu",
"yangzhou"  : "/d/city/majiu",
"dali"      : "/d/dali/majiu", 
"foshan"    : "/d/foshan/majiu", 
"fuzhou"    : "/d/fuzhou/majiu", 
"guanwai"   : "/d/guanwai/majiu", 
"hangzhou"  : "/d/hangzhou/majiu", 
"lanzhou"   : "/d/lanzhou/majiu", 
"lingzhou"  : "/d/lingzhou/majiu", 
"yongdeng"  : "/d/huanghe/majiu", 
"suzhou"    : "/d/suzhou/majiu",
"xiangyang" : "/d/xiangyang/majiu", 
"yili"      : "/d/xingxiu/majiu", 
"chengdu"   : "/d/city3/majiu", 
"emei"      : "/d/emei/majiu1", 
"emei2"     : "/d/emei/majiu2", 
"quanzhou"  : "/d/quanzhou/majiu1", 
"jiaxing"   : "/d/quanzhou/majiu2", 
"jingzhou"  : "/d/jingzhou/majiu", 
"nanyang"   : "/d/shaolin/majiu1", 
"changan"   : "/d/changan/majiu", 
"wugong"    : "/d/quanzhen/majiu", 
"hengyang"  : "/d/henshan/majiu", 
"kaifeng"   : "/d/kaifeng/majiu", 
"kunming"   : "/d/kunming/majiu", 
"zhongzhou" : "/d/zhongzhou/majiu",
// ����
"family_1"    :  "/d/huashan/laojun",
"family_2"    :  "/d/songshan/dadian",
"family_3"    :  "/d/henshan/zhurongdian",
"family_4"    :  "/d/shaolin/guangchang1",
"family_5"    :  "/d/wudang/sanqingdian",
"family_6"    :  "/d/emei/huayanding",
"family_7"    :  "/d/xiaoyao/xiaodao4",
"family_8"    :  "/d/lingjiu/damen",
"family_9"    :  "/d/xingxiu/xxh1",
"family_10"   :  "/d/gumu/mumen", 
"family_11"   :  "/d/quanzhen/jiaobei",
"family_12"   :  "/d/kunlun/guangchang",
"family_13"   :  "/d/taohua/tao_in",
"family_15"   :  "/d/xuedao/shandong2",
"family_16"   :  "/d/xueshan/shanmen",
"family_17"   :  "/d/gaibang/inhole",
"family_18"   :  "/d/tiezhang/guangchang",
"family_19"   :  "/d/kaifeng/tieta",
"family_20"   :  "/d/wudu/neijin",
"family_21"   :  "/d/mingjiao/shanmen",
"family_22"   :  "/d/xuanminggu/zulin2",
"family_23"   :  "/d/meizhuang/keting",
"family_24"   :  "/d/lingxiao/gate",
"family_25"   :  "/d/beijing/gate",
"family_26"   :  "/d/jueqing/shanzhuang",
"family_27-1" : "/d/heimuya/pingdingzhou",
"family_27-2" : "/d/heimuya/shenggu",
"family_28"    :  "/d/city/beidajie1",
"family_29"    :  "/d/zhongzhou/miaojia_houting",
"family_30"    :  "/d/yanziwu/shuiyun",
"family_31"    :  "/d/shaolin/shang_men",
"family_32"    :  "/d/guanwai/xiaowu",
"family_33"    :  "/d/dali/neitang",
// ����
"comm_1"  :  "/d/city/kedian",
"comm_2"  :  "/d/city/wumiao",
"comm_3"  :  "/d/city/zuixianlou",
"comm_4"  :  "/d/city/yh_cangku",
"comm_5"  :  "d/wuguan/guofu_gate",///
"comm_6"  :  "/d/item/xiaowu",
"comm_7"  :  "/d/item/road1",
"comm_8"  :  "/d/xiakedao/xkroad5",
"comm_9"  :  "/d/huashan/jianzhong",
"comm_10"  :  "/d/shaolin/hanshui1",
"comm_11"  :  "/d/huashan/shandong",
"comm_12"  :  "/d/dali/lushui",
"comm_13"  :  "/d/mingjiao/xuantianshi",
"comm_14"  :  "/d/beijing/shanlu3",
"comm_15"  :  "/d/xiakedao/haibin",
]);

mapping show_trans = ([
// ����
"beijing"   : "����",
"luoyang"   : "����",
"yangzhou"  : "����",
"dali"      : "����", 
"foshan"    : "��ɽ", 
"fuzhou"    : "����", 
"guanwai"   : "����", 
"hangzhou"  : "����", 
"lanzhou"   : "����", 
"lingzhou"  : "����", 
"yongdeng"  : "����", 
"suzhou"    : "����",
"xiangyang" : "����", 
"yili"      : "����", 
"chengdu"   : "�ɶ�", 
"emei"      : "����ɽ", 
"emei2"     : "���Ұ�ɽ", 
"quanzhou"  : "Ȫ��", 
"jiaxing"   : "����", 
"jingzhou"  : "����", 
"nanyang"   : "����", 
"changan"   : "����", 
"wugong"    : "�书��", 
"hengyang"  : "����", 
"kaifeng"   : "����", 
"kunming"   : "����", 
"zhongzhou" : "����",

// ����
"family_1":  "��ɽ��",
"family_15": "Ѫ����",
"family_2":  "��ɽ��",
"family_16": "������",
"family_3":  "��ɽ��",
"family_17": "ؤ��",
"family_4":  "������", 
"family_18": "���ư�",
"family_5":  "�䵱��", 
"family_19": "�컨��",
"family_6":  "������",    
"family_20": "�嶾��",
"family_7":  "��ң��",   
"family_21": "����",
"family_8":  "���չ�", 
"family_22": "��ڤ��",
"family_9":  "������",   
"family_23": "÷ׯ", 
"family_10": "��Ĺ��",   
"family_24": "ѩɽ��",
"family_11": "ȫ����",  
"family_25": "��Զ�ھ�",
"family_12": "������", 
"family_26": "�����",
"family_13": "�һ���",   
"family_27-1": "������̣��У�",
"family_27-2": "������̣�Ů��",
"family_28":  "ŷ������", 
"family_29":  "��ԭ���",
"family_30":  "Ľ������",     
"family_31":  "���Ե��̼ұ�",
"family_32":  "�������",
"family_33":  "�������",
// ����
"comm_1"  :  "���ݿ͵�",
"comm_2"  :  "��������",
"comm_3"  :  "����¥",
"comm_4"  :  "�ֿ�",
"comm_5"  :  "������",///d/wuguan/guofu_gate
"comm_6"  :  "�ɽ�Īа",
"comm_7"  :  "����ʦ",
"comm_8"  :  "����",
"comm_9"  :  "���",
"comm_10"  :  "����ʹ",
"comm_11"  :  "��ʦ�������",
"comm_12"  :  "��ʦ����",
"comm_13"  :  "��ʦ��ɽ",
"comm_14"  :  "��ʦ����̫��",
"comm_15"  : "����",

]);

mapping show_trans2;
string g_show_trans;

mapping get_trans2()
{
	mapping m;
	string *keys_show_trans;
	int i;
	
	m = ([]);
	keys_show_trans = keys(show_trans);
	
	for (i = 0; i < sizeof(keys_show_trans); i ++)
	{
		m += ([ show_trans[keys_show_trans[i]] : keys_show_trans[i] ]);
	}
	
	return m;
}

string get_trans_path(string s)
{
	string st;
	
	// ͬʱ�������ĺ�Ӣ��
	if (member_array(s, keys(trans)) == -1)
	{
		s = show_trans2[s];
	}
	
	return trans[s];
}

int is_horse()
{
	return 1;
}

void setup()
{
        set("ridable", 1);
	set("no_give", 1);
	set("value", 1);
	set("unit", "ƥ");
	set("base_unit", "ƥ");
	set_weight(1);

	show_trans2 = get_trans2();
	set_heart_beat(2);
	/*
	remove_call_out("start_heart_beat");
	call_out("start_heart_beat", 2);
	*/
	::setup();
}

int show_trans(object me)
{
	mapping self_flag;
        int i;
	string *places, show_places;
	string show_city, show_family, show_comm;
	int ncity, nfamily, ncomm;

	show_places = "";
	show_city = "";
	show_family = "";
	show_comm = "";
	if (sizeof(g_show_trans))
	{
		show_places += g_show_trans;
	}
	else
	{
		
		show_places += HIY "��������������µط���\n" + LINE + "\n"NOR;
	
		places = keys(show_trans2); 
		
	        for (i = 0; i < sizeof(places); i ++)
	        {
			if (strsrch(show_trans2[places[i]], "comm_") != -1)
			{
				show_comm += sprintf("%-18s", places[i]);
				ncomm ++;
				if (ncomm % LINE_COUNT == 0)show_comm += "\n";
			}
			else if (strsrch(show_trans2[places[i]], "family_") != -1)
			{
				show_family += sprintf("%-18s", places[i]);
				nfamily ++;
				if (nfamily % LINE_COUNT == 0)show_family += "\n";
			}
			else
			{
				show_city += sprintf("%-18s", places[i]);
				ncity ++;
				if (ncity % LINE_COUNT == 0)show_city += "\n";
			}
		}
	        show_places += HIG + "<����>\n" NOR;
	        show_places += show_city;
	        show_places += HIY + "\n<����>\n" NOR;
	        show_places += show_family;
	        show_places += HIC + "\n<����>\n" NOR;
	        show_places += show_comm;
	        	
	        g_show_trans = show_places; // ȫ�ּ�¼������Ҫÿ�ζ�����
	}

		// �Լ���¼�ĵص�
		self_flag=query("horse/flags", me);

		if (mapp(self_flag))
		{
			show_places += HIR "\n<�û���¼�ص�>\n" NOR;
			if (sizeof(self_flag))
			{
				places = ({});
				places = keys(self_flag);
				for (i = 0; i < sizeof(places); i ++)
				{
					show_places += sprintf("%-18s", places[i]);
					if ((i+1) % LINE_COUNT == 0)show_places += "\n";
				}
				if (sizeof(places) % LINE_COUNT != 0)show_places += "\n";
			}
		}
		else
		{
			show_places += "\n";
		}

		show_places += LINE + HIY "\n��ʹ�� rideto <Ŀ�ĵ�> ����ָ���ط������磺rideto �͵�\n" NOR;
		

	write(show_places);
	return 1;
}

// ����ָ���ص�
int move_to(object me, string place)
{
	object running, horse, follower;
        string trans_path;
	int trans_times, sk_riding, horse_level, horse_tili, cost_tili, level;
	string temp,temp2;
	object trans_target, me_env;
	

	// ����Ƿ�����
        if( !objectp(horse=query_temp("is_riding", me)) )
	{
		write("�㲢û��������\n" );
		return 1;
	}
	if( query_temp("running", horse) )
	{
		write(this_object()->name() + NOR "���ڱ����أ�\n" NOR);
		return 1;
	}
	if( query_temp("running", me) )
	{
		write("�����ڱ������ء�\n");
		return 1;
	}
	if (me->is_busy() || me->is_fighting())
	{
		write("����æ�أ�\n");
		return 1;
	}
	sk_riding = me->query_skill("riding", 1);
        if (sk_riding < 30)
	{
		write("�������������޷�����ָ���ص㡣\n");
		return 1;
	}

        // ����Ƿ��иõط���ȥ
        if (! stringp(trans_path = get_trans_path(place)))
	{
			if( stringp(trans_path=query("horse/flags/"+place, me)) )
			{
				if (! find_object(trans_path) && ! load_object(trans_path))
				{
					write("���޷�����ﵽ����ط���\n");
					return 1;
				}
				
			}
			if( !stringp(trans_path=query("horse/flags/"+place, me)) )
			{
				write("���޷�����ﵽ����ط���\n");
				return 1;
			}		
			else
			{
				if( !MEMBER_D->is_valib_member(query("id", me)) && !query("horse/stone", me) )
				{
					write("���޷�����ﵽ����ط���\n");
					return 1;
				}
			}
	}

	// ĳЩ�ط��޷�������
	trans_target = find_object(trans_path);
	if (! objectp(trans_target))trans_target = load_object(trans_path);

	if (! objectp(trans_target))
	{
		write("���޷�����ﵽ����ط���\n");
		return 1;
	}
	
	if( query("no_flyto", trans_target) )
	{
		write("���޷�����ﵽ����ط���\n");
		return 1;
	}

        // �����Ҳ�޷�����
	if (sscanf(trans_path, "/kungfu/class/sky%s", temp) == 1)
	{
		write("���޷�����ﵽ����ط���\n");
		return 1;
	}

	if (sscanf(trans_path, "/d/newbie/%s", temp) == 1)
	{
		write("���޷�����ﵽ����ط���\n");
		log_file("horse",query("id", me)+"��"+ctime(time())+"��ͼ���ü�¼��ص����ִ塣\n");
		return 1;
	}	
	// �������ϲ��ܵ���(��Ӱ�����)
	me_env = environment(me);
	
	if( query("no_rideto", me_env) )
	{
		write("�˴���������\n");
		return 1;		
	}
	if( sscanf(base_name(me_env),"/d/shenlong/%s",temp) == 1 && query("id", this_object()) != "chaoying" )
	{
		write("�˴��޷�����\n");
		return 1;
	}
	if( sscanf(trans_path,"/d/shenlong/%s",temp) == 1 && query("id", this_object()) != "chaoying" )
	{
		write("���޷�����ﵽ����ط���\n");
		return 1;
	}
	
	if (trans_path == "/d/shenlong/shejingdong")
	{
		write("��������޷���Ӧ�߾����ڵ�������޷�����ﵽ����ط���\n");
		return 1;
	}
	
        // dream_boat���޷�����
	if (sscanf(base_name(me_env), "/clone/misc/dream_%s", temp) == 1)
	{
		write("�˴��޷�����\n");
		return 1;
	}
	
	// ��ҷ����޷�����Լ��ķ������
	if (sscanf(trans_path, "/data/room/%s/%s", temp, temp2) == 2)
	{
		// �Լ�������Խ���
		if( query("id", me) != temp )
		{
			write("���޷��������˽��סլ��\n");
			return 1;
		}
	}

	if (sscanf(trans_path, "/clone/misc/dream_%s", temp) == 1)
	{
		write("���޷�����ﵽ����ط���\n");
		return 1;
	}
	if (sscanf(trans_path, "/d/xiangyang/%s", temp) == 1 && XYWAR_D->now_status() == 2)
	{
		write("����������ȫ��䱸���㻹�������Ƚϰ�ȫ��\n");
		return 1;
	}

	if (sscanf(base_name(environment(me)),"/d/xiangyang/%s", temp) == 1  && XYWAR_D->now_status() == 2)
	{
		write("����������ȫ��䱸���㻹�������Ƚϰ�ȫ��\n");
		return 1;
	}

	// ������ĺû��������ߵ��������жϴﵽĿ�ĵ�ʱ��
	level=query("level", horse);
	if (sk_riding >= 300)sk_riding = 300;
	trans_times = 2 + random(1 + 300 / sk_riding) + random(22 - level*4);

	if (trans_times <= 0)
		log_file("horse_time", trans_times + "\n");

        // �ж�����ָ���ص��������ĵ�����
	horse_tili=query("tili", horse);
	cost_tili = 10 + random(trans_times * 25);

	if (horse_tili <= cost_tili)
	{
		write(horse->name() + NOR "�������㣬����������Ϣ����ɡ�\n");
		return 1;
	}

	running = new("/clone/misc/running");

        if( objectp(follower=query_temp("is_rided_follow", horse)) )
	{
		if (environment(follower) && (interactive(follower) || ! userp(follower)))
			follower->move(running);
	}
	me->move(running);
        addn("tili", -1*cost_tili, horse);
set_temp("running", 1, 	horse);
set_temp("running", 1, 	me);

	message("vision",  "\n" + this_object() ->name() + HIW "һ����"
                  "˻����һ��س�� ����\n" NOR, environment(me), ({horse}));

	call_out("arrived_dest", trans_times, me, follower, running, horse, trans_path);

	return 1;
}

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path)
{
	object ob, ob2;
	
	if (objectp(me))
	{
		me->move(trans_path);
delete_temp("running", 		me);
		if (random(2))me->improve_skill("riding", 1);
	}
	if (objectp(follower))follower->move(trans_path);
	if( objectp(horse))delete_temp("running", horse);
	// �����ͬ����ͬ���Զ��ƶ�����ǰ
	ob=query("me_mater", me);
	if (objectp(ob))
		ob->move(environment(me));
		
	if (objectp(follower))
	{
		ob2=query("me_mater", follower);
		if (objectp(ob2))
			ob2->move(environment(follower));	
	}
		 		 	
        if(objectp(running))destruct(running);

	if (objectp(horse))
		message("vision",  "\n" + this_object()->name() + HIW "����Ŀ�ĵأ���Ȼ��˻��ǰ"
                          "�߸����ʱ������ɢ����\n" NOR, environment(horse), ({horse}));

	return 1;
}

// ǿ������
int force_me_ride(object me)
{
        object owner;

    if (! objectp(me))
    {
		write("�������\n");
		return 0;
    }

	if( query_temp("is_rided_follow", this_object()) )
		return 0;

	owner=query_temp("is_rided_by", this_object());

  set_temp("is_rided_follow", me, 	this_object());
set_temp("is_riding_follow", this_object(), 	me);

    message_vision("$NԾ��$n" NOR "������" + owner->name() + "�����\n", me, this_object());

	return 1;
}

// ����
void heart_beat()
{
     int level;
     object follower;
/*
     remove_call_out("start_heart_beat");
     call_out("start_heart_beat", 2);
*/
     level=query("level", this_object());

     if( !query_temp("running", this_object()) )
     {
	if( query("tili", this_object())+1<query("max_tili", this_object()))		
       addn("tili", level+random(level), 		this_object());
		
	if( query("tili", this_object())>query("max_tili", this_object()) )
set("tili",query("max_tili",  this_object()), 		this_object());
     }

     follower=query_temp("is_rided_follow", this_object());
     if (! objectp(follower))return;

     if (! objectp(environment(follower)) || 
         (objectp(follower) && (userp(follower) && ! interactive(follower))) ||
          (objectp(follower) && environment(follower) != query_temp("is_rided_by", environment(this_object()))) )
     {
delete_temp("is_rided_follow", 	this_object());
     }

     return;
}

int query_autoload()
{
     return 1;
}