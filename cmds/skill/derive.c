// derive.c

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

int deriving(object me);
int halt_deriving(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where;
        int point;
        string skill;

        seteuid(getuid());
        where = environment(me);
        
        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( me->is_busy() || query_temp("pending/deriving", me) )
                return notify_fail("��������æ���ء�\n");

        if (me->is_fighting())
                return notify_fail("ս���л��Ǻúõ�����Եаɡ�\n");

        if( query("combat_exp", me)<100000 )
                return notify_fail("���ʵս����̫ǳ�����޷����ͨ��ʵս��õ��ĵá�\n");

        if( query("experience", me)<query("learned_experience", me)+60 )
                return notify_fail("�����ڻ��۵�ʵս��ỹ̫�١�\n");

        if( query("qi", me)<query("max_qi", me)*7/10 )
                return notify_fail("������û�г����������������ʵս���ĵá�\n");

        if( query("jing", me)*100/query("max_jing", me)<70 )
                return notify_fail("�����ھ��񲻼ã�����ץסʵս����е���Ҫ��\n");

        if( query("no_fight", environment(me)) && 
            (query("doing", me) != "scheme" || this_player(1)) )
                return notify_fail("���޷�������ط���������ͨ��ʵս�õ����ĵá�\n");

        if (arg && sscanf(arg, "%d %s", point, skill) == 2 ||
            arg && sscanf(arg, "%d", point) == 1)
        {
                if( query("experience", me)-query("learned_experience", me)<point )
                        return notify_fail("�㲢û�л�����ô��ʵս��ᡣ\n");

                if (point < 60)
                        return notify_fail("�ƺ�û�б�ҪΪ�����������¹���\n");
        } else
        {
                point = -1;
                if (arg)
                        sscanf(arg, "%s", skill);
        }

        if (! stringp(skill)) skill = "martial-cognize";

        write("��ĬĬ����������ǰһ��ʱ��Ͷ��ֽ���ʱ�����Σ���ʼ���ռ�ȡ���е��ĵá�\n");

        set_temp("pending/deriving", 1, me);
        set_temp("derived_point", point, me);
        set_temp("derived_skill", skill, me);
        me->set_short_desc("����������ʽ��");
        message_vision("$N�����ſ����ƣ���ǰ���������㵸���ƺ���˼��ʲô��\n", me);
        me->start_busy(bind((:call_other, __FILE__, "deriving" :), me),
                       bind((:call_other, __FILE__, "halt_deriving" :), me));
        return 1;
}

