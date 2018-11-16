#include <ansi.h>

inherit NPC;
inherit F_DEALER;

mixed ask_xiongba();

void create()
{
        set_name("����ƽ", ({ "wang fangping", "wang", "fangping" }));
        set("nickname", WHT "����" NOR);
        set("shen_type", 1);

        set("gender", "����");
        set("age", 475);
        set("long", "����ƽ����ɽ�е�ʿ�����ڷᶼɽ�������ɣ����⡸��������\n");

        set_skill("unarmed", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("magic", 500);
        set_temp("apply/damage", 2000);
        set_temp("apply/parry", 2000);
        set_temp("apply/dodge", 2000);
        set_temp("apply/attack", 2000);
        set_temp("apply/force", 2000);

        set("combat_exp", 20000000);
        set("attitude", "friendly");
        /*
        set("vendor_goods", ({
                "/d/death/obj/weapon1",
                "/d/death/obj/weapon2",
                "/d/death/obj/weapon3",
                "/d/death/obj/weapon4",
                "/d/death/obj/weapon5",
                "/d/death/obj/weapon6",
                "/d/death/obj/weapon7",
                "/d/death/obj/weapon8",
                "/d/death/obj/weapon9",
                "/d/death/obj/weapon10",
                "/d/death/obj/weapon11",
                "/d/death/obj/weapon12",
                "/d/death/obj/weapon13",
                "/d/death/obj/weapon14",
                "/d/death/obj/weapon15",
                "/d/death/obj/weapon16",
                "/d/death/obj/weapon17",
                "/d/death/obj/weapon18",
                "/d/death/obj/weapon19",
                "/d/death/obj/weapon20",
                "/d/death/obj/weapon21",
                "/d/death/obj/weapon22",
                "/d/death/obj/weapon23",
                "/d/death/obj/weapon24",
                "/d/death/obj/weapon25",
                "/d/death/obj/weapon26",
                "/d/death/obj/weapon27",
                "/d/death/obj/weapon28",

                "/d/death/obj/weapon29",
                "/d/death/obj/weapon30",
                "/d/death/obj/weapon31",
                "/d/death/obj/weapon32",
                "/d/death/obj/weapon33",
                "/d/death/obj/weapon34",
                "/d/death/obj/weapon35",
                "/d/death/obj/weapon36",
                "/d/death/obj/weapon37",
                "/d/death/obj/weapon38",
                "/d/death/obj/weapon39",
                "/d/death/obj/weapon40",
                "/d/death/obj/weapon41",
                "/d/death/obj/weapon42",
                "/d/death/obj/weapon43",
                "/d/death/obj/weapon44",
                "/d/death/obj/weapon45",
                "/d/death/obj/weapon46",
                "/d/death/obj/weapon47",
                "/d/death/obj/weapon48",
                "/d/death/obj/weapon49",
                "/d/death/obj/weapon50",
                "/d/death/obj/weapon51",
                "/d/death/obj/weapon52",
                "/d/death/obj/weapon53",
                "/d/death/obj/weapon54",
                "/d/death/obj/weapon55",
                "/d/death/obj/weapon56",
                "/d/death/obj/weapon57",
                "/d/death/obj/weapon58",
                "/d/death/obj/weapon59",
                "/d/death/obj/weapon60",
                "/d/death/obj/weapon61",
                "/d/death/obj/weapon62",
                "/d/death/obj/weapon63",
                "/d/death/obj/weapon64",
                "/d/death/obj/weapon65",
                "/d/death/obj/weapon66",
                "/d/death/obj/weapon67",
                "/d/death/obj/weapon68",
                "/d/death/obj/weapon69",
                "/d/death/obj/weapon70",
                "/d/death/obj/weapon71",
                "/d/death/obj/weapon72",
                "/d/death/obj/weapon73",
                "/d/death/obj/weapon74",
                "/d/death/obj/weapon75",
                "/d/death/obj/weapon76",
                "/d/death/obj/weapon77",
                "/d/death/obj/weapon78",
                "/d/death/obj/weapon79",
                "/d/death/obj/weapon80",
        }));
        */
        set("inquiry", ([
                "������" : "�������˵�����Ʒ��ֻ��ţͷ����������������û�б�����������Ҳ��������������������\n",
                "����"   : "������ǰ��һ�ź����������Լ���Ů����ʹ֮�����ֻ�֮�࣬����ֻ��ʥ��\n" + 
                           "�������ķ�����������ຣ������Ͷ̥���ˣ���������ܰ��������ҵ��������ģ�������\n" +
                           "�ǿ�������һ�Σ���ţͷ������������������\n",
                "��������" : "���������е���Ʒ�������߿ɲ�׹�����������ֻأ�\n"
                             "��������˵������Ҳֻ��Īа���������������ġ�\n",  
                "�۰�����" : (: ask_xiongba :),
                "�Ե�"     : "�Ե��˵�����ѧ������֮�˵����۰����£������˼�����������...\n",
        ]));

        setup();
        carry_object(__DIR__"obj/cloth4")->wear();
}
/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/


mixed ask_xiongba()
{
        object me;
        
        me = this_player();
        
        if (! objectp(me))return;
        
        if( !query("can_perform/badao/can_xiong", me) )
        {
                tell_object(me, HIG "����ƽ�����㣺�����ѵõ���������������Ů�����ֻ�֮�࣬������ϡ���ʥѪ�塯\n"
                                    "���������ܳ��£���������ܰ����ҵ���ʥѪ�壬�ұ㴫�����۰����ºͰ��ǵ���\n"
                                    "һ�еľ��С�\n" NOR);
                return "��Σ�";                 
        }
        
        if( query("can_perform/badao/xiong", me) )
                return "����п������Ѿ����ˣ���ûʲô�ð�����ˡ�\n";
                
        if (me->query_skill("badao", 1) < 700)
                return "������Ե���򻹲��������㽲��Ҳ�ǰ׽���\n";
                
        message_vision(HIY "$N" HIY "˵������Ȼ��ˣ����۰����µľ��оʹ����ˣ���ɿ����ˣ���ֻʩչһ�� ....\n", 
                       this_object());
                       
        tell_object(me, HIG "��ϲ�㣬�����ˡ��۰����¡���\n" NOR);
        tell_object(me, HIG "��ϲ�㣬�����˰��ǵ���һ����\n" NOR);
        
        tell_object(me, HIM "����ƽ���Ķ���˵������˵��ֻҪ��Ե��ﵽ800�����Ⱒ�ǵ��ڶ�������������ѧϰ��\n" NOR);
        tell_object(me, HIM "����ƽ�ֶ���˵������������������׽��㣬��Ҫ�ҵ����µ�һ���--�����������������\n" NOR);

        set("can_perform/badao/xiong", 1, me);
        set("can_perform/badao/san-1", 1, me);
        me->save();
        
        return "���ҴӴ˻�����Ƿ�����߸�·�ɣ�\n";
}

int accept_object(object me, object obj)
{                       
        // ��ʥѪ��
        if( query("id", obj) == "god blood" && 
            base_name(obj) == "/clone/fam/etc/prize5")
        {               
                if( query("can_perform/badao/can_xiong", me) )
                {
                        command("bow"+query("id", me));
                        command("say ��л����������������ȴ��������Ը��");
                        return 0;
                }
                command("nod"+query("id", me));
                command("say ��Ȼ���ܰ����ҵ����}Ѫ�壬��Ҳ�������ҵ�ŵ�ԡ�");
                command("ke");
                command("say �ҵø�ȥ��������Ů�ˣ���л��");
                tell_object(me, HIY "һ��������Զ��Ʈ�������۰����ºͰ��ǵ��ڵ��ľ�������ʱ��������\n"
                                    "��ѧ(ask wang about �۰�����)��\n" NOR);

                set("can_perform/badao/can_xiong", 1, me);
                me->save();
                destruct(obj);
                destruct(this_object());
                return 1;
        }
        if( query("badao_quest/suoyangdan_allow", me) )
        {
                command("bow"+query("id", me));
                command("say ��л����������������ȴ��������Ը��");
                return 0;
        }

        if( query("id", obj) == "jinlan jiasha" && 
            base_name(obj) == "/clone/armor/jinlan-jiasha")
        {
                command("yi"+query("id", me));
                command("say ��.. ��.. ���ǽ��������𣬸��¾�Ȼ���ҵ� ...");
                command("tan");
                command("say ��Ȼ��ˣ�������Ը���ˣ���ȥ��ţͷ�����������������ɡ�");
                
                set("badao_quest/suoyangdan_allow", 1, me);
                me->save();
                destruct(obj);
                return 1;
        }
        else
                return 0;
        
        
                   
}
