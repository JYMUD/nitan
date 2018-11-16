// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i;
        
        if (! me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ�����컯����\n");

        if ((int)me->query_skill("linji-zhuang", 1) < 100)
                return notify_fail("����ټ�ʮ��ׯ���������ʹ�������컯����\n");  

        if ((int)me->query_skill("anying-fuxiang", 1) < 100)
                return notify_fail("��İ�Ӱ���㻹�������ʹ�������컯����\n");  

        if( query("jing", me)<500 )
                return notify_fail("�����ھ�������\n");

        if( query("neili", me)<500 )
                return notify_fail("����������������\n");

        if( query_temp("emei/parry", me) )
                return notify_fail("������ʹ�����컯����\n");

        msg = HBYEL "$Nʹ����Ӱ��������컯�������ֵ�ʱ�������ɣ�\n\n" NOR; 

        addn("neili", -200+random(100), me);
        me->recieve_damage("jing", 50);
        
        message_combatd(msg, me);
        
        i = me->query_skill("linji-zhuang", 1) / 5;
        
        addn_temp("apply/dex", i, me);
        addn_temp("apply/con", i, me);
        set_temp("emei/parry", i, me);
        
        remove_call_out("remove_effect");
        call_out("remove_effect", 1, me, (int)me->query_skill("force") / 3);
        return 1;
}

void remove_effect(object me, int count)
{
        int i;
        
        if (! me) return;
        if (! me->is_fighting()
        ||  me->query_skill_mapped("dodge") != "anying-fuxiang" 
        ||  count < 1)
        {
                i=query_temp("emei/parry", me);
                addn_temp("apply/dex", -i, me);
                addn_temp("apply/con", -i, me);
                delete_temp("emei/parry", me);
                tell_object(me, HIW "��ֹͣ�����컯������������˿�����\n" NOR);
                return;
       }
       call_out("remove_effect", 1 ,me ,count -1);
}
