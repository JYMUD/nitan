// luohuaqiuge.c �仨���
// Last Modified by suncity on May.26 2002

#include <ansi.h>;
#include <combat.h>;
inherit F_SSERVER;
#define PNAME "���仨����"
int perform(object me, object target)
{
        string msg;
        int skl_me, skl_you, extra_me, extra_you, i, damage;
        int FLAG=0;
        object you,ob,*obs,weapon;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"ֻ�ܶ�ս���еĶ���ʹ�á�\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        fskill = "honghua-shengong";
        bskill = "blade";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 100 )
                return notify_fail("���"+to_chinese(fskill)+"������죬����ʹ��"+PNAME+"��\n");

        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("���"+to_chinese(sskill)+"������죬����ʹ��"+PNAME+"��\n");

        if( query("max_neili", me)<800 )
                return notify_fail("���������Ϊ����������ʹ�þ��С�\n");

        if( query("neili", me)<500 )
                return notify_fail("�����������������ʹ�þ��С�\n");

        if(pointerp(obs=me->query_team()) )
        {
                FLAG=1;
                for(i=0;i<sizeof(obs);i++)
                {
                        if(obs[i] == me) continue;
                        if(!obs[i]) {FLAG=0;continue;}
                        if(environment(obs[i]) != environment(me))
                                {FLAG=0;continue;}
                        if(!obs[i]->query_skill("luohua-jian"))
                                {FLAG=0;continue;}
                        if(obs[i]->query_skill("luohua-jian",1) < 100)
                                {FLAG=0;continue;}
                        if( !objectp(ob=query_temp("weapon", obs[i]) )
                                 || query("skill_type", ob) != "sword" )
                                {FLAG=0;continue;}
                        if(obs[i]->query_skill_mapped("sword")!="luohua-jian")
                                {FLAG=0;continue;}
                        if( query("max_neili", obs[i])<800 )
                                {FLAG=0;continue;}
                        if( query("neili", obs[i])<500 )
                                {FLAG=0;continue;}
                }
                if(sizeof(obs) !=2) FLAG=0;
        }
        skl_me=(int)me->query_skill("blade");
        extra_me=query_temp("apply/damage", me)+me->query_str()*me->query_str()/10;
        if(FLAG)
        {
//                if(target->query("owner"))
                if(obs[0]==me) you=obs[1]; else you=obs[0];
                if(!userp(target))
                if (!target->accept_hit(me) || !target->accept_hit(you))
                        return notify_fail("�����������ɼٱ���֮����ɡ�\n");
                skl_you=(int)you->query_skill("sword");
                extra_you=query_temp("apply/damage", you)+you->query_str()*you->query_str();

                msg = HIR"$N����һ����"HIG"��СԷݺ��Ъ��"HIR"��������"+weapon->name()+HIR"Ȧת��Х����ǿ������Х����Ȼһ�壬����$n��\n"NOR;
                msg +=HIY"�����ŵ���ࡱ"HIR"����"+you->name()+HIR"����"+ob->name()+HIR"�������ƣ�Ʈ��$n��\n"NOR;
                message_combatd(msg, me, target);
                addn_temp("apply/attack", (skl_you+skl_me)/5, me);
                addn_temp("apply/damage", (extra_you+extra_me), me);
                addn_temp("apply/attack", (skl_you+skl_me)/5, you);
                addn_temp("apply/damage", (extra_you+extra_me), you);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);

                msg = HIY"���ۿ�����ȥ��"HIR"����$N�����ڶ�������"+weapon->name()+HIR"����ˮ��Ϯ��$n��\n"NOR,
                msg +=HIG"��������������"HIR"����"+you->name()+HIR"����"+ob->name()+HIR"������ǧ�����$n��\n"NOR,
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(you,target,query_temp("weapon", you),TYPE_REGULAR,msg);
                addn_temp("apply/attack", -(skl_you+skl_me)/5, you);
                addn_temp("apply/damage", -(extra_you+extra_me), you);
                addn_temp("apply/attack", -(skl_you+skl_me)/5, me);
                addn_temp("apply/damage", -(extra_you+extra_me), me);
                me->start_busy(random(4));
                you->start_busy(random(3));
                addn("neili", -400, me);
                addn("neili", -400, you);
        }
        else return notify_fail("����ʹ�仨��裬����û�˺ܺ���ϣ�ûʹ������\n");
        return 1;
}
int help(object me)
{
        write(WHT"\n����ߵ�֮�仨���"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                ���������������ͷ���������ͬ��������

        ����Ҫ��
                �컨��100��
                ����ߵ�100��
                ������Ϊ800
                ����500
                �����л��������
        ���Ҫ��
                �컨��100��
                �仨ʮ����100��
                ������Ϊ800
                ����500
HELP
        );
        return 1;
}
