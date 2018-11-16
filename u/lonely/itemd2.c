// itemd.c
// updated by Rcwiz 2006.03.14

#pragma optimize

#pragma save_binary


#include <ansi.h>
#include <command.h>

#define GIFT_POINT   1

void create() { seteuid(getuid()); }
void reduce_consistence(object item, object me, object victim, int damage);

// ���ر���Ʒ����
// 1 Ϊ������2 Ϊ˫��
int gift_point(){ return GIFT_POINT; }

// ���������ڹ��ӳɵ㼰�����ӳɵ�
// 1 Ϊ�ڹ��ӳ� �� 2Ϊ�����ӳ�
int neck_add_damage(object me, int k)
{
		mapping neck_enlist = ([
			"����ʯ"     :     ({ 5, 10 }),
			"�챦ʯ"     :     ({ 10, 5 }),
			"ʥ��֮��"   :     ({ 50, 10 }),
			"ʥ��֮��"   :     ({ 15, 40 }),
			"�����λ�"   :     ({ 50, 30 }),
			"�����ޱ�"   :     ({ 40, 40 }),
			"���顤��"    :     ({ 50, 60 }),
			"���顤��"    :     ({ 60, 50 }),	
		]);

		object ob; // ����
		int total_force, total_neili, i, count;
		string *key_enchase, *key_neck_point;
		mapping enchase;

		total_force = 0;
		total_neili = 0;

		if (! objectp(me))return 0;

		if (! objectp( ob = me->query_temp("armor/neck")))return 0;
				
		if (! ob->is_item_make())return 0;
		
		if (ob->query("enchase_all") < 1)return 0;
		
		enchase = ob->query("enchase");

		if (! sizeof(enchase))return 0;

		key_enchase = keys(enchase);
		count = sizeof(key_enchase);
		if (! count)return 0;
		
		
		for (i = 0; i < count; i ++ )
		{
			// �ҵ���Ӧ����Ƕ��Ʒ
			key_neck_point = neck_enlist[enchase[key_enchase[i]]["name"]];
			if (sizeof(key_neck_point))
			{
					total_force += key_neck_point[0];
					total_neili += key_neck_point[1];
			} 
		}

		if (k == 1)return total_force;
		if (k == 2)return total_neili;
		
		return 0;
						
}

// ����������Ƿ���Ƕ��ĳ������Ʒ
// ���ڼ���Ƿ����Ч
// ����0��û����Ƕ������������Ϊ�������Ч�ļ���
int neck_enchase_item(object me, string item1, string item2)
{
		object ob; // ����
		string *key_enchase;
		mapping enchase;
		int count, i, i1, i2, result;
		int have10kOB = 0; // �Ƿ���10����Ƕ��

		if (! objectp(me))return 0;

		if (! objectp( ob = me->query_temp("armor/neck")))return 0;
				
		if (! ob->is_item_make())return 0;
		
		if (ob->query("enchase_all") < 1)return 0;
		
		enchase = ob->query("enchase");

		if (! sizeof(enchase))return 0;

		key_enchase = keys(enchase);
		count = sizeof(key_enchase);
		if (! count)return 0;
		
		i1 = 0;
		i2 = 0;
		for (i = 0; i < count; i ++ )
		{
			// �ҵ���Ӧ����Ƕ��Ʒ
			if (enchase[key_enchase[i]]["name"] == item1)i1 ++;
			if (enchase[key_enchase[i]]["name"] == item2)i2 ++;	
			
			// �Ƿ���Ƕ10�ױ�ʯ
			if (enchase[key_enchase[i]]["spe_data"]["luhua-zhijing"])have10kOB = 1;
		}

		if (i1 == 0 || i2 == 0)return 0;
		
		// ���㼸��
		result = i1 < i2 ? i1 : i2;

		if (COMBAT_D->enchased_neck_item(me, "�߲�����"))result += 2;
		
		if (COMBAT_D->enchased_neck_item(me, "ʥʯ") &&
			item1 == "����ʯ" || item1 == "�챦ʯ")result += 6;

		if (COMBAT_D->enchased_neck_item(me, "ˮ��") &&
			item1 == "ʥ��֮��" || item1 == "ʥ��֮��")result += 5;

		if (COMBAT_D->enchased_neck_item(me, "��������") &&
			item1 == "�����λ�" || item1 == "�����ޱ�")result += 5;
		
		if (COMBAT_D->enchased_neck_item(me, "����֮��") &&
			item1 == "���顤��" || item1 == "���顤��")result += 5;
		
		if (have10kOB)result += 5;
		
		return result;

}

// �����������⹥��
int do_neck_attack(object me, object target)
{
		mapping special_attack = ([
			"��˫�ϻ�"    :  ({"����ʯ", "�챦ʯ"}),
			"ʥ��֮ŭ"    :  ({"ʥ��֮��", "ʥ��֮��"}),
			"������"      :  ({"�����λ�", "�����ޱ�"}),
			"����ϻ�"    :  ({"���顤��", "���顤��"}),
		]);

		string *key_special_attack, *need_item, msg;
		string skill; // ����ѡ���ļ���
		int count, point;

		key_special_attack = keys(special_attack);

		count = sizeof(key_special_attack);

		skill = key_special_attack[random(count)];

		// �ü��ܳ��ּ���
		need_item = special_attack[skill];
		point = neck_enchase_item(me, need_item[0], need_item[1]);

		if (point > 2 && userp(target))point /= 2;
				
		if (! point)return 0;
		
		if (! objectp(me) || ! objectp(target))return 0;		

		// ���㼸��
		if (1 + random(100) <= point)
		{
			if (skill == "��˫�ϻ�")
			{
				msg = HIY "$N��ǰ������â��������Ȼ��������ħһ�㣬��Ȼʩչ������˫�ϻ�������������$n" HIY "��\n" NOR;
				message_combatd(msg, me, target);
				COMBAT_D->do_attack(me, target, 0, 0);
				COMBAT_D->do_attack(me, target, 0, 0);
			}
			if (skill == "ʥ��֮ŭ")
			{
				msg = HIC "ɲ�Ǽ䣬$N��ǰ�����������۵����⣬����ͣ�Ĳ������񼼡�ʥ��֮ŭ����Ȼ��������̼䣬һ����â������$n" HIC "��\n" NOR;
				message_combatd(msg, me, target);
				if (target->query("neili") > 0)								
					target->add("neili", -1 * target->query("neili") / 10 );
				if (target->query("qi") > 0)								
					target->add("qi", -1 * target->query("qi") / 10 );
				if (target->query("eff_qi") > 0)								
					target->add("eff_qi", -1 * target->query("eff_qi") / 20 );
				
				if (userp(target))target->start_busy(5 + random(5));
				else target->start_busy(8 + random(8));
				
			}
			if (skill == "������")
			{
				msg = HIM "ͻȻ��$N��ǰ��������������죬����ǧ�������������������������ѱ�Х�������쳹��أ�\n" NOR;
				message_combatd(msg, me, target);
				if (userp(target))
					target->receive_wound("qi", me->query("jiali") * 2 + random(me->query("jiali") * 3));

				else
					target->receive_wound("qi", me->query("jiali") * 3 + random(me->query("jiali") * 6));

			}
			if (skill == "����ϻ�")
			{
				msg = HIG "�����������������$N��ǰ�ٳ���ӿ�����ܣ�����������ϻ���ȴ�ѷ�������$n" HIG "���֣�\n" NOR;
				COMBAT_D->do_attack(me, target, 0, 0);
				COMBAT_D->do_attack(me, target, 0, 0);
				message_combatd(msg, me, target);
				if (userp(target))
					target->receive_wound("qi", me->query_skill("force") * 2 + random(me->query_skill("force") * 3));
				
				else
					target->receive_wound("qi", me->query_skill("force") * 3 + random(me->query_skill("force") * 6));
			}

			// �����;ö�
			if (objectp(me->query_temp("armor/neck")))
			{
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
			}
		}
		
		return point;
		
}


// huya
void huya_remove_effect(object me, int ef_point, int en_heishuijing)
{
		me->delete_temp("enchase/special/huya", 1); // ȡ����־
		me->add_temp("apply/damage", -1 * (ef_point + ef_point / 2 * en_heishuijing));
		me->add_temp("apply/str", -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/force", -1 * (ef_point / 20 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/blade", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/staff", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/whip", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/club", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));	
		
		tell_object(me, HIG "����Х����Ч����ʧ�ˡ�\n" NOR);
}

// yingyan
void yingyan_remove_effect(object me, int ef_point, int en_heishuijing)
{
		me->delete_temp("enchase/special/yingyan", 1); // ȡ����־
		me->add_temp("apply/damage", -1 * (ef_point + ef_point / 2 * en_heishuijing));
		me->add_temp("apply/dex", -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/finger", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/strike", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/unarmed", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/cuff", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/hand", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/claw", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));

		tell_object(me, HIG "��ӥ֮�衹��Ч����ʧ�ˡ�\n" NOR);
}

