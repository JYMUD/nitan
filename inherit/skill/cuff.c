inherit SKILL;

mixed hit_ob(object me, object victim, int damage_bonus)
{
   if (random(me->query_skill("cuff"))>150) { 
        victim->apply_condition("cuff_power", 1 +me->query_condition("cuff_power")+query("jiali",me));
    }
}

//be_hit_ob(object me, object victim, int damage_bonus) 
//��������ʱ�����ܺ��ߵ�parry�Ϲ���ı�����Ч��,
//damage_bonus ��������ɵ��ܵ��˺�ֵ,���û�б�
//���Ͳ��������˺�ֵ
 
