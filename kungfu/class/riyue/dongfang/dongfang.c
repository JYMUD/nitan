#include <ansi.h>
#include <command.h>
#include "/kungfu/skill/eff_msg.h";

inherit NPC;
inherit F_MASTER;

mixed ask_kuihua();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();

int p, j;

void create()
{
        object ob;
	set_name(HIR "��������" NOR, ({ "dongfang bubai", "dongfang", "bubai" }));
	set("long", " �����Ƕ������ܣ����������в�Ů������ȴ��Ϊ���ġ�\n");
	set("gender", "����");
	set("age", 30);
	set("shen_type", -1);
	set("str", 51);
	set("int", 39);
	set("con", 50);
	set("dex", 62);
	
	set("max_qi", 10000);
	set("max_jing", 10000);
    set("max_jingli", 10000);
    set("jingli", 10000);
	set("max_neili", 12000);
	set("neili", 12000);
	set("jiali", 550);
	set("combat_exp", 5000000);
	set("score", 1200000);

	set_skill("force", 450);
    set_skill("parry", 450);
    set_skill("dodge", 450);
    set_skill("sword", 450);
    set_skill("unarmed", 450);
    set_skill("literate", 350);
    set_skill("martial-cognize", 400);
    set_skill("kuihua-mogong", 450);

	map_skill("force", "kuihua-mogong");
	map_skill("dodge", "kuihua-mogong");
	map_skill("unarmed", "kuihua-mogong");
	map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

	prepare_skill("unarmed", "kuihua-mogong");

	create_family("�������", 2, "����");

        set("inquiry", ([
                "����ͤ"    :    "���� ����\n",
                "������"    :    "�� �������ҵ������ɱ������\n",
                "����ħ��"  :    (: ask_kuihua :),
                "������Ϣ"  :    (: ask_skill1 :),
                "�����޾�"  :    (: ask_skill2 :),
                "�ޱ��޼�"  :    (: ask_skill3 :),
                "�޷�����"  :    (: ask_skill4 :),
                "�������"  :    (: ask_skill5 :),
		"����Ӱ"  :    (: ask_skill6 :),
                
        ]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "dodge.sheng" :),
		(: perform_action, "sword.bian" :),
		(: perform_action, "sword.tian" :),
		(: perform_action, "sword.qiong" :),
		(: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: perform_action, "sword.hui" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "roar" :),
	}) );

	setup();

        if (clonep())
        {
                     ob = find_object("/clone/lonely/book/kuihua-jianpu"); 
                     if (! ob) ob = load_object("/clone/lonely/book/kuihua-jianpu");
      
                     if (! environment(ob) && random(20) == 1) 
                             ob->move(this_object()); 
        }

        carry_object(__DIR__"zhen")->wield();
        carry_object(__DIR__"changpao")->wear();
}

mixed ask_kuihua()
{
        object ob = this_object();
        object me = this_player();
        int lv = me->query_skill("pixie-jian", 1);

        if( query_temp("teach_kh", me) )
        {
            command("shake");
            
            return 1;
        }
        
        if( query("gender", me) != "����" && !query("special_skill/guimai", me) )
        {
             command("heng");
             ob->kill_ob(me);
             return 1;
        }

	if (me->query_skill("kuihua-mogong", 1))
	{
		command("heng");
		return 1;
	}
	
        if (lv < 300)
        {
             if (me->query_skill("pixie-jian", 1))
             {
                     command("say ��ȥ�ú���ϰ���������ң�");
                     return 1;
             }
             command("say ��������ƾ��Ҳ�����������");
             return 1;
        }

        command("nod");
        command("heihei");
        command("say �ðɣ��Ҿʹ������ħ�������С���ˣ�");
        tell_object(me, HIG "\n����������Ȼ��Хһ�������������̶��������ĳ���ҡ��������ؿ�һ��һ����Ѫ�����\n" NOR);
        tell_object(me, HIC "Ȼ����ȴ�޷���׽���������ܵĶ���\n" NOR);

        set_temp("teach_kh", 1, me);

        if( query("qi", me)<2000 )
        {
              me->unconcious();
              delete_temp("teach_kh", me);
              return 1;              
        }
        
        me->receive_wound("qi",query("qi", me)/2);
        addn("neili", -(2000-lv), me);
        me->start_busy(2 + random(2));
        p=query("qi", me)*100/query("max_qi", me);
        tell_object(me, "(��" + eff_status_msg(p) + ")\n\n");
   
        j = 0;
    
    	me->start_busy(60);
    	
        remove_call_out("teach_kuihua");
        call_out("teach_kuihua", 2, me, lv);
        
        return 1;        
}

