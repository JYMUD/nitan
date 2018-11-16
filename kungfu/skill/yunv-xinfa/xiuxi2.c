// xiuxi.c ��Ů�ľ���ϰexert
// by April 01/08/09
// update April 01/09/22

#include <ansi.h>

/*
$Nͬ$n��ϰ��Ů�ľ�һ���ʱ�䣬ͷ�ϵ������������ࡣ
$Nһ�߸�$n��������һ�߽��Լ�������������ȫ���Ⱥ���ͷ��һ��һ�����˳�����
$n��$N�����İ�������Ů�ľ��ľ�����������ߣ����屻��ͣ�����İ�������Χ�ˣ�
*/

string *phases_me = ({
        "������������Ů�ľ�������������������������̫�����ߡ������� \n",
        "�����ڹ�������������ͷ�ϲ���΢΢���������ڹ����˻��֮��\n",
        "��������Ů�ľ��Ѿ�����һ��ʱ���������˿˿���ƣ��������ۡ�\n",
        "��ӽ��˹��������б�ȫ������ʱ������������ɵİ������������������������������Ƽ���һ�㣡\n",
        "����ϰ��Ů�ľ�ʱ��Խ��Խ����ͷ�����۰���ҲԽ��Խ�࣬��ͬ����������֮�У�\n",
        "����������е�Խ��Խ���죬��������������ҲԽ��Խ�࣬�ѽ������Χ��������\n",
        "��ֻ����һ�ɹ�ů�����ڶ��⻺����ɢ���ĵ׸��ӳ��ţ�������ϲ��\n",
});

int xiuxi(object me);
int halt_xiuxi(object me);

