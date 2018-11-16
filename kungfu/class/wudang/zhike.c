// zhike.c ����

#include <ansi.h>
//#include "daozhang.h"
inherit NPC;
//inherit F_MASTER;

void create()
{
        set_name("�������", ({ "lingxu daozhang", "lingxu", "daozhang" }));
        set("long", "�����䵱ɽ��֪�͵���������Զ�ŵĵ��ӡ�����ɽ��ӭ����͡�\n");
        set("gender", "����");
        set("nickname", "֪�͵���");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "taoist");
        set("no_get", 1);
        set("no_steal",1);
        set("owner","mud_os");
        set("quest_no_guard",1);

        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 800);
        set("max_jing", 400);
        set("neili", 500);
        set("max_neili", 500);

        set("combat_exp", 7500);
        set("score", 1000);

        set_skill("force", 80);
        set_skill("yinyun-ziqi", 40);
        set_skill("dodge", 80);
        set_skill("strike", 40);
        set_skill("wudang-zhang", 40);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("wudang-jian", 80);
        set_skill("taoism", 20);

        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("chat_chance",2);
        set("chat_msg", ({
                 "�������˵�������䵱�����˽ܣ����ʢ�������µ��˶������ݾ��㡣\n",
                 "�������˵�������������䵱�����Ż����ҵ�һ��Ҫ��������(volunteer)������˿��и����\n"
                 "�������˵����������Ʋ��ף�����������ˣ��Ϸ����߷��ܵ�֮��\n",
                 "�������˵�������䵱�����˽ܣ����ʢ�������µ��˶������ݾ��㡣\n",
                 "�������˵������˵ɽ��ǰ����������������п����ĵ�ʿ��ȥ�ң�����Ҳû�г�����\n",
        }));

        set("inquiry", ([
                "���" : "������Ʋ��ף�����������ˣ��Ϸ����߷��ܵ�֮��",
                "����" : "���㣿ͯ���޼ɣ�ͯ���޼ɣ�Ҫ˵������ǣ�",
                "����" : "���õ���������Ӳ��ϣ�����Ϊ���䵱���Ӻ�ɽ����ͼ�ʱ���",
                "�Ϸ���" : "�Ϸ��׾���������������Ǯ�������幤��",
                "����" : "�Ϸ��׾���������������Ǯ�������幤��",
                "����" : "�䵱������ɽ��ǰ�档",
                "����" : "�䵱���־������湬��",
                "name" : "�����䵱��֪�͵�������������ɽ�š�",
                "here" : "�������䵱�������ţ�һֱ���ϾͿɵ���������",
                "rumors" : "��˵ɽ��ǰ�����������������֪�����Ǽ١�"
                "�����п����ĵ�ʿ��ȥ�ң�����Ҳû�г�����\n",
                "����" : "������Ĺ�����������(volunteer)ɽ�ţ�ÿ����һ�졣\n",
                "����" : "������Ĺ�����������(volunteer)ɽ�ţ�ÿ����һ�졣\n",
                "�ɻ�" : "������Ĺ�����������(volunteer)ɽ�ţ�ÿ����һ�졣\n",
        ]));
        create_family("�䵱��", 3, "����");

        setup();
        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"dao-cloth")->wear();
        carry_object(CLOTH_DIR"dao-shoe")->wear();
}

void init()
{
        object me = this_player();
        ::init();
        if (environment() != load_object("/d/wudang/xuanyuegate") ) return;

        add_action("do_volunteer","volunteer");

        if( !is_fighting() && living(this_object()))
        {
                if(interactive(me))
                {
                        remove_call_out("greeting");
                        call_out("greeting", 1, me);
                }
        }
}

void greeting(object ob)
{
        mapping myfam;
        if (environment(this_object())!=environment(ob))
        return;
        myfam=query("family", ob);
        if ( myfam && myfam["family_name"] == "�䵱��" )
                command("say��λ��"+((query("gender", ob) == "Ů��")?"��":"��")+"�����ˣ�");
        else if( query("title", ob) == "�䵱��ͯ" )
                say("���������"+ob->name()+"˵������λ"+RANK_D->query_respect(ob)+"��Ҫ����Ŭ������\n");
        else if( query("shen", ob)>-100 )
                say("����������˸�Ҿ������λ" + RANK_D->query_respect(ob) + "���ˣ���ӭ�����䵱ɽ��\n");
        else        say("���������ৡ������������λ" + RANK_D->query_respect(ob) + "����ɱ��������������䵱�������ذɣ�\n");
}

