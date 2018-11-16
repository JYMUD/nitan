// ding.c ������

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

#include "xingxiu.h"
#include <ansi.h>

int ask_ding();
int ask_book();
int ask_poison();
int ask_staff();
int ask_job();
string ask_me();
string ask_du1();
string ask_du2();
string ask_xiangliao();
int do_answer(string arg);
void no_answer(object user);

#define ANTI_ROBOT "/kungfu/class/xingxiu/robot"
#define SUO "/clone/lonely/rousisuo"
#define YINLINFEN "/clone/medicine/poison/yinlinfen"
#define HONGLINFEN "/clone/medicine/poison/honglinfen"
#define DUCHONGFEN "/clone/medicine/poison/duchongfen"
#define BINGPOFEN "/clone/medicine/poison/bingpofen"

string ask_huoyan();
string ask_yinlinfen();
string ask_bingpofen();
string ask_duchongfen();
string ask_honglinfen();

void create()
{
        set_name("������", ({ "ding chunqiu", "ding" }));
        set("nickname", HIG "�����Ϲ�" NOR);
        set("long", @LONG
�����������ɿ�ɽ��ʦ����������ʿ���ʹ���������Ϲֶ����
��������������ò���棬�ɷ���ǡ�
LONG );
        set("gender", "����");
        set("age", 60);
        set("attitude", "friendly");
        set("class", "scholar");
        set("shen_type", -1);
        set("str", 25);
        set("int", 30);
        set("con", 38);
        set("dex", 38);

        set("max_qi", 6400);
        set("max_jing", 2900);
        set("neili", 7300);
        set("max_neili", 7300);
        set("jiali", 120);
        set("level", 30);
        set("combat_exp", 3850000);

        set_skill("force", 600);
        set_skill("huagong-dafa", 600);
        set_skill("guixi-gong", 600);
        set_skill("throwing", 600);
        set_skill("feixing-shu", 600);
        set_skill("dodge", 600);
        set_skill("zhaixing-gong", 600);
        set_skill("strike", 600);
        set_skill("chousui-zhang", 600);
        set_skill("claw", 600);
        set_skill("sanyin-zhua", 600);
        set_skill("whip", 600);
        set_skill("chanhun-suo", 600);
        set_skill("parry", 600);
        set_skill("staff", 600);
        set_skill("poison", 600);
        set_skill("tianshan-zhang", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("xingxiu-qishu", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixing-gong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-zhua");
        map_skill("whip", "chanhun-suo");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");
        map_skill("poison", "xingxiu-qishu");
        map_skill("throwing", "feixing-shu");

        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");

        set("book_count", 1);
        set("zhen_count", 1);
        set("san_count", 1);
        set("xiangliao_count", random(10) + 10);

        set("inquiry", ([
                "����" : (: ask_job :),
                "job" : (: ask_job :),
                "������" : (: ask_staff :),
                "����"       : (: ask_me :),
                "���޶���"   : (: ask_me :),
                "������"     : (: ask_du1 :),
                "����"       : (: ask_xiangliao :),
                "��ң��Цɢ" : (: ask_du2 :),
                "��ľ����" : (: ask_ding : ),
                "���Ͼ綾" : (: ask_poison :),
                "�ⶾ" : (: ask_poison :),
                "book" : (: ask_book :),
                "�׽��ƪ" : (: ask_book :),
//                "����" : (: ask_huoyan :),
                "���׷�"        : (:ask_yinlinfen:),
                "yinlin fen" : (:ask_yinlinfen:),
                "���׷�" : (:ask_honglinfen:),
                "honglin fen" : (:ask_honglinfen:),
                "���Ƿ�" : (:ask_bingpofen:),
                "bingpo fen" : (:ask_bingpofen:),
                "�����": (:ask_duchongfen:),
                "duchong fen": (:ask_duchongfen:),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                //(: perform_action, "staff.fugu" :),
                //(: perform_action, "staff.xue" :),
                //(: perform_action, "strike.tao" :),
                (: perform_action, "strike.dan" :),
                (: perform_action, "strike.tao" :),
                (: perform_action, "strike.shi" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        create_family("������", 1, "��ɽ��ʦ");
        set("class", "taoist");

        set_temp("apply/damage", 180);
        set_temp("apply/armor", 400);
        set_temp("apply/attack", 250);
        set_temp("apply/dodge", 250);
        set_temp("apply/parry", 250);

        set("master_ob", 5);
        setup();
        //carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        //set_temp("handing", carry_object("/clone/misc/duwan"));

}

void init()
{
        object me;
        object ob,ob1;
        string poison;

        ::init();

        me = this_player();

        if (! interactive(me))
                return;

        add_action("do_answer", "answer", 1);

        if( interactive(ob=this_player()) && ob->query_condition("bingcan_posion") )
        {
                   command("? "+query("id", ob));
                   command("say "+query("name", ob)+"��ͽ��,���ƺ����˱��Ͼ綾��\n");
        }

        if( interactive(ob=this_player()) && query("family/master_id", ob) == "ding chunqiu"
        && (!present("yu di", this_player()))){
                ob1=new("/d/xingxiu/obj/yudi");
                ob1->move(this_player());
                command("say ��ֻ������������޵��ӵĻ��������ú����ţ�����Ū����");
                write("���������һֻ��ѡ�\n");
        }

        /*
        if (living(this_object()) && present("shenmuwang ding", me))
        {
                command("say �üһԭ����͵���ҵ���ľ�����������ɣ�");
                kill_ob(me);
                return;
        }
        */

        add_action("do_flatter", "flatter");
}

int ask_book()
{
        object ob;
       object me=this_player();

       if( query("canbook", me) == 1 && (!present("yijinjing",me))){
                tell_object(me,"������˵��������ͽ������û��͸�Ȿ�׽�İ���ô��\n");
                tell_object(me,"�Ǻðɡ��Ȿ�������㣬�û�ȥ�úò���ɣ�\n");
                tell_object(me,"ͽ����һ��Ҫ��ס��ǧ�������ľ����һ��������Ҫ��Ȼ�������߻���ħ����\n");
                ob=new("/clone/book/yjj_book2.c");

                ob->move(me);
                write("���������һ���׽��\n");
                return 1;
        }
        else
                return 0;
}

int ask_ding()
{
        object ob;
        object me=this_player();
        if( query("ask/ding", me) == 1 && (!present("shenmuwang ding",me)) && query("family/master_id", me) == "ding chunqiu" )
        {
                tell_object(me,"�ҿ���Ѱ���׽��������ľ�����ŵ���ʧ�����������Ȼ��Ҫ����ȥ�ɡ�\n");
                ob=new("/clone/misc/swmuding");
                ob->move(me);
                delete("ask/ding", me);
                return 1;
        }
        else return 0;

}

int ask_poison()
{
        object ob=this_player();
        if( query("family/master_id", ob) == "ding chunqiu" && ob->query_condition("bingcan_poison") )
        {
        tell_object(ob,HIY "Ҫ����Ͼ綾�����ְ취��������׽��ƪ��
        Ȼ�������ľ�������������󷨣���㶾�����ʲô��
        ��ϧ�����Ǳ���ƪ������Ȼ���䲻������������ҵ���
        ����Ļ����ҿ����Ժ��Ȼ���ֲ������󷨵�ȱ������
        ��֮�⣬ֻ�ܿ�ҩ���ӹ��˽��ˣ�\n" NOR);
        return 1; }
        else
        return 0;
}

int do_answer(string arg)
{
        int result;
        object me = this_object(), user = this_player();
        result = ANTI_ROBOT->do_answer(arg, user, me);

        if (result == 2) {
                command("whisper "+query("id", user)+"�ã��ã��ã��������ڷ����ˡ�");
                command("say " + user->name(1) + "������ʲô����ֻ�����Ұɣ�");
                set("passed_ding", 1, user);
                return 1;
        }

        if (result == -1) {
                command("hammer "+query("id", user));
                command("say " + user->name(1) + "�������������Ȼ����ƭ���ɣ����ҹ�һ��ȥ��");
                addn("ding_robot", 1, user);
                set("robot_ding",query("mud_age",  user)+query("ding_robot", user)*600, user);
                return 1;
        }

        return result;
}

void no_answer(object user)
{
        if( objectp(present(query("id", user),environment()))){
        command("beep "+query("id", user));
        command("heihei "+query("id", user));
        command("say " + user->name(1) + "������Ϊ��װ���Ҿ��β���������");
        command("say ���ҹ�һ��ȥ�ɣ�");
        }
else {
        command("tell"+query("id", user)+""+user->name(1)+"������Ϊ��װ���Ҿ��β���������");
        command("tell"+query("id", user)+"����ʱ�ò��Ÿ����������ˣ�");
}
        addn("ding_robot", 1, user);
        set("robot_ding",query("mud_age",  user)+query("ding_robot", user)*600, user);
}

void attempt_apprentice(object me)
{

        if( query("shen", me)>-12000 )
        {
                command("say ������Խ����Խ��׵������Ե׵ġ�");
                return;
        }

        if( query("combat_exp", me)<300000 )
        {
                command("say �����΢ĩ���������ѧ�����ɵ������");
                return;
        }

        if (me->query_skill("chousui-zhang", 1) < 120)
        {
                command("say ������ƶ�û��������Ȼ�����������ң�");
                return;
        }

        if ((int)me->query_skill("poison", 1) < 120)
        {
                command("say �㶾����ûѧ���ף������������ң�");
                return;
        }

        if( query_temp("pending/flatter", me) )
        {
                command("say ����˲������ɷ�����������������㣿");
                return;
        } else
        {
                command("say ���������ɱ������������ʥ����ô������");
                message_vision("�����Ϲ�΢��˫�ۣ������룬һ����������(flatter)�����ӡ�\n",
                this_player());
                set_temp("pending/flatter", 1, me);
        }
}

int do_flatter(string arg)
{
        if( !query_temp("pending/flatter", this_player()) )
                return 0;

        if (! arg) return notify_fail("��˵����ʲô��\n");
        set_temp("pending/flatter", 0, this_player());
        message_vision("$N����˵����" + arg + "\n", this_player());
        if( strsrch(arg, "��������") >=0 && (strsrch(arg, "�������") >=0
         || strsrch(arg, "�������") >=0 || strsrch(arg, "�Ž��ޱ�") >=0 )) {
                command("smile");
                command("say �⻹��ࡣ\n");
                welcome(this_player());
                command("recruit "+query("id", this_player()));
        } else
        {
                command("say ����˲����ҷ���������������㣿");
        }
        return 1;
}

// �������ɣ�������أ��������Ž��ޱ�
string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��\n";

        if (query("book_count") < 1)
                return "�������ˣ����ɵ��ڹ��ķ����ڴ˴���\n";

        addn("book_count", -1);
        ob = new("/clone/book/dujing_2");
        ob->move(this_player());
        return "�ðɣ��Ȿ�����޶��������û�ȥ�ú����С�\n";
}

string ask_du1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��\n";

        if (this_player()->query_skill("poison", 1) < 50)
                return "��Ķ������δ�����ò������ֶ�����\n";

        if (query("zhen_count") < 1)
                return "�������ˣ������붼�����ˡ�\n";

        addn("zhen_count", -1);
        ob = new("/d/xingxiu/obj/bilinzhen");
        ob->move(this_player());
        return "�ðɣ������������Щ��ɡ�\n";
}

string ask_du2()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��\n";

        if (this_player()->query_skill("poison", 1)<100)
                return "��Ķ������δ�����ò������ֶ�����\n";

        if (query("san_count") < 1)
                return "�������ˣ�����ûʲôʣ���ˡ�\n";

        addn("san_count", -1);
        ob = new("/d/xingxiu/obj/sanxiaosan");
        ob->move(this_player());
        return "�ðɣ������ҩ���û�ȥ�Ƽ����ðɡ�\n";
}

string ask_xiangliao()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������" )
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��\n";

        if (is_busy() || is_fighting())
                return "�Ȼ����û��������æ����ô��\n";

        if( query_temp("get_xiangliao", this_player()) )
                return "�ղŲ��Ǹ������𣿲�����ô��������˰ɣ�\n";

        if (this_player()->query_skill("poison", 1) < 40)
                return "��Ķ������̫�����������˵�ɣ�\n";

        if (query("xiangliao_count") < 1)
                return "�������ˣ�����ûʲôʣ�µ������ˣ��㻹��ȥ�ֿ����ҿ��ɣ�\n";

        addn("xiangliao_count", -1);
        ob = new("/clone/misc/xiangliao");
        ob->set_amount(random(50) + 100);
        ob->move(this_player());
        start_busy(2);
        set_temp("get_xiangliao", 1, this_player());
        call_out("clear_xiangliao_flag", 180);
        return "�ðɣ���Щ��������ȥ�����ðɡ�\n";
}

void reset()
{
        set("book_count", 1);
        set("zhen_count", 1);
        set("san_count", 3);
        set("zhen_count", 7);
        set("wxs_count",3);
        set("xiangliao_count", random(10) + 10);
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch(topic)
        {
             case "����" :
             case "����" :
             case "����" :
                 return QUEST_D->accept_ask(this_object(), me, topic);

             case "�����":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chanhun-suo/duo",
                                 "name"     :  "�����",
                                 "sk1"      :  "chanhun-suo",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  130,
                                 "shen"     :  -10000,
                                 "family/gongji" :  80,
                                 "force"    :  80 ]));
                  break;

             case "���ĵ�":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/dan",
                                 "name"     :  "���ĵ�",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  950 ]));
                  break;

             case "���컨��":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/feixing-shu/hua",
                                 "name"     :  "���컨��",
                                 "sk1"      :  "feixing-shu",
                                 "lv1"      :  100,
                                 "sk2"      :  "force",
                                 "lv2"      :  120,
                                 "neili"    :  500,
                                 "family/gongji" :  300 ]));
                  break;

             case "��������":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/tao",
                                 "name"     :  "��������",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  220,
                                 "sk2"      :  "poison",
                                 "lv2"      :  250,
                                 "sk3"      :  "huagong-dafa",
                                 "lv3"      :  220,
                                 "shen"     :  -38000,
                                 "neili"    :  3000,
                                 "family/gongji" :  1200 ]));
                  break;

             case "�������":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huoyan",
                                 "name"     :  "�������",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  950 ]));
                  break;

             case "�������":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huoqiu",
                                 "name"     :  "�������",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  950 ]));
                  break;

             case "�������":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/biyan",
                                 "name"     :  "�������",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  140,
                                 "sk2"      :  "force",
                                 "lv2"      :  140,
                                 "sk3"      :  "poison",
                                 "lv3"      :  140,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  140,
                                 "shen"     :  -22000,
                                 "neili"    :  1800,
                                 "family/gongji" :  1000 ]));
                  break;

             case "�������":
                 return MASTER_D->teach_pfm(me, this_object(),
                               (["perform"  :  "can_perform/chousui-zhang/huolang",
                                 "name"     :  "�������",
                                 "sk1"      :  "chousui-zhang",
                                 "lv1"      :  200,
                                 "sk2"      :  "force",
                                 "lv2"      :  200,
                                 "sk3"      :  "poison",
                                 "lv3"      :  200,
                                 "sk4"      :  "throwing",
                                 "lv4"      :  200,
                                 "shen"     :  -50000,
                                 "neili"    :  1800,
                                 "family/gongji" :  2000 ]));
                  break;

             case "��˿��" :
                return MASTER_D->give_item(me, this_object(),
                               (["item"     :  SUO,
                                 "master"   :  1,
                                 "sk1"      :  "chanhun-suo",
                                 "lv1"      :  140,
                                 "shen"     :  -30000 ]));
                  break;

             default :
                  return 0;

        }
}

