#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��ǽ"; }

#include "/kungfu/skill/eff_msg.h";
int start_huoqiang(object me);
int check_pfm(object me, object target, object ob);

int perform(object me, object target)
{
        object ob;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(!target->is_character())
                return notify_fail("�����һ�㣬�ǲ��������\n");

        if(!living(target))
                return notify_fail(target->name()+"�Ѿ��޷�ս���ˡ�\n");

        if(me->is_busy())
                return notify_fail("����æ����˵ƴ�����¡�\n");

        if( me->query_skill("chousui-zhang", 1) < 150 )
                return notify_fail("�㷢���Լ������޶��ƻ�������죬�޷�ʹ�á���ǽ�����й�����\n");

        if( (int)me->query_skill("huagong-dafa",1) < 150 )
                return notify_fail("�㷢���Լ��Ļ�������Ϊ�������޷�ʹ�á���ǽ�����й�����\n");

        if((int)me->query_skill("poison",1) < 120)
                return notify_fail("�㷢���Լ����ھ۶��������޷�ʹ�á���ǽ�����й�����\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang"
        ||  me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("������ó����Ʋ���ʹ�á���ǽ�����й�����\n");

        if( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("�㷢���Լ����õ��ڹ��޷����С���ǽ��������\n");

        if( query("max_neili", me)<1000)
                return notify_fail("�㷢���Լ�����ʵ��̫�����޷���������ǽ�����й�����\n");

        if( query("neili", me)<800)
                return notify_fail("�㷢���Լ���������ʵ��̫�����ٲ��𡸻�ǽ�����й�����\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�á���ǽ����\n");

        if(!objectp(ob = present("huo yan", environment(me))))
                return notify_fail("û�л����ô��������ǽ�����й�����\n");

        if( query_temp("pfm_chousui", me) )
                return notify_fail("������������ѽ��й�����\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("���������ʩչ������\n");

        message_combatd(BLU"\n$N��ɫ�ҵ������ִ򿪷��٣������´����������ϣ����ŵ�ȼ���׷ۣ�ҧ����⣬\n"
                "һ��"RED"��Ѫ"BLU"���������ȥ��"HIR"�������һ�����漴��Ϊ"RED"����"HIR"��ҫ�������۾�Ҳ����������\n\n"NOR,me);

       me->start_busy(3);
       set_temp("pfm_chousui", 1, me);
       if(random(me->query_kar()) > 15)
             check_pfm(me, target, ob);
       else call_out("check_pfm", 2, me, target, ob);
       return 1;
}

int check_pfm(object me, object target, object ob)
{
        string msg;
        int p;

        if(!me) return 0;
        delete_temp("pfm_chousui", me);

        if(!living(me) || me->is_ghost()) return 1;

        if( !target || !living(target) || query("no_fight", environment(me) )
        ||  environment(me)!=environment(target)){
                message_combatd(HIY"$N�����ٷ�����̧���"HIR"��ǽ"HIY"ѹ�ػ���֮�С�\n"NOR,me);
                return 1;
        }
        if(!objectp(present(ob, environment(me)))){
                message_combatd(HIY"$N�ۿ����Ϩ��ɢ����Ϣ��\n"NOR,me);
                return 1;
        }
        addn("neili", -100, me);

        msg = BLU"\n$N�͵����Ӽ����������ݰ���ת��ʮ���Ȧ�ӣ�����$P���������"HIR"��������Ѷ��ز������\n"
              "ȼ�գ�����һ��"RED"��ǽ"HIR"�㣬������ɽ����֮����$nѹ����\n"NOR;
        //if( !target->is_killing(query("id", me))) target->kill_ob(me);

        if(random(me->query_str()) > target->query_dex()/2){
                msg += HIY"����ӳ��֮��$p΢һ���ɣ��ǻ�ǽ���ÿ켫����Ҫ�˵����ϣ�$pֻ��˫�������\n"
                       "������������ͳ�������ķ�Ʈ�𣬾����������Ƕ���ɫ�Ĺ�ǽ��\n\n" NOR;
                set_temp("huoqiang_target",query("id",  target), me);
                set_temp("huoqiang/period", 1, me);
                set_temp("huoqiang_target",query("id",  me), target);
                set_temp("huoqiang/period", 1, target);

                me->start_busy((: start_huoqiang :));
                target->start_busy((: start_huoqiang :));
                message_combatd(msg, me, target);
                return 1;
        }

        else if(random(me->query_str()) > target->query_dex()/3){
                me->start_busy(4);
                target->start_busy(3);
                msg += HIY"\n$nֻ��Ŀ�ɿڴ���һ��֮�䣬��æԾ�𣬵�һ��"HIW"��"HIY"���䵽��ǰ���͵�һ���죬\n"
                       "�������϶Ǹ���$n��������һ����У���������������"HIR"���ǽ"HIY"Ҳ�����������С�\n" NOR;
                target->receive_damage("qi", me->query_skill("force"), me);
                p=query("qi", target)*100/query("max_qi", target);
                msg += "( $n"+eff_status_msg(p)+" )\n";
                msg = replace_string(msg, "$l", "�Ǹ�");
                msg = replace_string(msg, "$w", HIW"��"NOR);
        }
        else {
                me->start_busy(3);
                if( query("neili", me)>10)set("neili", 10, me);
                msg += HIY"$nֻ��Ŀ�ɿڴ���һ��֮�䣬"HIR"��ǽ"HIY"���䵽��ǰ����æԾ��"HIR"��ǽ"HIY"������$p����·ɹ���\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

int start_huoqiang(object me)
{
        string msg, tar;
        object target, ob;
        int neili_lost, period, neili, neili2;

        if(!me) return 0;
        tar=query_temp("huoqiang_target", me);
        target = present(tar, environment(me));
        if (! objectp(target)) return 0;
        neili_lost=30+target->query_skill("force")/10+query("jiali", me)/2+query("jiali", target)/2;
        period=query_temp("huoqiang/period", me);
        neili=query("neili", me);
        neili2=query("neili", target);

        addn("neili", -100, me);
        me->improve_skill("force", random(2));

        if(me->is_ghost()) return 0;
        if(!target || target->is_ghost() || environment(me)!=environment(target)){
                message_combatd(CYN"$N�����ھ�һ�գ���һ˫����㼴���£�ҡҡ�ϻϵ�վ��������\n"NOR, me);
                return 0;
        }
        if(neili < neili_lost){
                message_combatd(HIY"$N�������Ĵ���������֧���أ�\n"NOR, me);
                me->unconcious();
                return 0;
        }
        if(!living(target) && living(me)){
                msg = HIR"$N˫���ĳ���һ��"GRN"����"HIR"�³�������$n��$p�˿�����˿��������أ���վ��������������Ҳ�ޡ�\n"
                      GRN"����"HIR"һ�䵽$p���ϣ���ʱ��ͷ�����Ż𣬿�вҺ����У�ȫ������"RED"����"HIR"֮�С�\n"NOR;
                set_temp("last_damage_from", "��"+me->name()+"ɱ", target);
                msg += "���ֻ���������������죬$nһ���ҽУ���̲�����������ȥ����\n";
                msg += "( "RED"$n���˹��أ��Ѿ�������в�����ʱ�����ܶ�����"NOR")\n";
                message_combatd(msg, me, target);
                target->die(me);
                return 0;
        }
        if(!living(me) && !living(target)){
                message_combatd(HIW"��ʱ$N���϶����ް��Ѫɫ�������Ѿ������;��ƿ�֮ʱ��\n"NOR,me);
                set_temp("last_damage_from", "��"+target->name()+"ͬ���ھ�", me);
                me->die();
                return 0;
        }
        if(!objectp(ob = present("huo yan", environment(me)))){
                message_combatd(HIY"$N�ۿ����Ϩ��Ҳ�����չ���վ��������\n"NOR,me);
                return 0;
        }


        switch(period) {
        case 3:
        case 9:
        case 15:
        case 21:
        case 27:
        case 33:
        case 39:
        case 45:
        case 51:
        case 57:
        case 63:
        case 69:
        case 75:
        case 81:
        case 87:
        case 93:
        case 99:
        case 115:
        case 145:
        case 175:
        case 205:
                if(neili > neili2){
                        msg = random(2)?HIR"������һ�����$N�ķ����ƶ���\n"NOR:HIR"�ۿ�$Nʹ��ȫ������ͼ���ǲ����ƽ��ı����Ƶ���ȥ��\n"NOR;
                        message_combatd(msg,target);
                 }
                 break;
        case 12:
        case 24:
        case 42:
        case 60:
        case 78:
        case 96:
        case 125:
        case 155:
        case 185:
                 if(neili > neili2){
                        msg = random(2)?HIR"$N�ۿ�"GRN"����"HIR"$Nʹ��ȫ������ͼ���ǲ����ƽ��ı����Ƶ���ȥ��\n"NOR:HIR"$N�ۿ�"GRN"����"HIR"���Լ�������ȴ���ܿ���ͣ����������Ȼ�������������ʱ�ᱻ���������\n"NOR;
                        message_combatd(msg, target);
                 }
                 break;
        case 36:
        case 54:
        case 72:
        case 90:
        case 105:
        case 135:
        case 165:
        case 195:
                 if( query("jiali", me)>query("jiali", target)){
                        msg = random(2)?HIR"��Ƭ"GRN"����"HIR"�ڿ�����һͣ�ͣ��㻺����$N��ǰ��ȥ��$N�󾪣��������\n"
                              "��һҧ��һ��"RED"��Ѫ"HIR"���������ȥ������һʢ�����˹�����\n"NOR:HIW"$N��ʱ�������ް��Ѫɫ��һ�ڿ�"RED"��Ѫ"HIW"��ס���������ȥ��Ҫ������ƻأ�\n"NOR;
                        message_combatd(msg, me);
                 }
                 break;
        }

        period++;
        set_temp("huoqiang/period", period, me);
        return 1;
}