int do_volunteer()
{
        object me = this_player();
        object *ob;
        object *obs;
        int i;

        if( query_temp("in_guard", me) )
                return notify_fail("֪�͵�������˵����ר���غ�ɽ�ţ���������ݹ���\n");

        if( query("family/family_name", me) != "�䵱��" )
        {
                message_vision("֪�͵������һ������Ϊ���ɵĵ��ӣ�����ô�������أ���\n", me);
                return 1;
        }

        if( query("short", environment(this_object())) != "������" )
        {
                message_vision("��ѽ������ô������ѽ�������Ȼ�ȥ��\n", me);
                return 1;
        }

        if( query("combat_exp", me) >= 400000 )
         {
                message_vision("֪�͵���һҾ�������ҷ���׳ʿ����ֻ\n", me);
                return 1;
        }

        ob = all_inventory(environment(me));
        obs = filter_array(ob,
                           (: interactive($1) &&
                           $1 != $(me) &&
                           query_temp("in_guard", $1) && 
                           environment($1) :));

        if (sizeof(obs) > 3)
                return notify_fail("֪�͵�������˵���Ѿ��в�������ɽ���ˣ���һ�������ɡ�\n");

        tell_room(environment(me),query("name", me)+"��ʼ���䵱ɽ��ֵ�ء�\n");
        set("qi", 30000);
        set("jing", 30000);
        set_temp("in_guard", 1, me);

        // remove_call_out("end_guard");
        call_out("end_guard", 150, me);
        // remove_call_out("clone_meng");
        call_out("clone_meng", 30, me);
        return 1;
}

void clone_meng(object me)
{
        object ob;
        int maxskill;
        int maxexp;
        int maxqi;

        if (! me) return;

        if( !query_temp("in_guard", me) )
                return;

        maxskill = me->query_skill("force", 1);
        maxqi=query("eff_qi", me);
        maxexp=query("combat_exp", me);

        if( query("short", environment(me)) != "������" )
        {
                tell_object(me,"�����䵱ɽ��ֵ���߿���ʧ�ܡ�\n");
                call_out("end_guard", 0, me);
                return;
        }

        tell_room(environment(me), "ɽ��ͻȻ������һ������󺺡�\n");

        ob = new("/d/wudang/npc/mengmian.c");
        if (! me->is_ghost())
        {
                ob->move(environment(me));
        }
        set("combat_exp", maxexp, ob);
        if (maxskill > 5 && maxexp > 50000)
        {
                ob->set_skill("kuang-jian", maxskill*2/3);
                ob->set_skill("sword", maxskill*2/3);
                ob->set_skill("parry", maxskill*2/3);
                ob->set_skill("unarmed", maxskill*1/2);
                ob->set_skill("dodge", maxskill*2/3);
        } else
        {
                ob->set_skill("kuang-jian", 5);
                ob->set_skill("sword", 5);
                ob->set_skill("parry", 5);
                ob->set_skill("unarmed", 5);
                ob->set_skill("dodge", 5);
        }
        set("qi", maxqi, ob);
        set("volunteer_owner",query("id",  me), ob);

        set("title", HIR"�����"NOR, ob);
        ob->kill_ob(me);
        message_vision(HIR "\n$N����$n���һ����ɱ��!��\n" NOR, ob, me);
        tell_room(environment(me), "ɽ��ͻȻ������һ������󺺡�\n");

        ob = new("/d/wudang/npc/mengmian.c");
        if (! me->is_ghost())
        {
                ob->move(environment(me));
        }

        set("combat_exp", maxexp, ob);
        if (maxskill > 5 && maxexp > 50000)
        {
                ob->set_skill("kuang-jian", maxskill);
                ob->set_skill("sword", maxskill);
                ob->set_skill("parry", maxskill);
                ob->set_skill("unarmed", maxskill);
                ob->set_skill("dodge", maxskill);
        } else
        {
                ob->set_skill("kuang-jian", 5);
                ob->set_skill("sword", 5);
                ob->set_skill("parry", 5);
                ob->set_skill("unarmed", 5);
                ob->set_skill("dodge", 5);
         }
        set("qi", maxqi, ob);
        set("volunteer_owner",query("id",  me), ob);

        set("title", HIR"�����"NOR, ob);
        ob->kill_ob(me);
        me->kill_ob(ob);
        message_vision(HIR "\n$N����$n���һ����ɱ��!��\n" NOR, ob, me);

        call_out("clone_meng", 100, me);
}

