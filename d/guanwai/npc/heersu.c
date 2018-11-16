#include <ansi.h>
inherit KNOWER;

string ask_me();

void create()
{
        set_name("�ն���", ({ "he ersu", "he", "ersu", "heersu" }));
        set("long", "����һ���ϲοͣ�����һƶ��ϴ��\n");
        set("title", WHT "�ο�" NOR);
        set("age", 65);
        set("combat_exp", 300);
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("attitude", "friendly");
        set("inquiry", ([
                "�˲�" : (: ask_me :),
                "ɽ��" : (: ask_me :),
        ]));

        if (random(10) > 5)
                set("count", 1);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/stick")->wield();
}

string ask_me()
{
        object me = this_player();

        if (query("count") < 1)
        {
                return "�ٺ٣����´������ɣ�����������Ҳû����\n";
        } else
        if( query_temp("tmark/��", me) )
        {
                return "�㵽�״�������Щʲô��\n";
        } else
        {
                set_temp("tmark/��", 1, me);
                return "������������˿���ɽ�Σ��������Ƚ�Ǯ��\n";
        }
}

int accept_object(object who, object ob)
{
        object obj;

        if( !query("money_id", ob) )
        {
                write(CYN "�ն��ղ����˵��������������ʲô��\n" NOR);
                return 0;
        }

        if (query("count") < 1)
        {
                write(CYN "�ն���ҡͷ��������´ΰɣ�����������Ҳû����\n" NOR);
                return 0;
        }

        if( !query_temp("tmark/��", who) )
        {
                write(CYN "�ն����ɻ�������ֲ�����ؤ��û�¸���Ǯ������\n" NOR);
                return 0;
        }

        if (ob->value() < 100000)
        {
                write(CYN "�ն�����Ц�����ٺ٣�������ô��Ǯ�ģ�\n" NOR);
                return 0;
        }

        obj = new("/clone/fam/pill/renshen1");
        obj->move(this_object());

        addn("count", -1);
        command("givebainianrenshento"+query("id", who));
        write(CYN "�ն���˵������Ȼ��������ۣ���������˲ξ͸����ɡ�\n" NOR);
        return 1;
}
