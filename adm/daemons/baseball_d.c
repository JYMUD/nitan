/* This program is a part of RW mudlib
 * See /doc/help/copyright for more info
 -----------------------------------------
 * File   : baseball_d.c
 * Author : Clode@RevivalWorld
 * Date   : 2010-08-14
 * Note   : ����ϵͳ
 * Update :
 *  o 2000-00-00  
 *
 -----------------------------------------
 */

#include <ansi.h>
#include <message.h>
#include <npc.h>
#include <time.h>
#include <skill.h>
#include <baseball.h>
#include <equipment.h>
#include <buff.h>

#define DATA		"/data/daemon/baseball.o"
#define BACKUP_DATA	"/data/daemon/baseball.o.bak"

string *season;
mapping setup;
mapping record;
array games;
private nosave int tick;
private nosave int max_game_times;
int post_season_level;
int post_season_start;
string *post_season_team_8;
string *post_season_team_4;
string *post_season_team_2;
string *post_season_eliminate_teams;
int season_year;

private varargs string *game_finish(int gameindex, string stopid);

private nosave mapping positionname = 
([
	"P" : HIC"Ͷ"NOR CYN"��"NOR,
	"C" : HIG"��"NOR GRN"��"NOR,
	"1B" : HIG"һ"NOR GRN"����"NOR,
	"2B" : HIG"��"NOR GRN"����"NOR,
	"3B" : HIG"��"NOR GRN"����"NOR,
	"SS" : HIG"��"NOR GRN"����"NOR,
	"RF" : HIY"��"NOR YEL"��Ұ��"NOR,
	"CF" : HIY"��"NOR YEL"��Ұ��"NOR,
	"LF" : HIY"��"NOR YEL"��Ұ��"NOR,
	"DH" : HIR"ָ"NOR RED"�����"NOR,
]);
private nosave string *pitch_ball_types = ({ "fourseam", "twoseam", "curveball", "slider", "forkball", "sinker" });
private nosave mapping pitch_ball_types_name = 
([
	"fourseam":"�ķ��߿�����",
	"twoseam":"�����߿�����",
	"curveball":"����",
	"slider":"����",
	"forkball":"ָ����",
	"sinker":"�쿨��",
]);

// ����������ֵ���ɿ��Ʊ仯�ʲ�������һ����Χ��
int calculate(int value, float decay, int value_max, int to_min, int to_max)
{
	float ratio = (to_max - to_min) / pow(to_float(value_max), decay);
	
	value = to_int( pow(to_float(value), decay) * ratio );
	
	value += to_min;
	
	return value;
}

int calculate_max_game_times(int year)
{
	if( !mapp(record[year]) ) return 0;
		
	max_game_times = 0;
	
	foreach(string team, mapping data in record[year][RECORD_TEAM])
		if( data["win"] + data["lose"] > max_game_times )
			max_game_times = data["win"] + data["lose"];
			
	return max_game_times;
}

int sort_team(string team1, string team2)
{
	int year = season_year;
	int win1, win2, lose1, lose2;
	int limit = (max_game_times-10)/2;
	float winrate1, winrate2;
	
	if( !mapp(record[year]) ) return 0;
		
	if( !mapp(record[year][RECORD_TEAM][team1]) )
		return 1;
		
	if( !mapp(record[year][RECORD_TEAM][team2]) )
		return -1;
		
	win1 = record[year][RECORD_TEAM][team1]["win"];
	win2 = record[year][RECORD_TEAM][team2]["win"];
	lose1 = record[year][RECORD_TEAM][team1]["lose"];
	lose2 = record[year][RECORD_TEAM][team2]["lose"];
	
	if( win1+lose1 == 0 )
		return 1;
	
	if( win2+lose2 == 0 )
		return -1;
		
	winrate1 = to_float(win1)/(win1+lose1);
	winrate2 = to_float(win2)/(win2+lose2);
	
	if( limit < 10 ) limit = 10;
		
	if( win1+lose1 < limit )
	{
		if( win2+lose2 <= limit )
			return winrate1 > winrate2 ? -1 : 1;
				
		return 1;
	}
	
	if( win2+lose2 < limit )
		return -1;

	if( winrate1 == winrate2 )
		return win1 > win2 ? -1 : 1;
	else
		return winrate1 > winrate2 ? -1 : 1;
}

string query_positionname(string code)
{
	return positionname[code];	
}

int save()
{
	save_object(DATA);
}

int backup()
{
	return cp(DATA, BACKUP_DATA);
}

varargs void broadcast(string msg, mapping game)
{
	if( post_season_start && post_season_level > 0 )
	{
		CHANNEL_D->channel_broadcast("sport", msg);
	}
	else
	{
		object user;
		
		foreach(string listener in setup[game[TEAM1]]["listener"] | setup[game[TEAM2]]["listener"] )
			if( objectp(user = find_player(listener)) )
				tell(user, HIG"��������"NOR+msg+"\n");
	}
}

// ��Ա����Ӽ�¼
mixed add_record(int recordtype, string id, string key, mixed value)
{
	int year = season_year;
	
	if( undefinedp(record[year]) )
	{
		record[year] = allocate_mapping(0);
		record[year][RECORD_TEAM] = allocate_mapping(0);
		record[year][RECORD_PLAYER] = allocate_mapping(0);
		record[year][RECORD_SPECIAL] = allocate_mapping(0);
	}
	
	if( undefinedp(record[year][recordtype][id]) )
		record[year][recordtype][id] = allocate_mapping(0);
		
	if( intp(value) || floatp(value) )
		record[year][recordtype][id][key] += value;
	else
		record[year][recordtype][id][key] = value;
	
	return record[year][recordtype][id][key];
}

varargs mixed get_record(int recordtype, string id, string key, int year)
{
	if( undefinedp(year) )
		year = season_year;
	
	if( undefinedp(record[year]) ||  undefinedp(record[year][recordtype][id]) ) return 0;
		
	return record[year][recordtype][id][key];
}

// ������Ա��¼
void add_player_record(string id, int number, string key, int value)
{
	string player = setup[id]["roster"][number]["file"];

	add_record(RECORD_PLAYER, player, key, value);
}

// ������Ӽ�¼
void add_team_record(string id, string key, int value)
{
	add_record(RECORD_TEAM, id, key, value);
}

// ȷ������趨�Ϸ�
varargs int valid_setup(string id, int all)
{
	object labor;
	object env;
	mapping roster_data;
	object boss = find_player(id);
	int fldaccuracy, fldrange;
	
	if( !mapp(setup[id]) ) return 0;	
	
	if( objectp(boss) )
	{
		setup[id]["username"] = boss->query_idname();
	}
	else if( !stringp(setup[id]["username"]) )
	{
		boss = load_user(id);
			
		setup[id]["username"] = boss->query_idname();	
			
		if( !userp(boss) )
			destruct(boss);	
	}
	
	if( !stringp(setup[id]["name"]) ) return 0;

	if( all )
	{
		setup[id]["outfield"] = 0;
		setup[id]["infield"] = 0;
	}
	
	for(int i=0;i<10;++i)
	{
		roster_data = setup[id]["roster"][i];
		
		if( !mapp(roster_data) )
			return 0;
			
		if( !objectp(labor = roster_data["object"]) )
		{
			if( !file_exists(roster_data["file"]) || !objectp(labor = load_object(roster_data["file"])) )
			{
				setup[id]["roster"][i] = 0;
				return 0;
			}

			roster_data["object"] = labor;
		}

		if( i==0 && labor->query_skill_level("twohands") > 0 )
			return 0;

		env = environment(labor);
		
		if( !objectp(env) || !env->is_module_room() || env->query_building_type() != "baseball" || query("owner", env) != query("boss", labor) || query("job/type", labor) != SPORTER )
		{
			setup[id]["roster"][i] = 0;
			return 0;
		}
		
		if( all )
		{
			roster_data[BUFF_BATTER_POWER] = labor->query_equipment_buff(BUFF_BATTER_POWER);
			roster_data[BUFF_PITCHER_POWER] = labor->query_equipment_buff(BUFF_PITCHER_POWER);
			roster_data[BUFF_FIELDER_POWER] = labor->query_equipment_buff(BUFF_FIELDER_POWER);

			fldaccuracy = labor->query_skill_level("fldaccuracy") + roster_data[BUFF_FIELDER_POWER];
			fldrange = labor->query_skill_level("fldrange") + roster_data[BUFF_FIELDER_POWER];
				
			switch(roster_data["position"])
			{
				case "P": setup[id]["infield"] += fldaccuracy * 4 / 5 + fldrange * 1 / 5 + labor->query_agi()/2; break;
				case "C": setup[id]["infield"] += fldaccuracy * 4 / 5 + fldrange * 1 / 5 + labor->query_agi()/2; break;
				case "1B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "2B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "3B": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "SS": setup[id]["infield"] += fldaccuracy * 2 / 3 + fldrange * 1 / 3 + labor->query_agi()/2; break;
				case "RF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "CF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "LF": setup[id]["outfield"] += fldaccuracy * 1 / 4 + fldrange * 3 / 4 + labor->query_agi()/2; break;
				case "DH": break;
			}
			
			if( i == 9 )
			{
				setup[id]["outfield"] = calculate(setup[id]["outfield"], 0.8, 999*3, 500, 1000);
				setup[id]["infield"] = calculate(setup[id]["infield"], 0.8, 999*6, 500, 1000);
			}	
		}
	}
	
	return 1;
}

// �������ÿ������Ӧ������
int query_income(string id)
{
	int year = season_year;
	int win, lose;
	
	if( !valid_setup(id) || !mapp(record[year]) || !mapp(record[year][RECORD_TEAM][id]) ) 
		return 0;	
	
	win = record[year][RECORD_TEAM][id]["win"];
	lose = record[year][RECORD_TEAM][id]["lose"];

	if( win + lose <= 0 ) return 0;

	return BASEINCOME * win / (win + lose);
}

