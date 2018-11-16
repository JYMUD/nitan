//by daidai
//���ӽ��߽��ܵڶ��׶�

#include <ansi.h>;
inherit NPC;
#define QUESTDIR "quest/���߽���/"
int ask_weapon();
int ask_fuchou();
int ask_jinshe();
int ask_anqi();

void throwing();
int do_kill(object me, object dest);
int give_weapon();
void create()
{
        set_name("��ѩ��", ({ "xia xueyi", "xia", "xueyi" }) );
        set("nickname", HIY"�����ɾ�"NOR);
        set("gender", "����" );
        set("shen_type", 1);
        set("age", 23);
        set("str", 34);
        set("con", 28);
        set("int", 27);
        set("dex", 34);
        set("per", 30);
        set("location", 1);
        set("shen", -50000);
        set("long",@LONG
������ĸ�������ò���ڡ�����ʱȫ�Ҳ��ұ��¼���
�Ͻ������ţ���־���𡣴�������Ź֣�Ϊ�����ݣ�
�书���������˰�����Ѳ⡣������������������Ϊ
֮ɫ�䣬���ǳ������Ѳ�����\
LONG);
        set("combat_exp", 2500000);
        set("attitude", "heroism");
        set("max_qi", 6000);
        set("quest/���߽���/pass", 1);
        set("unique", 1);
        set("max_jing", 5000);
        set("eff_jingli", 3000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jiali", 70);
        set_skill("force", 260);
        set_skill("medicine", 130);
        set_skill("hunyuan-yiqi", 260);
        set_skill("literate", 200);
        set_skill("jinshe-jianfa", 260);
        set_skill("jinshe-zhangfa", 260);
        set_skill("sword", 260);
        set_skill("dodge", 260);
        set_skill("parry", 260);
        set_skill("strike", 260);
        set_skill("xinyuegong", 260);

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "sword.kuangwu" :),
                (: perform_action, "sword.sheying" :),
                (: throwing :),
        }));
        set("chat_chance", 35);
        set("chat_msg", ({ (: random_move :), }));

    set("inquiry", ([
            "����׶" : (: ask_weapon :),
            "����" : (: ask_fuchou :),
            "����" : (: ask_anqi :),
            "����" : (: ask_fuchou :),
             "�ĵ�" : (: ask_jinshe :),
            "���߽���" : (: ask_jinshe :),
             "�ؾ�" : (: ask_jinshe :),
                ]));
 
        map_skill("force", "hunyuan-yiqi");
        map_skill("strike", "jinshe-zhangfa");
        map_skill("dodge", "xinyuegong");
        map_skill("parry", "jinshe-zhangfa");
        map_skill("sword", "jinshe-jianfa");
        prepare_skill("strike", "jinshe-zhangfa");

        set_temp("apply/armor", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/damage", 70);
        set_temp("apply/attack", 80);
        setup();

        if (clonep()) {
                UPDATE_D->get_cloth(this_object());
                add_money("gold", 2);
           carry_object("/d/huashan/jinshe/obj/jinshe-zhui");
                give_weapon();
                call_out("do_back", 300+random(200), this_object());
        }
}

int give_weapon()
{
        object sword, weapon;
        if (clonep(this_object())) {
                if( !objectp(weapon=query_temp("weapon", this_object()))){
                        sword = unew(BINGQI_D("sword/jinshesword"));
                        if(!sword) sword = unew(BINGQI_D("changjian1"));
                        sword->move(this_object());
                        sword->wield();
                }
                else if( query("id", weapon) != "jinshesword" && 
                        objectp(sword = unew(BINGQI_D("sword/jinshesword")))) {
                                weapon->unequip();
                                destruct(weapon);
                                sword->move(this_object());
                                sword->wield();
                }

                if(objectp(sword = unew(BINGQI_D("throwing/jinshe-zhui"))) )
                        sword->move(this_object());
                if(!objectp(sword = present("zhuihun biao", this_object()))
                || sword->query_amount() < 2 )
                        carry_object(BINGQI_D("zh_biao"));
        }
}

