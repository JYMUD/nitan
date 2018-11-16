// giftd.c

#include <ansi.h>
#include <quest.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

// �����ṩ���ⲿ���õĽӿں���
varargs public void bonus(object who, mapping b, int flag);
varargs public void freequest_bonus(object who);
varargs public void gift_bonus(object who, mapping b);
varargs public void work_bonus(object who, mapping b);
varargs public void war_bonus(object who, mapping b);
varargs public void battle_bonus(object who, mapping b);
public void delay_bonus(object who, mapping b);
public void delay_freequest_bonus(object who);
public void delay_gift_bonus(object who, mapping b);
public void delay_work_bonus(object who, mapping b);
public void delay_war_bonus(object who, mapping b);
public void delay_battle_bonus(object who, mapping b);

void create()
{
        seteuid(getuid());
        set("channel_id", "��������");
}

// override set function
varargs mixed set(string idx, mixed para, object who)
{
        int i, n, now_lvl, old_lvl;

        if( idx == "combat_exp" )
        {
                if( para > query("combat_exp", who) )
                {
                        old_lvl = query("level", who);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        // �ȼ���ӡ
                        if( !UPDATE_D->can_improve_level(old_lvl) &&
                            para > to_int(pow(old_lvl, 3.0)*10000) )
                        {
                                //tell_object(ob, HIR "�����㴦�ڵȼ���ӡ�У����ʵս�����޷�������\n" NOR);
                                return;
                        }

                        for (i = old_lvl; ;i++)
                        {
                                if( to_int(pow(i+1, 3)) > (para / 10000) )
                                {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = now_lvl - old_lvl;
                                efun::set("level", now_lvl, who);

                                addn("ability", 4 * n, who);
                                addn("experience", 20 * n, who);
                                addn("potential", 200 * n, who);
                                addn("magic_points", 20 * n, who);

                                tell_object(who, HIY "ֻ��һ�����ɽ�������ڣ��������ȼ������ˣ�\n" +
                                        "�˴�������������" + chinese_number(4 * n) +
                                        "�������㡢" + chinese_number(200 * n) +
                                        "��Ǳ�ܡ�" + chinese_number(20 * n) +
                                        "��ʵս��ᡢ" + chinese_number(20 * n) +
                                        "����ۣ�\n" NOR);

                                UPDATE_D->improve_valid_level(who, now_lvl); 
                        }
                }
        } else
        if( idx == "xiantian_zhengqi" )
        {
        } else
        if( idx == "yuanshen_exp" )
        {
                if( para > query("yuanshen_exp", who) )
                {
                        old_lvl = query("yuanshen_level", who);
                        if( !old_lvl || old_lvl < 1 ) old_lvl = 1;

                        for (i = old_lvl; ;i++)
                        {
                                if( to_int(pow(i+1, 3)) > (para / 100000) )
                                {
                                        now_lvl = i;
                                        break;
                                }
                        }

                        if( now_lvl > old_lvl )
                        {
                                n = now_lvl - old_lvl;
                                efun::set("yuanshen_level", now_lvl, who);

                                addn("yuanshen/attack", n, who);
                                addn("yuanshen/defense", n, who);
                                addn("yuanshen/damage", n, who);
                                addn("yuanshen/armor", n, who);

                                tell_object(who, HIY "ֻ��һ�����ɽ�������ڣ����Ԫ��ȼ������ˣ�\n" NOR);
                        }
                }
        }
        return efun::set(idx, para, who);
}

varargs mixed add(string prop, mixed data, object who)
{
        string para;
        int old;
        int level;

        if( prop == "combat_exp" )
        {
                if( !(old = query(prop, who)) )
                        return set(prop, data, who);

                if( data < 1 )
                        return efun::set(prop, old + data, who);

                level = query("level", who);
                if( !level || level < 1 ) level = 1;
                if( !UPDATE_D->can_improve_level(level) &&
                    old > to_int(pow(level, 3.0)*10000) )
                        return;

                return set(prop, old + data, who);
        } else
        if( prop == "xiantian_zhengqi" ) 
        {
        } else 
        if( prop == "yuanshen_exp" )
        {
                if( !(old = query(prop, who)) )
                        return set(prop, data, who);

                if( data < 1 )
                        return efun::set(prop, old + data, who);
        } else
                return efun::addn(prop, data, who);
}

// �ӳٽ�������Ϊ��ʱ����������ʱ��Ӧ������ĳЩ�¼������Ժ�
// �����ڸ��¼�����ʱ���뽱����������д�������Խ������ɵ�
// �ط����¼����ڷ�����ʱ�򣬵���Ҫ����ҿ����������¼�����
// �Ժ󡣱���ɱ�ˣ���������ʱ����뽱�����������ģ�������ϣ
// ������ڿ���NPC ��������Ϣ�Ժ�ſ�����������Ϣ����ʱ���
// ��delay_bonus�ˡ�

public void delay_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "bonus", who, b :), 1);
}

