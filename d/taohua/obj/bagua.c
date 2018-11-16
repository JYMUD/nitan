#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + CYN "������" NOR, ({ "tie bagua", "tie", "bagua" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "����һ�����������İ����̣����ϵ�"
                            "����̫������\n�����������÷ǳ����¡���ˮʦ"
                            "����������۲��\nˮ�Ͳ��ԣ�Ҳ���������Ƴ�"
                            "(" HIW "break" NOR + CYN ")���������󷨡�\n"
                            NOR);
                set("unit", "ֻ");
                set("value", 300000);
                set("no_sell", 1);
                set("material", "steel");
        }
        setup();
}

void init()
{
        add_action("do_break", "break");
        add_action("do_break", "pozhen");
}

int do_break(string arg)
{
        object me, env, owner;
        int skill;

        me = this_player();
        env = environment(me);
        skill = (int)me->query_skill("qimen-wuxing", 1);

        if (me->is_busy()
            || query_temp("pending/exercising", me )
            || query_temp("exit_blocked", me) )
                return notify_fail("��������æ���ء�\n");

        if (skill < 1)
                return notify_fail("��������Է�����ȥ��Ū�˰��죬ȴ"
                                   "��֪������֡�\n");

        if (skill < 80)
                return notify_fail("����������е��о������������޷�"
                                   "����\n");

        if( !env || !query("th_buzhen", env) )
                return notify_fail("���ﲢû�б����������󷨡�\n");

        if( !objectp(owner=find_player(query("th_zhen_owner", env)) )
           || environment(owner) != env)
        {
                set("long",query("org_desc",  env), env);
                set("exits",query("org_exits",  env), env);
                set("cost",query("org_cost",  env), env);
                delete("org_desc", env);
                delete("org_cost", env);
                delete("org_exits", env);
                delete("th_buzhen", env);
                delete("th_pozhen", env);
                delete("th_zhen_owner", env);

                tell_object(env, HIM "\nͻȻ��������Χɢȥ�����澰��"
                                 "��Ȼһ�䡣\n\n" NOR);
                return 1;
        }

        if( me != owner && query("max_jingli", me)<500 )
                return notify_fail("��ľ�����Ϊ���㣬��������\n");

        if( me != owner && query("jingli", me)<300 )
                return notify_fail("��Ŀǰ�ľ������㣬��������\n");

        if( me != owner && query("jing", me)<200 )
                return notify_fail("��Ŀǰ�ľ������㣬��������\n");

        if( me != owner && skill<query("th_pozhen", env)*3/4 )
        {
                message_vision(HIR "$N" HIR "���ڵ���ڤ˼���룬ͻȻ��ɫ��"
                               "�䣬Ż��һ����Ѫ��\n" NOR, me);
                me->receive_wound("jing", 100);
                me->start_busy(3);
                return 1;
        }

        if (me == owner && environment(owner) == env)
        {
                message_vision(HIW "ֻ��$N" HIW "����һ���������ʱ������"
                               "ɢȥ����Χ�����ָֻ������\n" NOR, me);
                me->start_busy(2);
        } else
        {
                message_sort(HIW "\n$N" HIW "��˼Ƭ�̣������ѽ��󷨵�����"
                             "���˱仯ȫ����Ȼ���أ���������һ����Ц������"
                             "һ�����������С�ֻ��$N" HIW "����������ֱ��"
                             "��ɳʯ���𣬲�һ������֮���������Ĵ���ɢ����"
                             "�ŵ���Ӱ���١�\n\n" NOR, me);
                me->receive_damage("jing", 100);
                addn("jingli", -150, me);
                me->start_busy(3);
        }        
        set("long",query("org_desc",  env), env);
        set("exits",query("org_exits",  env), env);
        set("cost",query("org_cost",  env), env);
        delete("org_desc", env);
        delete("org_cost", env);
        delete("org_exits", env);
        delete("th_buzhen", env);
        delete("th_pozhen", env);
        delete("th_zhen_owner", env);

        return 1;
}