string query_player_status(object player)
{
	string id = query("boss", player);
	mapping data;
	
	if( !undefinedp(setup[id]) && arrayp(setup[id]["roster"]) )
	{
		for(int i=0;i<10;++i)
		{
			data = setup[id]["roster"][i];
			
			if( !mapp(data) ) continue;

			if( data["file"] == base_name(player) )
				return positionname[data["position"]]+" "+(i > 0 ? GRN"�� "HIG+i+NOR GRN" �� "NOR:"");
		}	
	}
	
	return "";
}

// ����趨
void set_setup(string id, mapping newsetup)
{
	setup[id] += newsetup;
	
	save();
}

// ɾ������趨
void delete_setup(string id)
{
	map_delete(setup, id);
	
	save();
}

// ���뼾��
void join_season(string id)
{
	int index;
	
	// �Ѿ����뼾��
	if( member_array(id, season) != -1 ) return;
		
	season = sort_array(season, (: random(2) ? 1 : -1 :));

	foreach(string oldid in season)
	{
		index = random(sizeof(setup[oldid]["opponents"]));
	
		if( member_array(id, setup[oldid]["opponents"]) == -1 )
			setup[oldid]["opponents"] = setup[oldid]["opponents"][0..index] + ({ id }) + setup[oldid]["opponents"][index+1..];
	}
	
	if( !sizeof(setup[id]["opponents"]) )
		setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :)));

	setup[id]["listener"] |= ({ id });

	season |= ({ id });		
}

// ȡ������
varargs void cancel_game(string id, int force)
{
	int gamessize = sizeof(games);
	
	for(int i=0;i<gamessize;++i)
	{
		if( !mapp(games[i]) ) continue;
		
		if( games[i][TEAM1] == id || games[i][TEAM2] == id )
		{
			if( force )
			{
				if( games[i][TEAM1] == id )
					game_finish(i, id);
				else if( games[i][TEAM2] == id )
					game_finish(i, id);
			}
			else
			{
				setup[games[i][TEAM1]]["status"] = STATUS_IDLE;
				setup[games[i][TEAM2]]["status"] = STATUS_IDLE;
				
				games[i] = 0;
			}
		}
	}
	
	games -= ({ 0 });
}

// �˳�����
void leave_season(string id)
{
	if( member_array(id, season) == -1 ) return;

	foreach(string oldid in season)
		setup[oldid]["opponents"] -= ({ id });

	cancel_game(id);

	season -= ({ id });
}

// �Ƿ���뼾��
int in_season(string id)
{
	return member_array(id, season) != -1;
}

// �Ƿ����ڱ�����
int query_status(string id)
{
	if( !in_season(id) ) return 0;
		
	return setup[id]["status"];
}

