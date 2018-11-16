#include <ansi.h>
inherit NPC;

#include "xingxiu.h"

string ask_job();
void create()
{
        set_name("ʨ����", ({ "shihou zi", "shihou" }));
        set("nickname", "�����ɶ�ʦ��");
        set("long",
                "�����Ƕ�����Ķ�����ʨ���ӡ�\n"
                "����ʮ���꣬ʨ�����ڣ�һ����֪����������ʿ��\n");
        set("gender", "����");
        set("age", 32);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("class", "fighter");
        set("str", 28);
        set("int", 20);
        set("con", 26);
        set("dex", 22);

        set("max_qi", 2500);
        set("max_jing", 1200);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 25);
        set("combat_exp", 220000);

        set_skill("force", 120);
        set_skill("huagong-dafa", 120);
        set_skill("guixi-gong", 140);
        set_skill("dodge", 90);
        set_skill("zhaixing-gong", 90);
        set_skill("strike", 120);
        set_skill("chousui-zhang", 120);
        set_skill("claw", 100);
        set_skill("sanyin-zhua", 100);
        set_skill("parry", 100);
        set_skill("poison", 80);
        set_skill("staff", 50);
        set_skill("tianshan-zhang", 50);

        set("no_teach", ([
                "huagong-dafa" : "������Ҫ�������Դ��ڡ�",
        ]));

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("claw", "sanyin-zhua");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        create_family("������", 2, "����");
        set("inquiry", ([
                "������" : "����������е���û��ûС�ġ��Ժ�����ɣ�",
                "����"   : (: ask_job :),
                "job"    : (: ask_job :),
        ]));
        set("master_ob", 4);
        setup();
}

void attempt_apprentice(object ob)
{
        command("say �Ҳ���ͽ��");
        return 0;

        command("say �ðɣ��Ҿ��������ˡ�");
        welcome(ob);
        command("recruit "+query("id", ob));
}

string ask_job()
{
        object me, ob;
        mapping fam;
        int shen, exp;
        me = this_player();
        fam=query("family", me);
        shen=query("shen", me);
        exp=query("combat_exp", me);

        if(!fam)
                return "���ó��������̬�ȹ������β��ȼ������������أ�";
        if( fam["family_name"] != "������" && !query_temp("ding_flatter", me) )
                return "������ɵ�̬�ȿ���ȥ��̫��������";
        if(exp<250000)
                return "�����������ټӰ��������ɡ�";
        if(exp>=500000)
                return "�������������Ҳ�̫�������ȥ������ʦ��ժ���Ӱɡ�";
        if(me->query_condition("wait_xx_task"))
                return "�ϴθ����ˣ������͵ȵȰɡ�";
        if( interactive(me) && query_temp("xx_job", me) )
                return "����ô�������﷢����";
        if(interactive(me) && me->query_condition("wait_xx_task"))
                return "�����������黹�ã���������Ϊ�����ǡ�";
        if(query("di_count") < 1)
                return "�����������黹�ã�������������ˡ�";

        ob = new(__DIR__"obj/di");
        addn("di_count", -1);
        ob->move(me);
        set("xx_user", getuid(me), ob);
        if(fam["family_name"] != "������")
                set_temp("apply/short", ({WHT"�����ɸ���"NOR+me->name()+"("+query("id", me)+")"}), me);
        set_temp("xx_job", 1, me);
        message_vision("\n$N�ó�һֻ���ƶ̵ѣ�����$n��\n", this_object(), me);
        return "����������鲻�ѣ����Ҫ���Ϊ�����˼ҷ��ǲ��ǣ�\n";
}
