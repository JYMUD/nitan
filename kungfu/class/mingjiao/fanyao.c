// This program is a part of NT MudLIB

#include "ansi.h"

inherit NPC;
inherit F_COAGENT;
inherit F_GUARDER;

string ask_me();
string ask_me1();

void create()
{
        set_name("��ң", ({ "fan yao", "fan", "yao" }));
        set("long",
                "����һλ�������е�ͷ�ӣ����ײ����ۡ�\n"
                "�����������߰˰˵�ȫ���˰̣���ֱ������������Ŀ�ˡ�\n"
        );

        set("title",HIG "����" HIR "������ʹ" NOR);
        set("level",11);
        set("gender", "����");
        set("attitude", "peaceful");
        set("class", "bonze");

        set("age", 38);
        set("shen_type", 1);
        set("per", 12);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 3500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 800000);

        set_skill("force", 220);
        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("cuff", 220);
        set_skill("hand", 220);
        set_skill("claw", 220);
        set_skill("strike", 220);
        set_skill("literate", 150);

        set_skill("shenghuo-xinfa", 220);
        set_skill("lingxu-bu", 220);
        set_skill("shenghuo-quan", 220);
        set_skill("guangming-zhang", 220);
        set_skill("liehuo-jian", 220);
        set_skill("nianhua-zhi", 220);
        set_skill("sanhua-zhang", 220);
        set_skill("fengyun-shou", 220);
        set_skill("longzhua-gong", 220);
        set_skill("buddhism", 340);
        set_skill("martial-cognize", 220);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "lingxu-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("cuff", "shenghuo-quan");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        set("inquiry", ([
                "����ʥ����"  : (: ask_me :),
                "����ʥ����"  : (: ask_me :),
                "ʥ����"      : (: ask_me :),
                "���������"  : (: ask_me1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: prepare_skill("finger", "nianhua-zhi") :),
                (: prepare_skill("strike", "sanhua-zhang") :),
        }) );
        set("inherit_title",HIG"����"HIC"���̷���"NOR);
        create_family("����", 34, "������ʹ");

        set("master_ob",4);

        set("coagents", ({
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "zhang wuji" ]),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 150);
        set("heiyu", 1);
        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}

string ask_me1()
{
        mapping fam;
        object ob, *clone;
        int i, j;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "����" )
                return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";

        if (this_player()->query_skill("shenghuo-shengong", 1) < 50)
                return "�������̵�ʱ���ж̣������������㻹�����ʸ�ʹ�á�\n";

        if( query_temp("marks/��1", this_player()) )
                return "�㲻�Ǹ����˺��������������ô��Ҫ��";

        if (present("heiyu duanxugao", this_player()))
                return "�����ϲ��Ǵ��ź������������ô��Ҫ��";

        if( query("eff_qi", this_player()) == query("max_qi", this_player()) )
                return "�����ڲ���Ҫ�ú�������ࡣ";

        if( query("heiyu", this_object())<1 )
                return "�������ˣ�����������Ѹ�ȫ������ȥ�ˡ�";

        ob = new("/d/mingjiao/obj/heiyu");
        ob->move(this_player());
        set_temp("marks/��1", 1, this_player());
        addn("heiyu", -1, this_object());

        return "�ðɣ���к�������������ȥ�ðɡ�";
}

void reset()
{
        set("heiyu", 1);
}

#include "fanyao.h"