public void delay_work_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "work_bonus", who, b :), 1);
}

public void delay_freequest_bonus(object who)
{
        who->start_call_out((: call_other, __FILE__,
                               "freequest_bonus", who :), 3);
}

public void delay_gift_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "gift_bonus", who, b :), 1);
}

public void delay_war_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "war_bonus", who, b :), 1);
}

public void delay_fuben_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "fuben_bonus", who, b :), 1);
}

public void delay_boss_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "boss_bonus", who, b :), 1);
}

void special_bonus(object me, object who, mixed arg)
{
        // �������
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/xuantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
                "/clone/tessera/metal",
                "/clone/tessera/wood",
                "/clone/tessera/water",
                "/clone/tessera/fire",
                "/clone/tessera/earth",
                "/clone/goods/forging-stone",
        });

        object ob;

        /*
        message_vision("$n��$N΢΢һЦ�������ɵò���������"
                       "�ˣ������������е㶫���������ȥ�ɡ�\n",
                       who, me);
        */

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(who, 1);
        tell_object(who, HIM "������һ" + query("unit", ob) + ob->name() +
                        HIM "��\n" NOR);
}

// ��������Ľ���
varargs public void bonus(object who, mapping b, int flag)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int shen;               // ��������
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int gold;
        int pot_limit;          // Ǳ�ܵĽ���
        int mar_limit;          // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("quest_reward");

        // ��ý����İٷֱ�
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // ��Ҿ���̫�ߣ�����������
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
                                                        
        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                              
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        // Ԫ��
        if( exp > 100 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ������ʾ��Ϣ
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "��������";
        else
                msg = HIG "ͨ����ζ�����������";

        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
        if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������";
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��";
        if (score > 0) msg += chinese_number(score) + "�㽭��������";
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������";
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";
        if (gold > 0) msg += chinese_number(gold) + "���ƽ�";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
	{
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
        }

        msg += "�����õ���������\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// ��ͨ��������Ľ���
varargs public void work_bonus(object who, mapping b, int flag, string type/*��������,Ϊ�����Ԥ���ӿ�*/)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int shen;               // ��������
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int gold;
        int pot_limit;          // Ǳ�ܵĽ���
        int mar_limit;          // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("work_reward");

        // ��ý����İٷֱ�
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;

        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // ��Ҿ���̫�ߣ�����������
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
        
        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;                
        /*
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }
        */

        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ������ʾ��Ϣ
        if (stringp(msg = b["prompt"]))
                msg = HIC "\n" + msg + HIC "��������";
        else
                msg = HIC "\nͨ����ζ�����������";

        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
        if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������";
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��";
        if (score > 0) msg += chinese_number(score) + "�㽭��������";
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������";
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";
        if (gold > 0) msg += chinese_number(gold) + "���ƽ�";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
	{
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
        }

        msg += "�����õ���������\n\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// �ж�������������Ľ���
varargs public void freequest_bonus(object who)
{
        object gift;
        int quest;              // ��ǰ��������
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("quest_reward");

        quest=query("quest_count", who);
        quest *= 10;
        exp = quest + random(quest) + 5000;

        // ��Ϊ��ý����϶����޷��ۼ��ж�����������ʱ����
        // ���޵����ơ�
        pot = exp / 3;
        mar = random(quest / 2) + 500;

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;   
                             
        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }
        
        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        msg = HIC "\n������ε����������У�����ѧ�ƺ���"
              "�����µ�ͻ�ơ�������" +
              chinese_number(exp) + "�㾭�顢" +
              chinese_number(pot) + "��Ǳ�ܡ�" +
              chinese_number(mar) + "��ʵս��ᡢ";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
	{
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡣";
        }

        msg += "�����õ���������\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("quest/freequest", -1, who);

        if (query("quest/freequest", who) < 1)
        {
                delete("quest", who);
                message_sort(HIW "\n������ʱ��ֻ��һλ" +
                             query("family/family_name", who)+
                             "���Ӽ���ææ�ϵ�$N" HIW "��ߣ�˵"
                             "������ԭ���������ﰡ��ʦ����������"
                             "�������ء���˵��Ҫ���½�����죬��"
                             "�Ͽ��ȥ�ɣ����������ʦ������ת��"
                             "����ġ���\n" NOR, who);

                message_sort("\n"+query("family/family_name", who)+
                             "�����ó�һ�������ݸ�$N��\n\n" +
                             query("family/family_name", who)+
                             "���Ӽ���ææ���뿪�ˡ�\n" NOR, who);

                gift = new("/clone/misc/bag");
                gift->move(who, 1);
        }
}