int exert(object me, object target)
{
        object         where = environment(me);
        int xj_lvl_me = (int)me->query_skill("yunu-xinjing", 1);        //��Ů�ľ��ȼ�me
        int force_lvl_me = (int)me->query_skill("force", 1);                //�����ڹ��ȼ�me
        int xj_lvl_target;         //��Ů�ľ��ȼ�target
        int force_lvl_target;                //�����ڹ��ȼ�target
        int v,i,j,k;                // ��ʱ����
        string *sname;        // skill����
        object *inv;        // ���ϴ��Ķ���
        mapping skl;        // ����skill

        seteuid(getuid());

        return notify_fail("��������ʱû�п��ţ�\n");
                
        if( !objectp(target) || target == me )
                return notify_fail("��Ҫ��˭һ����������\n");

        //�ǻ���Ůֻ���ڻ�����������
        if( query("gender", target) != query("gender", me )
                && !me->is_spouse_of(target)
                 && query("short", where) != "��������" )
                return notify_fail("��������һ���������߲��߰���\n");

        xj_lvl_target = (int)target->query_skill("yunu-xinjing", 1);        //��Ů�ľ��ȼ�
        force_lvl_target = (int)target->query_skill("force", 1);                //�����ڹ��ȼ�

        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( query("sleep_room", where) )
                return notify_fail("��˯���ﲻ������Ů�ľ������Ӱ�����ˡ�\n");

        if( query("no_fight", where) )
                return notify_fail("����������Ů�ľ�����ʼ���ķ����ң��޷����ƣ�ֻ�����ա�\n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("��������æ���ء�\n");
        if( target->is_busy() || query_temp("pending/exercising", target) )
                return notify_fail("��Ļ��������æ���ء�\n");

        if( me->is_fighting() )
                return notify_fail("ս���в�������Ů�ľ������߻���ħ��\n");
        if( target->is_fighting() )
                return notify_fail("����Ļ��������˵�ɡ�\n");

        if( !stringp(me->query_skill_mapped("force")) )
                return notify_fail("��������� enable ѡ����Ҫ�õ��ڹ��ķ���\n");
        if( !stringp(target->query_skill_mapped("force")) )
                return notify_fail("��Ļ�����ϲ����Ů�ľ���\n");

        if( objectp(query_temp("is_riding", me)) )
                return notify_fail("���������˹������߻���ħ�ġ�\n");
        if( objectp(query_temp("id_riding", target)) )
                return notify_fail("����������Ļ��������������ɡ�\n");

        // �����ڹ�С����Ů�ľ�60%������
        if( force_lvl_me < xj_lvl_me*60/100)
                return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");
        if( force_lvl_target < xj_lvl_target*60/100)
                return notify_fail("��Ļ�������̫���ˡ�\n");

        // lvlС��30������
        if (xj_lvl_me<30)
                return notify_fail("����������һ��������������Ȼ��Ů�ľ���Ϊ�����������޷���ת��\n");
        if (xj_lvl_target<30)
                return notify_fail("��Ļ�鹦����������\n");

        // �������
        if( query_temp("weapon", me) )
        return notify_fail("��ϰ��Ů�ľ�������֣��������ķ��ɡ�\n");
        if( query_temp("weapon", target) )
        return notify_fail("������Ļ��ѱ������°ɡ�\n");

        // ��������
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("��ϰ��Ů�ľ������½󳨿����ܼ�ʱɢ��������\n");
        inv = all_inventory(target);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("��Ļ�鿴����������������\n");

        // ���ܱ���������
        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "����"
                        && inv[i] != me && inv[i] != target
                        && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me) )
                return notify_fail("��Ŀ��֮���ѹ������������㲻�Ӻ����𣿣�\n");

        // �ڹ�Ҫ�����������Ԫ��
        k=0;
        skl=me->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
    for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;  
    }
    if ( k >=2 ) {
                return notify_fail("��о����ڲ�ͬ���������ײ��ֻ�����ա�\n");
        }
        k=0;
        skl=target->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
    for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;  
    }
    if ( k >=2 ) {
                return notify_fail("��Ļ���ڹ���̫����!\n");
        }

        if( query("neili", me)<query("max_neili", me)*60/100 )
                return notify_fail("�����ڵ�����������ϰ��Ů�ľ���\n");
        if( query("neili", target)<query("max_neili", target)*60/100 )
                return notify_fail("��Ļ���������㡣\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("���������ˣ�ֻ��һ��������������Σ�գ�\n");
        if( query("eff_qi", target)<query("max_qi", target) )
                return notify_fail("��Ļ���������ˣ��Ȱ������˰ɣ�\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("���еĶ�û��ȫ�ã�ֻ��һ��������������Σ�գ�\n");
        if( query("eff_jing", target)<query("max_jing", target) )
                return notify_fail("��Ļ���еĶ�û��ȫ�ã�\n");

        if( query("jing", me)<query("max_jing", me)*90/100 )
                return notify_fail("�����ھ��������޷�������Ϣ��������\n");
        if( query("jing", target)<query("max_jing", target)*90/100 )
                return notify_fail("��Ļ�����ھ��������޷�������Ϣ��������\n");

        if( query("jingli", me)<query("max_jingli", me)*60/100 )
                return notify_fail("�����ھ����������޷�������Ϣ��������\n");
        if( query("jingli", target)<query("max_jingli", target)*60/100 )
                return notify_fail("��Ļ�����ھ����������޷�������Ϣ��������\n");

        if( query("qi", me)<query("max_qi", me)*60/100 )
                return notify_fail("�����ڵ���̫���ˣ��޷�������Ϣ����ȫ������\n");
        if( query("qi", target)<query("max_qi", target)*60/100 )
                return notify_fail("��Ļ�����ڵ���̫���ˣ��޷�������Ϣ����ȫ������\n");

        // ���ܿ���ϰ���� ---- 30n-1ʱ�������
        if ( (xj_lvl_me<270) && ((xj_lvl_me+1)/30*30 == xj_lvl_me + 1) )
                return notify_fail("�������ϰ����Ů�ľ�����Ȼ��������һ��... \n"
                        +"���ƺ��������޷�ͻ��ƿ����������ʱ������ˡ� \n");
        if ( (xj_lvl_target<270) && ((xj_lvl_target+1)/30*30 == xj_lvl_target +1 ) )
                return notify_fail("��Ļ��ù����ˡ�\n");

        if( query_temp("pending/xiuxi", target) != me )
        {
                set_temp("pending/xiuxi", target, me);
                message_vision("\n$N����$n˵����" 
                        + RANK_D->query_self(me) 
                        + me->name() + "�������ܺ�"
                        + RANK_D->query_respect(target) + "һ����ϰ��Ů�ľ���\n\n", me, target);
                tell_object(target,YEL"�����Ը��ͶԷ�һ����ϰ��Ů�ľ�������Ҳ��"+me->name()+"("+query("id", me)+")"+"��һ��yunxiuxi2ָ�\n"NOR);
                write(YEL "���ڶԷ�������ҿ��Ƶ���������ȶԷ�ͬ����ܹ�ͬ��ϰ��Ů�ľ���\n" NOR);
                return 1;
        }
        else
        {
                message_vision("\n$N��$n�⿪��������ϥ���£�������ԣ���ʼ��ͬ��ϰ��Ů�ľ���\n" , me, target);
                set_temp("pending/target", target, me);
                set_temp("pending/xiuxi", 2, me);
                me->start_busy((: xiuxi :), (:halt_xiuxi:));
                set_temp("pending/xiuxi", 2, target);
                set_temp("pending/target", me, target);
                target->start_busy((: xiuxi :), (:halt_xiuxi:));
        }
        
        return 1;
}

int xiuxi(object me)
{
        int qi_cost;        //������
        int jingli_cost;        //��������
        int neili_gain;                //��������
        int xj_gain;        //�ľ�����
        int love_gain;        //lovingness����
        int xj_lvl = (int)me->query_skill("yunu-xinjing",1);        //�ľ�����
        int force_lvl = (int)me->query_skill("force",1);        //�����ڹ�����
        float f,g,h;        //�ɱ����
        string wiz_report;        //��ʦ����
        object where = environment(me);        //������
        object target=query_temp("pending/target", me);//���
        int xj_lvl_target = (int)target->query_skill("yunu-xinjing",1);        //����ľ�����
        object *inv;
        int i;

        //���ͣ��ͣ
        if( query_temp("pending/xiuxi", target) != 2 )
        {
                message_vision("$N���������е�����ǿ��ѹ�ص����ֹ��������\n", me);
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                if( query("neili", me)<query("max_neili", me)*2);
                else {
                        if( query("max_neili", me)>me->query_skill("force")*query("con", me)*2/3){
                                write("���������Ϊ�ƺ��Ѿ��ﵽ��ƿ����\n");
                                set("neili",query("max_neili",  me), me);
                        }
                        else {
                                addn("max_neili", 1, me);
                                set("neili",query("max_neili",  me), me);
                                write("������������ˣ���\n");
                        }
                }
                return 0;
        }

        if( me->query_skill_mapped("force") != "yunu-xinjing" ){
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        if( me->is_fighting() ){
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        // ��������
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2){
        set("neili", 0, me);
        set("jingli", 50, me);
        set("qi", 50, me);
                i=(query("max_jing", me)*65/100);
                set("eff_jing", i, me);
                write("ͻȻ�������������𽥻��ۣ��޷���ɢ��������ʱ�����������������������Կ��ơ� \n"
                        +"����һҧ��������һ����Ѫ���Ų������߻���ħ��\n");
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "����"
                        && inv[i] != me && inv[i] != target
                        && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me)){
                                write("ͻȻ���㷢���������˹�����\n���ǻ�æ��ֹ������\n");
                                set_temp("pending/xiuxi", 0, me);
                                set_temp("pending/target", me, me);
                                return 0;
                }

        //�������ĺ����ã����Ǹ��ӵ��㷨
        neili_gain = 1 + (int)me->query_skill("force") / 8;
        jingli_cost = to_int(sqrt((xj_lvl/to_float(150)))*60);
        qi_cost = jingli_cost + neili_gain;

        if( query("qi", me)>query("max_qi", me)*30/100
                 && query("jingli", me)>query("max_jingli", me)*30/100
                &&         ((xj_lvl>270) || ((xj_lvl+1)/30*30 != xj_lvl+1)))
        {
                addn("neili", neili_gain, me);
                addn("combat_exp", 1, me);
/*
                f=to_float(query("combat_exp", target))/to_float(query("combat_exp", me));
                if (f>=2) f=2;
                else if (f>=0.5) f = to_float(1.8*pow(f-0.5,0.25));
                else f=0;
                xj_gain = to_int(pow(force_lvl/4+1,1.1)*f);
*/
                if (xj_lvl_target > xj_lvl * 2/3 ) xj_gain = to_int(pow(force_lvl/4+1,1.1)*1.5);
                else xj_gain = to_int(pow(force_lvl/4+1,1.1)*1.2);

                if (me->is_spouse_of(target)){
                        xj_gain *= 1.5;
                        love_gain =xj_gain*2;
                }
                else if( query("gender", me) != query("gender", target))xj_gain*=1.2;
                me->improve_skill("yunu-xinjing", xj_gain, 0);
                write(phases_me[random(6)]);
                me->receive_damage("qi", qi_cost, "���ڹ��߻���ħ����");
                me->receive_damage("jingli", jingli_cost, "���ڹ��߻���ħ����");

                wiz_report = "ÿ�ε�"+chinese_number(neili_gain)+"��������"
                        +chinese_number(xj_gain)+"����Ů�ľ�";
                if (me->is_spouse_of(target)){
                        wiz_report = wiz_report+chinese_number(love_gain)+"��˫��˫��";
                        me->improve_skill("lovingness", love_gain, 0);
                }
                wiz_report = wiz_report + "; \n ����" + chinese_number(qi_cost) + "������"
                        +chinese_number(jingli_cost)+"�㾫����\n";

                  if( wizardp(me) ) tell_object(me, wiz_report);

                return 1;
        }
        else {
                set_temp("pending/xiuxi", 0, me);
                message_vision("$N��$n�˹���ϣ���Ϣ���£���̬���ɵ�վ��������\n", me,target);
                if( query("neili", me)<query("max_neili", me)*2);
                else {
                        if( query("max_neili", me)>me->query_skill("force")*query("con", me)*2/3){
                                write("���������Ϊ�ƺ��Ѿ��ﵽ��ƿ����\n");
                                set("neili",query("max_neili",  me), me);
                        }
                        else {
                                addn("max_neili", 1, me);
                                set("neili",query("max_neili",  me), me);
                                write("������������ˣ���\n");
                        }
                }
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }
}

int halt_xiuxi(object me)
{
        if( query("neili", me)>query("max_neili", me)*2 )
        set("neili",query("max_neili",  me)*2, me);
        set_temp("pending/xiuxi", 0, me);
        set_temp("pending/target", me, me);
        message_vision("$N���������е�����ǿ��ѹ�ص����ֹ��������\n", me);
        return 1;
}
