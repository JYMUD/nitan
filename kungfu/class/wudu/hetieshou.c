#include <ansi.h>
#include "wudu.h"

#define SHEYING     "/clone/lonely/sheying"
#define JINWUGOU    "/clone/lonely/jinwugou"
#define ZHUSUO      "/clone/lonely/zhusuo"
#define DUJING      "/clone/lonely/book/dujing3"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_gou();
mixed ask_suo();
mixed ask_she();
mixed ask_jing();
int ask_me();
string ask_ling();
void create()
{
        object ob, ob2;
        set_name("������", ({ "he tieshou", "he", "tieshou" }));
        set("nickname", HIR "�嶾����" NOR);
        set("long",@LONG
��������һ��һ��ۺ�ɴȹ��Ц���绨����Ů��
�����ü���ѩ�ף�üĿ�续������һ˫���۵���
�㣬�ֽ��϶����������Ľ���˭���뵽������
�嶾�̵Ľ��������֣�������ʿ�������޲�����
�ľ���
LONG);
        set("title", "�嶾�̽���");
        set("gender", "Ů��");
        set("age", 25);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);

        set("max_qi", 5000);
        set("max_jing", 4000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 600);
        set_skill("wudu-shengong", 600);
        set_skill("xiuluo-yinshagong", 600);
        set_skill("dodge", 600);
        set_skill("wudu-yanluobu", 600);
        set_skill("strike", 600);
           set_skill("tianchan-zhang", 600);
        set_skill("hand", 600);
        set_skill("qianzhu-wandushou", 600);
        set_skill("claw", 600);
        set_skill("wusheng-zhao", 600);
        set_skill("parry", 600);
        set_skill("sword", 600);
        set_skill("jinwu-goufa", 600);
        set_skill("whip", 600);
        set_skill("ruanhong-zhusuo", 600);
        set_skill("xiewei-bian", 600);
        set_skill("throwing", 600);
        set_skill("hansha-sheying", 600);
        set_skill("literate", 600);
        set_skill("poison", 600);
        set_skill("wudu-qishu", 600 );
        set_skill("martial-cognize", 600);
        set_skill("wudu-jing", 600);

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "wudu-yanluobu");
        map_skill("strike", "tianchan-zhang");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("claw", "wusheng-zhao");
        map_skill("throwing", "hansha-sheying");
        map_skill("parry", "jinwu-goufa");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");

        prepare_skill("claw", "wusheng-zhao");
        prepare_skill("strike", "tianchan-zhang");

        create_family("�嶾��", 11, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.teng" :),
                (: perform_action, "whip.pan" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suo" :),
                (: perform_action, "claw.lian" :),
                (: perform_action, "strike.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();

        set("inquiry", ([
                "���ڹ�"   : (: ask_gou :),
                "�������" : (: ask_suo :),
                "��ɳ��Ӱ" : (: ask_she :),
                "����"     : "����Ҫ������ƪ����ƪ������ƪ��",
                "��ƪ"     : "������ƪ��ȥ�������ҵĵ���Ҫ�ɡ�",
                "������ƪ" : "������ƪ��ȥ�������ҵĵ���Ҫ�ɡ�",
                "��ƪ"     : "������ƪ���볤�����У���ȥ����Ҫ�ɡ�",
                "������ƪ" : "������ƪ���볤�����У���ȥ����Ҫ�ɡ�",
                "��ƪ"     : (: ask_jing :),
                "������ƪ" : (: ask_jing :),
                "����"     : "��Ҫ��ʲô���У�",
                "����"     : "��Ҫ��ʲô������",
                //"�򶾿�"    : (: ask_me :),
                "�嶾��"    : (: ask_ling :),
                "���߾�"   : "��һ����ȥ���볤��ѧ�ɡ�",
                "��ӥ��"   : (: ask_skill1 :),
                "������"   : (: ask_skill2 :),
                "������"   : (: ask_skill3 :),
                "�𹳶���" : (: ask_skill4 :),
                "��Ӱ��"   : (: ask_skill5 :),
                "�򶾴���" : (: ask_skill6 :),
        ]));

        if (clonep())
        {
                ob = find_object(ZHUSUO);
                ob2 = find_object(SHEYING);

                if (! ob) ob = load_object(ZHUSUO);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = find_object(JINWUGOU);
                        if (! ob) ob = load_object(JINWUGOU);
                        if (! environment(ob))
                        {
                                ob->move(this_object());
                                ob->wield();
                        } else
                        {
                                ob = new("/clone/weapon/changbian");
                                ob->move(this_object());
                                ob->wield();
                        }
                }
                if (! ob2) ob2 = load_object(SHEYING);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                }
        }
        carry_object("/clone/cloth/moon-dress")->wear();
}

