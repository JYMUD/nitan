//meipo.c

#include <ansi.h>
inherit NPC;

string ask_hunyin();

void create()
{
      set_name("ý��",({"meipo", "mei po", "po", "mei"}));
      set("age", 65);
      set("gender", "Ů��");
      set("nickname", "��Ե�춨");
      set_skill("unarmed", 40);

      set("inquiry",([
            "���ܶ���" :  (: ask_hunyin :),
      ]));

        set("chat_chance", 15); 
        set("chat_msg", ({ 
                "��ý�����������˵������˵��ɽ���д�˵�е�ѩ�������ǿ����͸���������õ�����Ŷ��\n",
                "��ý��ڨڨ��˵������������Ǹ�ȳ�ӣ��������ҿ�û˵�����ǰ�����޶����ˣ����ܹ��ң�\n",
                "��ý��͵͵һЦ����ѩ�������������ǻ�����ò�����������ӿ�Ҫ����������£����ܾ���ô������С���ӡ�\n"
        }) ); 

      setup();
      carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
      object ob;

      ::init();

      if (interactive(ob=this_player())&&!is_fighting())
      {
           remove_call_out("greeting");
           call_out("greeting", 1, ob);
      }
      add_action("do_agree", "agree");
}

void greeting(object ob)
{
      if (!ob||environment(ob)!=environment())   return;
      if( query("age", ob) >= 18 && !query("couple", ob) )
      {
           if( query("gender", ob) == "����" )
           {
                 message_vision("$N��$nҡͷ̾������ϧ�Ǹ�̫�࣬��ȻҲ��" +
                                "Ȣϱ����ʱ���ˡ�\n", this_object(), ob);
                 return;
           }

           if( query("gender", ob) == "����" )
           {
                 if( query("per", ob)<20 )

                 message_vision("$N����$n������һ������λ���ӿ���Ҫ������" +
                                "������ܶ������ģ�\n", this_object(), ob);
                 else

                 message_vision("$N����ǰ��$n��������һ���˲ģ���Ҫ������" +
                                "������ܶ���\n", this_object(), ob);
                 return;
           }

           if( query("gender", ob) == "Ů��" )
           {
                 if( query("per", ob)<20 )

                 message_vision("$N����$n��̾�˿�������λ�����䲻��ޣ���Ҫ��" +
                                "�����˼�ȴ�����£�\n", this_object(), ob);
                 else

                 message_vision("$N����ǰ��$n�����ÿ��ε��˶�����Ҫ������" +
                                "������ܶ���\n", this_object(), ob);
                 return;
           }
      }
      return;
}

string ask_hunyin()
{
      object *list = users();
      object ob = this_player();
      string who,gender=query("gender", ob);
      int i, p;

      if (gender == "����")
           return "�����̫�࣬�����Ҷ����麦�ˣ�";

      if( query("couple", ob) )
           return "�㶼�ǽ��˻������, ����ʲô����";

      if( query("age", ob)<18 )
           return "��ôС�����Ҷ�������������\n";

      if( query_temp("mameipo/agree", ob) )
           return "��ô��"+query_temp("mameipo/agree", ob)+
                  "��û�д�Ӧ������������\n";

      i = 0;
      while ( i <sizeof(list))
      {
           if( query("gender", list[i]) == gender || 
               query("gender", list[i]) == "����" || 
               query("age", list[i])<18 || 
               query("age", list[i])>query("age", ob)+5 || 
               query("age", list[i])<query("age", ob)-5 || 
               query("class", list[i]) == "bonze" || 
               query("couple", list[i]) )
           list[i] = 0;
           i++;
      }

      list -= ({ 0 });
      if ( sizeof(list) > 0 )
      {
           p = random(sizeof(list));
           who=query("id", list[p]);
           set_temp("mameipo/who", who, ob);
           return "����"+query("name", list[p])+"("+query("id", list[p])+")"+
                  "��������䣬��������Σ�(agree)\n";
      }
      else   return "��ʱ���Ҳ�������������ˡ�";
}

int do_agree()
{
      object who, ob = this_player();

      if( !query_temp("mameipo/who", ob) )
      {
           tell_object(ob, "��ý�Ŷ�����������������Ӹ�����ܶ���ô��\n");
           return 1;
      }

      tell_object(ob, HIC"��ý�Ŷ����������ˣ������Ӿ͸��������¶����Է�˵˵��\n"NOR);
      who=find_player(query_temp("mameipo/who", ob));
      if (!who)
      {
           tell_object(ob,HIC"��ý�Ŷ��������ϧ�������������Ҳ�����������ˡ�\n"NOR);
           return 1;
      }

      tell_object(who,query("name", ob)+"�л�ý�Ÿ���������"+HIR+"��õ��"NOR+"��\n");
      command("tell"+query_temp("mameipo/who", ob)+""+query("name", ob)+"("+
              query("id", ob)+")���������˼���������Ӹ���˵˵��\n");
      new("/d/city/obj/rrose")->move(who);
      tell_object(ob, HIC"��ý�Ŷ�������������Ѿ��������˼ת���ˣ������ȥ���װɡ�\n"NOR);
      delete_temp("mameipo/who", ob);
      set_temp("mameipo/agree",query("name",  who)+"("+query("id", who)+")", ob);
      return 1;
}
