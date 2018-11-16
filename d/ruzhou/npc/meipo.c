// NPC: /d/ruzhou/npc/meipo.c ֻ�����������
// llm 99/06/04 �޸�

#include <ansi.h>

inherit NPC;
//inherit F_CLEAN_UP;

int do_marry(string arg);
int waiting(object ob);
int do_name(string target);
int do_chase(object ob);
int do_ok(object ob);
int meipo_waiting(object ob,object me,object obj);
int ready_marry(object ob,object me,object obj);
int wait_marry(object ob,object me,object obj);
int start_marry(object ob,object me,object obj);
int do_back(object ob);
int do_bai(string arg);

void create()
{
        set_name("ý��", ({ "meipo","po" }) );
        set("title", HIM""NOR);
        set("gender", "Ů��" );
        set("age", 43);
        set("long",
                "һλ�����ܸɵ���ý�š�\n");
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("inquiry", ([
                "���" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)��ȻҪ��������ý��ѽ����\n",
                "marry" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)��ȻҪ��������ý��ѽ����\n",
      "�Ǽ�" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)�Ǽǵ�ȻҪ��������ý��ѽ����\n",
                "���" : "ý����ɫһ�䣬�е���ǿ��Ц������Ҫ...���(unmarry)����...���ҿ��ǿ����ǳɻ��ѽ��\n"
              "��������Ҫ��һ��Ҫ��Ļ����ǵ�ȥ����֪���������ˣ���\n",
                "unmarry" : "ý����ɫһ�䣬�е���ǿ��Ц������Ҫ...���(unmarry)����...��ý��������\n"
              "�ģ�ֻ�����Ұ죬������������\n",
      "����":"ý������Ц�����������ô����£����ѵĵط��ɲ��٣�Ҫ50 gold��,�����\n"
              "��Ҫ���Ѳ���Ǯ������Ҫ100 gold����\n",
        ]) );
        set_skill("literate", 100);
        set_skill("dodge", 500);
        set_skill("unarmed", 300);
   setup();
        add_money("gold", 4);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;
        ::init();
        add_action("do_marry", "marry");
   add_action("do_bai","��");
        add_action("do_name","��");
}

int accept_object(object me, object ob)//��Ǯ
{
   if( !query("money_id", ob) )
             return notify_fail("ý������Ц���������������г��кȲ���ʲô���������û�ȥ�ɣ���\n");
        if( !query_temp("ask_money", me))//�������жϽ�Ǯ�����Ƿ���Ͻ��������
           return notify_fail("ý���Ի���ʣ��������ʲô���׸���Ǯ����\n");
          if(ob->value() < 500000)
              return notify_fail("ý��������üͷ˵������Ǯ̫���˰ɣ�50 gold�������ô����£����پͲ����ˡ���\n");
        message_vision("ý�Žӹ�Ǯ��$N˵������λ"+RANK_D->query_respect(me)+"�ҿ�û׬���Ǯ��������һ�Ҫ����ϲ�á���\n"
                   "Ҫ���ˡ����а���磬�㲻���һ�������һ��ģ������һ����԰��㷢������\n"
         "��������롮�� <ĳ�˵�����>������\n",me);
        set_temp("marry/money", me->name(), this_object());//��¼����Ǯ����
          return 1;
}

int do_name(string target)//�����
{
        object me,ob,dest, *all;
        int i;
        me = this_player();
        ob = this_object();
        all = users();

        if (me->is_busy())
                return notify_fail("ý��˵��������æ����ٺ���˵���ɣ���\n");
        if( ob->is_fighting()||me->is_fighting() )
                return notify_fail("ý��˵����������û���򣡡�\n");
        if( !living(ob) )
                return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");
        if( query_temp("marry/money", ob) != me->name() )
      return notify_fail("ý��б��б�㣺������û��Ǯ����\n");
        if( query("waiting_target", ob) )
                return notify_fail("ý��ЦЦ˵������Ҫ�����ҵ�Сϲȵ�ǻ�û�зɻ����أ���\n");
        if( !target || target==" ")
                return notify_fail("ý�ų��һ�����д�˼����ʣ���������˭���μ���Ļ��񣿸�������(��)�����֣���\n");
        for(i=0; i<sizeof(all); i++)
        {
                if( target == all[i]->name() || target == query("id", all[i]) )
                        dest = all[i];
        }
        if( !dest )
                return notify_fail("ý�Ÿ����㣺�����ź�����������������ڲ�����Ϸ�У���\n");
        if (dest->is_ghost())
           return notify_fail("ý����ϧ�صظ����㣺����������֪����Ҫ������Ѿ����ˣ�����ڰ�˳�㣡��\n");
        set("waiting_target",query("id",  dest), ob);
        set("me_name",query("name",  me), ob);
        set("me_id",query("id",  me), ob);
        message_vision(HIG"ý��һ��ϲ����д�ϼ����֣�˫��һ�ģ��Ӷ��Ⱦͷɳ�һֻСϲȵ������ϲ����\n"
   "���㶵�һ������ʧ��������ˡ�\n" NOR,me);
        call_out("do_chase", 1, ob);
        return 1;
}

