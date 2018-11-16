// closed.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define PERIOD          864
#define PERIOD_POT      100

int clossing(object me);
int halt_closing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;

        seteuid(getuid());
        where = environment(me);

        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if (! ultrap(me))
                return notify_fail("�㻹û�е�����ʦ�ľ��磬���Ǻú�ѧϰ�����ɡ�\n");

        if (wizardp(me))
                return notify_fail("��ʦ��ʲô�أ�\n");

        if( !query("no_fight", where) )
                return notify_fail("������չأ���̫��ȫ�ɣ�\n");

        if( !query("sleep_room", where) )
                return notify_fail("�����һ���ܹ���Ϣ�ĵط��չء�\n");

        if( where->is_chat_room() )
                return notify_fail("������չأ���̫��ȫ�ɣ�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( query("potential", me)-query("learned_points", me)<10000 )
                return notify_fail("���Ǳ�ܲ�����û���չ����С�\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("�����ڵ���̫���ˣ��޷����ıչء�\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("�����ڵľ�̫���ˣ��޷����ıչء�\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("������������в��㣬����Ŀǰ������"
                                   "���г�ʱ��ıչ�������\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("�����ڵ�����̫���ˣ��޷����ıչء�\n");

        message_vision("$N��ϥ���£���ʼڤ���˹����չ����С�\n", me);
        set("startroom", base_name(where), me);
        set("doing", "closed", me);
        CLOSE_D->user_closed(me, "closed");
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("����ʦ%s(%s)��ʼ�չ����С�",
                              me->name(1),query("id", me)));

        return 1;
}

int continue_closing(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "closing" :), me),
                       bind((:call_other, __FILE__, "halt_closing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n������չ�...\n" NOR);
        return 1;
}

int filter_skill(string sk, object me)
{
        if (me->query_skill(sk, 1) < 200 || ! me->can_improve_skill(sk))
                return 0;

        if (SKILL_D(sk)->type() != "martial")
                return 0;

        if (SKILL_D(sk)->valid_enable("force"))
                return 1;

        if (SKILL_D(sk)->valid_enable("parry") ||
            SKILL_D(sk)->valid_enable("dodge"))
                return 0;

        return 1;
}

int closing(object me)
{
        int t;
        int tn;
        mixed pot;
        int r, period;
        int exp_inc;
        string *ks;

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

        pot=query("potential", me);
        if( pot <= query("learned_points", me) )
        {
                tell_object(me, "���Ǳ�ܺľ��ˡ�\n");
                message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�չع���Բ����",
                                      me->name(1),query("id", me)));
                if (! interactive(me))
                {
                        me->force_me("chat* haha");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        t=query_temp("last_closing", me);
        tn = time();
        if (tn - t < 0)
        {
                set_temp("last_closing", tn, me);
                return 1;
        }

        period = PERIOD;
        if (present("closed charm", me))
                period /= 4;
                
#ifdef DB_SAVE
        if (me->is_vip())             
                period /= 2;
#endif

        if (tn - t < period)
                return 1;

        set_temp("last_closing", tn, me);
        if( me->add("learned_points",PERIOD_POT/2+random(PERIOD_POT))>pot )
                set("learned_points", pot, me);

        if (random(10) == 0)
                tell_object(me, "�չ�������...\n");

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

        exp_inc = 50 + random(100);
        exp_inc = exp_inc * (100 + me->query_skill("martial-cognize", 1)) / 500;
        exp_inc=exp_inc*(100+query("int", me))/100;
        addn("combat_exp", exp_inc, me);
        me->improve_skill("martial-cognize", 800 + random(800));

        ks = filter_array(keys(me->query_skills()), (: filter_skill :), me);
        if (r = sizeof(ks))
        {
                r = random(r);
                tell_object(me, HIY "���" + to_chinese(ks[r]) + "��������\n" NOR);
                me->improve_skill(ks[r], 5000 + random(1000));
        }

        return 1;
}

int halt_closing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "����ֹ�˱չء�\n");
        message_vision(HIY "$N" HIY "���һ��������������һ��������ʱ"
                       "�����������Ĳ���\n\n" NOR, me);
        // addn("potential", (query("learned_points", me) - query("potential", me)) / 2);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                              "�չ���;ͻȻ������");
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
ָ���ʽ : closed

�չ����У�ֻ���㵽�˴���ʦ�ľ����Ժ���ܹ��չ����С�Ҫ�������
һ����ȫ���ҿ�����Ϣ�ĵط����ܱչأ��չ�ǰ��Ҫ��һ���Ǳ�ܣ���
�ؿ�ʼ�Ժ���������Ժ����ɫ����Ȼ�������У�ֱ�������ֹ�չ�
(halt)����Ǳ�ܺľ����ڼ�����ҵľ��顢���ܡ���������������

HELP );
        return 1;
}
