// shade.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int lvl,i;
        object env, *inv;
       string *can_perform;

       can_perform=query("can_perform/martial-cognize", me);

       if(!can_perform || 
          !arrayp(can_perform) || 
          !sizeof(can_perform) || 
          member_array("shade",can_perform) == -1
         )
                return notify_fail("�㻹û��ѧ��ʹ�ã�����֮��ݣ�\n");

        if (me->is_busy())
                return notify_fail("����һ��������û����ɣ��޷�ʹ������֮��\n");

        lvl = (int)me->query_skill("martial-cognize",1);

       if(lvl < 250)
                return notify_fail("�����ѧ�����������\n");

        if( query("jingli", me)<500 )
                return notify_fail("��ľ���������\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("��ľ�����û�дﵽ�㹻�Ĳ�Σ�\n");

       if( query("jing", me) <= 300 )
                return notify_fail("��ľ���״̬���ã�\n");

       if( query("env/invisibility", me) )
                return notify_fail("������ʩչ������֮���\n");

       if( time()-query("last_shade_time", me)<600 )
                return notify_fail("���ʹ�ù�������֮��ݲ��ã���û����ȫ�ָ�����������Ϣһ��ɡ�\n");

       if( environment(me) && query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��ʹ�ã�����֮���!\n");

        addn("jingli", -300, me);
        me->receive_damage("jing", 200);

        message_vision(HIW "$N��ɫ���أ����������˫Ŀ���������һ���ɫ����Ѹ��ӿ���ǿף����Լ��������¶���Χ�ţ������˽����黯������\n" NOR, me);
                set("env/invisible", 1, me);

       set("last_shade_time", time(), me);
       me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), lvl/5);
       if( me->is_fighting() ) me->start_busy(3);
       return 1;

}
void remove_effect(object me)
{
        delete("env/invisible", me);
        tell_object(me,"�������֮��ʧЧ�ˣ�\n");
        message_vision(HIW "һ������ͻȻ���֣�����Խ��ԽŨ����������ɢ��ȴ��$N�����ˡ�\n" NOR,me);
}