// ��������
private varargs string *game_finish(int gameindex, string stopid)
{
	int year = season_year;
	string *msg = allocate(0);
	mapping game = games[gameindex];
	string team1name = setup[game[TEAM1]]["name"];
	string team2name = setup[game[TEAM2]]["name"];
	string income_msg = HIG"����"NOR GRN"����"NOR;
	string finalscore;
	string winteam, loseteam;
	
	if( !undefinedp(stopid) && stringp(stopid) )
	{
		if( game[TEAM1] == stopid )
			game[TEAM1SCORE] = -1;
		else if( game[TEAM2] == stopid )
			game[TEAM2SCORE] = -1;	
	}

	if( game[TEAM1SCORE] > game[TEAM2SCORE] )
	{
		winteam = game[TEAM1];
		loseteam = game[TEAM2];
	}
	else
	{
		winteam = game[TEAM2];
		loseteam = game[TEAM1];
	}
	finalscore = HIG"����"NOR GRN"���"NOR" ˫��"+(game[INNING]>18?"һ�������� "+(game[INNING]/2+game[INNING]%2)+" �֣�":"")+"�ȷ�Ϊ"+setup[game[TEAM2]]["username"]+"��"+team2name+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+team1name+"��"+setup[game[TEAM1]]["username"];
	
	switch(game[TEAM1SCORE] - game[TEAM2SCORE])
	{
		case -999..-16:		msg += ({ finalscore+"�������ġ�"+team1name+"���⵽�˿ֲ���Ѫ����ɱ" });	break;
		case -15..-11:		msg += ({ finalscore+"����"+team2name+"�����׵������˶���" });			break;
		case -10..-6:		msg += ({ finalscore+"����"+team2name+"�����������ʹ���˶���" });		break;
		case -5..-3:		msg += ({ finalscore+"����"+team2name+"�����ⳡ���������ɻ�ʤ" });		break;
		case -2..-1:		msg += ({ finalscore+"����"+team2name+"���ھ����л�ʤ" });			break;
		case 1..2:		msg += ({ finalscore+"����"+team1name+"���ھ����л�ʤ" });			break;
		case 3..5:		msg += ({ finalscore+"����"+team1name+"�����ⳡ���������ɻ�ʤ" });		break;
		case 6..10:		msg += ({ finalscore+"����"+team1name+"�����������ʹ���˶���" });		break;
		case 11..15:		msg += ({ finalscore+"����"+team1name+"�����׵������˶���" });			break;
		case 16..999:		msg += ({ finalscore+"�������ġ�"+team2name+"���⵽�˿ֲ���Ѫ����ɱ" });	break;
		//default: error("error score");
	}
	
	if( !post_season_level )
	{	
		add_team_record(winteam, "win", 1);
		add_team_record(loseteam, "lose", 1);

		if( setup[winteam]["keeploses"] >= 5 )
		{
			msg += ({ "��"+setup[winteam]["name"]+"����ֹ������� "HIG+setup[winteam]["keeploses"]+NOR" ���ܡ�" });
		}
		if( setup[loseteam]["keepwins"] >= 5 )
		{
			msg += ({ "��"+setup[loseteam]["name"]+"����ֹ������� "HIR+setup[loseteam]["keepwins"]+NOR" ��ʤ��" });
		}
			
		setup[winteam]["keepwins"]++;
		setup[winteam]["keeploses"] = 0;
		
		setup[loseteam]["keepwins"] = 0;
		setup[loseteam]["keeploses"]++;
		
		if( setup[winteam]["keepwins"] > record[year][RECORD_SPECIAL]["keepwins"] )
		{
			record[year][RECORD_SPECIAL]["keepwins"] = setup[winteam]["keepwins"];
			record[year][RECORD_SPECIAL]["keepwinsteam"] = winteam;
			
			msg += ({ HIY"��¼"NOR YEL"���� "NOR"ʿ���߰��ġ�"+setup[winteam]["name"]+"��ͻ�Ʊ������ʤ��¼��"HIR"��ʤ"NOR RED"��¼"NOR"������ "HIR+setup[winteam]["keepwins"]+NOR" ��" });
		}
		else if( setup[winteam]["keepwins"] >= 5 )
		{
			msg += ({ "��"+setup[winteam]["name"]+"�����һ�� "HIR+setup[winteam]["keepwins"]+NOR" ��ʤ��ս�����Ծ��" });
		}
		
		if( setup[loseteam]["keeploses"] > record[year][RECORD_SPECIAL]["keeploses"] )
		{
			record[year][RECORD_SPECIAL]["keeploses"] = setup[loseteam]["keeploses"];
			record[year][RECORD_SPECIAL]["keeplosesteam"] = loseteam;
			
			msg += ({ HIY"��¼"NOR YEL"���� "NOR"ʿ������ġ�"+setup[loseteam]["name"]+"�����̱�������ܼ�¼��"HIG"����"NOR GRN"��¼"NOR"������ "HIG+setup[loseteam]["keeploses"]+NOR" ��" });
		}
		else if( setup[loseteam]["keeploses"] >= 5 )
		{
			msg += ({ "��"+setup[loseteam]["name"]+"���������� "HIG+setup[loseteam]["keeploses"]+NOR" ���ܣ�ս������˺�" });
		}
	}
	
	// ������������¼
	if( game[TEAM1K] > game[TEAM2K] && game[TEAM1K] > record[year][RECORD_SPECIAL]["maxstrikeouts"] )
	{
		record[year][RECORD_SPECIAL]["maxstrikeouts"] = game[TEAM1K];
		record[year][RECORD_SPECIAL]["maxstrikeoutsplayer"] = setup[game[TEAM1]]["roster"][0]["file"];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team1name+"����"+setup[game[TEAM1]]["roster"][0]["object"]->query_idname()+"ͻ�Ʊ���Ͷ�ֵ�����������¼����¼���� "HIY+game[TEAM1K]+NOR YEL"K"NOR" ����" });
	}
	else if( game[TEAM2K] > game[TEAM1K] && game[TEAM2K] > record[year][RECORD_SPECIAL]["maxstrikeouts"] )
	{
		record[year][RECORD_SPECIAL]["maxstrikeouts"] = game[TEAM2K];
		record[year][RECORD_SPECIAL]["maxstrikeoutsplayer"] = setup[game[TEAM2]]["roster"][0]["file"];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team2name+"����"+setup[game[TEAM2]]["roster"][0]["object"]->query_idname()+"ͻ�Ʊ���Ͷ�ֵ�����������¼����¼���� "HIY+game[TEAM2K]+NOR YEL"K"NOR" ����" });
	}
	
	// ������ల���¼
	if( game[TEAM1HIT] > game[TEAM2HIT] && game[TEAM1HIT] > record[year][RECORD_SPECIAL]["maxhits"] )
	{
		record[year][RECORD_SPECIAL]["maxhits"] = game[TEAM1HIT];
		record[year][RECORD_SPECIAL]["maxhitsteam"] = game[TEAM1];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team1name+"��ͻ�Ʊ���������ల���¼����¼���� "HIY+game[TEAM1HIT]+NOR YEL" ֻ����"NOR" ����" });
	}
	else if( game[TEAM2HIT] > game[TEAM1HIT] && game[TEAM2HIT] > record[year][RECORD_SPECIAL]["maxhits"] )
	{
		record[year][RECORD_SPECIAL]["maxhits"] = game[TEAM2HIT];
		record[year][RECORD_SPECIAL]["maxhitsteam"] = game[TEAM2];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team2name+"��ͻ�Ʊ���������ల���¼����¼���� "HIY+game[TEAM2HIT]+NOR YEL" ֻ����"NOR" ����" });
	}
		
	// �������÷ּ�¼
	if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM1SCORE] > record[year][RECORD_SPECIAL]["maxscores"] )
	{
		record[year][RECORD_SPECIAL]["maxscores"] = game[TEAM1SCORE];
		record[year][RECORD_SPECIAL]["maxscoresteam"] = game[TEAM1];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team1name+"��ͻ�Ʊ����������÷ּ�¼����¼���� "HIY+game[TEAM1SCORE]+NOR YEL" ��"NOR" ����" });
	}
	else if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM2SCORE] > record[year][RECORD_SPECIAL]["maxscores"] )
	{
		record[year][RECORD_SPECIAL]["maxscores"] = game[TEAM2SCORE];
		record[year][RECORD_SPECIAL]["maxscoresteam"] = game[TEAM2];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team2name+"��ͻ�Ʊ����������÷ּ�¼����¼���� "HIY+game[TEAM2SCORE]+NOR YEL" ��"NOR" ����" });
	}
	
	// ������������¼
	if( game[INNING] > record[year][RECORD_SPECIAL]["maxinnings"] )
	{
		record[year][RECORD_SPECIAL]["maxinnings"] = game[INNING];
		record[year][RECORD_SPECIAL]["maxinningsteam1"] = game[TEAM1];
		record[year][RECORD_SPECIAL]["maxinningsteam2"] = game[TEAM2];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team1name+"���롰"+team2name+"����ͬ���챾�������ӳ�����������¼����¼���� "HIY+(game[INNING]/2 + game[INNING]%2)+NOR YEL" ��"NOR" ����" });
	}
	
	// ��������������¼
	if( abs(game[TEAM1SCORE] - game[TEAM2SCORE]) > record[year][RECORD_SPECIAL]["maxscorediff"] )
	{
		record[year][RECORD_SPECIAL]["maxscorediff"] = abs(game[TEAM1SCORE] - game[TEAM2SCORE]);
		record[year][RECORD_SPECIAL]["maxscorediffwin"] = game[TEAM1SCORE] > game[TEAM2SCORE] ? game[TEAM1] : game[TEAM2];
		record[year][RECORD_SPECIAL]["maxscoredifflose"] = game[TEAM1SCORE] < game[TEAM2SCORE] ? game[TEAM1] : game[TEAM2];
		
		msg += ({ HIY"��¼"NOR YEL"���� "NOR"��"+team1name+"���롰"+team2name+"����ͬ���챾�����������������¼����¼���� "HIY+abs(game[TEAM1SCORE] - game[TEAM2SCORE])+NOR YEL" ��"NOR" ����" });
	}
	
	setup[game[TEAM1]]["status"] = STATUS_IDLE;
	setup[game[TEAM2]]["status"] = STATUS_IDLE;

	if( !post_season_level )
		for(int i=0;i<sizeof(msg);++i)
			call_out((: CHANNEL_D->channel_broadcast("sport", $(msg)[$(i)]) :), 0);
			
	if( undefinedp(stopid) )
	{
		int income;
		int total_income = query_income(game[TEAM1]) + query_income(game[TEAM2]);
		
		if( file_exists(setup[game[TEAM2]]["master"]) )
		{
			object master = load_object(setup[game[TEAM2]]["master"]);
			
			income = total_income * 10 / 100;
			income += total_income * 80 / 100 * game[TEAM2SCORE] / (game[TEAM1SCORE]+game[TEAM2SCORE]);
			
			if( post_season_level && post_season_start )
				income *= 20;
				
			if( query("owner", master) == game[TEAM2] && objectp(find_player(game[TEAM2])) )
			{
				addn("money", income, master);
				income_msg += "��"+setup[game[TEAM2]]["name"]+"�����Ʊ������ "HIY+money(MONEY_D->query_default_money_unit(), income)+NOR;
							
				master->save();
			}
		}
		
		if( file_exists(setup[game[TEAM1]]["master"]) )
		{
			object master = load_object(setup[game[TEAM1]]["master"]);
			
			income = total_income * 10/ 100;
			income += total_income * 80 / 100 * game[TEAM1SCORE] / (game[TEAM1SCORE]+game[TEAM2SCORE]);
			
			if( post_season_level && post_season_start )
				income *= 20;
	
			if( query("owner", master) == game[TEAM1] && objectp(find_player(game[TEAM1])) )
			{
				addn("money", income, master);
				income_msg += "��"+setup[game[TEAM1]]["name"]+"�����Ʊ������ "HIY+money(MONEY_D->query_default_money_unit(), income)+" "NOR;
				
				master->save();
			}
		}
		
		if( income_msg != HIG"����"NOR GRN"����"NOR )
			msg += ({ income_msg });
	}

	if( post_season_start )
	{		
		switch(post_season_level)
		{
			case 1..4: 
			{
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					post_season_team_4 |= ({ game[TEAM1] });
					msg += ({ HIR"����"NOR RED"��"NOR" "+setup[game[TEAM1]]["username"]+"����ġ�"+setup[game[TEAM1]]["name"]+"�������ǿ��������" });
					post_season_eliminate_teams |= ({ game[TEAM2] });
				}
				else
				{
					post_season_team_4 |= ({ game[TEAM2] });
					msg += ({ HIR"����"NOR RED"��"NOR" "+setup[game[TEAM2]]["username"]+"����ġ�"+setup[game[TEAM2]]["name"]+"�������ǿ��������" });
					post_season_eliminate_teams |= ({ game[TEAM1] });
				}
				save();
				break;
			}
			case 5..6:
			{
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					post_season_team_2 |= ({ game[TEAM1] });
					msg += ({ HIR"����"NOR RED"��"NOR" "+setup[game[TEAM1]]["username"]+"����ġ�"+setup[game[TEAM1]]["name"]+"����ý����ܹھ�������" });
					post_season_eliminate_teams |= ({ game[TEAM2] });
				}
				else
				{
					post_season_team_2 |= ({ game[TEAM2] });
					msg += ({ HIR"����"NOR RED"��"NOR" "+setup[game[TEAM2]]["username"]+"����ġ�"+setup[game[TEAM2]]["name"]+"����ý����ܹھ�������" });
					post_season_eliminate_teams |= ({ game[TEAM1] });
				}
				save();
				break;
			}
			case 7:
			{
				object user;
				
				if( game[TEAM1SCORE] > game[TEAM2SCORE] )
				{
					msg += ({ HIR"����"NOR RED"��"NOR" ��ϲ"+setup[game[TEAM1]]["username"]+"����ġ�"+setup[game[TEAM1]]["name"]+"�����"NOR CYN"�� "HIC+year+NOR CYN" ��"HIY"����"NOR YEL"����ھ�"NOR"����" });
					record[year][RECORD_SPECIAL]["champion"] = game[TEAM1];
					record[year][RECORD_SPECIAL]["2rd"] = game[TEAM2];
					post_season_eliminate_teams |= ({ game[TEAM2] });
					user = load_user(game[TEAM1]);
				}
				else
				{
					msg += ({ HIR"����"NOR RED"��"NOR" ��ϲ"+setup[game[TEAM2]]["username"]+"����ġ�"+setup[game[TEAM2]]["name"]+"�����"NOR CYN"�� "HIC+year+NOR CYN" ��"HIY"����"NOR YEL"����ھ�"NOR"����" });
					record[year][RECORD_SPECIAL]["champion"] = game[TEAM2];
					record[year][RECORD_SPECIAL]["2rd"] = game[TEAM1];
					post_season_eliminate_teams |= ({ game[TEAM1] });
					
					user = load_user(game[TEAM2]);
				}
				
				if( objectp(user) )
				{
					object ring = new("/obj/baseball/champion_ring_"+year);
					
					user->add_title(sprintf(HIC+"%-4d"+HIY"��"NOR YEL"��"NOR YEL"��"NOR, year));
					user->save();				
					
					tell(user, pnoun(2, user)+"���һֻ��"+ring->query_idname()+"����\n");
					CHANNEL_D->channel_broadcast("sport", user->query_idname()+"���һֻ��"+ring->query_idname()+"����");
					
					ring->set_keep();
					ring->move(user);
					
					if( !userp(user) )
						destruct(user);
				}
					
				save();
					
				break;
			}
		}
	}
	
	if( !random(10) )
	{
		int status;
		object *equipments;
		
		foreach(mapping roster_data in setup[game[TEAM1]]["roster"] + setup[game[TEAM2]]["roster"])
		{
			if( !objectp(roster_data["object"]) ) continue;
				
			equipments = roster_data["object"]->query_equipping_object(EQ_MITT[PART_ID]) || allocate(0);
			equipments |= roster_data["object"]->query_equipping_object(EQ_BAT[PART_ID]) || allocate(0);
			
			if( !sizeof(equipments) ) continue;
				
			equipments = sort_array(equipments, (: random(2) ? 1 : -1 :));
				
			if( !random(25) )
			{
				msg += ({ roster_data["object"]->query_idname()+"��ʹ�õ�"+equipments[0]->query_idname()+"���ⳡ�����л����ˣ���\n" });
				
				roster_data["object"]->unequip(equipments[0], ref status);
				
				destruct(equipments[0], 1);
			}
		}
	}
			
	games[gameindex] = 0;
	//games -= ({ 0 });

	return msg;
}