int do_chase(object ob)//ϲȵ�����
{
        object dest,obj;
        dest=find_player(query("waiting_target", ob));

        if( !objectp(dest) || !environment(dest) )
        {
                call_out("waiting", 0, ob);
                return 1;
        }
        message_vision(HIY"�����ͻȻ�ɹ���һֻ��ϲȵ������$N��ͷ�������ŵ�һ��ϲ��ݸ�$N��\n" NOR, dest);
        obj = new(__DIR__"obj/xitie");
        set("name", HIR+query("me_name", ob)+"("+query("me_id", ob)+")"+"�Ľ������"NOR, obj);
        obj->move(dest);
        call_out("do_ok", 0, ob);
        return 1;
}

int waiting(object ob)//ϲȵ�ȴ�
{
        object dest;
        dest=find_player(query("waiting_target", ob));

        if ( objectp(dest)&&dest->is_ghost() )
        {
                        delete("waiting_target", ob);
                        call_out("do_ok", 1, ob);
                        return 1;
        }
        remove_call_out("waiting");
        call_out("waiting", 60, ob);
   return 1;
}

int do_ok(object ob)//ϲȵ�ͼ�ɹ�����
{
        message("vision", "ͻȻ������ϲȵ�Ӵ���ɽ���������ý�����ԣ�ý��Ц���еظ��Ż�ϲȵ��ͷ��\n"
                "˵���������ղ��Ѿ����͵��ˣ���������˭���������˾Ϳ�ʼ�������(marry sb.)�ɣ���\n", environment(), ob);
          delete("waiting_target", ob);
        delete("me_name", ob);
        delete("me_id", ob);
        return 1;
}

