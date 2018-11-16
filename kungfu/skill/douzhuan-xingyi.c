// douzhuan-xingyi.c ��ת����

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *parry_msg = ({
        YEL"�����һ��������������$nһ��һ����$n��������Խ����������һ�ԡ�\n"NOR,
        BLU"$n����һ����������$l��$N����$n��$l������Ī��������ﻬ��һ�ԡ�\n"NOR,
        HIW"$n˫��ǰ̽����۴���$N�ұۣ��ұ�ʹ��$N��������$N���л�ȥ��\n"NOR,
        HIY"$n���ƶ�ת��$N����Ī�����������;ת�˷���ֱ���Լ�Ϯ����\n"NOR,
        YEL"$n�����Ϲۣ�˫����Է��ཻ���ƣ�̸Ц�侹ʹ��$N�������գ�ʹ��$N��֪����Ǻá�\n"NOR,
        BLU"$n����������$N�͹����ʹ������������$N�ĳ�����������$N�������������С�\n"NOR,
        HIW"ֻ��$n����Ʈ�磬ǡ���������ƣ������һʽ��˫�ƶ����޶�����׽��������$N��$l��\n"NOR,
        HIY"$n����Ʈ�������������ƶ�ת֮�䷴��$N����������$N��ȴ����$N��˼������⡣\n"NOR,
        HIY"$n����һ����$N�����Լ������ػ��������ŵ������˼�����\n"NOR,
        HIY"$n�ֱۻ�ת����$N����������һ�ƣ�$N������ա�\n"NOR,
        HIY"$n�����������$N����������һ����$N���Ʋ�ס��ֱ��ǰ��ȥ��\n"NOR,
        HIY"$n˫�ֻ�Ȧ��$Nֻ����ǰ�������һ��ǽ����Ҳ������ȥ��\n"NOR,
});

string *unarmed_parry_msg = ({
        "���Ǳ�$p˫��һ�ƣ�$N�Ĺ��ƶ�ʱ���˷���\n",
        "$n����һת��$Nֻ���õ����е�����ȫ�����䵽�˿մ���\n",
        "����$N�о�����޻���һ����˵�����Ĺ��졣\n",
});

int valid_enable(string usage) { return usage=="parry"; }
string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}
int valid_learn(object me)
{
        object ob;
        int d_lvl = (int) me->query_skill("douzhuan-xingyi",1);
        //int s_lvl = (int) me->query_skill("shenyuan-gong",1);
        int s_lvl = (int) me->query_skill("force",1);
        int l_lvl = (int) me->query_skill("literate",1);

        if ((int)me->query_skill("parry", 1) < 100)
                return notify_fail("��Ļ����мܼ������յĻ������������޷�ѧϰ��ת���ơ�\n");
        if( (int)me->query_int() < 40 )
                return notify_fail("����ϸ������һ�ᣬ����û���׽��������ĵ���\n");
        if( query("max_neili", me)<600 )
                return notify_fail("�������������û�а취����ת���ơ�\n");
        if( s_lvl < 100)
                return notify_fail("��ת���Ʊ�����ѧ����Ԫ��������ϰ��\n");
        if( s_lvl + 30 < d_lvl)
                return notify_fail("����ڹ����𲻹������������߼��Ķ�ת���ơ�\n");
        if( l_lvl + 50 < d_lvl)
                return notify_fail("��Ķ���д��ˮƽ�����������߼��Ķ�ת���ơ�\n");
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("��ת����ֻ��ͨ��ѧϰ����ߡ�\n");
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1; }

