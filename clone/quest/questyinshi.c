// /clone/quest/questyinshi.c
//// Last Modified by sir on 4.20.2002

#include <login.h>
#include <ansi.h>

inherit NPC;
inherit F_CLEAN_UP;
inherit F_UNIQUE;
int ask_me(object who);
string *msg_dunno = ({
        "$nҡҡͷ��˵����û��˵����\n",
        "$n�ɻ�ؿ���$N��ҡ��ҡͷ��\n",
        "$n�����۾�����$N����Ȼ��֪��$P��˵ʲô��\n",
        "$n�����ʼ磬�ܱ�Ǹ��˵���޿ɷ�档\n",
        "$n˵������....���ҿɲ��������������ʱ��˰ɡ�\n",
        "$n����һ�����˵�����Բ������ʵ�����ʵ��û��ӡ��\n"
});
string *reject_msg = ({
        "˵������̫�����ˣ�����ô�ҵ���\n",
        "�����ܳ�����һ����˵������̣�����ô�ҵ���\n",
        "Ц��˵��������Ц�ˣ��������С�������ʸ�ָ�㡹��ʲô��\n"
});
string * name_msg = ({
        "����",
        "����",
        "������ʿ",
        "��ҩ��",
        "��������",
        "�����",
        "����",
        "�Ҷ�",
        "��",
        "�ٱ�",
        "��������",
        "������",
        "��ؤ",
        "С��",
        "����",
        "����",
        "�Կ�",
        "�η�����",
        "�η�����",
        "��������",
});
string * long_id = ({
        "shu sheng",
        "ke shang",
        "wei shi",
        "caiyao ren",
        "jianghu yiren",
        "jinxiang ke",
        "tiao fu",
        "jia ding",
        "da han",
        "guan bing",
        "flower girl",
        "tangzi shou",
        "qi gai",
        "xiao fan",
        "dao ke",
        "jian ke",
        "chi ke",
        "seng ren",
        "dao ren",
        "jianghu haoke",
});

void create()
{
        int i;
        i = random(sizeof(name_msg));
        set_name(name_msg[i], ({ long_id[i]}) );
        set("gender", random(2)>0 ? "Ů��" : "����" );
        set("attitude", "friendly");
        set("chat_chance", 60);
        set("chat_msg", ({
          (:call_out,"random_move",0:),
                }) );
        set("inquiry", ([
                "��ʿ"    : (: ask_me :),
                "����"    : (: ask_me :),
                "yinshi" : (: ask_me :),
                "guiyin"  : (: ask_me :),
        ]) );
        set("no_steal", 1);
        set("ask_time",0);
        set("yinshi", 1 );
        set("owner","mud_os");
        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
        carry_object("/clone/food/jiudai");
}
                        
