// ������

#include <ansi.h>

inherit NPC;

string ask_renjiandao();
string ask_shedong();
string ask_zhen();
string give_lhd();

void create()
{
        set_name("������", ({ "sai shenlong", "sai", "shenlong" }) );
        set("gender", "����");
        set("age", 999999);
        set("long", "�����ɷ���ǣ�üĿ��Ƿ���������������\n");
        set("attitude", "peaceful");
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);        
        set("neili", 600000);
        set("max_neili", 600000);
        set("jiali", 100);

        set("combat_exp", 1000000000);

        set("inquiry", ([
                "�߾�" : "�Ǿ�ͷ�߾��Ͷ����߾����ڣ�ֻ����ͯ��ͯŮ�ɽ���������\n",
                "ͯ��ͯŮ" : "��Ҫ�ҵ��߾������߾�����һ��ͯ��ͯŮ�������������ǣ��˷���Υ�˵���\n" +
                             "������Ҳ��������ʦʩ��������ͯ��ͯŮ���Ž��������ġ�\n",
                "�˼��"   : (: ask_renjiandao :),   
                "�߾���"   : (: ask_shedong :),     
                "�߾���Ƭ" : "��������߾�ʱ������һ�����ʵ����߾���Ƭ��\n",
                "�桤�����ֻ�" : (: ask_zhen :),
                 //"�ֻص�"   : (: give_lhd :),
        ]));

        set_skill("unarmed", 2000);
        set_skill("sword", 2000);
        set_skill("blade", 2000);
        set_skill("staff", 2000);
        set_skill("hammer", 2000);
        set_skill("club", 2000);
        set_skill("whip", 2000);
        set_skill("dagger", 2000);
        set_skill("throwing", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("force", 2000);
        set_skill("lingbo-weibu", 2000);
        set_skill("lunhui-sword", 2000);  
        set_skill("never-defeated", 2000);  
        set_skill("martial-cognize", 2000);

        map_skill("sword", "lunhui-sword");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "lunhui-sword");
        map_skill("dodge", "lingbo-weibu");
        map_skill("force", "lunhui-sword");

        prepare_skill("unarmed", "never-defeated"); 
        
         set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              (: perform_action, "sword.xiuluo" :),
              (: perform_action, "sword.lan" :),
              (: perform_action, "sword.zhen" :),              
              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "sword" :),                             
        }));
        
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();

}

string ask_shedong()
{
        string msg;
        
        command("say ���߾������������ߣ����δ��۸��ӣ�һ��С�ľͻ���·��");
        command("say ���Ҫ���߶���������Ϥ���߾����ĵ�ͼ�ɣ�");
        
        write(@LONG
                              ������
                                |
                              ���߿�
                                |
                              ���߿�
                                |
                              ���߿�
                                |
                              ���߿�               
                                |
              ���߿ߡ����߿ߡ���������out���߶���
                                |
                              ���߿�
                                |
                              ���߶�
                                |
                              ǧ�߶�                             
                                |
                              ǧ�߶�
                                |
                              ǧ�߶�
                                |
                              ǧ�߶�����ͷ�߶�����ͷ�߶�
                                                   |
                                                �߾�����
                                                   |
                                                 �߾���
LONG);                                                 
        return "��ô������������\n";
        
}

