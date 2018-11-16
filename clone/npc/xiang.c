// lady1.c

#include <ansi.h>
inherit NPC;
object ob;
int is_ename(string id);
int is_cname(string name);

void create()
{
        set_name("���", ({"xiang zhanglao", "xiang", "zhanglao"}));
        set("nickname", "ؤ������");
        set("gender", "����");
        set("age", 59);
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 9);
        set("long", 
"����ؤ��Ĵ������ϣ�Ҳ�����ռ����ص��Ӵ������ĸ���С����Ϣ��\n"+
"����֮��û������֪�������\n");
        
        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 200);
        
        set("combat_exp", 1500000);
        set("score", 200000);
        set("shen", 100000);
         
        set_skill("force", 150);             // �����ڹ�
        set_skill("huntian-qigong", 150);    // ��������
        set_skill("dodge", 150);                   // ��������
        set_skill("xiaoyaoyou", 150);        // ��ң��
        set_skill("parry", 150);             // �����м�
        set_skill("hand", 150);              // �����ַ�
        set_skill("suohou-hand", 150);       // ����������
        set_skill("blade", 150);             // ��������
        set_skill("liuhe-dao", 150);       // �������ϵ�
        set_skill("begging", 100);           // �л�����
        set_skill("checking", 100);          // ����;˵
        set_skill("training", 100);          // Ԧ����
        
        map_skill("force", "huntian-qigong");
        map_skill("hand",  "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "liuhe-dao");
        prepare_skill("hand",  "suohou-hand");

        set("party/party_name", HIC"ؤ��"NOR);
        set("party/rank", RED"�Ŵ�����"NOR);
        set("party/level", 9);
        create_family("ؤ��", 10, "��������");

        setup();
        
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object("kungfu/class/gaibang/obj/cloth")->wear();
}



int accept_ask(object ob, string topic)
{
        object fob;
        object *livings;
                                int i;
                                
        if( topic == query("id", ob) || topic == query("name", ob) )
        {
                command("laugh"+query("id", ob));
                return 1;
        }
     if( is_cname(topic) && !(query_temp("pay_for_ask", ob)) )
       {
               set_temp("give_for_ask", 1, ob);
        set_temp("pending/ask_value", 10000, ob);
               command("say �������˿ɶ����أ��ҵö໨����˼�����õ�ƽ������");
        return 1;
      }
      
      if( is_cname(topic) && query_temp("pay_for_ask", ob) )
      {
              livings=livings();
              for (i=sizeof(livings)-1;i>=0;i--)
               {
                       if( (query("name", livings[i]) == topic || query("fname", livings[i]) == topic) && environment(livings[i]) )
                         {
                                 fob=livings[i];
                           break;
                         }
               }
              if (!fob)
                                {
//                command("shake");
//          command("say �Ҵ�û��˵����������������");
//          return 1;
            return 0;
        }
        delete_temp("pay_for_ask", ob);
      }
      
      if (is_ename(topic))
      {
        fob = find_player(topic);
        if (! fob || ! ob->visible(fob) ) 
        fob = find_living(topic);
        if (! fob || ! ob->visible(fob) )
        {
//                command("shake");
//          command("say �Ҵ�û��˵����������������");
//          return 1;
            return 0;
        }
        if ( ! environment(fob) )
        {
                message_vision(CYN "$N" CYN "��$n" CYN "С"
                               "��������������˵����ô���������û�е������һ㱨���������١�\n" NOR, this_object(), ob);
                return 1;
                
        }
      }
      if (!is_ename(topic) && !is_cname(topic))
        return 0;
      if (!environment(fob) || explode(file_name(environment(fob)),"/")[0]!="d")
              return 0;
         
//        if ( !ob->query("know_ask_cheap") ||ob->query("ask_cheap")   )
          if( !query("owner", fob) && !userp(fob) )
        {
//                      ob->set("know_ask_cheap",1);
                set_temp("pending/ask_about", topic, ob);
                if (!objectp(fob))
                {
                  command("slap");
                  return 1;
                }
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 2000, ob);
                message_vision(CYN "$N" CYN "������üͷ����$n" CYN "ҡҡ"
                               "ͷ�������������ȷʵ�����������ѣ������ʮ"
                               "�����������ˡ�\n" NOR, this_object(), ob);
                return 1;
        }else if( query("owner", fob) && !query("level", fob) )
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 30000, ob);
                message_vision(CYN "$N" CYN "�ٺټ�Ц��������$n" CYN "С"
                               "������û�����⣬������Ҫ�����ƽ𣬲���"
                               "�ۣ�\n" NOR, this_object(), ob);
                return 1;
        }else if( query("owner", fob) && query("level", fob)<3 )
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 1000, ob);
                message_vision(CYN "$N" CYN "������üͷ����$n" CYN "ҡҡ"
                               "ͷ�������������ȷʵ�����������ѣ�����ʮ"
                               "�����������ˡ�\n" NOR, this_object(), ob);
                return 1;
        }else if( query("owner", fob) && query("level", fob) >= 3 )
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 100000, ob);
                message_vision(CYN "$N" CYN "�ٺټ�Ц��������$n" CYN "С"
                               "������û�����⣬������Ҫʮ���ƽ𣬲���"
                               "�ۣ�\n" NOR, this_object(), ob);
                return 1;        
        } else if (userp(fob))
        {
                set_temp("pending/ask_about", topic, ob);
                set_temp("pending/ask_who", file_name(fob), ob);
                set_temp("pending/ask_value", 1000000, ob);
                message_vision(CYN "$N" CYN "�ٺټ�Ц��������$n" CYN "С"
                               "�����������Ҳû�����⣬������Ҫһ�����ƽ𣬲���"
                               "�ۣ�\n" NOR, this_object(), ob);
                return 1;
        }
}

