// yang.c ���

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include <ansi.h>
#include "gumu.h"

string ask_yunv();
int not_to_learn_ss(object ob);
mixed teach_sad();
string ask_sword();
int ask_youju();
mixed ask_me();
string ask_nuhai();

void create()
{
        set_name("���", ({"yang guo", "yang"}));
        set("gender", "����");
        set("age", 26);
        set("long", @LONG
������ȥüĿ֮����һ������֮����Ȼ������ԼԼȴ���˸е�һ����֮�飬
����յ����ģ���Ȼ���ǲм���
LONG );
        set("attitude", "friendly");

        set("str", 35);
        set("int", 36);
        set("con", 34);
        set("dex", 32);

        set("qi", 7800);
        set("max_qi", 7800);
        set("jing", 6900);
        set("max_jing", 6900);
        set("neili", 8500);
        set("max_neili", 8500);
        set("jiali", 120);
        set("no_get", 1);

        set("combat_exp", 5750000);

        set("couple/id", "xiao longnv");
        set("couple/name", "С��Ů");

        set_skill("force", 690);
        set_skill("yunv-xinfa", 690);
        set_skill("surge-force", 690);
        set_skill("sword", 680);
        set_skill("yunv-jian", 680);
        set_skill("quanzhen-jian", 680);
        set_skill("xuantie-jian", 680);
        set_skill("dodge", 650);
        set_skill("yunv-shenfa", 650);
        set_skill("parry", 680);
        set_skill("unarmed", 680);
        set_skill("meinv-quan", 670);
        set_skill("strike", 680);
        set_skill("sad-strike", 680);
        set_skill("fireice-strike", 680);
        set_skill("tianluo-diwang", 660);
        set_skill("literate", 600);
        set_skill("taoism", 600);
        set_skill("medical", 680);
        set_skill("array", 680);
        set_skill("yunv-xinjing", 680);
        set_skill("throwing", 640);
        set_skill("yufeng-zhen", 640);
        set_skill("hebi-jianzhen", 640);
        set_skill("martial-cognize", 600);

        map_skill("force", "surge-force");
        map_skill("sword", "xuantie-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "sad-strike");
        map_skill("unarmed", "sad-strike");
        map_skill("strike", "tianluo-diwang");

        prepare_skill("unarmed", "sad-strike");

        create_family("��Ĺ��", 3, "����");

        set("inquiry", ([
                "������" : "��...�٣�",
                "����"   : "�������������Ĵ�����",
                "����"   : "��ʦ��ô...�治��˵����",
                "С��Ů" : "����������Ӹ�ʲô��",
                "�"   : "���ˣ�������Ҳ�ա�",
                "�����" : "����ͷ��û�У��ܾ�û�������ˡ�",
                "��Ȼ������" : (: teach_sad :),
                "��������"   : "���Ƕ���ǰ��������ѧ���������ҵ���ϰ�ã�\n",
                "������" :   (: ask_sword :),
                "��������" : (: ask_sword :),
                "��Ĺ�ľ�" : (: ask_youju :),
                "ŭ������"   : (: ask_nuhai :),
        ]));

        set("guarder", ([
                "refuse_home" : "$N��$n�����������",
                "refuse_other": "$N��$n���������ǹ�Ĺ���������ĵط�������Ҫ���ţ�",
                "refuse_carry": "$N��$n�ȵ����������ϵ��˸������£�",
        ]));

        set("no_teach/sad_strike", (: not_to_learn_ss :));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.wang" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "unarmed.tuo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        carry_object("/clone/cloth/qingyi")->wear();
}

void init()
{
        ::init();
        add_action("do_yuanyi", "yuanyi");
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) == query("family/family_name") )
        {
                if (query_skill(skill, 1) < 1 ||
                    SKILL_D(skill)->type() != "martial")
                        return 0;

                if( query("int", ob)<24 )
                {
                        command("say ���������ʲ��ѣ��ҽ�����̫�ۡ�");
                        return -1;
                }

                return 1;
        }

        if (skill == "unarmed" &&
            this_player()->query_skill("sad-strike", 1) > 0 &&
            this_player()->query_skill(skill, 1) < 200)
                return 1;

        if (skill != "sad-strike")
        {
                command("say �㻹�������ʦ��ȥѧϰ�ɣ�");
                return 0;
        }

        if (not_to_learn_ss(ob))
                return -1;

        if (this_player()->query_skill(skill, 1) > 600)
                return 0;

        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 32)
        {
                command("say ������ʲ�������������ϳ��书��");
                return;
        }

        if ((int)ob->query_skill("force") < 150)
        {
                command("say �����Ϊʦô������ڹ������������ɣ�");
                return;
        }

        if( query("max_neili", ob)<1000 )
        {
                command("say �������������������Ҳ���ٰ���");
                return;
        }

        command("say �ðɣ�����Ҳ���������ˣ��Ҿ����������ͽ���ˡ�");
        command("recruit "+query("id", ob));
}

