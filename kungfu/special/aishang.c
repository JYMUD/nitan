#include <ansi.h>
#include <combat.h>

int is_scborn() { return 1; }

string name() { return HIC "����֮����" NOR; }

int perform(object me, string skill, string arg)
{

        int armor, damage, sk;
        string msg;
        
        if( query_temp("special2/aishang", me) )
                return notify_fail("���Ѿ����ڼ��ȵİ��˵����ˣ��Ժ���ʩչ�ɡ�\n");
        
        set_temp("special2/aishang", 1, me);
        
        armor = 3000;
        damage = 50000;
        sk = 500;
        
        addn_temp("apply/armor", armor, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/sword", sk, me);
        addn_temp("apply/parry", sk, me);
        addn_temp("apply/dodge", sk, me);
        addn_temp("apply/force", sk, me);

        msg = HIY "$N" HIY "�ḧ������֮���ˡ���ɲ�Ǽ䣬����ɢ��������ɫ�Ĺ�â��һֱ��ɫ�ĺ�����$N" HIY "���������𣬲���ɿ���ų��"
              "���������ػ���һ�����ӵ�ģ����������$N" HIY "���ϵġ�����֮���ˡ��������ص������� ���� $N" HIY "����������һ���ˣ���"
              "���ڴ˿��뽣���Ϊһ�壡\n" NOR;
        message_vision(sort_msg(msg), me) ;
        
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, armor, damage, sk :), 600);   

        return 1;
}

void remove_effect(object me, int armor, int damage, int skill)
{
        if (! objectp(me))return;

        if( query_temp("special2/aishang", me) )
        {                       
                addn_temp("apply/armor", -1*armor, me);
                addn_temp("apply/damage", -1*damage, me);
                addn_temp("apply/sword", -1*skill, me);
                addn_temp("apply/parry", -1*skill, me);
                addn_temp("apply/dodge", -1*skill, me);
                addn_temp("apply/force", -1*skill, me);
                delete_temp("special2/aishang", me);
                tell_object(me, HIG "�㽣��֮����ʩչ��ϡ�\n" NOR);
        }
}
