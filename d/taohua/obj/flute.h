//Cracked by Kafei
#include <ansi.h>
#define TRAVERSER "/clone/obj/traverser"

//int playing(object me);
//int halt_play(object me);
//void sound_float(object me, int range);

void init()
{
        add_action("do_play", "play");
        add_action("do_lianxi", "lianxi");
        add_action("halt_play", "halt");
        add_action("halt_play", "end");

}

string *play_msg = ({
        HIM"�������������಻�ϣ�Խ��Խ�����������ߺ��ͣ��������棬ʵ������֮��������֮�����ƶ��ʡ�",
        HIG"���������ߺ��ͣ���ǰ���ᣬ����������ٿ�����ϣ��ƺ���ʮ���˷������ܣ�����˷��Ĵ���ϷŪһ�㡣",
        MAG"�������Ӷ��䣬��ǳЦ���Ƶ��ߣ�������ˡ�",
        HIG"ֻ����������������ת���������٣����Ǵ������衣",
        HIM"��ʱ��$w"+HIM"֮������Ʈ����������ת������һ��Ů��һ���̾Ϣ��һ���������һ����������´桢�����л���",
        HIM"$w"+HIM"�������ʲŸ��ӹ������ǣ�������ת������ϸϸ��ˣ��������ǻ��",
        HIG"$N��������֮����ֻ��������Խ��Խ�ߣ��������ǻس�������",
        HIM"$N����ͻת�������ı��������ˣ�ǡ�����ڷ��������˽�",
});

string *bihai_play_msg = ({
        HIB"��ʱ�������糱ˮ����Ծ�����������Ϸ�ХŸ�ɣ��ټ���ˮ�����֣�ȺħŪ����������ɽƮ���������Ⱥ���У��������֮���¡�",
        BLU"��ʱ�����糱����ˮƽ�羵������ȴ���ǰ����ļ������������������գ����������߲�֪�������������Ϊ����ʤ����",
        HIB"���ﱾ�������ת��������ʱ������ȴ���߾�����ɱ֮�¡�",
        BLU"$N�ִ��ð��Σ�$w"+BLU"��������ϸ�������������š������ǡ��̺���������������֮�����������ᣬ��������",
});

string *succeed_msg = ({
        HIM"$n��ͷһ�������ϲ��Խ���¶��΢Ц��ֻ��ȫ����Ѫ���ڣ���ֻ�������㵸���Ҷ�һ�������������",
        HIM"$n������������ʱ�������������������ķ�����֮����������ͷ���ȣ�������",
        HIM"$n����һ��������һ����������һ��ֻ�������࣬Ѫ�����ţ����������㵸һ����",
        HIM"���������м���ħ����$n�ֵ���ס����������֮�£����е����ɽ��Ľ�����������ϡ�",
});

string *bihai_succeed_msg = ({
        HIB"$nֻ�����ҡ������������һ��һ����",
        HIB"$n��֧����һ�󣬺����������зɳ������⣬��ʱ���������������������������",
        HIB"$n���������֣����������ֹǣ��������к��⡣",
});

string *fail_msg = ({
        "$n�������������������㣬��ʱ������Ǳ��$f��������������",
        "����$n������տ����ͷ����һ��������Ӳ���������ȥ�����赸�������˻�����",
        "$n������������һƬ����������Ƭ������$N�����ٵ�������ֻ�뺣�в��Ρ����ҷ���һ�����졣",
        "$nֻ������һ�������Ϸ��ȣ���æ��������",
});

string *bihai_fail_msg = ({
        "����$n�������ܣ���Ԫ��һ��������־��$N����������ȴҲ���ܽ�$p������",
        "$n����������һ��ר�ز�����������������Ӧ��ԣ�磬ȴҲ������˿��������",
});

