// hand.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
       int lvl;
       string *can_perform;

       can_perform=query("can_perform/martial-cognize", me);

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("hand",can_perform) == -1
         )
                return notify_fail("�㻹û��ѧ��ʹ�ã�����֮�֣ݣ�\n");

        if (me->is_busy())
                return notify_fail("����һ��������û����ɣ��޷�ʹ������֮�֡�\n");

        lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("�����ѧ�����������\n");

        if( query("jingli", me)<500 )
                return notify_fail("��ľ���������\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("��ľ�����û�дﵽ�㹻�Ĳ�Σ�\n");

       if( query("jing", me) <= 300 )
                return notify_fail("��ľ���״̬���ã�\n");

        if( !target || !target->is_character() )
                return notify_fail("��Ҫ��˭ʹ�ã�����֮�֣ݣ�\n");

        if( target->is_corpse() )
                return notify_fail("�������ˣ�ֻ�л��˲��ܾ��ѡ�\n");

       if(me->is_fighting() || target->is_fighting())
                return notify_fail("ս���в���ʹ�ã�����֮�֣ݣ�\n");

        addn("jingli", -400, me);
        me->receive_damage("jing", 250);

       if (target == me)
                message_vision( HIY "$N˫�ֽ������ڶ�ͷ, �����۾���������...\n" NOR, me);
        else
                message_vision( HIY "$Nһ�ַ���$n���������, һ������$n�ĺ���, �����۾���������...\n" NOR, me, target);
        message_vision( HIY "$N�������ų�Ӥ�����Ц�ݣ��ƺ���������������������...\n" NOR, target);

       if( query("jing", target)<1 )
                set("jing", 1, target);
       if( query("max_jing", target)<1 )
                set("max_jing", 1, target);

       if( query("qi", target)<1 )
                set("qi", 1, target);
       if( query("eff_qi", target)<1 )
                set("eff_qi", 1, target);

        if(! living(target))
                target->revive();

       target->remove_all_killer();
        return 1;
}