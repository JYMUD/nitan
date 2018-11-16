// food.c

#include <name.h>

//string short() { return name() + "(" + capitalize(query("id")) + ")"; }

mixed func = 0;
int is_food() { return 1; }

void apply_effect(function f)
{
        if( !func )
                func = f;
        else if( functionp(func) )
                func = ({ func, f });
        else if( sizeof(func) < 12 )
                func += ({ f });
}

void clear_effect()
{
        func = 0;
}

mixed query_effect()
{
        return func;
}

void do_effect()
{
        int i;

        if( functionp(func) )
                evaluate(func);
        if( arrayp(func) )
                for( i=0; i < sizeof(func); i++ )
                        evaluate(func[i]);
}

string extra_long()
{
        string str;

        str =  "��Ʒ����    ��    ʳ��\n";
        str += sprintf("��    ��    ��    %d\n", this_object()->query_weight());
        str += sprintf("��    ��    ��    %d\n", query("food_supply"));
        str += sprintf("ʣ    ��    ��    %d\n", query("food_remaining"));
        str += sprintf("ʹ�÷�ʽ    ��    ����ָ�� eat %s ʳ�á�\n", query("id"));
        if( this_object()->query_autoload() )
                str += "���߶�ʧ    ��    ��\n";
        else
                str += "���߶�ʧ    ��    ��\n";
        return str;
}

int feed_ob(object me)
{
        string str;
        if( me->is_busy() )
                return notify_fail("����һ��������û����ɡ�\n");
        if( !living(me) ) return 0;

        if( stringp(query("food_race")) )
                return notify_fail( "��ɲ��Ǹ��˳ԵĶ�����\n");

        if( !query("food_remaining") )
                return notify_fail( name() + "�Ѿ�ûʲô�óԵ��ˡ�\n");
        if( (int)query("food", me) >= (int)me->max_food_capacity() )
                return notify_fail("���Ѿ���̫���ˣ���Ҳ�������κζ����ˡ�\n");

        addn("food", query("food_supply"), me);

        addn("jingli", query("food_supply")/5, me);
        if( query("jingli", me) > query("max_jingli", me))
                set("jingli", query("max_jingli",me), me);

        if( me->is_fighting() ) me->start_busy(2);

        // This allows customization of drinking effect.
        if( query("eat_func") ) return 1;

        set("value", 0);
        addn("food_remaining", -1);
        if( !query("food_remaining") ) {
                if( !stringp(str = query("eat_all")) )
                str = "$N��ʣ�µ�$n�Ե�ǬǬ������\n";
                message_vision(str, this_player(),this_object());
                if( !this_object()->finish_eat() )
                        destruct(this_object());
        } else  {
                if( !stringp(str = query("eat_msg")) )
                str = "$N����$nҧ�˼��ڡ�\n";
                message_vision(str, this_player(),this_object());
        }
        //me->start_busy(1);
        return 1;
}

void init()
{
        if( !query("decay") && userp(environment()) ) {
                set("decay", 1);
                remove_call_out("decay");
                call_out("decay", 280);
        }
}

void decay()
{
        object me = this_object(), ob = environment();
        if( !me || !ob ) return;
        switch(addn("decay", 1))
        {
                case 2:
                        set_temp("apply/long",({query("long")+"���ǿ��������Ǻ����ʡ�\n"}));
                        tell_object(ob, me->name()+"����ɫ��Щ�����ˡ�\n");
                        break;
                case 3:
                        set_temp("apply/long", ({query("long")+"��������ɢ����һ�����ŵ�ζ����\n"}));
                        tell_object(ob,me->name()+"ɢ����һ�����ŵ�ζ����\n");
                        break;
                case 4:
                        set_temp("apply/long",({query("long")+"������Щ�����ˡ�\n"}));
                        tell_object(ob,me->name()+"��Щ�����ˣ������̱ǵ�ζ����\n");
                        break;
                default:
                        tell_object(ob,me->name()+"�������õ��ˡ�\n");
                        destruct(this_object());
                        return;
        }
        remove_call_out("decay");
        call_out("decay", 150);
}