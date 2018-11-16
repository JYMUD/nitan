// This program is a part of NT MudLIB
// xu.c ����ʦ̫

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;
int peiyao();
int liandan();
void create()
{

        set_name("����ʦ̫", ({ "jingxu shitai","jingxu","shitai"}));
        set("long",
          "���Ƕ����ɶ�ʦ�㣬�������¶��꣬һ�׶����Ʒ�������������\n");
        set("gender", "Ů��");
        set("age", 43);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("shen", 10000);
        set("class", "bonze");
        set("inquiry",([
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
                "��ҩ"  : ( : peiyao :),
                "������": ( : liandan : ),
                "����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
        ]));

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 20);

        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jingli", 1500);
        set("max_jingli", 1500);
        set("level", 10);
        set("combat_exp", 250000);
        set("score", 1000);
        set_skill("persuading", 80);
        set_skill("throwing", 80);
        set_skill("force", 100);
        set_skill("dodge", 90);
        set_skill("finger", 100);
        set_skill("parry", 90);
        set_skill("strike", 80);
        set_skill("blade", 100);
        set_skill("literate", 90);
        set_skill("mahayana", 100);
        set_skill("jinding-zhang", 100);
        set_skill("tiangang-zhi", 90);
        set_skill("yanxing-dao", 100);
        set_skill("zhutian-bu", 100);
        set_skill("emei-xinfa", 100);
        set_skill("linji-zhuang", 100);
        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("blade","yanxing-dao");
        map_skill("parry","yanxing-dao");

        create_family("������", 4, "����");

        set("master_ob", 3);
        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

/*
void init()
{
        ::init();
        add_action("do_nod","nod");
}
*/

int do_nod(string arg)
{
        object me = this_player();

        if( !query_temp("pending/kao", me) )
                return 0;

        command("smile");
        command("say �ҽ�������������\n");

        message("vision", "����ʦ̫����"+me->name()+"���˼��仰��\n",
                        environment(me), ({me}) );

        switch(random(2)) {
                case 0:
                write("����ʦ̫˵����к�����ס�ڶ���ɽ��
            �и�ɮ��������ʲô��ʤ�壿�����˵��ֱ����ᰡ�
            ɮ�����ʣ������£�������֮�£���Σ����������������塣
            ɮ�����ʣ�ʲô�Ƿ𷨣�������˵��������ǰ���˹ġ�
            ��ɮ˵�����Ҳ���������к����������ش������أ�\n\n");

                if ((int)me->query_skill("mahayana", 1) > 50 + random(8)) {
                        write("��������һ�������������������¡�\n");
                        write("��˵��������ǧ��ĺ��˰١�\n\n");
                        message("vision", me->name()+"����һ�£�������ʦ̫˵�˼��仰��\n",
                                environment(me), ({me}) );

                        command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
                        command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("��������ã�Ҳ�ⲻ�������е�����\n");
                        command("say �����ӷ����ѧЩ�𷨺��������Ұɡ�\n");
                }
                break;

                case 1:
                write("����ʦ̫˵������������ڶ���ɽ���ҡ�
            ������������죬�и�ɮ�˳����ʣ�ʲô�Ƿ𷨴��⣿
            �������˵���ճ���֪�����ʣ������ĵ��ǰ�ƣ�
            ɮ�����ʣ�ʲô��˫�徳������������������ش������أ�\n\n");

                if ((int)me->query_skill("mahayana", 1) > 50 + random(8)) {
                        write("��������һ������������������ʡ�\n");
                        write("������ҹ��ˮ���ֺ�����������ǰɽ��\n\n");
                        message("vision", me->name()+"����һ�£�������ʦ̫˵�˼��仰��\n",
                                environment(me), ({me}) );

                        command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
                        command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������\n");
                        command("recruit "+query("id", me));
                }
                else {
                        write("��������ã�Ҳ�ⲻ�������е�����\n");
                        command("say �����ӷ����ѧЩ�𷨺��������Ұɡ�\n");
                }
                       break;
        }
        return 1;

}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("say �����ӷ����գ����գ��ڱ������У���Ҫ�ȿ�����ķ𷨡�");
        set_temp("pending/kao", 1, ob);
        command("say ��Ҫ׼�����ˣ��͸���(nod)�Ұɡ�\n");
        add_action("do_nod", "nod");
        return;
}
int peiyao()
{
        object me = this_player();
        object ob = this_object();
        object obj;
        int i;

        if(!objectp(present("caoyao 3",me)))
        {
                command("say �������û����ô���ҩ��");
                return 1;
        }
        for(i=0;i<3;i++)
        {
                obj=present("caoyao",me);
                destruct(obj);
        }
        command("smile");
        command("say �ðɣ��Ҿ͸�����ҩ�ˡ�");
        obj=new("/d/emei/obj/zhongyao");
        obj->move(me);
        message_vision("����ʦ̫��$Nһ����ҩ��\n",me);
        return 1;
}
int liandan()
{
        object me = this_player();
        object ob = this_object();
        object obj;
        int i;
        if(!objectp(present("liuhuang",me)))
        {
                command("say �������û�������������õ���ǡ�");
                return 1;
        }
        obj=present("liuhuang",me);
        destruct(obj);
        command("smile");
        command("say �ðɣ��Ҿ͸�������һ����������");
        obj=new("/d/emei/obj/pilidan");
        obj->move(me);
        message_vision("����ʦ̫��$Nһ����������\n",me);
        return 1;
}
