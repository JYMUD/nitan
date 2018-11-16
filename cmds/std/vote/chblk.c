// vote chblk

#include <ansi.h>
inherit F_CONDITION;

int clear_vote(object me);
int vote(object me, object victim)
{
        string reason;  // vote for what?
        int vv;                // valid voter numbers
        int vc;         // vote count;
        int df;
        string *juser;
        string *jip;
        string my_id, my_ip;
        
        if (! interactive(me))
                return 0;

        if (me == victim)
        {
                addn("vote/abuse", 1, me);
                  return notify_fail("�㲻�ǿ���Ц�ɣ����ı�������Ȩ��\n");
        }

        if (victim->query_condition("vote_clear") &&
            (reason=query("vote/reason", victim)) && reason != "chblk" )
                  return notify_fail("Ҫ�ѵ�ǰ�ı������Ժ�ſ������µĶ��顣\n");

        if( query("chblk_on", victim) )
                  return notify_fail(victim->name() + "��Ƶ���Ѿ��ǹرյ��ˡ�\n");

        if (! victim->query_condition("vote_clear"))
        {
                set("vote/count", 0, victim);
                reason = 0;
        }  

        if (reason != "chblk")
        {
                set("vote/reason", "chblk", victim);
                delete("vote/juror", victim);
        }

        my_id=query("id", me);
        my_ip = query_ip_number(me);

        // dont allow me to vote twice for the same issue
        if( !arrayp(juser=query("vote/juror/user", victim)) )
                juser = ({ });

        if( !arrayp(jip=query("vote/juror/ip", victim)) )
                jip = ({ });  

        if (member_array(my_ip, jip) != -1)
                return notify_fail("�����ڵ�IP��ַ�Ѿ�����Ͷ��Ʊ�ˡ�\n");
        else
        if (member_array(my_id, juser) == -1) 
        {
                 set("vote/juror/user", juser+({my_id}), victim);
                set("vote/juror/ip", jip+({my_ip}), victim);
        } else
        {
                addn("vote/abuse", 1, me);
                 return notify_fail("һ��һƱ�����ñ��Ȩ��Ҫ�ܳͷ��ģ�\n");
        }

        vv = (int) ("/cmds/std/vote")->valid_voters(me) / 2;
        if (vv < 3) vv = 3;
        if (vv > 10) vv = 10;
        if( query("mud_age", victim)<86400)vv=3;
        vc = addn("vote/count", 1, victim);
        df = vv - vc;

        if (df >= 1)
        {
                message("vision", HIG "�����񹫾���" + me->name(1) + "ͶƱ�ر�" + victim->name(1) +
                                  "�Ľ�̸Ƶ��������" + sprintf("%d", df) + "Ʊ��\n" NOR, all_interactive());
                victim->apply_condition("vote_clear", 10);
                return 1;
        } else
        {
                message("vision", HIG "�����񹫾���" + me->name(1) + "ͶƱ�ر�" + victim->name(1) +
                                  "�Ľ�̸Ƶ����" + victim->name(1) + "�Ľ�̸Ƶ�����ر��ˣ�\n" NOR, all_interactive());
        }                        

        victim->clear_condition("vote_clear");
        delete("vote/count", victim);
        delete("vote/reason", victim);
        delete("vote/juror", victim);
        set("chblk_on", 1, victim);

        return 1;
}
