// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

int in_ask, answer;
int bCheckingRobot;


void say_question(object me, object ob)
{
        // object ob = this_player();
        int a, b, c;
        string oper;

        // if( in_ask || random(20) > 10 ) return;
        if( !ob || !userp(ob) || !me || !userp(me) )
        {
                bCheckingRobot = 0;
                return;
        }

        delete_temp("wrong");
        a = random(19) + 2;
        b = random(19) + 2;
        switch(random(5)) {
                case 0:
                        answer = a + b;
                        oper = chinese_number(a) + "��" + chinese_number(b)+ "���ڶ��٣�";
                        break;
                case 1:
                        if (a < b) { c = b; b = a; a = c;}
                        answer = a - b;
                        oper = chinese_number(a) + "��ȥ" + chinese_number(b)+ "���ڶ��٣�";
                        break;
                case 2:
                        if( a * b < 200 ) {
                                answer = a * b;
                                oper = chinese_number(a) + "��" + chinese_number(b)+ "���ڶ��٣�";
                        } else {
                                answer = (a * b) % 10;
                                oper = chinese_number(a) + "��" + chinese_number(b)+ "����λ����춶��٣�";
                        }
                        break;
                case 3:
                        answer = a % b;
                        oper = chinese_number(a) + "����" + chinese_number(b)+ "�������Ƕ��٣�";
                        break;
                case 4:
                        oper = chinese_number(a) + "��" + chinese_number(b)+ "����������Ƕ��٣�";
                        if( b < a ) { c = b; b = a; a = c; }
                        while( a > 1 && b%a > 1 ) {
                                c = a;
                                a = b%a;
                                b = c;
                        }
                        answer = b%a == 1 ? 1 : a;
                        break;
        }
        message_vision("$N��$n���ʵ���"+oper + "��������ʮ��������(da <number>))��\n",me,ob);
        in_ask = 1;
        remove_call_out("say_answer");
        call_out("say_answer", 30, me,ob);
}

void say_answer(object me, object ob)
{
        object env, *inv;
        int i;

        if( !ob || !userp(ob) || !me || !userp(me) )
        {
                bCheckingRobot = 0;
                return;
        }

        addn("robot_check_wrong", 1, ob);
        call_out("ans_wrong", 1, me, ob);

        message_vision("$N˵������ô�򵥶����᣿�𰸵���" + chinese_number(answer) + "��\n",me);
        in_ask = 0;
        remove_call_out("say_question");
        call_out("say_question", 1, me, ob);
}


int do_answer(string arg)
{
        object ob = this_player();
        object partner;
        string s;
        int ans;

        if( !query_temp("partner", ob) || !query_temp("partner_id", ob) || !(partner=present(query_temp("partner_id", ob),environment(ob))) )
                return notify_fail("����û������Ҫ��֮���۵��ˡ�\n");


        if( !in_ask ) return notify_fail("��������һ�⡣\n");
        if( !arg ) return notify_fail("����ش�һ�����֡�\n");

        message_vision( CYN "$N�����" + arg + "\n" NOR, ob);

        if( sscanf(arg, "%d", ans)==1 ) {
                if( ans==answer ) {
                        addn("robot_check", 1, ob);
                        message_vision("$N˵��������ˣ�\n",partner);
                        partner->command("pat"+query("id", this_player()));

                        remove_call_out("say_answer");
                        in_ask = 0;
                        if( query("robot_check", this_player()) >= 3){
                                message_vision(HIG"$N˵�����ܺã����Ȼ���㷨�����о����������������Ǽ��������书�ɡ�\n\n"NOR,partner);
                                delete("robot_check", ob);
                                delete("robot_check_wrong", ob);
                                delete("robot_checking", ob);
                                delete("robot_check", partner);
                                delete("robot_check_wrong", partner);
                                delete("robot_checking", partner);
                                bCheckingRobot = 0;
                                return 1;
                        }
                        else
                        {
                                remove_call_out("say_question");
                                call_out("say_question", 1, partner,ob);
                        }

                } else {
                        message_vision("$N˵������\n",partner);
                        addn("robot_check_wrong", 1, this_player());
                        addn_temp("wrong/"+query("id", this_player()),1);
                        call_out("ans_wrong", 0, partner,ob);
                        if( query_temp("wrong/"+query("id", this_player()))>3){
                                message_vision(HIG"ֻ�����һ������ҩʦͻȻ������$N����ǰ��\n"NOR,ob);
                                message_vision(HIY"��ҩʦ�������ض�$N�ȵ������ⲻФ֮ͽ������ô�����ⶼ�𲻳���ȥ���ɡ�\n"NOR,ob);
                                message_vision(HIR"��ҩʦ��ָһ����һ���ھ��ƿն�������$nϮ����$Nֻ����͸�����������˵�һ�����ڵ��ϡ�\n"NOR,ob,ob);
                                message_vision(HIC"��ҩʦ����һ�ӣ���$N��վ����ߵ����⣬�����ͺ����������ǰ��ⲻФ֮ͽ�ӵ��⵺ȥ��ԽԶԽ�ã���\n\n��ҩʦ���ߺߵ����ˡ�\n\n"NOR,ob);

                                this_player()->receive_wound("qi", 100, this_object());
                                set("jingli", -1, this_player());
                                set("qi", -1, this_player());
                                this_player()->move("/d/island/icefire_land");
                                delete("robot_checking", ob);
                                delete("robot_check", ob);
                                delete("robot_check_wrong", ob);
                                bCheckingRobot = 0;
                                in_ask = 0;
                                remove_call_out("say_question");
                                remove_call_out("say_answer");
                        }

                        //remove_call_out("say_question");
                        //call_out("say_question", 1, ob);
                }
        }
        return 1;
}

