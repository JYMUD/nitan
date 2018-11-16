// dizangwang

#include <ansi.h>
#define QILIN_XUE    "/d/death/obj/qilinxue"

inherit NPC;

mixed ask_xue();
mixed ask_reborn();

void create()
{
        set_name("�ز���", ({ "dizang", }));
        set("long", "����ò���ϣ�����һ�����ۣ��������ƹ��˼����������ɡ�\n");
        set("gender", "����");
        set("age", 99);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 18);
        set("attitude", "peaceful");
        set("str", 31);
        set("int", 39);
        set("con", 34);
        set("dex", 36);

        set("max_qi", 9999);
        set("max_jing", 9999);
        set("neili", 9999);
        set("max_neili", 9999);
        set("jiali", 800);

        set("combat_exp", 50000000);
                
        set_skill("unarmed", 1500);
        set_skill("finger", 1500);
        set_skill("parry", 1500);
        set_skill("dodge", 1500);
        set_skill("force", 1500);
        set_skill("sword", 1500);
        set_skill("count", 1500);
        set_skill("kuihua-mogong", 1500);
        set_skill("martial-cognize", 1500);
        set_skill("literate", 220);

        map_skill("parry", "kuihua-mogong");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        prepare_skill("finger", "kuihua-mogong");     
           
        set("inquiry", ([
                "����ѥ"   : (: ask_xue :),
                "ת��"     : (: ask_reborn :),                
                "����"     : (: ask_reborn :),
                "ת��"     : (: ask_reborn :),
                "ת������" : (: ask_reborn :),
        ]));
        
        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/misc/spin")->wield();
                
        create_family("ڤ���ز�����ǰ", 1, "��ڤ֮��");
        set("title", HIR "��ڤ֮��" NOR);
}

int attempt_apprentice(object ob)
{
        if( !query("born", ob) )
        {
                command("say ���Ͷ̥ȥ��������Ϲ����ʲô��");
                return 0;
        }

        command("say ��������һ�߶�ȥ��");
}

mixed ask_xue()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( !query("hell_quest/������", me) )
                return "������ѥ���ҵı�����������ʲô��";

        ob = find_object(QILIN_XUE);
        if (! ob) ob = load_object(QILIN_XUE);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "����ѥ�������������ô����ô�����������أ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���Ѿ�������ѥ�Ѿ����ȥ�ˡ�";

                        return "����ѥ��������"+query("name", owner)+
                               "���У���ȥ�����һ����ɡ�";
        }

        ob->move(this_object());
        message_vision("$N���ͷ�������ã���Ȼ����Ϊ���Ϸ��������֮�£��Ϸ�ͽ����ɣ���\n", 
                       this_object(), me);
 command("give boots to "+query("id", me));
        return 1;
}

mixed ask_reborn()
{
        object who;
        
        who = this_player();

        if( !query("reborn_lunhui", who)){
                message_vision( BLU "$N" BLU "��$n" BLU "һ���֣���������ת���ȹ���������������һ����˵��\n", 
                                this_object(), who );
                return 1;
        }      
          
        if( query("betrayer", who) )
        {
                message_vision("$N��$nŭ�����㻹���Ȱ�����ʦ�����еľ�������������\n",
                               this_object(), who);
                return 1;
        }

        message_vision( BLU "$N" BLU "���ͷ�������ã���Ȼ�㴳���ظ��Ŀ��飬�Ϸ�����������ֱ��������棡��\n"
                        BLU "$N" BLU "����һ�У�ͻȻ����һ�����磬��$n" BLU "�����������硣\n" NOR, 
                        this_object(), who );                            
                 
        who->move("/d/reborn/heaven");
        set("startroom", "/d/reborn/heaven", who);
        return 1;
}
