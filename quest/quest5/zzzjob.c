#include <ansi.h>

mixed names = ({
        ({
        "��ȸ����","��������","�׻�����","��������","�찲��",
        "�������","�����ھ�","�����","������","Ȫ������",
        "��������","�������","����¥","������","��ɽ����",                
        "�߹���","�����ַ�","��������","ϲ�ݳ�","��³��", 
        "����С��","ɽ����","����ͷ","�������","��ɽ����",
        "����Ժ","ӿȪ��","������","���Ϸ�","�Ͻ��",
        "�ɷ��","����ɽ��","������","����̶","���ɷ�",                
        "��Ӧ��","������","������Ժ","������","������", 
        }),
        ({
         "�α�","��å","ƫ��","�Խ�","����","С��","�к�","��ܽ","������",
                 "С��","����ϰ�","����ͨ","�","����","������","��С��","�α�",
                 "����ʦ̫","����ʦ̫","��Զ��","Ī����","½�˷�","������","��ҩʦ","��׺�",
                 "��Ұ��","�˰ٴ�","��־ƽ","С��Ů","���з�","ŷ����","������Ů","�������",
                 "����","������","������","������","����Ⱥ","�����","�����ʦ","���Ʊ���",
                 "��������","ׯ����","˫��","������","ľ����","��Զɽ","������","������",
                 "����","�ڰ���","������","������","�彣��","��ص���","����","����",
                 "��ɽͯ��","ΤһЦ","лѷ","�μ�","½�˷�","�Ŵ�ɽ","������","�������",
                 "ʯ����","���Ǻ�","Ľ�ݸ�","�쵤��","����","�ⲻƽ",

        }),
        });

// names need modify
string ask_job()
{ 
  object  ob, me,gift,*team;
  int exp,position;
  string target,myfam,obfam,job_type;
  ob=this_player();
  me=this_object();
  exp=query("combat_exp", ob);
 /*myfam=query("family/family_name", me);//ͬһ���ɵĲŸ���job,��������ȥ
  obfam=query("family/family_name", ob);//�����û����������
  if(!myfam ||!obfam||myfam != obfam) 
  return "�㲻�Ǳ��ŵ���,�Ҳ��ܸ��㹤��!";
  */
  if( interactive(ob) && query_temp("zzz_job_target", ob )
      && (int)ob->query_condition("zzz_mission"))  
       return "����һ�ε�����û���!";
  if( interactive(ob) && !query_temp("zzz_job_target", ob )
      && (int)ob->query_condition("zzz_mission"))  
       return "����²������ȵȻ�ɡ�";
   
    if (interactive(ob) &&
       (int)ob->query_condition("zzz_busy"))  
       return "�����ҿ�û�и�������񣬵Ȼ������ɡ�\n";
     
        
        if(exp<=100000)     
    return "����书̫����,����ǿ�������ɡ�\n";
    job_type="����";
           set_temp("zzz_job_type", job_type, ob);
        
        if(job_type=="����")
        {target = names[1][random(sizeof(names[1]))];
    ob->apply_condition("zzz_mission",30);    
        set_temp("zzz_job_target", target, ob);
    message_vision(CYN"$N���˵�ͷ����$n˵��:�ɹ���������һ�����ְ���,����Ҫ��ɱ"+target+"����ȥ������һ�¡�\n"NOR , me,ob);
    call_out("begin_kill",30,ob,target);
        return "���С�ġ�";
        }
}

int accept_object(object who, object ob,object me)
{
        if( query("id", ob) != "corpse"){
                command("say ������������?");
                return 0;
        }
        if( !query_temp("zzz_job_target", who)){
                command("say �ð��������������������");
                return 0;
        }

/*if( query_temp("zzz_job_type", who) == "ɱ" )
                if( query("victim_name", ob) != query_temp("zzz_job_target", who )
                         || query("victim_user", ob) || query_temp("zzz_given", who) )
                {       command("shake");
                command("say ��ɱ�����ˡ�");
                return 0;
        }*/
        if( query_temp("zzz_job_type", who) == "����" )
                if( query_temp("must_killby", ob) != query("id", who )
                         || query("victim_user", ob) || query_temp("zzz_given", who) )
                {       command("shake");
                command("say ��ɱ�����ˡ�");
                return 0;
        } 

  /*if( query("kill_by", ob) != who){
                command("say ��������ƺ��������Լ���ɵİɣ�");
                return 0;
        }
set_temp("zzz_given", 1, who); */
        call_out("destroying", 1, ob);
        call_out("ok", 1, who);
        return 1;
}

