#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_wldh();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();

void create()
{
        set_name("������", ({ "duan zhengchun", "duan", "zhengchun" }));
        set("title",  "����������󽫾�" );
        set("nickname", HIR "������" NOR);
        set("long", "�����Ǵ�������������������̫�ܣ��������İ���ʥ�֡�\n");
        set("gender", "����");
        set("age", 45);
        set("class", "royal");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 28);
        set("int", 30);
        set("con", 31);
        set("dex", 30);
        set("max_qi", 4500);
        set("max_jing", 3000);
        set("neili", 5800);
        set("max_neili", 5800);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 50000);

        set_skill("force", 220);
        set_skill("duanshi-xinfa", 220);
        set_skill("dodge", 200);
        set_skill("tiannan-bu", 200);
        set_skill("cuff", 220);
        set_skill("jinyu-quan", 220);
        set_skill("strike", 220);
        set_skill("wuluo-zhang", 220);
        set_skill("sword", 220);
        set_skill("staff", 220);
        set_skill("duanjia-jian", 220);
        set_skill("finger", 200);
        set_skill("qiantian-zhi", 200);
        set_skill("sun-finger", 200);
        set_skill("parry", 220);
        set_skill("jingluo-xue", 180);
        set_skill("literate", 240);
        set_skill("martial-cognize", 200);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "sun-finger");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "sun-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "sun-finger");

        prepare_skill("finger", "sun-finger");

        create_family("���ϻ���", 15, "����");

        set("inquiry", ([
                "Ǭ����ָ" : (: ask_skill1 :),
                "���Ʊ��" : (: ask_skill2 :),
                "��������" : (: ask_skill3 :),
                "����һ��" : (: ask_skill4 :),
                "�����"   : (: ask_skill5 :),
              	"����ɽ����" : (: ask_skill6 :),
                "һ������"   : (: ask_skill7 :),
                "���ִ��" : (: ask_wldh :),
                "����ׯ"   : (: ask_wldh :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "sword.jing" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver", 50);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() &&
            query_temp("juxianzhuang_step", ob) == 2){
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        set("inquiry/���ִ��", (: ask_wldh :));
        set("inquiry/����ׯ", (: ask_wldh :));

        //say( "������˵�����Ǻǣ���λ" + RANK_D->query_respect(ob) + "���þò����˰��������ɺã����Ҵ���������\n");
        command("say �Ǻǣ���λ" + RANK_D->query_respect(ob) + "���þò����˰��������ɺã����Ҵ���������\n");
        return;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("nod");
        command("say �Ҿ������㣬����ú�ѧϰ�Ҷμ��似������������Ϊ��");
        command("recruit "+query("id", ob));
        return;
}

mixed ask_wldh()
{
        object me = this_player();

        if( (int)query_temp("in_speech")
         || query_temp("juxianzhuang_step", me) != 2 )
                return notify_fail("���������Ի�Ŀ��˿��㡣����\n");

        set_temp("in_speech", 1);
        remove_call_out("say_msg");
        call_out("say_msg", 1, me, 1);
        return CYN"ԭ������Ϊ�˾���ׯ���ִ�����������ġ�" NOR;
}

int say_msg(object me, int index)
{
        object ob;

        if( environment() != environment(me) )
                return 0;

        switch( index ) {
        case(1):
                message_vision(CYN"$N˵������ʲô������˵�ˣ����ǲ���ȥ�μ�����ν�ġ����塱֮�ٵġ�\n"NOR, this_object(), me);
                break;
        case(2):
                message_vision(WHT"<$N������ü����ɫ΢΢���ࡣ>\n"NOR, this_object(), me);
                break;
        case(3):
                message_vision(CYN"$N˵���������ϵ��������������Ķ��ˣ�����û������ô���׵ģ��Ƿ���һ���е����������εĴ�Ӣ�ۣ�����ʿ��\n"NOR, this_object(), me);
                break;
        case(4):
                message_vision(CYN"$N˵�����Ҿ��������������϶���ʲô��ᣬ��ν��ɱ����ɱĸ��ɱʦ������һ�������Ƿ�ɵģ����������ݺ�����\n"NOR, this_object(), me);
                break;
        case(5):
                message_vision(CYN"$N˵�����Ƿ��������Ľ���ֵܣ��ǰ����֪���������ҵľ������ˣ��Ƿ�������������Σ��������ѵ�û��Ӣ�ۺú���\n"NOR, this_object(), me);
                break;
        case(6):
                message_vision(CYN"$N˵��������Ը���Ƿ干ͬ���ˡ����������������飬�����æ��\n"NOR, this_object(), me);
                break;
        case(7):
                message_vision(CYN"$N˵������һ���£��ǰ�������͸��쳤�ϡ����������Ѿ�˵�����Ҳ�ȥ�μӾ���ׯ���ִ������ɡ�\n"NOR, this_object(), me);
                message_vision(WHT"$N�ó�һ���Ž�����$n��\n"NOR, this_object(), me);
                ob = new("/clone/misc/letter");
                set("long", "����һ��"+this_object()->name()+"д���쳤�ϵ��ױ��ź���\n", ob);
                set("send_to", "xuzhanglao", ob);
                set("send_from",query("id",  me), ob);
                set("send_from_name", me->name(), ob);
                ob->move(me, 1);
                break;
        case(8):
                message_vision(CYN"$N˵�����ڶ����£��������һ���������ׯ�����Ƿ���Ը���һ�����ھ���ׯ���ֵģ��Ƿ����ڱ�ǧ����ָ��һ������Ҫ��æ��\n"NOR, this_object(), me);
                set_temp("juxianzhuang_step", 3, me);
                break;
        default:
                delete("inquiry/���ִ��");
                delete("inquiry/����ׯ");
                delete_temp("in_speech");
                return 1;
        }
        remove_call_out("say_msg");
        call_out("say_msg", 0, me,++index);
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/qiantian-zhi/zhi", me) )
                return "�㲻���Ѿ�ѧ����ô������ʲô���ʣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ������ǶμҵĴ��ˣ��⻰��ʲô��˼��";

        if (me->query_skill("qiantian-zhi", 1) < 1)
                return "����Ǭ��ָ����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<50 )
                return "��������µµ��Ϊ����������ŵù��㣿";

        if (me->query_skill("force") < 100)
                return "���ڹ�����Ϊ�������������������ɡ�";

        if( query("max_neili", me)<500 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("qiantian-zhi", 1) < 80)
                return "���Ǭ��ָ����������������������˵�ɡ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ����$N" HIY "������ߣ���"
                     "$N" HIY "���Ե���ϸ˵���ã�$N" HIY "һ����һ�߲�"
                     "ס�ĵ�ͷ�������Ӵ�������\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say ���кܼ򵥣��Լ���ϰ��ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�Ǭ����ָ����\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("qiantian-zhi"))
                me->improve_skill("qiantian-zhi", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qiantian-zhi/zhi", 1, me);
        addn("family/gongji", -50, me);

        return 1;
}


mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/wuluo-zhang/bian", me) )
                return "�㲻���Ѿ�ѧ����ô������ʲô���ʣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ������ǶμҵĴ��ˣ��⻰��ʲô��˼��";

        if (me->query_skill("wuluo-zhang", 1) < 1)
                return "�������������ƶ�ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<150 )
                return "��������µµ��Ϊ����������ŵù��㣿";

        if (me->query_skill("force") < 100)
                return "���ڹ�����Ϊ�������������������ɡ�";

        if( query("max_neili", me)<500 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("wuluo-zhang", 1) < 100)
                return "������������ƻ���������������˵�ɡ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ�����¸����𻰣������������"
                     "һ������ʱ���������Ӱ����ƮƮ�����˳�ȥ��ȴ��������"
                     "�ۡ�������$n" HIY "��Ӱ����ľ��羹��$N" HIY "��Χ��"
                     "����ӡ���������ӡ��\n\n" NOR, me, this_object());

        command("say ������ô��");
        tell_object(me, HIC "��ѧ���ˡ����Ʊ�á���\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("wuluo-zhang"))
                me->improve_skill("wuluo-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/wuluo-zhang/bian", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if( query("can_perform/jinyu-quan/man", me) )
                return "�㲻���Ѿ�ѧ����ô������ʲô���ʣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ������ǶμҵĴ��ˣ��⻰��ʲô��˼��";

        if (me->query_skill("jinyu-quan", 1) < 1)
                return "��������ȭ����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<150 )
                return "��������µµ��Ϊ����������ŵù��㣿";

        if (me->query_skill("force") < 100)
                return "���ڹ�����Ϊ�������������������ɡ�";

        if( query("max_neili", me)<500 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("jinyu-quan", 1) < 80)
                return "��Ľ���ȭ������������������˵�ɡ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ����$N" HIY "������ߣ���"
                     "$N" HIY "���Ե���ϸ˵���ã�$N" HIY "һ����һ�߲�"
                     "ס�ĵ�ͷ�������Ӵ�������\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say ���ˣ����Լ�ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ��������á���\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("jinyu-quan"))
                me->improve_skill("jinyu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/jinyu-quan/man", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/jing", me) )
                return "�㲻���Ѿ�ѧ����ô������ʲô���ʣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ������ǶμҵĴ��ˣ��⻰��ʲô��˼��";

        if (me->query_skill("duanjia-jian", 1) < 1)
                return "�����μҽ�����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<300 )
                return "��������µµ��Ϊ����������ŵù��㣿";

        if( query("shen", me)<0 )
                return "���˰ɣ��������ֻ������ȥ����";

        if (me->query_skill("force") < 120)
                return "����ڹ�����Ϊ�����������������ɡ�";

        if( query("max_neili", me)<800 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("duanjia-jian", 1) < 80)
                return "��Ķμҽ��������У�������˵�ɣ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ����������������͸�����ʾ"
                     "һ�飬�ɿ�����ˣ���˵��ֻ��$n" HIY "�γ����䳤��"
                     "������һ���������²�������������֮�������г���ʹ��"
                     "�������һ�㣬������$N" HIY "����ʽ֮���ʵ��$N"
                     HIY "ǰ��δ�š�\n\n" NOR, me, this_object());

        command("haha");
        command("say ��ʽ�Ѿ������ˣ����Լ���ȥ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�����һ������\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("duanjia-jian"))
                me->improve_skill("duanjia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/duanjia-jian/jing", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/lian", me) )
                return "�㲻���Ѿ�ѧ���������ô����Ҫ���������ҿɴ����㡣";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ������ǶμҵĴ��ˣ�����ʲô��˼��";

        if( query("shen", me)<0 )
                return "���˰ɣ��������ֻ������ȥ����";

        message_vision(CYN "$n" CYN "��$N" CYN "��Ц����������"
                       "�书ѧ��Ҳ���ã��㻹�����ʻ��ְɣ�\n" NOR,
                       me, this_object());

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/ailao", me) )
                return "�㲻���Ѿ�ѧ����ô������ʲô���ʣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ������ǶμҵĴ��ˣ��⻰��ʲô��˼��";

        if (me->query_skill("duanjia-jian", 1) < 1)
                return "�����μҽ�����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<500 )
                return "��������µµ��Ϊ����������ŵù��㣿";

        if( query("shen", me)<0 )
                return "���˰ɣ��������ֻ������ȥ����";

        if (me->query_skill("force") < 200)
                return "����ڹ�����Ϊ�����������������ɡ�";

        if( query("max_neili", me)<1500 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("duanjia-jian", 1) < 150)
                return "��Ķμҽ��������У�������˵�ɣ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ����������������͸�����ʾ"
                     "һ�飬�ɿ�����ˣ���˵��ֻ��$n" HIY "�γ����䳤��"
                     "����ͻ�䣬�����ݺᣬ����������������ǰ������������"
                     "��������������������ʮ��·����˲����ɡ�\n\n" NOR, me, this_object());

        command("haha");
        command("say ��ʽ�Ѿ������ˣ����Լ���ȥ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�����ɽ���⡹��\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("duanjia-jian"))
                me->improve_skill("duanjia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/duanjia-jian/ailao", 1, me);
        addn("family/gongji", -500, me);

        return 1;
}


mixed ask_skill7()
{
        object me;

        me = this_player();
        if( query("can_perform/duanjia-jian/yiyang", me) )
                return "�㲻���Ѿ�ѧ����ô������ʲô���ʣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ������ǶμҵĴ��ˣ��⻰��ʲô��˼��";

        if (me->query_skill("duanjia-jian", 1) < 1)
                return "�����μҽ�����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<800 )
                return "��������µµ��Ϊ����������ŵù��㣿";

        if( query("shen", me)<0 )
                return "���˰ɣ��������ֻ������ȥ����";

        if (me->query_skill("force") < 300)
                return "����ڹ�����Ϊ�����������������ɡ�";

        if( query("max_neili", me)<1000 )
                return "���������Ϊ�����������ߵ������ɡ�";

        if (me->query_skill("duanjia-jian", 1) < 120)
                return "��Ķμҽ��������У�������˵�ɣ�";

        message_sort(HIY "\n$n" HIY "���˵�ͷ����������������͸�����ʾ"
                     "һ�飬�ɿ�����ˣ���˵��ֻ��$n" HIY "�γ����䳤��"
                     "������������һ��ָָ����ע�������ϣ�������ý��"
                     "��\n\n" NOR, me, this_object());

        command("haha");
        command("say ��ʽ�Ѿ������ˣ����Լ���ȥ�ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�һ����������\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("duanjia-jian"))
                me->improve_skill("duanjia-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/duanjia-jian/yiyang", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}


/*
void unconcious()
{
        die();
}
*/
