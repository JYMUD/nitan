int do_gpfm( string arg )
{
    object me = this_player();
    if( !me_ok(me) )
        return 0;
    if( !arg )
        return errs("��׼��ʹ��ʲô������\n");
    if( query_temp("hj_need_waiting", me) == "fighting" || query_temp("hj_fighting", me) )
    {
        set("pfm_ready", arg);
        write("��ĬĬ�۾���׼���������� ��"+arg+"�� ��\n");
        return 1;
    }
    write("����ֻ����ս��ʱ������\n");
    return 1;
}

int do_gbei( string arg )
{
    object me = this_player();
    string now_bei, msg;

    if( !me_ok(me) ) return 0;

    now_bei=query_temp("hj_bei", me);
    if( !now_bei ) now_bei = ".";
    if( now_bei == "." || now_bei == "hand" || now_bei == "none" )
        msg = "ͽ�ֹ���";
    else
    {
        if( strsrch( now_bei , "zj" ) != -1 )
            msg = "ʹ�ü��� ��"+now_bei+"��";
        else msg = "ʹ�õ��� ��"+now_bei+"��";
    }

    if( !arg ) return errs( "��ָ������������ս����ʹ�õķ�ʽ����ɼ�Ϊ <bb> ��
���磺 gbei bs jian , ��ս���н�����Ѱ�������Լ����ϵ�IDΪ\"bs jian\"��
       ���ߣ���Ŀ����е��߸�����ʽ�Ĺ�����
���磺 gbei hfzj , ��ս���н����Լ��ܡ�����֮��������Ŀ����м��ܹ�����

������������磺 gbei jian , ��ô���������� \"jian\" ���ID�ĵ���ʱ��
�������ʹ��������������

�����������õķ�ʽ�Ѿ��޷�ʵ�֣����Զ�ʹ�ÿ��ֹ�������������ûᱻ������

�����ϣ���Կ��ֹ����������ã� <gbei .>  ���� <gbei hand> �� �� <gbei none>��
��Ҫ�鿴�Լ��Ѿ����õ�״̬�������� <gbei ?> ָ�

���������õķ�ʽ�ǣ�"+ msg + " \n");

    if( arg == "?" )
        return errs("������׼���õ�ս����ʽ�ǣ�"+ msg + " \n");

    set_temp("hj_bei", arg, me);
    now_bei=query_temp("hj_bei", me);
    if( now_bei == "." || now_bei == "hand" || now_bei == "none" )
        msg = "ͽ�ֹ���";
    else
    {
        if( strsrch( now_bei , "zj" ) != -1 )
            msg = "ʹ�ü��� ��"+now_bei+"��";
        else msg = "ʹ�õ��� ��"+now_bei+"��";
    }
    write("���ս����ʽ׼��Ϊ�� "+ msg +" ��\n");
    return 1;
}

// gk ��ʽ���£�ʵ���Զ��򶷣������������
int do_gk(string arg)
{
    //    object me,target,tools;
    //    int damages,me_busy,me_power,target_busy;
    //    string tools_name,target_name,do_att="no",color_name,temp,skills_name,skills_name2;

    object me = this_player(), target;
    string target_id;

    if( !me_ok(me) ) return 0;

    if(!arg) return errs("����Ҫ����˭��\n");

    if( query_temp("hj_need_waiting", me) == "healing" || query_temp("hj_healing", me) )
            return errs("�㻹�������أ�Ҫ��ܵ���ͣ����(halt / ht)��\n");

    target = present( arg, environment(me) );

    if(!target) return errs("����û������ˡ�\n");
    if(!target->is_character()) return errs("�ⲻ�ǻ��\n");
    if( !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1 )
        return errs(query("name", target)+"û��˿���þ������Ϣ�����ع����˰ɡ�\n");
    if(!living(target)) return errs("�����Ϸ����������ѵĶ��ֲ��ܹ�����\n");
    if(target == me ) return errs("�����Լ���û��Ҫ�ɡ���\n");

/*  �����κ���Ҷ�ɱ��
// �Լ��÷ֲ���������ɱ���
    if( query_temp("hj_score", me)<200 && !query("hj_game/npc", target) )
        return errs("�����Ϸ�÷���ô�ͣ�����ץ��ʱ��Ū����ȥ�ɣ�\n");

// ������ɱ�÷ֵ͵����
    if( query_temp("hj_score", target)<200 && !query("hj_game/npc", target) )
        return errs(query("name", target)+"����Ϸ�÷�̫�ͣ�����������̫�ðɣ�\n");
*/


    if( query("gender", me) == "����" )
        message_vision(HIR"\nֻ����$N"HIR"��ȵ���������������������$n"HIR"���ϱ㹥��\n\n"NOR, me, target );
    else if( query("gender", me) == "Ů��" )
        message_vision(HIR"\nֻ����$N"HIR"һ���ú����������ɣ���������$n"HIR"���ϱ㹥��\n\n"NOR, me, target );
    else message_vision(HIR"\nֻ����$N"HIR"������һЦ�������򻰣�����$n"HIR"���ϱ㹥��\n\n"NOR, me, target );


    set_temp("hj_fighting", target, me);
    set_temp("hj_need_waiting", "fighting", me);

    // ���ﲻ�� remove_call_out(), ��Ϊ�ú��������жϾ䣬����� call_out ��������
    call_out("fighting", 1);
    return 1;
}

// ��Ŀ�����һ�ι���
void do_attack( object me, object target, int damages )
{
    string describe;
    if( !objectp(me) || !objectp(target) || damages < 1 )
        return;
    // ��ν��������
    if( !random(50) )
    {
        message_vision( HIR"��Ȼһ��"HIY"���"HIR"������$N"HIR"��һ����������ǿ��������\n"NOR, me );
        damages *= 2+random(2);
    }
    // ��NPCʱ
        if( query("hj_game/npc", target) )
        {
            // NPC������������
                set("killme_by",query("id",  me), target);
        // ���Եõ��÷֡�
        // ��֮���ȱ�������Ч��  ս���е÷�����
        if( query_temp("hj_special/gm", me) )
            addn_temp("hj_score", 1+random(damages/8), me);
        else
            addn_temp("hj_score", 1+random(damages/10), me);
    }
    target->hj_get_attack(me);  // Ŀ��ִ��һ���ܵ������ĺ�����ֻ�� hj npc �����������
    addn_temp("hj_hp", -damages, target);//��Ŀ���Ѫ
    // ��ʾ����״̬
    describe=get_health_desc(query_temp("hj_hp", target),query_temp("hj_hp_max", target));
    message_vision(NOR"�� $N"+describe+NOR" ��\n"NOR,target);
    // ��ϡ�
}

void fighting()
{
    object me = query("my_master"), inv_me, inv_target, target, use_tools, srl;
    string figh_type, fight_use, use_skills, color_name, skills_name, describe, temp;
    int damages, me_busy, me_power, target_busy;

    mapping pfm_info;

    if( !me || !me_ok(me) ) return;

    // �������ʽ(halt)��
    // ������Ӳ��У��к�С�ļ��ʻ���ɴ���
    //    if( !me->query_temp("hj_fighting") || me->query_temp("hj_need_waiting") != "fighting")
    // ��Ϳ����� :)
    if( !query_temp("hj_need_waiting", me )
      || query_temp("hj_need_waiting", me) != "fighting" )
        return;

    target=query_temp("hj_fighting", me);
    if( !target || query("room_mark", environment(me)) == 1 )
        return hj_halt( HIW"\n$N"HIW"����һ����ʽ��ͣ��������\n\n"NOR );

    // Ŀ������ң���������������
    if( !query("hj_game/npc", target) && 
        (!query_temp("huanjing", target )
         || query_temp("huanjing", target) != "start"
         || !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1
         || !query_temp("hj_hp_max", target)) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );

    // Ŀ�겻����ң�������
    if( query("hj_game/npc", target) && 
        (!query_temp("hj_hp", target) || query_temp("hj_hp", target)<1) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );

    inv_target = environment( target );
    if( !inv_target || inv_target != environment(me) || !query("room_mark", inv_target) )
        return hj_halt(HIW"\n$N"HIW"��"+query("name", target)+HIW"�Ѳ��ڴ˴�������һ����ʽ������������\n\n"NOR);

    // Ŀ��Я��������
    if( (srl=present("shenren ling",target)) )
    {
        message_vision(CYN"$N"NOR+CYN"���ϵ�"+query("name", srl)+NOR+CYN"ͻȻ����һ���â��\n"NOR,target);
        return hj_halt( HIB"$N"HIB"����һ��Ī���ľ޴�ѹ����ֻ�ð���������\n"NOR );
    }
    // Ŀ���뿪��Ϸ
    if( present( "hj temp leave obj", target ) )
    {
        return hj_halt( CYN"$n"NOR+CYN"���κ������֣����Ʋ���ʵ��һ�㣡$N"NOR+CYN"ֻ�ð���������\n"NOR );
    }
    // �õģ�����׼����ʼ����Ŀ�ꡣ
    // æʱ�У��ȴ���һ�롣
    if( me->is_busy() )
    {
        remove_call_out("fighting");
        call_out("fighting", 1);
        return;
    }
    // ���Դ��ˣ��жϴ����ʽ
    // ����
    if( !query_temp("hj_bei", me) )
        set_temp("hj_bei", "hand", me);

    figh_type = ".";

    // �о������������ж�
    if( query("pfm_ready") )
    {
        // �ú��������жϲ�������Ϣ��
        pfm_info = can_use_pfm( query("pfm_ready"), me, target );
        // �Ѿ�������ɾ��
        delete( "pfm_ready" );
        // �������0���򲻼������κδ���
        if( !mapp(pfm_info) || !sizeof(pfm_info) )
        {
            remove_call_out("fighting");
            call_out("fighting", 1);
            return;
        }
        // ������ʱ����������ʾ��Ϣ "err_msg" �����һ����ʾ
        // ������ sizeof() Ϊ 7 �����ݲ��������ġ�
        if( sizeof( pfm_info ) != 7 )
        {
            if( !pfm_info || undefinedp( pfm_info[ "err_msg" ] ) )
                tell_object( me, "�������⣬�޷�ʹ�þ�����\n");
            else tell_object( me, pfm_info[ "err_msg" ] + "��\n");
        }
        // �����޴�������ʹ�ø� pfm ��
        // �±ߵ����������У�����ȫʹ�� pfm_info ���ṩ�����ݡ�
        else figh_type = "pfm";
    }
    // ��ʼ�ж����������
    // ����趨����
    fight_use=query_temp("hj_bei", me);

    if( figh_type == "." &&
      (!fight_use || fight_use == "." || fight_use == "hand" || fight_use == "none")
    )
        figh_type = "hand";
    // ��������δȷ�������������жϡ��ж��Ƿ������͡�
    // �Ȳ鿴���޸ü��ܣ��Լ��Ƿ���Ϣ����
    if( figh_type == "." )
    {
        if( fight_use != "heal"
           && query_temp("hj_game_skills/"+fight_use, me )
           && query_temp("hj_game_damages/"+fight_use, me )
        )
        {
            // �м��ܣ������Ϣ�Ƿ����
            if( query_temp("hj_hp", me)<100 )
            {
                message_vision( HIY"\n$N"HIY"��Ȼ������Ϣ��˳��ֻ�÷������ܹ��������ÿ�����ս��\n\n"NOR, me);
                figh_type = "hand";
                // ǿ�Ƹ�������ͽ��ս��
                set_temp("hj_bei", "hand", me);
            }
            // ��ôOK��ʹ�ü���
            else
            {
                use_skills = fight_use;
                figh_type = "skills";
            }
        }
        // �޸���ܣ��������ϵĵ���
        else
        {
            use_tools = present( fight_use, me );
            // ֻ��ʹ�����ϵģ�Ҫ�þ�Ҫ��������
//            if( !use_tools ) use_tools = present( fight_use, environment( me ) );
            // �޸õ��ߣ�������ս
            if( !use_tools ) figh_type = "hand";
            else
            {
                // �ҵ��ˣ�Ҫ���ǲ����ܴ�ܵĶ���
                // �ǵ��ߵ��ǲ������õģ�ת����
                if( !query("hj_game/obj", use_tools )
                  || !query("use_times", use_tools) || !query("power", use_tools )
                  || !query("busy", use_tools )
                  || (query("hj_game/obj", use_tools) != "sword"
                     && query("hj_game/obj", use_tools) != "magic") )
                    figh_type = "hand";
                // ����Ϊ���á�
                else figh_type = "tools";
            }
        }
    }

    // ��ֹδ֪�Ĵ�����������˵�������
    if( figh_type != "tools" && figh_type != "skills" && figh_type != "pfm" )
        figh_type = "hand";
    // **********************************
    // ���ˣ�����������ͽ��й���
    // ������ҵ�������ȷ������������
    if( !query_temp("hj_game_mepower", me) )
        set_temp("hj_game_mepower", 5, me);
    me_power=query_temp("hj_game_mepower", me);

    // ��֮���ȱ�������Ч��  ս����������������
    if( query_temp("hj_special/ll", me) )
        me_power = (me_power*2) + random(me_power);
    // ͽ�ֹ���
    if( figh_type == "hand" )
    {
        // ȷ����������æʱ��
        damages = (me_power * 3 / 4 + random(me_power / 4) );
        me_busy = 2;
        // ��������
        temp = ({
            "�ӳ�һȭ",
            "�߳�һ��",
            "����һ��",
            "����һײ",
            "����һ��",
        })[ random(5) ];
        // ��ʹ�� message_vision() �ķ�ʽ
        tell_room(environment(me),CYN"\n"+query("name", me)+NOR+CYN"������"+query("name", target)+NOR+CYN+temp+"��\n"NOR,({me,target}));
        tell_object(target,CYN"\n"+query("name", me)+NOR+CYN"��������"+temp+"�������"HIR""+damages+""NOR+CYN"����˺���\n"NOR);
        tell_object(me,CYN"\n�������"+query("name", target)+NOR+CYN+temp+"�������"HIG""+damages+""NOR+CYN"����˺���\n");
        if( !random(query_temp("hj_game_mepower", me)*2) )
        {
            write(HIY"��ֻ���ô�ȭ�Ź�����ˣ������ƺ��ִ���Щ��\n"NOR);
            addn_temp("hj_game_mepower", 1, me);
        }
    }
    // �õ��߹���
    if( figh_type == "tools" )
    {
        // ������ʲô���͵ĵ�����
        // ����
        if( query("hj_game/obj", use_tools) == "sword" )
        {
            // ��ȷ����������æʱ��
            damages = ( me_power *3 / 4 + random( me_power / 4 ) ) +
                  (query("power", use_tools)*3/4)+
                  random(query("power", use_tools)/4);

            if( query("busy", use_tools) == 888)me_busy=0;
            else me_busy=query("busy", use_tools);
            addn("use_times", -1, use_tools);
            // �ж� use_tools ʹ�ô�����϶�Ҫ delete �ľ��ӷ��ں�ߣ�
            // �����ʱ delete ���������滹Ҫ���ã�����BUG BUG��
            // �ã���������
            temp = ({ "��", "��", "��", "��", "��" })[ random(5) ];
            tell_room(environment(me),CYN"\n"+query("name", me)+NOR+CYN"����"+query("name", use_tools)+NOR+CYN"��"+query("name", target)+NOR+CYN+temp+"ȥ��\n"NOR,({me,target}));
            tell_object(target,CYN"\n"+query("name", me)+NOR+CYN"����"+query("name", use_tools)+NOR+CYN"����"+temp+"���������"HIR+damages+NOR+CYN"����˺���\n"NOR);
            tell_object(me,CYN"\n������"+query("name", use_tools)+NOR+CYN"��"+query("name", target)+NOR+CYN+temp+"ȥ�������"HIG+damages+NOR+CYN"����˺���\n");
        }
        // ������ħ��ˮ����
        else
        {
            // ȷ����������
            damages = ( me_power * 3 / 4 + random( me_power / 4 ) ) +
                  (query("power", use_tools)*3/4)+
                  random(query("power", use_tools)/4);
            if( query("type", use_tools) == query("find_name") )
                damages *= 2+random(2);
            if( query("busy", use_tools) == 888)me_busy=0;
            else me_busy=query("busy", use_tools);
            addn("use_times", -1, use_tools);
            switch(query("type", use_tools) )
            {
                case "��֮����": color_name=HIW;break;
                case "��֮����": color_name=HIM;break;
                case "��֮����": color_name=HIC;break;
                case "��֮����": color_name=HIG;break;
                default:color_name = WHT;
            }
            message_vision(color_name+"\n$N"NOR+color_name+"����$n"NOR+color_name+"��������������ħ�����֣���\n"NOR,me, use_tools);
            tell_room(environment(me),color_name+"ֻ��"+query("att_msg", use_tools)+"��"+query("name", target)+NOR+color_name+"��ȥ�������"HIG+damages+NOR+color_name+"����˺���\n"NOR,target);
            tell_object(target,color_name+"ֻ��"+query("att_msg", use_tools)+"���㹥���������"HIR+damages+NOR+color_name+"����˺���\n"NOR);
        }
    }

    // ���ܹ���
    if( figh_type == "skills" )
    {
        // ȷ����������æʱ��
        // ����һ������ĵط���ʹ�ü���ʱ���ֻ���������� 1/2
        damages = me_power / 4 + random( me_power / 4 ) +  
            (query_temp("hj_game_damages/"+use_skills, me)*3/4)+
              random(query_temp("hj_game_damages/"+use_skills, me)/4);

        skills_name=query_temp("hj_game_skills/"+use_skills, me);
        me_busy = 2+random(2);

        switch( query("find_name") )
        {
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2 ;   // 1.5 ��
                break;
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2;
                break;
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2;
                break;
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2;
                break;
        }
        if(skills_name == "�ɻ�֮��" || skills_name == "��ʯ֮��")
            damages = 1+(damages/3)+random(damages*2);

        switch( skills_name )
        {
            case "����֮��" : color_name = HIW; break;
            case "����֮��" : color_name = HIM; break;
            case "����֮��" : color_name = HIC; break;
            case "����֮��" : color_name = HIG; break;
            default: color_name = WHT; break;
        }
        tell_room(environment(me),color_name+"\n"+query("name", me)+NOR+color_name+"����"+skills_name+"����"+query("name", target)+NOR+color_name+"��ȥ��\n"NOR,({me,target}));
        tell_object(target,color_name+"\n"+query("name", me)+NOR+color_name+"����"+skills_name+"�����㹥���������"HIR+damages+NOR+color_name+"����˺���\n"NOR);
        tell_object(me,color_name+"\n������"+skills_name+"����"+query("name", target)+NOR+color_name+"��ȥ�������"HIG+damages+NOR+color_name+"����˺���\n"NOR);

        addn_temp("hj_hp", -(3+random(3)), me);
        // ʹ�ü��ܣ�ÿ�ν������������HP���㡣
        // �л���õ������������Ѷȸ�����
        if( !random(query_temp("hj_game_damages/"+use_skills, me)*2) )
        {
            addn_temp("hj_game_damages/"+use_skills, 1, me);
            if( query_temp("hj_game_damages/"+use_skills, me)>99 )
                set_temp("hj_game_damages/"+use_skills, 99, me);
            else tell_object(me,HIY"��ԡ�"+skills_name+"��������ֽ���һ�㣡\n"NOR);
        }
    }
    // ��������
    if( figh_type == "pfm" )
    {
        // ��������ʱ������������ȫ�ɾ��������ж�������ֻ�Ǽ��������Ļ���������
        // ���������Ļ�����������ʹ�ü���ʱһ�������ֻ���������� 1/2
        damages = me_power / 4 + random( me_power / 4 ) + pfm_info[ "damages" ];
        me_busy = pfm_info[ "me_busy" ];
        addn_temp("hj_hp", -pfm_info["lost_hp"], me);
        // ����
        temp = replace_string( pfm_info[ "msg_all" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_room(environment(me), temp, ({ me, target }) );

        temp = replace_string( pfm_info[ "msg_me" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_object( me,temp );

        temp = replace_string( pfm_info[ "msg_target" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_object( target, temp );
    }
    // ���ˣ����е�����ʲô�Ķ��㶨��
    // ���� ��׼�����������й�����
    // ################################################
    do_attack( me, target, damages );
    // ################################################
    // ��֮���ȱ�������Ч����ս����busy������͡�
    if( query_temp("hj_special/xk", me) && me_busy )
        me->start_busy(1);
    // �����������㡣
    else
        me->start_busy(me_busy);
    // �ر�ļ��ܻ���ߣ���Է���æʱ
    if( figh_type == "skills" && skills_name =="���֮��" )
    {
        addn_temp("hj_hp", -(3+random(3)), me);
        // ����ʹ�ö��֮������������Ҫ�������Ϣ��
        // ���֮�����⼼������֮��(1)����Ч�ֿ�������ҵĶ���๥����æʱЧ��
        if( !query_temp("hj_special/sh", target) && !random(10 )
            && target->query_busy() < 6 )
        {
            // 99 lv ��꼼����� 20 ��æʱ
            target_busy=query_temp("hj_game_damages/dhzj", me)/5;
            if(target_busy < 2) target_busy = 2;
            target->start_busy( target_busy + target->query_busy() );
            tell_room( environment(me), sprintf( HIR"%s"HIR"ͻȻ���۷�ֱ�������˴�ס���Ƶġ�\n"NOR, target->name(1)), ({me,target}));
            tell_object( target, HIR"��ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
            tell_object( me, HIR+target->name(1)+HIR+"ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
        }
    }
    // ���֮�����⼼������֮��(2)����Ч�ֿ�������ҵĶ���๥����æʱЧ��
    if( !query_temp("hj_special/sh", target) && !random(5 )
        && figh_type == "tools" && target->query_busy() < 6
         && (query("id", use_tools) == "dh sj" || query("id", use_tools) == "dh jian") )
    {
        target_busy = 10+random(11);
        target->start_busy( target_busy + target->query_busy() );
        tell_room( environment(me), sprintf( HIR"%s"HIR"ͻȻ���۷�ֱ�������˴�ס���Ƶġ�\n"NOR, target->name(1)), ({me,target}));
        tell_object( target, HIR"��ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
        tell_object( me, HIR+target->name(1)+HIR+"ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
    }
    // ������ж��Ƿ�Ҫ delete use_tools.
    if( figh_type == "tools" && use_tools && query("use_times", use_tools) <= 0 )
        use_tools->delete_me();
    // �㶨��
    // ��֮������������Ч��  ս���п��ܸ��ӹ���
    if( random(8) == 2 && query_temp("hj_game_find", me) == "dian" )
    {
        message_vision( GRN"��Ȼ��֪����������һ��"BLINK+HIG"����"NOR+GRN"����$N"NOR+GRN"��������У�\n"NOR, target );
        damages=(query_temp("hj_game_damages/ydzj", me)/2);
        if( damages < 5 )
            damages = 5;
        if( damages > 20 )
            damages = 20;
        // ���� ��׼�����������й�����
        // ################################################
        do_attack( me, target, damages );
        // ################################################
    }
    // �����ټ�һ���жϣ�����Է����ˣ�ֱ�Ӿ� return �ˡ�
    // Ŀ������ң���������������
    if( !query("hj_game/npc", target) && 
        (!query_temp("huanjing", target )
         || query_temp("huanjing", target) != "start"
         || !query_temp("hj_hp", target) || query_temp("hj_hp", target)<1
         || !query_temp("hj_hp_max", target)) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );
    // Ŀ�겻����ң�������
    if( query("hj_game/npc", target) && 
        (!query_temp("hj_hp", target) || query_temp("hj_hp", target)<1) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );

    // ���ˣ�ѭ�� :)
    // ����Ǹ��ر�ĵ��ߣ�Ѹ��֮������ֱ�ӵ�����һ�Σ������ȴ�1��
    if( figh_type == "tools" && use_tools && query("id", use_tools) == "xy jian" )
    {
        fighting();
        return;
    }
    remove_call_out("fighting");
    call_out("fighting", 1);
    return;
}
