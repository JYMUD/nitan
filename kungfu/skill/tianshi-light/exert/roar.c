// roar.c �λ�Բ����
#include <ansi.h>
inherit F_CLEAN_UP;
int exert(object me, object target)
{
    object *ob;
    int i, skill, damage;
    if ( !wizardp(me)) return 0 ;
    skill = me->query_skill("force");
    message_vision(
        HIY "$N��������˼�ȫ����������һ�����λ�Բ��������\n" NOR, me);
    ob = all_inventory(environment(me));
    for(i=0; i<sizeof(ob); i++) {
        if( !living(ob[i]) || ob[i]==me ) continue;
        if (userp(ob[i]) && !wizardp(ob[i])) continue;
        if( skill/2+random(skill/2)<query("con", ob[i])*2)continue;
        
        damage=skill-(query("max_neili", ob[i])/10);
        if( damage > 0 ) {
            ob[i]->receive_damage("jing", damage * 2 );
            if( query("neili", ob[i])<skill*2 )
                ob[i]->receive_wound("jing", damage);
            tell_object(ob[i], "��ֻ������ǰһƬģ����������......\n");
        }       
        if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);
        if( !me->is_killing(ob[i]) ) me->fight_ob(ob[i]);
    }
    return 1;
}