void end_guard(object me)
{
        object *enemys;
        int i;
        if (! me) return;

        remove_call_out("clone_meng");
        if( !query_temp("in_guard", me))return ;

        delete_temp("in_guard", me);

        if( query("short", environment(me)) == "������" )
        {
                addn("family/gongji", random(8)+4, me);
                addn("combat_exp", random(220)+120, me);
                if( query("potential", me)>me->query_potential_limit() )
                        addn("potential", 1, me);
                else
                        addn("potential", random(50)+80, me);

                tell_room(environment(me),query("name", me)+"���䵱ɽ��ֵ����������\n");
                tell_object(me, "�����䵱ɽ��ֵ����������\n");
        } else
        {
                tell_room(environment(me),query("name", me)+"���䵱ɽ��ֵ���߿���ʧ�ܡ�\n");
                tell_object(me, "�����䵱ɽ��ֵ���߿���ʧ�ܡ�\n");
        }
        enemys = children("/d/wudang/npc/mengmian");
        enemys = filter_array(enemys, (: query("volunteer_owner", $1) == $(query("id",me)) :));
        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "ֻ��" + enemys[i]->name()
                                        + "ͻȻ��ɫһ�䣬Ѹ�ٹ������У�����սȦת�����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "ֻ��" + enemys[i]->name()
                                        + "��ֵһ�㣬ͻȻ��ɫ��䣬����ææ�������ˡ�\n");
                        }
                        destruct(enemys[i]);
                }
        }
}

void die()
{
        object *me, *enemys;
        int i;

        me = all_inventory(environment());

        for (i = 0; i < sizeof(me); i ++)
                delete_temp("in_guard", me[i]);

        enemys = children("/d/wudang/npc/mengmian");
        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "ֻ��" + enemys[i]->name()
                                        + "ͻȻ��ɫһ�䣬Ѹ�ٹ������У�����սȦת�����ˡ�\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "ֻ��" + enemys[i]->name()
                                        + "��ֵһ�㣬ͻȻ��ɫ��䣬����ææ�������ˡ�\n");
                        }
                        destruct(enemys[i]);
                }
        }
        ::die();
}

int accept_object(object who, object ob)
{
        object obn, wage;
        int i, j;
        string *wanted;
        if( query("money_id", ob) && ob->value() >= 100*query("age", who) )
        {
                if( (query("family/family_name", who)) == "�䵱��" )
                        tell_object(who,"�����������һЦ����Ȼ��"+((query("gender", who) == "Ů��")?"��":"��")+"��˳���������������������һ֦������ȥ����ɡ�\n");
                else
                        tell_object(who, "�����������һЦ����Ȼʩ����˳���������������������һ֦����ʩ����ȥ����ɡ�\n");
                obn = new("/d/wudang/obj/incense");
                obn->move(who);
                return 1;
        }
        else
                if( query("money_id", ob) )
                {
                        if( (query("family/family_name", who)) == "�䵱��" )
                                tell_object(who,"�������������̾�����䵱ɽ���ʢ��ȫ�����"+((query("gender", who) == "Ů��")?"��":"��")+"������������𰡣�\n");
                        else
                                tell_object(who, "�������������̾�����䵱ɽ���ʢ��ȫ����������������Ͱ���\n");
                        return 1;
                }
        return 0;
}
