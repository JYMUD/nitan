// This program is a part of NT MudLIB

#include <ansi.h>
#include "xueshan.h"

#define JINLUN    "/clone/unique/jinlun"
#define JIASHA    "/clone/unique/jiasha"

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
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill10();

mixed ask_lun();
mixed ask_midao();

void create()
{
        object ob1, ob2;
        set_name("���ַ���", ({ "jinlun fawang", "jinlun", "fawang" }));
        set("long", @LONG
������ѩɽ�µĻ��̷�������Ϊ�ɹŹ�ʦ����
�ܳɼ�˼�����ã��������������ս��������
ԭ���֣���λ�Ժ�����ޱȡ����ַ���̤����
ԭ�󺱷���֣�������ԭȺ�ۡ������֮����
����ν�����һ�ˡ�
LONG);
        set("nickname", HIY "�ɹŹ�ʦ" NOR);
        set("gender", "����");
        set("class", "bonze");
        set("age", 58);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("str", 33);
        set("int", 35);
        set("con", 38);
        set("dex", 33);

        set("max_qi", 6500);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 220);
        set("level", 40);
        set("combat_exp", 4000000);
        set("score", 500000);

        set_skill("force", 420);
        set_skill("mizong-neigong", 420);
        set_skill("unarmed", 420);
        set_skill("longxiang-gong", 420);
        set_skill("dodge", 400);
        set_skill("shenkong-xing", 400);
        set_skill("hammer", 420);
        set_skill("riyue-lun", 420);
        set_skill("dali-chu", 400);
        set_skill("xiangmo-chu", 400);
        set_skill("sword", 400);
        set_skill("mingwang-jian", 400);
        set_skill("dagger", 480);
        set_skill("finger", 480);
        // set_skill("poxu-daxuefa", 280);
        set_skill("hand", 480);
        set_skill("dashou-yin", 480);
        set_skill("cuff", 480);
        set_skill("yujiamu-quan", 480);
        set_skill("parry", 400);
        set_skill("lamaism", 400);
        set_skill("literate", 400);
        set_skill("sanscrit", 400);
        set_skill("martial-cognize", 300);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "longxiang-gong");
        map_skill("unarmed", "longxiang-gong");
        map_skill("hammer", "riyue-lun");
        map_skill("dagger", "poxu-daxuefa");
        map_skill("sword", "mingwang-jian");
        map_skill("finger", "poxu-daxuefa");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("unarmed", "longxiang-gong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hammer.po" :),
                (: perform_action, "hammer.yuan" :),
                (: perform_action, "hammer.lian" :),
                (: perform_action, "unarmed.tun" :),
                (: perform_action, "unarmed.die" :),
                (: perform_action, "unarmed.ji" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
        }));

        create_family("ѩɽ��", 2, "���̷���");

        set("inquiry", ([
                "���½���"  : (: ask_lun :),
                "�ܵ�"      : (: ask_midao :),
                "�ص�"      : (: ask_midao :),
                "���ӡ"    : (: ask_skill1 :),
                "���޽���"  : (: ask_skill2 :),
                "����"      : (: ask_skill3 :),
                "��ħ"      : (: ask_skill4 :),
                "������"    : (: ask_skill5 :),
                "Բ����"    : (: ask_skill6 :),
                "������ת"  : (: ask_skill7 :),
                "������"    : (: ask_skill8 :),
                "�����"    : (: ask_skill9 :),
                "������"    : (: ask_skill10 :),
                "�������"  : "���Ǵ�˵�е���ʽ��������Ҳδ������",
                "��Ԫͨ��"  : "��һ����ȥ�û���������ˡ�",
                "�������"  : "��һ����ȥ�ô���ͽ�����ˡ�",
                "�����"    : "��һ����ȥ�ô���ͽ�����ˡ�",
                "��������"  : "�����ҵ�������Ʒ����������������",
                "���־�ת"  : "������ȥ����骽ӿڣ���������˵���",
        ]));

        set("master_ob", 1);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        if (clonep())
        {
                //ob=new(WEAPON_DIR"treasure/jinlun");
                ob1 = find_object(JINLUN);
                if (! ob1) ob1 = load_object(JINLUN);
                if (! environment(ob1))
                {
                        ob1->move(this_object());
                        ob1->wield();
                }
        }

        if (clonep())
        {
                ob2 = find_object(JIASHA);
                if (! ob2) ob2 = load_object(JIASHA);
                if (! environment(ob2))
                {
                        ob2->move(this_object());
                        ob2->wear();
                } else
                {
                        ob2 = new("/d/xueshan/obj/p-jiasha");
                        ob2->move(this_object());
                        ob2->wear();
                }
                carry_object("/d/xueshan/obj/xuelian");
        }
        carry_object("/d/xueshan/obj/sengmao")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "����" )
        {
                command("say ��ϰ�����ڹ���Ҫ����֮�塣");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "������ذɣ�");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say �ҷ��ŵ����������ࡣ");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "������ذɣ�");
                return;
        }

        if( query("combat_exp", ob)<450000 )
        {
                command("say ���ʵս���鲻�㣬���ǻ�ȥ�������ȡ�");
                return;
        }

        if( query("shen", ob)>-80000 )
        {
                command("say ������̫�������ɲ���ʲô����");
                return;
        }

        if ((int)ob->query_skill("mizong-neigong", 1) < 120)
        {
                command("say ���ڹ���ô���ô���и�����似��");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 150)
        {
                command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
                return;
        }

        command("nod");
        command("say ���������Ͻ����Ժ�͸����Ұɣ�");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/dashou-yin/yin", me) )
                return "�������Ѿ��̹����ˣ��Լ���ȥ����ϰ��ϰ�ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("dashou-yin", 1) < 1)
                return "��������ӡ��ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<200 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-15000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if (me->query_skill("force") < 140)
                return "����ڹ���Ϊ���㣬����ѧ������һ�С�";

        if( query("max_neili", me)<1000 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("dashou-yin", 1) < 100)
                return "����Ѵ���ӡ�������������Ϸ�";

        message_sort(HIY "\n$n" HIY "΢΢һ㶣����´�����$N" HIY "һ������"
                     "�˵�ͷ������������ģ�����ׯ�أ�˫��Я�ž��������$N"
                     HIY "��ǰ��һ�������������䣬��ʱֻ���ú�Ȼ�����죬��"
                     "���ڵ���ұ�$n" HIY "�������������Ĵ������������"
                     "������������ɢ��$N" HIY "��ŷ����������������ϻ�"
                     "ȻǶ��һ˫��ӡ��\n\n" NOR, me, this_object());

        command("nod");
        command("say ֻҪ�ڹ����������в���������");
        tell_object(me, HIC "��ѧ���ˡ����ӡ����\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("dashou-yin"))
                me->improve_skill("dashou-yin", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/dashou-yin/yin", 1, me);
        addn("family/gongji", -200, me);

        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/yujiamu-quan/jiang", me) )
                return "�������Ѿ��̹����ˣ��Լ���ȥ����ϰ��ϰ�ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("yujiamu-quan", 1) < 1)
                return "����������ĸȭ��ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<300 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-18000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if (me->query_skill("force") < 150)
                return "����ڹ���Ϊ���㣬����ѧ������һ�С�";

        if( query("max_neili", me)<1200 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("yujiamu-quan", 1) < 100)
                return "����ѽ�����ĸȭ�������������Ϸ�";

        message_sort(HIY "\n$n" HIY "��΢���˵�ͷ���������һ�������ݲ���"
                     "ǰ����Ŀ��ȣ�ȭ�е��������籼�ף���ʱ����$N" HIY "��"
                     "����ȭ����ʽ��Ϊ���ʵ��$N" HIY "ǰ��δ�š�\n\n"
                     NOR, me, this_object());;

        command("nod");
        command("say ������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ����޽�������\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("yujiamu-quan"))
                me->improve_skill("yujiamu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/yujiamu-quan/jiang", 1, me);
        addn("family/gongji", -300, me);

        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/ruo", me) )
                return "�������Ѿ��̹����ˣ��Լ���ȥ����ϰ��ϰ�ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "����������������ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<100 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-10000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if (me->query_skill("force") < 140)
                return "����ڹ���Ϊ���㣬����ѧ������һ�С�";

        if( query("max_neili", me)<1200 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("mingwang-jian", 1) < 100)
                return "����Ѳ����������������������Ϸ�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ��Ҳ���𻰣���$N" HIY "��"
                     "�нӹ���������������һ����������ʱ����һ��ͳ���"
                     "���������������$N" HIY "ֻ�е���ͷһ�𣬾�ӿ��һ"
                     "��Ī���ı�����\n\n" NOR, me, this_object());

        command("haha");
        command("say �����ܼ򵥣����Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ���������\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/ruo", 1, me);
        addn("family/gongji", -100, me);

        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if( query("can_perform/mingwang-jian/xiang", me) )
                return "�������Ѿ��̹����ˣ��Լ���ȥ����ϰ��ϰ�ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("mingwang-jian", 1) < 1)
                return "����������������ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<400 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-15000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if (me->query_skill("force") < 180)
                return "����ڹ���Ϊ���㣬����ѧ������һ�С�";

        if( query("max_neili", me)<1600 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("mingwang-jian", 1) < 140)
                return "����Ѳ����������������������Ϸ�";

        message_sort(HIY "\n$n" HIY "��$N" HIY "΢΢һЦ���漴������֣���"
                     "ʳ��ָ��£���������������͡���һ���յ��������ʱ��"
                     "��֮�����죬һ��������ָ��ŷ�����$N" HIY "��������"
                     "ɮ�۴�͸��һ��С�ס�\n\n" NOR, me, this_object());

        command("nod");
        command("say ���в�������Խ���ý���������ˡ�");
        tell_object(me, HIC "��ѧ���ˡ���ħ����\n" NOR);

        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 1500000);
        if (me->can_improve_skill("mingwang-jian"))
                me->improve_skill("mingwang-jian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mingwang-jian/xiang", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/riyue-lun/po", me) )
                return "��������ʲô���Լ���ȥ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("riyue-lun", 1) < 1)
                return "���������ַ���ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<800 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-50000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if (me->query_skill("longxiang-gong", 1) < 30)
                return "��������������Ϊ���㣬��ѧ������һ�С�";

        if (me->query_skill("force") < 180)
                return "����ڹ���Ϊ���㣬����ѧ������һ�С�";

        if( query("max_neili", me)<1500 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("riyue-lun", 1) < 120)
                return "����������ַ��������������ҡ�";

        message_sort(HIY "\n$n" HIY "��˼Ƭ�̣����ŵ��˵�ͷ�����ֽ�$N" HIY
                     "������ߣ�������$P" HIY "���Ե���ϸ˵���ã�$N" HIY
                     "���󲻽����ĵ�һЦ���ƺ���$n" HIY "�Ľ̵���������"
                     "��\n\n" NOR, me, this_object());

        command("grin");
        command("say ���Ҹղ�˵�ļ��Σ��Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������ơ���\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/riyue-lun/po", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/riyue-lun/yuan", me) )
                return "��������ʲô���Լ���ȥ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("riyue-lun", 1) < 1)
                return "���������ַ���ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<800 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-50000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if (me->query_skill("longxiang-gong", 1) < 30)
                return "��������������Ϊ���㣬��ѧ������һ�С�";

        if (me->query_skill("force") < 180)
                return "����ڹ���Ϊ���㣬����ѧ������һ�С�";

        if( query("max_neili", me)<1500 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("riyue-lun", 1) < 120)
                return "����������ַ��������������ҡ�";

        message_sort(HIY "\n$n" HIY "��˼Ƭ�̣����ŵ��˵�ͷ�����ֽ�$N" HIY
                     "������ߣ�������$P" HIY "���Ե���ϸ˵���ã�$N" HIY
                     "���󲻽����ĵ�һЦ���ƺ���$n" HIY "�Ľ̵���������"
                     "��\n\n" NOR, me, this_object());

        command("nod");
        command("say ��Ȼ���п�ʹ�������˺�����ȴ��������ơ�");
        tell_object(me, HIC "��ѧ���ˡ�Բ���ơ���\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/riyue-lun/yuan", 1, me);
        addn("family/gongji", -800, me);

        return 1;
}

mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/riyue-lun/lian", me) )
                return "��������ʲô���Լ���ȥ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("riyue-lun", 1) < 1)
                return "���������ַ���ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<2000 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-80000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if (me->query_skill("force") < 250)
                return "����ڹ���Ϊ���㣬����ѧ������һ�С�";

        if( query("max_neili", me)<3000 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("riyue-lun", 1) < 150)
                return "����������ַ��������������ҡ�";

        message_sort(HIY "\n$n" HIY "������$N" HIY "���죬����Ϊ����ĵ�"
                     "�˵�ͷ��˵�����������д�ʵ��Ҳ�����ף�����Ϊʦ��"
                     "�������У�����ϸ�ˣ���˵��$n" HIY "��ȡ�����½���"
                     "����Ŀ��ȣ����ֶ�Ȼһ����ؽ����½��ַ�������"
                     "������������â���໥������ѹ��$N" HIY "����������"
                     "����֮����\n\n" NOR, me, this_object());

        command("haha");
        command("say ��������������ҵ����½���ʩչ�����ܼ�����Ч��");
        tell_object(me, HIC "��ѧ���ˡ�������ת����\n" NOR);

        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("hammer"))
                me->improve_skill("hammer", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        if (me->can_improve_skill("riyue-lun"))
                me->improve_skill("riyue-lun", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/riyue-lun/lian", 1, me);
        addn("family/gongji", -2000, me);

        return 1;
}

mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/longxiang-gong/tun", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("longxiang-gong", 1) < 1)
                return "���������������ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<1800 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-80000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if( query("max_neili", me)<3000 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("longxiang-gong", 1) < 180)
                return "��������������Ϊ���㣬���������ɡ�";

        message_sort(HIY "\n$n" HIY "��˼Ƭ�̣����ŵ��˵�ͷ�����ֽ�$N" HIY
                     "������ߣ�������$P" HIY "���Ե���ϸ˵���ã�$N" HIY
                     "���󲻽����ĵ�һЦ���ƺ���$n" HIY "�Ľ̵���������"
                     "��\n\n" NOR, me, this_object());

        command("nod");
        command("say �ղ���˵��ȫ�����еľ��裬�Լ���ȥ����ɡ�");
        tell_object(me, HIC "��ѧ���ˡ������ơ���\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/longxiang-gong/tun", 1, me);
        addn("family/gongji", -1800, me);

        return 1;
}

mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/longxiang-gong/die", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("longxiang-gong", 1) < 1)
                return "���������������ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<2200 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-120000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if( query("max_neili", me)<4000 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("longxiang-gong", 1) < 240)
                return "��������������Ϊ���㣬���������ɡ�";

        message_sort(HIY "\n$n" HIY "����$N" HIY "һ�ۣ�����Ҳ���𻰣���"
                     "Ȼ������֣���$N" HIY "�ؿ�̽ȥ��$N" HIY "��æ��"
                     "�ܣ�ȴ��֪�⿴�Ʋ������һ�ƣ���Ȼ�������������"
                     "���ڰ˳ɵĹ�����$N" HIY "������Ͼ��ܣ���ʱ������"
                     "���ƣ����ص�ˤ�˳�ȥ��\n\n" NOR, me, this_object());

        command("say ����ô��");
        tell_object(me, HIC "��ѧ���ˡ�����ơ���\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/longxiang-gong/die", 1, me);
        addn("family/gongji", -2200, me);

        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();

        if( query("can_perform/longxiang-gong/ji", me) )
                return "�Ҳ����Ѿ��̹�����ô��������ʲô��";

        if( query("family/family_name", me) != query("family/family_name") )
                return "������ƶɮ����ԨԴ����֪�˻��Ӻ�̸��";

        if (me->query_skill("longxiang-gong", 1) < 1)
                return "���������������ûѧ����̸ʲô���У�";

        if( query("family/gongji", me)<2500 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-160000 )
                return "��Ϊ��̫��������һ���㲻ѧҲ�ա�";

        if( query("max_neili", me)<5000 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("longxiang-gong", 1) < 300)
                return "��������������Ϊ���㣬���������ɡ�";

        message_sort(HIY "\n$n" HIY "΢΢���˵�ͷ��ֻ�����ִ���$N" HIY
                     "�ļ��ϣ�ͻȻ$N" HIY "����ȫ�����������Ϣ����"
                     "��ӿ֮�������罭�Ӿ��̣���������Ƴ�һ�㣬���ɴ�"
                     "����\n\n" NOR, me, this_object());

        command("haha");
        command("say �ղ�����һ�У��㿴�����˶��٣�");
        tell_object(me, HIC "��ѧ���ˡ�����������\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        if (me->can_improve_skill("longxiang-gong"))
                me->improve_skill("longxiang-gong", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/longxiang-gong/ji", 1, me);
        addn("family/gongji", -2500, me);

        return 1;
}

mixed ask_midao()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "ѩɽ��" )
                return "������ô��";

        command("whisper"+query("id", me)+"���ȻͶ����ѩɽ�£���"
                "����\nҪȥ��ԭ���£���������ѩɽ���ȱ������µ��ܵ���ֱ"
                "��ȥ��\n��ת��(" HIY "turn lunpan" NOR + WHT ") ���̴�"
                "�����أ������Ὺ���ܵ���Ȼ\n����˳���ܵ�ǰ�����ܵ���"
                "��ԭ���ݡ���Ҫ���¿�����ѩɽ��\n������ԭ����骣��ӿڵ�"
                "������" HIY "���־�ת" NOR + WHT "���ɼ�����ˡ�\n");
        return "�����ܲ���й¶�����ˣ��������Ĳ����㣡";
}