string ask_sword()
{
        object ob = this_player();
        mapping fam=query("family", ob);
        if (! fam || fam["family_name"] != "��Ĺ��")
                return RANK_D->query_respect(ob) + "���ҹ�Ĺ���ˣ���֪���˻�������";
        if (fam["generation"] > 4)
                return RANK_D->query_respect(ob) + "����������´��ˣ����ǵ��Ժ���˵�ɡ�";
        if( query("ygpass", ob) )
                return "�Ҳ����Ѿ���������������������֮����ô��";
        if( query("gender", ob) == "����" )
        {
                command("pat"+query("id", ob));
                command("say ���������������ϣ����������������ڶ��´���Ĺǰ��������������");
                set("ygpass", 1, ob);
                return "������Ϣ���������У����ص��������ں�ˮ�������ľ��ϣ���ú�ȥ����һ�°ɡ�";
        }
        if( query("gender", ob) == "Ů��"){
        if ((int)ob->query_str() < 35)
                return "��λ" + RANK_D->query_respect(ob) + "������������Ҫ���ߵ��������㻹����Ŭ��һ���ɡ�";
        if ((int)ob->query_dex() < 35)
                return "��λ" + RANK_D->query_respect(ob) + "���ں�ˮ����ϰ����������Ҫ���ߵ������㻹����Ŭ��һ���ɡ�";
        if ((int)ob->query_skill("sword", 1) < 200)
                return "��λ" + RANK_D->query_respect(ob) + "�Ļ���������������������������Եֵ���ˮ�ĳ����";
        if ((int)ob->query_int() < 35)
                return "��λ" + RANK_D->query_respect(ob) + "�����Ի������ߣ������������Ҫ���Ŀھ���";
                  command("pat"+query("id", ob));
                  command("say ���������������ϣ����������������ڶ��´���Ĺǰ��������������");
                  set("ygpass", 1, ob);
                  return "������Ϣ���������У����ص��������ں�ˮ�������ľ��ϣ���ú�ȥ����һ�°ɡ�";
        }
}

int ask_youju()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "��Ĺ��"){
                command("say ���ǡ���Ůȭ�������һ�е���ʽ���������Դ��ġ�");
                return 1;
        }
        if( query("family/master_name", ob) == "��Ī��"){
                command("say ���ǡ���Ůȭ�������һ�е���ʽ���������Դ��ġ�");
                command("say ������ʦ����Ī��ĵ��ӣ��ұ�����ָ�����㡣");
                command("say ��Ȼһ�������������Ը������Ϊ��ȥ�����ϵ�а����ָ�������С���Ĺ�ľӡ�����Ը��(yuanyi)��");
                set_temp("mark/youju", 1, ob);
                return 1;
                }
        if( query("can_perform/meinv-quan/you", ob)>0){
                command("say �㲻���Ѿ�ѧ������");
                return 1;
        }
        if ((int)ob->query_skill("unarmed", 1) < 120) {
                command("say Ҫʹ�������ľ�����Ҫ�����ȭ�����㻹�Ƕ���ϰ��ϰ����Ůȭ������˵�ɡ�");
                return 1;
        }
        command("say ���ǡ���Ůȭ�������һ�е���ʽ���������Դ��ġ�");
        command("say �ã���Ȼһ�����������ҿ�ν��Ե������ָ�������С���Ĺ�ľӡ���");
        message_vision( "$N��ϸ��$n�����ˡ���Ĺ�ľӡ��ľ�Ҫ���ڡ�\n",this_object(), ob );
        set("can_perform/meinv-quan/you", 1, ob);
        return 1;
}
int do_yuanyi()
{
        object me = this_player();

        if( !query_temp("mark/youju", me) )
                return 0;

        message_vision("$n������$N���ϼ������Ŵ�Ѩ�������¡�\n", me, this_object() );
        write("��е�ͷ����һ��̩ͨ��\n");
        set("shen", 0, me);
        command("say �ã����ӿɽ̣��Ҿ�ָ�������С���Ĺ�ľӡ���");
        message_vision( "$N��ϸ��$n�����ˡ���Ĺ�ľӡ��ľ�Ҫ���ڡ�\n",this_object(), me );
        delete_temp("mark/youju", me);
        set("can_perform/meinv-quan/you", 1, me);
        return 1;
}

