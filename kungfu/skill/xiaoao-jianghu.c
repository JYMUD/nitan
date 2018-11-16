#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "chuixiao-jifa" ||
                                        usage == "tanqin-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("tanqin-jifa", 1) < 50 &&
            me->query_skill("chuixiao-jifa", 1) < 50)
                return notify_fail("��Ĵ����͵��ٵļ���ˮƽ��̫�������������˵�ɣ�\n");

        if (me->query_skill("tanqin-jifa", 1) < me->query_skill("qingxin-pushan", 1) &&
            me->query_skill("cuhixiao-jifa", 1) < me->query_skill("qingxin-pushan", 1))
                return notify_fail("�����ո����Ĵ����������ټ���֮ǰ�����޷����������Ц����������\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !objectp(ob=query_temp("handing", me)) || 
            ! ob->valid_as_qin() &&
            ! ob->valid_as_xiao())
                return notify_fail("�����ϼ�û���Ҳû���٣���ô��ϰ��\n");

        if( query("jing", me)<100 )
                return notify_fail("��ľ��񲻹��ã�û����ϰ�ˡ�\n");

        if( query("qi", me)<50 )
                return notify_fail("������ʵ����̫���ˣ��������ˡ�\n");

        me->receive_damage("jing", 60);
        me->receive_damage("qi", 40);

        return 1;
}

void do_effect(object me)
{
        object *obs;
        object ob;
        string type;
        string other;
        int amount;
        int lvl;
        int i;

        lvl = me->query_skill("xiaoao-jianghu", 1);

        if (lvl < 100)
                return;

        if (previous_object() == find_object(SKILL_D("chuixiao-jifa")))
        {
                type = "xajh/xiao";
                other = "xajh/qin";
        } else
        if (previous_object() == find_object(SKILL_D("tanqin-jifa")))
        {
                type = "xajh/qin";
                other = "xajh/qin";
        } else
                return;

        // special effort
        obs = all_inventory(environment(me));
        for (i = 0; i < sizeof(obs); i++)
        {
                ob = obs[i];
                if (ob == me || ! ob->is_character() || ! living(ob))
                        continue;

                if( query_temp("xajh/powerup", ob) || 
                    time()-query_temp(other, ob)>30 || 
                    !stringp(query_temp("xajh/player", ob)) || 
                    query_temp("xajh/player", ob) == query("id", me) )
                {
                        set_temp(type, time(), ob);
                        set_temp("xajh/player",query("id",  me), ob);
                        set_temp("xajh/player_name", me->name(), ob);
                        message("visoin", HIG "������" + me->name() +
                                HIG "�����ӣ����÷ǳ��Ŀ���������\n" NOR, ob);
                } else
                {
                        // ˫�˺���
                        amount = lvl;
                        if (amount > ob->query_skill("force"))
                                amount = ob->query_skill("force");
                        amount /= 6;
                        delete_temp(other, ob);
                        delete_temp(type, ob);
                        addn_temp("apply/attack", amount, ob);
                        addn_temp("apply/dodge", amount, ob);
                        set_temp("xajh/powerup", 1, ob);
                
                        call_out("remove_effect", lvl / 2, ob, amount);
                        message("vision", HIG "������" + me->name() +
                                HIG"��"+query_temp("xajh/player_name", ob)+
                                "�����Ц��������ֻ�����ĳ����ȣ�������������\n" NOR, ob);
                        delete_temp("xajh/player", ob);
                        delete_temp("xajh/player_name", ob);
                }
        }
}

void remove_effect(object me, int amount)
{
        if (! objectp(me))
                return;
        if( query_temp("xajh/powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                delete_temp("xajh/powerup", me);
                tell_object(me, "������齥����ƽϢ������\n");
        }
}