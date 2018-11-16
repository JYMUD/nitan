// /d/city/npc/oldman.c
// Last Modified by winder on Aug. 5 2001

#include <ansi.h>
inherit NPC;
inherit F_DEALER;

string *classes = ({
        "dragon","phenix","kylin","elephant","lion","tiger","panther","bear","fox","wolf","dog",
        "pig","deer","marten","cat","mouse","monkey","eagle","vulture","chicken","duck","snake",
        "tortoise","crocodile","horse","donkey","cattle","rabbit"
});
string *title = ({
        HIY"��",HIC"���",YEL"����","��","ʨ","��","��","��","��","��","��","��","¹","��","è",
        "��","��","ӥ","��","��","Ѽ","��","��","��","��","¿","ţ","��"
});
int *petstr=({30,20,25,30,25,25,20,25,12,15,12,15,10, 5, 5, 5,12,10,18, 5, 5,15, 5,18,20,18,22,10});
int *petdex=({30,30,25,10,20,20,25,12,20,20,20,10,22,20,20,18,30,25,25,20,20,15, 5,10,20,22,12,18});
int *petcon=({30,30,30,25,25,25,20,25,13,15,18,15,15,18,20,18,15,20,20,12,12,20,22,20,15,18,20,12});
int *petint=({30,30,30,12,15,15,12,12,20,12,20,10,10, 5,12,11,30,10,12,10,10, 5, 5, 8,12,10,10,12});
int *petper=({25,25,25,20,20,20,20,12,15,15,15,12,22,25,22,11,22,20,18,15,13, 8,10, 5,15,15,15,18});
int *petkar=({30,30,30,12,15,18,20,12,18,15,20,18,15,20,25,23,28,20,22,18,15,10,10, 8,12,15,15,12});
int *petcor=({30,30,30,15,20,25,25,20,12,20,18,12, 5,10,20,18,15,25,28,10,10,12,15,20,12,13,15, 5});
int *petcps=({30,30,30,25,20,20,15,20,25,12,18,15, 5, 8,10, 9,15,10,20,10,10,12,20,20,13,12,15, 5});
int *weight=({90,10,50,80,60,60,40,70,15,20,20,40,18,10,10, 8,15,20,35,10,10,18,10,30,40,30,45, 5});
int *value =({99,99,99,49,49,49,49,39,39,39,39,19,29,19, 9, 9,29,29,49, 9, 9,19, 9,39,39,29,29, 9});