int ans_wrong(object partner,object ob)
{
        if( query("robot_check_wrong", ob)>5){
                message_vision(HIG"ֻ�����һ������ҩʦͻȻ������$N����ǰ��\n"NOR,ob);
                message_vision(HIY"��ҩʦ�������ض�$N�ȵ������ⲻФ֮ͽ������ô�����ⶼ�𲻳���ȥ���ɡ�\n"NOR,ob);
                message_vision(HIR"��ҩʦ��ָһ����һ���ھ��ƿն�������$nϮ����$Nֻ����͸�����������˵�һ�����ڵ��ϡ�\n"NOR,ob,ob);
                message_vision(HIC"��ҩʦ����һ�ӣ���$N��վ����ߵ����⣬�����ͺ����������ǰ��ⲻФ֮ͽ�ӵ��⵺ȥ��ԽԶԽ�ã���\n\n��ҩʦ���ߺߵ����ˡ�\n\n"NOR,ob);

                ob->move("/d/island/icefire_land");
                delete("robot_check_wrong", ob);
                delete("robot_check", ob);
                delete("robot_checking", ob);
                delete("robot_check_wrong", partner);
                delete("robot_check", partner);
                delete("robot_checking", partner);
                bCheckingRobot = 0;
                in_ask = 0;
                remove_call_out("say_question");
                remove_call_out("say_answer");
        }
        return 1;
}