void init()
{
        add_action("do_show", "show");
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)>-1000 )
        {
                command("say ��Խ����Խ���������������Եס�");
                return;
        }

        if( query("shen", ob)>-50000 )
        {
                command("say ���������Ĵ���������Ǹɲ��ɴ��µģ�");
                return;
        }

        if( query("combat_exp", ob)<350000 )
        {
                command("say �����ھ�����ǳ��������������书��������ȥ�����㾭��ɡ�");
                return;
        }

        if ((int)ob->query_skill("wudu-shengong", 1) < 120)
        {
                command("say ����嶾�ķ���ѧ�Ĳ�������");
                return;
        }

        if ((int)ob->query_skill("wudu-qishu", 1) < 120)
        {
                command("say ��ѱ��ŵ�ʩ����ѧ����͸���������Ұɡ�");
                return;
        }

        command("say �ðɣ���Ȼ��˱���������������ͽ�ܡ�");
        command("recruit "+query("id", ob));
        set("title", "�嶾�̳���", ob);
        return;
}

mixed ask_gou()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "�嶾��" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "������Ϊ���嶾�̵��ӣ�����ѧ����ʼ���"
                                       "���ˣ���Ȼ����������Ҫ�𹳣���\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��Цһ������$n" CYN "˵��"
                                       "��������ʲô�ˣ���Ȼ��������ǰ�������"
                                       "����\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "�嶾��" )
                return "�㲻�������嶾�̵ģ���������ʲô��";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ����ý��ڹ�������ȥ��ֻ�����Ҷ�����";

        if( query("shen", me)>-35000 )
                return "�������Ĵ���������㲻��Ҳ�ա�";

        if (me->query_skill("jinwu-goufa", 1) < 120)
                return "�������ڹ�����ûѧ�ã������ý�Ҳ�ǰ״";

        ob = find_object(JINWUGOU);
        if (! ob) ob = load_object(JINWUGOU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�ţ����ڹ����ڲ���������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ�������Ѿ��ѽ��ڹ������ͬ��ʦ�ֵ���ȥ�ˡ�";

                if( query("family/family_name", owner) == "�嶾��" )
                        return "���ڹ�������ʱ����ͬ��ʦ�ֵ�"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "���ŵĽ��ڹ���������"+query("name", owner)+
                               "���У���ȥ�����������ɣ�";
        }

        ob->move(this_object());

        ob = new("clone/weapon/changbian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "΢΢һЦ��������������ڹ����"
                       "��ȥ������Щ������ʿ�������嶾�̵���������\n" NOR,
                       this_object(), me);
          command("give jinwu gou to "+query("id", me));
        return 1;
}

mixed ask_suo()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "�嶾��" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "������Ϊ���嶾�̵��ӣ�����ѧ����ʼ���"
                                       "���ˣ���Ȼ����������Ҫ�����������\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��Цһ������$n" CYN "˵��"
                                       "��������ʲô�ˣ���Ȼ��������ǰ�������"
                                       "����\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "�嶾��" )
                return "�㲻�������嶾�̵ģ���������ʲô��";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ������������������ȥ��ֻ�����Ҷ�����";

        if( query("shen", me)>-35000 )
                return "�������Ĵ������������㲻��Ҳ�ա�";

        if (me->query_skill("ruanhong-zhusuo", 1) < 150)
                return "�������������ûѧ�ã�����������Ҳ�ǰ״";

        ob = find_object(ZHUSUO);
        if (! ob) ob = load_object(ZHUSUO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�ţ�����������ڲ���������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ�������Ѿ���������������ͬ��ʦ�ֵ���ȥ�ˡ�";

                if( query("family/family_name", owner) == "�嶾��" )
                        return "�������������ʱ����ͬ��ʦ�ֵ�"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "���ŵ����������������"+query("name", owner)+
                               "���У���ȥ�����������ɣ�";
        }

        ob->move(this_object());

        ob = new("/clone/weapon/changbian");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "΢΢һЦ���������������������"
                       "��ȥ������Щ������ʿ�������嶾�̵���������\n" NOR,
                       this_object(), me);
          command("give ruanhong zhusuo to "+query("id", me));
        return 1;
}

