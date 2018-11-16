//Cracked by Kafei
// qingzhu-ling.c ������

#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name("������", ({"qingzhu ling", "bamboo", "ling"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","����һ���������Ƶ����ƣ�������ⷢ������ʴ�š�ؤ��������֡�\n");
                set("material", "bamboo");
        }
}

void init()
{
        add_action("do_bihua", "bihua");
        add_action("do_bihua", "bi");
        add_action("do_halt", "halt");
        add_action("do_halt", "h");
        add_action("do_look", "look");
        add_action("do_look", "l");
}

int do_bihua(string arg)
{     
        object ob1, ob2, old_target;
        string family;

        ob1 = this_player();
        
        if( !arg || arg=="" ) 
        return notify_fail("�����˭�Ȼ���\n");  

        if( query_temp("busy", this_object()) )
        return notify_fail("ÿ��ֻ�������˲μӱ��䡣\n");

        if( !objectp( ob2 = present(arg, environment(ob1)) ) ) 
        return notify_fail("�����˭�Ȼ���\n");

        if( query_temp("owner", this_object()) != query("name", ob1) )
        return notify_fail("�㲻���������������ˣ�\n");

        if( !stringp(family=query("family/family_name", ob1)) )
        return notify_fail("�㲻��ؤ����ӣ�����ʹ����������˱Ȼ��书��\n");

        if( !stringp(family=query("family/family_name", ob2)) )
        return notify_fail("�Է�����ؤ����ӣ��㲻��ʹ����������֮�Ȼ��书��\n");

        if( query("rank", ob2) != query("rank", ob1) )
        return notify_fail("�Է��ڰ��еĵȼ����㲻ͬ�����ܻ�����գ�\n");

        if( !objectp( present("qingzhu ling", ob2) ) ) 
        return notify_fail("�Է�û����������ǲ��ܻ�����գ�\n");

        if( query_temp("gaibang_winner", ob1) )
        return notify_fail("���Ѿ���ѹͬ�ţ��Ͽ��Ҵ�ʦ�ֱ��԰� ��\n");

        if( query_temp("loser", this_object()) == query("name", ob2) )
        return notify_fail("�Է���������°ܽ����㲻����֮�Ȼ����գ�\n");

        if( ob1 == ob2)    
        return notify_fail("�㲻�ܹ����Լ���\n");

        if( query_temp("win_times", this_object()) >= 1 )
        return notify_fail("���Ѿ�սʤͬ��һ�Σ����ؼ����������ա�\n");

        if( userp(ob2) && query_temp("pending/fight", ob2) != ob1){
                message_vision("\n$N����$n˵����" 
                        + RANK_D->query_self(ob1) 
                        + ob1->name() + "���ʦ�ֵĸ��У�\n\n", ob1, ob2);
                if( objectp(old_target=query_temp("pending/fight", ob1)) )
                        tell_object(old_target, YEL + ob1->name() + "ȡ���˺�����Ե���ͷ��\n" NOR);
                set_temp("pending/fight", ob2, ob1);
                tell_object(ob2,YEL"�����Ը��ͶԷ����б��ԣ�����Ҳ��"+ob1->name()+"("+query("id", ob1)+")"+"��һ��bihuaָ�\n"NOR);

                write(YEL "���ڶԷ�������ҿ��Ƶ���������ȶԷ�ͬ����ܽ��б��ԡ�\n" NOR);
                return 1;
        }
            
        delete_temp("halted", ob1);
        delete_temp("halted", ob2);

        remove_call_out("fighting");
        call_out("fighting", 2, ob1, ob2);

        return 1;
}

void fighting(object ob1, object ob2)
{
        message_vision("\n" + ob1->name() + "��" + ob2->name() + "��ʼ���䣡\n\n", ob1);

        remove_call_out("checking");
        call_out("checking", 0, ob1, ob2);

        this_object()->set_temp("busy");

        ob1->fight_ob(ob2);
        ob2->fight_ob(ob1);
}

int checking(object ob1, object ob2)
{
        object ob; 
        
        if(ob1->is_fighting()) 
        {
                call_out("checking", 1, ob1, ob2);
                return 1;
        }

        delete_temp("pending/fight", ob1);
        delete_temp("pending/fight", ob2);

        if ( !present(ob1, environment(ob2)) ) return 1;

        if ( !present(ob2, environment(ob1)) ) return 1;
           
        if( query_temp("halted", ob1) )
        {
                delete_temp("halted", ob1);
                return 1;
        }

        if( query_temp("halted", ob2) )
        {
                delete_temp("halted", ob2);
                return 1;
        }

        if( query("qi", ob1)*2>query("max_qi", ob1) )
        {
                if( query("qi", ob2)*2>query("max_qi", ob2)){
                        message_vision( ob1->name() + "��" + ob2->name() + 
                        "���䲻��ʤ����\n", ob1);
                        return 1;
                }
                message_vision( ob2->name() + "��" + ob1->name() + 
                        "���˹��֣����������ϻ���һ���Ǻţ���ǩ���Լ������֡�\n", ob1);

                ob = present("qingzhu ling", ob1);
                addn_temp("win_times", 1, ob);
                set_temp("loser",query("name",  ob2), ob);
                set_temp("gaibang_winner", 1, ob1);
        } 
        else 
        {
                message_vision( ob1->name() + "��" + ob2->name() + 
                        "���˹��֣����������ϻ���һ���Ǻţ���ǩ���Լ������֡�\n", ob1);

                ob = present("qingzhu ling", ob2);
                addn_temp("win_times", 1, ob);
                set_temp("loser",query("name",  ob1), ob);
                set_temp("gaibang_winner", 1, ob2);
        }

        delete_temp("busy", this_object());

        return 1;

}

int do_halt()
{
        object me = this_player();

        if (me->is_fighting())
        set_temp("halted", 1, me);
        return 0;
}

int do_look(string arg)
{
        object ob = this_object();

        if( !arg || arg == "" ) return 0;

        if( present(arg, this_player()) != ob ) return 0;

        if( query_temp("win_times", ob)){
                tell_object( this_player(), 
                "����һ���������Ƶ����ƣ�������ⷢ������ʴ�š�ؤ��������֣�\n" +
                "������ı������һ����ʾʤ���ļǺš�������"+query_temp("loser", ob)+
                "��ǩ����\n");

                tell_object(this_player(),"\n����������ɼ���ǩ��������"+query_temp("owner", ob)+"��\n");
        }
        else         tell_object( this_player(), 
                "����һ���������Ƶ����ƣ�������ⷢ������ʴ�š�ؤ��������֡�\n" );

        return 1;
}