// xuejingling
void xuejingling_remove_effect(object me, int ef_point, int en_heishuijing)
{
		me->delete_temp("enchase/special/xuejingling", 1); // ȡ����־
		me->add_temp("apply/con",  -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/dex",  -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/str",  -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/dodge",  -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/parry",  -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/force",  -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));

		tell_object(me, HIG "��ѩ��ʥ������Ч����ʧ�ˡ�\n" NOR);
}

// xuejingling ��������
void fenshen_remove_effect(object me)
{
		me->delete_temp("hiding_kuihua");	    
		tell_object(me, HIG "��ѩ��ʥ�����������Ч����ʧ�ˡ�\n" NOR);
}

// ���ӻ������⹥��
int do_wrists_attack(object me, object victim, string en9)
{
	mapping enchase;
	int i_en, i, i_temp, j;
	string item_type, ran_item_enchase, s_temp;
	string ran_enchase_affect;

	string *k_enchase, *k_affect_list;
	mapping affect_list;
	string ran_affect;
	int en_zipili = 0; // �Ƿ���Ƕ�ſ�������
	int en_heishuijing = 0; // �Ƿ���Ƕ�ſ׺�ˮ��
	int i_ef;

	object item;

	int ef_point, ef_ran, n_ef;
	int ran_result;
	string msg;

	mapping list = ([
		"ӥ��"   :  ([
					"yingyan" : ([   "ran"    :  1 + random(2),
                                     "point"  :  500 + random(501)]),
		]),
		"����"   :  ([
					"huya" : (["ran"    :  1 + random(2),
                               "point"  :  500 + random(501)]),
		]),
		"ѩ����"   :  ([
					"xuejingling"    : (["ran"    :  1 + random(2),
                                         "point"  :  500 + random(501)]),
		]),
		"��ˮ�ڻ�"   :  ([
					"bishuironghua"  : (["ran"    :  1 + random(2),
                                         "point"  :  300 + random(201)]),
		]),
	]);

	if (! objectp( item = me->query_temp("armor/wrists")))return 0;

    // ������������򷵻�
	if (! item->is_item_make())return 0;

	// û����Ƕ�򷵻�
	enchase = item->query("enchase");
	
	if (! mapp(enchase))return 0;
	i_en = sizeof(enchase);
	if (! i_en)return 0;

	// ���ʼ��� ƽ��?% + �����ۼ�%
	// ͬһʱ�����ѡȡһ����Ч
	k_enchase = keys(enchase);

    // ������Ƕ����Ʒ�����ѡ��һ��
	ran_item_enchase = enchase[k_enchase[random(i_en)]]["name"];

	// ��ѡȡ����Ʒ�����ѡ��һ����Ч
	affect_list = list[ran_item_enchase];
	if (! affect_list)return 0;

	k_affect_list = keys(affect_list);

	i_ef = sizeof(k_affect_list);
	if (! i_ef)return 0;

	ran_affect = k_affect_list[random(i_ef)];

	// ��Чѡȡ�ú��������Ч���ʼ�������ʱ��ȣ�
	// ���ʼ��� ƽ��?% + �����ۼ�%
	// �������㣬��ǰ��ȡ�������Ƕ��Ʒ�ĸ���Ч����
	
	// �ȼ�������
	ef_point = list[ran_item_enchase][ran_affect]["point"];

	// ���㼸��
	// �ȼ��㼸���ܺͼ�����Ч����
	n_ef = 0;
	ef_ran = 0;
	for (i = 0; i < i_en; i ++)
	{
		// �ֱ����λ������Ƕ����Ʒ
		s_temp = enchase[k_enchase[i]]["name"];

		// ���Ч���������޸���Ƕ��Ʒ������
		if (member_array(s_temp,keys(list)) == -1)continue;

		// �������Ƕ��Ʒ���ڴ���Ч
		if (mapp(list[s_temp][ran_affect]))
		{
			n_ef += 1;
			ef_ran += list[s_temp][ran_affect]["ran"];
		}
	}

	// �õ�������ļ���
	if (n_ef <= 0)ran_result = 2;  //�Է���һ
	else
		ran_result = ef_ran / n_ef + n_ef - 1;


	// �Ƿ���Ƕ�������ͺ�ˮ��
	for (j = 0; j < sizeof(k_enchase); j ++ )
	{
		if (enchase[k_enchase[j]]["name"] == "��ˮ��")
		{
			en_heishuijing = 1;
		}
		if (enchase[k_enchase[j]]["name"] == "������")
		{
			en_zipili = 1;
		}
	}

    // �ⲿ���ã������Ƿ���Ƕĳ����Ʒ
	if (stringp(en9))
	{
		if (en9 == "heishuijing")
			return en_heishuijing;

		if (en9 == "zipili")
			return en_heishuijing;
	}

	// ����ж��Ƿ񷢳�����Ч
	if (1 + random(100) > ran_result)return 0;
	
	// ������Ч
	switch(ran_affect)
	{
		case "yingyan":

			if (me->query_temp("enchase/special/yingyan"))return 0;

			message_combatd(HIG + "$N" HIG "�ġ�" + ran_item_enchase + "������һ������Ĺ�â��\n" NOR, me);

			msg = HIR "����ɢȥ��һ��������Х������մ�����" + me->name() + HIR "ָ�����죬������⻮����" + me->name() +
				  HIR "\n��Χ��Ȼ�󽥽����������ڣ����˷�����˼��\n" NOR;
			tell_object(me, msg);
			
			me->set_temp("enchase/special/yingyan", 1); // ���ñ�־�������ظ��ۼ�Ч��
			me->add_temp("apply/damage", ef_point + ef_point / 2 * en_heishuijing);
			me->add_temp("apply/dex", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/finger", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/strike", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/unarmed", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/cuff", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/hand", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/claw", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->start_call_out((: call_other, __FILE__, "yingyan_remove_effect",
				                  me, ef_point, en_heishuijing :), 180 + 180 / 2 * en_zipili);
			return 0;

		case "huya":

			if (me->query_temp("enchase/special/huya"))return 0;

			message_combatd(HIG + "$N" HIG "�ġ�" + ran_item_enchase + "������һ������Ĺ�â��\n" NOR, me);

			msg = HIY "��Ȼ�䣬һ�������ĺ�����" + item->name() + HIY "����㴫�����������ǣ�����" + me->name() + HIY
				  "\n�������£�һ�����ɫ�Ĺ�â����ȫ�����֣�ɲ�Ǽ������ޱȣ������ͻ���\n" NOR;
			tell_object(me, msg);

			me->set_temp("enchase/special/huya", 1); // ���ñ�־�������ظ��ۼ�Ч��
			me->add_temp("apply/damage", ef_point + ef_point / 2 * en_heishuijing);
			me->add_temp("apply/str", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/force", ef_point / 20 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/blade", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/staff", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/whip", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/club", ef_point / 10 + ef_point / 20 * en_heishuijing);

			me->start_call_out((: call_other, __FILE__, "huya_remove_effect",
				                  me, ef_point, en_heishuijing :), 180 + 180 / 2 * en_zipili);

			return 0;

		case "xuejingling":

			if (me->query_temp("enchase/special/xuejingling"))return 0;

			message_combatd(HIG + "$N" HIG "�ġ�" + ran_item_enchase + "������һ������Ĺ�â��\n" NOR, me);

			msg = HIW "��ɫͻ�䣬�����ѩ���裬����ѩ��������£��׷�����" + me->name() + HIW +"��Ȼ������" + me->name() +
				  HIW "\n��֫��������ʧ��\n" NOR;
			tell_object(me, msg);

			me->set_temp("enchase/special/xuejingling", 1); // ���ñ�־�������ظ��ۼ�Ч��
			me->add_temp("apply/con", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/dex", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/str", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/dodge", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/parry", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/force", ef_point / 10 + ef_point / 20 * en_heishuijing);
			
			me->set_temp("hiding_kuihua", 1); // ����Ӱ

			me->start_call_out((: call_other, __FILE__, "xuejingling_remove_effect",
				                  me, ef_point, en_heishuijing :), 180 + 180 / 2 * en_zipili);

			me->start_call_out((: call_other, __FILE__, "fenshen_remove_effect",
				                  me :), 45 + 22 / 2 * en_zipili);

			return 0;

		case "bishuironghua":

			if (time() - victim->query_temp("enchase/special/bishuironghua") < 180)return 0;			

			message_combatd(HIG + "$N" HIG "�ġ�" + ran_item_enchase + "������һ������Ĺ�â��\n" NOR, me);

			msg = HIG "һ���̹�������" + victim->name() + HIG "�ƺ�����аһ�㣬�ճյ�����ǰ�����̹�ȴ���޼ɵ��ش���" + 
				  victim->name() + HIG "���壬����಻���ԡ�\n" NOR;
			tell_object(me, msg);

			victim->set_temp("enchase/special/bishuironghua", time());
			victim->start_busy(2 + random(2));
			victim->affect_by("bishuihan_poison",
                              ([ "level" : 300 + 300 / 2 * en_heishuijing,
                                 "id"    : me->query("id"),
                                 "duration" : 100 + 100 / 2 * en_zipili ]));

			return 0;
	}

	return 0;
		
}

// ����������͸����Ʒ�б���������Ʒ��base_name
string *imbue_list = ({
        "/clone/fam/gift/int3",
        "/clone/fam/gift/con3",
        "/clone/fam/gift/str3",
        "/clone/fam/gift/dex3",
        "/clone/fam/item/bless_water",
        "/clone/fam/etc/lv7d",
        "/clone/fam/etc/lv7c",
});

// ����Ĵ�����������ޣ����ÿ��IMBUE�Ժ�ȡ0-IMBUE���������
// �����������ֵ����IMBUE���ճɹ���
#define RANDOM_IMBUE_OK         105

// ÿ�ν�����Ҫʥ���Ĵ���
#define SAN_PER_IMBUE           5

// ɱ�����Ժ�Ľ���
void killer_reward(object me, object victim, object item)
{
        int exp;
        mapping o;
        string my_id;

        if (! me || ! victim)
                return;

        if (! victim->query("can_speak"))
                // only human does effect
                return;

        // record for this weapon
	if (victim->is_not_bad())  item->add("combat/WPK_NOTBAD", 1);
	if (victim->is_not_good()) item->add("combat/WPK_NOTGOOD", 1);
	if (victim->is_good())     item->add("combat/WPK_GOOD", 1);
	if (victim->is_bad())      item->add("combat/WPK_BAD", 1);

        if (userp(victim))
                item->add("combat/PKS", 1);
        else
                item->add("combat/MKS", 1);

        exp = victim->query("combat_exp");
        if (exp < 10000 || me->query("combat_exp") < exp * 4 / 5)
                return;

        exp /= 10000;
        if (exp > 250) exp = 100 + (exp - 250) / 16; else
        if (exp > 50) exp = 50 + (exp - 50) / 4;
        my_id = me->query("id");
        o = item->query("owner");
        if (! o) o = ([ ]);
        if (! undefinedp(o[my_id]) || sizeof(o) < 12)
                o[my_id] += exp;
        else
        {
                // Too much owner, I must remove one owner
                int i;
                int lowest;
                string *ks;

                lowest = 0;
                ks = keys(o);
                for (i = 1; i < sizeof(ks); i++)
                        if (o[ks[lowest]] > o[ks[i]])
                                lowest = i;
                map_delete(o, ks[lowest]);
                o += ([ my_id : exp ]);
        }
        item->set("owner", o);
}

// �ٻ���Ʒ
int receive_summon(object me, object item)
{
        object env;
        object temp;
        int type;
        
/* ��/adm/daemons/biwud.c ������
	// ���⣺�����սϵͳ�����ҵı��������ٻ� 
	if (! playerp(me) && item->item_owner() != me->query("id"))return 1;
*/	
        if ((env = environment(item)) && env == me)
        {
                tell_object(me, item->name() + "������������"
                            "����ٻ���ʲô����\n");
                return 1;
        }

        if (me->query("jingli") < 200)
        {
                tell_object(me, "����ͼ����" + item->name() +
                            "���������Խ��뾳�磬�����Ǿ������á�\n");
                return 0;
        }
        me->add("jingli", -200);

        if (item->query("id") == "qingtian")
        {
              message_sort(HIM "\nֻ�����ܽ��ɢ�������ƶ�䣬Զ���з�����ƣ�������Ϸ������"
                           "��������������$N" HIM "һ����Х��" + item->query("name") + HIM
                           "�ƿն��� ������\n\n" NOR, me); 
        }
        else

              message_vision(HIW "$N" HIW "ͻȻ���һ��������������"
                             "һץ����Ȼ�����ܲ�������������\n\n" NOR, me);

        if (env == environment(me))
        {
                message_vision(HIW "ֻ�����ϵ�" + item->name() +
                               HIW "Ӧ�����𣬷�Ծ��$N" HIW
                               "�����У�\n\n" NOR, me);
        } else
        {
                type = random(3);
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        switch (type)
                        {
                        case 0:
                                message("vision", HIW "����д�������������"
                                        "����Ȼ����������" + item->name() +
					HIW "�ڿն���"
                                        "��ʧ������\n\n" NOR, env);
                                break;
                        case 1:
                                message("vision", HIC "һ�����������"
                                        "���ֶ���" + item->name() + HIC "��ֻ��" +
					item->name() + HIC "���������ƿն�"
					"�ߡ�\n\n" NOR, env);
                                break;
                        default:
                                message("vision", HIY "��Ȼ�������أ���������" +
                                        item->name() + HIY "�����ʵĶ������£�����һ"
					"�����ת˲������\n\n" NOR, env);
                                break;
                        }

                        if (interactive(env = environment(item)))
                        {
                                tell_object(env, HIM + item->name() +
                                                 HIM "��Ȼ�����ȥ�ˣ�\n" NOR);
                        }
                }

                switch (type)
                {
                case 0:
                        message_vision(HIW "һ��" HIR "����" HIW "��"
                                       "���绮�Ƴ��գ�" + item->name() + HIW
                                       "�������������$N" HIW "�����У�\n\n" NOR, me);
                        break;
                case 1:
                        if (item->query("id") == "qingtian")break;

                        message_vision(HIW "һ��" HIY "����" HIW "ɨ��"
                                       "��գ�ֻ��" + item->name() + HIW
					"������$N" HIW "�����У�\n\n" NOR, me);
                        break;
                default:
                        message_vision(HIW "ֻ��" + item->name() + HIW "�������죬��"
                                       "����ʣ�Ю�ƴ���ͻ����$N"
                                       HIW "�����У�\n\n" NOR, me);
                        break;
                }
        }

        // ȡ��no_get����
        item->delete_temp("stab_by");
        item->delete("no_get");

        item->move(me, 1);
        if (environment(item) != me)
                return 1;

        if (item->query("armor_type"))
        {
                // is armor
                temp = me->query_temp("armor/" + item->query("armor_type"));
                if (temp) temp->unequip();
                WEAR_CMD->do_wear(me, item);
        } else
        if (item->query("skill_type"))
        {
                if (temp = me->query_temp("weapon"))
                        temp->unequip();
                if (temp = me->query_temp("secondary_weapon"))
                        temp->unequip();
                WIELD_CMD->do_wield(me, item);
        }

        return 1;
}

// ������Ʒ
int hide_anywhere(object me, object item)
{
        if (item->item_owner() != me->query("id"))
                return 0;

        if (me->query("jingli") < 100)
        {
                tell_object(me, "����ͼ��" + item->name() +
                            "��ȥ�����Ǿ������ã����Է�������������\n");
                return 0;
        }
        me->add("jingli", -100);

        message_vision(HIM "$N" HIM "����һ��" + item->name() +
                       HIM "����Ȼ�����ټ���\n", me);
        destruct(item);
        return 1;
}

// ׷Ѱ��Ʒ
int receive_miss(object me, object item)
{
        object env, me_env;
	string bn, bn2;

        env = environment(item);

        if (env == environment(me))
        {
                write("�����" + item->name() + "����ɶ��\n");
                return 0;
        }

        if (env == me)
        {
                write("������" + item->name() + "�����˰���Ĵ���\n");
                return 0;
        }

        if (! objectp(env) || userp(env) || environment(env))
        {
                write("����ͼ��Ӧ" + item->name() + "�����Ǹо��ǳ�����ã��\n");
                return 0;
        }

        if (! wizardp(me) && ! env->query("outdoors"))
        {
                write("ڤڤ�����Ӧ��" + item->name() + "�������ƺ����Ե������\n");
                return 0;
        }

        message("vision", me->name() + "������˼������֪��Ҫ��Щʲô��\n",
                environment(me), ({ me }));
        if (me->query("jingli") < 400)
        {
                write("�����" + item->name() + "�ĸо��൱"
                      "Ʈ���������������ã����Ը�Ӧ��\n");
                return 0;
        }

	bn = base_name(env);
	me_env = environment(me);
	if (sscanf(bn, "/kungfu/class/sky%s", bn2) == 1)
	{
		write("��о� " + item->name() + NOR " �ƺ����������˽磡\n" NOR);
		return 0;
	}
	if (sscanf(bn, "/d/newbie/%s", bn2) == 1)	
	{
		log_file("horse", me->query("id") + "��" + ctime(time()) + " ��ͼ���ñ����ص����ִ塣\n");
		return notify_fail("��о� " + item->name() + NOR " �ƺ����ܸ�Ӧ����ĺ�����\n" NOR);
	}
	if (bn->query("no_flyto"))
	{
		write("���޷�׷Ѱ������������ڵء�\n");
		return 0;
	}
	
	// �������ϲ���MISS
	if (sscanf(base_name(me_env), "/d/penglai/%s", bn2) == 1)
	{
		write("�޷���Ӧ����ı������ڣ�\n" NOR);
		return 0;
	}
		
	// �������ϲ���MISS
	if (sscanf(bn, "/d/shenlong/%s", bn2) == 1)
	{
		write("�޷���Ӧ����ı������ڣ�\n" NOR);
		return 0;
	}

	if (sscanf(base_name(me_env), "/d/shenlong/%s", bn2) == 1)
	{
		write("�˴��޷���Ӧ����ı�����\n");
		return 0;
	}

        // ���ľ���
        me->add("jingli", -300 - random(100));
        message_vision(HIM "$N" HIM "���������дʣ�ת˲���һ�����绮"
                       "����$N" HIM "�ݲʺ���ߡ�\n" NOR, me);
        tell_object(me, "��׷Ѱ" + item->name() + "��ȥ��\n");
        me->move(environment(item));
        message("vision", HIM "һ���ʺ绮����ʣ�" + me->name() +
                HIM "ƮȻ���£��������ɡ�\n" NOR, environment(me), ({ me }));
        tell_object(me, HIM "��׷Ѱ����" + item->name() +
                    HIM "�����¶ݹ⡣\n" NOR);
        return 1;
}

// ���ڵ���
int do_stab(object me, object item)
{
        if (! item->is_weapon() && item->query("armor_type") != "hands")
                return notify_fail(item->name() + "Ҳ�ܲ��ڵ��ϣ�\n");

        if (! environment(me)->query("outdoors") &&
            ! wizardp(me))
                return notify_fail("��������Ūʲô��\n");

        item->set("no_get", bind((: call_other, __FILE__, "do_get_item", item :), item));
        item->set_temp("stab_by", me->query("id"));

        message_vision(WHT "\n$N" WHT "���ֽ�" + item->name() + NOR +
                       WHT "������һ�壬��������㶡�һ�����졣\n\n" NOR, me);
        item->move(environment(me));
        return 1;
}

// ��ȡ��Ʒʱ���
mixed do_get_item(object item)
{
        object me;

        if (! objectp(me = this_player()))
                return 1;

        if (me->query("id") != item->query_temp("stab_by") &&
            me->query("id") != item->item_owner())
                return "����ͼ��" + item->name() + "����ȴ"
                       "�������·�������������һ�㣬�޷�������\n";

        message_vision(HIW "\n$N" HIW "���ַ���" + item->name() +
                       HIW "��������ʱֻ�����͡���һ��������һ��"
                       "������\n\n" NOR, me);
        item->delete_temp("stab_by");
        item->delete("no_get");
        item->move(me, 1);
        return "";
}

// �������⹦��
mixed do_touch(object me, object item)
{
        string msg;
        object ob;
        object *obs;
        mapping my;
        int ran_n; 

        if (me->query("id") != item->item_owner())
        {
                message_vision(HIR "\n$N���ᴥ��" + item->name() +
                               HIR "��ͻȻ��ȫ��һ��������������"
                               "���ܵ����\n" NOR, me);
                me->receive_damage("qi", 50 + random(50));
                return 1;
        }

		

        if (me->query("jingli") < 160)
        {
                me->set("jingli", 1);
                return notify_fail(CYN "\n������" + item->name() +
                                   CYN "��ã�����һ����̾��\n" NOR);
        }
		else
                me->add("jingli", -150);

        switch (random(3))
        {
        case 0:
                msg = CYN "\n$N" CYN "����һ��$n" CYN "������"
                      "������������������\n" NOR;
                break;
        case 1:
                msg = CYN "\n$N" CYN "���ḧ��$n" CYN "������"
                      "��һ�ף�$n" CYN "�������죬���Ժ�֮��\n" NOR;
                break;
        default:
                msg = CYN "\n$N" CYN "��Ȼһ����̾���ḧ$n"
                      CYN "����˼���ã������п���ǧ��\n" NOR;
                break;
        }

        switch (random(3))
        {
        case 0:
                msg += HIM "��Ȼֻ��$n" HIM "����һ���⻪��"
                       "��Ծ����ɢ��ǧ�����롣\n" NOR;
                break;
        case 1:
                msg += HIM "����$n" HIM "һ�����������Ʋ���"
                       "��ֱ���뵽����ķ���ȥ��\n" NOR;
                break;
        default:
                msg += HIM "��ʱ��$n" HIM "��â���䣬������"
                       "����ʣ��Ƶ�������Ŀ�ӡ�\n" NOR;
                break;
        }

        msg = replace_string(msg, "$n", item->name());
        message_vision(msg, me);

	ran_n = 1000;
	if (me->is_fighting())ran_n = 3000;
	
        if (random(ran_n) == 1 || wizardp(me))
        {
                obs = filter_array(all_inventory(environment(me)), (: userp :));
                foreach (ob in obs)
                {
                        my = ob->query_entire_dbase();
                        my["jing"]   = my["eff_jing"] = my["max_jing"];
                        my["qi"]     = my["eff_qi"]   = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                        my["jingli"] = my["max_jingli"];
                        ob->set_temp("nopoison", 1);
                }
                tell_object(obs, HIC "��е�һ���º͵�����Ϯ��������"
                                "�������һ�㡣\n" NOR);
        } else
        if (me->query("neili") < me->query("max_neili") || item->query("enchase_all") >= 9 )
        {
			    // �ſױ�����Ч
			    if (item->query("enchase_all") >= 9 
					&& me->query("qi") > 500 
					&& time() - me->query_temp("last_touch_jl") > 180)
			    {
						me->set("eff_jingli", me->query("max_jingli"));
						me->set("jingli", me->query("max_jingli"));

						me->receive_damage("qi", 400);
						me->set_temp("last_touch_jl", time());
			    }

                me->set("neili", me->query("max_neili"));
                tell_object(me, HIC "��ֻ��һ������������ȽȽ����"
                                "˵�����������\n" NOR);
        }
        return 1;
}

// ʥ����Ʒ
int do_san(object me, object item)
{
        string my_id;
        int count;
        int san;

        if (! item->query("skill_type") && item->query("armor_type") != "hands")
        {
                // ��װ���ࣿ
                return notify_fail("װ�����ڻ��޷�ʥ����\n");
        }

        // �������ʥ��
        if (item->query("magic/power") > 0)
                return notify_fail("����" + item->name() + "������"
                                   "�Ѿ��õ��˳�ֵķ����ˡ�\n");

        if (item->query("magic/imbue_ok"))
                return notify_fail("����" + item->name() + "��Ǳ��"
                                   "�Ѿ�����ھ��ˣ�����ֻ����Ҫ��"
                                   "��һ���ںϡ�\n");

        my_id = me->query("id");

        count = sizeof(item->query("magic/do_san"));
        if (item->query("magic/imbue_ob"))
                return notify_fail("����" + item->name() + "�Ѿ�����ֵ�ʥ"
                                   "���ˣ���Ҫ���������Խ�һ��ĥ����\n");

        if (item->query("magic/do_san/" + my_id))
                return notify_fail("���Ѿ�Ϊ" + item->name() + "ʥ�����ˣ�"
                                   "�Ƿ����������޷�������ȫ���ա�\n��"
                                   "�б�ҪѰ�����˰����Լ���ʥ����\n");

        if (item->item_owner() == my_id)
        {
                if (! count)
                        return notify_fail("��Ӧ����Ѱ����λ����Э��������ʥ��" +
                                           item->name() + "��\n");

                if (count < SAN_PER_IMBUE - 1)
                        return notify_fail("��Ӧ����Ѱ��" +
                                           chinese_number(SAN_PER_IMBUE - 1 - count) +
                                           "λ��������ʥ��" + item->name() + "��\n");
        } else
        {
                if (count >= SAN_PER_IMBUE - 1)
                        return notify_fail("�����Ҫ��������Ϊ��ʥ��������������ˡ�\n");
        }

        if (me->query("neili") < me->query("max_neili") * 9 / 10)
                return notify_fail("�����������������棬����óȻ���ã�\n");

        if (me->query("jingli") < me->query("max_jingli") * 9 / 10)
                return notify_fail("�����ھ������ã�����óȻ���ã�\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����������ʵ������óȻʥ����\n");

        if (me->query("max_neili") < 8000)
                return notify_fail("�㳢������һ���������޷�˳"
                                   "������һ�����죬����ʩչ���������\n");

        if (me->query("max_jingli") < 1000)
                return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");

        message_sort(HIM "\n$N" HIM "���ḧ��$n" HIM "����ָ�������ϣ�ͬ"
                     "ʱ��ת���������������澭����ԴԴ������������ע"
                     "��$n" HIM "������ֻ����������$n" HIM
                     "����Ȼ�������������ܡ�\n" NOR, me, item);

        if (me->query("max_neili") < me->query_neili_limit() - 400)
        {
                if (random(2) == 1)
                {
                        // ����δ������
                        message_vision(HIR "$N" HIR "��ɫ��Ȼ���˱䡣\n" NOR,
                                       me);
                        tell_object(me, HIC "���Ȼ���õ�����Ϣ��Щ���ҡ�\n" NOR);
                } else
                {
                        message_vision(HIR "$N" HIR "��Ȼ�ƺ�һ������"
                                       "��ɲʱ�����죡\n" NOR, me);
                        tell_object(me, HIC "��е����������������δ����"
                                    "���������������������ڹ�������\n" NOR);
                        tell_object(me, HIC "��Ļ����ڹ��½��ˡ�\n");
                        me->set_skill("force", me->query_skill("force", 1) - 10 - random(5));
                        return 1;
                }
        }

        // ͳ��IMBUE���Ĵ��������������㱾��MAX_NEILI/JINGLI������
        san = item->query("magic/imbue");

        me->add("max_neili", -(san + 5));
        me->add("neili", -(san * 10 + 100));
        me->add("max_jingli", -(san * 5 + 50));
        me->add("jingli", -(san * 5 + 50));
        item->set("magic/do_san/" + my_id, me->name(1));
        me->start_busy(1);

        if (item->item_owner() == my_id)
        {
                tell_object(me, HIW "������Ƭ�̣�����" + item->name() +
                            HIW "�ƺ��������ԣ���Ծ���ݣ�����΢΢һЦ��\n" NOR);
                message("vision", HIW + me->name() + HIW "��Ȼ"
                        "΢΢һЦ��\n" HIW, environment(me), ({ me }));

                // ѡ��һ����Ҫimbue����Ʒ
                item->set("magic/imbue_ob", imbue_list[random(sizeof(imbue_list))]);
        }
        return 1;
}

// ��͸��Ʒ
int do_imbue(object me, object item, object imbue)
{
        if (item->query("magic/power") > 0)
                return notify_fail("����" + item->name() + "������"
                                   "�Ѿ��õ��˳�ֵķ����ˡ�\n");

        if (item->query("magic/imbue_ok"))
                return notify_fail("����" + item->name() + "��Ǳ��"
                                   "�Ѿ�����ھ��ˣ�����ֻ����Ҫ��"
                                   "��һ���ںϡ�\n");

        if (sizeof(item->query("magic/do_san")) < SAN_PER_IMBUE)
                return notify_fail("������ȶ�" + item->name() +
                                   "���г�ֵ�ʥ�����С�\n");

        if (base_name(imbue) != item->query("magic/imbue_ob"))
                return notify_fail(item->name() + "���ڲ���Ҫ��" +
                                   imbue->name() + "�����롣\n");

        message_sort(HIM "$N" HIM "����һ����������������һ���˪��ֻ����ס$n" +
                     imbue->name() +
                     HIM "����Ȼ���ڻ������ģ���Ө��͸��$N"
                     HIM "����һ�ӣ���һ����Һ����$n" HIM
                     "�ϣ���ʱ������������������ʣ������˸��\n" NOR,
                     me, item);

        tell_object(me, "�㽫" + imbue->name() + "��Ч��������" +
                    item->name() + "��\n");
        item->delete("magic/do_san");
        item->delete("magic/imbue_ob");
        imbue->add_amount(-1);
        if (imbue->query_amount() < 1)
                destruct(imbue);

        me->start_busy(1);

        item->add("magic/imbue", 1);
        if (random(item->query("magic/imbue")) >= RANDOM_IMBUE_OK)
        {
                // ��͸���
                tell_object(me, HIG "���Ȼ�������е�" + item->name() +
                            HIG "��һ��ԾԾ���Եĸо����ƺ��ڴ���ʲô��\n" NOR);
                item->set("magic/imbue_ok", 1);
        }

        return 1;
}

// ��Ƕ��Ʒ
int do_enchase(object me, object item, object tessera)
{
        if (item->query("magic/power") > 0)
                return notify_fail("����" + item->name() + "������"
                                   "�Ѿ��õ��˳�ֵķ����ˡ�\n");

        if (! item->query("magic/imbue_ok"))
                return notify_fail("����" + item->name() + "��Ǳ��"
                                   "��û�г�ֵļ�����δ����Ƕ��ʱ��\n");

        if (! tessera->query("can_be_enchased"))
                return notify_fail(tessera->name() + "����û"
                                   "��������Ƕ�ɡ�\n");

        if (! mapp(tessera->query("magic")))
                return notify_fail(tessera->name() + "���ܷ���ħ����"
                                   "û�б�Ҫ��Ƕ��" + item->name() + "���档\n");

        if (me->query_skill("certosina", 1) < 100)
                return notify_fail("����������Ƕ���ջ�����"
                                   "��죬����óȻ���֡�\n");

        message_sort(HIM "��������һ����$N" HIM "��" + tessera->name() +
                     HIM "��Ƕ����$n" HIM "���棬ֻ��$n" HIM
                     "�����������Թ���һ������Ĺ�â����"
                     "�����ƽ����˵������ƽ����\n" NOR, me, item);
        tell_object(me, HIC "�����" + item->name() + HIC "������"
                    "���������ı仯��\n" NOR);
        item->set("magic/power", tessera->query("magic/power"));
       	item->set("magic/type", tessera->query("magic/type"));
        item->set("magic/tessera", tessera->name());
        item->save();
        destruct(tessera);

        // ������Ϣ
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "��˵��Ʒ" + item->name() + HIM +
                              "�������˼䡣");

        me->start_busy(1);
        return 1;
}

string get_random_key(string key_id)
{
	key_id += sprintf("%d", random(20));
	return key_id;
}
// ��չ��Ƕ
int do_enchase2(object me, object item, object tessera)
{
		string key_id;
		mapping enchases;
		string *k_enchases;
		int i;
	
        if (! tessera->query("enchase/point"))
                return notify_fail(tessera->name() + "����û"
                                   "��������Ƕ�ɡ�\n");

        if (me->query_skill("certosina", 1) < 100)
                return notify_fail("����������Ƕ���ջ�����"
                                   "��죬����óȻ���֡�\n");

        if (item->query("enchase_all") - sizeof(item->query("enchase")) <= 0)
		return notify_fail("��� " + item->name() + NOR " ����û���㹻�Ĳ�λ��\n" );

		// �ſ���Ƕ��Ʒֻ����Ƕ���ھſ��ϣ���ÿ�ѱ���ֻ����Ƕһ��
		if (tessera->query("nine_object"))
		{
			enchases = item->query("enchase");
			if (mapp(enchases))
			{
				k_enchases = keys(enchases);
			}

			if (item->query("enchase_all") < 9)
			{
				return notify_fail("��鱦ʯֻ����Ƕ���ھſ��ϡ�\n");
			}

			for (i = 0; i < sizeof(k_enchases); i ++ )
			{
				if (enchases[k_enchases[i]]["name"] == "����ʯ" ||
					enchases[k_enchases[i]]["name"] == "���۶�ħ")
				{
					return notify_fail("������һ�ѱ�����ͬʱ��Ƕ�����ſױ�ʯ��\n");
				}
				if (enchases[k_enchases[i]]["name"] == "���ɲ���" ||
					enchases[k_enchases[i]]["name"] == "��������")
				{
					return notify_fail("������һ�ѱ�����ͬʱ��Ƕ�����ſױ�ʯ��\n");
				}
				if (enchases[k_enchases[i]]["name"] == "���Ǹ���" ||
					enchases[k_enchases[i]]["name"] == "����������")
				{
					return notify_fail("������һ�ѱ�����ͬʱ��Ƕ�����ſױ�ʯ��\n");
				}	
				if (enchases[k_enchases[i]]["name"] == "��ˮ��" ||
					enchases[k_enchases[i]]["name"] == "������")
				{
					return notify_fail("������һ�ѱ�����ͬʱ��Ƕ�����ſױ�ʯ��\n");
				}							
			}
		}

	log_file("beset", me->query("id") + " beset " + tessera->name() + NOR " to " + base_name(item) + "(" + 
	                  item->name() + NOR + ") at " + ctime(time()) + "\n");
        message_sort(HIG "��������һ����$N" HIG "��" + tessera->name() +
                     HIG "��Ƕ����$n" HIG "���棬ֻ��$n" HIG
                     "�����������Թ���һ������Ĺ�â����"
                     "�����ƽ����˵������ƽ����\n" NOR, me, item);
        tell_object(me, HIC "�����" + item->name() + HIC "������"
                    "���������ı仯��\n" NOR);

        key_id = tessera->query("id");
	if (item->query("enchase/" + key_id))
	{
		while (1)
		{			
			key_id = get_random_key(tessera->query("id"));
			if (! item->query("enchase/" + key_id))break;
		}
	}

        item->set("enchase/" + key_id + "/name", tessera->query("enchase/name"));
       	item->set("enchase/" + key_id + "/point", tessera->query("enchase/point"));
       	item->set("enchase/" + key_id + "/fy", tessera->query("enchase/fy"));
       	item->set("enchase/" + key_id + "/qy", tessera->query("enchase/qy"));
       	item->set("enchase/" + key_id + "/type", tessera->query("enchase/type"));
       	item->set("enchase/" + key_id + "/cur_firm", tessera->query("enchase/cur_firm"));
       	item->set("enchase/" + key_id + "/spe_data", tessera->query("enchase/spe_data"));

	// ������Ƕ����˺�50��
	if (item->query("skill_type") || item->query("armor_type") == "hands")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 2500); //itemmake.c point * 2
	}
	
	// �����
	if (item->query("armor_type") == "myheart" || item->query("armor_type") == "myheart2" )
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
		{
			item->set("enchase/" + key_id + "/fy", 3);
       			item->set("enchase/" + key_id + "/qy", 3);
		}
	}
	// ������Ƕ����˺�40�� itemmake.c
	if (item->query("armor_type") == "wrists")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 1);
	}
	// ������Ƕ����˺�40�� itemmake.c
	if (item->query("armor_type") == "surcoat")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 1);
	}
	// ת��ѫ����Ƕ���point 21��
	if (item->query("armor_type") == "medal2")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 21);
	}
	// ������Ƕ��߷���+50
	if (item->query("armor_type") == "armor")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 2500); // 2500*2.4
	}
	
        item->save();
	tell_object(me, HIM + item->name() + HIM " ͻȻ�����ȥ ����\n" NOR);
	destruct(item);
        destruct(tessera);

        me->start_busy(1);

        return 1;
}

