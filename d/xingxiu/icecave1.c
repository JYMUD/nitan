// Code of ShenZhou
// Ryu, 5/10/97
// wsky 2000

#include "ansi.h"
#include <room.h>


inherit ROOM;

private int blow_result(object victim);
int blow();
int do_dig();


void create()
{
        set("short", "����");
        set("long", @LONG
�����������棬�Ƕ����Ͻ��������ű�׶(icicle)�����̲��룬
��ϸ��һ�������±���������ǧ����̬�����ж��ڣ����ƽ��˹��½
��������硣
LONG );

         set("item_desc",([
                "icicle" : "��Щ��׶���̲�һ���ڻ�����ҫ��ɢ������Ө�Ĺ�������뵯(flick)�����������档\n",
        ]));

       set("exits", ([
                "west" : "/d/xingxiu/icecave2",
        ]));
        set("cost", 2);
        set("icicle", 100);
        set("bing_can", 7);

        setup();
}

void init()
{
        add_action("do_flick", "flick");
        add_action("do_flick", "tan");
//      add_action("do_lingwu", "lingwu");
        add_action("do_dig", "dig");
        remove_call_out("blow");
        call_out("blow",4 + random(3) );
}

int do_dig()
{
        remove_call_out("blow");
        call_out("blow",1 );
        return 1;
}


int do_flick(string arg) {
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return 0;

        if (me->query_busy())
                return notify_fail("����æ���ء�\n");

        if (query("icicle") < 1)
                return notify_fail("����ı�׶�㶼�������ˡ�\n");

        if( query("jing", me)<30 || query("jingli", me)<30 )
                return notify_fail("��ľ����ܼ��С�\n");

        if( arg=="icicle")
        {
        me->receive_damage("jing", 15); 
        me->receive_damage("qi", 15);
        addn("icicle", -1);
        message_vision("$N���������ָ������һ����׶��\n", me);
        if (random(me->query_skill("feixing-shu", 1)) > 30){
        me->improve_skill("feixing-shu",query("int", me));

        message_vision("$N���ɳ�ȥ�ı�׶ײ������һ����׶��ƹƹ�������졣\n", me);
        tell_object(me, "���ƺ�������һ��������ļ��ܡ�\n");
        if (me->query_skill("feixing-shu", 1) > 100)
        me->receive_damage("jing", 15);
        if (me->query_skill("feixing-shu", 1) > 150)
        me->receive_damage("jing", 15);
        }
/*
        if (query("icicle") < 1){
        remove_call_out("renew_up");
        call_out("renew_up", 100+random(200));
        }
*/
        return 1;
        }
}

int blow()
{
        object *inv = all_inventory(find_object("/d/xingxiu/icecave1"));
        object ob, me= this_player();
        int i;

        if( !this_player() || !environment(this_player()) )  return 1;
        if( base_name(environment(this_player())) !="/d/xingxiu/icecave1") return 1;

        message_vision( HIC"\n¶ˮ�Ӷ����������������ؽ���˱�׶��\n"NOR, this_player() );

        for ( i=0 ; i < sizeof(inv); i++)
        {
                if( query("race", inv[i]) == "����" )
                {
                        blow_result(inv[i]);
                }
        }


        remove_call_out("blow");
        call_out( "blow",4 + random(6) );
        return 1;

}


private int blow_result(object victim)
{
        object me, fighter, room;
        int skill, exp;
        mapping fam;
        
        fam=query("family", this_player());
        me = this_player();
        room = this_object();
        exp=query("combat_exp", me);

        if( random(50)<1 && !me->is_fighting() && fam["family_name"] =="������")
        {

             message_vision(HIR"$Nֻ����һ��ŭ�ȣ��Ӻڰ����������һ�ˣ���$N������\n"NOR,me);
             fighter = new(CLASS_D("generate") + "/xxnpc.c");
             NPC_D->set_from_me(fighter, me, 110 + random(20));
             fighter->addn_temp("apply/attack",fighter->query_skill("force")*
                                             1/ 15);
             fighter->addn_temp("apply/dodge",fighter->query_skill("force")*
                                             1/ 15);
             fighter->addn_temp("apply/parry",fighter->query_skill("force")*
                                             1/ 15);
             addn_temp("apply/damage", 5+1*7, fighter);
             addn_temp("apply/unarmed_damage", 5+1*7, fighter);
             addn_temp("apply/armor", 10+1*15, fighter);
             set("player",query("id",  me), fighter);

             fighter->move(room); 
             if( !fighter->is_killing(me) ) fighter->kill_ob(me);    
        }


        if( random(victim->query_skill("force"))>45 && query("neili", victim)>20 && victim->query_skill("feixing-shu",1)>100 )
        {
                message_vision( WHT"\n$N�˹�����������ͬʱ���Ŷ����ı�׶�������Ű����ذ��\n"NOR, victim );
                if(query("icicle")<100) addn("icicle", 1+random(6));
                addn("neili", -random(40), victim);
                victim->improve_skill("feixing-shu",query("int", me));
        }
        else
        {
                message_vision( RED"\n$N���˸������\n"NOR, victim );
                victim->receive_damage("qi", random(50));
                if(query("icicle")<100) addn("icicle", 1+random(3));
        }


        return 1;
}


/*

void renew_up()
{
        set("icicle", 100);
}
*/