string *dazuo_fail_msg = ({
        "$n��ϥ���ڵ��£���ͷ�й��������������������ա�",
        "$n���ָ��أ����ַ��ڱ��ᣬǱ��$f���������񣬶�$N�Ĵ���ȫȻ���Ų�����",
        "$n��ϥ��������������������������ڻ����Լ���Ķ�������������",
        "$n��ϥ���ڵ��ϣ�һ������$f���������񣬵������������ա�",
});

string *faint_msg = ({
        HIM"������������ת��$n��Ҳ���Ͳ�ס������������������......",
        HIM"$n����Ƭ������������֮����ʧ�������������������......",
        HIM"$n����ȫ��ƮƮ���ɣ�����¶����㯶���������飬�鲻�Խ��������㵸����......\n",
});

int do_play()
{
        int i, count, range;
        object me, ob, weapon;
        string msg, play_type, *shape;

        ob = this_object();
        me = this_player();
        shape=query("shape", ob);

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("��������æ���ء�\n");
                
        if( me->query_skill_mapped("force") != "bitao-xuangong" )
                return notify_fail("�����õĲ��Ǳ����������޷�ʩչ�̺���������\n");
        
        if( me->query_skill("force") < 120 )
                return notify_fail("��ı����������δ�����޷�ʩչ�̺���������\n");

        if( (int)me->query_skill("music", 1) < 100 )
                return notify_fail("ƾ����������裬���޷�����ó��̺���������\n");

        if( query("neili", me)<800 )
                return notify_fail("�������������\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("�����в�û�����\n");

        if( query("name", weapon) != query("name", ob) )
                return notify_fail("�����в�û�����\n");

        for( i=0; i < sizeof(shape); i++ )
                if( shape[i] == "flute" )
                {
                        count++;
                        break;
                }

//        if( !count ) return notify_fail("�����в�û�����\n");
        
        
        if( query_temp("wuzhuan", me) && !query_temp("playing_bihai", me) )
        msg = "����$N��ɫ֣�أ��ְ�$n�����߱ߴ�������̤�Ű��Է�λ��";
        else msg = "$N$n�ʹ����������ʵĴ���������";
        if( query("no_fight", environment(me)) )
                msg += "�ⴵ�಻��˿�����������볣�˴������졣\n";
        else
        {
                msg += "\n";
                addn("neili", -200, me);
                me->receive_damage("qi", 10);
                play_type = "martial";
        }

        message_vision(msg, me, ob);
        set_temp("apply/short", ({me->name()+"��������"+ob->name()+"��"}), me);
        set_temp("play_type", play_type, me);

        message_vision(HIC"ͻȻ֮�䣬����������٣�����񣬷��˼����������������Ʈ��һ��������͵Ķ���������\n"NOR, me);
//        me->start_busy((: playing :), (: halt_play :));
        me->start_busy(2);
        call_out("playing", 1, me);
//                range = 1+(me->query_skill("bitao-xuangong", 1)-100)/4;
//                sound_float(me, range);
                set_temp("exercise/playing", 1, me);

        return 1;
}

void playing(object me)
{
        string play, succeed, fail, faint, map_force;
        int range, i, k=0, flag, music, music2, force, force2, tag, attacker, defender,damage,times;
        object *target, ob, env;
        
        env = environment(me);
        ob=query_temp("weapon", me);
        force = me->query_skill("force");
        music = (int)me->query_skill("music",1);
        times=query_temp("played_times", me);

        if( !query_temp("exercise/playing", me) )
        {
                message_vision(CYN"������ͣ������������Ϣ��һ��������������Ъ��\n"NOR, me);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }


        me->start_busy(2);

        if( !objectp(ob) )
        {
                message_vision(CYN"$N�������������ͣ��\n"NOR, me);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }
        if( query("jing", me)<200 || query("neili", me)<200
        || !living(me) || me->is_ghost())
        {
                if( query("jing", me)<200 )
                        tell_object(me,"��ľ������Լ�������̺��������ˡ�\n");
                if( query("neili", me)<200 )
                        tell_object(me,"������������Լ�������̺��������ˡ�\n");
                message_vision(CYN"������ͣ������������Ϣ��һ��������������Ъ��\n"NOR, me);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }

        target = all_inventory(environment(me));

                for(i=0; i<sizeof(target); i++) {
                if( !living(target[i]) || target[i]==me ) continue;
                k++;
                }

        if( k<1 && !query("no_fight", environment(me))){
                tell_object(me,CYN"���²��޵��ˣ������ٴ���̺��������ˡ�\n"NOR);
                delete_temp("apply/short", me);
                me->set_temp("delete/playing");
                delete_temp("played_times", me);
                delete_temp("playing_bihai", me);
                delete_temp("exercise/playing", me);
                return 0;
        }
        else {
                if( query_temp("wuzhuan", me) && !query_temp("playing_bihai", me)){

                        set_temp("apply/short", ({me->name()+"�ְ�"+ob->name()+"������̤�Ű��Է�λ�����бߴ���"}), me);
                        addn_temp("playing_bihai", 1, me);//��Ϊ�̺�msg
                }

                //����playѶϢ���
                if( query_temp("playing_bihai", me) == 1 )
                play = HIC"��������ģ��󺣺��������޲���Զ����ˮ�����ƽ����������죬���������ӿ��������ɽ��";
                else if( !query_temp("playing_bihai", me) )
                play = play_msg[random(sizeof(play_msg))];
                else 
                play = bihai_play_msg[random(sizeof(bihai_play_msg))] ;
                //end
                
                if( query("neili", me)<random(600))message_vision(CYN"��������΢�����ͣ����漴�ع�ԭ����������\n"NOR,me);//����play��


                if(times != 0 && times/2 * 2 == times)
                        message_vision("", me);
                else message_vision("\n"+replace_string( play, "$w", ob->name() ) +"\n"NOR, me, ob);

                me->receive_damage("jing", 20+random(20), "����͸֧��������");

                if( query("no_fight", environment(me))){//nofight-roomnouse
                call_out("playing", 1, me);
                return;
                }

                //playЧ������
                addn_temp("played_times", 1, me);

                if( query("id", this_object()) == "yuxiao" )
                flag = 2;
                else flag = 1;

                attacker=query("neili", me)/20+random(force)/2+random(music*flag);

                if( query_temp("wuzhuan", me) )
                attacker=query("neili", me)/20+random(force)/2+random(music*flag)+times*10;
                if( attacker <= 0 ) attacker = 0;
                //��ʼ�ظ��������е���
                for(i=0; i<sizeof(target); i++) {
                
                if( !living(target[i]) || target[i]==me ) continue;
                                        //����ѶϢ��� 2

                if( !query_temp("playing_bihai", me)){
                play = play_msg[random(sizeof(play_msg))];
                succeed = succeed_msg[random(sizeof(succeed_msg))];
                fail = fail_msg[random(sizeof(fail_msg))];
                }
                else {
                play = bihai_play_msg[random(sizeof(bihai_play_msg))] ;
                succeed = bihai_succeed_msg[random(sizeof(bihai_succeed_msg))];
                fail = bihai_fail_msg[random(sizeof(bihai_fail_msg))];
                }
                faint = faint_msg[random(sizeof(faint_msg))];
                
                if( query_temp("pending/exercise", target[i]) || query_temp("pending/respirate", target[i]) )
                fail = dazuo_fail_msg[random(sizeof(dazuo_fail_msg))];
                
                        //end

                tag=query("married_times", target[i]);
                if(tag > 20) tag = 20;
                music2 = (int)target[i]->query_skill("music",1);
                force2 = target[i]->query_skill("force");
                defender=query("neili", target[i])/25-tag*5+random(force2)+music2;
                //����������ʱ�������
                if( query_temp("pending/exercise", target[i]) || query_temp("pending/respirate", target[i]) )
                defender=query("neili", target[i])/10-tag*10+random(force2)+music2;

                if(defender < 1) defender = 1;

                if( times/2*2 != times && query("family/family_name", target[i]) == "�һ���" && music2>music/2){
                        message_vision("$n��֪�������仯����$N������һ�����ǲ���Σ����\n"NOR, me, target[i]);
                        }
                else if( attacker < defender ) {
                
                map_force = target[i]->query_skill_mapped("force");
                if (!target[i]->query_skill_mapped("force")) map_force = "force";
                        if( query("race", target[i]) != "����" || times/2*2 == times )
                        message_vision("", me, target[i]);
                        else message_vision( replace_string( fail, "$f", to_chinese(map_force)) +"\n"NOR, me, target[i]);
                        if( wizardp(me) && query("env/check_play", me) )
                        tell_object(me,sprintf("attacker��%d ,defender��%d \n"
                        ,attacker,defender));
                }
                else {
                        damage=force+music/3+random(music/2)*flag+random(tag*10)+(-query("max_neili", target[i])/30)+-random(force2/2)+-force2/3;
                        if( damage > 600+flag*200 ) damage = 600+flag*200; // most ppl have at most 1k+ jing
                        if( damage < 100 ) damage = 100;

                        damage=damage+query_temp("playing_bihai", me)*8;
                        
                        if( wizardp(me) && query("env/check_play", me) )
                        tell_object(me,sprintf("attacker��%d ,defender��%d ,damage��%d \n"
                        ,attacker,defender,damage));

                        if( damage > 0 ) {
                        target[i]->receive_damage("jing", damage, me);

                        addn("jingli", -damage, target[i]);
                        addn("neili", -damage, target[i]);
                        addn_temp("be_played/"+query("id", me), 1, target[i]);
                        target[i]->start_busy(random(2));

                        if( !target[i]->is_killing(query("id", me)) || !target[i]->is_fighting(me) || !me->is_fighting(target[i]) )
                        target[i]->kill_ob(me);

                        //target[i]->set_temp("last_damage_from",me);
                        //��ͬ�����˺���ͬ
                        if( !query_temp("playing_bihai", me) )
                        target[i]->receive_damage("jing", random(damage/3 + tag*5), me);
                        else addn("neili", -random(damage/2), target[i]);
                        //
                        if( query("neili", target[i])<0 )
                                set("neili", 0, target[i]);

                        if( (query("jing", target[i])<0 || query("jingli", target[i])<0 )
                         && query("race", target[i]) == "����" )
                        message_vision( faint+"\n"NOR, me, target[i]);
                        else if( (query("jing", target[i])<0 || query("jingli", target[i])<0) && query("race", target[i]) != "����" )
                        message_vision("ֻ��$n������ͷ����������ҡͷ���Ե��趯��\n"NOR, me, target[i]);
                        else if(times/2 * 2 == times)
                        message_vision("", me, target[i]);
                        else if( query("race", target[i]) != "����" )
                        message_vision("ֻ��$n������ͷ����������ҡͷ���Ե��趯��\n"NOR, me, target[i]);
                        else message_vision( succeed +"\n"NOR, me, target[i]);
                        }
                        }
                }
                //playЧ�����㵽����

                if( wizardp(me) && query("env/check_play", me) )
                        tell_object(me,sprintf("times��%d\n" ,times));

                if( query_temp("playing_bihai", me))addn_temp("playing_bihai", 1, me);
                addn("neili", -100, me);
                set("playing", me, env);
                call_out("playing", 1, me);
                return;
        }
}

int halt_play()
{
        object me;
        me = this_player();
        if( query_temp("exercise/playing", me)){
        message_vision(CYN"������ͣ������������Ϣ��һ��������������Ъ��\n"NOR, me);
        delete_temp("apply/short", me);
        me->set_temp("delete/playing");
        delete_temp("played_times", me);
        delete_temp("playing_bihai", me);
        delete_temp("exercise/playing", me);
        remove_call_out("playing");
        return 1;
        }
        else return 0;
}