void clear_xiangliao_flag()
{
        if( query_temp("get_xiangliao", this_player()) )
               delete_temp("get_xiangliao", this_player());

        return;
}

int ask_staff()
{
        object me=this_player();
        object waguan;
        mapping fam;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������"){
                command("?");
                return 1;
        }

        if( query("tianshan", me) == 1){
                command("say ��Ҫ���������ĵ���Ц��");
                return 1;
        }

        if (me->query_skill("pixie-jian",1)>=10){
                command("hmm");
                command("say ������ʧ�������������˹���");
                return 1;
        }

        if (me->query_skill("staff", 1) < 200){
                command("say ������ȷ�����Ϊ������");
        }

        if (me->query_str() < 50) {
                command("say �������̫���ˣ��úö��������������Ұɡ�");
                return 1;
        }

        if (me->query_con() < 50) {
                command("say ����ڹ���Ϊ̫���ˣ��úö��������������Ұɡ�");
                return 1;
        }

        if (me->query_int() < 35) {
                command("sneer");
                command("say ������ѧ��������������̫���ȥ�úö�һ����ɡ�");
                return 1;
        }


                message_vision(HIG"$N΢΢һЦ����$n����һ�ԣ������ؽ�����ɽ��������һ�С�\n", this_object(), this_player());
                message_vision(HIG"$n��$N�Ľ����£�����ɽ�ȷ�������һ���µ���⡣", this_object(), this_player());
                set("tianshan", 1, me);
                tell_object(this_object(),HIC"�����ɽ�ȷ������ˣ�");
                me->add_skill("tianshan-zhang", 10);
                return 1;


        return 1;
}