// 10��������������
mixed weapon10lv_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        mapping magic;
        int jingjia;
        int power, resistance;
        int damage;
        string msg;

		int point;

        // ����ħ��Ч��
        magic = weapon->query("magic");
        power = magic["power"];
        damage = 0;
        resistance = 0;
        //jingjia = me->query("jiajing");
        jingjia = me->query("jiali") / 3;
      
        switch (magic["type"])
        {
        case "lighting":
                // ���繥�����˺�����++����+
                resistance = victim->query_temp("apply/resistance/lighting");
                damage = (power + jingjia) * 200 / (100 + resistance);
                switch (random(3))
                {
                case 0:
                        msg = HIY + weapon->name() + HIY "�ŷ����������������⣬�������죬��$n"
                              HIY "����Ϊ֮���顣\n" NOR;
                        break;
                case 1:
                        msg = HIY "һ�����������" + weapon->name() + HIY
                              "���ҫ�۶�Ŀ����$n" HIY "�޷����ӣ������ϡ�\n" NOR;
                        break;
                default:
                        msg = HIY "����������������ף�������һ������ֱ�£�" +
                              weapon->name() + HIY "��������������ͷף����$n"
                              HIY "����������\n" NOR;
                        break;
                }

                if (victim->query("neili") > damage)
                        victim->add("neili", -damage);
                else
                        victim->set("neili", 0);

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 4);
                break;

        case "cold":
                // �䶳�������˺���++����+
                resistance = victim->query_temp("apply/resistance/cold");
                damage = (power + jingjia) * 200 / (100 + resistance);
                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 5);
                switch (random(3))
                {
                case 0:
                        msg = HIB + weapon->name() + HIB "����һ����ɬ�����⣬��$n"
                              HIB "����������\n" NOR;
                        break;
                case 1:
                        msg = HIB "��Ȼ��" + weapon->name() + HIB
                              "���͸��ͨ����һ��������ĺ���ŷ�������$n"
                              HIB "����ֻ��һ�䡣\n" NOR;
                        break;
                default:
                        msg = HIB "һ����Ȧ��" + weapon->name() + HIB "�����"
                              "ɭȻ������$n" HIB "���ܣ���Ȼ��Ϣ��\n" NOR;
                        break;
                }
                break;

        case "fire":
                // ���湥�����˺���+����++
                resistance = victim->query_temp("apply/resistance/fire");
                damage = (power + jingjia) * 300 / (100 + resistance);
                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                switch (random(3))
                {
                case 0:
                        msg = HIR + weapon->name() + HIR "�������һ�����棬��$n"
                              HIR "�����������������ҽ�������\n" NOR;
                        break;
                case 1:
                        msg = HIR "һ������" + weapon->name() + HIR
                              "�ϱų���Ѹ�����׵Ļ���$n" HIR "�����˱��޿ɱܣ�\n" NOR;
                        break;
                default:
                        msg = HIR "һ���������" + weapon->name() + HIR "�Ϸɽ������"
                              "����ɢ������������$n" HIR "��\n" NOR;
                        break;
                }
                break;

        case "magic":
                // ħ����������ȡ��+
                resistance = victim->query_temp("apply/resistance/magic");
                damage = (power + jingjia) * 200 / (100 + resistance);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 4);
                switch (random(3))
                {
                case 0:
                        msg = HIM + weapon->name() + HIM "����һ�������������������������$n"
                              HIM "���񲻶��������㱡�\n" NOR;
                        break;
                case 1:
                        msg = HIM "��࣡���һ����" + weapon->name() + HIM
                              "����ܸȴ��$n" HIM "�ƺ�һ����ҡ�β�����\n" NOR;
                        break;
                default:
                        msg = HIM + weapon->name() + HIM "������һ��������ͷ׵�"
                              "��Ȧ��������$n" HIM "�����·��衣\n" NOR;
                        break;
                }
                break;

        default:
                msg = "";
                break;
        }

        // ʹ��perform
        if (random(2)) return msg;
        damage = 200 + random(400);


		if (do_wrists_attack(me, victim, "zipili"))		
			point = 6;		
		else
			point = 8;
		
        switch (random(point))
        {
        case 0:
                victim->receive_wound("jing", damage / 6 + random(damage / 6), me);
                return msg + HIM "$N" HIM "��Ȼ��Ц������" + weapon->name() +
                       HIM "�������⻪һ���������$n" HIM "���ڵ��У��޷��԰Ρ�\n" NOR;

        case 1:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                return msg + HIC "$N" HIC "���е�" + weapon->name() + HIC "������ֹ�â��"
                       "ѣĿ���ˣ�һ�������ӳ�����ؾ���ʧɫ����$n"
                       HIC "Ŀ�ɿڴ���\n" NOR;
        case 2:
                victim->receive_wound("qi", damage / 4 + random(damage / 4), me);
                return msg + HIY "$N" HIY "����" + weapon->name() +
                       HIY "��ֻ�����һ������������$n" HIY "���¼�����Ѫ��\n" NOR;

        case 3:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                return msg + HIG "$N" HIG "���ֻ���" + weapon->name() + HIG "��һȦȦ��â"
                       "Χ��$n" HIG "�����$n��Ѫ������\n" NOR;

        case 4:
                victim->receive_wound("qi", damage / 2 + random(damage / 2), me);
                return msg + HIW "$N" HIW "һ����̾��" + weapon->name() + HIW "����ݳ���"
                       "��ʱ�����㾲��$n" HIW "ֻ���������˶������˵�����ȥ��\n" NOR;

        default:
                if (me->query_temp("weapon_performing"))
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 10 + random(4) :), me), 0);
        }
}

