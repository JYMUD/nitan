//Cracked by Kafei
// /d/city/npc/obj/biaoche.c �ڳ�
// sdong,12/05/98 created

#include <ansi.h>
#include <room.h>
inherit ITEM;

string *Robber_Name = ({
                                         "����","ɽ����","·��","ɽ��","ë��","կ��","���"

});





mapping default_dirs = ([
                  "north":        "��",
                  "south":        "��",
                  "east":         "��",
                  "west":         "��",
                  "northup":      "����",
                  "southup":      "�ϱ�",
                  "eastup":       "����",
                  "westup":       "����",
                  "northdown":    "����",
                  "southdown":    "�ϱ�",
                  "eastdown":     "����",
                  "westdown":     "����",
                  "northeast":    "����",
                  "northwest":    "����",
                  "southeast":    "����",
                  "southwest":    "����",
                  "up":           "��",
                  "down":         "��",
                  "out":          "��",
                  "enter":        "��",
]);



void set_owner(object owner,object owner2);
int do_drive(string arg);
int do_open();
int do_check();
int do_unride(string arg);
int do_ride(string arg);
int do_attack(string arg);
int do_rob();
void host_appear();
void destroy_cart(object cart);
void greeting(object ob);
void destroy_it(object ob);
void do_leave(object ob);
void robber_rob(object me);

void create()
{
        seteuid(getuid());
        set_name(HIW"�ڳ�"NOR, ({"biao che", "che"}));
        set("long",
                "����һ���ǳ���ʵ���ڳ�������ƥ���������ţ���֪װ��ʲô�������ڳ�������һ����죬���顰�����ھ֡��ĸ����֡�\n");
        set("unit", "��");
        set_weight(10000);
        set_max_encumbrance(5000);

        set("value", 1000000);
        set("material", "steel");

        set("no_get",1);

        set("no_refresh", 1);

        remove_call_out("auto_check");
        call_out("auto_check", 30+random(30) );
}