int ask_job(){

        object me=this_player();
        object waguan;
        mapping fam;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������"){
                command("?");
                return 0;
        }

        if( query("robot_ding", me)>query("mud_age", me)){
                command("say �ߣ��ϴ���ƭ���ɵ��£����ɻ�û�к��������أ������ڻ������������ǣ�");
                command("say ���ȸ��һ�ȥ�ú÷�ʡ�Լ�һ�£��Ժ�������");
                return 1;
        }

        if( query("robot_answer", me))return notify_fail("����Ϸ����ǰ��������ˣ�\n");

        if( random(4) == 1 && !query("passed_ding", me)){
                command("say ��ҹ�Ϸ������˸�䣬˵��" + me->name(1) + "���²���ʵ����д��������ƭ�Ϸ�");
                command("say �����Ϸ�����Ҫ����һ�ʣ��������ˣ�");
                ANTI_ROBOT->get_question(me, this_object());
                return 1;
        }

        if( query_temp("xx_job", me) == 1){
                command("say ��С�ӣ���һ������û����ɾ͸������ҹ�����");
                return 1;
        }
        command ("say �����������������ҪһЩ�������㵽��ɽ��Щ�����Ұɡ���");
        waguan=new("/d/xingxiu/obj/waguan");
        set_temp("xx_job", 1, me);
        if (!present("wa guan", me)) waguan->move(me);
            message_vision("������˳�ִ���������ȡ��һ��С�߹��Ӹ��㡣\n", me);
                command ("say ����ȥ��أ�·��С�ġ���");
        return 1;

}