// 9��������������
mixed weapon_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        int ap;
        int dp;
        int damage;
		int point;

        if (random(2)) return;

        // ����damage�������ǿ�������������ͨ������ͳһ����
        if (weapon->is_weapon())
                damage = me->query_temp("apply/damage");
        else
                damage = me->query_temp("apply/unarmed_damage");

		if (do_wrists_attack(me, victim, "zipili"))		
			point = 5;		
		else
			point = 8;

        switch (random(point))
        {
        case 0:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                return HIY "$N" HIY "�������е�" + weapon->name() + HIY
                       "���û���ҹ�����ǣ�����" HIM "��â" HIY "������"
                       "��Ϯ��$n" HIY "��\n" NOR;
        case 1:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                return HIR "$N" HIR "���һ��������" + weapon->name() +
                       HIR "ңָ$n" HIR "��һ��ɱ����ʱ��$n" HIR "����"
                       "������\n" NOR;
        case 2:
                victim->receive_wound("qi", damage / 6 + random(damage / 6), me);
                victim->receive_wound("jing", damage / 10 + random(damage / 10), me);
                return HIG "$N" HIG "��ػ�ת" + weapon->name() + HIG
                       "��������̲�������" NOR + HIB "�Ǻ�" HIG "��"
                       "������$n" HIG "Ȧ�����С�\n" NOR;
        case 3:
				if (do_wrists_attack(me, victim, "zipili"))
				{
					 if (me->query_temp("weapon_performing"))
			                break;
					 me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 5 + random(4) :), me), 0);					
				}
				break;
        case 4:
        case 5:
        case 6:
                break;

        default:
                if (me->query_temp("weapon_performing"))
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 5 + random(4) :), me), 0);
        }
}