// ��ȡŭ����������
string ask_nuhai()
{
        object me;
        string msg;
        
        
        me = this_player();
        
        if( query("can_perform/surge-force/new", me) )
                return "��ŭ�����εľ�ѧ�Ѿ������ˣ���������Ҹ�ʲô��";
                
        //����Ѿ���ȡ����
        if( query("can_perform/surge-force/quest/step", me) )
                return "������ܰ����ҵ���������ŭ�����εľ�ѧ�ұ㴫�㡣";
        
        msg = HIC "ŭ���������Ҷ��������뺣�˲�������������ľ�����ѧ�����������˶��ֶ�����ѧ\n"
                  "�ľ��衣��ϧ��Ŀǰ���������ַ���°�ߣ����䲻�����������Э�����һ���������\n"
                  "�׾�ѧ�ұ㴫�㡣\n" NOR;
        
        tell_object(me, msg);

        set("can_perform/surge-force/quest/step", 1, me);
        me->save();
        
        return "��˵���ַ�������ھ���ȳ�û�����������ȥ������\n";    
}
mixed teach_sad()
{
        object ob = this_player();

        if (ob->query_skill("sad-strike", 1) >= 1)
        {
                command("say �㲻���Ѿ�������");
                return 1;
        }

        if( query("gender", ob) != "����" )
        {
                command("say �������书ֻ�ʺ������������㻹�����˰ɣ�");
                return 1;
        }

        if( query("static/sadly", ob)<3 )
        {
                command("say ����᲻������˼�����ӵ��黳��"
                        "�޷�����ҵ���Ȼ�����ƣ�");
                return 1;
        }

        if( query("character", ob) == "���ռ�թ" || 
            query("character", ob) == "�ĺ�����" )
        {
                command("say ��һ������ȥ���ˣ��޷�������Ȼ����ľ��磡");
                return 1;
        }

        if( query("int", ob)<24 )
        {
                command("say ���������Բ��㣬�޷�������Ȼ�����ơ�");
                return 1;
        }

        if( query("str", ob)<28 )
        {
                command("say ������������㣬�޷�������Ȼ�����ơ�");
                return 1;
        }

        if( query("max_neili", ob)<3000 )
        {
                command("say ���������Ϊ���㣬�޷�����Ȼ�����ơ�");
                return 1;
        }

        if (ob->query_skill("force") < 320)
        {
                command("say ���ڹ���Ϊ���㣬�޷�������Ȼ�����ơ�");
                return 1;
        }

        if ((int)ob->query_skill("unarmed", 1) < 200)
        {
                command("say ��Ļ���ȭ�Ų�����죬�޷�����Ȼ�����ơ�");
                return 1;

        }

        if (ob->query_skill("martial-cognize", 1) < 200)
        {
                command("say ����ѧ�������㣬�޷���������Ȼ�����ơ�");

                return 1;
        }

        message_vision(HIW "$n" HIW "���˿�$N" HIW "�������ã�����Ҳ��������"
                       "ԨԴ���Ҿʹ�����Ȼ�����ƣ�\n" NOR, ob, this_object());

        ob->set_skill("sad-strike", 10);

        tell_object(ob, HIG "��ѧ���ˡ���Ȼ�����ơ���\n" NOR);

        command("tan");
        command("say ��ȥ��ϰ�ɣ��ǵ�Ҫ�úöԴ�������ӣ�");

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "���־�" :
       return MASTER_D->teach_pfm(this_player(), this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/juan",
                           "free"    : 1,
                           "name"    : "���־�",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 100,
                           "neili"   : 3000,
                           "force"   : 600,
                        ]));
                break;

        case "Ѹ��" :
       return MASTER_D->teach_pfm(this_player(), this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/lei",
                           "name"    : "Ѹ��",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 200,
                           "sk2"     : "force",
                           "lv2"     : 200,
                           "sk3"     : "surge-force",
                           "lv3"     : 200,
                           "gongxian": 600, ])); 
                break;

        case "�󽭶�ȥ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/dong",
                           "free"    : 1,
                           "name"    : "�󽭶�ȥ",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 200,
                           "neili"   : 5000,
                           "force"   : 600,
                         ]));
                break;

        case "����Ⱥħ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/dang",
                           "name"    : "����Ⱥħ",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 70,
                           "sk2"     : "force",
                           "lv2"     : 90,
                           "gongxian": 600, ]));
                break;

        case "������ӿ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/hai",
                           "name"    : "������ӿ",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 130,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600, ]));

                break;

        case "ǧ��һ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/ji",
                           "name"    : "ǧ��һ��",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 130,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600, ]));

                break;

        case "��Ȼ����" :
                return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/sad-strike/xiao",
                           "free"    : 1,
                           "name"    : "��Ȼ����",
                           "sk1"     : "sad-strike",
                           "lv1"     : 150,
                           "neili"   : 3200,
                           "force"   : 320,
                         ]));
                break;

        case "�����ˮ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sad-strike/tuo",
                           "free"    : 1,
                           "name"    : "�����ˮ",
                           "sk1"     : "sad-strike",
                           "lv1"     : 180,
                           "neili"   : 6000,
                           "force"   : 360,
                         ]));
                break;

            case "ŭ������" :
                  return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/sad-strike/tao",
                             "free"    : 1,
                               "name"    : "ŭ������",
                             "sk1"     : "sad-strike",
                             "lv1"     : 280,
                             "neili"   : 6000,
                             "force"   : 560,
                           ]));
                  break;

        default:
                return 0;
        }
}

