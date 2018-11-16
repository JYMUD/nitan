// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

string ask_jiu();

void create()
{
        set_name(HIW "�ƽ���" NOR, ({ "jiujian xian", "jiujian", "xian" }));

        set("long", HIW "���˺������죬�ѵ���ɽ�ɵľƽ��ɣ��������������\n" NOR);

        set("gender", "����");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("sword", 2500);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);
        set_skill("medical", 2500);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "�����ɵ�"               :   "�ⲻ��������ĵط����ҿ��㻹�ǿ��߰ɡ�\n",
                "��ɽ��"                 :   "��Ҳ��˵���𣬿������������Ǻǡ�\n",
                "��÷��"                 :   (: ask_jiu :),
        ]));
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

string ask_jiu()
{
        object me = this_player();
        object ob_xy, ob_xnj, ob_hbk, ob_qmj;
        int i;

        // ��Ҫ����
        /*
         ��÷     2
         ������� 1
         �ջ�     1
       */
        command("nod");
        command("say ��Ȼ��Ϊ����÷�ƶ������Ҿƽ��ɵ�Ȼ�岻�ݴǡ�");
        command("say ����������÷����ҪһЩ����Ĳ��ϣ�");
        message_vision(HIM  + "\n"
                       "��÷     2 �� \n"
                       "������� 1 ��\n"
                       "�ջ�     1 ��\n\n" NOR, this_object());
        command("say �������Щ���϶������˵Ļ��������Ұɣ�");
        command("say �����������ˣ�������ǵ�һ���ұ�����������÷�ƣ��ٺ� ����");
        
        if (! me->query_temp("want_make_qingmeijiu"))
        {
                me->set_temp("want_make_qingmeijiu", 1);
                return "��ô��������㿼�Ǻ��ˣ��������ң�\n";
        }
                
                        
        // ��Ҫ��÷
        if (! objectp(ob_xy = present("penglai qingmei", me)))
                return "�����û������÷�ɣ�\n";                        
        if (base_name(ob_xy) != "/d/penglai/obj/qingmei")
                return "�����û������÷�ɣ�\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_xy) >= 2)
        {
                for (i = 1; i <= 2; i++)
                {
                        //destruct(ob_xy);
                        ob_xy = present("penglai qingmei", me);
                }
        }
        else
        {
                return "��ô����2����÷��������\n";
        }
        
        
        // ��Ҫ�������
        if (! objectp(ob_xnj = present("penglai pantao", me)))
                return "�����û����������Ұɣ�\n";                        
        if (base_name(ob_xnj) != "/d/penglai/obj/pantao")
                return "�����û����������Ұɣ�\n";

        if ("/adm/daemons/stored"->get_ob_amount(me, ob_xnj) >= 1)
        {
                for (i = 1; i <= 1; i++)
                {
                        //destruct(ob_xy);
                        ob_xnj = present("penglai pantao", me);
                }
        }
        else
        {
                return "��ô����1��������ұ�������\n";
        }        

        // ��Ҫ�ջ�
        if (! objectp(ob_hbk = present("penglai juhua", me)))
                return "�����û����ջ��ɣ�\n";                        
        if (base_name(ob_hbk) != "/d/penglai/obj/juhua")
                return "�����û����ջ��ɣ�\n";

        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hbk) >= 1)
        {
                for (i = 1; i <= 1; i++)
                {
                        //destruct(ob_xy);
                        ob_hbk = present("penglai juhua", me);
                }
        }
        else
        {
                return "��ô����1��ջ���������\n";
        }

        // ���Ĳ���      
        ob_xy =  present("penglai qingmei", me);
        destruct(ob_xy);
        ob_xy =  present("penglai qingmei", me);
        destruct(ob_xy);
        ob_xnj = present("penglai pantao", me);
        destruct(ob_xnj);
        ob_hbk = present("penglai juhua", me);        
        destruct(ob_hbk);
        
       
        
        command("say ��Ȼ����϶������ˣ�����÷�ƾ��ɱ��������ưɡ�");
        
        message_sort(HIR "\n$N" HIR "������ȡ��һ����«�������ֲ��ϷŽ���«�У�Ȼ������۾�������"
                     "Ĭ����ʲô���ƺ�����ʩչ���� ���� ��̣�һ�ɾ���Ӻ�«��Ʈ������������÷���ѳɡ�\n\n" NOR, this_object(), me);

        command("say ���˺��ˣ��ܾ�û���ŵ�����÷�Ƶ���ζ�ˡ�");
        
        if (! me->query("penglai/qingmeijiu_quest/ok"))
        {
                command("say ���������Ǹ������ˣ����ǵ�һ������������÷�ƺ���ƶ��ɱ����ɴ�ΪƷ���� ����");
                message_vision(HIC "˵�գ�$N" HIC "����һ��������«�����÷�ƺ��˸����⡣\n" NOR, this_object());
                command("haha");
                command("say �þƣ��þư���");
                me->set("penglai/qingmeijiu_quest/ok", 1);
                me->delete_temp("want_make_qingmeijiu");
                me->save();
                return "�����㲻�õ��ģ��´����ƺú��ұ㽫�������ˣ����� ~~~";
        }
        else
        {
                ob_qmj = new("/d/penglai/obj/qingmeijiu");
                ob_qmj->move(me, 1);
                message_vision("$N" NOR "�ó�һƿ��÷�Ƹ�$n��\n" NOR, this_object(), me);
                log_file("penglai_quest", me->query("id") + " ������÷�Ƴɹ���\n");
        }
        
        tell_object(me, HIG "��ϲ�㣬�������÷�ƣ��Ͻ�������·���˰ɣ�\n" NOR);        
        
        me->delete_temp("want_make_qingmeijiu");
        
        me->save();
        
        return "С�ģ������ˣ���ƿ��Ƿ���Ʒ�������ģ�\n";
}

void unconcious()
{
        die();
}