// ���У�12��������
void continue_attack(object me, object victim, object weapon, int times)
{
        int i;
        string msg;
        int ap, dp;

        if (! me || ! victim || ! weapon || ! me->is_fighting(victim))
                return;

        msg  = HIW "��ʱֻ��$N" HIW "������Х������" + weapon->name() +
               HIW "��Ϊһ�壬��ʱ�亮â��ɢ����$n" HIW "��ȥ��\n" NOR;

        ap = me->query_skill("martial-cognize");
        dp = victim->query_skill("parry");

        if (ap / 2 + random(ap) > dp * 2 / 3)
                msg += HIR "$n" HIR "��֮����æ���ˣ�����Ȼ�������ܣ�����"
                       "�в�������������\n" HIW "$N" HIW "��ס$n" HIW "����"
                       "������������ת����" + weapon->name() + HIW "������"
                       "ʯ���ѳ�$n" HIW "����" + chinese_number(times) + HIW
                       "�У�\n" NOR;
        else
        {
                msg += CYN "����$n" CYN "ڤ��ֵ�����$N"
                       CYN "���е����б仯ȫȻ��ס��\n" NOR;
                message_combatd(msg, me, victim);
                return;
        }
        message_combatd(msg, me, victim);

        me->set_temp("weapon_performing", 1);
        i = times;
        while (i--)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 0);
        }
        me->delete_temp("weapon_performing");
}