// �����¼��Ľ���
varargs public void gift_bonus(object who, mapping b)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        string temp;            // ���̼�¼��Ϣ
        int quest_times;
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;

        // ��ý����İٷֱ�
        percent = b["percent"];

        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        // ���̼�¼����Ե�һ������н��������
        temp = b["temp"];

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;                
       // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ����ҥ����Ϣ
        if (stringp(msg = b["rumor"]))
        {
                shout(HIR "�����ִ��š�" NOR + WHT "��˵" +
                      who->name()+WHT"["+query("id", who)+
                      WHT "]" + msg + WHT "��\n" NOR);
        }

        if( !stringp(temp) || !query(temp, who) )
        {
                // ������ʾ��Ϣ
                if (stringp(msg = b["prompt"]))
                        msg = HIW "\n" + msg + HIW "��������";
                else
                        msg = HIW "\nͨ���˴ξ�����������";

                // ��¼�½���
                if (stringp(temp))
                        addn(temp, 1, who);

                if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
                if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
                if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
                if (score > 0) msg += chinese_number(score) + "�㽭��������";
                if (weiwang > 0) msg += chinese_number(weiwang) + "�㽭��������";
                if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";

                if( ob )
	        {
	                msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
                }

                if( query("yuanshen", who) )
	        {
	                msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
                }
                msg += "�����õ���������\n" NOR;
                tell_object(who, sort_msg(msg));

                // bonus
                add("combat_exp", exp, who);
                addn("potential", pot, who);
                addn("experience", mar, who);
                addn("score", score, who);
                addn("weiwang", weiwang, who);
                addn("family/gongji", gongxian, who);
        }
}

varargs public void war_bonus(object who, mapping b)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int shen;               // ��������
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int gold;
        int pot_limit;          // Ǳ�ܵĽ���
        int mar_limit;          // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = ACTION_D->query_action("battle_reward");

        // ��ý����İٷֱ�
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        // ת����������Ƚ��ͣ�ת����������Ϊ��������Ӧ����
        if( query("reborn/times", who) ) percent /= 4; 
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // ��Ҿ���̫�ߣ�����������
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                                
        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ������ʾ��Ϣ
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "��������";
        else
                msg = HIG "ͨ����ζ�����������";

        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
        if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������";
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��";
        if (score > 0) msg += chinese_number(score) + "�㽭��������";
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������";
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";
        if (gold > 0) msg += chinese_number(gold) + "���ƽ�";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
        {
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
        }

        msg += "�����õ���������\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// BOSS����Ľ���
varargs public void boss_bonus(object who, mapping b, int flag)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int shen;               // ��������
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int gold;
        int pot_limit;          // Ǳ�ܵĽ���
        int mar_limit;          // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("boss_reward");

        // ��ý����İٷֱ�
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // ��Ҿ���̫�ߣ�����������
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
        
        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                                
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ������ʾ��Ϣ
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "��������";
        else
                msg = HIG "ͨ����ζ�����������";

        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
        if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������";
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��";
        if (score > 0) msg += chinese_number(score) + "�㽭��������";
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������";
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";
        if (gold > 0) msg += chinese_number(gold) + "���ƽ�";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
        {
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
        }

        msg += "�����õ���������\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// ��������Ľ���
varargs public void fuben_bonus(object who, mapping b, int flag)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int shen;               // ��������
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int gold;
        int pot_limit;          // Ǳ�ܵĽ���
        int mar_limit;          // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = "/adm/daemons/actiond"->query_action("fuben_reward");

        // ��ý����İٷֱ�
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // ��Ҿ���̫�ߣ�����������
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                                
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ������ʾ��Ϣ
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "��������";
        else
                msg = HIG "ͨ����ζ�����������";

        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
        if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������";
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��";
        if (score > 0) msg += chinese_number(score) + "�㽭��������";
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������";
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";
        if (gold > 0) msg += chinese_number(gold) + "���ƽ�";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
        {
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
        }

        msg += "�����õ���������\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