int accept_object(object who, object ob){

        object me=this_player();
        mapping fam;
        int pot, exp;
        string msg;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "������"){
                command("?");
                return 0;
        }

        if( query("id", ob) == "du dan"){

              if( query_temp("xx_job", this_player()) != 1 || query("player", ob) != query("id", me)){
                        command("hehe");
                        return 0;
                } else {
                     command("pat "+query("id", this_player()));
                        command("say �����ģ�������Խ����Խ˳���ˡ�\n");
                        // exp triple
                        pot = random(100)+100;
                        exp = 200 + random( 50 );

        if( query("combat_exp", me)>6400000 )
        {
                pot /= 2;
                exp = exp / 2;
        }
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        msg = sprintf("��ץ��õ� %d �㾭��� %d ��Ǳ�ܡ�\n", exp, pot);
                        tell_object(me,msg);
                        delete_temp("xx_job", me);
                        delete_temp("found", me);
                        delete_temp("bug_hold", me);
                        delete_temp("bug_out", me);
                        delete("passed_ding", me);
                        call_out("destob",2,ob);
                        return 1;
                }
        }
        if( query("id", ob) == "a zi"){

                        command("say ̫���ˣ������а������ͽץ�����ˣ�\n");
                        command("say �����ģ��������ͽ�����ȹص��η�����ȥ��\n");
                        tell_object(me,"��������������޵��ӰѰ����ϳ�ȥ�ˡ�\n");
                        pot = random(300)+80;
                        exp = 500 + random( 20 );
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        set("ask/ding", 1, me);
                        destruct(ob);
                        return 1;
        }
        if( query("id", ob) == "noname book" )
        {
        if( !query("my_owner", ob) || query("my_owner", ob) != me )
                return notify_fail("������ŭ��������������������ƶ������������ˣ�\n");
                // if(me->query("ask/ding")==1)
                if(me)
                {
                        tell_object(me,"�⡭�������׽��ƪ������
ͽ������������һͳ�������������ˣ������Ȼ����ȡ�ã��պ��㵱ȻҲ��
����ϰ����Ϊʦ�����������¼����������ʦͽ��ͬ�о���\n");
                        set("canbook", 1, me);
                        return 1;
                }
                else
                return notify_fail("������ŭ�������������Ǻε���ݣ����������������������Ҳ�Ҫ����\n");
        }

        if( query("id", ob) == "ling pai"){
                if( query("player", ob) != query("id", me)){
                        command("hehe");
                        return 0;
                } else {
                        command("hehehe");
                        command("say �����ģ�����Щ�Գ��������ɵ�֪�����ɵ�������\n");
                        if( query("menpai", ob) == "huashan" || query("menpai", ob) == "quanzhen" )
                                exp = 100 + random( 50 );
                        else if( query("menpai", ob) == "mingjiao"){
                                command("say �š������̾�ȻҲ���Ҹ����ˡ�\n");
                                //exp triple
                                exp = 120 + random( 60 );
                        } else        exp = 70+random(30);
        if( query("combat_exp", me)>6400000 )
        {
                exp = exp / 2;
        }
                        addn("combat_exp", exp, me);
                        msg = sprintf("������Ƶõ� %d �㾭�顣\n", exp);
                        tell_object(me,msg);
                        call_out("destob",1,ob);
                        delete("passed_ding", me);
                        return 1;
                }
        }

        return ::accept_object(who, ob);
}