int ask_me(object who)
{
        object ob = this_object(), me = this_player();
        mapping map_status, skill_status,hp_status,skl;
        string *sname,*mname;
        string *skillname;
        int i,j,skilllvl,topexp;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg =({});

        if( query("ask_time", ob)<2 )
          {
            message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
            addn("ask_time", 1, ob);
           }
           
        else if( query("ask_time", ob) == 2 )
           {
            message_vision(HIC"$N���к���һ���������ֱ��ĮȻ�ˣ�ֻ����ֵؿ���$n��\n"NOR, ob, me);
            set("owner",query("id",  me), ob);
            addn("ask_time", 1, ob);
           }   

        else if( query("ask_time", ob) == 3 && query("family_name", ob) != query("family/family_name", me) )
        {
              hp_status = me->query_entire_dbase();              
        
              addn("ask_time", 1, ob);
              set("str", hp_status["str"], ob);
              set("int", hp_status["int"], ob);
              set("con", hp_status["con"], ob);
              set("dex", hp_status["dex"]+10, ob);
              set("age", hp_status["age"]+2, ob);

              set("max_jing", hp_status["max_jing"]*3/2, ob);
              set("eff_jing", hp_status["max_jing"]*3/2, ob);
              set("jing", hp_status["jing"]*3/2, ob);
              if ((hp_status["max_qi"]*2)<1500)
                { 
                  set("max_qi", 1500, ob);
                  set("eff_qi", 1500, ob);
                  set("qi", 1500, ob);
                 }  
              else                
                {
                  set("max_qi", hp_status["max_qi"]*2, ob);
                  set("eff_qi", hp_status["max_qi"]*2, ob);
                  set("qi", hp_status["max_qi"]*2, ob);
                 }
              if ((hp_status["max_neili"])<1500)
                 {
                   set("max_neili", 1500, ob);
                   set("neili", 1500, ob);
                   set("jiali", 50, ob);
                  }
              else 
                 { 
                  set("max_neili", hp_status["max_neili"], ob);
                  set("neili", hp_status["max_neili"], ob);
                  set("jiali", hp_status["max_neili"]/30, ob);
                 }
              topexp=query("combat_exp", me);
              set("combat_exp", topexp*3/2+100, ob);
              set("no_check", 1, ob);
              skl = me->query_skills();
              skilllvl=200;        
              if (sizeof(skl))
              {
                skillname = sort_array( keys(skl), (: strcmp :) );
                for (j=0; j<sizeof(skl); j++)
                {
                        if (skilllvl < skl[skillname[j]])
                                skilllvl = skl[skillname[j]];
                }                                
              }
              if (skilllvl>=300)  skilllvl=skilllvl*5/6;
              skill_status = ob->query_skills();
              sname = keys(skill_status);
              for(i=0; i<sizeof(skill_status); i++)
                {
                        ob->set_skill(sname[i], skilllvl);
                }
                
                message_vision(HIC"$N̾�˿�����˵���������ѹ������꣬��ȴ��Ҫ�����ƣ���\n"NOR, ob, me);       
                message_vision(HIY"$N����ͻȻ����һ�����⣬��ŭ�ص���$n�������ȵ���"+RANK_D->query_self_rude(ob)+"����"+query("fname", ob)+"��"+RANK_D->query_rude(me)+"���������ɣ�\n"NOR,ob,me);
                me->start_busy(1);      
                addn_temp("apply/dodge", 150, ob);
                addn("yinshi", 1, ob);
                set("title",query("family_name",  ob)+"��ʿ", ob);
                set("name",query("fname",  ob), ob);
                if ( mapp(map_status = ob->query_skill_map()) )
                {
                        mname  = keys(map_status);
                        for(i=0; i<sizeof(map_status); i++) 
                     {
                                perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
                                for ( j = 0; j < sizeof( perform_actions ); j++ )
                                {
                                        sscanf( perform_actions[j], "%s.c", perform_actions[j] );
                                        if ( mname[i] == "force" )
                                                msg = ({ (: exert_function, perform_actions[j] :) });
                                        else
                                                msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
                                        combat_actions += msg;
                                }
                        }
                }
                set( "chat_chance_combat", 60);         
                set( "chat_msg_combat", combat_actions );               
                fight_ob(me);
                addn("ask_time", 1, ob);

        }
        else if( query("ask_time", ob) >= 3 && query("family_name", ob) == query("family/family_name", me )
                 && query("owner", ob) == query("id", me) )
                message_vision(HIG"$N̾�˿���������$nЦ������ԭ����ͬ�ź󱲣�����ô��������ң���Ϊ���£�����\n"NOR, ob, me);
        else message_vision(HIG"$N̾�˿���������$n��Ц����������ô��������ң���Ϊ���£�����\n"NOR, ob, me);
        return 1;
}

int random_move()
{
        mapping exits;
        string *dirs, dir, dest;

        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys(exits);
        dir = dirs[random(sizeof(dirs))];
        dest = exits[dir];
        if( query("no_fight", find_object(dest)))return 0;
        if( this_object()->is_fighting() ) return 0;
        command("go " + dir);
        return 1;
}