int do_goumai(string arg);
void addaction(object pet);
void addaction(object pet)
{
        switch(query("class", pet) )
        {
                case "dragon"   :     //��
                        set("verbs", ({"angel","bite","claw","rope","tail"}), pet);break;
                case "phenix"   :     //���
                        set("verbs", ({"claw","poke","wind"}), pet);break;
                case "kylin"    :     //����
                        set("verbs", ({"angel","bite","hoof","knock"}), pet);break;
                case "elephant" :     //��
                        set("verbs", ({"hoof","knock","snoot"}), pet);break;
                case "lion"     :     //ʨ
                        set("verbs", ({"bite","claw","hoof","snap"}), pet);break;
                case "tiger"    :     //��
                        set("verbs", ({"bite","claw","hoof","snap","tail"}), pet);break;
                case "panther"  :     //��
                        set("verbs", ({"bite","claw","hoof","snap"}), pet);break;
                case "bear"     :     //��
                case "fox"      :     //��
                        set("verbs", ({"bite","claw","hoof"}), pet);break;
                case "wolf"     :     //��
                case "dog"      :     //��
                        set("verbs", ({"bite","claw","hoof","snap"}), pet);break;
                case "pig"      :     //��
                        set("verbs", ({"bite","hoof","knock"}), pet);break;
                case "deer"     :     //¹
                case "cattle"   :     //ţ
                        set("verbs", ({"angel","hoof","knock"}), pet);break;
                case "marten"   :     //��
                case "cat"      :     //è
                case "monkey"   :     //��
                case "rabbit"   :     //��
                case "mouse"    :     //��
                        set("verbs", ({"bite","claw","hoof"}), pet);break;
                case "eagle"    :     //ӥ
                case "vulture"  :     //��
                case "chicken"  :     //��
                case "duck"     :     //Ѽ
                        set("verbs", ({"claw","poke","wind"}), pet);break;
                case "snake"    :     //��
                        set("verbs", ({"bite","rope","tail"}), pet);break;
                case "tortise"  :     //��
                        set("verbs", ({"bite"}), pet);break;
                case "crocodile":     //��
                        set("verbs", ({"bite","claw","tail"}), pet);break;
                case "horse"    :     //��
                case "donkey"   :     //¿
                        set("verbs", ({"bite","hoof","knock"}), pet);break;
                default:
                        set("verbs", ({"bite","claw"}), pet);break;
        }
}
void create()
{
        set_name("������ͷ", ({ "lao tou", "laotou", "oldman"}) );
        set("gender", "����" );
        set("age", 64);
        set("long","һ���뷢�԰׵����ߣ��������壬�����⡣���������Ȥ����������Ҫֻ�����������档\n");
        set("max_qi", 2000);
        set("max_jing", 2000);
        set("max_neili", 2000);
        set("jiali", 50);
        set("combat_exp", 400000);
        set("attitude", "friendly");
        set_skill("dodge", 120);
        set_skill("unarmed",120);
        set_skill("parry", 120);
        set_skill("force",120);
        set("inquiry", ([
                "����"  : "��Ҫ����(goumai)ʲô����뿴�������ơ�\n",
        ]) );
        set("vendor_goods", ({
                FODDER_DIR+"siliao",
                FODDER_DIR+"fantuan",
                FODDER_DIR+"miantuan",
                FODDER_DIR+"roukuai",
                FODDER_DIR+"routuan",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",30);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_goumai","goumai");
        add_action("do_return","return");
        add_action("do_lingqu","lingqu");
        add_action("do_zancun","zancun");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("Pet", ob) )
        {
                say("������������Ц��������λ"+RANK_D->query_respect(ob)+"����ĳ�����������˰�����\n");
        }
        else
        {
                say("������������Ц��������λ"+RANK_D->query_respect(ob)+"��������ﰡ����\n");
        }
}
int do_goumai(string arg)
{
        object pet, gold, me = this_player(), ob = this_object();
        int num;

        if(!arg)
                return notify_fail("��ͷЦ�������𼱣����빺��ʲô������ȿ�������ơ���\n");
        if( query("Pet", me) && !wizardp(me) )
        {
                command("say ��λ"+RANK_D->query_respect(me)+"������ֻ�ܻ���һֻ����������µģ��ðѾɵ��Ȼ�(return)���ҡ���\n");
                return 1;
        }
        if ( member_array(arg, classes) == -1)
                return notify_fail("��ͷǸȻЦ��������ʱû�����ֳ�������뿴������ơ���\n");
        if( !wizardp(me) && query("combat_exp", me)<2000000 && 
                (arg == "dragon" || arg == "phenix" || arg == "kylin"))
                return notify_fail("��ͷ�Ǻ�һͨ��Ц��������ľ��黹��������Щ�����\n");

        num = member_array(arg, classes);
        gold = present("gold", me);
        if(!gold) return notify_fail("��ͷЦ��Ц������û������������\n");
        if((int) gold->query_amount() < value[num])
                return notify_fail("��ͷ������һ�ۣ��������ϻƽ�û��������\n");
        pet = new("/clone/misc/pet");
        set("class", classes[num], pet);
        set("id", classes[num], pet);
        set("title", title[num]+NOR, pet);
        set("name", "����", pet);
        set("race", "Ұ��", pet);
        pet->set_name("����", ({classes[num], "pet"}));
        set("long", "����һֻ����"+title[num]+"��\n"NOR, pet);
        set("level", 1, pet);
        set("owner",query("id",  me), pet);
        set_temp("owner",query("id",  me), pet);
        set_temp("ownername",query("name",  me), pet);
        set("Pet/id", classes[num], me);
        set("Pet/name", "����", me);

        set("str", petstr[num]+random(10), pet);
        set("dex", petdex[num]+random(10), pet);
        set("con", petcon[num]+random(10), pet);
        set("int", petint[num]+random(10), pet);
        set("per", petper[num]+random(10), pet);
        set("kar", petkar[num]+random(10), pet);
        set("cor", petcor[num]+random(10), pet);
        set("cps", petcps[num]+random(10), pet);
        set("obe", 1, pet);//��ʼѱ����
        set("age", 1, pet);//����
// ��������ʳ��
        set("weight", weight[num]*1000, pet);
        pet->set_weight(weight[num]*1000);
        if( random(10)>4)set("gender", "����", pet);
        else set("gender", "����", pet);
        gold->add_amount(-value[num]);

        addaction(pet);
        pet->move(environment(me));
        message_vision("$N�ͳ�"HIR+chinese_number(value[num])+NOR"��"HIY"�ƽ�"NOR"��������һ�ң���������һֻ"+title[num]+NOR"����\n", me);
        message_vision("$N����һ��"HIY"�ƽ�"NOR"��ɫ������һ�ۣ������۵������Ȼ������������ȡ��һֻ"+title[num]+NOR"���ڵ��ϡ�\n", ob);
        set("Pet/class",query("class",  pet), me);
        set("Pet/exp",query("combat_exp",  pet), me);
        set("Pet/id",query("id",  pet), me);
        set("Pet/title",query("title",  pet), me);
        set("Pet/name",query("name",  pet), me);
        set("Pet/nickname",query("nickname",  pet), me);
        set("Pet/long",query("long",  pet), me);
        set("Pet/level",query("level",  pet), me);
        set("Pet/max_jing",query("max_jing",  pet), me);
        set("Pet/eff_jing",query("eff_jing",  pet), me);
        set("Pet/jing",query("jing",  pet), me);
        set("Pet/max_qi",query("max_qi",  pet), me);
        set("Pet/eff_qi",query("eff_qi",  pet), me);
        set("Pet/qi",query("qi",  pet), me);
        set("Pet/food",query("food",  pet), me);
        set("Pet/water",query("water",  pet), me);

        set("Pet/str",query("str",  pet), me);
        set("Pet/dex",query("dex",  pet), me);
        set("Pet/con",query("con",  pet), me);
        set("Pet/int",query("int",  pet), me);
        set("Pet/per",query("per",  pet), me);
        set("Pet/kar",query("kar",  pet), me);
        set("Pet/cor",query("cor",  pet), me);
        set("Pet/cps",query("cps",  pet), me);
        set("Pet/obe",query("obe",  pet), me);

        if( query("last_age_set", pet) )
                addn("mud_age", time()-query("last_age_set", pet), pet);
        else addn("mud_age", 1, pet);
        set("Pet/mud_age",query("mud_age",  pet), me);
        set("Pet/weight",query("weight",  pet), me);
        set("Pet/gender",query("gender",  pet), me);
        set("Pet/wimpy",query("env/wimpy",  pet), me);

        set("Pet/unarmed", pet->query_skill("unarmed",1), me);
        set("Pet/dodge", pet->query_skill("dodge",1), me);
        set("Pet/parry", pet->query_skill("parry",1), me);

        return 1;
}

int do_return()
{
        object me = this_player(), *ob;
        string file, id;
        int i;

        if( !query("Pet", me) )
                return notify_fail("��ͷ�Ǻ����ˣ������û����������ɶ�������ţ���\n");
        if(me->is_busy())
                return notify_fail("����һ��������û����ɡ�\n");
        id=query("id", me);
        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if( query("owner", ob[i]) == id && query("curiousness", ob[i]) )
                {
                        break;
                }
        }
        if( i == sizeof(ob) )
                return notify_fail("��ͷ��ֵؿ�����һ�ۣ�����ĳ���û������������ô�����Ұ�����\n");
        message_vision("$Nһ�ѱ�����ϵ�$n���ݹ���̨������ͷ��\n", me, ob[i]);
        delete("Pet", me);
        destruct(ob[i]);
        me->start_busy(1);
        return 1;
}
int do_lingqu()
{
        object pet, me = this_player(), ob = this_object(), *obj;
        int i;

        if(me->is_busy())
                return notify_fail("����һ��������û����ɡ�\n");
        if( !query("Pet", me) )
        {
                command("say ��λ"+RANK_D->query_respect(me)+"����û�ݴ�(zancun)������������ж�������ȡ����\n");
                return 1;
        }

        obj = objects();
        for (i=0; i<sizeof(obj); i++)
        {
                if( query("owner", obj[i]) == query("id", me) && //��ϸҲ��owner
                        query("curiousness", obj[i]) )
                {
                        if(environment(obj[i]) == me )
                                return notify_fail(ob->name()+ "˵�����㲻����������ĳ�������ô��\n");
                        else
                                if(environment(obj[i]) != environment(me) )
                                        return notify_fail(ob->name()+"˵������ĳ�����"+(query("outdoors",environment(obj[i])) ? to_chinese(query("outdoors",environment(obj[i]))) : "����")+"��"+query("short",environment(obj[i]))+"���Ͽ�ȥ�Ұɡ�\n");
                                else
                                        return notify_fail(ob->name()+ "˵������ĳ��ﲻ�Ǿ������Ա�ô��\n");
                        return 1;
                }
        }
        pet = new("/clone/misc/pet");

        set("owner",query("id",  me), pet);
        set_temp("owner",query("id",  me), pet);
        set_temp("ownername",query("name",  me), pet);

        set("class",query("Pet/class",  me), pet);
        set("id",query("Pet/id",  me), pet);
        set("title",query("Pet/title",  me), pet);
        set("name",query("Pet/name",  me), pet);
        set("nickname",query("Pet/nickname",  me), pet);
        set("race", "Ұ��", pet);
        pet->set_name(query("Pet/name", me),({query("Pet/id", me),"pet"}));
        set("long",query("Pet/long",  me), pet);
        set("level",query("Pet/level",  me), pet);

        set("str",query("Pet/str",  me), pet);
        set("dex",query("Pet/dex",  me), pet);
        set("con",query("Pet/con",  me), pet);
        set("int",query("Pet/int",  me), pet);
        set("per",query("Pet/per",  me), pet);
        set("kar",query("Pet/kar",  me), pet);
        set("cor",query("Pet/cor",  me), pet);
        set("cps",query("Pet/cps",  me), pet);
        set("obe",query("Pet/obe",  me), pet);

        set("combat_exp",query("Pet/exp",  me), pet);
        set("mud_age",query("Pet/mud_age",  me), pet);
        set("age", 1+query("Pet/mud_age", me)/86400, pet);
        set("weight",query("Pet/weight",  me), pet);
        pet->set_weight(query("Pet/weight", me));
        set("gender",query("Pet/gender",  me), pet);
        set("env/wimpy",query("Pet/wimpy",  me), pet);

        set("max_jing",query("Pet/max_jing",  me), pet);
        set("eff_jing",query("Pet/eff_jing",  me), pet);
        set("jing",query("Pet/jing",  me), pet);
        set("max_qi",query("Pet/max_qi",  me), pet);
        set("eff_qi",query("Pet/eff_qi",  me), pet);
        set("qi",query("Pet/qi",  me), pet);
        set("food",query("Pet/food",  me), pet);
        set("water",query("Pet/water",  me), pet);

        set("curiousness", 1, pet);
        set("last_age_set", time(), pet);

        pet->set_skill("unarmed",query("Pet/unarmed", me));
        pet->set_skill("dodge",query("Pet/dodge", me));
        pet->set_skill("parry",query("Pet/parry", me));

        addaction(pet);

        pet->move(environment(me));
        message_vision("$N�����������ȡ��һֻ"+pet->name()+"���ڵ��ϡ�\n", ob);
        me->start_busy(1);
        return 1;
}