int not_to_learn_ss(object ob)
{
        if( query("gender", ob) == "Ů��" )
        {
                command("say �������书���ʺ�Ů����ѧϰ���������˰ɣ�");
                return 1;
        }

        if( query_temp("can_learn/yang/sad-strike", ob) )
                return 0;

        if( query("family/family_name", ob) != query("family/family_name") )
        {
                command("say " + RANK_D->query_respect(ob) + "�㲻���ҵ��״����ӣ����Һθɣ�");
                return 1;
        }

        if( query("static/sadly", ob)<3 )
        {
                command("say ����᲻������˼�����ӵ��黳��"
                        "�޷�����ҵ���Ȼ�����ƣ�");
                return 1;
        }

        message_vision("$n���˿�$N�������ã�����Ҳ��������"
                       "ԨԴ���Ҿʹ�����Ȼ�����ƣ�\n",
                       ob, this_object());
        set_temp("can_learn/yang/sad-strike", 1, ob);
        return 0;
}

/*
mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/sad-strike/wannian", me) )
                return "�Լ��úö���ϰ�ɣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�㲻���ҵ��״����ӣ��γ����ԣ�";

        if( query("shen", me)<200000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����һ�У�";

        if (me->query_skill("sad-strike", 1) < 180)
                return "�����Ȼ�����ƻ������������һ����ܽ�����һ�У�";

        message_vision(HIM "$n" HIM "���������ڹ���Ȼ���Լ������ٶ���$N"HIM"�ӳ�һ�ƣ�\n"
                       HIM "$n" HIM "��һ����Ȼ����ޱȣ�����$N"HIM"ȷ��һ�е����ƿ��ú�͸����Ȼ������׾ٵıܿ��ˣ�\n"
                       "����$N" HIM "���Ϊʲô��һ����ô���ʱ��$n"HIM"������ͻȻ���Ա�һת�����ô�����$N"HIM"���ؿ��ϣ�����\n"
                       "$N"HIM"���һ��������Ѿ����У���æ�����ڹ�Ӳ������������һ�У�����......\n" NOR,
                       me, this_object());
        command("sigh");
        command("say �������һ�°ɡ�");
        tell_object(me, HIG "��ѧ���������ҡ�\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 160000);
        set("can_perform/sad-strike/wannian", 1, me);
        me->unconcious();
        return 1;
}
*/
// ���ܾ��鵤
int accept_object(object me, object ob)
{
        int r;
        
        if (r = ::accept_object(me, ob)) 
                return r;
                
        if (! objectp(me) || ! objectp(ob))return 0;
        
        if( query("id", ob) != "jueqing dan" )
        {
                return 0;
        }

        if( query("can_perform/surge-force/new", me) )
        {
                tell_object(me, HIG "��������㣺��л�����ϴ������������ⶫ���������Լ����Űɡ�\n" NOR);
                return 0;
        }
        
        if( query("can_perform/surge-force/quest/step", me)<3 )
                return 0;
        
        if( query("reborn/times", me) < 3 )
        {               
                tell_object(me, HIG "��������㣺�㻹δ�����ֻ�ת����ĥ������������ѧ��ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);
                return 0;
        }
                
        if( query("int", me)<40 || query("con", me)<40 )
        {               
                tell_object(me, HIG "��������㣺���������Բ��㣬����ѧ��ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);
                return 0;
        }
                
        if (me->query_skill("force", 1) < 1000)
        {
                tell_object(me, HIG "��������㣺������ڹ���Ϊ���㣬�޷�����ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);
                return 0;
        }               
        if( query("max_neili", me)<35000 )
        {
                tell_object(me, HIG "��������㣺��������Ϊ���㣬�޷�����ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);
                return 0;
        }       
        if (me->query_skill("taoism", 1) < 1)
        {
                tell_object(me, HIG "��������㣺���ѧ�ķ���Ϊ���㣬�޷�����ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);  
                return 0;
        }               
        if (me->query_skill("xuantie-jian", 1) < 1)
        {
                tell_object(me, HIG "��������㣺������������Ϊ���㣬�޷�����ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);  
                return 0;                               
        }               
        if (me->query_skill("martial-cognize", 1) < 1200)
        {
                tell_object(me, HIG "��������㣺����ѧ�������㣬�޷�����ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);              
                return 0;
        }               
        if (me->query_skill("jiuyin-shengong", 1) < 1 && 
            me->query_skill("jiuyin-hamagong", 1))
        {
                tell_object(me, HIG "��������㣺��δ�����ɹ������澭���޷�����ŭ�����Ρ��ⵤ��Ҫ���á�\n" NOR);
                return 0;       
        }               

        command("thank "+query("id", me));
        
        message_sort(HIM "\n$N" HIM "��$n˵��������˸����������������������о��ˣ���ĳ����Ϊл����"
                     "����ŭ�����ξ�ѧ�������㣬��������� ...\n\n" NOR, this_object(), me);

                                
        tell_object(me, HIG "�����ŭ�����ξ�ѧ����Ҫ��һһ��������...\n" NOR);

        tell_object(me, HIC "\n��ϲ�㣡������ŭ�����Σ��£���\n");

        CHANNEL_D->do_channel(this_object(), "rumor", "\n��˵�����ŭ�����ξ�ѧ���ڸ���" HIY + me->name() + HIM "��" NOR);

        me->set_skill("surge-force", 200);
        set("can_perform/surge-force/new", 1, me);
        
        destruct(ob);
        
        me->save();     

        return 1;
}
/*
void unconcious()
{
        die();
}
*/