void ok(object who)
{
        int exp,pot,i;
        if (!who) return;
        command("pat"+query("id", who));
        command("say �ɵĺã�����¸ɾ�����,�����سɴ���!");
        if( !query("zzz_job_count", who) )
                set("zzz_job_count", 1, who);
        else
                addn("zzz_job_count", 1, who);
                i=query("zzz_job_count", who);
                i/=30;
             exp=800+random(200)+i;
        if( query_temp("zzz_job_super", who) )
        {exp+=100;
                 delete_temp("zzz_job_super", who);
                }
                pot=exp/3+random(10);
                //i=3+random(3)+exp/200;
                
                addn("potential", pot, who);
        addn("combat_exp", exp, who);
        delete_temp("zzz_job_target", who);
        delete_temp("zzz_given", who);
                delete_temp("zzz_job_type", who);
                who->clear_condition("zzz_mission");
          who->apply_condition("zzz_busy",1);  
                                tell_object(who,HIW"�㱻�����ˣ�\n" + 
                       chinese_number(exp) + "��ʵս����\n" +
                       chinese_number(pot) + "��Ǳ��\n"+
                       NOR);
                return;
}


void destroying(object obj)
{
        destruct(obj);
        return;
}

string ask_fangqi()
{
         object me;
         me = this_player();
         if(me->query_condition("zzz_mission")<=1)
         return "��û��������,������Ϲ����ʲ��?";
         me->clear_condition("zzz_mission");
         addn("combat_exp", -100+random(20), me);
          me->apply_condition("zzz_busy",4+random(10));
         delete_temp("zzz_job_target", me);
                 delete_temp("zzz_job_type", me);
         return "û��ϵ,�´μ���Ŭ�� ��";
}


void begin_kill(object me,string target)
{  object obj,*ob;
   int i,flag=0;
   if(!me->query_condition("zzz_mission"))
   return;
   if( query_temp("zzz_job_type", me) != "����" || query_temp("zzz_job_target", me) != target )
   return;
   ob = all_inventory(environment(me));
   for(i=0; i<sizeof(ob); i++)
   {
   if( !living(ob[i])||userp(ob[i])||ob[i]==me ) continue;
   if( query("name", ob[i]) == target )
   {flag=1;
        break;
   }
   }
   if (flag==0)
   { call_out("begin_kill",30,me,target);
     return;           
   } 
        obj=new(__DIR__"killer");
        obj->move(environment(me));
    if( random(10)>7 || query("id", me) == "zzz" )
        {obj->do_copy(me,1);
         set("title", HIR"���ְ���"NOR, obj);
         set_temp("zzz_job_super", 1, me);
        }
        else
        obj->do_copy(me,0);
        set_temp("must_killby",query("id",  me), obj);
        message_vision(GRN"\n$N����"+target+"����һ����Ц������"+target+"ȫ�����µĺ�ë�������𣬲���������\n"NOR,obj); 
        message_vision(HIY"$N��$n�ȵ�:�󵨿�ͽ,����������Ұ����\n"NOR,me,obj);    
    message_vision(HIY"$N����һЦ:Ҫ��������,ȥ���ɣ���\n"NOR,obj);
    obj->kill_ob(me);
}

string ask_gonglao(object who)
{
  object me;
  int i;
           
  me = this_player();
  if( !query("zzz_job_count", me) )
  i=0;
  else 
  i=query("zzz_job_count", me);
  message_vision(CYN"$N��$n˵��:���Ѿ������" + chinese_number(i) + "������\n"NOR,who,me);
  return "����Ŭ���ɣ�";
}