int do_zancun()
{
        object me = this_player(), *ob;
        string file, id;
        int i;

        if( !query("Pet", me) )
                return notify_fail("��ͷ�Ǻ����ˣ������û����������ɶ�������ţ���\n");
        if(me->is_busy())
                return notify_fail("����һ��������û����ɡ�\n");
        id=query("id", me);
        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if( query("owner", ob[i]) == id && query("curiousness", ob[i]) )
                {
                        break;
                }
        }
        if( i == sizeof(ob) )
                return notify_fail("��ͷ��ֵؿ�����һ�ۣ�����ĳ���û�������ݴ�ɶ������\n");
        if( query_temp("feeded", ob[i]) )
                return notify_fail(ob[i]->name()+"�ճ��˶�����������Ĳ������㡣\n");

        set("Pet/class",query("class",  ob[i]), me);
        set("Pet/exp",query("combat_exp",  ob[i]), me);
        set("Pet/id",query("id",  ob[i]), me);
        set("Pet/title",query("title",  ob[i]), me);
        set("Pet/name",query("name",  ob[i]), me);
        set("Pet/nickname",query("nickname",  ob[i]), me);
        set("Pet/long",query("long",  ob[i]), me);
        set("Pet/level",query("level",  ob[i]), me);
        set("Pet/max_jing",query("max_jing",  ob[i]), me);
        set("Pet/eff_jing",query("eff_jing",  ob[i]), me);
        set("Pet/jing",query("jing",  ob[i]), me);
        set("Pet/max_qi",query("max_qi",  ob[i]), me);
        set("Pet/eff_qi",query("eff_qi",  ob[i]), me);
        set("Pet/qi",query("qi",  ob[i]), me);
        set("Pet/food",query("food",  ob[i]), me);
        set("Pet/water",query("water",  ob[i]), me);

        set("Pet/str",query("str",  ob[i]), me);
        set("Pet/dex",query("dex",  ob[i]), me);
        set("Pet/con",query("con",  ob[i]), me);
        set("Pet/int",query("int",  ob[i]), me);
        set("Pet/per",query("per",  ob[i]), me);
        set("Pet/kar",query("kar",  ob[i]), me);
        set("Pet/cor",query("cor",  ob[i]), me);
        set("Pet/cps",query("cps",  ob[i]), me);
        set("Pet/obe",query("obe",  ob[i]), me);

        if( query("last_age_set", ob[i]) )
                addn("mud_age", time()-query("last_age_set", ob[i]), ob[i]);
        else addn("mud_age", 1, ob[i]);
        set("Pet/mud_age",query("mud_age",  ob[i]), me);
        set("Pet/weight",query("weight",  ob[i]), me);
        set("Pet/gender",query("gender",  ob[i]), me);
        set("Pet/wimpy",query("env/wimpy",  ob[i]), me);

        set("Pet/unarmed", ob[i]->query_skill("unarmed",1), me);
        set("Pet/dodge", ob[i]->query_skill("dodge",1), me);
        set("Pet/parry", ob[i]->query_skill("parry",1), me);

// ȡ������״̬
        delete_temp("comedby", me);

        message_vision("$Nһ�ѱ�����ϵ�$n���ݹ���̨����ͷ�ݴ档\n", me, ob[i]);
        destruct(ob[i]);
        me->start_busy(1);
        return 1;
}
