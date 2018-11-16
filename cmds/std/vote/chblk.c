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
                  return notify_fail("你不是开玩笑吧？当心被剥夺表决权！\n");
        }

        if (victim->query_condition("vote_clear") &&
            (reason=query("vote/reason", victim)) && reason != "chblk" )
                  return notify_fail("要把当前的表决完成以后才可以提新的动议。\n");

        if( query("chblk_on", victim) )
                  return notify_fail(victim->name() + "的频道已经是关闭的了。\n");

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
                return notify_fail("你所在的IP地址已经有人投过票了。\n");
        else
        if (member_array(my_id, juser) == -1) 
        {
                 set("vote/juror/user", juser+({my_id}), victim);
                set("vote/juror/ip", jip+({my_ip}), victim);
        } else
        {
                addn("vote/abuse", 1, me);
                 return notify_fail("一人一票！滥用表决权是要受惩罚的！\n");
        }

        vv = (int) ("/cmds/std/vote")->valid_voters(me) / 2;
        if (vv < 3) vv = 3;
        if (vv > 10) vv = 10;
        if( query("mud_age", victim)<86400)vv=3;
        vc = addn("vote/count", 1, victim);
        df = vv - vc;

        if (df >= 1)
        {
                message("vision", HIG "【人民公决】" + me->name(1) + "投票关闭" + victim->name(1) +
                                  "的交谈频道，还差" + sprintf("%d", df) + "票。\n" NOR, all_interactive());
                victim->apply_condition("vote_clear", 10);
                return 1;
        } else
        {
                message("vision", HIG "【人民公决】" + me->name(1) + "投票关闭" + victim->name(1) +
                                  "的交谈频道。" + victim->name(1) + "的交谈频道被关闭了！\n" NOR, all_interactive());
        }                        

        victim->clear_condition("vote_clear");
        delete("vote/count", victim);
        delete("vote/reason", victim);
        delete("vote/juror", victim);
        set("chblk_on", 1, victim);

        return 1;
}