int do_marry(string arg) //�жϽ��
{
        object obj, me,ob,old_target;
        me = this_player();
        ob = this_object();
        if( query("gender", me) == "����" )
                return notify_fail("ý�ź���һ���������޸����ԣ����ʲô�飿����\n");

        if( (query("age", me)<18) && (query("gender", me) == "����" )
                 || (query("age", me)<16) && (query("gender", me) == "Ů��") )
                return notify_fail("ý��Ц������˵�������������ڻ����ᣬ�Ժ���˵�ɣ���\n");
        if (me->is_busy())
                return notify_fail("ý��˵�����������ڲ�����æ���𣿡�\n");

        if( me->is_fighting(this_object()) )
        {
                if( !this_object()->is_killing(me) )
                        this_object()->kill_ob(me);
                return notify_fail("ý��˵�������ã��ã���������ȥ����ɻ飡��\n");
        }

        if( this_object()->is_fighting() )
                return notify_fail("ý��˵������û����������˵����𣡡�\n");

        if( !living(this_object()) )
                return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");

        if( me->is_fighting() )
                return notify_fail("ý��˵�����ٺ٣����Ȼ������������������˵�ɣ�\n");

        if( !environment() || base_name(environment()) != query("startroom"))
                return notify_fail("ý��˵�������汧Ǹ�������ں�æ��������һ�ᵽ����ׯ�����Ұɡ���\n");

        if( query("class", me) == "bonze" || query("jobname", me) == "bonze" )
                return notify_fail("ý��Ц��������������ô���ŷ��Ҳ�뿪ɫ������?��\n");

        if( query("jobname", me) == "taoist" )
                return notify_fail("ý��ҡ��ҡͷ�����������˵������Ƿ��Ĳ�����������Ҫ�����룬���ǻ����������ɣ���\n");

        if(!arg ||!find_player(arg) )
                return notify_fail("ý���ʵ����������˭ϲ����Ե����\n");

        if(!objectp(obj = present(arg, environment(me))))
                return notify_fail("ý��˵������������Ҫ������һ������ѽ����\n");

        if( query_temp("pending/pro", me) )
                return notify_fail("ý����������ף���Ļ��������ڽ������𣿻�Ҫ��ʲô����\n");

        if( query_temp("pending/pro", obj) )
                return notify_fail("ý��˵��������������˽����𣿡�\n");

        if( !obj->is_character() )
                return notify_fail("ý��˵���������ⲻ�����Լ������𡣡�\n");

        if( query("class", obj) == "bonze" || query("jobname", me) == "taoist" )
                return notify_fail("ý��Ц����������"+ obj->name() +"���ǳ����ˣ�����˼ҿ���Ц�ˡ�\n");

        if( mapp(query("couple", me)) )
        {
      if( query("couple/married", me)>2 )
              return notify_fail("ý�ŷ��˷���Ե����������˵����������͸���˵������ô�����ˣ�\n"
              "�����ʵ�ڲ��ܰ���ʲô�ˣ��������̫���ˣ�����͢�ټͣ��ǲ�\n"
              "׼�ٰ����������ˣ�����ȥ����Ұԧ��ɣ�\n");
              if( query("couple/have_couple", me) )
              {
                      if( obj == present(query("couple/couple_id", me),environment(me)) )
                              return notify_fail("ý������������Ǳ������Ƿ���ѽ�����ﻹҪ��������\n");
                      if( query("gender", me) == "Ů��" )
                              return notify_fail("ý��˵���������Ѿ����з�֮���ˣ����ﲻ�����ػ�ġ���\n");
                      else
                              return notify_fail("ý��˵���������Ѿ����и�֮���ˣ����ﲻ�����ػ�ġ���\n");
              }
        }
        if( mapp(query("couple", obj)) )
        {
      if( query("couple/married", obj)>2 )
              return notify_fail("ý�ŷ��˷���Ե����̾�˿����������������˵������ô�����ˣ���\n"
           "����ʵ�ڲ��ܰ�����ʲô�ˣ�����û���⣬��"+obj->name()+"������̫���ˣ�\n"
        "����͢�ټͣ��ǲ�׼�ٰ����������ˣ�����ȥ����Ұԧ��ɣ�\n");
        if( query("couple/have_couple", obj) )
                {
                        if( query("gender", obj) == "Ů��" )
                                return notify_fail("ý��˵������ϧ���Ѿ����з�֮���ˣ����ﲻ�����ػ�ġ�\n");
                        else
                                return notify_fail("ý��˵������ϧ���Ѿ����и�֮���ˣ����ﲻ�����ػ�ġ�\n");
                }
        }
        if( !living(obj) )
                return notify_fail("ý��ҡҡͷ˵������"+ obj->name()+"���ڻ�û���ѹ������һ�����ȷ������˫��������Ը�ġ���\n");

        if( query("gender", obj) == query("gender", me) )
                return notify_fail("ý�ž��������ۣ�����ͬ�������Բ��������Ӵ��������£���\n");

        if(obj == me)
                return notify_fail("ý��˵���������ⲻ�����Լ������𣿡�\n");

       if( !userp(obj) )
                return notify_fail("ý��˵�������Բ�����ֻ�ܺ���ҽ�顣��\n");

   if( query_temp("marry/money", ob) != me->name( )
            && query_temp("marry/money", ob) != obj->name())//ֻҪ������һ���˸�������
        {
           set_temp("ask_money", 1, me);
       set_temp("ask_money", 1, obj);//��ֹ���������׽��
           return notify_fail("ý��Ц�����ص��������Ҫ��һ��Ǯ��ඣ�Ҫ50 gold������Ǯ���ҿ�û������죡\n");
   }

        if( query("unmarried", me)>2 )
        {
           delete("unmarried", me);
      delete("married", me);
      set("couple/married", 2, me);
      message_vision("ý�ŷ��˷���Ե������$N˵����������������ô���������������㣿����\n"
      "�ٸ������һ�λ��ᣬ����飬������Ͳ���������ˣ���\n",me);
   }
        if( query("unmarried", obj)>2 )
   {
           delete("unmarried", obj);
      delete("married", obj);
      set("couple/married", 2, obj);
      message_vision("ý�ŷ��˷���Ե������$N˵����������������ô���������������㣿����\n"
      "�ٸ������һ�λ��ᣬ����飬������Ͳ���������ˣ���\n",obj);
   }
        if( !query_temp("marry/answer", me) )
   {
           message_vision(HIG"ý��̯����Ե��������߶߶��˵�����������һ���ӵ�������£��ɲ���\n"
           "�����㣬���������������ˡ�ÿ����ֻ��������������ν��������\n"
           "���ҿ�����"HIC""+me->name()+"���"+query("couple/married", me)+"�λ飻"+obj->name()+"���"+query("couple/married", obj)+"�λ飻"
           HIG"�õģ�\n������������濼��һ�£��ǲ�������Ը��ͶԷ���飿��\n"NOR,me);
           set_temp("marry/answer", 1, obj);
   }
        if( query_temp("pending/marry", obj) != me )
        {
                if( query("gender", obj) == "Ů��" )
                        message_vision(MAG "\n$N����$n�ʵ�������Ը��޸����𣿡�\n\n"NOR, me,obj);
                else
                        message_vision(MAG "\n$N����$n�ʵ�������Ը��Ȣ���𣿡�\n\n"NOR, me,obj);

                if( objectp(old_target=query_temp("pending/marry", me)) && old_target != obj )
                        tell_object(old_target, YEL + me->name() +
                        "ȡ���˺��������ͷ��\n" NOR);

                set_temp("pending/marry", obj, me);

                if( query("gender", obj) == "Ů��" )
                        tell_object(obj, MAG "�����Ը��޸���������Ҳ��" + me->name()
                        +"("+query("id", me)+")"+"��һ��marryָ�\n"NOR);
                else
                        tell_object(obj, MAG "�����Ը��Ȣ��������Ҳ��" + me->name() +
                        "("+query("id", me)+")"+"��һ��marry"+query("id", me)+"��ָ�\n"NOR);
      write(MAG"�����㼱�����������������˵ͬ��...\n" NOR);
      return 1;
        }
        message_vision(MAG "\n$N����$n����˵������Ը�⣡\n\n"NOR, me,obj);
        message_vision(MAG "ý�źǺ�Ц�������Ǿͺã��Ǿͺã������ҵ����ߵ���Ե����׼�����ðɣ���\n"
           "˵�꣬ý��һŤһŤ���߽��˶��ߵĴ��á�\n" NOR, obj, me);
        delete_temp("ask/marry", me);
        ob->move("/d/ruzhou/yinyuan-tang");

        set_temp("pending/pro", 1, me);
        set_temp("pending/pro", 1, obj);

        set("couple/couple_name", obj->name(), me);
        set("couple/couple_id",query("id",  obj), me);

        set("couple/couple_name", me->name(), obj);
        set("couple/couple_id",query("id",  me), obj);

        if( query("gender", obj) == "Ů��" )
        {
                set("couple/couple_gender", "����", me);
                set("couple/couple_gender", "�ɷ�", obj);
        }
        else
        {
                set("couple/couple_gender", "����", obj);
                set("couple/couple_gender", "�ɷ�", me);
        }
   call_out("meipo_waiting", 1,ob,me,obj);
         return 1;
}