void init()
{
        object ob;

        add_action("do_check", "check");
        add_action("do_drive", "gan");
        add_action("do_drive", "g");
        add_action("do_ride", "ride");
        add_action("do_ride", "shang");
        add_action("do_unride", "leave");
        add_action("do_attack", "attack");
        add_action("do_attack", "att");
        add_action("do_rob", "jiebiao");

        if( interactive(ob = this_player()) ) {
                 call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        int bonus,old_pot;

        object target,robber;
        object here = environment(this_object());
        object owner;
        string sO;

        if( !ob || environment(ob) != environment() ) return;


        sO = query("owner");

        if(sO)
         owner = present( sO,here);

        if( !owner || owner != ob )
        {
                sO = query("owner2");

                if(sO)
                 owner = present( sO,here);
        }

        if( !owner || owner != ob)return;


        if( !owner && here && (robber = present("robber",here)) )
        {
                robber->command("open");
        }
        else if( query_temp("biao/dest2") && here && (base_name(here) == query_temp("biao/dest2") )&& owner && userp( owner ) )
        {
                message_vision(HIG"\n$N"+HIG"�۵ð���������ϵ�Ŀ�ĵأ�\n\n",owner);

                if( (target = present( query_temp("biao/dest"),here)  ) )
                {
                        call_out("award",1,target,ob );
                }
                else
                {
                        message_vision(RED"����$N"+RED"ȴ�Ҳ������ˣ���$P����ֱð����\n\n"NOR,owner);
                        remove_call_out("host_appear");
                        call_out("host_appear", 2 + random(3) );
                }
        }
        else if( query_temp("biao/dest") && here && (target = present( query_temp("biao/dest"),here)  ) )
        {
                        message_vision("$N����ææ�뿪�ˣ�\n",target);
                        target->move( query_temp("biao/dest2")+".c" );
                        message_vision("$N����ææ���˹�����\n",target);
        }
}

void host_appear()
{
        object target;
        string host = query_temp("biao/dest");

        if(!host)return;

        target = find_object( host );
        if(!target)target = find_player(host);
        if(!target )target = find_living(host);


        if( !target )
        {
                seteuid(geteuid());
                if ( query_temp("biao/dest") == "dao baifeng" ) target = new ("/kungfu/class/dali/daobaifeng.c");
                else if ( query_temp("biao/dest") == "hu laoye" ) target = new ("/d/xingxiu/npc/bayi.c");
                else if ( query_temp("biao/dest") == "ye erniang" ) target = new ("/kungfu/class/xixia/ye.c");
                else if ( query_temp("biao/dest") == "feng yiming" ) target = new ("/d/foshan/npc/yiming.c");
                else if ( query_temp("biao/dest") == "wang tongzhi" ) target = new ("/d/quanzhou/npc/wang.c");
        }
        else
        {
                if( target && environment( target) )
                        message_vision("$N����ææ�뿪�ˣ�\n",target);
        }

        if(target)
        {
                target->move( query_temp("biao/dest2")+".c" );
                message_vision("$N����ææ���˹�����\n",target);
        }

}

void award2(object dest,object owner)
{
        object wage;
        object here = environment(dest);
        int nGold;

        if( userp(owner) && query("biao/dest2", owner) )
        {
                nGold=2+random(2+query("combat_exp", owner)/100000);

                if (MONEY_D->player_job_pay(owner, dest, nGold * 10000))
                        message_vision(HIY"$N"+HIY"�ݸ�$n�����ƽ�˵����һ��С��˼��"+RANK_D->query_respect(owner)+"��Ц�ɣ���\n"NOR,dest,owner);

                delete("biao/dest", owner);
                delete("biao/dest2", owner);
                delete_temp("riding", owner);
                set("biao/bonus", 660+random(500), owner);
        }
}

void award(object dest,object owner)
{
        object *obj,here = environment(dest);
        object cart=this_object();
        int i;

        if(userp(owner))
        {
                message_vision(HIY"$N"+HIY"�������ڳ���\n"NOR,owner);
                delete_temp("riding", owner);
                message_vision("$N��ǰ����$n��ȭ��������λ"+RANK_D->query_respect(dest)+"���ˡ�"+RANK_D->query_self(owner)+"���㲻�����У��ֽ��ڻ�ԭ����ϡ�������㣡��\n",owner,dest);
                message_vision("$N������Ц��˵������λ�����ھֵ�"+RANK_D->query_respect(owner)+"��ȻӢ���˵á�"+RANK_D->query_self(dest)+"��л�ˣ���\n",dest);
                call_out("award2",1,dest,owner);
                remove_call_out("killer_show");
                remove_call_out("auto_check");
                if(owner->query_condition("biaoju"))
                        owner->clear_one_condition("biaoju");


                obj = all_inventory(here);

                 for(i=0;i<sizeof(obj);i++)
                {

                        if( living(obj[i]) && (query_temp("biao/owner", obj[i]) == query("id", owner )

                                 || query_temp("biao/owner2", obj[i]) == query("id", owner) )

                         && obj[i] != owner )

                        {

                                call_out("destroy_cart",2,obj[i]);

                        }

                        if( query("id", obj[i]) == "robber" && !userp(obj[i]) )

                                do_leave(obj[i]);

                }



                call_out("destroy_cart",5,cart);

        }

}

void destroy_cart(object cart)
{
        if( !objectp(cart) )return;
        if( query("race", cart) != "����" )
                message_vision("������ǰ��$N�����ˡ�\n",cart);
        else message_vision("Ѿ����ǰ��$N���ȥ�ˡ�\n",cart);

        destruct(cart);
}

void set_owner(object owner,object owner2)
{
        object ob = this_object();
        set("owner",query("id", owner));
        if(owner2)
                set("owner2",query("id", owner2));
        set_temp("biao/dest",query("biao/dest", owner));
        set_temp("biao/dest2",query("biao/dest2", owner));

        call_out("destroy_it", 1200,ob);
}



int do_ride(string arg)
{
        object me = this_player();
        object cart = this_object();


        if (!arg) return notify_fail("��Ҫ��ʲô��\n");

        if( query_temp("riding", me))return notify_fail("���Ѿ����ڳ��ϣ�\n");

        if( cart = present("biao che",environment()) );

        if( query("owner") != query("id", me) && query("owner2") != query("id", me))return notify_fail("������ĳ���\n");

        message_vision(HIY"$N"+HIY"�������������ڳ���һ��������ӣ�һ����ס������ߺ����������\n"NOR,me);
        me->set_leader( cart );
        set_temp("riding", 1, me);
        return 1;
}

int do_unride(string arg)
{
        object me = this_player();

        if( !query_temp("riding", me))return notify_fail("���Ѿ������ڳ��ϣ�\n");

        message_vision(HIY"$N"+HIY"�������ڳ���\n"NOR,me);
        delete_temp("riding", me);
        return 1;
}



int auto_check()
{
        object me = this_object();
        object here,owner;
        if( !me )return 0;
        here = environment(me);
        if(!here) return 0;
        call_out("auto_check", 45+random(30) );

        //if( !(owner = present(query("owner"),here) ) && query("owner2") && !(owner = present(query("owner2"),here) )  )
                if( !(owner = find_player(query("owner")) ) &&  query("owner2") && !(owner = find_player(query("owner2")) ) )
                {
                        call_out("auto_check", 1+random(3) );
                        call_out( "destroy_it",1, me );
                        return 1;
                }


  if( !owner || !query("biao/dest2", owner) )
  {
                call_out( "destroy_me",1, me );
                return 0;
  }


        if( strsrch(base_name(here), "/d/city") == -1 &&
                strsrch(base_name(here), "/d/") != -1 &&
                strsrch(base_name(here), "duchuan") == -1   )
        {
                                call_out( "killer_show",1+random(5),owner );
                                if( query("owner2") && query("owner2") != query("owner") )
                                {
                                        owner = find_player( query("owner2") );
                                        if( owner && random(2) ==0 ) call_out( "killer_show",1+random(5),owner );
                                }
        }

        return 1;
}


void do_leave(object ob)
{
                if( objectp(ob) )
                {
                        if( ob->is_busy() || ob->is_fighting())
                        {
                                message_vision("$N���һ��������սȦ��\n",ob);
                                if( random(2)==0 )
                                        message_vision("$N˵����û�뵽�����ھֵĻ����������ӡ�"+RANK_D->query_self(ob)+"������������һ��������\n",ob);
                                else
                                        message_vision("$N˵�������������������ã�����ݣ��������������棡\n",ob);
                        }

                        if(!living(ob))ob->revive(0);
                        message_vision("$N����ææ�뿪�ˡ�\n",ob);
                        destruct(ob);
                }
}



void run_away()

{
        object obj, ob=this_object(), me,partner;

        object here = environment(ob);

        string *dirs,dir,dest,target_dir;

        mapping exit;



        if(!ob)return;

        if(!here || !objectp(here) )return;



        if(random(16) != 0) call_out("run_away",0);



        exit=query("exits", here);

        if( !exit ) return;

        dirs = keys(exit);

        dir = dirs[random(sizeof(dirs))];

        if(!dir)return;

        dest = exit[dir];

        if( !dest )return;



        if( !(obj = find_object(dest)) )

                call_other(dest, "???");

        if( !(obj = find_object(dest)) )

                return;

        if( !wizardp(ob) && query("short", obj) == "��ʦ��Ϣ��" )

                return;



        if( query("short", obj) == "��ɳĮ" || query("short", obj) == "ɳĮ" || query("short", obj) == "��ͤ" )

                return;



        if( !undefinedp(default_dirs[dir]) )

                                         target_dir = default_dirs[dir];

                  else

                                         target_dir = dir;



        message( "vision", HIY"�����ܾ������㷢�������������ڳ����ܡ�\n"NOR,environment(ob), ({ob}));



        if( ob->move(obj) ) {

                        message( "vision", HIY "ֻ��һ��"

                                +ob->name()+HIY"��¡¡���ص�ʻ�˹�����\n" NOR, environment(ob), ({ob}));



                        if( query("owner", ob) )

                        {

                                if( (me=present(query("owner", ob),here)) && query_temp("riding", me) )

                                {

                                        me->move(obj);

                                        all_inventory(here)->follow_me(me,dir);

                                }

                        }



                        if( query("owner2", ob) )

                        {

                                 if( (partner=present(query("owner2", ob),here)) && query_temp("riding", partner) )

                                 {

                                        partner->move(obj);

                                        all_inventory(here)->follow_me(partner,dir);

                                 }

                        }

        }



}


void action(object me, object ob)
{
        object here = environment();


        if( !ob || !objectp(ob) )return;

        if( !(me=present( query("owner"), here ) ) )
        {
                if( query("owner2") )
                {
                  if( !(me=present( query("owner2"), here )) )
                        {
                                if( here == environment(ob) )
                                {
                                        robber_rob(ob);
                                        return;
                                }
                        }
                } else
                {
                        if( here == environment(ob) )
                        {
                                 robber_rob(ob);
                                 return;
                        }
                }
        }


        if( !living(ob) )
        {
                 call_out("action",random(10),me,ob);
                 return;
        }

        if( !ob->is_busy() && !ob->is_fighting() )
        {
          if(random(3)) message_vision(HIR"\n$N"+HIR"�ȵ������������ԣ���·���ҿ���Ҫ�Ӵ˴�����������·Ǯ����õģ�ʶȤ�㽻��������������һ��������\n"NOR, ob);

          else if( random(3) ) message_vision(HIR"\n$N"+HIR"�ȵ���"+RANK_D->query_self(ob)+"������ȱ����Ǯ������õģ��Ͽ콻������������������һ��ȫʬ��\n"NOR, ob);
          else message_vision(HIR"\n$N"+HIR"�ȵ���"+RANK_D->query_self(ob)+"�������е����ٸ���ƶ�������ӣ�ʶȤ�㽻�������������㲻����\n"NOR, ob);
          ob->kill_ob(me);
        }



        if( random(60) == 1 )

        {

          message_vision(HIR"\n$N"+HIR"ͻȻ����һ�ţ���������ȥ����������������ӵ�ƨ���ϡ�\n"NOR, ob);

          call_out("run_away",0);

        }

        call_out("action",random(10),me,ob);
}

void robber_rob(object me)
{
        object here, target;

        if(random(3)) message_vision(HIR"\n$N"+HIR"�ȵ������������ԣ���·���ҿ���Ҫ�Ӵ˴�����������·Ǯ����õģ�ʶȤ�㽻��������������һ��������\n"NOR, me);
        else if( random(3) ) message_vision(HIR"\n$N"+HIR"�ȵ���"+RANK_D->query_self(me)+"������ȱ����Ǯ������õģ��Ͽ콻������������������һ��ȫʬ��\n"NOR, me);
        else message_vision(HIR"\n$N"+HIR"�ȵ���"+RANK_D->query_self(me)+"�������е����ٸ���ƶ�������ӣ�ʶȤ�㽻�������������㲻����\n"NOR, me);

        target = find_player( query("owner") );
        remove_call_out("destroy_it");

        message_vision(HIY"$N���ڳ���ȡ��һ����ڻ���\n",me);

        if(target)

        {

                         target->remove_all_killer();

                         target->remove_enemy(me);

                         CHANNEL_D->do_channel(this_object(), "rumor","��˵"+me->name()+"ϴ����"+target->name()+"���ڳ���" );

                         delete("biao", target);

                         target->set("biao/fail");

        }

        else

         CHANNEL_D->do_channel(this_object(), "rumor","��˵"+me->name()+"ϴ����"+ query("owner")+"���ڳ���" );

  call_out("do_leave",1,me);
  call_out("destroy_me",3,this_object() );
  return ;

}



private int is_suitable(object victim, object killer)
{
                  string *no_kill_list = ({

                                         "mu ren",

                                         "huang zhen",

                                         "juexin dashi",

                                         "fighter dummy",

                                         "xie yanke",

                                         "ren woxing",

                                         "zuo lengchan",

                                         "ouyang zhan",

                                         "seng bing",

                                         "ding chunqiu",

                                         "ouyang feng",

                                         "ye erniang",

                                         "ouyang ke",

                                         "jiumozhi",

                                         "mengmian ren",

                                         "black gargoyle",

                                         "white gargoyle",

                                         "zhen xibei",

                                         "xie xun",

                                         "biao shi",

                                         "bangzhong",

                                         "yin li",

                                         "lao denuo",

                                         "robber",

                                         "yue buqun",

                                         "mao zei",

                                          "zhou zhiruo",

                                        "jinlun fawang",
                                        
                                        "sangtu gong",
                                        "dongfang bubai",
                  });



                  if(  !victim || !clonep(victim) || !living(victim) || userp(victim)

                         || query("race", victim) != "����"

                         || query("shen", victim) >= 0

                         || query("winner", victim )

                        || strsrch(base_name(victim), "/kunfu/skill/") != -1

                        || strsrch(base_name(victim), "/clone/") != -1

                        || strsrch(base_name(victim), "/u/") != -1

                        || strsrch(base_name(victim), "/d/xiakedao/") != -1

                         || query("combat_exp", victim)<query("combat_exp", killer)*1/10

                         || query("combat_exp", victim)>query("combat_exp", killer)*7/4

                         || query("family/family_name", victim) == query("family/family_name", killer )

                         || query("family/family_name", victim) == "�һ���"

                         || member_array(query("id", victim),no_kill_list) != -1 || random(2) == 0 )

                  {

                                         return 0;

                  }

                  return 1;

}

void setup_skill(object me,object obj)
{
        mapping skills;
        string *names;
        int level,i;

        if(!objectp(me) || !objectp(obj) )return;


        if( query("combat_exp", obj)<query("combat_exp", me) )

        {

                set("combat_exp",query("combat_exp",  me)/100*(100+random(80)), obj);

        }



        level=pow(query("combat_exp", obj)*10.,0.33333);

        if(level < 10) level = 10;



        if( query("combat_exp", obj)<300000 )

        {

                level = level/2 + random(level*2/3);

        }

        else if( query("combat_exp", obj)<500000 )

        {

                level = level/2 + random(level/2);

        }

        else if( query("combat_exp", obj)<800000 )

        {

                level = level/2 + random(level/3);

        }

        else if( query("combat_exp", obj)<2000000 )

        {

                level = level/2 + random(level/3);

        }
        else
                level = level/2  + random(level*2/3);

        if( query("family/family_name", me) == "������")//theirqishort,solowerrobber'sskillabit

        {

                level = level*2/3 ;

        }

        
        skills = obj->query_skills();

        names = keys(skills);

        for (i=0; i<sizeof(names); i++) {
          obj->set_skill(names[i], level);
        }

        delete("title", obj);
        delete("nickname", obj);
        delete("long", obj);
        delete("family", obj);
        delete("name", obj);
        delete("short", obj);
        obj->set_name(Robber_Name[random(7)], ({ "robber", "zei" }));
        set("owner",query("id",  me), obj);
        set_temp("biao/dest",query("biao/dest",  me), obj);

        if( query("owner2") )
                set("owner2", query("owner2"), obj);

        call_out("do_leave",20+random(15),obj);

}

void killer_show(object me)
{
  object ob,here,owner;
  object *target_list;

  int i;

  if( !me || !(here=environment()) || strsrch(base_name(here),"/d/") == -1 || query("no_fight", here) )
  {

                if( query("owner2") )

                {
                        owner = find_player( query("owner2") );
                        if( owner ) call_out( "killer_show",1,owner );
                }
                return;

 }


  if( !query("biao", me) )

  {

                call_out( "destroy_me",1, this_object() );

                return;

  }



  target_list = filter_array(livings(), "is_suitable", this_object(), me);

  if( sizeof(target_list) == 0 ) {

                  // try again in 5 secs.

                 call_out("killer_show", 5, me);

                 return;

  }

  do
  {
          i = random(sizeof(target_list));
          if( !environment(target_list[i]) )
                {
                        destruct(target_list[i]);
                        continue;
                }
          if( !target_list[i] || !objectp(target_list[i]) )continue;
          ob=new( base_name(target_list[i]) + ".c" );

  }
  while( !ob || !living(ob) );



  ob->move(here);
  setup_skill(me,ob);
  message_vision("\n$NͻȻ���˳���!\n", ob);

  ob->set_leader(me);
  call_out("action",random(3),me,ob);

  if( random(3) == 1)
  {
          remove_call_out("killer_show");
          call_out( "killer_show",1+random(2),me );
  }
}


int do_attack(string arg)
{
        object here, *obj, me = this_player(),target;
        string victim;
        int i;

        if (!arg) return notify_fail("��Ҫ����˭��\n");

        victim = arg;
        if( victim == query("id", me))return notify_fail("�㷢������\n");
        here = environment(me);

        target = present(victim, here);
        if (!target) return notify_fail("���ﲢ�޴��ˣ�\n");

        if( query("race", target) != "����" )
        {
                return notify_fail("�㷢������\n");
        }

        obj = all_inventory(here);

        message_vision(HIR "$N����$n"+HIR"�ȵ���"+RANK_D->query_rude(target)+HIR"Ҳ����ڣ������ǣ����Һݺݵؽ�ѵ$p��\n\n" NOR, me, target);

        if( query("biao/dest", me) )
        {
                for(i=0;i<sizeof(obj);i++)
                {

                        if( living(obj[i]) &&

                                (query("biao/dest", obj[i]) == query("biao/dest", me )

                                         || query_temp("biao/owner", obj[i]) == query("id", me )

                                         || query_temp("biao/owner2", obj[i]) == query("id", me )

                                ) && obj[i] != me && query("id", obj[i]) != "robber" && query("id", target) != query("id", obj[i]) )

                        {

                                if( query("combat_exp", obj[i])<query("combat_exp", target) )

                                {

                                        message_vision(HIY "ֻ��$NӦ������$n���˹�ȥ���ȵ���"+RANK_D->query_rude(target)+HIY"�������ɣ�\n" NOR, obj[i], target);

                                        obj[i]->kill_ob(target);

                                }

                                else

                                {

                                        message_vision(HIG "ֻ��$N����$n��м�غ���һ���������֪��ߵغ��"+RANK_D->query_rude(target)+HIG"�ͽ�������ȥ��ʰ�ˣ�\n" NOR, obj[i], target);

                                }

                        }

                }

        }



        if( living(target) )

        {

                if(random(2)==0)

                        message_vision( HIR "\n$N����$n"+HIR"��Цһ���������ӱ���ȫ�ϣ������кξ壬���У�\n\n" NOR, target,me );
                else message_vision( HIR "\n$N����$n"+HIR"��Цһ�������ж�Ϊʤ�����У�\n\n" NOR, target,me );
                target->kill_ob(me);
        }

        return 1;
}


int do_check()
{
        object ppl = this_player();
        object obj = this_object();

        if( query_temp("biao/dest", obj) == "daobaifeng")write("������"+query("owner", obj)+"ѹ�˵Ĵ����������׷���ڻ���\n");
        else if( query_temp("biao/dest", obj) == "hulaoye")write("������"+query("owner", obj)+"ѹ�˵ı���С��������͵����ڣ�Ҫ�����͵���\n");
        else if( query_temp("biao/dest", obj) == "yeerniang")write("��������Ҷ�������͵����ڣ���"+query("owner", obj)+"ѹ�ˣ�Ҫ�����͵���\n");
        else if( query_temp("biao/dest", obj) == "fengyiming")write("���Ƿ�ɽӢ�ۻ�ݷ�һ�������ڣ���"+query("owner", obj)+"ѹ�ˡ�\n");
        else if( query_temp("biao/dest", obj) == "wangtongzhi")write("����Ȫ�ݼ������ϵ�����ڣ���"+query("owner", obj)+"ѹ�ˣ���ؽ���ҩ���ƹ���ͨ�����\n");

        return 1;
}

void destroy_it( object obj)
{
        object ppl;
        if(!objectp(obj))return;

        remove_call_out("killer_show");
        remove_call_out("auto_check");

        if( !query("owner", obj) && !query("owner2", obj))return ;
        if( query("owner", obj))ppl=find_player(query("owner", obj));
        if( userp(ppl) )
        {
                delete_temp("apply/short", ppl);
                delete("biao", ppl);
                set("biao/fail", 1, ppl);
        }


        if( query("owner2", obj))ppl=find_player(query("owner2", obj));
        if( userp(ppl) )
        {
                delete_temp("apply/short", ppl);
                delete("biao", ppl);
                set("biao/fail", 1, ppl);
        }


        if( objectp(obj) )
        {
                if( userp(ppl) && query_temp("riding", ppl) )
                {
                        message_vision( HIR"����ͻȻ�����Ƶ�����$N"+HIR"���ܣ���$n"+HIR"һƨ��˦�ڵ��ϣ�ת�۾���ûӰ�ˡ���\n",obj,ppl);
                }
                else
                        message_vision( HIR"����ͻȻ�����Ƶ�����$N"+HIR"�ܣ�ת�۾���ûӰ�ˡ���\n",obj );
                destruct(obj);
        }
}

void destroy_me(object me)
{
  remove_call_out("killer_show");
  remove_call_out("auto_check");
  destruct(me);
}


int do_rob()
{
        object here, *obj, me = this_player(),target,biaohuo;
        int i,bGuarded = 0;

        here = environment(me);

        if(!here)return 1;

        if( !query("xbiao/owner", me) || 
                (query("owner") != query("xbiao/owner", me) && query("owner2") != query("xbiao/owner", me) || 
                  query_temp("biao/dest") != query("xbiao/dest", me )
                )
        )
                return notify_fail("û���ҽ��ڣ��������С����\n");

        obj = all_inventory(here);


        if(random(3)) message_vision(HIR"\n$N"+HIR"�ȵ������������ԣ���·���ҿ���Ҫ�Ӵ˴�����������·Ǯ����õģ�ʶȤ�㽻��������������һ��������\n"NOR, me);
        else if( random(3) ) message_vision(HIR"\n$N"+HIR"�ȵ���"+RANK_D->query_self(me)+"������ȱ����Ǯ������õģ��Ͽ콻������������������һ��ȫʬ��\n"NOR, me);
        else message_vision(HIR"\n$N"+HIR"�ȵ���"+RANK_D->query_self(me)+"�������е����ٸ���ƶ�������ӣ�ʶȤ�㽻�������������㲻����\n"NOR, me);

         for(i=0;i<sizeof(obj);i++)
         {

                        if( living(obj[i]) &&

                                        (query("id", obj[i]) == query("xbiao/owner", me )

                                                || ( query("owner2") && obj[i] == present( query("owner2"), here ) )

                                                 || query_temp("biao/owner", obj[i]) == query("xbiao/owner", me )

                                                 || query_temp("biao/owner2", obj[i]) == query("xbiao/owner", me )

                                        ) && obj[i] != me && query("id", obj[i]) != "robber"

                                )

                        {

                                obj[i]->kill_ob(me);

                                me->kill_ob(obj[i]);

                                bGuarded = 1;

                        }

         }



         target=find_player(query("xbiao/owner", me));



         if( !bGuarded )

         {

                 remove_call_out("destroy_it");

                 biaohuo = new ("/clone/npc/obj/biaohuo.c");

                 if(biaohuo)biaohuo->move(me);

                 message_vision(HIY"$N���ڳ���ȡ��һ����ڻ���\n",me);

                 set("owner",query("id",  me), biaohuo);

                 me->remove_all_killer();

                 delete("xbiao/owner", me);

                 if(target)

                 {

                         me->remove_enemy(target);

                         target->remove_all_killer();

                         target->remove_enemy(me);

                         CHANNEL_D->do_channel(this_object(), "rumor","��˵"+me->name()+"ϴ����"+target->name()+"���ڳ���" );

                         delete("biao", target);

                         target->set("biao/fail");

                 }

                 else

                         CHANNEL_D->do_channel(this_object(),"rumor","��˵"+me->name()+"ϴ����"+query("xbiao/owner", me)+"���ڳ���");
                 call_out("destroy_me",1,this_object() );
         }



        return 1;

}


int do_drive(string arg)
{
        object env, obj, ob, me = this_player(), partner;
        string target_dir, dir, dest, victim;
        mapping exit;
        object here = environment(me),robber = present("robber",here);
        int busy_time;

        if (!arg) return notify_fail("��Ҫ����ʲô��\n");

        if( sscanf(arg, "%s %s", victim, dir) != 2 ) return notify_fail("ָ�����\n");

        if( victim == query("id", me))return notify_fail("�αض��һ�٣�\n");

        if( !query_temp("riding", me))return notify_fail("���ֲ����ڳ��ϣ���ô�ϳ���\n");

        if ( victim != "che" && victim != "da che" ) return notify_fail("��Ҫ����ʲô��\n");

        ob = present(victim, environment(me));

        if (!ob) return notify_fail("���ﲢ�޴��ˣ�\n");

        if ( me->is_busy() ) return notify_fail("����æ���أ�\n");

        env = environment(me);
        if( !mapp(exit=query("exits", env)) || undefinedp(exit[dir]) )
                return notify_fail("�޴˷����ȥ��\n");

        dest = exit[dir];

        if( !(obj = find_object(dest)) )
                                         call_other(dest, "???");
                  if( !(obj = find_object(dest)) )
                                         return notify_fail("�޷��ߣ�\n");
        if( !wizardp(ob) && query("short", obj) == "��ʦ��Ϣ��" )
                return notify_fail("�޷��ߣ�\n");

        if( !undefinedp(default_dirs[dir]) )
                                         target_dir = default_dirs[dir];
                  else
                                         target_dir = dir;

        message_vision( HIG"$N"+HIG"��������ӣ������������Ӽ���$n"+HIG"��"+target_dir+"ʻȥ��\n" , me, ob);

        if( robber && (query("owner", robber) == query("id", me) || query("owner2", robber) == query("id", me)) )
        {
                message_vision( HIR"$N�ȵ������û�ţ�\n"NOR,robber);
                return 1;
        }

        if( query("owner", ob) != query("id", me) && query("owner2", ob) != query("id", me) )
        {
                message_vision( HIW"��������������$N��\n" NOR,me);
                return 1;
        }

        message("vision", HIY "ֻ��"+ob->name()+HIY"��¡¡���ص���"+target_dir+"ʻ��ȥ��\n" NOR, environment(ob), ({ob}));

        if( ob->move(obj) ) {
                        message( "vision", HIY "ֻ��һ��"+ob->name()+HIY"��¡¡���ص�ʻ�˹�����\n" NOR, environment(ob), ({ob}));

                        busy_time = 4 + random(4);

                        if( query("owner", ob) )
                        {
                                if( (me=present(query("owner", ob),env)) && query_temp("riding", me) )
                                {
                                        message_vision( HIG"$N�����ڳ�����"+target_dir+"ʻ��ȥ��\n" NOR,me);
                                        me->move(obj);
                                        message_vision( HIG"$N�����ڳ���ʻ������\n" NOR,me);
                                        me->start_busy( busy_time );
                                        all_inventory(env)->follow_me(me,dir);
                                }
                                else if( (me=present(query("owner", ob),environment(ob))) )
                                        me->start_busy( busy_time );
                        }

                        if( query("owner2", ob) )
                        {
                                 if( (partner=present(query("owner2", ob),env)) && query_temp("riding", partner) )
                                 {
                                        message_vision( HIG"$N�����ڳ�����"+target_dir+"ʻ��ȥ��\n" NOR,partner);
                                        partner->move(obj);
                                        message_vision( HIG"$N�����ڳ���ʻ������\n" NOR,partner);
                                        partner->start_busy( busy_time );
                                        all_inventory(env)->follow_me(partner,dir);
                                 }
                                 else if( (partner=present(query("owner2", ob),environment(ob))) )
                                {
                                        partner->start_busy( busy_time );
                                }
                        }
        }

        return 1;
}