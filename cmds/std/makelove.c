// makelove.c
// updated by Lonely

#include <ansi.h>
#include <command.h>

void do_makelove(object me, object target);
string *loving_msg = ({ 
        HIR "$N���������$n�Ĵ������ƿ�ʼ�����ֵĸ���$n�⻬����Ӱ�ļ�����$n����������˫�������ı�ס$N...\n" NOR,
        WHT "$NҲԽ��Խ�˷ܣ����ں�$n��Ϊһ�壬ֻ��$n�����Ӱ�ġ�����������һ��������ʹ�࣬�������...\n" NOR,
        HIW "$N�Ķ���Խ��Խ�죬Խ��Խ�ͣ�$n�������$N�Ľ����ͷų���$N�İ�����������,�������ڣ���������...\n" NOR,
        HIM "��ӿ���ȵĸ߳�����$n��˳������$N�Ļ������$N����������$N����ĸ�Ū��$n�⻬��Ƥ������������...\n" NOR,
});

void do_loving(object me, object target, int n);        
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string no_tell, can_tell;
        object target, *ob;
        object where = environment(me);
        int i;

        seteuid(getuid());

        if( !(query("sleep_room", where) )
              || (query("no_sleep_room", where)) )
                return notify_fail("���������ɲ�̫�ã��Ҹ���ȫ��ĵط��ɣ�\n");

        if (! arg || ! objectp(target = present(arg, where)))
                return notify_fail("�����˭������\n");

        if( !target->is_character() || query("not_living", target) )
                return notify_fail("������ˣ��ǲ��ǻ��ˣ�\n");

        if( !query("can_speak", target) )
                return notify_fail("����ˣ����" + target->name() + "�Խ���\n");

        if (me == target)
                return notify_fail("���Լ�Ҫ���Լ�...�㻹�ǿ�ؼ��Լ��о��ɡ�\n");

        if (me->is_busy())
                return notify_fail("��������æ���أ�\n");

        if (me->is_fighting())
                return notify_fail("�߶��ֱ����������Ȼ���д��⣡\n");

        if (! userp(target))
                return notify_fail(target->name() + "һ�ţ�ŭ�����㡣(���Ǳ����˼���)\n");

        if( query("gender", me) == "����" )
                return notify_fail("�����˶���ģ���˻������£������ټ���\n");

        if( query("gender", me) == query("gender", target) )
                return notify_fail("ͬ����ô...�����Լ��ú��о���ôŪ�ɣ�����ָ�̫���ʡ�\n");

        if( query("age", me)<16 )
                return notify_fail("�㻹û�з�����ȫ���������£�\n");

        if (me->query_condition("huaiyun") > 0 ||
            target->query_condition("huaiyun") > 0)
                return notify_fail("��Ц�����и�Ҫע�ⱦ����ȫ����ô����������һ������\n");
                
        if( query_temp("pending/makelove", me) == target )
                return notify_fail("���Ѿ���������Ҫ���ˣ������˼һ�û�д�Ӧ�㡣\n");

        if( query("jing", me)*100/query("max_jing", me)<80 )
                return notify_fail("��ľ��񲻼ã�����û���������˼�������\n");

        if( query("qi", me)*100/query("max_qi", me)<60 )
                return notify_fail("���������֧������û���������˼�������\n");

        if( query("gender", me) == "����" && 
            time()-query_temp("last_makelove", me)<120 )
                return notify_fail("������������������û������һ�Ρ�\n");

        no_tell=query("env/no_tell", target);
        if (no_tell == "all" || no_tell == "ALL" ||
            is_sub(query("id", me),no_tell) )
        {
                can_tell=query("env/can_tell", target);
                if( !is_sub(query("id", me),can_tell) )
                        return notify_fail("����˲���������������\n");
        }

        ob = all_inventory(where);
        for (i = 0; i < sizeof(ob); i++)
                if (ob[i]->is_character() && ob[i] != me &&
                    ob[i] != target && ! wizardp(ob[i]))
                        return notify_fail("������б����أ��಻����˼ѽ��\n");
                        
        if( query_temp("pending/makelove", target) == me )
        {
                delete_temp("pending/makelove", target);
                if( query("gender", me) == "����" )
                        message_sort(YEL "$N���˺ð��죬ʵ���ܲ���$n������ͻȻһ�ѽ�$n������סѹ�ڴ���....\n" NOR,
                                     me, target);

                else
                        message_sort(YEL "$N������������$n���ȵ���������ͷС¹ײ����ͣ������̱����$n�Ļ��"
                                     "��$nһ�Ѻᱧ������������ķ��ڴ���....\n" NOR, me, target);
                            
                do_makelove(me, target);
                return 1;
        }

        set_temp("pending/makelove", target, me);

        message("vision", me->name() + "���ĵĺ�" + target->name() + "˵�˼��仰��\n",
                environment(me), ({ me, target }));
                
        if( query("gender", me) == "����" )
        {
                message_sort(YEL "$N�����ע����$n��˫��§��$n��С���������������$n��С����....\n" NOR, 
                             me, target);
                me->force_me("tell"+query("id", target)+
                             " �ñ���������ͺ��һ���һ�ΰɡ�");
        } else
        {
                message_sort(YEL "$N��С���������˵ģ���������ס$n�Ĳ��ӣ���ǰ����������$n�����ţ�"
                             "С���ཱུĴ��������������$n���촽....\n" NOR, me, target);                
                me->force_me("tell"+query("id", target)+
                            " ��������Ҫ��ô��");
        }

        return 1;
}