// �������
private string *new_score(int gameindex, string attacker, string defender, int score, int scoretype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];
	int attacknumber;
	
	// ����÷�
	if( attacker == game[TEAM1] )
	{
		game[TEAM1SCORE] += score;
		attacknumber = game[TEAM1NUMBER];
	}
	else
	{
		game[TEAM2SCORE] += score;
		attacknumber = game[TEAM2NUMBER];
	}
		
	add_player_record(defender, 0, "run", score);
	add_player_record(attacker, attacknumber, "rbi", score);
	
	msg += ({ "��"+setup[game[TEAM2]]["name"]+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+setup[game[TEAM1]]["name"] +"��" });
	
	// �°�֣��ټ��÷�
	if( game[INNING] >= 18 && (game[INNING] % 2) == 0 && game[TEAM1SCORE] > game[TEAM2SCORE] )
	{
		switch(scoretype)
		{
			case SCORETYPE_HOMERUN:		msg += ({ "����һֻ�ټ�ȫ�ݴ򣡣�" }); 	break;
			case SCORETYPE_FOURBALL:	msg += ({ "����һ���ټ��Ļ�����" }); 	break;
			case SCORETYPE_SACRIFICE:	msg += ({ "����һֻ�ټ������򣡣�" });	break;
			case SCORETYPE_HIT:		msg += ({ "����һֻ�ټ����򣡣�" }); 	break;
			default: error("error scoretype");
		}

		msg += game_finish(gameindex);
	}
	
	return msg;
}

// �����µĳ�����
private string *new_out(int gameindex, string attacker, string defender, int outcount, int outtype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];
	int attackernumber = attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER];
		
	game[STRIKE] = 0;
	game[BALL] = 0;

	// ��ϯ������¼
	add_player_record(attacker, attackernumber, "ab", 1);
	
	// Ͷ�ֶԾ��˴μ�¼
	add_player_record(defender, 0, "bf", 1);
	
	// Ͷ�ֶԾ�������
	add_player_record(defender, 0, "out", outcount);
	
	if( outtype == BASETYPE_STRIKEOUT )
		add_player_record(defender, 0, "strikeout", 1);	
			
	if( (game[OUT]+=outcount) >= 3 )
	{			
		game[OUT] = 0;

		if( game[INNING] >= 17 && (((game[INNING] % 2) && game[TEAM1SCORE] > game[TEAM2SCORE]) || (!(game[INNING] % 2) && game[TEAM1SCORE] != game[TEAM2SCORE])))
			return game_finish(gameindex);
		
		game[INNING]++;
		
		msg += ({ "��"+setup[game[TEAM2]]["name"]+" "+game[TEAM2SCORE]+" : "+game[TEAM1SCORE]+" "+setup[game[TEAM1]]["name"] +"�����ؽ��棬�������뵽"+(game[INNING]>=19?"�ӳ���":"")+"�� "+( game[INNING]%2 ? ((game[INNING]+1)/2)+" ���ϰ�" : ((game[INNING]+1)/2)+" ���°�" ) });
			
		game[RUNNER1ST] = 0;
		game[RUNNER2ND] = 0;
		game[RUNNER3RD] = 0;
	}
	else
	{	
		// ��ɱ, �л������
		if( outtype == BASETYPE_BUNT || outtype == BASETYPE_TOUCHKILL )
		{
			// �������ɱ��������
			if( game[RUNNER3RD] > 0 && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 )
			{
				game[RUNNER3RD] = game[RUNNER2ND];
				game[RUNNER2ND] = game[RUNNER1ST];
				game[RUNNER1ST] = attackernumber;
			}
			else
			{
				// �������� ��������, ����
				if( game[RUNNER3RD] == 0 && game[RUNNER2ND] > 0 )
				{
					game[RUNNER3RD] = game[RUNNER2ND];
					game[RUNNER2ND] = 0;
				}
				
				// �������� һ������, ����
				if( game[RUNNER2ND] == 0 && game[RUNNER1ST] > 0 )
				{
					game[RUNNER2ND] = game[RUNNER1ST];
					game[RUNNER1ST] = 0;
				}
			}	
		}
		// ��ɱ, �л������
		else if( outtype == BASETYPE_CATCHKILL )
		{
			if( game[RUNNER3RD] > 0 )
			{
				msg += ({ "��"+setup[attacker]["name"]+"���������߳�ر��ݵ÷֣�" });
				msg += new_score(gameindex, attacker, defender, 1, SCORETYPE_SACRIFICE);
				
				if( !games[gameindex] )
					return msg;

				game[RUNNER3RD] = 0;
			}
		}
		// ˫ɱ, �л������
		else if( outtype == BASETYPE_DOUBLEPLAY )
		{
			// �������� ��������, ����
			if( game[RUNNER2ND] > 0 )
			{
				game[RUNNER3RD] = game[RUNNER2ND];
				game[RUNNER2ND] = 0;
			}
			
			game[RUNNER1ST] = 0;
		}
		// ��ɱ , �����ϲ���ִ�е���(ֱ�ӻ���)
		//else if( outtype == BASETYPE_TRIPLEPLAY ) { }
		
		if( game[RUNNER3RD] > 0 || game[RUNNER2ND] > 0 || game[RUNNER1ST] > 0 )
			msg += ({ "��"+setup[attacker]["name"]+"��Ŀǰ���ϵ���������Ϊ [ "+(game[RUNNER3RD] > 0?HIW"��"NOR:WHT"�w"NOR)+" "+(game[RUNNER2ND] > 0?HIW"��"NOR:WHT"�w"NOR)+" "+(game[RUNNER1ST] > 0?HIW"��"NOR:WHT"�w"NOR)+" ] "HIW+game[OUT]+NOR WHT"out"NOR });
	}

	// ����һ��
	if( attacker == game[TEAM1] )
		game[TEAM1NUMBER] = 1 + (game[TEAM1NUMBER] % 9);
	else
		game[TEAM2NUMBER] = 1 + (game[TEAM2NUMBER] % 9);
		
	setup[attacker]["hint"] = 0;
	setup[defender]["hint"] = 0;
	
	games[gameindex] = game;
	
	return msg;
}

// �����µĽ���
private string *new_base(int gameindex, string attacker, string defender, int basecount, int basetype)
{
	string *msg = allocate(0);
	mapping game = games[gameindex];

	int score = 0;
	int attacknumber = attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER];
	
	if( basecount <= 0 ) error("basecount_error");

	game[STRIKE] = 0;
	game[BALL] = 0;

	// Ͷ�ֶԾ��˴�
	add_player_record(defender, 0, "bf", 1);

	if( basetype == BASETYPE_HIT ) // �������
	{
		int scoretype;
		
		// ���ߴ��������¼
		add_player_record(attacker, attacknumber, "ab", 1);

		if( attacker == game[TEAM1] )
			game[TEAM1HIT]++;
		else
			game[TEAM2HIT]++;
			
		switch(basecount)
		{
			case 1:
			{
				add_player_record(attacker, attacknumber, "hit1", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 )
				{
					if( random(setup[attacker]["roster"][game[RUNNER2ND]]["object"]->query_int()) > random(400) )
					{
						score++; 
						msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" });	
					
						game[RUNNER2ND] = 0; 
					}
					else
					{
						game[RUNNER3RD] = game[RUNNER2ND];
						game[RUNNER2ND] = 0; 
					}
				}
						
				// һ�����ˣ�����
				if( game[RUNNER1ST] > 0 )
				{
					if( game[RUNNER3RD] > 0 )
						game[RUNNER2ND] = game[RUNNER1ST];
					else
						game[RUNNER3RD] = game[RUNNER1ST];
						
					game[RUNNER1ST] = 0;
				}
				
				// �����ϵ�һ��
				game[RUNNER1ST] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
				
				scoretype = SCORETYPE_HIT;
				
				break;
			}
			case 2:
			{
				add_player_record(attacker, attacknumber, "hit2", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"��һ�����߱��ر��ݵ÷֣�" }); game[RUNNER1ST] = 0; }
				
				// �����ϵ�����
				game[RUNNER2ND] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
	
				scoretype = SCORETYPE_HIT;
				
				break;	
			}
			case 3:
			{
				add_player_record(attacker, attacknumber, "hit3", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"��һ�����߱��ر��ݵ÷֣�" }); game[RUNNER1ST] = 0; }
							
				// �����ϵ�����
				game[RUNNER3RD] = (attacker == game[TEAM1] ? game[TEAM1NUMBER] : game[TEAM2NUMBER]);
				
				scoretype = SCORETYPE_HIT;
				
				break;	
			}
			case 4:
			{
				add_player_record(attacker, attacknumber, "hit4", 1);
				add_player_record(attacker, attacknumber, "hit", 1);
				
				if( game[RUNNER3RD] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" }); game[RUNNER3RD] = 0; }	
				if( game[RUNNER2ND] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"���������߱��ر��ݵ÷֣�" }); game[RUNNER2ND] = 0; }
				if( game[RUNNER1ST] > 0 ) {	score++; msg += ({ "��"+setup[attacker]["name"]+"��һ�����߱��ر��ݵ÷֣�" }); game[RUNNER1ST] = 0; }
					
				msg += ({ "��"+setup[attacker]["name"]+"�����߱��ر��ݵ÷֣�" });
				score++;
	
				scoretype = SCORETYPE_HOMERUN;
				
				break;
			}
		}
		
		msg += new_score(gameindex, attacker, defender, score, scoretype);
			
		if( !games[gameindex] )
			return msg;
	}
	else if( basetype == BASETYPE_BALL ) // ���ͽ���
	{
		add_player_record(defender, 0, "fourball", 1);
		add_player_record(attacker, attacknumber, "walk", 1);

		// ��һ������
		if( game[RUNNER1ST] > 0 )
		{
			// ������Ҳ����
			if( game[RUNNER2ND] > 0 )
			{
				// ������Ҳ����
				if( game[RUNNER3RD] > 0 )
				{
					msg += ({ "��"+setup[attacker]["name"]+"���������ߺ����������߻ر��ݵ÷֣�" });
					msg += new_score(gameindex, attacker, defender, 1, SCORETYPE_FOURBALL);
					
					if( !games[gameindex] )
						return msg;
				}

				game[RUNNER3RD] = game[RUNNER2ND];	
			}

			game[RUNNER2ND] = game[RUNNER1ST];
		}

		game[RUNNER1ST] = attacknumber;	
	}

	// ����һ��
	if( attacker == game[TEAM1] )
		game[TEAM1NUMBER] = 1 + (game[TEAM1NUMBER] % 9);
	else
		game[TEAM2NUMBER] = 1 + (game[TEAM2NUMBER] % 9);

	setup[attacker]["hint"] = 0;
	setup[defender]["hint"] = 0;
	
	if( game[RUNNER3RD] > 0 || game[RUNNER2ND] > 0 || game[RUNNER1ST] > 0 )
		msg += ({ "��"+setup[attacker]["name"]+"��Ŀǰ���ϵ���������Ϊ [ "+(game[RUNNER3RD] > 0?HIW"��"NOR:WHT"�w"NOR)+" "+(game[RUNNER2ND] > 0?HIW"��"NOR:WHT"�w"NOR)+" "+(game[RUNNER1ST] > 0?HIW"��"NOR:WHT"�w"NOR)+" ] "HIW+game[OUT]+NOR WHT"out"NOR });
		
	games[gameindex] = game;

	return msg;
}

