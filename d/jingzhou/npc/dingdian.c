// This program is a part of NT MudLIB

#include <ansi.h>
inherit NPC;

int ask_skill1();
int ask_skill2();
void destroying(object, object);

void create()
{
        set_name("����", ({ "ding dian", "ding" }));
        set("long",
                "����������ף�ͷ��������ֱ���������������ò�������ֱ��ͬ��ɽ�е�Ұ�ˡ�\n");
        set("gender", "����");
        set("age", 35);

        set_skill("unarmed", 120);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("ding-dodge", 120);
        set_skill("ding-force", 120);
        set_skill("ding-unarmed", 120);
        set_skill("shenzhaojing", 300);
        map_skill("force", "shenzhaojing");
        map_skill("parry", "shenzhaojing");
        map_skill("unarmed", "shenzhaojing");
        map_skill("dodge","ding-dodge");
        prepare_skill("unarmed","shenzhaojing");
        set("max_neili",2000);
        set("neili",2000);
        set("jiali",100);

        set("combat_exp", 600000);
        set("shen_type", 1);
        set("chat_chance", 10);
        set("chat_msg", ({
                "��������̾��һ��������̾Ϣ�У��������ˡ�����֮�⡣\n",
                "������ǹ���һ˿΢Ц������Զ����¥ɴ������һ���ʻ���\n",
                "�������������ô�����ǣ�������ģ��ѵ������ѵ������˲���\n",
                "�����૵������������˲���Ҳ���������������\n",
        }) );
        set("inquiry", ([
                "��˪��" : "������������Ȼ��ָ��ָ��������С¥�Ĵ��ڣ�ɶҲ��˵�ˡ�\n",
                "����"   : (: ask_skill1 :),
                "�ƾ�"   : (: ask_skill2 :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

int accept_object(object me, object obj)
{
        object key;
        if( query("id", obj) == "green flower" && 
             filter_color(query("name", obj),1) == "��������"){
                message("vision",me->name()+"������һ���̾ջ���\n",environment(me),
                        ({me}));
                key = new("/clone/book/shenzhaojing");
                if (!key){
                        command("say ���Ѿ����˰������˪���ˣ�����������ˡ�");
                        return 0;
                }

                command("touch"+query("id", me));
                command("say ��λ"+RANK_D->query_respect(me)+"��˪���������ŵİɡ�");
                key->move(me);
                addn("book_count", -1);
                message_vision("$n�ݸ�$Nһ���顣\n", me, this_object() );
                command("say �Ȿ����������������õġ����վ���������ȥ����˪���ɡ�");
                command("rumor"+query("name", me)+"Ū����һ�����վ���");
                remove_call_out("destroying");
                call_out("destroying", 1, this_object(), obj);
                return 1;
        }
        if( query("id", obj) == "green flower" && 
            filter_color(query("name", obj),1) == "��ˮ�̲�" )
        {
                message("vision",me->name()+"������һ���̾ջ���\n",environment(me),
                        ({me}));
                message_vision("����ͬ��ָ��$NһЩ�书�����⡣\n",me);
                addn_temp("mark/��", 1000, me);
                return 1;
        }
        return 0;
}

void destroying(object me,object obj)
{
        destruct(obj);
        return;
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/��", ob) )
                return 0;
        addn_temp("mark/��", -1, ob);
        return 1;
}

int ask_skill1()
{
        object ob = this_object();
        object who = this_player();

        if( !query_temp("mark/��", who))return 0;
        if (!who->query_skill("shenzhaojing",1)) return 0;
        if( query("can_perform/shenzhaojing/wakeup", who))return 0;
        if (who->query_skill("shenzhaojing",1) < 100)
        {
                command("say ������վ������������ߣ���ѧѧ�ɡ�");
                return 1;
        }
        command("sign");
        command("say ��֪��ѧ�����վ��Ǹ��ǻ��ˡ�Ҳ�գ�����ȥ�ɡ�");
        tell_object(who,HIC"���������������˵�˼����˹��Ŀھ����㼱æ����һһ���¡�\n"NOR);
        tell_object(who,HIC "��ѧ���ˡ����ѡ���\n" NOR);
        set("can_perform/shenzhaojing/wakeup", 1, who);
        return 1;
}
int ask_skill2()
{
        object ob = this_object();
        object who = this_player();

        if( !query_temp("mark/��", who))return 0;
        if (!who->query_skill("shenzhaojing",1)) return 0;
        if( query("can_perform/shenzhaojing/jingheal", who))return 0;
        if (who->query_skill("shenzhaojing",1) < 50)
        {
                command("say ������վ������������ߣ���ѧѧ�ɡ�");
                return 1;
        }
        command("sign");
        command("say ��֪��ѧ�����վ��Ǹ��ǻ��ˡ�Ҳ�գ�����ȥ�ɡ�");
        tell_object(who,HIC"���������������˵�˼����˹��Ŀھ����㼱æ����һһ���¡�\n"NOR);
        tell_object(who,HIC "��ѧ���ˡ��ƾ�����\n" NOR);
        set("can_perform/shenzhaojing/jingheal", 1, who);
        return 1;
}