void do_makelove(object me, object target)
{
        mapping armor;
        string msg;
        string msg1, msg2;
        object man, woman;        

        if( query("gender", me) == "����" )
        {
                man = me;
                woman = target;
        } else
        {
                man = target;
                woman = me;
        }
        
        message_vision(HIB "...�����" + HIR "����" + HIB "��������...\n" NOR, me, target);
        
        msg = YEL "$N�����§��$n��˫�ִ�$n�����������ĸ�����ȥֱ�����ţ�ֻ��$p"
              "���ɵĲ�����һ�£�һʱ���������ԣ�˫�ֽ����ı�ס��$N��������"
              "�������$N�Ļ��У�ĥ����$P���ؿڣ���ʱ�����ô��⣬���������"
              "�������˽����Ľ��������ҵ�״̬��" NOR;
        msg1 = replace_string(msg, "$N", "��");
        msg1 = replace_string(msg1, "$n", woman->name());
        msg1 = replace_string(msg1, "$P", "��");
        msg1 = replace_string(msg1, "$p", "��");

        msg2 = replace_string(msg, "$N", man->name());
        msg2 = replace_string(msg2, "$n", "��");
        msg2 = replace_string(msg2, "$P", "��");
        msg2 = replace_string(msg2, "$p", "��");

        msg = replace_string(msg, "$N", man->name());
        msg = replace_string(msg, "$n", woman->name());
        msg = replace_string(msg, "$P", "��");
        msg = replace_string(msg, "$p", "��");

        msg1 = sort_string(msg1, 60);
        msg2 = sort_string(msg2, 60);
        msg  = sort_string(msg, 60);

        message("vision", msg1, man);
        message("vision", msg2, woman);
        message("vision", msg, environment(man), ({ man, woman }));      
        
        if( armor=query_temp("armor", me) && sizeof(armor) )
                me->force_me("remove all");

        if( armor=query_temp("armor", target) && sizeof(armor) )
                target->force_me("remove all");
                
        message_sort(HIM "$n�����۾����������ڴ��ϣ��е��Լ����ϵ��·�һ��һ���ı��ѵ���ͻȻ$n�е�$N���̵�����ѹ�����Լ�...\n" NOR, 
                     man, woman);

        remove_call_out("do_loving");
        call_out("do_loving", 1, man, woman, 0); 

}

void do_loving(object me, object target, int n)
{
        remove_call_out("do_loving"); 
        message_sort(loving_msg[n], me ,target); 
        
        if (n == sizeof(loving_msg) - 1) 
        {
                remove_call_out("do_over");
                call_out("do_over", 3, me, target);
                return;
        }
        call_out("do_loving", 3, me, target, n + 1); 
        return;
}

void do_over(object me, object target)
{
        set_temp("last_makelove", time(), me);
        addn("sex/"+target->name(1), 1, me);
        addn("sex/times", 1, me);
        if( query("sex/times", me) == 1 )
                set("sex/first", target->name(1), me);

        set("jing", 20, me);
        set("qi", 50, me);

        set_temp("last_makelove", time(), target);
        addn("sex/"+me->name(1), 1, target);
        addn("sex/times", 1, target);
        if( query("sex/times", target) == 1 )
                set("sex/first", me->name(1), target);

        if( query("id", target) == query("couple/couple_id", me )
         && query("id", me) == query("couple/couple_id", target )
        &&  ! target->query_condition("huaiyun")
         && !query("couple/child_id", me )
         && !query("couple/child_id", target )
        &&  random(100) < 21)
        {
                message("shout",HIR"������ϲ�¡���"HIM"��ϲ"HIY+query("name", me)+"("+query("id", me)+")"
                        HIM"��"HIY+query("name", target)+"("+query("id", target)+")"HIM"����׼��ĸ��\n"NOR,
                        users());
                message_vision(HIY "\n$NͻȻ����һ����Ż�������ߺ�������ҧҧ���������Ǹ������ġ�\n" NOR, target);
                message_vision(HIM"\n$N�����ˡ��Ͽ�֪ͨ���ӵİְ�"HIY+query("name", me)+"("+query("id", me)+")"HIM"����������\n"NOR,target);
                target->apply_condition("huaiyun", 1200);           
                set("longbak",query("long",  target), target);
                set("long", HIY"\n"+query("name", target)+"ͦ�Ÿ�����ӣ�һ����֪���ǻ����ˣ�����ɢ����һ�ɴ����ĸ����\n"NOR, target);
        }
}

int help(object me)
{
        write(@HELP
ָ���ʽ : makelove <id>
 
����������ָ������ϲ���������������Ҫ�󣬵�ȻҪ�ڰ�ȫ�ĵ�
��������Է�����������no_tell ��ѡ�����޷�������Ҫ��
�����Ժ�Ἣ��������з��ľ�������

HELP );
        return 1;
}