// ���㴩͸��Ч��
public int chuantou_point(object me, object item)
{	
		int total;
		mapping enchase;
		string *k_enchase, *k_chuantou_item;
		int i;
		string name;

		mapping chuantou_item = ([
			"�׻�֮��"       : 100,
			"�׻ơ�ս��"      : 100,
			"�׻ơ���������"  : 100,
			"��Ů�����"      : 100,
			"��Ů��ʴ"        : 200,
		]);

		total = 0;

		total = me->query_temp("apply/chuantou");

		enchase = item->query("enchase");
		if (! mapp(enchase))return total;

		k_enchase = keys(enchase);

		if (! sizeof(k_enchase))return total;

		k_chuantou_item = keys(chuantou_item);

		for (i = 0; i < sizeof(k_enchase); i ++ )
		{
			name = enchase[k_enchase[i]]["name"];
			if (member_array(name, k_chuantou_item) != -1)
			{	
				  total = total + chuantou_item[name];	
			}
		}
		
		return total;
}

// ������Ƕ��Ʒ����Ч
public void do_enchase_attack(object item, object me, object victim, int damage)
{
	mapping enchase;
	int i_en, i, i_temp, j;
	string item_type, ran_item_enchase, s_temp;
	string ran_enchase_affect;

	string *k_enchase, *k_affect_list;
	mapping affect_list;
	string ran_affect;
	int i_ef;

	int ef_point, ef_ran, n_ef;
	int ran_result;
	string msg;

	object shenlong; // �̺�����

	mapping list = ([
		"��ħ������"   :  ([
					"suck_neili" : (["ran"    :  1 + random(3),
                                     "point"  :  30 + random(21)]),
		]),
		"��ħ���λ�"   :  ([
					"add_damage" : (["ran"    :  1 + random(3),
                                     "point"  :  30 + random(21)]),
		]),
		"��ħ����ɷ"   :  ([
					"suck_qi"    : (["ran"    :  1 + random(3),
                                     "point"  :  10 + random(21)]),
		]),
		"��ħ������"   :  ([
					"add_wound"  : (["ran"    :  1 + random(3),
                                     "point"  :  30 + random(21)]),
		]),
		"���¡�����"   :  ([
					"busy"  :      (["ran"    :  2 + random(2),
                                     "point"  :  2 + random(2)]),
		]),
		"���¡�����"   :  ([
					"add_damage"  : (["ran"   :  2 + random(2),
                                      "point" :  30 + random(21)]),
		]),
		"���¡���ϼ"   :  ([
					"jing_wound"  : (["ran"   :  1 + random(3),
                                      "point" :  10 + random(11)]),
		]),
		"���¡�ʥ��"   :  ([
					"suck_neili"  : (["ran"   :  2 + random(2),
                                      "point" :  50]),
		]),
		"�콿����ħ"   :  ([
					"add_wound"  : (["ran"    :  2 + random(2),
                                     "point"  :  50]),
		]),
		"�콿������"   :  ([
					"add_damage"  : (["ran"   :  3 + random(3),
                                      "point" :  50]),
		]),
		"�콿������"   :  ([
					"jing_wound"  : (["ran"   :  2 + random(2),
                                      "point" :  15 + random(6)]),
		]),
		"��Ρ�����"   :  ([
					"suck_qi"    : (["ran"    :  2 + random(2),
                                     "point"  :  30]),
		]),
		"�ֻء�����"   :  ([
					"poison_lianyu"    : ([ "ran"    :  2 + random(2),
                                            "point"  :  me->query_temp("apply/damage")]),
		]),
		"�ֻء�����"   :  ([
					"suck_neili" : (["ran"    :  3 + random(3),
                                     "point"  :  50 + random(31)]),
		]),
		"�ֻء�����"   :  ([
					"add_wound"  : (["ran"    :  3 + random(3),
                                     "point"  :  50 + random(31)]),
		]),
		"�ֻء��һ�"   :  ([
					"no_exert"   : (["ran"    :  2 + random(2),
                                     "point"  :  10 + random(6)]),
		]),
		"�ֻء��þ�"   :  ([
					"no_perform"   : (["ran"    :  2 + random(2),
                                       "point"  :  10 + random(6)]),
		]),
		"�ֻء�����"   :  ([ // �ر��
					"lunhui-chongsheng" : (["ran"    :  3 + random(3),
                                            "point"  :  0]),
		]),
		"�ֻء�����"   :  ([ // �ر�� ����������
					"unconcious" : (["ran"    :  1,
                                     "point"  :  0]),
		]),
		
		"�׻�֮��"   :   ([ // ���ָ�����Ч
					"suck_neili" : (["ran"    :  5,
                                     "point"  :  150]),
					"suck_qi"    : (["ran"    :  5,
                                     "point"  :  150]),
		]),
		"��Ů֮��"   :   ([ // ���ָ�����Ч
					"suck_neili" : (["ran"    :  5,
                                     "point"  :  100]),
					"suck_qi"    : (["ran"    :  5,
                                     "point"  :  100]),
					"reduce_def" :(["ran"   :  5, // ����Է������ȼ�1
						            "point" :  100]),
					"reduce_dam" :(["ran"   :  5, // ����Է��˺��ȼ�1
						            "point" :  100]),
		]),
		"�׻ơ���������":  ([
					"jing_wound"  : (["ran"   :  3 + random(3),
                                      "point" :  50 + random(31)]),
					"busy"  :       (["ran"    :  5,
                                      "point"  :  5]),
		]),		
		"�׻ơ���ɫ����":   ([ // ���ָ�����Ч
					"suck_neili" : (["ran"    :  5,
                                     "point"  :  100]),
					"suck_qi"    : (["ran"    :  5,
                                     "point"  :  100]),
					"busy"  :       (["ran"    :  5,
                                      "point"  :  5]),
					"no_exert"   : (["ran"    :  3,
                                     "point"  :  15]),
					"no_perform"   : (["ran"    :  3,
                                       "point"  :  15]),
		]),		
		"�׻ơ�ս��":  ([ // �ر�� ����������
					"unconcious" : (["ran"    :  2,
                                     "point"  :  0]),
					"add_damage"  : (["ran"   :  5,
                                      "point" :  200]),
		]),		
		"��Ů���̺�����":  ([ // �ر�� ���ٻ�����
					"summon_shenlong": (["ran"   :  5,
                                         "point" :  0]),
					"add_damage"  : (["ran"   :  5,
                                      "point" :  200]),					
		]),
		"��Ů�����"   :  ([
					"add_wound"  : (["ran"   :  3 + random(3),
                                      "point" :  100 + random(101)]),
					"jing_wound" : (["ran"   :  3 + random(3),
                                      "point" :  35 + random(26)]),
		]),
		"��Ů��ʴ":       ([
					"add_damage"  : (["ran"   :  3,
                                      "point" :  300]),					
		]),
	]);


    // �������������⹥������
	do_neck_attack(me, victim);

	// ���ӻ������⹥��Ч��
	do_wrists_attack(me, victim, "");

    // ������������򷵻�
	if (! item->is_item_make())return;

	if (item->query("skill_type"))item_type = "weapon";
	if (item->query("armor_type") == "hands")item_type = "weapon";

    // ���Ǳ����򷵻�
	if (item_type != "weapon")return;

	// û����Ƕ�򷵻�
	enchase = item->query("enchase");
	
	if (! mapp(enchase))return;
	i_en = sizeof(enchase);
	if (! i_en)return;

	// ���ʼ��� ƽ��?% + �����ۼ�%
	// ͬһʱ�����ѡȡһ����Ч
	k_enchase = keys(enchase);

	// ���Ӵ�͸��Ч
	victim->receive_wound("qi", chuantou_point(me, item), me);	

    // ������Ƕ����Ʒ�����ѡ��һ��
	ran_item_enchase = enchase[k_enchase[random(i_en)]]["name"];

	// ��ѡȡ����Ʒ�����ѡ��һ����Ч
	affect_list = list[ran_item_enchase];
	if (! affect_list)return;

	k_affect_list = keys(affect_list);

	i_ef = sizeof(k_affect_list);
	if (! i_ef)return;

	ran_affect = k_affect_list[random(i_ef)];

	// ��Чѡȡ�ú��������Ч���ʼ�������ʱ��ȣ�
	// ���ʼ��� ƽ��?% + �����ۼ�%
	// �������㣬��ǰ��ȡ�������Ƕ��Ʒ�ĸ���Ч����
	
	// �ȼ�������
	ef_point = list[ran_item_enchase][ran_affect]["point"];

	// ���㼸��
	// �ȼ��㼸���ܺͼ�����Ч����
	n_ef = 0;
	ef_ran = 0;
	for (i = 0; i < i_en; i ++)
	{
		// �ֱ����λ������Ƕ����Ʒ
		s_temp = enchase[k_enchase[i]]["name"];

		// ���Ч���������޸���Ƕ��Ʒ������
		if (member_array(s_temp,keys(list)) == -1)continue;

		// �������Ƕ��Ʒ���ڴ���Ч
		if (mapp(list[s_temp][ran_affect]))
		{
			n_ef += 1;
			ef_ran += list[s_temp][ran_affect]["ran"];
		}
	}

	// �õ�������ļ���
	if (n_ef <= 0)ran_result = 3;  //�Է���һ
	else
		ran_result = ef_ran / n_ef + n_ef - 1;

	// �����Ƕ�˱�ʯ--���۶�ħ�����1%��2%�ļ���
	for (j = 0; j < sizeof(k_enchase); j ++ )
	{
		if (enchase[k_enchase[j]]["name"] == "���۶�ħ")
		{
			ran_result = ran_result + 1 + random(2);
		}
	}

	// ����ж��Ƿ񷢳�����Ч
	if (1 + random(100) > ran_result)return;
	
	message_combatd(HIG + "$N" HIG "�ġ�" + ran_item_enchase + "������һ������Ĺ�â��\n" NOR, me);

	// ������Ч
	switch(ran_affect)
	{
		case "suck_neili":
			if (victim->query("neili") < ef_point)return;

			msg = HIY "��" + ran_item_enchase + "����ȡ��" + victim->name() + HIY +
                              "��������" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);			
			victim->add("neili", -1 * ef_point);
			if (victim->query("neili") < 0)victim->set("neili", 0);
			me->add("neili", ef_point);
			if (me->query("neili") > me->query("max_neili"))
				me->set("neili", me->query("max_neili"));

			return;

		case "suck_qi":
			if (victim->query("qi") < ef_point)return;

			msg = HIY "��" + ran_item_enchase + "����ȡ��" + victim->name() + HIY +
                              "����Ѫ��" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);
			victim->receive_damage("qi", ef_point, me);
			if (victim->query("qi") < 0)victim->set("qi", 0);
			me->add("qi", ef_point);
			if (me->query("qi") > me->query("eff_qi"))
				me->set("qi", me->query("eff_qi"));

			return;

		case "add_damage":
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "���˺���" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);
			victim->receive_damage("qi", ef_point, me);

			return;

		case "add_wound":
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "���˺����ޣ�" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);
			victim->receive_wound("qi", ef_point, me);

			return;
		
		case "busy":
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "��æ��Ч����" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);
			if (! victim->is_busy())victim->start_busy(ef_point);

			return;

		case "no_exert":
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "����Ϣ���ң�" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);
			if (! victim->query_temp("no_exert"))victim->set_temp("no_exert", 1);
			tell_object(victim, HIM "�㱻" + me->name() + "��" + HIY + ran_item_enchase + HIM "���У��پ���Ϣ���ң�\n" NOR);

			// ����Ч��
			call_out("remove_effect", ef_point, victim, "��Ϣ����");
			return;

		case "no_perform":
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "��������ɢ��" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);
			if (! victim->query_temp("no_perform"))victim->set_temp("no_perform", 1);
			tell_object(victim, HIM "�㱻" + me->name() + "��" + HIY + ran_item_enchase + HIM "���У��پ�������ɢ��\n" NOR);

			// ����Ч��
			call_out("remove_effect", ef_point, victim, "������ɢ");
			return;		

        // �ֻء�����������Ч��
		// ����ս��
		case "lunhui-chongsheng":
			if (victim->query_temp("lunhui-chongsheng/xueruo"))return;

			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "������ս�����������������رܡ����и�30%��\n" NOR;
			
			tell_object(me, msg);
			
			victim->set_temp("lunhui-chongsheng/xueruo", 1);
			victim->set_temp("apply/damage", victim->query_temp("apply/damage") / 10 * 7);
			victim->set_temp("apply/unarmed_damage", victim->query_temp("apply/unarmed_damage") / 10 * 7);
			victim->set_temp("apply/defense", victim->query_temp("apply/defense") / 10 * 7);
			victim->set_temp("apply/attack", victim->query_temp("apply/attack") / 10 * 7);

			return;

        // ����һ��
		case "unconcious":
			if (userp(victim))return;
						
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "������һ����\n" NOR;
			
			tell_object(me, msg);

			victim->receive_wound("qi", 1, me);
			victim->unconcious(me);

			return;
		
		// �������
		case "reduce_def":
			if (userp(victim))return;
			
			if (victim->query_temp("apply/defense") <= 0)return;
						
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "�����������" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);

			if (victim->query_temp("apply/defense") < ef_point)
					victim->set_temp("apply/defense", 0);
			else
					victim->add_temp("apply/defense", -1 * ef_point);

			return;
			
		// �����˺�
		case "reduce_dam":
			if (userp(victim))return;
						
			msg = HIR "��" + ran_item_enchase + "��׷�ӡ�" + victim->name() + HIY +
                              "�������˺���" + sprintf("%d", ef_point) + "��\n" NOR;
			tell_object(me, msg);

			if (victim->query_temp("apply/damage") < ef_point)
					victim->set_temp("apply/damage", 0);
			else
					victim->add_temp("apply/damage", -1 * ef_point);

			if (victim->query_temp("apply/unarmed_damage") < ef_point)
					victim->set_temp("apply/unarmed_damage", 0);
			else
					victim->add_temp("apply/unarmed_damage", -1 * ef_point);

			return;

        // �ٻ�����
		case "summon_shenlong":

			if (time() - me->query_temp("last_summon_shenlong") < 180)return;

			if (! victim)return;

			msg = HIG "��" + ran_item_enchase + "����â���ɣ�һ�����������Ź�â���������\n" NOR;
			message_combatd(msg, me);
			
			shenlong = new("/kungfu/class/misc/shenlong");
			
			if (! objectp(shenlong))return;
						
			me->set_temp("last_summon_shenlong", time());

			shenlong->move(environment(me));
			shenlong->set("long", HIC + me->name() + "�ı�����Ů���̺��������������ٻ��������������ޱȡ�\n" NOR);
			shenlong->kill_ob(victim);
			shenlong->force_me("guard " + me->query("id") );

			return;

	}

	return;
}