mixed ask_she()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "�嶾��" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "������Ϊ���嶾�̵��ӣ�����ѧ����ʼ���"
                                       "���ˣ���Ȼ����������Ҫ��ɳ��Ӱ����\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��Цһ������$n" CYN "˵��"
                                       "��������ʲô�ˣ���Ȼ��������ǰ�������"
                                       "����\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "�嶾��" )
                return "�㲻�������嶾�̵ģ���������ʲô��";

        if( query("shen", me)>-10000 )
                return "�������Ĵ������⺬ɳ��Ӱ�㲻��Ҳ�ա�";

        if (me->query_skill("hansha-sheying", 1) < 50)
                return "�����Ű����ַ�̫��ò��û����˼�����";

        //ob = new("/d/wudu/npc/obj/hanshasheying");
        ob = find_object(SHEYING);
        if (! ob) ob = load_object(SHEYING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�ţ���ɳ��Ӱ���ڲ���������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��ɳ��Ӱ���ڲ��������";

                if( query("family/family_name", owner) == "�嶾��" )
                        return "��ɳ��Ӱ������ʱ����ͬ��"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "�ҵĺ�ɳ��Ӱ��������"+query("name", owner)+
                               "���У���ȥ�����������ɣ�";
        }
        ob->move(this_object());

        message_vision(CYN "$N" CYN "΢΢һЦ��������ɳ��Ӱ����ȥ�ɣ������ǳ�����"
                       "���嶾�̵�������\n" NOR, this_object(), me);
          command("give hansha sheying to "+query("id", me));
        command("whisper"+query("id", me)+"�⺬ɳ��Ӱ��Ķ��������ˣ�������"
                "(show)�������Ҹ���װ��");
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/ruanhong-zhusuo/panying", me) )
                return "�㲻���Ѿ�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "�������������ûѧ����̸���ԣ�";

        if( query("family/gongji", me)<300 )
                return "���ڽ��������Ĺ��׻������������Ҳ�æ���㡣";

        if( query("shen", me)>-30000 )
                return "�Ĵ����������Զ�ɲ��˴����������㲻ѧҲ�գ�";

        if (me->query_skill("ruanhong-zhusuo", 1) < 130)
                return "���������������ò����ң��Լ���ȥ���������ɣ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ��������ȡ�³�������������һ������"
                     "ʱ��Ӱ���أ���ȫ����$N" HIY "�����ܣ�ֱ����$N" HIY "Ŀ�ɿ�"
                     "����\n\n" NOR, me, this_object());

        command("nod");
        command("say ��һ�б����������������ӥ������ɿ������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ���ӥ������\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruanhong-zhusuo/panying", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/ruanhong-zhusuo/bohu", me) )
                return "�㲻���Ѿ�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "�������������ûѧ����̸���ԣ�";

        if( query("family/gongji", me)<1300 )
                return "���ڽ��������Ĺ��׻������������Ҳ�æ���㡣";

        if( query("shen", me)>-50000 )
                return "�Ĵ����������Զ�ɲ��˴����������㲻ѧҲ�գ�";

        if (me->query_skill("ruanhong-zhusuo", 1) < 160)
                return "���������������ò����ң��Լ���ȥ���������ɣ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ�����������������㴫�����У����"
                     "�����ˣ���$n" HIY "˵�գ�������ȡ�³�����һ�����ȣ����г�"
                     "�����裬�����Ӱ��ʱ��������СȦ������ǵ�����$N" HIY "��"
                     "\n\n" NOR, me, this_object());

        command("nod");
        command("say ��һ�б������������������������ɿ������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ�����������\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruanhong-zhusuo/bohu", 1, me);
        addn("family/gongji", -1300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/ruanhong-zhusuo/suolong", me) )
                return "�㲻���Ѿ�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("ruanhong-zhusuo", 1) < 1)
                return "�������������ûѧ����̸���ԣ�";

        if( query("shen", me)>-80000 )
                return "�Ĵ����������Զ�ɲ��˴����������㲻ѧҲ�գ�";

        if( query("family/gongji", me)<1500 )
                return "���ڽ��������Ĺ��׻������������Ҳ�æ���㡣";

        if (me->query_skill("ruanhong-zhusuo", 1) < 160)
                return "���������������ò����ң��Լ���ȥ���������ɣ�";

        message_sort(HIY "\n$n" HIY "��$N" HIY "����ص��˵�ͷ����������Ȼ����"
                     "�����ģ���������ٴ������У���˵��$n" HIY "�������֣�$N"
                     HIY "��æ����ǰȥ��ֻ��$n" HIY "������$N" HIY "˵��Щ����"
                     "�������г���һ������ʱ�ó������Ӱ����������ͨ�죬������"
                     "Ӱһ��������˷�ϯ���ȥ��\n\n" NOR, me, this_object());

        command("sweat");
        command("nod");
        command("say ��һ�б��������������������������ȥ���ڼ���ϰ��");
        tell_object(me, HIC "��ѧ���ˡ�����������\n" NOR);

        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("ruanhong-zhusuo"))
                me->improve_skill("ruanhong-zhusuo", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruanhong-zhusuo/suolong", 1, me);
        addn("family/gongji", -1500, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/jinwu-goufa/duo", me) )
                return "�������Ѿ��̹����ˣ������Լ���ȥ�����ϰ�ɣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("jinwu-goufa", 1) < 1)
                return "�������ڹ�����ûѧ����̸���ԣ�";

        if( query("family/gongji", me)<1300 )
                return "���ڽ��������Ĺ��׻������������Ҳ�æ���㡣";

        if( query("shen", me)>-80000 )
                return "�ߣ��������Ĵ������ܸɳ�ʲô�£������㲻ѧҲ�գ�";

        if (me->query_skill("jinwu-goufa", 1) < 160)
                return "��Ľ��ڹ��������ò����ң��Լ���ȥ���������ɣ�";

        message_sort(HIY "\n$n" HIY "΢΢���˵�ͷ����$N" HIY "��������˵��Щ��"
                     "��һ��˵��һ�߱Ȼ���Щʲô�������㣬�������á���\n\n"
                     NOR, me, this_object());

        command("say �ղ���Щ�������еĿھ���������Ҫ�죬���Ҫ�����ˡ�");
        command("nod");
        command("say ���н𹳶��ǱȽ����������Լ�������Ҫ����о���");
        tell_object(me, HIC "��ѧ���ˡ��𹳶��ǡ���\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("jinwu-goufa"))
                me->improve_skill("jinwu-goufa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinwu-goufa/duo", 1, me);
        addn("family/gongji", -1300, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/hansha-sheying/zhen", me) )
                return "�����Ҳ����Ѿ��̹�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("hansha-sheying", 1) < 1)
                return "������ɳ��Ӱ��ûѧ����̸���ԣ�";

        if( query("family/gongji", me)<300 )
                return "���ڽ��������Ĺ��׻������������Ҳ�æ���㡣";

        if( query("shen", me)>-80000 )
                return "�ߣ��������Ĵ������ܸɳ�ʲô�£������㲻ѧҲ�գ�";

        if (me->query_skill("hansha-sheying", 1) < 120)
                return "��ĺ�ɳ��Ӱ�����ò����ң��Լ���ȥ���������ɣ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ�����ֽ�$N" HIY "�е���ǰ����$N"
                     HIY "���������ֹ���Щ����$N" HIY "���˰��죬ͻȻ�䲻�ɻ�"
                     "�ĵ�һЦ��������������\n\n" NOR, me, this_object());

        command("nod");
        command("say ���в������ӣ���������͵Ϯ�Ͱ������ȴ����Ч����������ɣ�");
        tell_object(me, HIC "��ѧ���ˡ���Ӱ�롹��\n" NOR);
        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("hansha-sheying"))
                me->improve_skill("hansha-sheying", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hansha-sheying/zhen", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/qianzhu-wandushou/chuan", me) )
                return "�����Ҳ����Ѿ��̹�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�";

        if( !query("reborn/times", me) )
                return "�㻹δ�������ѣ����ž����ɲ�����㴫���㡣";

        if( query("family/gongji", me)<2000 )
                return "���ڽ��������Ĺ��׻������������Ҳ�æ���㡣";

        if( query("shen", me)>-100000 )
                return "�ߣ��������Ĵ������ܸɳ�ʲô�£������㲻ѧҲ�գ�";

        if (me->query_skill("qianzhu-wandushou", 1) < 800)
                return "���ǧ�����ֻ����ò����ң��Լ���ȥ���������ɣ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ�����ֽ�$N" HIY "�е���ǰ����$N"
                     HIY "���������ֹ���Щ����$N" HIY "���˰��죬ͻȻ�䲻�ɻ�"
                     "�ĵ�һЦ��������������\n\n" NOR, me, this_object());

        command("nod");
        command("say ���п��Ǳ����ش�����Ϊ���������ȥ��ɵö���ϰ��ϰ��");
        tell_object(me, HIC "��ѧ���ˡ��򶾴��ġ���\n" NOR);
        if (me->can_improve_skill("qianzhu-wandushou"))
                me->improve_skill("qianzhu-wandushou", 1500000);
        if (me->can_improve_skill("hand"))
                me->improve_skill("qianzhu-wandushou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qianzhu-wandushou/chuan", 1, me);
        addn("family/gongji", -2000, me);
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != JINWUGOU
        && base_name(ob) != ZHUSUO)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say ��л��λ" + RANK_D->query_respect(me) + "�����ű��ｻ�ء�");
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
        return 1;
}