void destob(object ob){
        destruct(ob);
}

string ask_huoyan()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "������")
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
        if (this_player()->query_skill("poison",1)<100)
                return "��Ķ������δ�����ò������ֶ�����";
        if (query("huoyan_count") < -100) return "�������ˣ�����ûʲôʣ���ˡ�";
        addn("huoyan_count", -1);
        ob = new("/d/xingxiu/npc/obj/huoyan.c");
        ob->move(this_player());
        return "�ðɣ��Ҿ͸���ѻ���ɡ�";
}

string ask_yinlinfen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "������")
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
        if (me->query_skill("poison",1)<100)
                return "��Ķ������δ�����ò������ֶ�����";
        ob=new(YINLINFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                return query("name",ob)+"��������������";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "�������ˣ�"+query("name", ob)+"���ڲ��������С�";
      if( query("family/family_name", owner) == "������" )
           return query("name",ob)+"�����ڱ���" + query("name",owner) +"���У���Ҫ�þ�ȥ�����ɡ�";
      else
           return "����Ϊ���µ����أ�"+query("name", ob)+"����������"+query("name", owner)+"֮�֣����ȥ����ɱ�ˣ��Ѷ���ȡ������";
     }
  }
        command("nod");
  ob->move(this_object());
  command("give fen to "+query("id", me));
  return "��"+query("name", ob)+"�����ȥ��ϣ�����ܺú����á�";
}

