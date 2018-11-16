// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
#define SNAKE_STAFF query_temp("weapon", this_player())

inherit F_SSERVER;

string name() { return "����ҧ��"; }
//void remove_bite(object);

int perform(object me, object target)
{
        string type, snake_path, msg;
        object weapon, snake;
        int t, lv, poison, poi_amount, train_lv, snake_lv, damage, dp, i;

        t=query_temp("baituo/bite", me);
        lv = (int)me->query_skill("lingshe-zhangfa", 1);
        poison = (int)me->query_skill("poison", 1);
        train_lv = (int)me->query_skill("training", 1);

        poi_amount = lv + poison;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("��ֻ������͵Ϯս���еĶ��֡�\n");

        if (lv < 200 )
                return notify_fail("��������ȷ�������죬�޷���ʹ�ȹ���֮���������ˡ�\n");

        if (poison < 200 )
                return notify_fail("���ʹ���ķ�����֪���ޡ�\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                 return notify_fail("������û�����ߵı�����\n");

        type=query("snake_type", weapon);

        if( !type && query("id", weapon) != "she zhang" )
                return notify_fail("���"+weapon->name()+"�ϲ�û���ߡ�\n");

        if( t && (time() - t) < 5 )
                return notify_fail("��ո��Ѿ��������ˣ������͹ʼ���ʩ������������Ч��\n");

        if( me->query_skill("training",1) < 100 )
               return notify_fail("���Ԧ�����޷�˳����ʹ�������ˡ�\n");

        if( query("neili", me)<poi_amount )
                return notify_fail("�����������������������Ϯ��ʱ�ȿ�"+weapon->name()+"��\n");

        if( query("jingli", me)<300 )
                return notify_fail("��ľ�������������������Ϯ��ʱ�ȿ�"+weapon->name()+"��\n");

        if(( me->query_skill_mapped("force") != "hama-gong") && ( me->query_skill_mapped("force") != "jiuyin-hamagong"))
                return notify_fail("�����õ��ڹ��롸�����ȷ�����·��㣣�\n");

        addn("neili", -(poi_amount/2+50), me);
        addn("jingli", -200, me);

        switch (type) {
        case "����" :
        snake_path = "/d/baituo/npc/guaishe";
        break;
        case "����" :
        snake_path = "/d/baituo/npc/lingshe";
        break;
        default:
        snake_path = "/d/baituo/npc/snake";
        type = "����";
        }

        seteuid(getuid());

        snake = new(snake_path);

        snake_lv = (train_lv + lv)*2/3;

        set("bite_busy", 1, snake);
        set("env/invisible", 10, snake);
        set("owner", me, snake);
        snake->move(environment(me));
        set("default_actions", (:call_other,__FILE__,"query_action":), snake);
        set("combat_exp",query("combat_exp",  me), snake);

        addn_temp("apply/speed", 2, snake);
        addn_temp("apply/attack", snake_lv, snake);
        addn_temp("apply/damage", snake_lv, snake);
        set("neili",query("neili",  me), snake);
        set("jingli",query("max_jingli",  me)*2, snake);
        set("max_jingli",query("max_jingli",  me), snake);
        set("snake_poison", poi_amount*5, snake);
        snake->kill_ob(target);

        message_combatd(HIB"\n$N��"+weapon->name()+HIB"һ�������Ͻ𻷵���һ�����죬һ��"+type+HIB"���ȵ�ֱ��������\n"NOR,me);

        me->start_busy(1);

        COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
        COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));

        if( query("snake", weapon) == 2){
                set("second_attack", 1, snake);
                COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
                COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
        }

        destruct(snake);
        damage = lv +  poison + train_lv + me->query_skill("staff",1);
        damage += (damage);
        dp=target->query_skill("dodge")+target->query_skill("training",1);
        if (damage/2+random(damage)>dp)
        {
                addn("neili", -200, me);
                message_combatd(HIB"\n$N��Ȼ��"+weapon->name()+HIB"��ͷ����������$n��Ϊ�������߶�����������\n"NOR,me,target);
                COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100);
        }

        target->kill_ob(me);
        set_temp("baituo/bite", time(), me);

        call_out("remove_bite", 5, me, type);

        return 1;
}

void remove_bite(object me, string type)
{
        if (! objectp(me)) return;
        delete_temp("baituo/bite", me);
        tell_object(me, type+"������ͷ��˻��һ����ͷ��\n");
}

mapping query_action(object me)
{
        string msg1, msg2;
        msg1 = HIR"���"+SNAKE_STAFF->name()+HIR"��$n��ǰ�ӹ�������������һ��$N������������Ȼ�ſ�ҧ��$n$l����������֮����"NOR;
        msg2 = HIW BLK"һ��$N�Ÿմܳ����䲻��"+SNAKE_STAFF->name()+HIW BLK"����һ��$NҲ����û��Ϣ�ذ��׶���һ����$n$lҧȥ��"NOR;
        return ([
        "action":query("second_attack", me)?msg2:msg1,
        "force" : 400,
        "dodge" : 0,
        "parry" : 0,
        "damage" : 400,
        "weapon" :"����",
        "damage_type":"ҧ��"]);
}