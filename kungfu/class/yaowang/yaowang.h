// yaowang.h
#include <ansi.h>
int permit_recruit(object ob)
{
        if( query("detach/ҩ����", ob) || 
            query("betrayer/ҩ����", ob) )
        {
                command("say ���Ȼ�Ѿ��뿪��ҩ���ȣ�������Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���²��Ҳ��ţ�����ҩ������С����ȴ������ʦ֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "ҩ����" )
        {
                command("say ���������ʦָ�㣬��Ҫ���¿๦����Ҫ���Ķ��⣡");
                return 0;
        }

        return 1;
}



/*
void kill_ob(object ob)
{
        set_temp("my_killer",ob);
        remove_call_out("check");
        call_out("check",1);
        ::kill_ob(ob);
}
*/

int accept_fight(object ob)
{
        command("say ��û����Ȥ�����ܡ�");
        return 0;
}

int accept_hit(object ob)
{
        command("heng");
        command("command ��Ҫ����ô��");
        remove_call_out("check");
        call_out("check",1);
        return 1;
}

int accept_kill(object ob)
{
        command("haha");
        command("say ���ĺã��Ҿ�Ҫ������ʹ�죡");
        remove_call_out("check");
        call_out("check",1);
        return 1;
}

void check()
{
        object ob=this_object();
//        object me=query_temp("my_killer");
        object me=this_player();
        if(! present(me,environment()) )
        {
                remove_call_out("check");
                return;
        }
        if( me->is_ghost() )
        {
        remove_call_out("check");
        return;
        }
      
        switch(random(4))
        {        
        case 0:
        {
        message_vision(HIR"$N˫��һ�ӣ�һ֧�ϳ���ֱ��$n��ȥ��\n",ob,me);

        if(random(2))
        
                {
                message_vision(HIR"$Nֻ��һ�ɵ���Ϯ��,��ʱ����һ����ľ��\n"NOR,me,ob);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("flower_poison", 30 +
                                    (int)me->query_condition("flower_poison"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N����׾ٵĶ����$n�Ķϳ�����\n"NOR,me,ob);
                call_out("check",2+random(3));
                }
        }
        break;

        case 1:
        {

        message_vision(HIR"$N˫��һ�꣬������ˮ�黯��������$nȥ��\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"ֻ�������Կ���ֱ����£�����$N���в����ˣ�\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("iceshock", 30 +
                                    (int)me->query_condition("iceshock"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$Nӭ�ű����ȥ����������������÷���!\n"NOR,me);
                call_out("check",2+random(3));
                
                }
        }
        break;

        case 2:
        {

        message_vision(HIR"$N��������������$n��ȥ\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"$N�ӹ���������������ȥ��\n"NOR,me);
                message_vision(HIR"$Nֻ�����ӡ����������и���ͣ�������˸����"
                                "�ޱȵ�ƨ��\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                set("food", 0, me);
                set("water", 0, me);
                me->apply_condition("hunger", 5 +
                                    (int)me->query_condition("hunger"));
                remove_call_out("check");
                message_vision(HIR"$N���ÿ����ˡ�\n"NOR,me);
                message_vision(HIR"$N�ʵ�Ҫ�����ˡ�\n"NOR,me);
                }
        else
                {
                message_vision(HIR"$N�ӹ���������������ȥ��\n"NOR,me);
                message_vision(HIR"$Nֻ��ƣ��һɨ���գ���Ҳ�����ü�����\n"NOR,me);
                if( query("food", me)<400 )
                        set("food", 400, me);

                if( query("water", me)<400 )
                        set("water", 400, me);
                call_out("check",2+random(3));
                }
        }
        break;
        
        case 3:
        {

        message_vision(HIR"$N����һ˦��һ֧͸����ֱ��$n��ȥ��\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"$N��ʱѪ����ע�����Ⱦ����ȫ��\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("tougu_zhen", 30 +
                                    (int)me->query_condition("tougu_zhen"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N˳��͸����ķ�������Ծ�𣬶��������һ����\n"NOR,me);
                call_out("check",2+random(3));
                
                }
        }
        break;

        }
/*
        if( random(10) == 9 )
//      ����ط����������Ǻ��Ķ���������NPC������������ʯ������        
*/

}


