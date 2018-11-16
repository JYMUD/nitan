// upgrade

#include <ansi.h>

inherit F_CLEAN_UP;

#define PERIOD          864
#define PERIOD_POT      20000
#define PERIOD_MAR      12000

int clossing(object me);
int halt_closing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;
        
        seteuid(getuid());
        where = environment(me);
        
        if (! arg)
               return notify_fail("��Ҫ�չ�����ʲô�书��\n");
        
        if (! me->query_skill(arg) || 
            file_size(SKILL_D(arg) + ".c") < 0)    
               return notify_fail("��Ҫ���е��书�����ڻ��㲻����书��\n");
        
        //if (! SKILL_D(arg)->is_invent_skill())
        if (me->query_skillo(arg, 1) < 4600 )
               return notify_fail("���" + to_chinese(arg) + "�����򻹲������޷�������COMBAT������\n");  
               
        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( !query("no_fight", where) )
                return notify_fail("������չ����У���̫��ȫ�ɣ�\n");

        if( !query("sleep_room", where) )
                return notify_fail("�����һ���ܹ���Ϣ�ĵط��չ����С�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");
                        
        if( query("potential", me)-query("learned_points", me)<1000000 )
                return notify_fail("���Ǳ�ܲ�����û���չ����С�\n");

        if( query("experience", me)<query("learned_experience", me)+600000 )
                return notify_fail("�����ڻ��۵�ʵս��ỹ̫�١�\n"); 
        
        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("�����ڵ���̫���ˣ��޷��������С�\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("�����ڵľ�̫���ˣ��޷��������С�\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("������������в��㣬����Ŀǰ������"
                                   "���г�ʱ��ıչ����С�\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("�����ڵ�����̫���ˣ��޷��������С�\n");

        message_vision("$N��ϥ���£���ʼڤ���˹����չ�����" + to_chinese(arg) + "��\n", me);
        set("startroom", base_name(where), me);
        set("doing", "invent", me);
        set("upgrade", arg, me);
        CLOSE_D->user_closed(me, "invent");
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("����ʦ%s(%s)��ʼ�չ���������%s��",
                              me->name(1),query("id", me),to_chinese(arg)));

        return 1;
}

int continue_uping(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me,HIR"\n������չ���������"+to_chinese(query("upgrade", me))+"...\n"NOR);
        return 1;
}

int closing(object me)
{
        int t;
        int tn;
        mixed pot, mar;
        int r;
        int exp_inc;
        string skill;
        
        skill=query("upgrade", me);
        pot=query("potential", me);
        mar=query("experience", me);

#ifdef DB_SAVE
        if (! interactive(me) && 
            !MEMBER_D->is_valid_member(query("id", me)) && 
            query("online_time", me) <= query("offline_time", me)*3 )
        {
                CLOSE_D->user_opened(me);
                call_out("user_quit", 0, me);
                return 0;
        }
#endif

        if( pot <= query("learned_points", me )
         || mar <= query("learned_experience", me) )
        {
                tell_object(me, "���Ǳ�ܻ����ľ��ˡ�\n");
                message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)��������%s����Բ����",
                                      me->name(1),query("id", me),to_chinese(skill)));
                if (! interactive(me))
                {
                        me->force_me("chat* haha");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        if( me->add("learned_points",PERIOD_POT/2+random(PERIOD_POT))>pot )
                set("learned_points", pot, me);

        if( me->add("learned_experience",PERIOD_MAR/2+random(PERIOD_MAR))>mar )
                set("learned_experience", mar, me);
                
        t=query_temp("last_closing", me);
        tn = time();
        if (tn - t < 0)
        {
                set_temp("last_closing", tn, me);
                return 1;
        }

        if (tn - t < PERIOD)
                return 1;

        set_temp("last_closing", tn, me);
                
        if (random(10) == 0)
                //tell_object(me, "�չ�����" + to_chinese(skill) + "��...\n");
                tell_object(me, "��չ�����" + to_chinese(skill) + "��������˼��\n");
        
        /*
        if ((random(100) < 3) && me->can_improve_neili())
        {
                tell_object(me, HIR "����ڹ��������򣬸е����������ˣ�\n" NOR);
                addn("improve/neili", 1, me);
                me->improve_neili(10 + random(20));
        }

        if ((random(100) < 3) && me->can_improve_jingli())
        {
                tell_object(me, HIM "�����ͨ�������򣬸е����������ˣ�\n" NOR);
                addn("improve/jingli", 1, me);
                me->improve_jingli(5 + random(10));
        }
        */

        exp_inc = 50 + random(100);
        exp_inc = exp_inc * (100 + me->query_skill("martial-cognize", 1)) / 500;
        exp_inc=exp_inc*(100+query("int", me))/100;
        addn("combat_exp", exp_inc, me);
        me->improve_skill("martial-cognize", 800 + random(800));

        tell_object(me, HIM "������ͻȻ���һ�������" + to_chinese(skill) + "���˸��������\n" NOR); 
        me->improve_skill(skill, 5000 + random(1000));
        SKILLS_D->upgrade_skill_power(skill); 
        CHANNEL_D->do_channel(find_object(SKILLS_D), "rumor", 
                              "�������ԣ���ѧ����ʦ" + me->name(1) + "�չ���������" + 
                              to_chinese(skill) + "����������������֮��������Ϊ������"); 

        return 1;
}

int halt_closing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me,"����ֹ�˱չ�����"+to_chinese(query("upgrade", me))+"��\n");
        message_vision(HIY "$N" HIY "���һ��������������һ��������ʱ"
                       "�����������Ĳ���\n\n" NOR, me);

        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                              "����"+to_chinese(query("upgrade", me))+"��;ͻȻ������");
        return 1;
}

protected void user_quit(object me)
{
        if (! objectp(me) || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : upskill

�չ������о��书��ֻ�����书�ﵽ4600���Ժ���ܹ��չ������о���������书
��COMBAT��ֵ��Ҫ�������һ����ȫ���ҿ�����Ϣ�ĵط���������������ǰ��Ҫ��
һ�����Ǳ�ܼ���ʮ����ᣬ�չؿ�ʼ�Ժ���������Ժ����ɫ����Ȼ�������У�
ֱ�������ֹ����(halt)����Ǳ�ܻ����ľ����ڼ�����ҵľ��顢�����书����
ѧ�������Լ������书��������������

HELP );
        return 1;
}
