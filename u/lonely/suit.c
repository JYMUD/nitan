// special

#include <ansi.h>

#define TAOZHUANG_D   "/adm/daemons/taozhuangd"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string tzx, result, *keys_tzlist;
	object ob;
	int i;
	mapping tz;
	string *keys_tz, str_color;

	mapping tzlist = ([
		"head"       :  "ͷ��",
		"waist"      :  "����",
		"boots"      :  "ѥ��",
		"surcoat"    :  "����",//
		"armor"      :  "ս��",
		"cloth"      :  "ս��",
		"wrists"     :  "����",
		"neck"       :  "����",
		"rings"      :  "��ָ",
		"myheart"    :  "���",
		"myheart2"   :  "�ҷ�",
	]);

	if (! objectp(me))return 0;

	if (! arg)arg = "show";

	keys_tzlist = keys(tzlist);

	// һ���Դ���һ��
	if (arg == "wear")
	{
		tz = me->query("tzlist");

		if (! sizeof(tz))
			return notify_fail("�㻹û���Զ�����װ�б������ help taozhuang ˵����\n");
		/*
		if (sizeof(tz) < 12 && ! wizardp(me)) // ��ʦ���Ե�ʱ��ɲ��ô�12��
			return notify_fail("�㻹δ���12����װ�����Ķ��壬��ʹ�� suit show �鿴��\n");
*/
		keys_tz = keys(tz);
		for (i = 0; i < sizeof(keys_tz); i ++)
		{
			if (! objectp(ob = present(tz[keys_tz[i]], me)))
			{
				// δ�����ϣ������ٻ�
				__DIR__"summon"->main(me, tz[keys_tz[i]]);
				// �ٻ��������û������ֹ
				if (! objectp(ob = present(tz[keys_tz[i]], me)))
					return notify_fail("δ�ҵ�װ�� " + tz[keys_tz[i]] + "��������ֹ��\n");
			}

			if (ob->query("equipped"))continue;


			// װ�����⴦��
			if (ob->query("skill_type"))
			{
				"/cmds/std/wield"->do_wield(me, ob);
			}
			else
			{
				"/cmds/std/wear"->do_wear(me, ob);
			}
		}

		return notify_fail("OK.\n");
	}


	// ��ʾ�Ѽ������װ�б�
	if (arg == "show")
	{
		result = HIG "-----------�Զ�����װ�б�-------------\n" NOR;

		if (! sizeof(me->query("tzlist")))
			return notify_fail("�㻹û���Զ�����װ�б������ help taozhuang ˵����\n");

		if (sizeof(me->query("tzlist/weapon")))
		{
			ob = present(me->query("tzlist/weapon"), me);
			if (objectp(ob))
			{
				str_color = ob->query("equipped") ? HIM : HIC;
				result += str_color + "������ " + HIC + ob->name() + HIC + "��" +
		                 	  TAOZHUANG_D->taozhuang_name(ob->query("taozhuang")) + HIC "��\n" NOR;
		        }
		        else
		        	result += HIC "������ " NOR + WHT + me->query("tzlist/weapon") + "\n" NOR;
		}
		else
		{
			result += HIC "������ " + NOR + WHT "----\n" NOR;
		}

		for (i = 0; i < sizeof(keys_tzlist); i ++)
		{
			if (sizeof(me->query("tzlist/" + keys_tzlist[i])))
			{
				ob = present(me->query("tzlist/" + keys_tzlist[i]), me);
				if (objectp(ob))
				{
					str_color = ob->query("equipped") ? HIM : HIC;
					result += str_color + tzlist[keys_tzlist[i]] + "�� " + HIC + ob->name() + HIC + "��" +
		                          	  TAOZHUANG_D->taozhuang_name(ob->query("taozhuang")) + HIC "��\n" NOR;
		                }
		                else
		                	result += HIC + tzlist[keys_tzlist[i]] + "�� " NOR + WHT +
		                	          me->query("tzlist/" + keys_tzlist[i]) + "\n" NOR;
			}
			else
			{
				result += HIC + tzlist[keys_tzlist[i]] + "�� " NOR + WHT + "----\n" NOR;
			}
		}
		result += HIG "-------------------------------------\n" NOR;
		result += HIW "װ��������Ϊ" HIM "�Ϻ�ɫ" HIW "�ı�ʾ��װ����" HIC "����ɫ" HIW "Ϊδװ����\n" NOR;
		result += HIY "ʹ��ָ�� suit add װ��id ����Զ�����װ�б�\n" NOR;
		result += HIR "ʹ��ָ�� suit wear �ɽ��Զ�����װ�б��ڵ��׼�����װ����\n" NOR;
		//result += HIY "ʹ��ָ�� suit remove װ��id ���Զ�����װ�б����Ƴ���װ����\n" NOR;
		write(result);
		return 1;
	}


	// ��ָ��װ��������װ�б�
	if (sscanf(arg, "add %s", tzx))
	{
		if (! objectp(ob = present(tzx, me)))
			return notify_fail("������û�����װ����\n");

		// �ж�װ���Ƿ������Լ�
		if (ob->item_owner() != me->query("id"))
			return notify_fail("������������������������ɣ�\n");

		// �ж��Ƿ�Ϊ12��װ���е�����
		if (ob->query("skill_type") || ob->query("armor_type") == "hands") // ����
		{
			me->set("tzlist/weapon", tzx);
			return notify_fail("����Զ�����װ�ɹ�����ʹ�� suit show �鿴��\n");
		}
		if (! ob->query("armor_type"))
			return notify_fail("�����Ʒ������װ�����ͣ�\n");

		if (member_array(ob->query("armor_type"), keys_tzlist) == -1)
			return notify_fail("�����Ʒ��������װ������\n");

		me->set("tzlist/" + ob->query("armor_type"), tzx);
		return notify_fail("����Զ�����װ�ɹ�����ʹ�� suit show �鿴��\n");
	}

	return TAOZHUANG_D->suit_special(me, arg);

}