mixed valid_damage(object ob, object me, int damage, object weapon)
{
         mixed result;
         int ap, dp, mp, apr, opr, app, opp, rantemp;
         int lvl, ran;
         string msg;

         if ((int) me->query_skill("douzhuan-xingyi", 1) < 100 ||
          ! living(me) || me->query_skill("shenyuan-gong",1) < 100)
              return;
        
          // ���ǻ���Ч��
          if (query_temp("yixinghuanyue", me)) 
          {
                me->stop_busy(); 
                me->clear_weak(); 
          }
                
          mp = ob->query_skill("count", 1);
          ap = me->query_skill("force", 1);
          dp = me->query_skill("parry", 1);

          lvl = me->query_skill("douzhuan-xingyi", 1);

          // ���ⷴ�˺�����
          if (lvl > 280)ran = 50;
          if (lvl > 300)ran = 45;
          if (lvl > 320)ran = 35;
          if (lvl > 350)ran = 30;
          if (lvl > 380)ran = 20;
          if (lvl > 400)ran = 10;
          if (lvl > 450)ran = 8;
          if (lvl > 500)ran = 6;
          if (lvl > 550)ran = 4;
          if (lvl > 600)ran = 2;

          apr = me->query_skill("force", 1) + me->query_skill("dodge", 1) +
          me->query_skill("martial-cognize", 1);
          opr = ob->query_skill("force", 1) + ob->query_skill("parry", 1) +
          ob->query_skill("martial-cognize", 1);

          app = apr - opr;

          if (app > 0)
          {
             if (app > 1500)app=1500;

             //�ȼ�������ⷴ�˺����ʵ���ϵ��

                opp = 10;
             if (lvl > 280)opp = 30;
             if (lvl > 300)opp = 34;
             if (lvl > 320)opp = 43;
             if (lvl > 350)opp = 50;
             if (lvl > 380)opp = 75;
             if (lvl > 400)opp = 150;
             if (lvl > 450)opp = 188;
             if (lvl > 500)opp = 250;
             if (lvl > 550)opp = 375;
             if (lvl > 600)opp = 750;

             rantemp = ran;
             ran = ran - (app / opp);

             if (ran < 2)ran = 2;
             if (ran > rantemp)ran = rantemp;
           }

              // ��ת���Ʒ���Ч��

              if (query_temp("yixinghuanyue", me) || (lvl > 280 &&
               me->query_skill("zihui-xinfa", 1) > 300 &&
               ! me->is_busy() &&
               //me->query("max_neili") * 2 / 3 > ob->query("max_neili") &&
               query("neili", me)>500 &&
               mp < 100)
               //random(ran) == 1 )
               )
               {
                     set_temp("xingyi/"+query("id", ob), 1, me);
                     me->start_call_out((: call_other, __FILE__, "xingyi",
                                 ob, me :), 1);
                     
                     //if( !query_temp("yixinghuanyue", me) )
                     //   me->start_busy(2);

                     result = ([ "damage" : -damage ]);
                     result += ([ "msg" : msg ]);

                     return result;

                } else

                if (ap / 2 + random(ap) < dp)
                {
                     result = ([ "damage" : -damage ]);

                     switch (random(3))
                      {
                          case 0:
                             result += ([ "msg" : HIC "$n" HIC "���κ�Ȼת����ͣ��$N"
                                                  HIC "��һ�о�Ȼ�޴����֡�\n" NOR ]);
                          break;
                          case 1:
                             result += ([ "msg" : HIC "$n" HIC "����һ�У�$N"
                                                  HIC "��ʱ����׼����������"
                                                  "����һ�����������ĸо���\n" NOR ]);
                          break;

                          default:
                             result += ([ "msg" : HIC "$N" HIC "һ���ۿ�������$n"
                                                  HIC "��Ȼ��$n" HIC "����һж��"
                                                  "��$N" HIC "�Ĺ������������Ρ�\n" NOR ]);
                          break;
                        }
                     return result;
                  } else

                  if (mp >= 100)
                  {
                        switch (random(3))
                         {
                             case 0:
                               result = HIY "$n" HIY "���κ�Ȼת����ͣ��Ȼ��$N"
                                        HIY "���ѿ������а��˿������Ӱ�죬����ֱ�롣\n" NOR;
                               break;

                              case 1:
                               result = HIY "$n" HIY "����һ�У�$N"
                                        HIY "��������׼��������Ȼ���ѣ���ʱ�仯��ʽ��\n" NOR;
                               break;

                              default:
                               result = HIY "$n" HIY "����һж��������$N"
                                        HIY "��Ȼ��������������ǧ��ı仯��������Ų����$n"
                                        HIY "�������̾ʹ���ա�\n" NOR;
                               break;
                           }
                          COMBAT_D->set_bhinfo(result);
                    }
}