void init()
{
         add_action("do_hit","hit");
         add_action("do_hit","kill");    
         add_action("do_hit","touxi");
         add_action("do_hit","ansuan");
         add_action("do_hit","steal");   
         add_action("do_halt","halt");
         add_action("do_halt","go");
         add_action("do_halt","surrender");
         add_action("do_qingjiao","qingjiao");
         add_action("do_look","look");
}
int do_look(string arg)
{
        object ob = this_object();
        object me = this_player();
        if( !arg || arg != query("id", ob) )
                return 0;

        if( query("yinshi", ob) == 1 )
         {
          message_vision("���뿴��Է������ӣ���ȴ��ôҲ�޷�������\n",me);
          return 1;        
         }
        else return 0;

}
int do_qingjiao(string arg)
{  
     object ob = this_object(), me =this_player();
     string special;
     int bl,sl,i;
   
      if (!living(me)||!living(ob)) return 0;
      if (me->is_busy() || me->is_fighting())
                 return notify_fail("����æ���ء�\n");
      if (ob->is_fighting())
          return notify_fail("�Է���æ���ء�\n");
      if( query("ask_time", ob)<3 )
          {
            message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);           
           }
      else if( query("owner", ob) != query("id", me )
              || query("family_name", ob) != query("family/family_name", me) )
          {
             return  notify_fail( ob ->name() + reject_msg[random(sizeof(reject_msg))] );
          }   
      else{     
           if (!arg) return notify_fail("��Ҫ���ʲô��\n");
           if (!(special=me->query_skill_mapped(arg)))
                return notify_fail("��ֻ�ܴ����⼼������̻������ܡ�\n");
           bl=me->query_skill(arg,1);
           sl=me->query_skill(special,1);
           i=random(10);
           message_vision(HIG"$N����Ц���������Ҽ���ͬ�ţ��������Ҳ����Ե���ð��Ҿ͸�����Щ�����书�ĵã�����\n"NOR, ob, me);
           if( i<3 )
           { 
             write(HIM"������ָ�����˼���룬��"+to_chinese(arg)+"�����������һ�㡣\n"NOR);
             me->set_skill(arg,bl+1);
            }
           else 
           { 
             write(HIR"������ָ�����˼���룬��"+to_chinese(special)+"�����������һ�㡣\n"NOR);
             me->set_skill(special,sl+1);
            }
           addn("score", 1000+random(500), me);
           me->start_busy(1);
           message_vision(HIG"$N̾�˿�����˵����������������Ե�������Ի��پۣ�ʱ�����ˣ�������һ��!����\n"NOR, ob, me);
           destruct(ob);
        }
} 
           
int do_hit(string arg)
{
        object ob = this_object();
        object me = this_player();
        mapping map_status;
        string* mname;
        int i,j;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg =({});
        if( !arg || arg != query("id", ob) )
                return 0;
         
        //if (!ob->query("owner"))
        if( (query("id", me) == query("owner", ob)) && (query("ask_time", ob) == 3) )
             return notify_fail("������ԩ�޳��������Ǻα��أ�\n");
 
       else if( query("ask_time", ob)>3 && query("family_name", ob) == query("family/family_name", me )
            && query("owner", ob) == query("id", me) )
           return notify_fail("���Ȼ���ҵ�����ǰ���������ô˴�û����ֽ��书��\n");
           
        else if( query("ask_time", ob)>3 )
        {
                if ( mapp(map_status = ob->query_skill_map()) )
                {
                        mname  = keys(map_status);
        
                        for(i=0; i<sizeof(map_status); i++) 
                      {
                                perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
                                for ( j = 0; j < sizeof( perform_actions ); j++ )
                                {
                                        sscanf( perform_actions[j], "%s.c", perform_actions[j] );
                                        if ( mname[i] == "force" )
                                                msg = ({ (: exert_function, perform_actions[j] :) });
                                        else
                                                msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
                                        combat_actions += msg;
                                }
                        }
                }
                set("chat_chance_combat", 60, ob);
                set("chat_msg_combat", combat_actions, ob);
                if( query("combat_exp", me)>query("combat_exp", ob) )
                  set("combat_exp",query("combat_exp",  me), ob);
                kill_ob(me);    
        }
}

int do_halt()
{
        object me = this_player();
        object ob = this_object();
        
        if( me->is_fighting(ob) && query("ask_time", ob) >= 3 )
        {
                message_vision(HIW"$N�ȵ��������Ȼʶ���ҵ���ݣ�����������뿪����\n"NOR, ob, me);
                return 1;
        }
        return 0;
}
void die()
{
        object ob = this_object();
        object me,fme;
        int pot,exp,score;
        me = query_temp("last_damage_from");
        fme=query_temp("last_opponent");          
  
         if( fme && 
             query("ask_time", ob)>3 && query("owner", ob) == query("id", me )
              && query("owner", ob) == query("id", fme )
              && query("family_name", ob) != query("family/family_name", me) )
            {
              pot = 400+random(400);
              exp = 1500+random(500);
              score =300+random(50);
              addn("combat_exp", exp, me);
              addn("potential", pot, me);
              addn("score", score, me);
              tell_object(me,HIW"����Ѱ�ù����еõ����½�����\n");
              tell_object(me,chinese_number(exp) +"��ʵս����\n" +
              chinese_number(pot) + "��Ǳ��\n" +
              chinese_number(score)+"�㽭������\n"NOR);
              }
         ::die();    
}