string ask_duchongfen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "������")
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
        if (me->query_skill("poison",1)<100)
                return "��Ķ������δ�����ò������ֶ�����";
        ob=new(DUCHONGFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                ob->query("name",ob)+"��������������";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "�������ˣ�"+query("name", ob)+"���ڲ��������С�";
      if( query("family/family_name", owner) == "������" )
           return query("name",ob)+"�����ڱ���" + query("name",owner) +"���У���Ҫ�þ�ȥ�����ɡ�";
      else
           return "����Ϊ���µ����أ�"+query("name", ob)+"����������"+query("name", owner)+"֮�֣����ȥ����ɱ�ˣ��Ѷ���ȡ������";
     }
  }
        command("nod");
  ob->move(this_object());
   command("give fen to "+query("id", me));
  return "��"+query("name", ob)+"�����ȥ��ϣ�����ܺú����á�";
}

string ask_honglinfen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "������")
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
        if (me->query_skill("poison",1)<100)
                return "��Ķ������δ�����ò������ֶ�����";
        ob=new(HONGLINFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                return query("name",ob)+"��������������";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "�������ˣ�"+query("name", ob)+"���ڲ��������С�";
      if( query("family/family_name", owner) == "������" )
           return query("name",ob)+"�����ڱ���" + query("name",owner) +"���У���Ҫ�þ�ȥ�����ɡ�";
      else
           return "����Ϊ���µ����أ�"+query("name", ob)+"����������"+query("name", owner)+"֮�֣����ȥ����ɱ�ˣ��Ѷ���ȡ������";
     }
  }
        command("nod");
  ob->move(this_object());
   command("give fen to "+query("id", me)); 
  return "��"+query("name", ob)+"�����ȥ��ϣ�����ܺú����á�";
}

