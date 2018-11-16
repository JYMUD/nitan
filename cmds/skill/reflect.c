// reflect.c
// ڤ˼ָ���ȡ���������Ǳ��
// ��Աר��ָ�� Create by Rcwiz for HERO.CD

#include <ansi.h>
#define MEMBER_D     "/adm/daemons/memberd"

inherit F_CLEAN_UP;

void end_reflect(object me)
{
         mixed exp, pot;

         if( query_temp("reflect", me) )
         {
               message_vision(HIY "$N" HIY "ڤ˼��ϣ������������۾����ƺ���������\n" NOR, me);
 
               delete_temp("reflect", me);

               exp=query("combat_exp", me);
               exp /= 100000;
               if (exp > 2000) exp = 2000;
               pot = exp / 5;

               exp = exp + random(exp / 2);
               pot = pot + random(pot / 2);
               if( query("jingmai/reflect", me) )
               {
                       exp+=exp*query("jingmai/reflect", me)/100;
                       pot+=pot*query("jingmai/reflect", me)/100;
               }

               addn("combat_exp", exp, me);
               addn("potential", pot, me);

               write(HIG "ͨ�����ڤ˼��������" HIC + chinese_number(exp) + HIG 
                     "��ʵս�����" HIC + chinese_number(pot) + HIG "��Ǳ�ܡ�\n");

         }

         if (! me->is_busy())me->start_busy(1);
         return;
}

int main(object me)
{
         object ob;


         if (me->is_busy() || me->is_fighting())
                 return notify_fail("����æ����˵�ɣ�\n");

         if( query_temp("reflect", me) )
                 return notify_fail("������ڤ˼��\n");

         if (! wizardp(me) && ! MEMBER_D->is_valid_member(query("id", me)))
                 return 0;

         if( !query("doing", me) )
                 return notify_fail("ֻ�мƻ�ʱ����ڤ˼��\n");

         if( query("combat_exp", me)<1000000 )
                  return notify_fail("��ʵս���飬�޷�ڤ˼��\n");

         if (me->query_skill("martial-cognize", 1) < 160)
                  return notify_fail("����ѧ�������㣬�޷�ڤ˼��\n");
 

         set_temp("reflect", 1, me);

         me->start_busy(30);

         me->start_call_out((: call_other, __FILE__,
                             "end_reflect", me:), 28 + random(6));

         message_vision(HIY "$N" HIY "��ϥ��������Ŀڤ˼ ����\n" NOR, me);

         return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : reflect

��ָ������ڼƻ�ʱʹ����������������Ǳ�ܡ�
��ָ��ֻ�޻�Աʹ�á�

HELP
);
    return 1;
}
 