// ������Ч
void remove_effect(object victim, string eff)
{

	if (! objectp(victim))return;
	
	switch(eff)
	{
		case "��Ϣ����":
			victim->delete_temp("no_exert");			
			return;

		case "������ɢ":
			victim->delete_temp("no_perform");
		    return;
	}
	return;
}

// �����;ö�
void reduce_consistence(object item, object me, object victim, int damage)
{
        int st;
        int con;
		int i, en_num, flag, cur_firm;
		mapping enchases;
		string* en_keys;

        // ������Ƕ��Ʒ������Ч	
		if (! objectp(item))return;
		if (item->query("armor_type") != "neck" && item->query("armor_type") != "armor")
			do_enchase_attack(item, me, victim, damage);

        st = item->query("stable");

        if (st < 2)
                return;

        con = item->query("consistence");

		// ������Ƕ��Ʒ���;ö�
		flag = 0;
        enchases = item->query("enchase");
        en_num = sizeof(enchases);
        if (en_num && mapp(enchases))
		{
		en_keys = keys(enchases);
		for (i = 0; i < en_num; i ++)
		{
			cur_firm = item->query("enchase/" + en_keys[i] + "/cur_firm");
			if (enchases[en_keys[i]]["cur_firm"] == 100)continue;
			if (random(100) >= 20)/*random(st) > ((100 - cur_firm / 2) / 10) )*/continue;
			if (item->add("enchase/" + en_keys[i] + "/cur_firm", -1) > 0)
				continue;
			flag = 1;
        	if (environment(item))
			{
             			tell_object(environment(item), HIG "���" +
                         	            item->query("enchase/" + en_keys[i] + "/name") + HIG "�Ѿ��������ˡ�\n" NOR);

			}
			item->set("enchase/" + en_keys[i] + "/cur_firm", 0);
                        item->delete("enchase/" + en_keys[i]);
			item->save();

		}
		if (flag)
		{
			tell_object(environment(item), HIM "ͻȻ�䣬" + item->name() + HIM "�����ȥ��\n" NOR);
			destruct(item);
			return;
		}
	}

        // ����쾧���Ƶ���������ĥ��
        if (item->query("material") == "tian jing")
                return;

        if (random(st) > (100 - con) / 13 || random(2))
                return;

        if (item->add("consistence", -1) > 0)
                return;

        item->set("consistence", 0);

        if (environment(item))
                tell_object(environment(item), HIG "���" +
                            item->name() + HIG "�Ѿ��������ˡ�\n" NOR);

        item->unequip();
}

// ������Ʒȱʡ���;ö���Ϣ
void equip_setup(object item)
{
        int stable;
        mapping dbase;

        dbase = item->query_entire_dbase();
        if (undefinedp(dbase["consistence"]))
                dbase["consistence"] = 100;

        if (undefinedp(item->query("stable")))
        {
                switch (item->query("material"))
                {
                case "cloth":
                        // ��Զ������
                        stable = 0;
                        break;
                case "paper":
                        stable = 3;
                        item->set("no_repair", "�ⶫ���ҿ�û������\n");
                        break;
                case "bone":
                        stable = 8;
                        item->set("no_repear", "����������ɱ�����Ѱ���ġ�\n");
                        break;
                case "bamboo":
                case "wood":
                        stable = 10;
                        item->set("no_repair", "�ⶫ����զ����\n");
                        break;
                case "copper":
                        stable = 40;
                        break;
                case "silver":
                        stable = 40;
                        break;
                case "iron":
                        stable = 45;
                        break;
                case "gold":
                        stable = 50;
                        break;
                case "steel":
                        stable = 75;
                        break;
                case "stone":
                        stable = 80;
                        break;
                default:
                        stable = 100;
                        break;
                }

                if (! item->is_item_make())
                        stable /= 2;

                item->set("stable", stable);
        }
}


