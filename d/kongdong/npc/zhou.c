// zhou.c

inherit NPC;
#include <ansi.h>
string *pashan_msg = ({
        HIR"�������������˼����������Ų������Ƶ�ջ�����˹�ȥ......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,        
        HIG"�ۿ��������Ѿ�����ջ��������......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,
        HIR"ֻ��������������һ��һ������ǰŲ......\n"NOR,         
        });



void create()
{
        set_name("������", ({ "zhou zhenren","zhou","zhenren" }) );
        set("title","������");
        set("gender", "����" );
        set("age",40);
        set("social_exp",2000);
        set("combat_exp",10000000);
        set_force(3000,3000,300);
        set("attitude", "friendly");
	set_wugong("qishang-quan",150,150,1);
	set_wugong("luofeng",30,30,1);
	set_xiuwei("dodge",3300);
	set_xiuwei("unarmed",5300);
        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}

void init()
{
    object ppl;

    ::init();
    if ( userp( ppl = this_player() ) 
        && can_act()
        &&!this_object()->query_temp("have") ) 
    {
        remove_call_out( "Greeting" );
        call_out( "Greeting", 5, ppl );
       	this_object()->set_temp("have",1);
    }
    if(environment(this_object())->query("short")==WHT"���׶�"NOR)
        remove_call_out( "say" );
        call_out( "say", 5, ppl );    
}

void Greeting( object ppl )
{
    command("nod "+ppl->query("id"));
    command( "climb ջ��" );     
}

void say(object ppl)
{
	
	}
/*
int refuse_killing(object me)
{
        command("nokill "+me->query("id"));
        me->unconcious();
    return 1;
}
*/

