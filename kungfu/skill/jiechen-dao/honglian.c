// snowman
#include <ansi.h>

int check_fight(object me);
int remove_effect(object me);

int perform(object me)
{
        object weapon;

        if( !me->is_fighting() || !living(me))
                return notify_fail("��������ֻ����ս���е�ʹ�á�\n");

      if( !objectp(weapon=query_temp("weapon", me)) || 
          query("skill_type", weapon) != "blade" )
                return notify_fail("�����Ұѵ���˵�ɣ�\n");

        if( query_temp("honglian", me) )
                return notify_fail("������ʹ�á������𡹡�\n");  

        if( query_temp("mz_lx", me) )
                return notify_fail("������ʹ�á�������ħ�䡹��\n");  

        if((int)me->query_skill("jiechen-dao", 1) < 180 )
                return notify_fail("��Ľ䳾��������죬��������ᡸ������֮���ϡ�\n");

        if (me->query_skill_mapped("blade") != "jiechen-dao")
                return notify_fail("�����ʹ�ý䳾����ʩչ�������𡹡�\n");   

        if( query("max_neili", me)<3500 )
                return notify_fail("���������Ϊ̫����ʹ�����������𡹡�\n");                

        if( query("neili", me)<800 )
                return notify_fail("����������������ʹ�����������𡹡�\n");


        if(userp(me) && (int)me->query_skill("buddhism", 1) < 180 )
                return notify_fail("��������ķ������򲻹����޷�ʹ�á������𡹡�\n");

        if(userp(me) && me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("����ڹ����ԣ���������ʹ���������𡹡�\n");
                                                                                     
        if( !query("jiali", me) )
                return notify_fail("��������ȫ������Ϊ�����㲻���������޷����ӳ����������ġ�\n");

        message_vision(RED "\n$N����䳾��֮�������𡹾����������������ʺ�ɫ����ӿ����\n"
                           "����ǰ����֮�����㼴ͣס����������Ʈ���޶����������ڰ�գ�\n"
                           "������������翣�����׽����ȴ��ɱ�������Σ�ʵ������������\n" NOR, me);
        me->start_busy(1);
        set_temp("honglian", 1, me);
        addn("neili", -300, me);
        addn("jingli", -100, me);
        addn_temp("apply/parry", me->query_skill("jiechen-dao",1)/3, me);
        addn_temp("apply/arrmor", me->query_skill("jiechen-dao",1)/3, me);
        check_fight(me);
        return 1;
}

int check_fight(object me)
{
        object *enemy, target;
        int sz;        

        if (!me) return 0;

        if( me->is_ghost() || !living(me) || query("no_fight", environment(me)) || query_temp("weapon", me)){
           addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
           addn_temp("apply/arrmor", -me->query_skill("jiechen-dao",1)/3, me);
           delete_temp("honglian", me);
           return 0;
           }        

        addn("neili", -5, me);
        enemy = me->query_enemy();

        if( !enemy || !arrayp(enemy) ) remove_effect(me);
        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;
        if( sz > 0 ) target = enemy[random(sz)];
        else remove_effect(me);
        if( !query_temp("honglian", me))return 1;

        else if(!me->is_fighting())
        {
                if( !query_temp("stopped", me) )
                {
                    set_temp("stopped", 1, me);
                    call_out("check_fight", 2, me);
                }
                else remove_effect(me);
        }
        else if (userp(me))
        {
                  message_vision(HIY"$Nһ��������ͻȻ���У���Ȼ����ȫ��ͬ����������\n"NOR,me);
                  me->start_busy(1);
                  addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
                  addn_temp("apply/arrmor", -me->query_skill("jiechen-dao",1)/3, me);
                  delete_temp("honglian", me);
                  return 1;
        }   
       else if( query("neili", me) <= 10 || !target)remove_effect(me);
       else call_out("check_fight", 1, me);
       return 1;
}       

int remove_effect(object me)
{
   string msg;
   message_vision(HIY "\n$N����һ�к�����ʹ�꣬˫�ֺ�ʮ���ڵ��أ�ʾ�ȱ�Ϊ����\n\n"NOR, me);
   addn_temp("apply/parry", -me->query_skill("jiechen-dao",1)/3, me);
   addn_temp("apply/armor", -me->query_skill("jiechen-dao",1)/3, me);
   delete_temp("honglian", me);
   delete_temp("stopped", me);
   remove_call_out("check_fight"); 
   return 0;
}
