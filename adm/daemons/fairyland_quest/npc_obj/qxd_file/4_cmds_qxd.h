// hj �ڻ���ָ��

int do_who_in_hj()
{
    object rooms;
    mapping info;

    rooms = find_object( HJ_DIR+ "room_door_hj" );
    if( !rooms ) rooms = load_object( HJ_DIR + "room_door_hj" );
    if( !rooms ) return errs("������������޷���ѯ��\n");
    write( rooms->who_in_hj()[ "info" ] );
    return 1;
}

int do_hjtop()
{
    object out_room;

    out_room = find_object( HJ_OUT_ROOM );
    if( !out_room )
        return errs("�����޷��鿴��¼��\n");
    write(HIW"
       ���þ���ңԶ��˵֮��Ե���������֡�
"+out_room->get_TOP_pic()+"\n"NOR);
    return 1;
}

// ��BUG 55555555 �Ѹ����������Ż���һ���¡�  naihe 2:36 03-10-24
// ������� pah (xsmarter) �Ľ��飬�����˷������ܵ�ָ�
// �����б�ʽ����Ȼ��֮ǰ�ķ��������ܹ������ҵ���Ҫ������
int do_gsks( string arg )
{
    object me = this_player();
    int i, amount, temp;
    string *key;
    string msg, clcl, cl, pic, lv_pic, t1, t2;
    mapping all_skills, all_damages;

    string *list;


    if( !me_ok(me) ) return 0;

    all_skills=query_temp("hj_game_skills", me);
    all_damages=query_temp("hj_game_damages", me);

    if( !all_skills || !mapp(all_skills) || sizeof(all_skills) < 1 ||
        !all_damages || !mapp(all_damages) || sizeof(all_damages) < 1 )
        return errs("�㲢δѧ���κ� �þ� �ڵļ��ܡ�\n");

    if( !arg ) arg = ".";

    if( sscanf(arg, "-d %s", msg) )
    {
        if( undefinedp( all_skills[msg] ) || undefinedp( all_damages[msg] ) )
            return errs("�㲢����������þ��ڵļ��ܡ�\n");

        arg = all_skills[msg];
        delete_temp("hj_game_skills/"+msg, me);
        delete_temp("hj_game_damages/"+msg, me);
        delete("huanjing2003/last_skills_name/"+msg, me);
        delete("huanjing2003/last_skills_lv/"+msg, me);
        me->save();
        message_vision( "$N���˼��ܣ����Լ������õġ�"+arg+"��ɢȥ�ˡ�\n",me);
        return 1;
    }

    // ���濪ʼ�Թ̶������г���������õļ��ܡ�
    list = ({ "heal", "hfzj", "hyzj", "llzj", "ydzj", "dhzj", "fhzj", "gszj", });


    clcl = NOR + WHT;
    pic = "��";
    msg = clcl +
          "�q���������������Щ��Щ����������Щ����������Щ������������������r\n" +
          "��    ��   ��   ��LV�� ����(yun)�� ����(pfm)��    Ч     ��     ��\n" +
          "�����������������੤�੤���������੤���������੤������������������\n";


    for( i=0;i<sizeof(list);i++ )
    {
        if( undefinedp( all_skills[list[i]] ) || undefinedp( all_damages[list[i]] ) )
            continue;

        // ��ɫ�����⼼��ʾ��������ʾ
        cl = "";
        t1 = "   ----   ";
        t2 = "   ----   ";
        switch( list[i] )
        {
            case "heal" : cl = CYN; t1 = "����(kz)"; break;
            case "hfzj" : cl = HIW; t1 = "���(xk)"; t2 = "���(kf)"; break;
            case "hyzj" : cl = HIM; t1 = "����(cm)"; t2 = "����(by)"; break;
            case "llzj" : cl = HIC; t1 = "����(ll)"; t2 = "����(jl)"; break;
            case "ydzj" : cl = HIG; t1 = "��â(gm)"; t2 = "Ѹ��(xd)"; break;
            case "dhzj" : cl = HIB; t1 = "�ػ�(sh)"; t2 = "���(dh)"; break;
            case "fhzj" : cl = HIR; t1 = "����(rq)"; t2 = "����(hy)"; break;
            case "gszj" : cl = HIY; t1 = "Ѱʯ(xs)"; t2 = "��ʯ(js)"; break;
        }

        // ��Ч����ǣ�����һ�ۿ��Կ����Ƿ���yun, pfm �Լ����ܸߵ�
        if( all_damages[list[i]] > 99 )
            all_damages[list[i]] = 99;
        // ��һ��ʵ���Ϻ� me->set_temp() ͬ��Ч����Ī�� mapping Ҳ�����ơ�ָ�롱�ģ�
        // ���磺 mapping test = objecttt->query("lalala");
        //        objecttt->delete("lalala");
        // ��ô���ʱ�� lalala ��ֵ��Ҳ��Ϊ��0���ˣ���֮��Ȼ��
        temp = all_damages[list[i]];

        if( t1 != "   ----   " )
        {
            if( temp >= YUN_LvNeed ) t1 = "��" + t1;
            else t1 = "��" + t1;
        }
        if( t2 != "   ----   " )
        {
            if( temp >= PFM_LvNeed ) t2 = "��" + t2;
            else t2 = "��" + t2;
        }
        lv_pic = "";
        while( temp>9 )
        {
            lv_pic += pic;
            temp -= 10;
        }
        if( strlen(lv_pic) > 18 ) lv_pic = lv_pic[0..17];

        msg += sprintf( clcl+"��%s%s(%s)"+clcl+"��%2d"+clcl+"��%-10s"+clcl+"��%-10s"+clcl+"��"+cl+"%-18s"+clcl+"��\n"+clcl,
            cl, all_skills[list[i]],list[i], 
            all_damages[list[i]],t1, t2, lv_pic );
        // �������� +1
        amount ++;
    }

    // Ϊ�˽��������չʱ��Ҳ������ʾ�¼���
    // ��һ��δ���ƣ���Ҫ���ӵ���ʲô�����ٿ��Ǹ��ġ�
    key = keys( all_damages );
    for( i=0; i<sizeof( key ); i++ )
    {
        // ����ǰ�洦����ˣ����߼���������������
        if( member_array(key[i],list) != -1 || undefinedp( all_skills[ key[i] ] ) )
            continue;
        // ��������ɫ����
        msg += sprintf( clcl+"��%s(%s)"+clcl+"��%2d"+clcl+"��%-10s"+clcl+"��%-10s"+clcl+"��"+cl+"%-18s"+clcl+"��\n"+clcl,
            all_skills[key[i]], key[i], 
            all_damages[key[i]], "   ----   ","   ----   ","");
            amount ++;
    }
    // û��ͨ�����ļ���
    if( !amount )
        return errs("�㲢δѧ���κ� �þ� �ڵļ��ܡ�\n");
    msg += clcl+ "�t���������������ة��ة����������ة����������ة������������������s\n"NOR;
    write( "  ��������ѧ�õĻþ��ڼ���(��"+chinese_number(amount)+"��)��\n" + msg + "  ����Ҫ����ĳ��ܣ���ʹ��ָ�<gsks -d ������>  ���磺gsks -d heal\n  ��ע�⣬����ָ�ֱ�ӷ����ü��ܣ����޷��ָ���\n");
    return 1;
}

int do_ghp()
{
    object me=this_player();
    string color, temp, temp2, temp3;
    int hp,hp_max, iii;

    if( !me_ok(me) ) return 0;

    hp=query_temp("hj_hp", me);
    hp_max=query_temp("hj_hp_max", me);

    color = HIB;
    if( hp > (hp_max * 2/10) ) color = HIR;
    if( hp > (hp_max * 4/10) ) color = HIM;
    if( hp > (hp_max * 6/10) ) color = HIY;
    if( hp > (hp_max * 8/10) ) color = HIG;
    if( hp > hp_max ) color = HIC;

    if( !temp = query("find_name") )
        temp = "���ع���";
    switch( temp )
    {
        case "��֮����": temp = HIW+temp+NOR;break;
        case "��֮����": temp = HIM+temp+NOR;break;
        case "��֮����": temp = HIC+temp+NOR;break;
        case "��֮����": temp = HIG+temp+NOR;break;
    }
    temp2 = "";
    if( query_temp("hj_special/xk", me))temp2+=HIW"����ա�"NOR;
    if( query_temp("hj_special/cm", me))temp2+=HIM"��������"NOR;
    if( query_temp("hj_special/ll", me))temp2+=HIC"��������"NOR;
    if( query_temp("hj_special/gm", me))temp2+=HIG"����â��"NOR;
    if( query_temp("hj_special/kz", me))temp2+=CYN"�����ơ�"NOR;
    if( query_temp("hj_special/sh", me))temp2+=HIB"���ػ���"NOR;
    if( query_temp("hj_special/rq", me))temp2+=HIR"�����项"NOR;
    if( query_temp("hj_special/xs", me))temp2+=HIY"��Ѱʯ��"NOR;

    if( temp2 == "" ) temp2 = " ---";

    temp3 = "";
    iii=query_temp("hj_game_mepower", me);
    while( iii >4 )
    {
        temp3 += "��";
        iii -= 5;
    }
    if( strlen( temp3 ) > 20 ) temp3 = temp3[0..19] + ">>>>";

    write( sprintf("�� %s �� LV "HIY"%d"NOR" �� ��Ϣ��%s%d"NOR"/"HIG"%d"NOR" �� �÷֣�"HIY"%d"NOR" �� ����������"HIY"%s"NOR" �� �ۼ�ɱ��NPC "HIM"%d"NOR" �� ��\n�� ���������У�%s ��\n"NOR,
        temp,query("huanjing2003/lv", me),color,
        hp,hp_max,query_temp("hj_score", me),temp3,query("huanjing2003/kill_npc", me),temp2));
    return 1;
}

// heal ��ʽ���£�����ʵ���Զ��ָ���
int do_gheal(string arg)
{
    object target,me=this_player();

    if( !me_ok(me) ) return 0;

    if( !query_temp("hj_game_skills/heal", me) || !query_temp("hj_game_damages/heal", me) )
        return errs("�㲢�����ûָ����ܡ�\n");

    if( !arg || arg == query("id", me))target=me;
    else target=present( arg,environment( me ) );
    if( !target ) return errs("��Ҫ��˭�ָ���Ϣ��\n");
    if( !target->is_character() ) return errs("�ⲻ�ǻ��\n");
    if( !living(target) ) return errs("�����ȵ�����������˵�ɡ�\n");
    if( !query_temp("hj_hp", target) || !query_temp("hj_hp_max", target) )
        return errs("����û��˿����Ϣ���������˰ɡ�\n");

    // ��ָ����ɰ�NPC�ָ���Ϣ������������NPC��Ҫ���ȥ������ :)
    // �Ѳ��ɰ���NPC�ָ���Ϣ��
    if( query_temp("hj_need_waiting", me) == "fighting" || query_temp("hj_fighting", me) )
            return errs("�㻹��ս���У�Ҫ���˵���ͣ����(halt / ht)��\n");

    if( query_temp("hj_healing", me) )
        return errs("���������ûָ�֮����\n");

    if( me->is_busy() )
        return errs("�㻹æ���ء�\n");

    if(target == me )
    {
        if( query_temp("hj_hp", me)>(query_temp("hj_hp_max", me)*9/10) )
            return errs("�㻹�����úܣ����ص�����Ϣ��\n");
        message_vision(CYN"$N"NOR+CYN"���������������ص����Լ�����Ϣ��\n"NOR,me);
    }
    else
    {
        if( present( "hj temp leave obj", target )      // �Ѿ���ʱ�뿪��Ϸ�ˣ����ܰ����ָ�hp
           || query("hj_game/npc", target )
           || query_temp("huanjing", target) != "start"
        )
            return errs("�㲻�ܰ�������˻ָ���Ϣ��\n");

        if( query_temp("hj_hp", target)>(query_temp("hj_hp_max", target)*9/10) )
            return errs("���˻������úܣ����ص�����Ϣ��\n");
        if( query_temp("hj_hp", me)<100 )
            return errs("���Թ˲�Ͼ����Ϊ�������ˣ�\n");
        message_vision(CYN"$N"NOR+CYN"����������$n"NOR+CYN"�ı��ϣ����𡸻ָ�֮��������\n"NOR, me, target );
    }

    set_temp("hj_healing", target, me);
    set_temp("hj_need_waiting", "healing", me);

    remove_call_out("healing");
    call_out("healing", 1, me );
    return 1;
}

void healing( object me)
{
    object env_me,env_target, target;
    int heal_lv, heal_hp;

    if( !me || !me_ok(me) )
        return;
    if( !query_temp("hj_need_waiting", me )
       || query_temp("hj_need_waiting", me) != "healing"
    )
        return;
    target=query_temp("hj_healing", me);
    if( !target
       || !query_temp("huanjing", target )
       || query_temp("huanjing", target) != "start"
       || !query_temp("hj_hp", target )
       || query_temp("hj_hp", target)<1
       || !query_temp("hj_hp_max", target )
      || present( "hj temp leave obj", target )
    )
         return hj_halt( CYN"$N"NOR+CYN"�ھ�һ����ֹͣ�����ûָ�֮����\n"NOR );
    env_target = environment( target );
    env_me = environment( me );
    if( !env_target || env_target != env_me || !query("room_mark", env_target )
      || query("room_mark", env_target) == 1 )
        return hj_halt( CYN"$N"NOR+CYN"�ھ�һ����ֹͣ�����ûָ�֮����\n"NOR );
    // �����ж�ͨ����
    if( query_temp("hj_hp", target)>(query_temp("hj_hp_max", target)*9/10) )
    {
        if( me == target )
            return hj_halt( CYN"$N"NOR+CYN"��Ϣ��˳������������һ������\n"NOR);
        return hj_halt( CYN"$N"NOR+CYN"����$n"NOR+CYN"�Ѿ���Ϣ˳����������������\n"NOR);
    }

    if( me->is_busy() )
    {
        remove_call_out("healing");
        call_out("healing", 1, me );
        return;
    }
    heal_lv=query_temp("hj_game_damages/heal", me);
    heal_hp = (heal_lv / 2 + random(heal_lv / 2 ));  // lv 100 = 50 + random(50)
    // ��֮������������Ч��  ʹ�ûָ�֮����ʱЧ����ǿ
    if( query_temp("hj_game_find", me) == "yu" )
        heal_hp += (heal_hp / 3) + random(heal_hp/5);
    if(target == me)
    {

        // �ɻ�֮��Ψһ����(1)��ʹ�� heal ʱ����æʱ
        if( query_temp("hj_special/rq", me) )
            me->start_busy(1)+random(2);
        else me->start_busy(2+random(2));

        addn_temp("hj_hp", heal_hp, me);
        if( query_temp("hj_hp", me)>query_temp("hj_hp_max", me) )
            set_temp("hj_hp",query_temp("hj_hp_max",  me), me);
        message_vision(CYN"$N"NOR+CYN"���ĵ�����Ϣ��ֻ�������ƻָ���Щ��\n"NOR,me);
        tell_object( me, sprintf("��ǰ�� %d / %d \n",
            query_temp("hj_hp", me),query_temp("hj_hp_max", me)));

        /* ȡ��
        // ����������ܣ���������ʧһ������
        if( !random(query_temp("hj_game_mepower", me)*3 )
           && query_temp("hj_game_mepower", me)>20 )
        {
            addn_temp("hj_game_mepower", -1, me);
            tell_object(me,HIY"��ֻ����Ԫ���ָ�����࣬������ȴ�ƺ�С�ˡ�\n"NOR);
        }
        */
        // ��Ҳ���ܻ�õȼ�����
        if( !random(query_temp("hj_game_damages/heal", me)*2) )
        {
            addn_temp("hj_game_damages/heal", 1, me);
            if( query_temp("hj_game_damages/heal", me)>99 )
                set_temp("hj_game_damages/heal", 99, me);
            else tell_object(me,HIY"��ԡ��ָ�֮����������ֽ���һ�㣡\n"NOR);
        }
        remove_call_out("healing");
        call_out("healing", 1, me );
        return;
    }

    if( query_temp("hj_hp", me)<100 )
        return hj_halt( CYN"$N"NOR+CYN"���ڰ���$n"NOR+CYN"���ˣ�ȴ�����Լ���Ϣ������ֻ�ð��֡�\n"NOR);


    // �ɻ�֮��Ψһ����(2)��ʹ�� heal ʱ����æʱ
    if( query_temp("hj_special/rq", me) )
        me->start_busy( 1+random(3) );
    else
        me->start_busy(3+random(3));
    // ȡ��������
    // ����Ϊ��NPC�������ң����ˣ��Է�����æʱ��
    //    if( !target->query("hj_game/npc") )
    //        target->start_busy(2+random(2));
    addn_temp("hj_hp", heal_hp, target);

    if( query_temp("hj_hp", target)>query_temp("hj_hp_max", target) )
        set_temp("hj_hp",query_temp("hj_hp_max",  target), target);

    message_vision(CYN"$N"NOR+CYN"ȫ��ʩ��Ϊ$n"NOR+CYN"���ˣ�ֻ����$n"NOR+CYN"����ɫ��ת����ࡣ\n"NOR, me, target);
    // ��������(�����Ƿ�NPC)�������һС��ļӷ֣�����Ҫ�����������Ϣ��
    // �Ѹ��ģ���Ҫ�����Լ���Ϣ��С�������������е÷֡�
    addn_temp("hj_hp", -random(heal_lv/3), me);
    message_vision(CYN"$N"NOR+CYN"�۾�����ת�ۼ��������ֳ�ƣ��֮ɫ��\n"NOR,me);
    remove_call_out("healing");
    call_out("healing", 1, me );
    return;
}

int do_hjquit(string arg)
{
    object qxd,me = this_player();

    if( !me_ok(me) ) return errs("�㲻��ʹ�ñ�ָ�\n");

    if ( !arg || (arg!= "fail" && arg!="ok") )
        return errs(HIG"\n             <hjquit> ָ��ʹ����ʾ��

< hjquit fail >     �������еĳɼ��������˳� �þ� ��Ϸ��
                      "HIR"ʹ�ô�ָ��������1�㹱�׶ȣ������á�"NOR"
< hjquit ok >       ��������ʽ�˳�������ʹ�� �ع�֮������
                      ��������� 500 �����ϵĵ�ǰ�÷֣�����
                      ��Ҫһ���� �ѽ�����Ϸ ʱ�䡣
\n"NOR);

    if ( arg == "fail" )
    {
        if( query("shenzhou/pts", me)<1 )
            return errs("����1�㹱�׶ȶ�û�У�����ʹ�ñ�ָ�\n");
        write("��������ǿ���˳�ָ�����ʧ�ܵ�����˳� �þ� 1 ��Ϸ��"HIR"��ָ��۳���һ�㹱�׶ȣ�\n"NOR);
        addn("shenzhou/pts", -1, me);
        set_temp("hj_hp", -1, me);
        me->start_busy(5);
        return 1;
    }

    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("�㻹æ���ء�\n");

    qxd = present( "qixing deng",me);
    if( !qxd || query("my_master", qxd) != me )
        return errs("������û�����ǵƣ����������㲻���������ˣ�����\n");

    if( !query("can_quit_hj", qxd) )
        return errs("��Ÿս�����Ϸû��ã�ȷʵҪ�˳���ʹ�� <hjquit fail> ָ���������˳���\n"HIR"��ע�⣬ʹ�� fail ����ָ���˳�����ۼ���Ĺ��׶�1�㣬�����ã�\n"NOR);

    if( !query_temp("hj_score", me) || query_temp("hj_score", me)<500 )
        return errs("�㵱ǰ����Ϸ�÷ֲ��� 500 �֣�ȷʵҪ�˳���ʹ�� <hjquit fail> ָ���������˳���\n"HIR"��ע�⣬ʹ�� fail ����ָ���˳�����ۼ���Ĺ��׶�1�㣬�����ã�\n"NOR);

    if( query("wait_over", qxd) == "yes" )
        return errs("�����Ϸʱ�伴������������Ϊ�ȴ����ɡ�\n");

    message_vision(CYN"$N"NOR+CYN"�����е�������ʵӳ�֣���\n"NOR,me);
    write(HIR"ʹ�ñ�ָ����۳���� 500 ����Ϸ�÷֣�\n"NOR);
    addn_temp("hj_score", -499, me);
    me->start_busy(3);

    set("use_huigui", "yes", qxd);

    message_vision(WHT"ֻ��һ�����֪�Ӻδ�Ʈ����������Ũ����\n"NOR,me);
    return 1;
}

int do_hjtime()
{
    object me = this_player();
    int enter_time=query_temp("hj_enter_time", me);;

    write(sprintf( "�������Ϸ��ʱ���� %s �����ڵ�ʱ���� %s ��\n��Ϸʱ��%s ��\n",
        !enter_time ? "δ֪" : ctime_format( enter_time ),  ctime_format(),
        !enter_time ? "δ֪" : sprintf( "�� %d Сʱ %d �� %d ��", 
            ( time() - enter_time ) / 3600,
            ( ( time() - enter_time ) % 3600 ) / 60,
            ( ( time() - enter_time ) % 3600 ) % 60 ) ) );

    return 1;
}

int do_halt()
{
    object me = this_player(),target;
    string temp;

    if( !me_ok(me) )
        return errs( "ʲô��\n");
    if( (!query_temp("hj_healing", me) && !query_temp("hj_fighting", me)) || 
        !query_temp("hj_need_waiting", me) )
    {
        delete_temp("hj_need_waiting", me);
        return errs( "�����ڲ�����ս���������С�\n");
    }
    temp=query_temp("hj_need_waiting", me);
    if( temp == "healing" )
    {
        target=query_temp("hj_healing", me);
        if( target == me )
        {
            hj_halt(CYN"$N"NOR+CYN"����һ�ڴ�����ֹͣ�˵�����Ϣ��\n"NOR);
            return 1;
        }
        hj_halt(CYN"$N"NOR+CYN"����һ�գ�ͣ���˶�$n"NOR+CYN"�����ˡ�\n"NOR);
        return 1;
    }
    hj_halt(CYN"$N"NOR+CYN"���һ�У�Ծ��սȦ�����ˡ�\n"NOR);
    return 1;
}

// �����ˣ���ң����ڣ�������ᱻ��������Բ��ÿ���
// ��ʱ�з��������⡣
void delete_special_sks( object me, string sks, string sks_name )
{
    // ����ô˵��������ȫ��Ҫ����
    if( !me || !me_ok(me) )
        return;
    // ����� wiztools ֹͣ�����ã�������ͣһ�Σ���Ǹ�Ц������Ҫ�������Ƿ����á�
    if( !query_temp("hj_special/"+sks, me) )
        return;
    delete_temp("hj_special/"+sks, me);
    message_vision( HIY"\nֻ��Χ��$N"HIY"��һȦ΢�����ˣ���"+sks_name+"�����ܵ�Ч����ʧ�ˡ�\n\n"NOR, me);
}

int do_gyun( string arg )
{
    // ���ָ�����չ���ã������ˣ��������ա�
    // ʵ����Ҫ����ʱ���ٸ�Ϊ������ķ�ʽ��
    object me = this_player();
    string *sp_sks = ({ "xk", "cm", "ll", "gm", "kz", "sh", "rq", "xs" }), find_name;
    int HpNeed = 50, hpneed, del_time;
    // HpNeed ���ܸ������� 20%
    mapping sks_sks = ([
        "xk": ({ "���", "��֮����", "hfzj", "����֮��" }), 
        "cm": ({ "����", "��֮����", "hyzj", "����֮��" }),
        "ll": ({ "����", "��֮����", "llzj", "����֮��" }),
        "gm": ({ "��â", "��֮����", "ydzj", "����֮��" }),
        "kz": ({ "����",       "--", "heal", "�ָ�֮��" }),
        "sh": ({ "�ػ�",       "--", "dhzj", "���֮��" }),
        "rq": ({ "����",       "--", "fhzj", "�ɻ�֮��" }),
        "xs": ({ "Ѱʯ",       "--", "gszj", "��ʯ֮��" }),
    ]);


    if( !me_ok(me) )
    {
        write("ʲô��\n");
        return 1;
    }

    if( !arg || member_array( arg, sp_sks ) == -1 )
    {
        write( sprintf("
      ������⼼�����������
"WHT"=====================================
"HIW"    ���(xk)   >>>>>>   %s
"HIM"    ����(cm)   >>>>>>   %s
"HIC"    ����(ll)   >>>>>>   %s
"HIG"    ��â(gm)   >>>>>>   %s
"NOR+CYN"    ����(kz)   >>>>>>   %s
"HIB"    �ػ�(sh)   >>>>>>   %s
"HIR"    ����(rq)   >>>>>>   %s
"HIY"    Ѱʯ(xs)   >>>>>>   %s
"NOR+WHT"=====================================\n"NOR, 
    query_temp("hj_special/xk", me)?"������":"--",
    query_temp("hj_special/cm", me)?"������":"--",
    query_temp("hj_special/ll", me)?"������":"--",
    query_temp("hj_special/gm", me)?"������":"--",
    query_temp("hj_special/kz", me)?"������":"--",
    query_temp("hj_special/sh", me)?"������":"--",
    query_temp("hj_special/rq", me)?"������":"--",
    query_temp("hj_special/xs", me)?"������":"--"));
        return 1;
    }

    // æʱ�����е���������Ϊ�˿�����ս���л����������ü���
    if( me->query_busy() > 5 )
    {
        write("������ʵ����̫æ��(æʱ5������)���޷������������⼼�ܡ�\n");
        return 1;
    }
    // �����ظ����á�
    if( query_temp("hj_special/"+arg, me) )
    {
        write("����������������ܡ�\n");
        return 1;
    }
    // ��Ҫ������Ϣ
    hpneed = HpNeed + random(HpNeed/5);
    if( query_temp("hj_hp", me)<(hpneed+50) )
    {
        write("�����Ϣ̫�����޷��������⼼�ܡ�\n");
        return 1;
    }
    if( query_temp("hj_game_damages/"+sks_sks[arg][2], me)<YUN_LvNeed )
    {
        write(sprintf("��ġ�%s���ȼ��������޷����á�%s�����ܡ�\n",
            sks_sks[arg][3], sks_sks[arg][0] ) );
        return 1;
    }
    // Ч��
    del_time=query_temp("hj_game_damages/"+sks_sks[arg][2], me)*4/5;
    // ����F,Y,L,D�������⼼���Ǳ�������Ч������
    if( sks_sks[arg][1] != "--" && query("find_name") != sks_sks[arg][1] )
        del_time /= 2;

    set_temp("hj_special/"+arg, del_time, me);
    // ��� set ��ֵ��ʵ�����壬��ʹ���������ֵ��
    addn_temp("hj_hp", -hpneed, me);
    //    me->start_busy( me->query_busy() + 1 );
    // ȡ���������õ�æʱ�����䱾����Ҫ������Ϣ���ʲ�������æʱ��
    // �����⼼����ʱ������
    switch( sks_sks[arg][0] )
    {
        // #########################################################
        case "���":
            message_vision(HIW"\nֻ��$N"HIW"�ſ�˫�֣������Ŀ�������ģ���ʱ��ƽ����磬$N"HIW"���������գ�\n"
                "�����Ƿ�֮����ա��ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "����":
            message_vision(HIM"\nֻ��$N"NOR+HIM"���ֻ��գ���ͷ��ĿĬ�����ģ���ʱ����������з�ӿ������\n"
                "��������֮���������ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "����":
            message_vision(HIC"\nֻ��$N"HIC"˫ĿԲ����ȭ���죬���д��һ������ʱȫ������ž���죬���ƾ��ˣ�\n"
                "��������֮���������ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "��â":
            message_vision(HIG"\nֻ��$N"HIG"����̯�ƻ���ǰ�죬ɲ�Ǽ���������һ��ҫ�۹�â��˲������ȫ��\n"
                "�����ǵ�֮����â���ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "����":
            message_vision( CYN"\nֻ��$N"NOR+CYN"˫�ƺ�ʮ��ĬĬ�����˼������ģ���ʱһ��������������ľ�ƽ�ͣ����޷��ǡ�\n"
                "�����ǻָ�֮�������ơ��ؼ���\n\n"NOR, me );
            del_time *= 4;  // Ч���־�
            break;
        // #########################################################
        case "�ػ�":
            message_vision( HIB"\nֻ��$N"HIB"˫��ʳָ���ö��ģ��������ģ��Ĵ���ʱ����һ������֮�����������廤��һ�㣡\n"
                "�����Ƕ��֮�����ػ����ؼ���\n\n"NOR, me );
            break;
        // #########################################################
        case "����":
            message_vision( HIR"\nֻ��$N"HIR"������ȭ��������֮�ԣ��������ʳ���ж�ָ������Ц�ݣ���һ������Ү����\n"
                "�����Ƿɻ�֮�������项�ؼ���\n\n"NOR,me);
            break;
        // #########################################################
        case "Ѱʯ":
            message_vision( HIY"\nֻ��$N"HIY"˫�ֽ��շ�����ǰ����Ŀ����������ʯͷ��ʯͷ����Ҫʯͷ������\n"
                "�����ǹ�ʯ֮����Ѱʯ���ؼ���\n\n"NOR,me);
            break;
        // #########################################################
    }
    call_out( "delete_special_sks", del_time , me, arg, sks_sks[arg][0] );
    write( sprintf( "����Լ���� %d ��þ�ʱ����Ч��\n", del_time ) );
    return 1;
}
