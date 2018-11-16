// guxu.c ����

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("�������", ({ "guxu daozhang", "guxu", "daozhang" }));
        set("long","����������ҵĵ��ӹ��������\n��������ʮ�꣬�����䵱�ɵ����¡�\n");
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 22);
        set("int", 25);
        set("con", 26);
        set("dex", 23);

        set("max_qi", 2800);
        set("max_jing", 1400);
        set("neili", 3300);
        set("max_neili", 3300);
        set("jiali", 50);

        set("combat_exp", 500000);
        set("score", 28000);

        set_skill("force", 120);
        set_skill("yinyun-ziqi", 120);
        set_skill("dodge", 100);
        set_skill("tiyunzong", 100);
        set_skill("strike", 110);
        set_skill("wudang-zhang", 110);
        set_skill("parry", 120);
        set_skill("sword", 100);
        set_skill("wudang-jian", 100);
        set_skill("taoism", 70);
          set_skill("literate", 80);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("env/wimpy", 60);
        create_family("�䵱��", 3, "����");
        set("inquiry", ([
                "���¾�" : (: ask_me :),
                "jing"   : (: ask_me :),
                "book"   : (: ask_me :),
        ]));

        set("book_count", 1);

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}

/*
void init()
{
        object me = this_player();

        ::init();

        if( query("family/family_name", me) == "�䵱��" && 
                query("wudang/offerring", me)>query("age", me)*2 )
                set_temp("mark/����", 1, me);
}
*/

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return;
        }
        command("say �ðɣ�ƶ�����������ˡ������䵱�������������ƣ�");
        command("recruit "+query("id", ob));
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "�䵱��")
                return RANK_D->query_respect(this_player()) +"�뱾��������������֪�˻��Ӻ�̸��";
        if (query("book_count") < 1)
                return "�������ˣ����ɵĵ����澭���ڴ˴���";
        addn("book_count", -1);
        ob = new(BOOK_DIR"daodejing-ii");
        ob->move(this_player());
        return "�ðɣ��Ȿ�����¾������û�ȥ�ú����С�";
}

void reset()
{
        set("book_count", 1);
}