void init()
{
        object ob, me;
        me = this_object();
        ::init();
        if (interactive(ob = this_player()) && !wizardp(ob) && !is_fighting()){
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_look",({"look", "consider", "smash", "kick", "kick2", "cut", "flirt", "lean"
                                "love", "interest", "kiss" }));
}


int do_look(string target)
{
        object me;

        if( !target ) return 0;
        me = this_player();

        if( id(target) && query("gender", me) != "Ů��" && !is_busy() && !wizardp(me)){
                message("vision",HIR "��ѩ��ӥ��һ���������"+RANK_D->query_rude(me)+"��������\n"NOR, environment(), this_object() );
                if(present("zhuihun biao", me))
                        command("throwbiaoat"+query("id", me));
                else COMBAT_D->do_attack(this_object(),me,query_temp("weapon", this_object()),1);
        }
        return 0;
}

void greeting(object ob)
{
        object me = this_object();

        if(!me || !ob || environment(ob) != environment(this_object())) return;

        if( query("combat_exp", ob)>800000 && query("gender", ob) != "Ů��" )
                addn_temp("xiaxueyi_meet", 1, ob);

        if( present("jinshesword",ob) && !query("no_fight", environment(me))){
                message_vision( CYN"\n$NͻȻ����$n���£���������Ľ�������\n"NOR,me,ob);
               ob->start_busy(1);
                do_kill(me, ob);
        }

        if( me->is_busy() || me->is_fighting()) return;

        else if( query_temp("xiaxueyi_meet", ob)>2
           && !query("no_fight", environment(me) )
           && query_temp("user_type", ob) != "worker"){
                message_vision( CYN"\n$N����Ŀ���$nһ�ۣ�һ����м�����ӡ�\n"NOR,me,ob);
                ob->start_busy(random(2));
                delete_temp("xiaxueyi_meet", ob);
   //             me->fight_ob(ob); //������ǰ���룬xia����ô����ô��
   //            ob->fight_ob(me);
        }
}

void throwing()
{
        switch(random(2)) {
                case 0 : command("throw zhui"); break;
                case 1 : command("throw biao"); break;
        }
}

void kill_ob(object me)
{
      command("perform kuangwu");
      ::kill_ob(me);

}

string get_user_place(int i)
{
        object *obs = users(), ob, room;

        i++;
        if( i > 10 ) return 0;

        ob = obs[random(sizeof(obs))];
        room = environment(ob);

        if (wiz_level(ob)
        || ob->is_ghost()
        || !room
         || query("no_fight", room )
        || strsrch(file_name(room),"/d/") < 0
        || !strsrch(base_name(room), "/d/wizard/")
        || !strsrch(base_name(room), "/d/zhiye/")
        || !strsrch(base_name(room), "/d/death/")
        || !strsrch(base_name(room), "/d/wuguan/"))
                return get_user_place(i);

        else return file_name(room);

}
int do_back(object me)
{
        string room;

        remove_call_out("do_back");
        if (!stringp(room = get_user_place(0)))
                me->move("/d/huashan/shanlu1");
        else me->move(room);

        tell_room(environment(me),query("name", me)+"�첽���˹�����\n",({me}));
        me->set_leader(0);
        give_weapon();
        me->reincarnate();
        return 1;
}

int checking(object me, object dest)
{
        object ob;
        if (!me || !dest || !present(dest, environment(me))) return 0;
        if (me->is_fighting(dest)){
                call_out("checking", 1, me, dest);
                return 1;
        }

        if( objectp(ob = present("corpse", environment(me)))
           && query("victim_name", ob) == query("name", dest)){
                remove_call_out("checking");
                if( objectp(dest = present("jinshe sword", ob)))
                        destruct(dest);
                command("chat* grin corpse");
                tell_room(environment(me),query("name", me)+"������һ�ڣ��첽���˳�ȥ��\n"NOR,({me}));
                call_out("do_back", 1, me);
                return 1;
        }

        return 1;
}

