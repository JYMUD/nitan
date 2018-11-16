// qiao-feng.c

#include <ansi.h>;
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_MANAGER;
string ask_me();

void create()
{
        set_name("�Ƿ�", ({"qiao feng", "feng", "qiao"}));
        set("nickname", "���Ƿ�");
        set("gender", "����");
        set("age", 29);
        set("long",
"������ؤ���ʮ�ΰ������ڽ��������������Ľ�ݸ�����Ϊ�����Ƿ壬��Ľ�ݡ���
����һ����ͨ�Ĵֲ����ӣ�������һ���������һϵ��������������࣬���
ʮ�ֿ��࣬����һ�������ֿ���ʮ�����Ի������ӣ�˫Ŀ��磬��������\n");
        set("attitude", "peaceful");
        set("class", "beggar");
         set("beggarlvl", 10);

        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 300);

        set("combat_exp", 3000000);
        set("score", 200000);
        set("shen", 100000);

        set_skill("force", 200);             // �����ڹ�
        set_skill("huntian-qigong", 200);    // ��������
        set_skill("unarmed", 200);           // ����ȭ��
        set_skill("dodge", 200);                   // ��������
        set_skill("xiaoyaoyou", 300);        // ��ң��
        set_skill("parry", 200);             // �����м�
        set_skill("strike", 200);            // �����Ʒ�
        set_skill("dragon-strike", 300);   // ����ʮ����
        set_skill("hand", 200);              // �����ַ�
        set_skill("suohou-hand", 300);       // ����������
        set_skill("blade", 200);             // ��������
        set_skill("liuhe-dao", 300);       // �������ϵ�
        set_skill("staff", 200);             // �����ȷ�
        set_skill("fengmo-zhang", 300);      // ��ħ�ȷ�
        set_skill("stick", 200);             // ��������
        set_skill("dagou-bang", 300);        // �򹷰���
        set_skill("begging", 100);           // �л�����
        set_skill("checking", 100);          // ����;˵
        set_skill("training", 100);          // Ԧ����
        set_skill("lianhua-zhang",85); // ������

        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("hand",  "suohou-hand");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("blade", "liuhe-dao");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        map_skill("staff", "fengmo-zhang");
//        prepare_skill("hand",  "suohou-hand");
        prepare_skill("strike", "dragon-strike");

        set("inquiry",([
                "�ؼ�"     : (: ask_me :),
                "��������" : (: ask_me :),
        ]));
        set("book_count", 1);
        //set("party/party_name", HIC"ؤ��"NOR);
        //set("party/rank", HIR"����"NOR);
        //set("party/level", 10);
        create_family("ؤ��", 10, "����");

        setup();

        carry_object(__DIR__"obj/lvyv_bang")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
//      carry_object(BOOK_DIR"stick_book")->wear();
}

/*
void init()
{
         object ob;
        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_qiecuo","qiecuo");
}


void greeting(object me)
{
               mapping myfam;
        myfam=query("family", me);
        if( (myfam["family_name"] == "ؤ��") && (!me->query_skill("huntian-qigong",1)) && (query("combat_exp", me)>500000) )
        {
                command("say �㾹�ҷ��������ķ��������������ȥ�ɣ�");
                command("expell"+query("id", me));
        }

}
*/

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        command("sigh");
        command("say �߿����Ҳ���ͽ��");
        return;

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                command("say ��Ľ������鲻�������������λ����ѧϰ�ɡ�");
                return;
        }

        if( query("shen", ob)<30000 )
        {
                command("say ����Ϊؤ����ӣ���Ȼ�������£�");
                return;
        }

        if( query("family/beggarlvl", ob)<5 )
        {
                command("say ���ڱ���ĵ�λ̫�ͣ����������λ����ѧϰ�ɡ�");
                return;
        }

        if ((int)ob->query_str() < 26)
        {
                command("say �ҵ������Ը���Ϊ�������������У��������˰ɡ�");
                return;
        }

        if (ob->query_skill("force") < 150)
        {
                command("say ����ڹ���򻹲��������������λ����ѧϰ�ɡ�");
                return;
        }
        command("nod");
        command("say �ҽ��ձ�����Ϊͽ�������ڿ�Ŭ������������һ����Ϊ��");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "ؤ��")
                return RANK_D->query_respect(this_player()) +"�뱾�ɺ��޹ϸ����ɵ��书�伮�ɲ��ܽ����㡣";
        if (query("book_count") < 1)
                return "�������ˣ����ɵ��ؼ����ڴ˴���";
        addn("book_count", -1);
        ob = new("/clone/book/stick_book.c");
        ob->move(this_player());
        command("rumor"+query("name", this_player())+"�õ�������������\n");
        return "�ðɣ��Ȿ���������š����û�ȥ�ú����С�";
}