void teach_kuihua(object me, int lv)
{
        int sz;
	int qi;
	
        string* teach_words = ({
        HIG "��Ȼ�䶫����������Ȼ�ӿ죬��Х��������Χ��ת����о��������̡�\n" NOR,
        HIG "���Ǽ�һ�����������������������������ʱ����Ϊ��ǧ��Ӱ������������Χ���㽥������ͷ��Ŀѣ��\n" NOR,
        HIG "�����أ�����������Խ��Խ�죬�ѻ���Ϊ����������Ӱ���������ܼ�Хһ�����Ӳ�ͬ�ĽǶ�����Ϯ����\n" NOR,
        HIG "�������ܳ���һ����һ�����⻮������Ȼ��������ǰһ������پ����ؿڴ�ʹ�ޱȡ�\n" NOR,
        });

        if (environment(me) != environment(this_object())
            || ! environment(me))
              return;

        sz = sizeof(teach_words);

        tell_object(me, teach_words[random(sz)]);
        tell_object(me, HIC "Ȼ����ȴ�޷���׽���������ܵĶ���\n" NOR);
        
	qi = 1400 - lv;
	if (qi < 100)qi = 100;
	
        if( query("qi", me) <= (1400-lv) )
        {
               me->unconcious();
               delete_temp("teach_kh", me);
               return;
        }

        me->receive_wound("qi", qi);
        addn("neili", -(1600-lv), me);
        p=query("qi", me)*100/query("max_qi", me);
        tell_object(me, "( ��" + eff_status_msg(p) + ")\n\n");
        j ++;

        // ��ѧ����ħ����
        if (j >= 6 + random(2))
        {
              message_sort(HIW "�������ܼ�Хһ�����ֻص���ԭ�أ��ƺ���δ�뿪����\n" NOR, me);

              message_sort(HIW "����������δ���κ����ֻ����Ū���Լ���ָ�� ����\n" NOR, me);

              if (random(10) > 7)return;
              
              write(HIM "����ϸ��ζ�ղ��Ǿ��Ķ��ǵ�һĻ�����붫������ʩչ�ĸ�����ʽ����Ȼ����һ����̾��"
                        "�������Ƕ�Ȼ���� ����\n" NOR);
              if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
              if (me->can_improve_skill("dodge"))
                    me->improve_skill("dodge", 1500000);
              if (me->can_improve_skill("parry"))
                    me->improve_skill("parry", 1500000);
              me->improve_skill("martial-cognize", 1500000);

	      me->set_skill("pixie-jian", 0);
              me->delete_skill("pixie-jian");
              delete_temp("teach_kh", me);

              if( query("can_perform/pixie-jian/po", me) )
                       set("can_perform/kuihua-mogong/qiong", 1, me);
              me->set_skill("kuihua-mogong", 200 + (lv - 300) / 2 );
              tell_object(me, HIG "��ѧ���ˡ�����ħ������\n" NOR);
              
              me->save();
              
              me->interrupt_me(me);
              
              return;
        }

        remove_call_out("teach_kuihua");
        call_out("teach_kuihua", 3, me, lv);
                       
}

