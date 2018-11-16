// dizangwang

#include <ansi.h>

inherit NPC;

void greeting(object me);

void create()
{
        set_name("�̹�", ({ "pan gu", }));
        set("long", "����ò���ϣ�����һ�����ۣ������ǿ���ٵص����ɡ�\n");
        set("gender", "����");
        set("age", 999);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 30);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/weapon/bigaxe.c")->wield();
        create_family("����֮��", 1, "���֮��");
        set("title", HIY "����֮��" NOR);
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
                command("say "+query("name", me)+"������ѡ��(choose)�ý�ɫ�Ը�Ȼ��Ͷ̥ȥ�ɣ�");
                tell_object(me, CYN "�ر���ʾ����Ȼ�Ը������ĸ����ɲ�û��Ӱ�죬��������Ӱ����ѧĳЩ�书��\n" NOR);
                tell_object(me, HIY "���ֵ�ʦ�������� help start ����֪��Ը����������Ƽ����Ը�(��ʦ֮ǰ�����ڱ�����������Ը�)\n" NOR);
                tell_object(me, "������ѡ��(choose)�Ľ�ɫ�Ը����£�\n"
                            HIC "1" NOR ".��������  "
                            HIC "2" NOR ".������  "
                            HIC "3" NOR ".�ĺ�����  "
                            HIC "4" NOR ".���ռ�թ ("
                            HIC "choose 1" NOR "-" HIC "4" NOR ")\n\n");

        } else
        {
                if (wizardp(me))
                        command("heihei "+query("id", me));
                else
                {
                        command("kick "+query("id", me));
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
                command("give book to "+query("id", me));
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
