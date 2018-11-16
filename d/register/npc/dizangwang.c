// dizangwang

#include <ansi.h>

inherit NPC;

void greeting(object me);

void create()
{
        set_name("�ز���", ({ "dizang", }));
        set("long", "����ò���ϣ�����һ�����ۣ��������ƹ��˼����������ɡ�\n");
        set("gender", "����");
        set("age", 99);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 18);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        create_family("ڤ���ز�����ǰ", 1, "��ڤ֮��");
        set("title", HIR "��ڤ֮��" NOR);
}

void init()
{
        object me;

        ::init();
        me = this_player();
        if (! objectp(me) || ! userp(me))
                return;

        greeting(me);
}

void greeting(object me)
{
        object ob;

        if (! objectp(me) || environment(me) != environment(this_object()))
                return;

        if (! query("startroom") || base_name(environment()) != query("startroom"))
                return;

        if( undefinedp(query("born", me)) )
        {
                command("say"+query("name", me)+"�����������ǳ���ϴ�ѽ��(wash)��Ȼ��Ͷ̥ȥ�ɣ�");
        } else
        {
                if (wizardp(me))
                        command("heihei"+query("id", me));
                else
                {
                        command("kick"+query("id", me));
                        command("say �����ܵ���������ʲô��");
                        message_vision("$Nһ�Ű�$n�ߵ���Ӱ���١�\n\n",
                                       this_object(), me);
                        me->move(VOID_OB);
                        message_vision("\n$N������ϣ�����ƨ�����۽��˼�����\n",
                                       me);
                }
        }

        if( undefinedp(query("born", me)) && !objectp(present("book",me)) )
        {
                command("say �������է����δ�ض��ù�ء�����һ���飬����Կ�����(read book)");
                ob = new ("/clone/misc/newbie");
                ob->move(this_object());
                command("givebookto"+query("id", me));
        }
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