private void check_cache(object player)
{
	if( query_temp("baseballcache/handside/time", player) < time() - 300 )
	{
		int type;
		int level;
		
		if( (level = player->query_skill_level("twohands")) > 0 )
			type = HANDSIDE_TWOHANDS;
		else if( (level = player->query_skill_level("lefthand")) > 0 )
			type = HANDSIDE_LEFTHAND;
		else if( (level = player->query_skill_level("righthand")) > 0 )
			type = HANDSIDE_RIGHTHAND;
		else
			type = HANDSIDE_NONE;
			
		set_temp("baseballcache/handside", ([ "time":time(), "type":type, "level":level ]), player);
	}
}

int get_handside_type(object player)
{
	check_cache(player);
	return query_temp("baseballcache/handside/type", player);
}

int get_handside_level(object player)
{
	check_cache(player);
	return query_temp("baseballcache/handside/level", player);
}

// ������Ͷ�����ҷ��Ĳ��� (-60~70) ֮��
int get_handside_diff(object pitcher, object batter)
{
	int base_level_diff = (get_handside_level(batter) - get_handside_level(pitcher))/20;
	int batter_handside_type = get_handside_type(batter);
	int pitcher_handside_type = get_handside_type(pitcher);
	
	if( pitcher_handside_type == HANDSIDE_NONE )
		return 20 + base_level_diff;
	else if( batter_handside_type == HANDSIDE_TWOHANDS )
		return 8 + base_level_diff;
	else if( batter_handside_type != pitcher_handside_type )
		return 20 + base_level_diff;
	else
		return -10 + base_level_diff;
}

// ȡ�ô����
varargs float get_hit_rate(string teamid, int num, int year)
{
	int hit, ab;
	
	if( undefinedp(year) )
		year = season_year;

	if( undefinedp(setup[teamid]) || !mapp(setup[teamid]["roster"][num]) )
		return 0.;

	hit = get_record(RECORD_PLAYER, setup[teamid]["roster"][num]["file"], "hit", year);
	ab = get_record(RECORD_PLAYER, setup[teamid]["roster"][num]["file"], "ab", year);

	if( !hit || !ab ) return 0.;
		
	return 10. * hit / ab;
}

