// �����硤���μǡ��汾�����ͣ�
/* <SecCrypt CPL V3R05> */

//by night 
string test_name(string);

#include <ansi.h>
inherit ITEM;

string *names = ({
  "����",
  "ľ��",
  "����",
  "����",
  "����",
  "����",
  "����",
});

string *ids = ({
  "fa ling",
  "mu yu",
  "jing lun",
  "luo yi",
  "chan zhang",
  "nian zhu",
  "jia sha",
});

string *units = ({
  "��",
  "��",
  "��",
  "��",
  "��",
  "��",
  "��",
});

void create()
{
        int i = random(sizeof(names));
        set_name(names[i], ({ids[i],"fa qi"}));
        set("unit", units[i]);   
        if (clonep())
                set_default_object(__FILE__);
        else {      
                set("no_drop","���Ƿ�ҷ�����������㶪����\n");
                set("no_put",1);
                set("long", "���Ƿ�ҷ����������������������budao����\n");
                set("value", 0);
             }
        setup();
}

void init()
{
        add_action("do_budao", "budao");
        add_action("do_check", "kan");
        add_action("do_check", "chakan");                
}

int do_budao(string arg)
{
        object me=this_player();
        int nforce,nmana,skl,i;
        int j = 0;
        string people = "";
        object *obs = all_inventory(environment(me));
        
        nforce=query("force", me)/4;
        nmana=query("mana", me)/4;
        skl = random(60) + 140 - (int)me->query_skill("chanting", 1);
        if(skl>180) skl = 180;
        if(skl<10) skl = 10 + random(5);
        i = sizeof (obs);
        while (i--)
        {
        if (living (obs[i]) && obs[i]!=me && me->visible(obs[i]) )
                {
                j++;
                people = people + obs[i]->name();
                }
        }

        if( query_temp("obj/done", me) >= 1 )
        {
          tell_object(me,"���Ѿ���ɲ����ˣ���ȥ����ɡ�\n");
          return 1;
        }
        else
        if( query_temp("obj/budao", me)<1 )
        {
          tell_object(me,"���ں���û���ֵ���ȥ������\n");
          return 1;
        }
        else
        if( query_temp("obj/where", me) != test_name(base_name(environment(me))) )
        {
          tell_object(me,"�㲼���ĵط���������ɣ�\n");
          return 1;
        }
        else
        if( query_temp("budao", environment(me)) >= 1 )
        {
          tell_object(me,"�������ǰ�����������������ڿ������ò���ʱ��\n");
          return 1;
        }
        else          
        if( (query("sen", me)<20) )
        {  
          tell_object(me,"��ľ������ܼ��У������Բ�����\n");
          return 1;
        }
        else
        if( (query("kee", me)<30) )
        {
          tell_object(me,"�������״̬̫����ܴ���������\n");
          return 1;
        }
        else          
        if (j == 0 || !me)
        {
          tell_object(me,"����˶�û�У���ʲô����\n");
          return 1;
        }
        else
        if (me->is_busy())
        {
          tell_object(me,"��������æ���أ�û��������\n");
          return 1;
        }
        else
        if (!arg || arg == "" )
        { 
          tell_object(me,"��Ҫ��ʲô���߽��в�����\n");
          return 1;
        }
        else
        if ( arg == "fa ling" || arg == "mu yu")
        {
          if(!present(arg,me)) return notify_fail("������û������������\n");        
          if( nforce<30 || (query("force", me)<nforce) )
            return notify_fail("��������Ҫ��Ϣ�Ƴ�������������㣬�����ܼ���\n");
          
          message_vision(HIW"$N���������ӣ�����ׯ�ϣ�����һ���󳪡�\n"NOR,me);          
          me->start_busy(skl);
          addn("force", -nforce, me);
        remove_call_out ("reacting");
        call_out ("reacting",1+random(3),me,people,j);
          remove_call_out("fanchang");             
          call_out("fanchang",skl,me);
          return 1;
        }
        else
        if ( arg == "luo yi" || arg == "jia sha")
        {
          if(!present(arg,me)) return notify_fail("������û������������\n");
          if( nmana<30 || (query("mana", me)<nmana) )
            return notify_fail("�������뷨����ӯ���㷨�����㣬��˼���Լ��С�\n");
            
          message_vision(HIW"$N��Ŀ���ף���ʲ���أ������ˡ�����������\n"NOR,me);          
          me->start_busy(skl);
          addn("mana", -nmana, me);
        remove_call_out ("reacting");
        call_out ("reacting",1+random(3),me,people,j);
          remove_call_out("jiangjing");                       
          call_out("jiangjing",skl,me);
          return 1;
        }
        else
        if ( arg == "chan zhang" || arg == "jing lun" || arg == "nian zhu")
        {
          if(!present(arg,me)) return notify_fail("������û������������\n");        
          if( (nmana<30 || nforce<30) || (query("mana", me)<nmana) || (query("force", me)<nforce) )
            return notify_fail("�����̳�������������ڶ�Ϊһ����ؽ��㣬���״̬��������\n");

          message_vision(HIW"$N�����̳������Ĭ����Ϊ���ս�����\n"NOR,me);          
          me->start_busy(skl); 
          addn("mana", -nmana, me);
          addn("force", -nforce, me);
        remove_call_out ("reacting");
        call_out ("reacting",1+random(3),me,people,j);
          remove_call_out("kaitan");                                         
          call_out("kaitan",skl,me);
          return 1;
        }
}

int fanchang(object me)
{
        message_vision(HIY"$N������΢�����ⲻɢ��Χ�۵�Ⱥ���ƺ���������\n"NOR,me);
        set_temp("obj/done", 1, me);
        set_temp("budao", 1, environment(me));
        return 1;
}

int jiangjing(object me)
{
        message_vision(HIY"$N�����������컨��׹����Χ��Ⱥ�������������ѡ�\n"NOR,me);
        set_temp("obj/done", 1, me);
        set_temp("budao", 1, environment(me));
        return 1;
} 

int kaitan(object me)
{
        message_vision(HIY"$N�ȱ��նɣ�����ׯ�ϡ���Χ��Ⱥ�ڶ�����Ŀ�ɿڴ���\n"NOR,me);
        set_temp("obj/done", 1, me);
        set_temp("budao", 1, environment(me));
        return 1;
}  

string test_name(string arg)
{
  string *temp;
  temp=explode(arg,"/");
  return temp[2];
}

int do_check(string arg)
{
        object me;

        me = this_player();

        if(!arg) return 0;
        if( (arg == "faqi" || arg == "faqi") && query_temp("obj/budao", me)){
                write(
                        "����һ���������㲼����Ŀ�ĵ��ǣ�"
                        HIG"��"+query_temp("obj/budaowhere", me)+"��"NOR"��\n"NOR);
        }
        else
        {
        if( (arg == "faqi" || arg == "faqi") && !query_temp("obj/budao", me) )
        write("����һ���������������Ϸ�����\n");
         }
        return 1;
}

void reacting (object me, string people, int j)
{
  if (j == 0 || !me)
    return;

  if (j == 1)
    message_vision (people+"���������ڴ˲���������ͣ������������������\n",me);
  else
    message_vision (people+"���˼������ڴ˲�������Χ�˹�ȥ������������\n",me);
}
