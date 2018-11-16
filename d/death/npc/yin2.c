#include <ansi.h>

inherit NPC;
inherit F_DEALER;

#define BADAO "/clone/lonely/book/badao"

void create()
{
        object ob;
        
        
        set_name("������", ({ "yin changsheng", "yin", "changsheng" }));
        set("title", HIR "ڤ���ز�����ǰ" NOR);
        set("nickname", HIB "����" NOR);
        set("shen_type", 1);

        set("gender", "����");
        set("age", 475);
        set("long","���������Ǹ������ţ����ڷᶼɽ�������ɣ����⡸��������\n");

        set("str", 60);
        set("int", 80);
        set("con", 60);
        set("dex", 60);

        set("max_qi", 9000000);
        set("eff_qi", 9000000);
        set("qi", 9000000);
        
        set("max_jing", 30000000);
        set("jing", 30000000);
        set("eff_jing", 30000000);
        set("max_jingli", 30000000); 
        set("jingli", 30000000);  

        set("neili", 2000000);
        set("max_neili", 150000);
        set("jiali", 600);
        set("combat_exp", 1100000000);

        set_skill("unarmed", 1000);
        set_skill("finger", 1000);
        set_skill("claw", 1000);
        set_skill("strike", 1000);
        set_skill("hand", 1000);
        set_skill("cuff", 1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 1000);
        set_skill("sword", 1000);
        set_skill("zuoyou-hubo", 1000);
         
        set_skill("jiuyin-shengong", 1000);
        set_skill("martial-cognize", 1200);
        set_skill("literate", 1000);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");
        
        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({                                
              // ������
              (: command("perform claw.zhua twice") :), 
              (: command("perform claw.xin") :), 
              (: command("perform shou twice") :), 
              (: command("perform quan twice") :),                                                                            
              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              (: exert_function, "roar" :),  
        }));    

        set("vendor_goods", ({
                "/d/death/obj/armor1",
        }));

        setup();
        carry_object(__DIR__"obj/cloth5")->wear();
}

void init()
{
        object me;

        me = this_player();
        
        if (! wizardp(me) && userp(me))
        {
                command("say �ߣ��ô�����������");
                this_object()->kill_ob(me);
        }
}


int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void unconcious()
{
        die();
}

void die()
{
        
        object ob;
        ob = find_object(BADAO);
        if (! ob) ob = load_object(BADAO);
        
        command("heng");
        command("say �����˼�Ҳ����������Ľ�ɫ���������и�ǣ����������ֽ̣�");
        
        if (! environment(ob) && random(10) == 1)
        {
                message_vision(HIW "��~~��һ���������������ϵ���һ���飬���ڵ��ϡ�\n" NOR, this_object());
                ob->move(environment(this_object()));
        }
        destruct(this_object());
        
        return;                                 
        
}

int accept_object(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))return 0;
        
        if( query("id", ob) != "tianyi shenjiu" )
        {
                return 0;
        }
        
        command("yi");

        if( !query("can_perform/badao/san-1", me) )
        {
                command("say �ⲻ�����������̫��л�ˣ��Ǻǣ�");
                command("tan");
                command("say ��ϧ������Ϊ��������Ҫ������ƣ�����ѧ�ᰢ�ǵ���һ�������ɣ�");
                return 0;
        }
        
        if( query("can_perform/badao/san-2", me) )
        {
                command("say лл���ϴε����ơ�");
                tell_object(me, HIR "��˵����������ͤ������һλ���ˣ�Ҫѧ���ǵ������������������ԡ�\n" NOR);
                return 0;
        }

        command("say �ⲻ����������𣡼�Ȼ�����ҵ���ʧ���Ѿõ����ƣ��ұ㴫�㰢�ǵ��ڶ�������������� ...");

        tell_object(me, HIG "��ϲ�㣬�����˰��ǵ��ڶ�����\n" NOR);
        tell_object(me, HIR "��˵����������ͤ������һλ���ˣ�Ҫѧ���ǵ������������������ԡ�\n" NOR);
        set("can_perform/badao/san-2", 1, me);

        me->save();
        
        destruct(ob);
        
        return 1;
}