string ask_bingpofen()
{
        mapping fam;
        object ob;
        object owner;
        object temp;
        object me=this_player();
        if( !(fam=query("family", me)) || 
                fam["family_name"] != "������")
                return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
        if (me->query_skill("poison",1)<100)
                return "��Ķ������δ�����ò������ֶ�����";
        ob=new(BINGPOFEN);
        if (temp=ob->violate_unique())
         {
                 destruct(ob);
                 ob=temp;
          owner = environment(ob);
          if (owner == me)
                return query("name",ob)+"��������������";
          if (objectp(owner) && owner != this_object())
     {
      if (! owner->is_character())
           return "�������ˣ�"+query("name", ob)+"���ڲ��������С�";
      if( query("family/family_name", owner) == "������" )
           return query("name",ob)+"�����ڱ���" + query("name",owner) +"���У���Ҫ�þ�ȥ�����ɡ�";
      else
           return "����Ϊ���µ����أ�"+query("name", ob)+"����������"+query("name", owner)+"֮�֣����ȥ����ɱ�ˣ��Ѷ���ȡ������";
     }
  }
        command("nod");
  ob->move(this_object());
   command("give fen to "+query("id", me)); 
  return "��"+query("name", ob)+"�����ȥ��ϣ�����ܺú����á�";
}