string give_lhd()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
      if( query("reborn/times", me) < 3 ) 
                return "�߿����߿���û������æ��\n";
        
        if( query("scborn/get_lhd_sai", me) )
                return "�ֻص��㲻���Ѿ���ȡ����\n";
        
        if( query("scborn/total_lunhui_point", me) >= 18 )
                return "����ֻص��Ѿ��ﵽ18���ˣ��޷�����ȡ��\n";
        
        if( query("scborn/total_lunhui_point", me)+3>18 )
                return "�������ȡ�ֻص�ͻᳬ��18���ˣ��޷�����ȡ������BUG�����뱾վ����Ա��ϵ��\n";
                                
        // �Ѿ��������
        if( query("scborn/lunhuidian/finish", me) )
                return "���������ܴ��߾������õ���Ƭ������֮���٣�������������һ����\n";

        // ��������
        if( !query("scborn/lunhuidian/give_quest", me) )
        {
                command("look"+query("id", me));
                command("say ���ֻص��쳣���ֻ�����ߣ����������֤�����ҿ����ֻص��Ե����ϡ�");
                command("say ǰ����Զ����һ���߾�����������ǰ�ҽ���������ѹ�ڴˣ�ʹ֮�޷����˼��˷����ˡ�");
                command("ke");
                command("say ��������ܴ�������ȡ��50Ƭ�߾���Ƭ���Ǿ�֤�����±�Ϊ���ߡ�");
                command("say �������߾���ǧ�����������и�����Ҫ������ˣ�");
                
                tell_object(me, this_object()->name() + HIG "������߾�����ȡ����Ƭ��֤���������ߡ�\n" NOR);
                set("scborn/lunhuidian/give_quest", 1, me);
                me->save();
                return "��ô�����е���ȥ��";
        }
        
        // �������        
        if (! objectp(ob_hlp = present("shejing linpian", me)))
                return "��ô����50Ƭ�߾���Ƭȡ������\n";
                
        if (base_name(ob_hlp) != "/d/shenlong/npc/obj/linpian")
                return "��ô����50Ƭ�߾���Ƭȡ������\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hlp) >= 50)
        {
                for (i = 1; i <= 50; i++)
                {
                        destruct(ob_hlp);
                        ob_hlp = present("shejing linpian", me);
                }
        }
        else
        {
                return "��ô����50Ƭ�߾���Ƭȡ������\n";
        }
        
        command("hehe");
        command("nod"+query("id", me));
        command("say ������Ȼ�����ߣ����ֻص�ͷ��͸����ˡ�");        
                             
        tell_object(me, HIG "��ϲ������ 3 ���ֻص㡣\n");

        set("scborn/lunhuidian/finish", 1, me);
        addn("scborn/cur_lunhui_point", 3, me);
        addn("scborn/total_lunhui_point", 3, me);
        set("scborn/get_lhd_sai", 1, me);

        me->save();
        
        return "����������";        
}

string ask_renjiandao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "����������Ի������������˼�����ҿ��㻹���Ȼ�ȥ�ɡ�\n";

        if( query("reborn/times", me) < 3 )
                return "�˴����Ƕ���פ��֮�أ�����������ȥ�ɡ�\n";
                
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return "�ߣ��������ӣ���Ȼ���̰�ģ�\n";

        if (me->query_skill("lunhui-sword",1))
                return "�ߣ��������ӣ���Ȼ���̰�ģ�\n";
                
        if (me->query_skill("renjian-dao", 1))
                return "��ô������������������\n";
                
        command("nod");
        command("say ǧ�����������ڴ������߾������ⶾ���ܲ����ǵ���֮���ܹ����롣");
        command("look "+query("id", me));
        command("say �������ճ�Ⱥ����Ȼ���ˣ�����Ҳ��һ��Ե�֣��⡸�˼�����ʹ���ɣ�");

        message_sort(HIC "\n$N" HIC "����ǰȥ����$n" HIC "��������˵�˼��䣬Ȼ�����ó�һ���飬ָָ��㣬"
                     "$n" HIC "��ס�ص�ͷ������üͷ������������ͷ��˼ ����\n���ã�$n" HIC "��Цһ�����ƺ�"
                     "�Ըղŵ�������������\n", this_object(), me);

        command("nod "+query("id", me));

        tell_object(me, HIG "��ϲ�������ˡ��˼����������Ŀǰ�ȼ�Ϊ10����\n" NOR);
        me->set_skill("renjian-dao", 10);
        
        return "����Ϊ֪�ɣ�";
        
                
}
int accept_kill(object me)
{
        command("heng");
        command("say �ܺã�");
        return 1;
}

void unconcious()
{
       die();
}

void die()
{
        command("chat �����ܣ������� ����");
        destruct(this_object());
}

int accept_object(object me, object ob)
{

        if (base_name(ob) != "/clone/lonely/book/dugubook")
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }


        destruct(ob);
        return 1;
}