// �ⲿ�������� /clone/fam/item/moye-shengfu.c
// д���ļ�
public int extern_write_file(string str_file, string msg, int flag)
{
	if (! write_file(str_file, msg, flag))return 0;

	return 1;
}
2371    // ����/feature/itemmake.c�ĵ��ã�ǿ���ȼ�������Ӧ����ǶЧ�� 
2372    //public int qianghua_enchase_points("WEAPON", enchase_points, query("qh_level")) 
2373    public int qianghua_enchase_points(string stype, int points, int qh_level) 
2374    { 
2375            int i; 
2376            if (points <= 0)return points; 
2377            if (qh_level < 1)return points; 
2378             
2379            switch(stype) 
2380            { 
2381            case "weapon": // ����ÿ��ǿ������x% 
2382                    for (i = 0; i < qh_level; i ++) 
2383                            points = points + points / 10; 
2384                    return points; 
2385            break; 
2386     
2387            case "wrists": // ����ÿ������x% 
2388                    points *= 300; // ���������sizeof(��Ƕ) 
2389                    for (i = 0; i < qh_level; i ++) 
2390                            points = points + points * 3 / 50; 
2391                    return points; 
2392            break; 
2393     
2394            case "surcoat": // ����ÿ������x%������Ϊ��Ƕ����*300 
2395                    points *= 300; // ���紫�����sizeof(��Ƕ�� 
2396                    for (i = 0; i < qh_level; i ++) 
2397                            points = points + points / 10; 
2398                    return points; 
2399            break; 
2400     
2401            default: 
2402                    return points; 
2403            break; 
2404            } 
2405     
2406            return points; 
2407    } 
2408     
2409    // �����ⲿ���ã�ǿ��װ���ȼ� 
2410    public int qianghua_object(object me, object obj) 
2411    { 
2412            string *can_qianghua, str_log; 
2413            int qh_level, qhobj_count, suc_points; 
2414            object qhobj; 
2415            mapping suc_points_list; 
2416             
2417            // ����ǿ���ĵ��� 
2418            can_qianghua = ({ 
2419                    "hands", "surcoat", "wrists", "head", 
2420            }); 
2421    /* 
2422            suc_points_list = ([ 
2423                    "0" :  80,  // ����0->1 
2424                    "1" :  70, 
2425                    "2" :  50, 
2426                    "3" :  30, 
2427                    "4" :  10, 
2428                    "5" :  5,   // 5��6��ʱ��ʧ�ܾͻή��4�������涼�ǽ���4�� 
2429                    "6" :  4,   
2430                    "7" :  3, 
2431                    "8" :  2, 
2432                    "9" :  1, 
2433            ]); 
2434    */ 
2435            suc_points_list = ([ 
2436                    "0" :  80,  // ����0->1 
2437                    "1" :  70, 
2438                    "2" :  60, 
2439                    "3" :  50, 
2440                    "4" :  45, 
2441                    "5" :  40,   // 5��6��ʱ��ʧ�ܾͻή��4�������涼�ǽ���4�� 
2442                    "6" :  35,   
2443                    "7" :  20, 
2444                    "8" :  22, 
2445                    "9" :  12, 
2446            ]); 
2447                     
2448            str_log = ctime(time()); // ��¼LOG 
2449             
2450            if (! objectp(me) || ! objectp(obj)) 
2451                    return notify_fail("�������⣬��ʱ����ǿ����\n"); 
2452             
2453            // �������������ǿ�� 
2454            if (! obj->is_item_make()) 
2455                    return notify_fail("ֻ��������Ʒ����ǿ����\n"); 
2456             
2457            // �����Լ��ĵ��߲���ǿ�� 
2458            if (obj->item_owner() != me->query("id")) 
2459                    return notify_fail("������������װ���ɣ�����ǿ����\n"); 
2460     
2461            // ֻ���ŵ�ǿ������ 
2462            if (! obj->query("skill_type") && // ���� 
2463                  member_array(obj->query("armor_type"), can_qianghua) == -1) 
2464                    return notify_fail("�����͵�װ����ʱ��δ����ǿ������������ļ���\n"); 
2465     
2466            // û����Ƕ��Ϣ����ǿ�� 
2467            if (! sizeof(obj->query("enchase"))) 
2468                    return notify_fail("���װ���ƺ���û����Ƕ���κζ�������ʱ����ǿ����\n"); 
2469             
2470            qh_level = obj->query("qh_level"); 
2471            // ǿ���ȼ����˲���ǿ�� 
2472            if (qh_level >= 10) 
2473                    return notify_fail("��װ��ǿ���ȼ�������\n"); 
2474     
2475            // ��Ҫ����ǿ����Ʒ 
2476            if (! objectp(qhobj = present("tie ying", me))) 
2477                    return notify_fail("������û����Ӣʯ������ǿ��װ��!\n"); 
2478             
2479            // ǿ����Ʒ�Ƿ���ȷ 
2480            if (! qhobj->query("qhobj")) 
2481                    return notify_fail("������û����Ӣʯ������ǿ��װ����\n"); 
2482     
2483            qhobj_count = qh_level - 3; 
2484            if (qhobj_count < 1)qhobj_count = 1; 
2485            // �����Ƿ��㹻 
2486            if (qhobj->query_amount() < qhobj_count) 
2487                    return notify_fail("������û���㹻����Ӣʯ����ǰǿ����Ҫ" +  
2488                                       sprintf("%d", qhobj_count) + "����\n"); 
2489     
2490            // ��ʼǿ�� 
2491            str_log += " " + obj->name() + "(" + obj->query("id") + ") of " + obj->item_owner() + NOR " ǿ����"; 
2492            // ����ɹ�����suc_points 
2493            suc_points = suc_points_list[sprintf("%d", qh_level)]; 
2494            str_log += sprintf("�����ɹ��ʣ�%d��", suc_points); 
2495            // ���װ���гɹ��ʼӳ������� 
2496            if (obj->query("suc_points_add")) 
2497                    suc_points += obj->query("suc_points_add"); 
2498            str_log += sprintf("�ӳɺ�ɹ��ʣ�%d��", suc_points); 
2499            // �۵���Ʒ 
2500            qhobj->add_amount(-1*qhobj_count); 
2501            if (qhobj->query_amount() < 1)destruct(qhobj); 
2502     
2503            // ������ӳɹ��� 
2504            if (obj->query("suc_points_add")) 
2505            { 
2506                    obj->delete("suc_points_add"); 
2507                    obj->save(); 
2508            } 
2509             
2510            // �ȼ�����6ʱ���ɹ��ʽ���5% 
2511            if (qh_level > 6)suc_points -= 5; 
2512            // 9��ʱ���ټ�2% 
2513            if (qh_level == 9)suc_points -= 2; 
2514             
2515            // �Ƿ�ʧ�� 
2516            if (random(100) >= suc_points) // ʧ�� 
2517            { 
2518                    // ��ǰ�ȼ�������4����ʧ����ʾ���ؼ��� 
2519                    if (qh_level <= 4) 
2520                    { 
2521                            str_log += sprintf("ǿ��ʧ�ܵȼ�Ϊ��%d��\n", qh_level); 
2522                            log_file("0װ��ǿ��", str_log); 
2523                            return notify_fail("���ź���ǿ��ʧ���ˣ�\n"); 
2524                    } 
2525                    else // ����4����ʧ�ܾͻᵹ�˵�4�� 
2526                    { 
2527                            // ����з�ֹʧ�ܵ��� 
2528                            if (obj->query("no_reduce_level")) 
2529                            { 
2530                                    obj->delete("no_reduce_level"); 
2531                                    obj->save(); 
2532                                    str_log += sprintf("ǿ��ʧ�ܵȼ�Ϊ��%d(ǿ���ȼ�δ��ʧ����\n", qh_level); 
2533                                    log_file("0װ��ǿ��", str_log); 
2534                                    return notify_fail("���ź���ǿ��ʧ����(ǿ���ȼ�δ��ʧ����\n"); 
2535                            } 
2536                            else 
2537                            { 
2538                                    obj->set("qh_level", 4); 
2539                                    obj->save(); 
2540                                    str_log += sprintf("ǿ��ʧ�ܵȼ�Ϊ��%d(ǿ���ȼ���Ϊ4������\n", qh_level); 
2541                                    log_file("0װ��ǿ��", str_log); 
2542                                    write(HIG "��о�" + obj->name() + HIG "ͻȻ�����ȥ���ƺ������˲��������ı仯��\n" NOR); 
2543                                    //destruct(obj); 
2544                                     
2545                                    return notify_fail(HIR "���ź���ǿ��ʧ����(ǿ���ȼ���Ϊ4������\n" NOR); 
2546                            } 
2547                    } 
2548            } 
2549            else // �ɹ������� 
2550            { 
2551                    obj->set("qh_level", qh_level+1); 
2552                    obj->save(); 
2553                    write(HIG "ǿ���ɹ���" + obj->name() + HIG "ǿ��������" + 
2554                          sprintf(HIY "%d" HIG, obj->query("qh_level")) + "����\n" NOR); 
2555                    str_log += sprintf("ǿ���ɹ����ȼ���%d������%d\n", qh_level, obj->query("qh_level")); 
2556                    log_file("0װ��ǿ��", str_log); 
2557                     
2558                    // ȫ��ͨ�� 
2559                    if (obj->query("qh_level") >= 6) 
2560                    { 
2561                            CHANNEL_D->do_channel(this_object(), "chat",  
2562                                                  "��˵" + HIY + me->name() + HIM "��" + obj->name() +  
2563                                                  HIM "ǿ����" HIR + sprintf("%d", obj->query("qh_level")) +  
2564                                                  HIM "����\n" NOR); 
2565     
2566                    } 
2567                    if (obj->query("qh_level") == 10) 
2568                    { 
2569                            CHANNEL_D->do_channel(this_object(), "chat",  
2570                                                  HIR "��ϲ" + HIY + me->name() + HIR "��" + obj->name() +  
2571                                                  HIR "ǿ��Ϊ���������\n" NOR); 
2572                    } 
2573                    write(HIG "��о�" + obj->name() + HIG "ͻȻ�����ȥ���ƺ������˲��������ı仯��\n" NOR); 
2574                    //destruct(obj); 
2575                    return 1; 
2576            } 
2577    } 
2578     
2579    // ����/inherit/char/dream_npc���� 
2580    // �ж��Ƿ������Ӣʯ���ⲿ���Ƽ��ʣ�������ʱ���� 
2581    public int drop_tieyingshi(object me) 
2582    { 
2583            int ran; 
2584             
2585            if (! objectp(me))return 0; 
2586     
2587            if (me->query("service/jiutoushe")) 
2588            { 
2589                    ran = 20000; 
2590            } 
2591            else 
2592            { 
2593                    if (! MEMBER_D->is_valib_member(me->query("id")))ran = 1200000; // �ǻ�Ա���ʼ��� 
2594                    else 
2595                            ran = 150000; 
2596            } 
2597            /* 
2598            if (random(ran) == 1) 
2599            { 
2600                    // ��¼ÿ����Ӣ�������� 
2601                    total_tieying += 1; 
2602                    if (total_tieying % 100 == 0) 
2603                    { 
2604                            DB_D->set_data("tieying_drop/" + sprintf("%d", time() / 86400), total_tieying); 
2605                    } 
2606                     
2607                    // ����1����� 
2608                    return 1; 
2609            } 
2610            */ 
2611            return 0; 
2612    } 