void xingyi(object ob, object me)
{
        string msg;
        int ap, dp, damage;
        object weapon;
        string menpai;

        if (! ob
        || ! me->is_fighting(ob)
         || !query_temp("xingyi/"+query("id", ob), me) )
                  return;

        menpai=query("family/family_name", ob);
        weapon=query_temp("weapon", me);
        ap = me->query_skill("force");
        dp = ob->query_skill("parry");

        if (dp / 2 + random(dp) < ap)
        {
           damage = ap+random(ap) / 2;

           msg = HIY "\n$N" HIY "ʩչ���ѧ����ת���ơ�  " HIR "----�Ա�֮������ʩ����----\n" NOR;

              switch (menpai)
               {
                  case "������" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,
                                HIC "$N" HIC "ʹ����Ħ���ľ�������Ħ��������������Ȼ�ӿ죡\n"
                                HIR "$n" HIR "���һ����$N" HIR "����ʹ��"
                                "$p" HIR"�ĳ�����ʽ��\n"
                                "$n" HIR "һ���Һ�����Ȼ���ܲ�����\n" NOR);
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIB "$N" HIB "��Ȼ��¶�׹⣬���α���쳣Ʈ�죬��$n"
                                HIB "���������߸���ͣ��\n$n" HIB "����ãʱ��$N"
                                HIB "ͻȻ����������Ϣ��һָ���֡����޾���ָ����"
                                    "����\n" NOR );
                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "���ϻ���" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,
                                HIY "$N" HIY "����һ���������²�������������֮�������е�" +
                                weapon->name() + HIY "ʹ���������һ�㣬������$n" HIY "��\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, 0, 0,
                                HIY "$N" HIY "��Ȼʹ����" HIR "һָǬ��" HIY "����������ָ��"
                                "��$n" HIY "̴��ҪѨ����ʽ�仯����֮����\n" NOR );
                         msg += HIR "$n" HIR "ֻ���ؿ�һ�飬�ѱ�$N"
                                HIR "һָ���У���ʱ��Ѫ��ӿ��ȫ������"
                                "��\n" NOR;
                         ob->start_busy(5+random(2));

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "�䵱��" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,
                                HIC "$N" HIC "ʹ�����ƽ������������¡���һ��֮���������У�����"
                                "�ǵ�����$n" HIC "��\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIW "$N" HIW "ʹ��̫��ȭ�����־������ָߣ����ֵͣ���Ȼ"
                                "��Ȧ����ͼ����������$n" HIW "��\n" NOR );

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "������" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIY "$N" HIY "�粽��ǰ������" + weapon->name() +
                                HIY "�����ҽ�����ת��ɣ����������ֱ����$n"
                                HIY "��\n" NOR );
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, 0, 0,
                                HIC "$N" HIC "ʹ�����ָѨ�����������ָѨ��������"
                                "һ����ָ����$n" HIC "��ǰ��Ѩ����������\n" NOR );
                         msg += HIR "���$p" HIR "�������У�ƴ�����$P"
                                HIR "ָ����ʱ�������ң�\n" NOR;
                         ob->start_busy(3+random(3));

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "��ң��" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIY "$N" HIY "һ����Х���������䣬����" + weapon->name() + HIY
                                "���Ữ��������һ���ޱ�Ѥ���Ľ�â��ңָ$n" HIY "��ȥ��\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIR "ֻ��$N" HIR "һ���Ϻȣ�˫�Ʒ׷ɣ�һʽ���������¡���"
                                "��������$n" HIR "��ȥ��\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "������" :
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIR "$N" HIR "��Ȼ������$n" HIR "��ǰ����Ȼʹ��"
                                "�����־������������������������$n" HIR "̫��"
                                "Ѩ�����Ű��������\n" NOR );
                         msg += HIY "$n���һ����ȴ��ͻȻ���֣���Ȼ��ʽ��·��ȫһ����"
                                "���Լ�ȴδ�а�ֶ����������˿ڳ�����\n" NOR;
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));

                       break;

                  case "Ѫ����" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,
                                HIW "$N" HIW "��Ŀ��ȣ�������������������" HIW "һ�ơ�"
                                HIR "������" HIW "���ų�����Ѫ�⣬����ǵ�����$n"
                                HIW "��\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(3+random(3));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIR "$N" HIR "Ŀ�����ѣ�һ�����ȣ�ȫ�������ž���죬ȭ"
                                "ͷ����������$n" HIR "��Ҫ����\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIR "$N" HIR "���һ������ɫ��죬ȫ�������ž���죬��"
                                "һȭ����������$n \n" NOR );

                         addn("neili", -500, me);
                         me->start_busy(5);
                       }
                       break;

                       default :
                         msg = HIM "\n$N" HIM "Ĭ���ϻ��ķ���ʩչ���ѧ����ת���ơ���\n"
                               HIM "һ������������Ѹ�ٹ��У������ǣ����$n \n"
                               HIM "����ʽ��\n" NOR;
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 200,
                               HIR "\n$n" HIR "���һ��������$N" HIR "����"
                               "$p" HIR"��ǰ����ʽ�����ۻط������Լ���\n��"
                               "Ȼ��$n" HIR "һ���Һ�����Ȼ���ܲ�����\n" NOR);

                         addn("neili", -500, me);
                         me->start_busy(2);

                  }

        } else
        {
               msg = HIC "$n" HIC "�ۼ�$P������ӿ������"
                      "���⣬ʩ������������⿪����\n" NOR;
        }
           delete_temp("xingyi", me);
           message_combatd(msg, me, ob);
}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}
int help(object me)
{
        write(HIC"\n��ת���ƣ�"NOR"\n");
        write(@HELP

    ����Ľ�ݼ������ֵľ���������һ�Ž�������֮������������
ת���ơ������˲�֪��ϸ������Ľ���ϡ��Ա�֮������ʩ������
���似��������������֮ʱ�������ԶԷ��ĳ�����������������
Ȼ���¸��Ÿ��ɵľ���������Ľ������һ���ᣬ��һ��������ʵ��
���о���ǧǧ����������δ���Ԩ�������ѽ�ÿһ�������ѧ��
�ˣ��ο����Ǿ������Էǳ�Ϧ֮���������ɡ���Ľ����������һ��
�����ޱȵġ���ת���ơ�֮�������۶Է�ʩ�����ֹ����������ܽ�
֮ת���������������Է��������ֵ����书Խ�ߣ�������Խ����
�Ľ�������ǵ���������������а��ն����µ��������⡰��ת
���ơ��Ĺ�������ʹ�ã����Թ���Ľ�������𽭺��������Ĺ���
���ڣ�ȴ��˭Ҳ��֪�������ֵı���ȭ��ת�����������������
�ܣ����е���ȫ�ڡ����������֡���������һȭ����ʯǽ֮�ϣ�
����Խ�أ�ȭͷ�����ܵ�����Խ������ǿ��������ֺ���ֻ����
ת�����εı���ȭ�����ף�ת���������ʵ������������Ǿͼ��ѡ�

        ѧϰҪ��
                ����ʦ
                Ľ�ݸ��ĵմ�����
                ��������40
                ��Ԫ��100��
                ��Ԫ�����ܵ��ڶ�ת����30��
                ����д�ֲ��ܵ��ڶ�ת����50��
                ����600
HELP
        );
        return 1;
}