int deriving(object me)
{
        int improve;
        int cost;
        string skl_id, skl_name;
        object weapon;
        string skill;
        int r;
        int n;

        skill=query_temp("derived_skill", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" || 
            skill != "sword-cognize")
                skl_id = "martial-cognize";
        else skl_id = "sword-cognize";
 
        skl_name = to_chinese(skl_id);
                        
        if (! me->can_improve_skill(skl_id))
        {
                write("��о��Լ���ʵս���黹��Ƿȱ�����޷�"
                      "�����߾����" + skl_name + "��\n");
                message("vision", me->name() + "�����̾�˿���������"
                        "�ķ���һ����Ĵ���\n", environment(me), ({ me }));
                delete_temp("pending/deriving", me);
                me->set_short_desc(0);
                return 0;
        }

        cost = me->query_skill(skl_id, 1) / 2 + 1;
        cost+=query_temp("apply/derive_times", me);
        if (present("derive emblem", me)) 
                cost += cost * 3;
                
        if( query("special_skill/musha", me) )
                cost += cost * 50 / 100;

        if( n = ACTION_D->query_action("jiqu_speed") )
                cost *= n;

        if( cost+query("learned_experience", me)>query("experience", me) )
                cost=query("experience", me)-query("learned_experience", me);

        // gain martial-cognize & combat_exp, potential
        improve = cost * (1 + random(5 + me->query_skill(skl_id, 1) / 10));
        if( intp(r=query_temp("apply/derive_effect", me)) )
                improve += improve * r / 100;

        if( intp(r=query("jingmai/derive_effect", me)) )
                improve += improve * r / 100;

        if( query("jingmai/finish", me) )
                improve += improve * ZHOUTIAN_D->query_jingmai_effect("derive_effect")/100;
                
        // ת������Ⱥа����������ȡЧ��
        if( query("special_skill/nopoison", me) )
                improve += improve * 50 / 100; 

        if( query("special_skill/musha", me) )
                improve += improve * 50 / 100; 
        
        if( query("time_reward/study", me) )
                improve += improve * 25 / 100;
                
        // ����������
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "jiqu") )
                improve += improve * 20 / 100;

        if( me->query_family() && BUNCH_D->query_family_efficient(me->query_family(), "jiqu") )
                improve += improve * 20 / 100;
                
        if (me->can_improve_skill(skl_id))
                me->improve_skill(skl_id, improve);

        addn("combat_exp", 1+random(2), me);

        if (random(2))
                // not limit by potential limit
                addn("potential", 1, me);

        // cost experience
        if( me->add("learned_experience",cost) >= query("experience", me) )
        {
                write("�㽫ʵս�л�õ�����ĵó�ֵ����������ˡ�\n");
                message("vision", me->name() + "΢΢һЦ������������Ϊϲ�á�\n",
                        environment(me), ({ me }));
                delete_temp("pending/deriving", me);
                delete_temp("derived_point", me);
                delete_temp("derived_skill", me);
                me->set_short_desc(0);
                return 0;
        }

        if( query_temp("derived_point", me)>0 )
        {
                if( me->add_temp("derived_point",-cost)<1 )
                {
                        write("������������һЩʵս�л�õ�����ĵá�\n");
                        message("vision", me->name() + "΢΢һЦ������������Ϊϲ�á�\n",
                                environment(me), ({ me }));
                        delete_temp("pending/deriving", me);
                        delete_temp("derived_point", me);
                        delete_temp("derived_skill", me);
                        me->set_short_desc(0);
                        return 0;
                }
        }

        switch (skl_name)
        {
        case "��ѧ����":
                switch (random(20))
                {
                case 0:
                        write("����˼���ã����ڹ������������µ���ᡣ\n");
                        break;
        
                case 1:
                        write("��ĬĬ˼������ȭ�Ź�������ͨ��һЩ�ؽڡ�\n");
                        break;
        
                case 2:
                        write("�㾲����ĥ����������������һ����⡣\n");
                        break;
        
                case 3:
                        write("���ܽ��˼�ʶ�������ֱ�����������ͨ�����е�һЩ���ء�\n");
                        break;
                }
                break;

        case "��������":
                switch (random(20))
                {
                case 0:
                        write("����ӳ�����ϸϸ��Ħ������΢֮����\n");
                        break;
        
                case 1:
                        write("�����г�����Ĩ�������������������ַ��Ĳ�ͬ��\n");
                        break;
        
                case 2:
                        write("�㾲����ĥ���·���������һ�㽣���Ϲ��ؽ��˵ļ��ɡ�\n");
                        break;
        
                case 3:
                        write("����ǰ���ֳ���ͬ���ɵĸ�ʽ��������������\n");
                        break;
                }
                break;
        }

        if( random(2) && query("total_hatred", me)>0 )
        {
                // addn("total_hatred", -random(1 + cost), me);
                addn("total_hatred", -(random(10) + 1), me);
                tell_object(me, CYN "��ֻ��һ������͸��θ�������ɱ�⽥����\n" NOR);
                if( query("total_hatred", me)<0 )
                        set("total_hatred", 0, me);
        }

        return 1;
}

int halt_deriving(object me)
{
        tell_object(me, "��������ת���ջ���ͷ������˼����ѧ�ذ¡�\n");
        tell_room(environment(me), me->name() + "Ψһ��ü����ס�����ơ�\n", me);
        delete_temp("pending/deriving", me);
        delete_temp("derived_point", me);
        delete_temp("derived_skill", me);
        me->set_short_desc(0);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : derive [<����>] [ ���� ]

    ���ָ������������ռ�ȡʵս�е���ᣬ�����ֵ���������
�е��ذ��Ժ󣬿��������Լ�����ѧ����������һ�ż����ѧ�ʣ���
������ѧ�Ļ�������Ϊһ����ʦ����ѧ�����Ǳز����ٵġ������װ
���˽���������������ָ���˼�����Ϊ sword-cognize���򽫻�ý�
��������

HELP );
        return 1;
}
