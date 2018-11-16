
// yiyang.c һ��ָ��ע������

#include <ansi.h>

inherit F_SSERVER;

string name() { return "һ������"; }

private int remove_effect(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill, skill1, damage;

        if (me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "duanshi-xinfa")
                return notify_fail("�����õ��ڹ��ķ����ԣ��޷�����һ��ָ��\n");

        if( query_temp("yiyang", me) )
                return notify_fail("������һ��ָָ�����������ˣ�\n");

        if (me->query_skill("force",1)<100
                || (me->query_skill("kurong-changong",1)<100 &&
                    me->query_skill("duanshi-xinfa",1)<100)
                || me->query_skill("duanjia-jian",1)<100
                || me->query_skill("sun-finger",1)<120)
                return notify_fail("��Ĺ����������޷�����һ��ָָ���������ϣ�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || query("skill_type", weapon) != "sword" )
                return notify_fail("��û��ʹ����ȷ���������޷���һ��ָ�������ϡ�\n");

        if( query_temp("yiyang", weapon) )
                return notify_fail("�������Ѿ�ע����һ��ָָ����\n");

        if( query("neili", me) <= 300 )
                return notify_fail("�������������һ��ָ����\n");

        if( query("jingli", me) <= 100 )
                return notify_fail("��ľ���������һ��ָ����\n");

        if( query("weapon_prop/damage", weapon) >= 5000 )
                return notify_fail("�㷢�������������ľ����ޱȣ��ɶ��칦���޷���ע���������ϣ�\n");

        message("vision",HIY"\n"+query("name", me)+"����"+query("name", weapon)+"��������Ƭ�̡�\n\n"NOR,environment(me),me);
        tell_object(me,HIY"\n��������������һ��ָָ����ע��"+query("name", weapon)+"�ϡ�\n\n"NOR);

        skill = me->query_skill("force");

        set_temp("yiyang", 25+skill/10, me);

        skill = me->query_skill("sun-finger",1) + me->query_skill("kurong-changong",1);
        skill /= 3;
        set_temp("rig",query("weapon_prop/damage",  weapon), weapon);
        set_temp("yiyang", 1, weapon);

        if( query("weapon_prop/damage", weapon)<1000 )
                damage = 3000 + skill;
        else if( query("weapon_prop/damage", weapon)<3000 )
                damage = 2000 + skill;
        else if( query("weapon_prop/damage", weapon)<5000 )
                damage = 1000 + skill;

        addn("weapon_prop/damage", damage, weapon);
        addn_temp("apply/damage", damage, me);
        call_out("checking", 1, me, weapon);
        addn("neili", -200, me);
        addn("jingli", -50, me);

        return 1;
}

void checking(object me, object weapon)
{
        if (!me) {
                if (!weapon) return;
                set("weapon_prop/damage",query_temp("rig",  weapon), weapon);
                delete_temp("yiyang", weapon);
                delete_temp("rig", weapon);
                return;
        }
        if( query_temp("yiyang", me)){
           if (!weapon)
           {
                       remove_effect(me, weapon);
                tell_object(me, HIY "\n���һ��ָָ�����˻�����\n\n" NOR);
                return;
           }
           else if( environment(weapon) != me || weapon != query_temp("weapon", me)){
                       remove_effect(me, weapon);
                tell_object(me, HIY "\n���һ��ָָ����"+weapon->name()+"�����˻�����\n\n" NOR);
                return;
           }
           else if( query("weapon_prop", weapon) == 0){
                remove_effect(me, weapon);
                tell_object(me, HIY "\n���"+weapon->name()+"�ѻ٣����ò��ջع�ע�����ϵ�һ��ָָ����\n\n" NOR);
                return;
           }
           else if (me->query_skill_mapped("force") != "kurong-changong" &&
                    me->query_skill_mapped("force") != "duanshi-xinfa") {
                remove_effect(me, weapon);
                tell_object(me, HIY "\n��е���Ϣ�������޷����ֹ�ע��"+weapon->name()+"�ϵ�һ��ָָ����\n\n" NOR);
                return;
           }

           addn_temp("yiyang", -1, me);
           call_out("checking", 1, me, weapon);
        }
        else {
           remove_effect(me, weapon);
        tell_object(me, HIY "\n��е���Ϣ���ǣ����ò������˹�����"+weapon->name()+"���ջع�ע��һ��ָָ����\n\n" NOR);
        }
}

private int remove_effect(object me, object weapon)
{
        if (weapon)
        {
                if( query_temp("weapon", me) &&
                    query_temp("weapon", me) == weapon )
                    addn_temp("apply/damage", -query("weapon_prop/damage", weapon)+query_temp("rig", weapon), me);
                set("weapon_prop/damage",query_temp("rig",  weapon), weapon);
                delete_temp("yiyang", weapon);
                delete_temp("rig", weapon);
        }
        delete_temp("yiyang", me);
        return 1;
}