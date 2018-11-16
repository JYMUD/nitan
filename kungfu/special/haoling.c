
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIR "����˷�" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
        object *t;
        object tob;
        int attack, damage;

        joblv = me->query_joblv();

        t = me->query_team(); // ����Ҫ��Ӳ���ʩչ

        if (me->query_temp("special2/haoling"))
                return notify_fail("������˷����Ĺ�Ч��δ��ʧ���޷�ʩչ��\n");

        if (me->query("yhjob/job") != "ħʦ")
                return notify_fail("���ְҵ�����޷�ʩչ��\n");
                
        if (me->query("neili") < 1200)
                return notify_fail("����������㣬�޷�ʩչ��\n");

        if (joblv < 30)
                return notify_fail("���ְҵ�ȼ����㣬�޷�ʩչ��\n");                

        if (! arrayp(t))
                return notify_fail("�ü���ֻ������ӵ�ʱ��ʩչ��\n");

        t -= ({ 0 });
        if (sizeof(t) <= 1)
                return notify_fail("�ü���ֻ���ڶ�����ӵ�ʱ��ʩչ��\n");
                        
        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        message_vision(HIR "$N" HIR "˫Ŀ���⣬��۸ߺ�����ħ������������˷����� �������������ܣ�������η��\n" NOR, me);

        foreach (tob in t)
        {
                if (1)
                {                        
                        tell_object(tob, HIW + me->name() + "ʩչ�����С�����˷�����������ж��ѵ����м��˺�����\n" NOR);
                        attack = 100 + me->query_joblv() * 20 + me->query("lhpoint/special/haoling") * 60;
                        damage = 100 + me->query_joblv() * 30 + me->query("lhpoint/special/haoling") * 80;

                              // �����ظ�ʩչ
                        if (! tob->query_temp("special2/haoling"))
                        {
                                tob->set_temp("special2/haoling", joblv);
                                tob->add_temp("apply/attack", attack);
                                tob->add_temp("apply/damage", damage);
                                tob->add_temp("apply/unarmed_damage", damage);
                                tob->start_call_out( (: call_other, __FILE__, "remove_effect", tob, attack, damage :), 
                                                    60 + joblv * 10);
                        }
                }
        }
 
        me->add("neili", -1200);
        me->start_busy(1);

        return 1;
}

void remove_effect(object me, int attack, int damage)
{
        if ((int)me->query_temp("special2/haoling"))
        {
                me->add_temp("apply/attack", -1 * attack);
                me->add_temp("apply/damage", -1 * damage);
                me->add_temp("apply/unarmed_damage", -1 * damage);
                me->delete_temp("special2/haoling");
                tell_object(me, "������˷����Ĺ�Ч�Ѿ���ʧ��\n");
        }
}