mixed ask_skill1()
{
        object me = this_player();
        
        if( query("gender", me) != "����" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/sheng", me) )
        {
               command("say �Ҳ����Ѿ���������������ô�������ң�");
               return 1;
        }
        command("nod");
        command("heihei");
        tell_object(me, HIR "\n�����������Ӻ������ˣ����ι����쳣���������Ʈ�������������ֻص���ԭ�ء�\n");
        command("say ������ˣ���");
        if (me->can_improve_skill("dodge"))
              me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/sheng", 1, me);
        tell_object(me, HIG "��ѧ���ˡ�������Ϣ����\n");

        return 1;
}

mixed ask_skill2()
{       
        object me = this_player();
        
        if( query("gender", me) != "����" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/qiong", me) )
        {
               command("say �Ҳ����Ѿ���������������ô�������ң�");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 250)
        {
               command("say �����ħ����������죬��������ȥ�����ϰ��");
               return 1;
        }
      
        command("heihei");
        tell_object(me, HIR "\n�������ܼ�Хһ������Ȼ������ǰ��һ�о�ֱϮ����գ��ٶ�֮�죬���˳��档\n" NOR);
        command("say ������ˣ���");
        command("say ���о�Ҫ���ڿ졢׼���ݣ�����ʵս����ϵ͵��˿��ܻ�һ��ʹ�������");
        command("say ����ȥһ��Ҫ�ڼ���ϰ��");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/qiong", 1, me);
        tell_object(me, HIG "��ѧ���ˡ������޾�����\n");

        return 1;
}

mixed ask_skill3()
{
        object me = this_player();
        
        if( query("gender", me) != "����" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/pixie-jian/po", me) )
        {
               command("say ��ȥ�ú���ϰ�ɣ�û�±������ң�");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 260)
        {
               command("say �����ħ����������죬��������ȥ�����ϰ��");
               return 1;
        }      
        command("heihei");
        tell_object(me, HIR "\n��������һ����Х��������Ȼ��ת���������Ǽ��ƺ���ǧ������룬���������� ����\n" NOR);
        command("say ���������޴����˶Է���Ԫ��ʹ������ڲ���ʩչ�κ��⹦��");
        command("say ����ȥһ��Ҫ�ڼ���ϰ��");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/pixie-jian/po", 1, me);
        tell_object(me, HIG "��ѧ���ˡ��ޱ��޼ʡ���\n");

        return 1;

}

mixed ask_skill4()
{
        object me = this_player();
        
        if( query("gender", me) != "����" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/tian", me) )
        {
               command("say �Ҳ����Ѿ���������������ô�������ң�");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 220)
        {
               command("say �����ħ����������죬��������ȥ�����ϰ��");
               return 1;
        }      
        command("heihei");
        command("say �����ˣ�");
        tell_object(me, HIR "\n��������Ĭ�˿���ħ�������α������ޱȣ������Ӳ�ͬ�ķ�λ����չ������У�\n" NOR);
        command("say �����Կ�ȡʤ���Կ��ƵС�");
        command("say ����ȥһ��Ҫ�ڼ���ϰ��");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/tian", 1, me);
        tell_object(me, HIG "��ѧ���ˡ��޷����졹��\n");

        return 1;
}


mixed ask_skill5()
{
        object me = this_player();
        string msg;

        if( query("gender", me) != "����" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/hui2", me) )
        {
               command("say �Ҳ����Ѿ���������������ô�������ң�");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 320)
        {
               command("say �����ħ����������죬��������ȥ�����ϰ��");
               return 1;
        }
        if( query("max_neili", me)<4000 )
        {
               command("say ��������Ϊ�����㣬��������ȥ���������");
               return 1;
        }

        // δѧ�����ʽ����һ��ѧϰ
        if( !query("can_perform/kuihua-mogong/hui", me) )
        {
               command("heihei");
               msg = HIW "�������ܶ�$N" HIW "˵�����ã���Ȼ�����Ҿʹ������ħ����߾���������ء���"
                     "������ط����У���һ�С�����ʽ�����ڶ��С���ؾ���������Ҫ��������ѧȫ������"
                     "�����������ء����������ȴ����һ�С�����ʽ����������ȥ���������õ���������"
                     "�ٴ��㡸��ؾ�������ֻҪ��ս����ʹ�� " HIR "perform sword.hui" HIW " ���Ҵ���"
                     "�Է������е������Ⱦͻ�������\n" NOR;

               message_sort(msg, me);
               tell_object(me, HIM "�������ܽ�������ʽ���Ŀھ��������㣡\n" NOR);
               command("say ��ȥ�ú���ϰ�ɣ�");
               tell_object(me, HIG "��ѧ���ˡ�����ʽ����\n" NOR);
               set("can_perform/kuihua-mogong/hui", 1, me);
               if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
               if (me->can_improve_skill("kuihua-mogong"))
                    me->improve_skill("kuihua-mogong", 1500000);
               me->improve_skill("martial-cognize", 1500000);
               
               return 1;
               
        }
        else // ׼��ѧϰ��ؾ�
        {
               if( query("can_perform/kuihua-mogong/hui1", me)<200 )
               {
                      command("shake");
                      command("say �㻹���Ƚ�������ʽ�����������������ɣ�");
                      return 1;
               }
               command("nod");
               msg = HIW "�������ܶ�$N" HIW "˵�������������㡸����ʽ���Ѿ����õú������ˣ�����"
                     "��ѧϰ����ؾ�����ʱ���ˣ���ɿ����ˡ���Ȼ�䶫����������һ�Σ���û���ټ���ɲ"
                     "�Ǽ䣬��ֻ���õض�ɽҡ��������ӿ������ԥ�䣬���������Ѵ�����������������"
                     "�����ͷ��\n" NOR;

               message_sort(msg, me);
               command("say �����ˣ�");
               command("say ��ȥ�ú���ϰ�ɣ�");
               tell_object(me, HIG "��ѧ���ˡ���ؾ�����\n" NOR);
               set("can_perform/kuihua-mogong/hui2", 1, me);
               if (me->can_improve_skill("force"))
                    me->improve_skill("force", 1500000);
               if (me->can_improve_skill("kuihua-mogong"))
                    me->improve_skill("kuihua-mogong", 1500000);
               me->improve_skill("martial-cognize", 1500000);
               
               return 1;
        }
}

mixed ask_skill6()
{
        object me = this_player();
        
        if( query("gender", me) != "����" && !query("special_skill/guimai", me) )
        {
               command("heng");
               this_object()->kill_ob(me);
               return 1;
        }
        if( query("can_perform/kuihua-mogong/fenshen", me) )
        {
               command("say �Ҳ����Ѿ���������������ô�������ң�");
               return 1;
        }
        if (me->query_skill("kuihua-mogong", 1) < 460)
        {
               command("say �����ħ����������죬��������ȥ�����ϰ��");
               return 1;
        }
 	if( query("max_neili", me)<6000 )
	{
                command("say ��������Ϊ�������޷������С�\n");
		return 1;
	}
        command("heihei");
        command("say �����ˣ�");
        tell_object(me, HIR "\n����������Цһ�����û�����������Ӱ�������ۻ����ң���������\n" NOR);
        command("say �����ˣ�");

        if (me->can_improve_skill("force"))
              me->improve_skill("force", 1500000);
        if (me->can_improve_skill("dodge"))
              me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("kuihua-mogong"))
              me->improve_skill("kuihua-mogong", 1500000);
        me->improve_skill("martial-cognize", 1500000);

        set("can_perform/kuihua-mogong/fenshen", 1, me);
        tell_object(me, HIG "��ѧ���ˡ�����Ӱ����\n");

        return 1;
}

void unconcious()
{
        ::die();
}