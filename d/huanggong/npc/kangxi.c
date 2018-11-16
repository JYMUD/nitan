//kangxi.c �������

#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;

string * officer = ({
        "�ر�",
        "��˾",
        "�λ�",
        "�ν�",
        "����",
        "�ܱ�",
        "�ᶽ",
        "�ܶ�",
        "�󽫾�",
});
int ask_officer();
void dest(object ob);

void create()
{
        set_name(HIR "�������" NOR, ({"kang xi", "kang"}));
        set("title", "��ʥ��");
        set("gender", "����");
        set("age", 36);
        set("str", 25);
        set("dex", 20);
        set("int", 28);
        set("con", 28);
        set("per", 27);
        set("long", HIR @LONG
��λ�ߴ���࣬Ӣ�����������Ӿ������¶���Ŀ�����ۡ�
LONG NOR
        );

        set("combat_exp", 500000);
        set("score", 20000);
        set("shen_type", 1);
        set("attitude", "peaceful");


        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("literate", 100);
        set_skill("force", 100);
        set_skill("hunyuan-yiqi", 100);
        set_skill("shaolin-shenfa", 100);
        set_skill("finger", 100);
        set_skill("nianhua-zhi", 100);
        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "nianhua-zhi");
        map_skill("finger", "nianhua-zhi");
        prepare_skill("finger", "nianhua-zhi");

        set_temp("apply/attack", 50);
        set_temp("apply/defence", 50);
        set_temp("apply/armor", 30);
        set_temp("apply/damage", 35);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 600);
        set("max_jing", 600);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 80);

        set("inquiry", ([
                "ΤС��" : "\nС�����ҵ��ĸ�,������Ϊ���ռ������Ա����Ϣ.\n",
                "����": "\n�������ǿ���Ԫ��,��̫����ϸ���,�����ҵ��ĸ���.\n",
                "��ְ" : (:ask_officer:),
                "ְ��" : (:ask_officer:),
                "����" : (:ask_officer:),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
    "�������Ҷ��Ͽ��˿���\n",
                "����˵��������֮�£�Ī������������֮����Ī��������\n",
                "����˵��������ȡʿ�����ͻ��¡��ҳ����ϵ����£��������������¡� \n",
                "����˵������Ҫ��ְ����Ȼ�����ˡ�\n",
                "����˵����������ʮ���¾��ߣ����������͡�\n",
        }) );
        setup();
        carry_object(__DIR__"obj/jinduan")->wear();
        add_money("gold", 5);
}
int ask_officer()
{
        int lv, worked;
        string officerlvl;
        object ob = this_player();
        lv=query("officerlvl", ob);
        worked=query("bt/worked", ob);
        if (lv < 1) 
        {
                command("say"+query("name", ob)+"����û�и�����֪����ּ�������˺θɣ���\n");
                return 1;
  }
  if( query_temp("guard", ob) )
   {
    command("say"+query("name", ob)+"�����Ѿ�������͹�ְ�ˣ�����ȥ�ɣ�");
    return 1;
   }
  officerlvl = officer[lv-1];
        command("chat"+query("name", ob)+"�������ּ�⣬�Ҿ��������������ű���ʵ��"+officerlvl+"ְ֮��\n");
        set("guard", HIY+officerlvl+NOR, ob);
        set_temp("guard", 1, ob);
        return 1;
}

int accept_object(object me, object ob)
{
        object gold;
        object cloth;
        int exp,pot,score;
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0; 
        if ( !present(ob, me) ) return notify_fail("��û�����������");
        if( query("id", ob) == "book1" )
        {
                set_temp("book14/1", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else if( query("id", ob) == "book2" )
        {
                set_temp("book14/2", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else if( query("id", ob) == "book3" )
        {
                set_temp("book14/3", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book4" )
        {
                set_temp("book14/4", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book5" )
        {
                set_temp("book14/5", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book6" )
        {
                set_temp("book14/6", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book7" )
        {
                set_temp("book14/7", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        if( query("id", ob) == "book8" )
        {
                set_temp("book14/8", 1, me);
                command("smile"+query("id", me));
                call_out("dest",0,ob);
        }
        else
        {
                command("shake ");
                command("say ��ֻ��������ʮ���¾����������¡�");
        }
        if( query_temp("book14/1", me) && 
             query_temp("book14/2", me) && 
             query_temp("book14/3", me) && 
             query_temp("book14/4", me) && 
             query_temp("book14/5", me) && 
             query_temp("book14/6", me) && 
             query_temp("book14/7", me) && 
             query_temp("book14/8", me) )
        {
                command("chat"+query("name", me)+"�����һذ˲���ʮ���¾����й�����𢣬�ͻ����һ����\n");
                cloth = new(__DIR__"obj/ycloth");
                delete_temp("book14", me);
                cloth -> move(me);
                gold = new("/clone/money/gold");
                gold->set_amount(20);
                gold->move(this_object());
                command("give20goldto"+query("id", me));
                if( !query("skybook/luding/42jing", me) )
   {
                 set("skybook/luding/42jing", 1, me);
                 exp=500+random(1000);
     pot=exp/2;
     score=pot/2;
     addn("combat_exp", exp, me);
     addn("potential", pot, me);
             tell_object(me,HIC"��ɹ��õ��˿��������Σ�\n�����������������"+
                      chinese_number(exp)+"�㾭�顢"+
               chinese_number(pot)+"��Ǳ���Լ�"+
               chinese_number(score)+"�㽭��������\n\n"NOR);
                }
                
        }
        return 1;
}

void dest(object ob)
{
        destruct(ob);
}