#include <ansi.h>
inherit NPC;
inherit F_DEALER;

string ask_eguidao();

void create()
{
        set_name("�ŷ��", ({ "du fenge", "du", "fenge" }) );
        set("gender", "����" );
        set("age", 22);
        set("long", "�ŷ��һ����꣬��֪������������Ϊ���¡�\n");
        set("combat_exp", 400000);
        set("attitude", "friendly");
        set("no_get", "1");
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_temp("apply/damage", 25);

        set("inquiry", ([
                "����"   : "��˵���ܻ��ɺ��ɣ��ҵ���������һ�ء�\n",
                "���"   : "��ٹ���þ�û�������ҵĻ��ˣ���֪����������ô���ˣ�\n",
                "�����" : (: ask_eguidao :),
                
        ]));
        set("vendor_goods", ({
                "/clone/tattoo/face1",
                "/clone/tattoo/face2",
                "/clone/tattoo/face3",
                "/clone/tattoo/face4",
                "/clone/tattoo/face5",
                "/clone/tattoo/face6",
                "/clone/tattoo/face7",
                "/clone/tattoo/face8",
                "/clone/tattoo/face9",
                "/clone/tattoo/face10",
                "/clone/tattoo/face11",
                "/clone/tattoo/face12",
                "/clone/tattoo/face13",
                "/clone/tattoo/face14",
                "/clone/tattoo/face15",
                "/clone/tattoo/face16",
                "/clone/tattoo/face17",
                "/clone/tattoo/face18",
                "/clone/tattoo/face19",
                "/clone/tattoo/face20",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

// �����
// ��Ҫ100�ź���Ƥ
string ask_eguidao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "����������Ի�������������������ҿ��㻹���Ȼ�ȥ�ɡ�\n";

        if( query("reborn/times", me)<3 )
                return "�ߣ��ҿ�������ʲô����û�±������ң��߿���\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "�����书�Ѿ��������£���ϲ��ϲ��\n";

        if (me->query_skill("lunhui-sword",1))
                return "�ߣ��������ӣ���Ȼ���̰�ģ�\n";
                                
        // �Ƿ��Ķ���������
        if( !query("lunhui-sword_quest/read_huxian_book", me) )
        {
                    
                command("tan");
                return "������" HIM "����" NOR "�Ĺ�����\n";
        }
        
        // �Ѿ��������
        if( query("lunhui-sword_quest/eguidao/finish", me) )
                return "�Ǻǣ����ϴ��ҵ���Щ����Ƥ�ʵز������������ϲ����\n";

        // ��������
        if( !query("lunhui-sword_quest/eguidao/give_quest", me) )
        {
                command("tan");
                command("say �����ڼ�����ʮ�Ű׺�Ƥ�����ƺ�Ƥ���£����Ӧ�û�ܸ��˵ģ�");
                command("ke");
                command("say �ܰ�����������Ը��");
                tell_object(me, this_object()->name() + HIG "��������Ѽ�50�Ű׺�Ƥ���Ͽ�ȥ�ɣ�\n" NOR);
                set("lunhui-sword_quest/eguidao/give_quest", 1, me);
                me->save();
                return "�³�֮���һ������һ���������ܣ�";
        }
        
        // �������
        
        if (! objectp(ob_hlp = present("baihu pi", me)))
                return "��ô����50�Ű׺�Ƥ�Ѽ�������\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/lipi2")
                return "��ô����50�Ű׺�Ƥ�Ѽ�������\n";
 
        if (ob_hlp->query_amount() >= 50)
        {
                ob_hlp->add_amount(-50);
                if (ob_hlp->query_amount() < 1)destruct(ob_hlp);
        }
        else
        {
                return "��ô����50�Ű׺�Ƥ�Ѽ�������\n";
        }
        
        command("hehe");
        command("nod");
        command("say ��Ȼ����������æ���Ҿ͸�����һ������ ...");
        
        message_sort(HIC "\n$N" HIC "����ǰȥ����$n" HIC "��������˵�˼��䣬Ȼ�����ó�һ���飬ָָ��㣬"
                     "$n" HIC "��ס�ص�ͷ������üͷ������������ͷ��˼ ����\n���ã�$n" HIC "��Цһ�����ƺ�"
                     "�Ըղŵ�������������\n", this_object(), me);
                     
        
        tell_object(me, HIG "��ϲ�������ˡ��������������Ŀǰ�ȼ�Ϊ10����\n");
        me->set_skill("egui-dao", 10);
        set("lunhui-sword_quest/eguidao/finish", 1, me);
        
        return "�����ˣ�";
        
                
}

void init()
{       
        object ob; 

        ob = this_player();

        ::init();
        if (interactive(ob) && ! is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;

        say(CYN "�ŷ��ҡ��ҡͷ������λ" + RANK_D->query_respect(ob) +
            "�����ź��ܻ��ɺ�����\n" NOR);

        return;
}