int accept_object(object me, object ob)
{
           string wid;
           object fob;
           int va;
           string old_fob;
           int flag;
           string env;
           string str;
        if (clonep(this_object()))
        {
                command("hehe");
                command("say ���������ϣ���ٰ�������");
                return 1;
        }
     if( !stringp(query("money_id", ob)) )
     {
        switch(query_temp("beichou_refused", me) )
        {
          case 0:
                command("heihei");
                command("say �������������Űɡ�");
                set_temp("beichou_refused", 1, me);
                return 0;

          case 1:
                 message_vision(HIC "$N" HIC "����һ�ţ���$n"
                                HIC "���˳�ȥ���������ʲô��"
                                "��\n" NOR,this_object(), me);
                 break;

          case 2:
                 message_vision(HIC "$N" HIC "����һ�ţ��ݺ�"
                                "�İ�$n" HIC "���˳�ȥ�������"
                                "��Ȼ���������ң�\n" NOR,
                                this_object(), me);
                 me->receive_damage("qi", 100);
                 me->receive_wound("qi", 10);
                 break;

          default:
                 message_vision(HIC "$N" HIC "��ŭ��һ�з���"
                                "���죬�ͼ�$n" HIC "��ֽƬһ"
                                "�����˳�ȥ��\n" NOR,
                                this_object(), me);
                 command("chat*kick4"+query("id", me));
                 me->unconcious();
                 break;
         }

         addn_temp("beichou_refused", 1, me);
         me->move("/d/city/shilijie5");
         message_vision(HIC "ֻ����žડ���һ����$N" HIC
                        "�ݺݵ�ˤ���˵��ϡ�\n" NOR, me);
                return 0;
     }
     delete_temp("beichou_refused", me);
           va=query_temp("pending/ask_value", me);
           if (wizardp(me)) va = 1;
            if( query_temp("give_for_ask", me) && ob->value() >= va )
            {
       delete_temp("give_for_ask", me);
       set_temp("pay_for_ask", 1, me);
                     command("say �ðɣ�˵˵������˭��");
                     return 1;
           }
     if( stringp(wid=query_temp("pending/ask_about", me)) )
     {
              if (ob->value() < va)
        {
            message_vision(CYN "$N" CYN "��Цһ�����������Ǯ��"
                               "�򷢵�С������ࡣ\n" NOR,
                               this_object());
            return 0;
        }
        delete_temp("pending/ask_about", me);
        old_fob=query_temp("pending/ask_who", me);
        flag=1;
        if (!stringp(old_fob) || !objectp(fob=find_object(old_fob)) || !me->visible(fob) || !environment(fob) )
        {
                        message_vision(CYN "$N" CYN "����ͷ��$n" CYN "�������¡���"
                                       "���һ���������Ϣ�أ���ô��ôһ�����\n" NOR,
                                       this_object(), me);
                        return 0;            
            }
//          destruct(ob);
          if (!objectp(fob))
          {
                  command("say �����е����⣬��һ����ʦ�ɡ�");
            return 1;
          }
          env=file_name(environment(fob));
          if (sscanf(env,"/d/%s/%*s",env)!=2) 
          {
             message_vision(CYN "$N" CYN "����ͷ��$n" CYN "�������¡���"
                           "���һ���������Ϣ�أ���ô��ôһ�����\n" NOR,
                           this_object(), me);
                        return 0;
          }
          
          env=to_chinese(env);
          if (strsrch(env,"/")>0 || is_ename(env))
            env="ĳ���ط�";
//          command("whisper " + me->query("id") +" �ո��е���ǰ�����棺");     
          log_file("xiang",me->name()+"ѯ��"+fob->name()+"("+query("id", fob)+")\n");

          str = this_object()->name()+"����Ķ�������˵����"+fob->name()+"�ղ���";
          if( stringp(query("place", fob)) )
                  str += env+"��";
          str+=query("short", environment(fob))+"������û��\n";

          tell_object(me,str);
 //         if (va <= 2000)
 //               me->add("ask_cheap", -1);
 //         else me->set("ask_cheap", 3);
          return 1;
        }
        
        if (ob->value() )
        {
                message_vision(CYN "$N" CYN "�ӹ�$n" CYN "�ݹ�ȥ��" + ob->name() +
                               NOR + CYN "��������ü����������Ǯû�ط����������ˣ��㲻Ҫ��"
                               "���Ұɣ�\n" NOR, this_object(), me);
                return 1;
        }
        return 1;
}

int is_ename(string id)
{
        int i;

        id = replace_string(id,"'s betrayer","");
        if (strsrch(id," ")==-1)
        if( strlen(id) < 3 || strlen(id) > 12  ) 
                        return 0;
        id = replace_string(id," ","");
        i = strlen(id);
        while(i--)
          if( id[i]<'a' || id[i]>'z')
            return 0;
//        tell_object(find_player("qingyun"),"is ename\n");
        return 1;
}

int is_cname(string name)
{
        int i;

        i = strlen(name);
        
        if( strlen(name) < 4 || strlen(name) > 10  ) 
                return 0;
        if( strsrch(name, "��") >= 0) 
                return 0;
        while(i--) {
                if( name[i]<=' ' ) 
                   return 0;
                if( i%2==0 && !is_chinese(name[i..<0]) )                        
                   return 0;
        }

        return 1;
}