varargs public void battle_bonus(object who, mapping b)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int shen;               // ��������
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int gold;
        int pot_limit;          // Ǳ�ܵĽ���
        int mar_limit;          // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times = ACTION_D->query_action("battle_reward");

        // ��ý����İٷֱ�
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // ��Ҿ���̫�ߣ�����������
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (quest_times)
        {
                exp *= quest_times;
                pot *= quest_times;
                mar *= quest_times;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;

        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;                
        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        if( exp > 10 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ������ʾ��Ϣ
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "��������";
        else
                msg = HIG "ͨ����ζ�����������";

        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
        if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������";
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��";
        if (score > 0) msg += chinese_number(score) + "�㽭��������";
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������";
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";
        if (gold > 0) msg += chinese_number(gold) + "���ƽ�";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
        {
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
        }

        msg += "�����õ���������\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}

// ��Ľ���
varargs public void event_bonus(object who, mapping b, int flag)
{
        int exp;                // �����ľ���
        int pot;                // ������Ǳ��
        int mar;                // ������ʵս���
        int shen;               // ��������
        int score;              // �����Ľ�������
        int weiwang;            // �����Ľ�������
        int gongxian;           // ���������ɹ���
        int gold;
        int pot_limit;          // Ǳ�ܵĽ���
        int mar_limit;          // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ�
        string msg;             // ������������Ϣ
        int yuanshen_exp;
        int warcraft_exp;
        object ob;
        int rate;
        int quest_times;
        int event;

        // ��ý����İٷֱ�
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;
        
        if( query("reborn/times", who) ) percent /= 2;
        
        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;
        gongxian = b["gongxian"] * percent / 100;
        gold = b["gold"] * percent / 100;

        // ��Ҿ���̫�ߣ�����������
        /*
        if( query("combat_exp", who) >= 2160000000 )
        {
                exp /= 3;
                pot /= 3;
                mar /= 3;
        } else
        if( query("combat_exp", who) >= 1250000000 )
        {
                exp /= 2;
                pot /= 2;
                mar /= 2;
        } else
        if( query("combat_exp", who) >= 640000000 )
        {
                exp = exp*2/3;
                pot = exp*2/3;
                mar = exp*2/3;
        }
        */

#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(who))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif
        event = ACTION_D->query_action("event_reward");
        if (event)
        {
                exp *= event;
                pot *= event;
                mar *= event;
        }

        if( quest_times=query_temp("apply/add_reward", who) )
        {
                if( query("reborn/times", who) && !event ) quest_times /= 3;
                if( quest_times > 100 ) quest_times = 100;
                exp += exp*range_random(quest_times/2,quest_times)/100;
                pot += pot*range_random(quest_times/2,quest_times)/100;
                mar += mar*range_random(quest_times/2,quest_times)/100;
        }

        if( quest_times=query_temp("apply/add_exp", who) )
        {
                if( query("reborn/times", who) && !event ) quest_times /= 3;
                if( quest_times > 200 ) quest_times = 200;
                exp += exp*random(quest_times)/100;
        }
        
        if( quest_times=query_temp("apply/add_pot", who) )
                pot += pot*random(quest_times)/100;

        if( quest_times=query_temp("apply/add_mar", who) )
                mar += mar*random(quest_times)/100;
                                                        
        // ����������
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "exp") )
                exp *= 2;        
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "pot") )
                pot *= 2;
        if( who->query_bunch() && BUNCH_D->query_bunch_efficient(who->query_bunch(), "mar") )
                mar *= 2;

        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "exp") )
                exp *= 2;        
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "pot") )
                pot *= 2;
        if( who->query_family() && FAMILY_D->query_family_efficient(who->query_family(), "mar") )
                mar *= 2;
                              
        if (! flag)
        {
                pot_limit=who->query_potential_limit()-query("potential", who);
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit=who->query_experience_limit()-query("experience", who);
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if( who->query_potential_limit()<query("potential", who) )
                        pot = 1 + random(2);

                if( who->query_experience_limit()<query("experience", who) )
                        mar = 1;
        }

        // ħ����
        if( exp > 100 && intp(rate = query("env/share_exp", who)) &&
            query("warcraft/file", who) && objectp(ob=find_object(query("warcraft/file", who))) )
        {
                if( rate < 0 ) rate = 0;
                if( rate > 100 ) rate = 100;
                warcraft_exp = exp * rate/100 + 1;
                ob->add("combat_exp", warcraft_exp);
                exp -= warcraft_exp;
        }

        // Ԫ��
        if( exp > 100 && query("yuanshen", who) )
        {
                yuanshen_exp = exp / 4 + 1;
                add("yuanshen_exp", yuanshen_exp, who);
                exp -= yuanshen_exp;
        }

        // ������ʾ��Ϣ
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "��������";
        else
                msg = HIG "ͨ����ζ�����������";

        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢";
        if (pot > 0) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (mar > 0) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������";
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��";
        if (score > 0) msg += chinese_number(score) + "�㽭��������";
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������";
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����";
        if (gold > 0) msg += chinese_number(gold) + "���ƽ�";

        if( ob )
	{
	        msg += ob->name() + "��þ���" + chinese_number(warcraft_exp) + "�㡢";
        }

        if( query("yuanshen", who) )
	{
	        msg += "Ԫ���þ���" + chinese_number(yuanshen_exp) + "�㡢";
        }

        msg += "�����õ���������\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        add("combat_exp", exp, who);
        addn("potential", pot, who);
        addn("experience", mar, who);
        addn("shen", shen, who);
        addn("score", score, who);
        addn("weiwang", weiwang, who);
        addn("family/gongji", gongxian, who);
        addn("balance", gold*10000, who);
}