int do_kill(object me, object dest)
{
        if( objectp(dest) && present(dest, environment(me))){
                me->set_leader(dest);
                me->kill_ob(dest);
                dest->fight_ob(me);
                checking(me, dest);
        }
        return 1;
}
 int ask_anqi()
{
         object obj, me = this_player();
        if(me->query_skill("jinshe-jianfa",1) <200 )
                  return 1;
        if( query_temp(QUESTDIR+"����", me) >= 3){
         command("say �Ҳ����Ѿ���������");
            return 1; 
            }
       obj= new(BINGQI_D("throwing/jinshe-zhui"));
       obj->move(me);
        message_vision("$N��$nһЩ"+obj->name()+NOR"��\n",this_object(),me);
          addn_temp(QUESTDIR+"����", 1, me);
         command("say �ú��ˣ������׶�����ҵĶ��Ű�������ҪС��ʹ�á�");
           return 1; 
 }


int ask_weapon()
{
        object obj, me = this_player();

//        if (!me->query(QUESTDIR+"pass")) {
       if( !query(QUESTDIR+"over", me)){
          command("heng");
            return 1; 
           }

        if( query_temp(QUESTDIR+"����׶", me)){
          command("say �Ҳ����Ѿ���������");
            return 1; 
            }
       obj= new("/d/huashan/jinshe/obj/jinshe-zhui");
       set("owner",query("id",  me), obj);
       set("no_drop", 1, obj);
       set("no_give", 1, obj);
       obj->move(me);
       message_vision("$N��$nһЩ"+obj->name()+NOR"��\n",this_object(),me);
          set_temp("quest/�����Ʒ�/start", 1, me);//�����Ʒ���ʼ���ƾ�˿���������ѯ��
          addn_temp(QUESTDIR+"����׶", 1, me);
          command("say �����׶�����ҵĶ��Ű������Դ�Ϊ������ȥ�¼ұ���������Ҫ�������ı��");
            return 1; 
}