int meipo_waiting(object ob,object me,object obj)//ý�ŵȰ���
{
        if( query_temp("wait_time", ob) == 200 )
        {
                say( "ý���ɻ��˵������С����������Ҳ�������ѵ�������Ե�޷ݣ�����������ȡ���գ�\n"
              "������ǰ�׬��50 gold�ˣ��ǺǺ�...��\n\n");
                call_out("do_back", 0, ob);
      return 1;
        }
        if( environment(ob)==environment(me)&&environment(ob)==environment(obj) )
   {                                                 //���˶���
      delete_temp("wait_time", ob);
           call_out("ready_marry", 1,ob,me,obj);
   }
        else
   {
                if( environment(ob)==environment(me)&&environment(ob)!=environment(obj) )
                {
                        if( random(10) == 0 )
                        say("\ný���ʵ�����"+me->name()+"����ȥ����"+obj->name()+"��ô�����������ѵ���Ը���ˣ�\n");
                        addn_temp("wait_time", 1, ob);//����һ��obj����
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
           else if( environment(ob)!=environment(me)&&environment(ob)==environment(obj) )
                {                                            //����һ��me����
                        if( random(10) == 0 )
                        say("\ný���ʵ�����"+obj->name()+"����ȥ����"+me->name()+"��ô�����������ѵ���Ը���ˣ�\n");
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
                else
      {
                   addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
      }
   }
        return 1;
}

int ready_marry(object ob,object me,object obj)//׼������
{
        object room,npc;

        if(!( room = find_object("/d/ruzhou/yinyuan-tang")) )
        room = load_object("/d/ruzhou/yinyuan-tang");

        message("vision", HIY "\ný�Ÿ����е��������죬�ɻ�Ķ������ˣ����ϲ���ϲ�ã���\n" NOR, room);
        message("vision", HIC"\nֻ���ú�����һ��Ų�����ʮ����������������·���������Ů�����������ܽ�����\n"
                "ߴߴ�����������ţ��ַ�ͷ�ܿ��ˣ�ʱ��ʱ��Ц�ſ�һ��"+me->name()+"��"+obj->name()+"��\n\n"NOR, room);
        say("ý�Ŷ���λ����˵��������Ҫ�ż������Ƕ��Ǻ��о���ģ��ܿ�ͻ᲼�úõģ���\n"
   CYN"ֻ����ߵ���������ȥ��æ�ò����ˡ�\n"NOR);
        call_out("wait_marry", 1, ob,me,obj);
   return 1;
}

int wait_marry(object ob,object me,object obj) //����ϲ��
{
        object room;
        if(!( room = find_object("/d/ruzhou/yinyuan-tang")) )
        room = load_object("/d/ruzhou/yinyuan-tang");
        switch(query_temp("wait_time", ob) )
        {
           case 0:
            say(RED"\nһ��С�һ��ܹ������е�����ý�ţ����ֽ��Ǯ�����ˣ���ý�ŸϽ�����һЩǮ��\n\n"NOR);
           set_temp("wait_time", 1, ob);
           call_out("wait_marry", 1, ob,me,obj);
           break;
      case 1:
             say(MAG"\nͻȻ���Ǳߵ�С����е�����ý�ţ���ԧ�����������������ý��һ�������ұ�����ȥ�㣡��\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
      case 2:
             say(CYN"\n�ĸ��һ��Ӵ��Ӵ��̧��һֻ�����Ӵ�����������߹���ý�Ŷ�����������Щ����㣡��\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
                case 3:
      say("\ný��һ����ס����ܹ���һ��С���ӣ���ӭ��¥��ϲ�綩���𣿿�ȥ����\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
      case 4:
             say(YEL"\n�Ǳߵ��˽е��������û��������������������������\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
           break;
                case 5:
             say("\n�Ǳ��ֽ���������ý�ţ�����Ǯ���ͻ����İɣ��������ˣ���ý�ŸϽ��ܹ�ȥ��\n\n");
      addn_temp("wait_time", 1, ob);
                 call_out("wait_marry", 1, ob,me,obj);
      break;
                case 6:
             say(CYN"\ný��һ·С�ܹ��������������������ģ����ͷ��ͷ�У����죬������׼��ϲװ����\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
                case 7:
                  say(WHT"\nһ�������ְ˽ŵ�̧���˼��Ŵ����ӣ��������Ϲ���һ������\n"HIR
"                               ��      ��\n"
"                            ����������������\n"
"                            ����������������\n"
"                             ������  ������\n"
"                             ������  ������\n"
"                              ����    ����\n"
"                            ����������������\n"
"                             ������  ������\n"
"                             ������  ������\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
           case 8:
             say(YEL"\n�������ֿ�ʼ���Ի������������������������ʶ����ʶ���ˣ��׷׹�����أ�����ϲ��ϲ����\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
                case 9:
                    say("\n����С����Ц������һ�߲������Σ�һ�߻���ҧ�Ŷ��䣬��ʱ��͵�ۿ������ˡ�\n\n");
      message("vision", HIY "\ný�Ÿ�������һ��������׼�������𣿡�����Ӧ���������ˣ���\n"
      "ý�������ϳ��������������������������ֻ��񡭡�����\n"
      YEL"��ʱ���������������ڴ��������ɰ���ӵ���������ְ˽Ÿ����ɡ����ﻻ�����£�\n"
      "׺ӵ�������������ȥ��\n"NOR,room);
              addn_temp("wait_time", 1, ob);
              call_out("start_marry", 1, ob,me,obj);
//            call_out("wait_marry", 1, ob,me,obj);
                break;
//                case 10:
//      call_out("start_marry", 1, ob,me,obj);
//      break;
   }
   return 1;
}

int start_marry(object ob,object me,object obj) //��ʼ����
{
        object moon,room;
   string msg;
        if(!(room = find_object("/d/ruzhou/yinyuan-tang")))
                room = load_object("/d/ruzhou/yinyuan-tang");
        moon=new(__DIR__"yuelao");
   moon->move(room);
        message("vision", "\n����һ�������Ц��һλ�����������ߣ��첽������У��ڳ���������Ů��������ݣ�\n"
           "����������үү�������ϰڰ��֣�Ц�Ǻǵؿ���"+me->name()+"��"+obj->name()+"�����ͷ����\n"
      "���ã��ã��ɲ�Ůò������֮�ϣ�����֮��ѽ����\n"
           HIY"\ný��һ���֣�ϲ���ָ���ֻ�������ϸ��������������ɡ�����ݡ���ء�������\n"NOR,room, moon);
   say("ý����С���ض���������˵������˳�����롮�� ��ء��� ���úͰ� �Է������֡�����\n");
   CHANNEL_D->do_channel(moon, "mudnews",
           sprintf("����%s��%sϲ����Ե�����ô���ʱ��ʼ��\n",me->name(),obj->name()));
        set_temp("pending/bai", 1, me);
   set_temp("pending/bai", 1, obj);
        return 1;
}

int do_back(object ob)//����
{
   delete_temp("wait_time", ob);
   delete_temp("marry/money", ob);
        say("ý�����������ϣ���һŤһŤ����������ȥ��\n");
   ob->move("/d/ruzhou/hongniang-zhuang");
        return 1;
}

int do_bai(string arg)//����
{
        object me,ob,obj;
        string act;

        me = this_player();
   ob = this_object();
        if (me->is_busy())
                return notify_fail("ý��˵�����������ڲ�����æ����æ����˵����\n");

        if( me->is_fighting(this_object()) )
        {
                if( !this_object()->is_killing(me) )
                        this_object()->kill_ob(me);
                return notify_fail("ý��˵������������ĸ������£���Ҷ��䣬����ȥ����ɻ�ɣ���\n");
        }

        if( this_object()->is_fighting() )
                return notify_fail("ý��˵����û����������˵�����\n");

        if( !living(this_object()) )
                return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");

        if( me->is_fighting() )
                return notify_fail("ý��˵�������ٺ٣����Ȼ������������������˵�ɣ���\n");

        if( !environment()||base_name(environment()) != ("/d/ruzhou/yinyuan-tang") )
                return notify_fail("ý��˵���������������ǵģ�������Ҫ����Ե�ò��е�ѽ����\n");

        if( !query_temp("pending/bai", me) )
                return notify_fail("ý��Ц�������������㷸ʲôɵѽ����\n");

        if( !objectp(obj=present(query("couple/couple_id", me),environment(me)) )
                 || !find_player(query("couple/couple_id", me)) )
        {
           message_vision("ý��ת��һ�������ȵ�˵��������ѽ����İ�����ôͻȻ���ˣ�������ô���У����ɢ̯�ɡ���\n"
              "��һƬ��ϧ������ҷ׷��볡��ϲ���ϵĶ���Ҳ��һ�ն��ա�\n",me);
      call_out("do_back",1,ob);
      return 1;
   }

   if( arg == "���" || arg == "����" || arg == ""+query("couple/couple_name", me) )
                return notify_fail("���ݡ������Ĵ�֮�����ð�ǿո�\n");

        if( !arg || (query_temp("pending/bai", me) == 1 && arg != "���" )
                 || (query_temp("pending/bai", me) == 2 && arg != "����" )
                 || (query_temp("pending/bai", me) == 3 && arg != query("couple/couple_name", me)) )
                return notify_fail("ý��Ц���������Ұ�ʲôѽ��һ����أ����ݸ��ã�������İ��ˣ��ɱ��ٴ��ˣ���\n");

        if( query_temp("pending/act", obj) != arg )
        {
      if( query_temp("pending/bai", me) != 3 )
      {
                        tell_object(obj, MAG"��İ��������ź���� " + arg + " ��...\n" NOR);
                        write(MAG "���������ȴ�����İ���...\n" NOR);
                        set_temp("pending/act", arg, me);
      }
      else
      {
                        tell_object(obj, MAG"��İ��������ź��㻥�ݣ����������֣���...\n" NOR);
                        write(MAG "���������ȴ�����İ���...\n" NOR);
                        set_temp("pending/act", me->name(), me);
      }
                return 1;
        }
        else if( query_temp("pending/bai", me) == 1 )
   {
                  message_vision("��һ�ݡ��졭�ء�����$N��$n�������������ӯӯ����......\n",me,obj);
      addn_temp("pending/bai", 1, me);
      addn_temp("pending/bai", 1, obj);
      return 1;
   }
        else if( query_temp("pending/bai", me) == 2 )
   {
                  message_vision("�����ݡ��ߡ��á�����$N��$n��վ��������һЦ���ֻ�������......\n",me,obj);
      addn_temp("pending/bai", 1, me);
      addn_temp("pending/bai", 1, obj);
      return 1;
   }
        else if( query_temp("pending/bai", me) == 3 )
   {
                  message_vision("�����ޡ��ԡ��ݡ�����$N��$n���໥�������һ��......\n",me,obj);
                message_vision(HIY "����Ц�Ǻǵ�˵�������ã�$N��$n��������ʽ��Ϊ����! \n" NOR, obj, me);
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf( "��ϲ%s��%s��һ�����ϲ����Ե��\n        ��λ������ѣ���Я������ӭ��¥�μ����ǵĻ��磡\n", me->name(), obj->name()));

                addn("couple/married", 1, me);//������
                set("couple/have_couple", 1, me);//�����ѻ�״̬
      set_temp("married_party", 1, me);//���ϼǺţ�ϲ�����ϰ忴���ͻ�ͬ�⿪��ϯ
      set_temp("married_party", 1, obj);//���˶�������ֻ�����Բ�����
                addn("couple/married", 1, obj);//������
                set("couple/have_couple", 1, obj);//�ѻ�״̬

      delete_temp("pending/bai", me);
      delete_temp("pending/bai", obj);
      delete_temp("pending/act", me);
      delete_temp("pending/act", obj);
                delete_temp("pending/pro", me);
                delete_temp("pending/pro", obj);
             delete_temp("ask_money", me);
           delete_temp("ask_money", obj);
           call_out("last_marry",1,ob,me,obj);
                return 1;
   }
}

int last_marry(object ob,object me,object obj)//���ý���
{
        object moon,room;
        if(!(room = find_object("/d/ruzhou/yinyuan-tang")))
                room = load_object("/d/ruzhou/yinyuan-tang");
        moon = present("yue lao", room);
        moon->move("/d/city/empty");
   delete_temp("wait_time", ob);
   delete_temp("marry/money", ob);
        say("ý�ź��������η򣡿콫�����͵�ӭ��¥���л��磬�Һ����ϾͲ�ȥ�ˣ��Ǻǣ���\n˵��һŤһŤ����������ȥ��\n");
   ob->move("/d/ruzhou/hongniang-zhuang");
        message_vision(HIR"���ɰ���ӵ����λ���ˣ������ſڵ�������컨�Σ�ֻ���η���һ������Σ���\n"
           "һ���˴������ر���ӭ��¥......\n"NOR,me,obj);
   me->move("/d/ruzhou/jiao1");
   obj->move("/d/ruzhou/jiao2");
   call_out("go_lou",8,ob,me,obj);
        return 1;
}

int go_lou(object ob,object me,object obj)//����¥
{
        object room,npc;
        if(!(room = find_object("/d/ruzhou/xifu-tang")))
                room = load_object("/d/ruzhou/xifu-tang");
        message_vision("\n    ���˺ó�һ�����ֻ���η���һ����������������������һ�������䵽�˵��ϣ�\n"
           "$N��$n�ӽ���������һ����ԭ���Ѿ�����ӭ��¥�������ֱ�ӵ����һֱ���˶�¥�����á�\n"
      "ֻ����һ��Ǻ�Ц����ӭ��¥�ϰ�ϲ����Ц�������ӭ����������ϲ��λ���ˣ���ϲ��ϲ��\n��",me,obj);
   npc=new(__DIR__"xi-laifu");//�ϰ����
   set("name1", me->name(), npc);
   set("name2", obj->name(), npc);//˫������
   npc->move("/d/ruzhou/xifu-tang");
   me->move("/d/ruzhou/xifu-tang");
   obj->move("/d/ruzhou/xifu-tang");
   return 1;
}