mixed ask_jing()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "�嶾��" )
                return "����˭������ʶ��ô��";

        if( query("shen", me)>-30000 )
                return "�������ĳ���ô�ã���ȥѧ��������";

        if( query("combat_exp", me)<150000 )
                return "�����ھ���̫ǳ������æ��ȥ�Ķ�������";

        if (me->query_skill("wudu-qishu", 1) > 149)
                return "��Ա��ŵĶ����Ѿ�ͨ���ñȽ�͸���ˣ������Լ����о��ɡ�";

        ob = find_object(DUJING);
        if (! ob) ob = load_object(DUJING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "������������ô����ô�����������ˣ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���š�������ƪ���ڲ��������";

                if( query("family/family_name", owner) == "�嶾��" )
                        return "������������ͬ��"+query("name", owner)+
                               "�ڿ���ȥ�����ɡ�";
                else
                        return "�ҽ̵Ķ���������"+query("name", owner)+
                               "�����У���ȥ����������ɣ�";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "��ͷ��������ȥ���ɣ����в���֮��"
                       "���������ҡ�\n" NOR, this_object(), me);
          command("give du jing3 to "+query("id", me));
        return 1;
}

int do_show(string arg)
{
        object ob;
        object me;
        int n;

        if (! arg)
                return notify_fail("��Ҫ����ʲô������\n");

        me = this_player();

        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");

        if( query("family/family_name", me) != "�嶾��" )
                return notify_fail(CYN "����������������һ�ۣ�û���㡣\n" NOR);

        if( query("id", ob) != "hanshasheying" )
                return notify_fail(CYN "������������üͷ��˵��������ҿ����"
                                   "���\n" NOR);

        if( query("equipped", ob) )
                return notify_fail(CYN "������˵�����㲻�Ѻ�ɳ��Ӱ����������"
                                   "����ô����װ�룿\n" NOR);

        if( query("zhen", ob)>5 )
                return notify_fail(CYN "������˵������ɳ��Ӱ��Ķ�������һ��"
                                   "����������Ϲ��ʲô��\n" NOR);

        message_vision(HIC "\n������΢΢һЦ����$N" HIC "���нӹ���ɳ��Ӱ����"
                       "�ᲦŪ���£��ֻ�����$N" HIC "��\n\n" NOR, me);

        command("say ���ˣ���ɳ��Ӱ��Ķ����Ѿ������ˡ�");
        set("zhen", 10, ob);
        return 1;
}