int ask_fuchou() 
{
        object me = this_player();

        if(me->query_skill("jinshe-jianfa",1) <200 )
                   return 1;

        if(me->query_condition("killer"))
         {
           command("fear"+query("id", me));
           command("say С�Ĺٸ�ͨ����");
           return 1;
        }

        if( query_temp(QUESTDIR+"start", me) )
  {
          command("shake"+query("id", me));
          command("say �㲻��˵Ҫ���Ҹ��������ô�������");
          return 1;
  } 
        if( query(QUESTDIR+"over", me) )
  {
          command("thank"+query("id", me));
          command("say ���Ѿ�ɱ���¼����ϰ��Ҹ����ˣ�����̫��л�ˣ�");
          return 1;
  } 
  //��vip��ң�ֻ��ʧ������
  if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
  {
          command("shake"+query("id", me));
          command("say ����ʱ��������⸴������黹���Ժ���˵�ɡ�");
          return 1;
        }
        //��Ҫ���һ�죬������Ҫ���500k

        if( query(QUESTDIR+"start/time", me) && time()-query(QUESTDIR+"start/time", me)<86400 )
        {
          command("shake"+query("id", me));
          command("say ����������ɣ���ʲô����������˵�ɡ�");
          return 1;
  }
        if( query(QUESTDIR+"start/combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"start/combat_exp", me)<500000 )
        {
          command("look"+query("id", me));
          command("say ���㵱ǰ�ľ�����»������԰��Ҹ��𣬻���ץ��ȥ����ȥ�ɡ�");
          return 1;
  }
        
          command("look"+query("id", me));
          command("say �ðɣ���ȥ����ɱ���¼����ϣ��Ҷ�����л��");
          command("say ��ֻҪ���¼����ϵ��ϴ����𡰽����ɾ������ɡ�");

          set_temp(QUESTDIR+"start", 1, me);//��ʼ��־
         //��ǿ�ʼʱ��;���
         set(QUESTDIR+"start/time", time(), me);
         set(QUESTDIR+"start/combat_exp",query("combat_exp",  me), me);
          return 1;
}

int ask_jinshe() 
{
        object me = this_player();      
        int exp, neili;
     
       //����书�ȼ�������250����
        if(me->query_skill("jinshe-jianfa",1) <250 )
                   return 1;
        if(me->query_skill("jinshe-zhangfa",1) <250 )
                   return 1;
          //����ɱ�����¼�����
        if( !query(QUESTDIR+"over", me) )
                   return 1;

        if(me->query_condition("killer"))
         {
           command("fear"+query("id", me));
           command("say С�Ĺٸ�ͨ����");
           return 1;
        }

  //��vip��ң�ֻ��ʧ������
  if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
  {
          command("shake"+query("id", me));
          command("say �Ҳ��Ƕ����������������˿������Լ��������ˡ�");
          return 1;
        }
        //�书ѧϰ֮����Ҫ���һ�죬������Ҫ���500k

        if( query(QUESTDIR+"time", me) && time()-query(QUESTDIR+"time", me)<86400 )
        {
          command("shake"+query("id", me));
          command("say ����������ɣ���ʲô����������˵�ɡ�");
          return 1;
  }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
          command("look"+query("id", me));
          command("say ���㵱ǰ�ľ�����»�����������Ҫ��������ץ��ȥ����ȥ�ɡ�");
          return 1;
  }
         exp=700+random(300);
         neili=20+random(30);
          command("look"+query("id", me));
          command("say ��Ȼ����ұ��˴���Ҿͽ��ҶԽ����ؼ����о��ĵø�����ɡ�");
         //����书��ʱ��ͱ�־
         set(QUESTDIR+"time", time(), me);
         set(QUESTDIR+"combat_exp",query("combat_exp",  me), me);
      if( random(query("kar", me))>22){
           set(QUESTDIR+"pass", 1, me);
         tell_object(me,HIG"\n��������ѩ�˵�ָ�㣬������������в���֮��һ�Ӳ��գ���ʱ��Ȼ��ͨ����Ȼ�������\n\n"NOR);
        tell_object(me,HIC"\n���Ŀڤ˼�����������š��������书�ذ£�����һ���γ���СϪ������������������\n"NOR);
        tell_object(me,HIC"��ɼ��ף����Ȱ�����ң�ֱ����ò��Ѿ�������һ���˼������ͨ���˽����ɾ���\n"NOR);
        tell_object(me,HIC"\n��ѧ�ؾ�����ʦ����������ϳ��书��Ҳ�и���һ����ᡣ\n"NOR);
          command("wa2"+query("id", me));
              tell_object(me,HBYEL"\n����"+NATURE_D->game_time()+"�õ���ѩ�˵�ָ�㣬��ѧ��Ϊ���������"+exp+"�㾭�齱����"+neili+"�����������\n"NOR);
                addn("combat_exp", exp, me);
                addn("max_neili", neili, me);
                me->set_skill("wudu-yanluobu", 1);
              log_file("quest/jinshequest",sprintf("%s(%s)ʧ��%d�κ�õ���ѩ�˵�ָ�㣬��ѧ��Ϊ������������%d�㾭�飬%d�����������\n",me->name(1),query("id", me),query("quest/���߽���/fail", me),exp,neili));

                  return 1;
            }
        tell_object(me,HIR"\n��˼ڤ�룬�����Լ���Ȼ�޷������ѩ�������ؾ���\n\n"NOR);
          command("sigh"+query("id", me));
           addn(QUESTDIR+"fail", 1, me);
       log_file("quest/jinshequest",sprintf("%s(%s)��%d������ѩ����̣�������Ȼ�޷�������о��ϡ�\n",me->name(1),query("id", me),query("quest/���߽���/fail", me)));

          return 1;
}
