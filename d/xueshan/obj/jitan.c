// /d/xueshan/obj/jitan.c
// jitan.c ��̳
// Ryu
// kane

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY"������̳"NOR, ({ "fa tan", "altar", "tan" }) );
        set_weight(300000);
        set_max_encumbrance(5000000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�������Ӵ��ͭ�Ƽ�̳����Լ���ɣ���ԲԼ�����ɣ����ǵ����·�������\n"
                            "��ָ������ģ������֮����ʮ�귽�ɡ�\n");
                set("value", 1000);
                set("material", "wood");
                set("no_get",1);
        }
        setup();
}

int is_container() { return 1; }

void init()
{
        add_action("do_put", "put");
        add_action("do_light", "light");
        add_action("do_spray", "peng");
        add_action("do_dazuo", "dazuo");
        add_action("do_wave", "wave");
        add_action("do_spray", "spray");
}

int do_put(string arg)
{
        object me, obj;
        string item, target; 
        int amount;

        me = this_player();

        if (me->is_busy()
         || query_temp("pending/exercising", me )
         || query_temp("exit_blocked", me) )
                return notify_fail("��������æ���ء�\n");

        if( !arg || sscanf(arg, "%s in %s", item, target) != 2 )
                return notify_fail("��Ҫ��ʲô�����Ž����\n");
                
        if( item == "all" ) {
                write("����һ��һ�����ɡ�\n");
                return 1;
        }
                                                                
        sscanf(item, "%d %s", amount, item);
        
        if( !objectp(obj = present(item, me)) )
                return notify_fail("��Ҫ��˭ʲô������\n");

        if( query("id", obj) != "corpse"){
                write("�㲻������̳�������������\n");
                return 1;
        }

}
int do_light(string arg)
{
        object  me = this_player();

        if (!present("fire", me))
                return notify_fail("��Ҫ��ʲô���\n");
        if (!query("in_use"))
                return notify_fail("��Ҫ��ȼʲô��\n");
        if (!id(arg))
                return notify_fail("��Ҫ��ȼʲô��\n");
        if( query("pending", this_object()) != query("name", me) )
                return notify_fail("�ֲ����㳬�ȣ�Ϲ����ʲô��\n");
        message_vision(HIR"$N��ȼ�˼�̳�е�ľ�������ͣ������һ�������\n"NOR, me);
        set("burning", 1);
        set("pending",query("name", me));
        set("long", query("long") + HIR"����ȼ�����ܵĻ��档\n"NOR);
        set("in_use", 0);
        log_file("job/xueshan",query("name", me)+"("+
            query("id", me)+")��ʼ����"+ctime(time())+"\n");
        remove_call_out("burning");
        call_out("burning",20+random(20), me);
        return 1;
}
void burning(object me)
{
        int point, butter;
                object room, gang, suyou;

        // add to involve the butter stuff ***************
                butter = 0;
            if(!( room = find_object("/d/xueshan/dumudian")) )
                   room = load_object("/d/xueshan/dumudian");
            if ( objectp(gang = present("tong gang", room)) ) {
                if( gang->query_current_liquid() >= 30) {
                                // if less than 30 then can't deduct, shouldn't happen
                    if ( objectp(suyou = present("su you", gang)) ) {
                   if( (query("liquid/status", suyou) == 1) && (suyou->query_amount() >= 30)){
                                          // take 30 for each burn
                                          butter=gang->query_current_liquid();
                                          suyou->add_amount(-15);
                                      gang->add_current_liquid(-15);
                                   }
                                }
                }
            }
                // butter bonus = butter level / 200
                // for max 50000 / 200 = 250 bonus
                // for gang started at 3000 / 200 = 15 bonus
                butter = butter/200;
                // ***********************************************

        point=query_temp("award_pot", me)*10/query("combat_exp", me);
        point = point * me->query_skill("lamaism")/20;
                
        if( query("combat_exp", me)<150000)point=point/2;
        message_vision(BLU"һ˿����������̳��ȽȽ���𡣻�����$N�𷨸��٣��ǻ���ȥ��\n"NOR, me);
/************ add butter bonus ******/
                point += butter;
/************************************/
        if( query_temp("award_pot", me) )
        addn("potential", point+random(point), me);
        if( query_temp("award_doubling", me) )
                set("potential", me->query_potential_limit(), me);
        if( query("potential", me)>me->query_potential_limit() )
                set("potential", me->query_potential_limit(), me);
        set("wait_for_spray", 1);
}
int do_spray(string arg)
{
        object  ob, me = this_player();
        ob = (present("lubo", me));
        
        if (!present("lubo", me))
                return 0;
        if( query("name", me) != query("pending") )
                return notify_fail("��������ʲô���֣�\n");
        if (!query("wait_for_spray"))
                return notify_fail("ʱ��δ����\n");
        if (!id(arg))
                return notify_fail("�������Ķ��磿\n");
        if( query("liquid/remaining", ob)<1 )
                return notify_fail("­�������ˮ�Ѿ���ʣ�޼��ˡ�\n");

        message_vision(HIW"$N����­������һ��ˮ�����ۡ���һ���͵س������ܻ����罫��ȥ��\n"NOR, me);
        addn("liquid/remaining", -1, ob);
        set("wait_for_spray", 0);
        set("time_to_dazuo", 1);
        return 1;
}
int do_dazuo()      
{
        object me = this_player();

        if (me->is_busy()
         || query_temp("pending/exercising", me )
         || query_temp("exit_blocked", me) )
                return notify_fail("��������æ���ء�\n");
        
        if( query("name", me) != query("pending") )
                return notify_fail("���ʲô���֣�\n");
        if( query("neili", me)<600 )
                return notify_fail("������������\n");
        if (!query("time_to_dazuo"))
                return notify_fail("�ⲻ���������ʱ��\n");

        message_vision(HIY"$N���ȴ�����������̣����������дǣ�������һ˿������$N��ǰ���۳��Ρ�\n"NOR, me);
        me->start_busy(20);
        remove_call_out("rise");
        call_out("rise",20+random(20), me);
        return 1;
}
void rise(object me)
{
        message_vision(BLU"����Խ��Խ�࣬��Ȼ�ʳ����Σ� $N��ָ���Σ��������ԣ�ָ������֮·��\n"NOR, me);
        addn("neili", -600, me);
        if( query_temp("award_pending", me)*10/query("combat_exp", me) >= 16){
        addn("max_neili", me->query_skill("lamaism",1)/100, me);
        log_file("job/xueshan",query("name", me)+"("+query("id", me)+")�õ�"+me->query_skill("lamaism",1)/100+"���������ֵ"+ctime(time())+"\n");
        }

        if( query_temp("award_doubling", me)){
        addn("max_neili", me->query_skill("lamaism",1)/20, me);
        log_file("job/xueshan",query("name", me)+"("+query("id", me)+")�õ�"+me->query_skill("lamaism",1)/100+"���������ֵ"+ctime(time())+"\n");
        }
        set("time_to_dazuo", 0);
        set("time_to_wave", 1);
}
int do_wave(string arg)
{
        object weapon, me = this_player();

        if (!arg && arg != "ling" && arg != "fa ling")
                return notify_fail("��Ҫҡʲô��\n");
                
        if (!present("fa ling", me))
                return notify_fail("��Ҫҡʲô��\n");

        if( query("name", me) != query("pending") )
                return notify_fail("��������ʲô���֣�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || (query_temp("weapon",query("name",  me))) != "����" )
                return notify_fail("������û������������\n");
        
        if (!query("time_to_wave"))
                return notify_fail("ʱ��δ����\n");

        message_vision(CYN"$N�ֳַ��壬���߱�ҡ�������ж��ܴ����䡣ͻȻ���һ��������������\n"NOR, me);
        set("time_to_wave", 0);
        remove_call_out("close_up");
        call_out("close_up",20+random(20), me);
        me->start_busy(20);
        return 1;
}
void close_up(object me)
{
        object *inv, ob, room, gang, suyou;
        int gaining, butter, i;
    int expG, potG;
        ob = this_object();


        // add to involve the butter stuff ***************
                butter = 0;
            if(!( room = find_object("/d/xueshan/dumudian")) )
                   room = load_object("/d/xueshan/dumudian");
            if ( objectp(gang = present("tong gang", room)) ) {
                if( gang->query_current_liquid() >= 15) {
                                // if less than 15 then can't deduct, shouldn't happen
                    if ( objectp(suyou = present("su you", gang)) ) {
                   if( (query("liquid/status", suyou) == 1) && (suyou->query_amount() >= 15)){
                                          // take 30 for each burn
                                          butter=gang->query_current_liquid();
                                          suyou->add_amount(-15);
                                      gang->add_current_liquid(-15);
                                   }
                                }
                }
            }
                // butter bonus = butter level / 50
                // for max 50000 / 50 = 1000 bonus
                // for gang started at 3000 / 50 = 60 bonus
                butter = butter/50;
                // ***********************************************

        gaining=query_temp("award_pending", me)*10/query("combat_exp", me);
        gaining = 12 * gaining;
        if (gaining > 300) gaining = 300;       

        if( query("combat_exp", me)<80000 )
        gaining = gaining/3;

        if( query("combat_exp", me)>80000 && query("combat_exp", me)<100000 )
        gaining = gaining/2;

//*********** add butter bonus *******
        gaining = gaining + butter;
//************************************

        message_vision(HIW"��Ժ���ã����һ����������ָֻ���ƽ����������ϡ�\n"NOR, me);
        set("long", "����һ�������Ӵ��ͭ�Ƽ�̳����Լ���ɣ���ԲԼ�����ɣ����ǵ����·�������\n"
                    "��ָ������ģ������֮����ʮ�귽�ɡ�\n");
        set("long", query("long") + RED"����ȼ�ŵĻ����Ϩ���ˡ�\n"NOR);
        me->improve_skill("lamaism",query("int", me));
        addn("jingli", -300, me);
        set("burning", 0);
       //expG = gaining + random(gaining/2);
        expG = gaining*2 + random(gaining);
         if( query_temp("award_pending", me) )
            addn("combat_exp", expG, me);
        log_file("job/xueshan",query("name", me)+"("+query("id", me)+")���˻��"+
            expG + " �㾭��� "+ 0 + " ��ǳ�� "+ctime(time())+"\n");

       // if (me->query_temp("award_doubling"))
        //me->addn("combat_exp", (int)me->query_temp("award_pending")/50);       
        delete_temp("award_pending", me);
        delete_temp("award_doubling", me);
        delete_temp("award_pot", me);
        delete_temp("marks/��", me);

        //clean all stuff in fatan after finish  // by maco
        inv = all_inventory(ob);
        for (i=0; i < sizeof(inv); i++) 
                {
                        destruct(inv[i]);
                }

        if( random(query("potential", me)-query("leaned_points", me))>me->query_con()*10 )
        me->unconcious();

        remove_call_out("renewing");
        call_out("renewing", 50 + random(100), ob);
}

void renewing(object ob)
{
        set("last_burner",query("pending",  ob), ob);
        set("pending", 0, ob);
        ob->set("long","����һ�������Ӵ��ͭ�Ƽ�̳����Լ���ɣ���ԲԼ�����ɣ����ǵ����·�������\n"
                        "��ָ������ģ������֮����ʮ�귽�ɡ�\n");
}                                