// ��������
void play_game()
{
	string *msg;
	mapping attacksetup, defendsetup;
	string attackteamname, defendteamname;
	int attacknumber, defendnumber;
	string attacker, defender;
	string team1, team2;
	mapping game;
	
	games -= ({ 0 });

	for(int gameindex=0;gameindex<sizeof(games);++gameindex)
	{
		msg = allocate(0);

		game = games[gameindex];
			
		if( ++game[TICK] < PREPARETIME ) continue;

		if( post_season_start && post_season_level )
		{
			if( (game[TICK]+gameindex) % POSTSEASON_TICKTIME ) continue;
		}
		else if( (game[TICK]+gameindex) % TICKTIME ) continue;

		team1 = game[TEAM1];
		team2 = game[TEAM2];
	
		if( !setup[team1] || !setup[team2] ) continue;

		if( !valid_setup(team1) )
		{
			broadcast(HIG"��������"NOR"��"+setup[team1]["name"]+"����������ϲ���������ֹ������\n", game);
			cancel_game(team1, 1);
			continue;
		}
			
		if( !valid_setup(team2) )
		{
			broadcast(HIG"��������"NOR"��"+setup[team2]["name"]+"����������ϲ���������ֹ������\n", game);
			cancel_game(team2, 1);
			continue;
		}
		
		if( game[TICK] <= PREPARETIME + TICKTIME && game[TICK] >= PREPARETIME )
		{
			setup[team1]["status"] = STATUS_PLAYING;
			setup[team2]["status"] = STATUS_PLAYING;
		}
		
		if( (game[INNING] % 2) > 0 )
		{	
			attacksetup = setup[team2];
			defendsetup = setup[team1];
			
			attacknumber = game[TEAM2NUMBER];
			defendnumber = game[TEAM1NUMBER];
			
			attacker = team2;
			defender = team1;
		}
		else
		{
			attacksetup = setup[team1];
			defendsetup = setup[team2];
			
			attacknumber = game[TEAM1NUMBER];
			defendnumber = game[TEAM2NUMBER];
			
			attacker = team1;
			defender = team2;
		}

		attackteamname = "��"+attacksetup["name"]+"��";
		defendteamname = "��"+defendsetup["name"]+"��";
		
		if( game[INNING] == 0 )
		{
			string defendhandside, attackhandside;
			
			switch(get_handside_type(defendsetup["roster"][0]["object"]))
			{
				case HANDSIDE_NONE: defendhandside = ""; break;
				case HANDSIDE_LEFTHAND: defendhandside = HIC"��"NOR CYN"Ͷ"NOR; break;
				case HANDSIDE_RIGHTHAND: defendhandside = HIG"��"NOR GRN"Ͷ"NOR; break;
				default: defendhandside = HIR"����"NOR; break;
			}
			switch(get_handside_type(attacksetup["roster"][0]["object"]))
			{
				case HANDSIDE_NONE: attackhandside = ""; break;
				case HANDSIDE_LEFTHAND: attackhandside = HIC"��"NOR CYN"Ͷ"NOR; break;
				case HANDSIDE_RIGHTHAND: attackhandside = HIG"��"NOR GRN"Ͷ"NOR; break;
				default: attackhandside = HIR"����"NOR; break;
			}
			
			msg += ({ attacksetup["username"]+"��"+attackteamname+"��"+defendsetup["username"]+"��"+defendteamname+"������ʽ��ʼ��" });
			msg += ({ "˫���ɳ����ȷ�Ͷ�ֱַ�Ϊ"+attackteamname+attackhandside+attacksetup["roster"][0]["object"]->query_idname()+"��"+defendteamname+defendhandside+defendsetup["roster"][0]["object"]->query_idname()+"��" });
			
			game[INNING]++;
		}
		else
		{
			object pitcher = defendsetup["roster"][0]["object"];
			object batter = attacksetup["roster"][attacknumber]["object"];
			
			string defend_msg="", attack_msg="", info_msg="", *special_msg = allocate(0);
			string pitcherballtype;
			
			int pitcherbase = get_handside_level(pitcher) + pitcher->query_str() * 2;		// Ͷ�ֻ�������(Ԥ����Χ 10~1500 ֮��)
			int batterbase = get_handside_level(batter) + batter->query_str() * 2;			// ���߻�������(Ԥ����Χ 10~1500 ֮��)
			
			string *availableballtypes;
			int pitchballpower;
			int pitchballspeed;
			int pitchswingeffect = 0;
			int pitchhiteffect = 0;
			int pitchgoodhiteffect = 0;
			
			availableballtypes = filter_array(pitch_ball_types, (: $(pitcher)->query_skill_level($1) > 0 :));
			
			
				
			if( sizeof(availableballtypes) )
			{
				string balltype = availableballtypes[random(sizeof(availableballtypes))];
				
				pitchballpower = pitcher->query_skill_level(balltype);
				pitcherballtype = pitch_ball_types_name[balltype];
				
				switch(balltype)
				{
					case "fourseam":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 120, 157) + random(6); 
						pitchswingeffect = -20;
						pitchhiteffect = 10;
						pitchgoodhiteffect = 10;
						break;
					case "twoseam":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 115, 151) + random(6);
						pitchswingeffect = -10;
						pitchhiteffect = 0;
						pitchgoodhiteffect = 10;
						break;
					case "curveball":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 90, 127) + random(6);
						pitchswingeffect = 10;
						pitchhiteffect = -15;
						pitchgoodhiteffect = 5;
						break;
					case "slider":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 110, 148) + random(6);
						pitchswingeffect = -5;
						pitchhiteffect = 10;
						pitchgoodhiteffect = -5;
						break;
					case "forkball":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 100, 137) + random(6);
						pitchswingeffect = 0;
						pitchhiteffect = -10;
						pitchgoodhiteffect = 10;
						break;
					case "sinker":
						pitchballspeed = calculate(pitchballpower, 0.8, 999, 110, 148) + random(6);
						pitchswingeffect = 5;
						pitchhiteffect = 20;
						pitchgoodhiteffect = -25;
						break;
				}
				
				// �������࣬������ǿ
				if( sizeof(availableballtypes) == 1 )
					pitchballpower -= 200;
				else
					pitchballpower += sizeof(availableballtypes) * 30;
			}
			else
			{
				pitchballpower = 0;
				pitcherballtype = "����ֱ��";
				
				pitchballspeed = 100+random(15);
			}
			
			pitchballpower += defendsetup["roster"][0][BUFF_PITCHER_POWER];
			
			if( pitchballpower <= 0 )
				pitchballpower = 0;
				
			pitchballpower = calculate(pitchballpower, 0.8, 999, 0, 100);
			
			if( objectp(find_player(defender)) )
			switch(get_handside_type(pitcher))
			{
				case HANDSIDE_LEFTHAND: pitcher->add_skill_exp("lefthand", random(100)); break;
				case HANDSIDE_RIGHTHAND: pitcher->add_skill_exp("righthand", random(100)); break;
			}
			
			if( objectp(find_player(attacker)) )
			switch(get_handside_type(batter))
			{
				case HANDSIDE_LEFTHAND: batter->add_skill_exp("lefthand", random(900)); break;
				case HANDSIDE_RIGHTHAND: batter->add_skill_exp("righthand", random(900)); break;
				case HANDSIDE_TWOHANDS: batter->add_skill_exp("twohands", random(900)); break;
			}
			
			if( defendsetup["hint"] == HINTTYPE_PITCHER )
			{
				pitchballpower += 70;
				pitchballspeed += range_random(2, 5);
				
				defend_msg = defendteamname+pitcher->query_idname()+HIY"ȫ��"NOR YEL"��ע"NOR+(pitchballspeed>=155?"�":"Ͷ")+"��"+(pitchballspeed>=160?"���˵�":"")+" "+pitchballspeed+"km "+ pitcherballtype;
			}
			else
			{
				defend_msg = defendteamname+pitcher->query_idname()+(pitchballspeed>=155?"�":"Ͷ")+"��"+(pitchballspeed>=160?"���˵�":"")+" "+pitchballspeed+"km "+ pitcherballtype;
			}

			
			attack_msg = attackteamname+attacknumber+" ��"+batter->query_idname();
			
			// ��Զ�Ļ�
			if( defendsetup["hint"] == HINTTYPE_WALK )
			{
				if( ++game[BALL] == 4 )
				{
					defend_msg = defendteamname+pitcher->query_idname()+"��һ��������������֣�"HIG"����"NOR"����������һ������";
					attack_msg += "��þ�Զ�Ļ��������ݡ�";
	
					// ��һ��
					special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
				}
				else
				{
					defend_msg = defendteamname+pitcher->query_idname()+"��һ��������������֣�"HIG"����"NOR"����������һ������";
					attack_msg += "���ĵصȴ��Ļ�����";
	
					info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
				}				
			}
			// ���д����̴�
			else if( attacksetup["hint"] == HINTTYPE_BUNT )
			{
				// ��Ұ����!
				if( random(batter->query_int()) > random(600) )
				{
					attack_msg += "�ڳ���Ϯ�̰��������������һ֧��Ұ���򣡣�";
					
					special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_HIT);
				}
				else if( !random(5) )
				{
					attack_msg += "�ڳ��̰������������ȴ����һ���������򱻽�ɱ��";
					
					info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
					
					special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
				}
				else
				{
					// ����
					if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
					{
						if( game[OUT] < 2 )								
							attack_msg += "�ڳ��̰�����������������߱���ɱ�ڱ��ݣ�";
						else
							attack_msg += "�ڳ��̰����������������Ұ����ס����ɱ��һ�ݣ�";
					}
					else
						attack_msg += "�ڳ��̰����������������Ұ����ס����ɱ��һ�ݣ�";
													
					info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
					
					special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_BUNT);
				}
			}
			// Ͷ������
			else if( calculate(pitcherbase, 0.8, 1500, 400, 700) > random(1000) )
			{
				// ���߾�׼ѡ���ҳ����Ļ��� 550 + (0~100) + (-60~70) - (0~100) + (-20~5)
				int swingchance = 550 + calculate(batter->query_skill_level("hitaccuracy"), 0.8, 999, 0, 100) + get_handside_diff(pitcher, batter) - pitchballpower + pitchswingeffect;
								
				if( attacksetup["hint"] == HINTTYPE_BATTER )
				{
					attack_msg += HIY"ȫ��"NOR YEL"��ע"NOR;
					swingchance += 40;
				}

				defend_msg += HIR"����"NOR"��";

				if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM2] == attacker )
					swingchance += 3 * (game[TEAM1SCORE] - game[TEAM2SCORE]);

				if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM1] == attacker )
					swingchance += 3 * (game[TEAM2SCORE] - game[TEAM1SCORE]);
						
				// �����ҳ���
				if( swingchance > random(1000) )
				{
					// ������Ļ��� 700 + (0~100) - (0~100)
					int hitchance = 700 + calculate(batter->query_skill_level("hitrange"), 0.7, 999, 0, 100) - pitchballpower;
						
					if( attacksetup["hint"] == HINTTYPE_BATTER )
						hitchance += 40;
					
					if( game[INNING] > 18 )
						hitchance += 3 * (game[INNING]/2-9);
								
					hitchance += attacksetup["roster"][attacknumber][BUFF_BATTER_POWER];
		
					switch(attacknumber)
					{
						case 1: hitchance += 50; break;
						case 2: hitchance += 20; break;
						case 3: hitchance += 40; break;
						case 4: hitchance += 80; break;
						case 5: hitchance += 40; break;
						case 6: hitchance += 10;break;
						case 7: hitchance -= 10; break;
						case 8: hitchance -= 10; break;
						case 9: hitchance -= 10; break;
					}
							
					// �����ȥ
					if( hitchance + pitchhiteffect > random(1000) )
					{
						//tell(find_player("clode"), attacker+(hitchance + pitchgoodhiteffect)+"/"+defender+(defendsetup["outfield"]+defendsetup["infield"])+"\n");
						
						// ����
						if( hitchance + pitchgoodhiteffect + 100 > random(800 + defendsetup["outfield"] + defendsetup["infield"] ) )
						{												
							// ��������ٶ�(500~3300)
							int hitpower = batter->query_skill_level("hitpower");
							int ballspeed = 500 + hitpower + batterbase;
							
							ballspeed = calculate(ballspeed, 0.7, 3000, 0, 1000);

							// ȫ�ݴ�
							if( ballspeed > random(8000) )
							{
								int distance;
								
								// ����
								special_msg += new_base(gameindex, attacker, defender, 4, BASETYPE_HIT);
								
								if( hitpower > random(5000) )
								{
									if( hitpower > random(5000) )
									{
										if( hitpower > random(5000) )
											distance = range_random(180, 190);
										else
											distance = range_random(170, 180);
									}
									else
										distance = range_random(160, 170);
										
									attack_msg += "�����һֻ�����"+( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 ? "����" : "" )+"ȫ�ݴ�("+distance+"m)����";
								}
								else
								{
									distance = range_random(140, 160);
									attack_msg += "����"+( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 ? "����" : "" )+"ȫ�ݴ�("+distance+"m)����";
								}
								
								if( distance > record[season_year][RECORD_SPECIAL]["maxhomerundistance"] )
								{
									record[season_year][RECORD_SPECIAL]["maxhomerundistance"] = distance;
									record[season_year][RECORD_SPECIAL]["maxhomerundistanceplayer"] = attacksetup["roster"][attacknumber]["file"];
									
									CHANNEL_D->channel_broadcast("sport", HIY"��¼"NOR YEL"���� "NOR+attackteamname+"��"+batter->query_idname()+"������������ȫ�ݴ򣬾������� "HIY+distance+NOR YEL"m"NOR" ����" );
								}
								
								attack_msg += "("HIY+get_record(RECORD_PLAYER, attacksetup["roster"][attacknumber]["file"], "hit4", season_year)+NOR")";
							}
							// ���ݴ�
							else if( ballspeed > random(10000) )
							{
								// ����
								special_msg += new_base(gameindex, attacker, defender, 3, BASETYPE_HIT);
								
								if( random(defendsetup["outfield"]) < 100 )
									attack_msg += "������Զ������Ұ�ַ���������Ȼ����һ�����γ����ݰ���("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "�������ݰ���("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}
							// ���ݴ�
							else if( ballspeed > random(3000) )
							{
								// ����
								special_msg += new_base(gameindex, attacker, defender, 2, BASETYPE_HIT);
								
								if( random(defendsetup["outfield"]) < 100 )
									attack_msg += "������Ӫ��������Ұ���������٣��γɶ��ݰ���("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "�������ݰ���("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}
							// һ�ݴ�
							else
							{
								// ����
								special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_HIT);
								
								if( random(defendsetup["infield"]) < 100 )
									attack_msg += "�����Ĺ�����Ӳ�Ǵ���Ұ�����д�Խ��ȥ���γ�һ�ݰ���("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
								else
									attack_msg += "����һ�ݰ���("HIG+sprintf("%.2f", get_hit_rate(attacker, attacknumber))+NOR")";
							}								
						}
						// ������
						else if( hitchance > random(5000) )
						{
							if( game[STRIKE] < 2 )
							{
								attack_msg += "���ɽ�����";

								game[STRIKE]++;

								info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
							}
							else
							{
								attack_msg += "���ɽ�����";

								info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
							}
						}
						// �����ȥ���ɱ���ɱ
						else
						{						
							// ����
							if( random(2) )
							{
								attack_msg += "����ԶԶ�����ȥ��������ɱ";
								
								info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
									
								special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
							}
							// ����
							else
							{
								if( !random(15) && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 && game[OUT] == 0 )
								{
									attack_msg += "��������ȥ������һ֧��������ɱ�򣡣�";
									
									info_msg = " "HIW+(game[OUT]+3)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 3, BASETYPE_TRIPLEPLAY);
								}
								else if( random(2) && game[RUNNER3RD] == 0 && game[RUNNER1ST] > 0 && game[OUT] < 2 )
								{
									attack_msg += "��������ȥ������һ֧˫ɱ�򣡣�";
									
									info_msg = " "HIW+(game[OUT]+2)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 2, BASETYPE_DOUBLEPLAY);
								}
								else
								{								
									// ����
									if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
									{
										if( game[OUT] < 2 )								
											attack_msg += "��������ȥ���������߱���ɱ�ڱ��ݣ�";
										else
											attack_msg += "��������ȥ��������Ұ����ס����ɱ��һ�ݣ�";
									}
									else
										attack_msg += "��������ȥ��������Ұ����ס����ɱ��һ�ݣ�";
									
									info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;
									
									special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_TOUCHKILL);
								}
							}
						}

					}
					// �Ӱ����
					else
					{
						if( ++game[STRIKE] == 3 )
						{							
							defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

							attack_msg += "�Ӱ�����⵽�������";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);
						}
						else
						{
							attack_msg += "�Ӱ����";	

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}	
				}
				// ����δ����
				else
				{
					if( ++game[STRIKE] == 3 )
					{					
						defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

						attack_msg += "վ�ŷ����⵽�������";

						info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

						special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);
					}
					else
					{
						attack_msg += "վ�ŷ���";

						info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
					}
				}
			}
			// Ͷ������
			else
			{
				// ���߿�׼�����Ҳ������Ļ��� 750 + (0~100) + (-60~70)
				int swingchance = 750 + calculate(batter->query_skill_level("hitaccuracy"), 0.8, 999, 0, 100) + get_handside_diff(pitcher, batter) + pitchswingeffect;

				if( setup[attacker]["hint"] == HINTTYPE_BATTER )
				{
					attack_msg += HIY"ȫ��"NOR YEL"��ע"NOR;
					swingchance += 50;
				}

				if( game[TEAM1SCORE] > game[TEAM2SCORE] && game[TEAM2] == attacker )
					swingchance += 3 * (game[TEAM1SCORE] - game[TEAM2SCORE]);

				if( game[TEAM2SCORE] > game[TEAM1SCORE] && game[TEAM1] == attacker )
					swingchance += 3 * (game[TEAM2SCORE] - game[TEAM1SCORE]);

				defend_msg += HIG"����"NOR"��";

				// ������û����
				if( swingchance > random(1000) )
				{
					if( random(200 + pitcherbase) < 5 )
					{
							attack_msg += "����Ͷ����У���ô���������";

							// ��һ��
							special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
					}
					else
					{
						if( ++game[BALL] == 4 )
						{
							attack_msg += "��סû�лӰ�����ñ�������";

							// ��һ��
							special_msg += new_base(gameindex, attacker, defender, 1, BASETYPE_BALL);
						}
						else
						{
							attack_msg += "��סû�лӰ�";

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}
				}
				// �����г���
				else
				{
					if( 200 + pitchballpower > random(800) )
					{
						if( ++game[STRIKE] == 3 )
						{						
							defender == game[TEAM1] ? game[TEAM1K]++ : game[TEAM2K]++;

							attack_msg += "�Ӱ�����⵽�������";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out "HIY + (defender == game[TEAM1] ? game[TEAM1K] : game[TEAM2K]) +NOR YEL"K!"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_STRIKEOUT);	
						}
						else
						{
							attack_msg += "����һ�ӣ��Ӱ����";

							info_msg = " "HIR+game[STRIKE]+NOR" "HIG+game[BALL]+" "HIW+game[OUT]+NOR;
						}
					}
					else
					{
						// ����
						if( random(2) )
						{						
							attack_msg += "����ԶԶ�����ȥ��������ɱ";

							info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;

							special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_CATCHKILL);
						}
						// ����
						else
						{
							if( !random(15) && game[RUNNER2ND] > 0 && game[RUNNER1ST] > 0 && game[OUT] == 0 )
							{
								attack_msg += "��������ȥ������һ֧��������ɱ�򣡣�";

								info_msg = " "HIW+(game[OUT]+3)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 3, BASETYPE_TRIPLEPLAY);
							}
							else if( random(2) && game[RUNNER3RD] == 0 && game[RUNNER1ST] > 0 && game[OUT] <= 1 )
							{
								attack_msg += "��������ȥ������һ֧˫ɱ�򣡣�";

								info_msg = " "HIW+(game[OUT]+2)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 2, BASETYPE_DOUBLEPLAY);
							}
							else
							{
								// ����
								if( game[RUNNER1ST] > 0 && game[RUNNER2ND] > 0 && game[RUNNER3RD] > 0 )
								{
									if( game[OUT] < 2 )								
										attack_msg += "��������ȥ���������߱���ɱ�ڱ��ݣ�";
									else
										attack_msg += "��������ȥ��������Ұ����ס����ɱ��һ�ݣ�";
								}
								else
									attack_msg += "��������ȥ��������Ұ����ס����ɱ��һ�ݣ�";

								info_msg = " "HIW+(game[OUT]+1)+NOR WHT"out"NOR;

								special_msg += new_out(gameindex, attacker, defender, 1, BASETYPE_TOUCHKILL);
							}
						}
					}
				}
			}

			if( !game ) continue;

			msg += ({ defend_msg+attack_msg+info_msg });
			
			if( sizeof(special_msg) > 0 )
				msg += special_msg;
		}

		if( sizeof(attacksetup["messages"]) )
		{
			msg = attacksetup["messages"] + msg;
			attacksetup["messages"] = 0;
		}

		if( sizeof(defendsetup["messages"]) )
		{
			msg = defendsetup["messages"] + msg;
			defendsetup["messages"] = 0;
		}
				
		if( sizeof(msg) )
		{
			foreach(string m in msg)
			{
				broadcast(m, game);
			}
		}
	}
}