mixed ask_lun()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if( query("family/family_name", me) == "ѩɽ��" )
                        message_vision(CYN "$N" CYN "��ŭ����$n" CYN "����������"
                                       "Ϊ��ѩɽ�µ��ӣ�����ѧ����ʼ������ˣ���"
                                       "�ҹ��ɣ���\n" NOR, this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��ŭ����$n" CYN "�ȵ�������"
                                       "��ʲô�ˣ���Ȼ��̰ͼ�ҵ�������������ò�"
                                       "�ͷ��ˣ���\n" NOR, this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "ѩɽ��" )
                return "���½������ҵ�������������������ʲô��";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ���ʹ�ý��֣��㻹���Լ���ȥ�����ɡ�";

        if( query("shen", me)>-50000 )
                return "�ߣ����Ȼ������壬���Ǳ��ý��ֵĺá�";

        ob = find_object(JINLUN);
        if (! ob) ob = load_object(JINLUN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "��ô�����½��ֲ�����������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ�������½������ڲ��������С�";

                if( query("family/family_name", owner) == "ѩɽ��" )
                        return "����������ʱ����ͬ��ʦ��"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "�ҵ����½�����������"+query("name", owner)+
                               "���У���ȥ�������ˣ��ѽ�����������";
        }

        ob->move(this_object());
        message_vision(CYN "$N" CYN "΢΢Ц����������ƽʱ�̿�Ŭ���������"
                       "���������ȥ�ðɡ�\n" NOR, this_object(), me);
        command("giveriyuejinlunto"+query("id", me));
        return 1;
}

/*
void unconcious()
{
        die();
}
*/