string ask_ling()
{
        mapping fam;
        object *allob,env,ob,me=this_player();
        string *sname;
        int i, count, here = 0;

        if (query("ling_count") < 1)
                return "�������ˣ��嶾���Ľ����������ء�\n";
        if( !(fam=query("family", me)) || fam["family_name"] != "�嶾��" )
                return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��";

        if( query("duchong_cun", me) == 1 )
                return "��Ķ��治���ڶ����Ǻúõ�ô��";

        env = environment(me);
        allob = all_inventory(env);
        count = 0;
        for(i=0; i<sizeof(allob); i++)
                if(allob[i] != me && allob[i]!=this_object() )
                {
                        if( query("host_id", allob[i]) == query("id", me) )
                        {
                                here = 1;
                        }
                        count++;
                }
        if (here == 1)
                return "��Ķ��治�Ǵ���������𣡣�";
        if( query("duchong_cun", me) == 0 && count >= 1 )
                return "�����˶����ӣ����ͷ�����ɣ�";

        if( !query("du/id", me) )
                return "��û������ɣ�";

        addn("ling_count",-1);
        ob = new(__DIR__"obj/wudu-ling");
        ob->move(me);
        message_vision("$N���һ���嶾�\n",me);
        remove_call_out ("give_wuduling");
        call_out ("give_wuduling", 600); // 10 ����

        return "�ðɣ�ƾ�����嶾����ȥҪ����Ķ��档";

}

void unconcious()
{
        die();
}