// ������׼����ʼ, ǰ��Ϊ����, ����Ϊ�ͳ�
void new_game(string id1, string id2)
{
	mapping game = allocate_mapping(0);
	object user;
	
	game[TEAM1] = id1;
	game[TEAM2] = id2;
	game[TEAM1NUMBER] = 1;
	game[TEAM2NUMBER] = 1;
	
	if( post_season_start && post_season_level )
	{
		if( objectp(find_player(id1)) )
			tell(find_player(id1), "\a");
		
		if( objectp(find_player(id2)) )
			tell(find_player(id2), "\a");
			
		game[TICK] = PREPARETIME*4/5 - random(POSTSEASON_TICKTIME);
		
	}
	else
		game[TICK] = random(TICKTIME);

	games += ({ game });

	setup[id1]["status"] = STATUS_PREPARING;
	setup[id2]["status"] = STATUS_PREPARING;

	if( post_season_start && post_season_level )
	{
		setup[id1]["hinttimes"] = HINTTIMES * 2;
		setup[id2]["hinttimes"] = HINTTIMES * 2;
	}
	else
	{
		setup[id1]["hinttimes"] = HINTTIMES;
		setup[id2]["hinttimes"] = HINTTIMES;
	}

	setup[id1]["opponents"] -= ({ id2 });
	setup[id2]["opponents"] -= ({ id1 });
	
	if( objectp(user = find_player(id1)) )
		tell(user, pnoun(2, user)+"�İ�����鼴����"+setup[id2]["username"]+"�ġ�"+setup[id2]["name"]+"�����б�����\n");
	
	if( objectp(user = find_player(id2)) )
		tell(user, pnoun(2, user)+"�İ�����鼴����"+setup[id1]["username"]+"�ġ�"+setup[id1]["name"]+"�����б�����\n");
}

void start_game(string id)
{
	foreach(mapping ref game in games)
	{
		if( game[TEAM1] == id || game[TEAM2] == id )
		{
			if( game[TICK] < PREPARETIME )
				game[TICK] = PREPARETIME - 1 - random(TICKTIME);
		}
	}
}

string query_opponent(string id)
{
	foreach(mapping game in games)
	{
		if( !mapp(game) ) continue;

		if( game[TEAM1] == id )
			return game[TEAM2];
		if( game[TEAM2] == id )
			return game[TEAM1];
	}
	
	return 0;
}

varargs mixed query_game(string id)
{
	if( undefinedp(id) ) 
		return games;

	foreach(mapping game in games)
	{
		if( !mapp(game) ) continue;

		if( game[TEAM1] == id || game[TEAM2] == id )
			return game;
	}
	
	return 0;
}

string *query_season()
{
	return season;
}

varargs mapping query_setup(string id)
{
	if( undefinedp(id) )
		return setup;
	else
	{
		// ��ʼ���趨
		if( undefinedp(setup[id]) )
		{
			setup[id] = allocate_mapping(0);
			setup[id]["listener"] = ({ id });
			setup[id]["roster"] = allocate(10);
		}

		return setup[id];
	}
}

int exists(string id)
{
	return !undefinedp(setup[id]);
}

// �����趨������ӵĶ���
void reset_all_opponents()
{
	foreach(string id, mapping data in setup)
		setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });	
}

int is_playing(object labor)
{
	string id = query("boss", labor);
	string file = base_name(labor);

	if( undefinedp(setup[id]) ) return 0;

	if( setup[id]["status"] != STATUS_PLAYING ) return 0;

	for(int i=0;i<10;++i)
		if( setup[id]["roster"][i]["file"] == file )
			return 1;

	return 0;
}

mapping query_record()
{
	return record;
}

