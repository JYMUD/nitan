mapping *dizhia=({
        (["cdizhi":        "����ɽ",
        "weizhi2" :        "/d/baituo/cao1",]),
        (["cdizhi":        "����",
        "weizhi2" :        "/d/changcheng/changcheng13",]),
        (["cdizhi":        "���ݳ�",
        "weizhi2" :        "/d/city/bingyin",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/beijing/huayuan",]),
        (["cdizhi":        "�ɶ���",
        "weizhi2" :        "/d/chengdu/wuhouci",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/changan/chaguan",]),
        (["cdizhi":        "�����",
        "weizhi2" :        "/d/dali/tingyuan",]),
        (["cdizhi":        "����ɽ",
        "weizhi2" :        "/d/emei/jieyindian",]),
        (["cdizhi":        "��ɽ��",
        "weizhi2" :        "/d/foshan/street4",]),
        (["cdizhi":        "���ݳ�",
        "weizhi2" :        "/d/fuzhou/luoxingta",]),
        (["cdizhi":        "����",
        "weizhi2" :        "/d/guanwai/xuedi2",]),
        (["cdizhi":        "���ݳ�",
        "weizhi2" :        "/d/hangzhou/shiwudong",]),
        (["cdizhi":        "��ľ��",
        "weizhi2" :        "/d/heimuya/shijie2",]),
        (["cdizhi":        "��ɽ",
        "weizhi2" :        "/d/hengshan/yuyang",]),
        (["cdizhi":        "��ɽ",
        "weizhi2" :        "/d/henshan/nantaisi",]),
        (["cdizhi":        "�ƺ�",
        "weizhi2" :        "/d/huanghe/weifen",]),
        (["cdizhi":        "��ɽ",
        "weizhi2" :        "/d/huashan/yunuci",]),
        (["cdizhi":        "�����",
        "weizhi2" :        "/d/jiangling/longzhong",]),
        (["cdizhi":        "���˳�",
        "weizhi2" :        "/d/jiaxing/njroad2",]),
        (["cdizhi":        "����ɽ",
        "weizhi2" :        "/d/kunlun/jiuqulang2",]),
        (["cdizhi":        "���ݳ�",
        "weizhi2" :        "/d/lanzhou/street1",]),
        (["cdizhi":        "���շ�",
        "weizhi2" :        "/d/lingjiu/jian",]),
        (["cdizhi":        "���ݳ�",
        "weizhi2" :        "/d/lingzhou/kongdi",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/luoyang/wanghuating",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/mingjiao/tohsq1",]),
        (["cdizhi":        "����ɽ",
        "weizhi2" :        "/d/qilian/zhutishan",]),
        (["cdizhi":        "���ɽ",
        "weizhi2" :        "/d/qingcheng/huyingting",]),
        (["cdizhi":        "��ɽ",
        "weizhi2" :        "/d/songshan/junjigate",]),
        (["cdizhi":        "���ݳ�",
        "weizhi2" :        "/d/suzhou/liuyuan",]),
        (["cdizhi":        "̩ɽ",
        "weizhi2" :        "/d/taishan/tianjie",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/tianlongsi/tading",]),
        (["cdizhi":        "���Ʒ�",
        "weizhi2" :        "/d/tiezhang/guangchang",]),
        (["cdizhi":        "��ɽ��",
        "weizhi2" :        "/d/village/wexit",]),
        (["cdizhi":        "��ٹ�",
        "weizhi2" :        "/d/wanjiegu/port2",]),
        (["cdizhi":        "�嶾��",
        "weizhi2" :        "/d/wudujiao/wdsl2",]),
        (["cdizhi":        "����ɽ",
        "weizhi2" :        "/d/wuliang/road4",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/wuxi/road15",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/xiangyang/walle3",]),
        (["cdizhi":        "���޺�",
        "weizhi2" :        "/d/xingxiu/shidao",]),
        (["cdizhi":        "ѩ��",
        "weizhi2" :        "/d/xuedao/shandong2",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/xueshan/zoulang2",]),
        (["cdizhi":        "������",
        "weizhi2" :        "/d/yanziwu/qiushuan",]),
        (["cdizhi":        "Ȫ��",
        "weizhi2" :        "/d/quanzhou/jiangjunfu1",]),
        (["cdizhi":        "Į��",
        "weizhi2" :        "/d/mobei/caocong1",]),
});

void init()
{
        object ob, me;
        mapping dizhis,hp_status;
        int exp, nei, nei1;

        ::init();
     if (!query("inited"))
      {
         set("chat_chance", 10);
               set("chat_msg", ({
                      (: random_move :)
                          }) );
                      remove_call_out("dest");
         call_out("dest",2000);
         set("inited",1);
      }
        ob = this_player();
  me = this_object();

        if (interactive(ob)
                 && !query("no_fight", environment(ob) )
//                && ob->query_condition("guanfu_task")
                && present("wenshu", ob)
                 && query("id", me) == query_temp("guanfu_target", ob) )
        {
        nei=query("neili", me);
        nei1=query("neili", ob);
        hp_status = ob->query_entire_dbase();

        dizhis = dizhia[random(sizeof(dizhia))];
        exp=query("combat_exp", ob);

///��һ��׷ɱ
        if( query_temp("mark/gkill1", ob) )
        {
          message_vision( HIR"$n����$NĿ������ע�����Լ�һ������������ͣ���˽Ų���\n"NOR, ob, me);
         if( query("name", me) == query_temp("guanf_huida1", ob) )
                {
                        message_vision( HIR"$n����$N�ߵ���ǰ���ݺݵ��������ʶ̧�ٵĶ������Һ�����Ȱû�ã�\n��������㳢����ү��������\n"NOR,ob,me);
                        me->set_leader(ob);
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 0, ob);
                        delete_temp("guanf_huida1", ob);
                        delete_temp("mark/gkill1", ob);

                        if ((int)exp<3000000)
                            set("combat_exp", exp*3/2, me);
                        else
                            set("combat_exp", exp*2, me);
     if ((hp_status["max_qi"]*3/2)<1500)
     {
        set("max_qi", 1500, me);
        set("eff_qi", 1500, me);
        set("qi", 1500, me);
     }
     else
           {
              set("max_qi", hp_status["max_qi"]*3/2, me);
              set("eff_qi", hp_status["max_qi"]*3/2, me);
              set("qi", hp_status["max_qi"]*3/2, me);
           }

     if ((hp_status["max_neili"])<1500)
        set("max_neili", 1500, me);
     else
        set("max_neili", hp_status["max_neili"], me);

     if((hp_status["neili"])<1500)
        set("neili", 1500, me);
     else
        set("neili", hp_status["neili"], me);
           set("jiali", nei1/20, me);
         }
   else
   {

                        switch(random(4))
                        {
                                case 0:
                                        message_vision("$n�ٺټ�Ц��������æ��Ц������λ"+RANK_D->query_respect(ob)+ "�ǹٸ��Ĳ�ͷ�ɣ�����Ҷ����������ˣ������ܷ��̧���֣��ұ�����л����ú�����һ�£��Ƿ�Ը�⣿\n",ob,me);
                                        write (HIY"�����ѡ��ͬ��(yes)���߾ܾ�(no)��\n"NOR);
                                        set_temp("guanf_huida1",query("name",  me), ob);
                                        break;
                                case 1:
                                        message_vision( HIR"$n��Цһ��˵��������಻�����ģ�����ʮ����ү��Ҳ���£�\n�漴�۾�һ�ɣ�����$N�ͳ��˹�ȥ��\n"NOR,ob,me);
                                        me->set_leader(ob);
                                        remove_call_out("kill_ob");
                                        call_out("kill_ob", 0, ob);
                                        delete_temp("mark/gkill1", ob);
                                        break;
                                case 2:
                                        message_vision( WHT"$n��$N�ߵ���ǰ������һЦ��˵������ǧ��׷������ҿ����������ҺΣ�\n"NOR,ob,me);
                                        write(WHT"��е�һ�����ε�ɱ�������в���һ����\n"NOR);
                                        delete_temp("mark/gkill1", ob);
                                        break;
                                case 3:
                                        message_vision("$n��Ȼ�������棬һ�������������$N˵����С������������С��������ȫ�ǹٸ���\n�ݺ�����˵ز����������������������һ�棬�ҽ���һ���м�������\n",ob,me);
                                        delete_temp("mark/gkill1", ob);
                        }
                }
        }
// end///  �ڶ���׷ɱ
                if( query_temp("mark/gkill2", ob) )
                {
                        switch(random(2))
                        {
                                case 0:
                                        message_vision( HIR"$n��ͷ��������������һ��������ͨ����۾�����$N�ͳ��˹�ȥ��\n"NOR, ob,me);
                                        me->set_leader(ob);
                                        if ((int)exp<3000000)
                                           set("combat_exp", exp*3/2, me);
                                        else
                                           set("combat_exp", exp*2, me);
                                        set("jiali", nei1/15, me);
                                        remove_call_out("kill_ob");
                                        call_out("kill_ob", 0, ob);
                                        break;
                                case 1:
                                        message_vision( HIY"$nһ����$N���ٺ�һЦ��ͷҲ���ؼ�������֮�У�����Ĩ�����ˡ�\n"NOR,ob,me);
                                        delete_temp("mark/gkill2", ob);
                                        set_temp("mark/gkill3", 1, ob);
                                        write(WHT"��"+query_temp("guanfu_targetnm", ob)+"����������"+dizhis["cdizhi"]+"���ķ�����ȥ�ˡ�\n"NOR);
                                        me->move(dizhis["weizhi2"]);
                                        me->random_move();
                                        me->random_move();
                                        me->random_move();
                                        return;
                        }
                }
                //������
                if( query_temp("mark/gkill3", ob) )
                {
                        message_vision(HIR "$n�����ܻ��Ķ�$N�µ���ɱ�˲���ͷ��أ���һ�ٿ����ƣ���ү����ͺ���ƴ���������ơ�\n"NOR,ob,me);
                        if( nei<nei1 && (!query_temp("gf_nlset", me)) )
                        {
                                set("max_neili",query("max_neili",  ob), me);
                                set("neili", nei1, me);
                                set_temp("gf_nlset", 1, me);
                        }
                        me->set_leader(ob);
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 0, ob);
                        if ((int)exp<3000000)
                            set("combat_exp", exp*3/2, me);
                        else
                            set("combat_exp", exp*2, me);
                        set("jiali", nei1/15, me);
                        me->reincarnate();
                }
        }
        add_action("do_yes","yes");
  add_action("do_no","no");

//        call_out("dest", 2000);
/*        add_action("do_hit","hit");
        add_action("do_hit","kill");
        add_action("do_hit","touxi");
        add_action("do_hit","ansuan");
        add_action("do_hit","steal");
*/
}

/*int do_hit(string arg)
{
        object ob = this_object();
        object me = this_player();
        if( !arg || arg != query("id", ob) )
                return 0;

        if( !(query_temp("guanfu_target", me) == query("id", ob)) )
        {
                if (userp(me) )
                {
                        tell_object(me,HIW"������Ҫץ���ˣ���ʲô���֣�\n"NOR);
                        return 1;
                }
                else return 0;
        }
}*/
int accept_hit(string arg)
{
           object me = this_player();
     object ob = this_object();
     if( !(query_temp("guanfu_target", me) == query("id", ob)) )
        return notify_fail(HIW"������Ҫץ���ˣ���ʲô���֣�\n"NOR);
     return 1;
}
/*
int accept_kill(object who)                {return (int)accept_hit(who);}
int accept_ansuan(object who) {return (int)accept_hit(who);}
int accept_touxi(object who)       {return (int)accept_hit(who);}
*/


void random_move()
{
/*        mapping exits;
        string *dirs, dir, dest;

        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys(exits);
        dir = dirs[random(sizeof(dirs))];
        dest = exits[dir];
        if (!find_object(dest)) load_object(dest);
        if( query("no_fight", find_object(dest)))return 0;
        if( this_object()->is_fighting() ) return 0;
        command("go " + dir);
        return 1;
*/
        NPC_D->random_move(this_object());
}

int do_yes()
{
        object r_shen, me, ob;
        me = this_object();
        ob = this_player();

        if( !query_temp("guanf_huida1", ob))return 0;
        if( query_temp("guanf_huida1", ob) != query("name", me) )
                return 0;
        if( query("shen", ob)<1 && query("combat_exp", ob)<180000 )
        {
                command("say ��λ"+RANK_D->query_respect(ob)+"һ��ǰ;Զ�󣬺ٺ٣����ǲ��������ġ�\n");
                me->add_money("gold",20+random(20));
                command("give"+query("id", ob)+"gold");
                message_vision("$N�ٺ�һЦ��ת���뿪��һգ�۾���ʧ�����ˡ�\n",me);
                destruct(me);
                return 1;
        }
        if( query("shen", ob)<1 && 
                query("combat_exp", ob)>180000 && 
                query("combat_exp", ob)<500000 )
        {
                command("say ����Ϳ�����λ"+RANK_D->query_respect(ob)+"�ǵ����Ŀ��ܣ��ٺ٣����С������������¡�\n");
                message_vision("$N�ٺټ�Ц����������������$nһ���˲Ρ�\n",me,ob);
                r_shen=new("/clone/medicine/vegetable/renshen");
                r_shen->move(ob);
                command("give"+query("id", ob)+"gold");
                message_vision("$N�ٺ�һЦ��ת���뿪��һգ�۾���ʧ�����ˡ�\n",me);
                destruct(me);
                return 1;
        }
        if( query("shen", ob)<1 && query("combat_exp", ob)>500000 )
        {
                command( "say �����˼ҹ�����˳��ڣ�С��ʵ���벻����ʲ��Т�����ϣ���ͷ��������˵�ɡ�\n");
                message_vision("$N�ٺ�һЦ��ת���뿪��һգ�۾���ʧ�����ˡ�\n",me);
                destruct(me);
                return 1;
        }
        if( query("shen", ob)>1 && query("combat_exp", ob)<120000 )
        {
                command("say ��λ"+RANK_D->query_respect(ob)+"ǰ;Զ��һ���������ٺ٣������\n");
                me->add_money("gold",20+random(30));
                command("give"+query("id", ob)+"gold");
                addn("shen", -1000, ob);
                message_vision("$N�ٺ�һЦ��ת���뿪��һգ�۾���ʧ�����ˡ�\n",me);
                destruct(me);
                return 1;
        }
        if( query("shen", ob)>1 && 
                query("combat_exp", ob)>120000 && 
                query("combat_exp", ob)<500000 )
        {
                command("say ��λ"+RANK_D->query_respect(ob)+"�����屡���죬���С���ﾴ��������¡�\n");
                me->add_money("gold",30+random(30));
                command("give"+query("id", ob)+"gold");
                message_vision("$N�ٺټ�Ц����������������$nһ���˲Ρ�\n",me,ob);
                r_shen=new("/clone/medicine/vegetable/renshen");
                r_shen->move(ob);
                addn("shen", -3000, ob);
                message_vision("$N�ٺ�һЦ��ת���뿪��һգ�۾���ʧ�����ˡ�\n",me);
                destruct(me);
                return 1;
        }
        command("say �Թ�а���Ʋ����������²�������СС��Ц��ǧ��Ҫ���氡��\n");
        command("laugh"+query("id", ob));
        write("�Է�����������ȡЦ���㲻��ŭ�����ա�\n");
        tell_room(environment(me),query("name", me)+"������������֮�У�ת�۾Ͳ����ˡ�\n",({me}));
        destruct(me);
        return 1;
}


int do_no()
{
        object me, ob;
        me = this_object();
        ob = this_player();

        if( !query_temp("guanf_huida1", ob))return 0;
        if( query_temp("guanf_huida1", ob) != query("name", me) )
                return 0;
        if( query("shen", ob)<1 )
        {
                command("say ��λ"+RANK_D->query_respect(ob)+"һ�����������ұ���һ·��ɫ��ȴ������װʲô����Ӣ���أ���\n");
                delete_temp("guanf_huida1", ob);
                delete_temp("mark/gkill1", ob);
                return 1;
        }
        command("say ��λ"+RANK_D->query_respect(ob)+"һ�������������������ɵ��ӣ�������֪����������������\n");
        command("hehe"+query("id", ob));
        delete_temp("guanf_huida1", ob);
        delete_temp("mark/gkill1", ob);
        return 1;
}

void die()
{
        object ob, me,newob;
        mapping dizhis;

        ob = this_object();
        me = query_temp("last_damage_from");
        dizhis = dizhia[random(sizeof(dizhia))];

        if( !query_temp("mark/gkill3", me) && 
                !query_temp("mark/gkill2", me) && 
                query("id", ob) == query_temp("guanfu_target", me) )
        {
                message_vision(WHT "$N������������Ц�����������֣���˵��ǿ����ʹ������"+dizhis["cdizhi"]+"�������ߡ�\n"NOR,ob,me);
                set_temp("mark/gkill2", 1, me);
//                message_vision(WHT"��"+ob->query_temp("guanfu_targetnm")+"����������"+dizhis["cdizhi"]+"���ķ�����ȥ�ˡ�\n"NOR);
                newob=new(query_temp("path_rooms", me));
                newob->move(dizhis["weizhi2"]);
                newob->random_move();
                newob->random_move();
                newob->random_move();
                destruct(ob);
                return;
        }
        if( query_temp("mark/gkill2", me) && 
                query("id", ob) == query_temp("guanfu_target", me) )
        {
                message_vision(WHT "$N��Цһ����˵�������ÿ��Ĺ��򣡡�˵��������"+dizhis["cdizhi"]+"�������ߡ�\n"NOR,ob,me);
                delete_temp("mark/gkill2", me);
                set_temp("mark/gkill3", 1, me);
//                message_vision(WHT"��"+ob->query_temp("guanfu_targetnm")+"����������"+dizhis["cdizhi"]+"���ķ�����ȥ�ˡ�\n"NOR);
//                new(me->query_temp("path_rooms"))->move(dizhis["weizhi2"]);
                newob=new(query_temp("path_rooms", me));
                newob->move(dizhis["weizhi2"]);
                newob->random_move();
                newob->random_move();
                newob->random_move();
                destruct(ob);
                return;
        }
        if( query("id", ob) != query_temp("guanfu_target", me) )
        {
                message_vision(WHT "ͻȻ$NһԾ���𣬵������ټ��˸�λ��������ʧ����Ӱ�����ˡ�\n"NOR,ob,me);
                destruct(ob);
                return;
        }
        ::die();
}
int accept_fight(object me)
{
        command("say ��ү����Ҫ��·��û��˼���㶯�֡�");
        return 0;
}
void dest()
{
        object ob;
        ob = this_object();
        if (environment())
        message_vision("ֻ��$N��Ȼ��ת���У�������������У�ת�۾��ټ����ޡ�\n", ob);
        destruct(this_object());
}