int do_discuss(string arg)
{
        object me,partner;
        int exp1, exp2, pot1, pot2, times, i;
        string name1, name2, name3, name4, target;

        me = this_player();
                  if (me->is_busy()
                   || query_temp("pending/exercising", me )
                   || query_temp("exit_blocked", me) )
                                         return notify_fail("��������æ���ء�\n");

        if( !arg || arg == getuid(me))
                return notify_fail("û������Ҫ��֮���۵��ˡ�\n");

/*
        if (sscanf(arg, "%s %d", target ,times)!=2 ) {
                times = 1;
        if( !arg || arg == getuid(me))
                return notify_fail("û������Ҫ��֮���۵��ˡ�\n");
        }
*/
        if (sscanf(arg, "%s %d", target ,times)!=2 ) {
                times = 1;
            if (sscanf(arg, "%s", target )!=1 )
                return notify_fail("����û������Ҫ��֮���۵��ˡ�\n");
        }
        
        if (times < 1) 
                return notify_fail("��Ҫ���۶��ٴΣ�\n");
        if( !(partner = present(target, environment(me))) || !partner->is_character() || me == partner)
                return notify_fail("����û������Ҫ��֮���۵��ˡ�\n");


        exp1=query_temp("exp_gain", me);
        pot1=query_temp("pot_gain", me);
        name1 = me->name();
        name3=query_temp("partner", me);
        exp2=query_temp("exp_gain", partner);
        pot2=query_temp("pot_gain", partner);
        name2 = partner->name();
        name4=query_temp("partner", partner);

        set_temp("partner_id",query("id",  me), partner);
        set_temp("partner_id",query("id",  partner), me);
        if( query("th_discuss", me)>2000 )
                return notify_fail("������������࣬Ӧ��ʵ��һ�±����书�ļ����ˡ�\n");
        if( query("th_discuss", partner)>2000 )
                return notify_fail(name2+"�Ѿ����۹��ܶ౾����ѧ��Ӧ��ʵ��һ���ˡ�\n");

/*
        if( query("huang_called", me) )
                return notify_fail("��ҩʦҪ��ȥ��������Ϊ���ӣ��õ�������ʦ�����ǣ��ɲ����д蹦���ʱ��\n");
        if( query("huang_called", partner) )
                return notify_fail("��ҩʦҪ"+name2+"ȥ��������Ϊ���ӣ��õ�������ʦ�����ǣ��ɲ����д蹦���ʱ��\n");

        if( query("th_ask", me) )
                return notify_fail("�㻹ûȥ��"+query("th_ask", me)+"�ء�\n");
        if( query("th_ask", partner) )
                return notify_fail("�Է���û������ʦ���������¡�\n");
        if( query("th_teach", me) )
                return notify_fail("���"+query("th_teach", me)+"�����򣬲Űﵽһ���ġ�\n");
        if( query("th_teach", partner) )
                return notify_fail("�Է���û������ʦ���������¡�\n");
*/
        if( (exp1 < times || exp2 < times ) && times > 1)
                return notify_fail("�����������۲�����ô��Χ��\n");

        if( query("jing", me)<20 || query("jingli", me)<20 )
                return notify_fail("��̫���ˣ��޷�����������ȥ��\n");
                  if( query("jing", partner)<20 || query("jingli", partner)<20 )
                                         return notify_fail("���ͬ��һ�������˯�����ӣ������޷�����������ȥ��\n");

        if( query("jing", me)<10+10*times || query("jingli", me)<10+10*times )
                return notify_fail("����Ŀǰ�ľ���״��������һ�����۲�������ණ����\n");
                  if( query("jing", partner)<10+10*times || query("jingli", partner)<10+10*times )
                                         return notify_fail("�ԶԷ�Ŀǰ�ľ���״��������һ�����۲�������ණ����\n");

        addn("jing", -10*times, me);
        addn("jing", -10*times, partner);
        addn("jingli", -10*times, me);
        addn("jingli", -10*times, partner);

        if( exp1 < 1 && exp2 < 1) {
                tell_object(me,CYN"���"+name2+"������һ�󣬸о��Դ��յ����ģ�һ�����á�\n"NOR);
                tell_object(partner,CYN"���"+name1+"������һ�󣬸о��Դ��յ����ģ�һ�����á�\n"NOR);
                message_vision(CYN"$N��$n����һ�ûһ��İڿ�������\n"NOR,me,partner);
                delete_temp("exp_gain", me);
                delete_temp("exp_gain", partner);
                me->start_busy(random(3));
                partner->start_busy(random(3));
                return 1;
        }

        if( exp1 < 1 ) {
                tell_object(me,CYN"����Ҫ��"+name2+"̽��һ���书�ĵã���ȴ����ûɶ��˵��...\n"NOR);
                tell_object(partner,CYN""+name1+"�ƺ���������۵�ʲ�������...\n"NOR);
                message_vision(CYN"$N��$nһ��������ֹ������ģ����\n"NOR,me,partner);
                delete_temp("exp_gain", me);
                return 1;
        }

                  if( exp2 < 1 ) {
                                         tell_object(me,CYN"����Ҫ��"+name2+"̽��һ���书�ĵã���"+name2+"ȴһ���Ĳ����ɵ�����...\n"NOR);
                                         tell_object(partner,CYN""+name1+"�ƺ���������۵�ʲ������ӣ�����ȴ����ûɶ��˵��...\n"NOR);
                                         message_vision(CYN"$n��$Nһ��������ֹ������ģ����\n"NOR,me,partner);
                                         delete_temp("exp_gain", me);
                                         return 1;
                  }

  if( query("robot_checking", me) )
  {
        if(bCheckingRobot == 0)
        {
                bCheckingRobot = 1;
                call_out("say_question",1,partner,me);
        }
        return notify_fail("�㻹���Ȱ�������������İ�! \n");
  }

  if( query("robot_checking", partner) )
  {
        if(bCheckingRobot == 0)
        {
                bCheckingRobot = 1;
                call_out("say_question",1,me,partner);
        }
        return notify_fail("���ǵ��˼��Ȱ����������˵��! \n");
  }

//discuss���discuss xxx <����>�ᣬ��ָ�������٣�check robot�������̫�࣬��ʱȡ��

/*
  if( random( 150 ) == 1 && bCheckingRobot == 0)
  {
        message_vision(HIG"$N˵�������һ����ɲ������书�������£�����ʦ�������Ű��ԡ����Ӱټ�����������������ͨ��\n",me);
        message_vision("$N˵�����ҵȵ�������ѧ��ʦ��һ������ѧ�ʣ��ʹ����޺��ˡ�\n",me);
        message_vision("$N˵��������������ô�ã�������Ϣ��Ϣ����������̽��̽��һЩ�㷨���⡣\n"NOR,me);
        set("robot_checking", 1, partner);
        bCheckingRobot = 1;
        call_out("say_question",1,me,partner);
        return 1;
  }

        if( query("th_discuss", me)>2000){
        message_vision("$N����������ѧ��Ҫ��һ���������˹�������$N����ѽѽ�����˸����ƣ��ǻ�ҩʦ����Ҫ��$N����֪�кηԸ���\n",me,partner);
        message_vision("$N��$n����һ�ۣ�ͣ��������$N�����ͻӻ��֣�ʾ��֪�������ͱ㼴��ȥ��\n",me,partner);
        set("huang_called", 1, me);
        delete("th_discuss", me);
        return 1;
        }
*/

        message_vision(CYN"$N��$n���ҵ�̽���Ÿ����书�ĵ�ʧ���������ѧ����⡣\n"NOR,me,partner);
        tell_object(me,HIY"��һ�ߺ�"+name2+"ӡ֤��ѧ��һ�߻�������"+name3+"�ı��侭��������ѧ����ʶ������һ�㣡\n"NOR);
                  tell_object(partner,HIY"��һ�ߺ�"+name1+"ӡ֤��ѧ��һ�߻�������"+name4+"�ı��侭��������ѧ����ʶ������һ�㣡\n"NOR);
        //me->start_busy(1+random(2));
        //partner->start_busy(1+random(2));

        exp1 = exp1-times; pot1 = pot1-times;
        exp2 = exp2-times; pot2 = pot2-times;

        set_temp("exp_gain", exp1, me);
        set_temp("exp_gain", exp2, partner);

                    for (i=0; i<times; i++) {
        addn("combat_exp", (me->query_int()/30+1), me);
        addn("th_discuss", 1, me);
        addn("combat_exp", (partner->query_int()/30+1), partner);
        addn("th_discuss", 1, partner);
        }

        if (pot1>0) {
                set_temp("pot_gain", pot1, me);
                for (i=0; i<times; i++) {
                if( query("potential", me)<query("max_potential", me )
                && random(3) == 1) {
                addn("potential", (me->query_int()/20+1), me);
                }
                }
        }else delete_temp("pot_gain", me);

        if (pot2>0) {
                set_temp("pot_gain", pot2, partner);
                for (i=0; i<times; i++) {
                if( query("potential", partner)<query("max_potential", partner )
                && random(3) == 1) {
                addn("potential", (partner->query_int()/20+1), partner);
                }
                }
        }else delete_temp("pot_gain", partner);
                if( wizardp(me) )
        message_vision("exp1:"+exp1+" exp2:"+exp2+" pot1:"+pot1+" pot2:"+pot2+"\n",me,partner);

        return 1;
}