// ������ʽ
void heart_beat()
{
	int *realtime = TIME_D->query_realtime_array();

	if( !(++tick % 1855) ) save();

	if( !post_season_start && realtime[WDAY] == 0 && realtime[HOUR] == 14 )
	{
		CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ֹͣ������ԣ�Ŀǰ���ڽ��еı���ȫ��������� "HIC+season_year+NOR" �򼾼�����������ʼ��");
		post_season_start = 1;	
	}
	
	if( !(tick%10) )
	{
		if( post_season_start )
		{		
			// ���б���������
			if( sizeof(games) ) return;
			
			switch(post_season_level)
			{
				// ��ʼ������
				case 0:
				{
					post_season_team_8 = sort_array(filter_array(season, (: valid_setup($1, 1) :)), (: sort_team($1, $2) :))[0..7];
					post_season_team_4 = allocate(0);
					post_season_team_2 = allocate(0);
					post_season_eliminate_teams = allocate(0);

					// ���������鲻�� 8 ��
					if( sizeof(post_season_team_8) != 8 )
					{
						if( realtime[WDAY] == 0 && realtime[HOUR] == 20 )
						{
							CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���������鲻���֧��ӣ�����˴μ�����ȡ����");
							post_season_level = 8;
						}
						return;
					}
					
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" �������漾���Ѿ�����������ѡ������ʤ����ߵ�ǰ��ǿ������м�������");
					
					for(int i=0;i<sizeof(post_season_team_8);++i)
					{
						if( objectp(find_player(post_season_team_8[i])) )
							tell(find_player(post_season_team_8[i]), "\a");

						CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" "NOR YEL"��"HIY+(i+1)+NOR YEL"��"NOR"����"+setup[post_season_team_8[i]]["name"]+"������"+setup[post_season_team_8[i]]["username"]+"�����");
					}
		
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���ϰ˶Ӿ��ý��μӱ��򼾵����վ�������ȡ����������ҫ��"HIY"��"NOR YEL"��"HIY"��"NOR YEL"��"NOR"����");
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" �������������½�һս��ʤ�����ܹ� 7 �����������˶�Ƶ��ȫ����ͬ��ʵ��ת����");
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" �������ı��������н���ӵ�� 2 ���İ���ʹ�ô�����ͬʱ��ӵ�� 20 ����Ʊ�����롣");
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���Ƚ��� "HIC"A ���ǿ��"NOR"���������� 1 �ġ�"+setup[post_season_team_8[0]]["name"]+"������������ 8 �ġ�"+setup[post_season_team_8[7]]["name"]+"������������ 2 ���Ӻ�ʼ��");
				
					post_season_level++;
					new_game(post_season_team_8[0], post_season_team_8[7]);
					
					break;
				}
				case 1:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���Ž��� "HIC"B ���ǿ��"NOR"���������� 2 �ġ�"+setup[post_season_team_8[1]]["name"]+"������������ 7 �ġ�"+setup[post_season_team_8[6]]["name"]+"������������ 2 ���Ӻ�ʼ��");
					
					post_season_level++;
					new_game(post_season_team_8[1], post_season_team_8[6]);
					
					break;
				}
				case 2:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���Ž��� "HIC"C ���ǿ��"NOR"���������� 3 �ġ�"+setup[post_season_team_8[2]]["name"]+"������������ 6 �ġ�"+setup[post_season_team_8[5]]["name"]+"������������ 2 ���Ӻ�ʼ��");
					
					post_season_level++;
					new_game(post_season_team_8[2], post_season_team_8[5]);
					
					break;
				}
				case 3:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���Ž��� "HIC"D ���ǿ��"NOR"���������� 4 �ġ�"+setup[post_season_team_8[3]]["name"]+"������������ 5 �ġ�"+setup[post_season_team_8[4]]["name"]+"������������ 2 ���Ӻ�ʼ��");
					
					post_season_level++;
					new_game(post_season_team_8[3], post_season_team_8[4]);
					
					break;
				}
				case 4:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���Ž���"HIY"��ǿ׼����"NOR"���� A ��������顰"+setup[post_season_team_4[0]]["name"]+"������ D ��������顰"+setup[post_season_team_4[3]]["name"]+"������������ 2 ���Ӻ�ʼ��");
					
					post_season_level++;
					new_game(post_season_team_4[0], post_season_team_4[3]);
					
					break;
				}
				case 5:
				{
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���Ž���"HIY"��ǿ׼����"NOR"���� B ��������顰"+setup[post_season_team_4[1]]["name"]+"������ C ��������顰"+setup[post_season_team_4[2]]["name"]+"������������ 2 ���Ӻ�ʼ��");
					
					post_season_level++;
					new_game(post_season_team_4[1], post_season_team_4[2]);
					
					break;
				}
				case 6:
				{
				CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" ���Ž��е� "HIC+season_year+NOR" ��"HIY"��"NOR YEL"�ھ���"NOR"���ǡ�"+setup[post_season_team_2[0]]["name"]+"�����ϡ�"+setup[post_season_team_2[1]]["name"]+"������������ 2 ���Ӻ�ʼ��");
					
					post_season_level++;
					new_game(post_season_team_2[0], post_season_team_2[1]);
					
					break;
				}
				case 7:
				{
					post_season_level++;
					CHANNEL_D->channel_broadcast("sport", HIR"����"NOR RED"��"NOR" �������м����뼾�����Ѿ�ȫ��������������һ�����ټ�����");
					break;
				}
				case 8:
				{
					post_season_level = 0;
					post_season_start = 0;
					season_year++;
					
					CHANNEL_D->channel_broadcast("sport", HIG"ȫ��"NOR GRN"��"NOR" �µĵ� "HIC+season_year+NOR" �򼾿�ʼ�����в�����ӿ�ʼ���б�����ԡ�");
					
					post_season_team_8 = allocate(0);
					post_season_team_4 = allocate(0);
					post_season_team_2 = allocate(0);
					post_season_eliminate_teams = allocate(0);
					
					record[season_year] = allocate_mapping(0);
					record[season_year][RECORD_TEAM] = allocate_mapping(0);
					record[season_year][RECORD_PLAYER] = allocate_mapping(0);
					record[season_year][RECORD_SPECIAL] = allocate_mapping(0);
		
					reset_all_opponents();
					
					foreach(string id in season)
					{
						setup[id]["keepwins"] = 0;
						setup[id]["keeploses"] = 0;
					}	
			
					save();
					break;	
				}
			}
		}
		else
		{
			// ����������
			foreach(string id in season)
			{
				if( undefinedp(setup[id]) ) continue;
		
				// Ѱ�Ҷ��֣��µı���׼����ʼ
				if(setup[id]["status"] == STATUS_IDLE )
				{
					string opponent_id = 0;
		
					// ����趨����ȡ�����
					if( !valid_setup(id, 1) )
					{
						leave_season(id);
						continue;
					}
		
					// �����޶��֣������б�
					if( !sizeof(setup[id]["opponents"]) )
						setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });
		
					// ��ѰĿǰû�б����Ķ���
					foreach(string teamid in setup[id]["opponents"])
					{
						if( setup[teamid]["status"] == STATUS_IDLE )
						{
							if( !valid_setup(teamid, 1) )
							{
								leave_season(teamid);
								continue;
							}
		
							opponent_id = teamid;
							break;
						}
					}
		
					// �Ҳ������֣��ȴ��´� heartbeat ��������Ѱ
					if( !stringp(opponent_id) )
					{
						// ���� 180 ��(40min)�Ҳ������֣������б�
						if( ++setup[id]["no_opponent"] > 240 )
						{
							setup[id]["no_opponent"] = 0;
							setup[id]["opponents"] = copy(sort_array(season, (: random(2) ? 1 : -1 :))) - ({ id });
						}
						continue;
					}
		
					setup[id]["no_opponent"] = 0;
					setup[opponent_id]["no_opponent"] = 0;
					
					// ����������ͳ�
					if( !random(2) )
					{
						//CHANNEL_D->channel_broadcast("sport", HIC+"����"NOR CYN"��� "NOR+setup[id]["username"]+"�ġ�"+setup[id]["name"]+"����"+setup[opponent_id]["username"]+"�ġ�"+setup[opponent_id]["name"]+"������ "+(PREPARETIME/60)+" ���Ӻ����������");
						new_game(id, opponent_id);
					}
					else
					{
						//CHANNEL_D->channel_broadcast("sport", HIC+"����"NOR CYN"��� "NOR+setup[opponent_id]["username"]+"�ġ�"+setup[opponent_id]["name"]+"����"+setup[id]["username"]+"�ġ�"+setup[id]["name"]+"������ "+(PREPARETIME/60)+" ���Ӻ����������");
						new_game(opponent_id, id);
					}
				}
			}
		}
	}
	play_game();
}

// �л���ʱս��
void set_listener(string listener_id, string target_team)
{	
	if( !stringp(target_team) )
	{
		foreach(string team, mapping data in setup)
			setup[team]["listener"] -= ({ listener_id });
	}
	else
	{
		setup[target_team]["listener"] |= ({ listener_id });
	}
}

int remove()
{
	return save();
}

void fix_setup()
{
	/*
	foreach(string id, mapping data in setup)
	{

	}
*/
	save();
}

void fix_record()
{

}

int query_season_year()
{
	return season_year;	
}

int is_in_post_season()
{
	return post_season_start && post_season_level;	
}

string *query_post_season_team(int number)
{
	switch(number)
	{
		case 8:
			return post_season_team_8;
			break;
		case 4:
			return post_season_team_4;
			break;
		case 2:
			return post_season_team_2;
			break;
	}
}

string *query_post_season_eliminate_teams()
{
	return post_season_eliminate_teams;
}

void add_message(string id, string message)
{
	if( undefinedp(setup[id]) ) return;	
	
	if( !arrayp(setup[id]["messages"]) )
		setup[id]["messages"] = ({ message });
	else
		setup[id]["messages"] += ({ message });
}

void create()
{
	backup();
	
	if( !restore_object(DATA) )
	{
		setup = allocate_mapping(0);
		season = allocate(0);
		games = allocate(0);
		record = allocate_mapping(0);
		
		save();
	}

	set_heart_beat(1);
}

string query_name()
{
	return "����ϵͳ(BASEBALL_D)";
}