// �桤�����ֻ�
string ask_zhen()
{
        object *obs; 
        object ob;
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("reborn/times", me) < 3)
                return "�߿����߿���û������æ��\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return "�����书�Ѿ��������£��α����̰��?\n";

        if( query("max_neili", me)<10000 )
                return "���������Ϊ�����������һ����ܴ��㡣\n";

        if ((int)me->query_skill("buddhism", 1) < 200)
                return "��������ķ����򲻹��������һ����ܴ��㡣\n";

        if ((int)me->query_skill("lunhui-sword", 1) < 900)
                return "�������ֻؽ���򲻹��������һ����ܴ��㡣\n";

        // �Ѿ��������
        if( query("lunhui-sword_quest/zhen/finish", me) )
                return "���������ܴ��߾������õ���Ƭ������֮���٣�������������һ����\n";
        
        /*
        // ����ֻص�        
        if( query("scborn/cur_lunhui_point", me)<6 && !query("thborn/ok", me) )
                return "��ϧ�������ֻص㲻�㣬�޷����򵽴��С�\n";
        */
        
        // ��������
        if( !query("lunhui-sword_quest/zhen/give_quest", me) )
        {
                command("look "+query("id", me));
                command("say ѧ�����ߣ���Ϊ���ߣ����������֤�����ҿ������б��������ܡ�");
                command("say ǰ����Զ����һ���߾�����������ǰ�ҽ���������ѹ�ڴˣ�ʹ֮�޷����˼��˷����ˡ�");
                command("ke");
                command("say ��������ܴ�������ȡ��10Ƭ�߾���Ƭ���Ǿ�֤�����±�Ϊ���ߡ�");
                command("say �������߾���ǧ�����������и�����Ҫ������ˣ�");
                
                tell_object(me, this_object()->name() + HIG "������߾�����ȡ����Ƭ��֤���������ߡ�\n" NOR);
                set("lunhui-sword_quest/zhen/give_quest", 1, me);
                me->save();
                return "��ô�����е���ȥ��";
        }
        
        // �������        
        if (! objectp(ob_hlp = present("shejing linpian", me)))
                return "��ô����10Ƭ�߾���Ƭȡ������\n";
                
        if (base_name(ob_hlp) != "/d/shenlong/npc/obj/linpian")
                return "��ô����10Ƭ�߾���Ƭȡ������\n";
        
        obs = all_inventory(me); 
        obs = filter_array(obs, (: base_name($1) == "/d/shenlong/npc/obj/linpian" :)); 
        if( sizeof(obs) < 10 ) 
                return "��ô����10Ƭ�߾���Ƭȡ������\n";

        for (i = 0; i < 10; i++) 
        { 
                ob = obs[i]; 
                obs[i] = 0; 
                destruct(ob); 
        }
        
        command("hehe");
        command("nod "+query("id", me));
        command("say ������Ȼ�����ߣ��⡸�桤�����ֻء��ʹ����ˣ���������� ����");
        
        message_sort(HIC "\n$N" HIC "����ǰȥ����$n" HIC "��������˵�˼��䣬Ȼ�����ó�һ���飬ָָ��㣬"
                     "$n" HIC "��ס�ص�ͷ������üͷ������������ͷ��˼ ����\n���ã�$n" HIC "��Цһ�����ƺ�"
                     "�Ըղŵ�������������\n", this_object(), me);
                             
        tell_object(me, HIG "��ϲ��ѧ���ˡ��桤�����ֻء���\n");
        set("can_perform/lunhui-sword/zhen", 1, me);
        set("lunhui-sword_quest/zhen/finish", 1, me);
        
        /*
        // �۳��ֻص�
        if( !query("thborn/ok", me) )
                addn("scborn/cur_lunhui_point", -6, me);

        // ���ÿ۳��ֻص�ĳ���
        if( !query("thborn/ok", me) )
                set("scborn/perform_zhen_saishenlong", 1, me);
        */
        me->save();
        
        return "����������";
        
                
}
