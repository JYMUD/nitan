#include <ansi.h>
inherit NPC;

int do_liandan();
string ask_me();
string ask_yinzhen();

void create()
{
        set_name("Ҧ��", ({"yao chun", "yao", "chun"}));
        set("gender", "����");
        set("age", 56);
        set("title", HIG "�ش���" NOR);
        set("nickname",HIR "������ҽ" NOR);
        set("long",
                "����Ǿ��ǻش���ҩ�̵ĵ�����ҽҦ������ĸ�\n"
                "�ݣ���ò���������ػ����촨�����ˣ�����\n"
                "��ҽ�Σ����˼�����ҽ�����ö̴�Ҳ��һ����\n");
        set("attitude", "heroism");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 20000);
        set("max_neili", 20000);

        set("combat_exp", 10000000);
        set("score", 300000);

        set_skill("medical", 150);
        set_skill("zhenjiu-shu", 150);
        set_skill("liandan-shu", 150);
        set_skill("literate", 150);

        map_skill("medical", "bencao-shuli");

        set("inquiry", ([
                "���촨"  :  "���Ϻ�������Ҹ�ҽ�εģ���ô��Ҳ֪����\n",
                "����"    : (:do_liandan:),
                "liandan" : (:do_liandan:),
                "quest"   :  "����������԰����ҡ�" HIR "����" NOR + CYN
                             "�������Ը���������ѯ�ʡ�\n",
                "job"     :  "����������԰����ҡ�" HIR "����" NOR + CYN
                             "�������Ը���������ѯ�ʡ�\n",
                "ҩ��"    :  "ȥ���ҵ�Сͯ��������㴦��\n",
                "ԭ��"    :  "ȥ���ҵ�Сͯ��������㴦��\n",
                "yaocai"  :  "ȥ���ҵ�Сͯ��������㴦��\n",
                "ҩ"      :  "ȥ���ҵ�Сͯ��������㴦��\n",
                "ҽ��"    : (: ask_me :),
                "ѧҽ��"  : (: ask_me :),
                "ѧϰҽ��": (: ask_me :),
                "������"  : (: ask_me :),
                "�����"  : (: ask_me :),
                "��������": (: ask_me :),
                "����ҽ��": (: ask_me :),
                "ѧϰ"    : (: ask_me :),
                "ѧ��"    : (: ask_me :),
                "����"    : (: ask_yinzhen :),
                "��"      : (: ask_yinzhen :),
                "���"    : (: ask_yinzhen :),
        ]) );

        setup();

}

void init()
{
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
}

int do_liandan()
{
        int exp, pot;
        object ob;
        object me = this_player();

        if( query_temp("liandan", me) )
        {
                if( query_temp("liandan", me)<4 )
                {
                        command("say ����Ҫȥ��������ô��������ţ�\n");
                        return 1;
                }
                message_vision(CYN "Ҧ����$N" CYN "΢Ц���������Ǹ��������Ե�"
                               "���̣����ܳɹ����ܲ���\n" NOR, me);

                exp = 100 + random(140);
                pot = exp / 3;

                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));

                delete_temp("liandan", me);
                addn("over_quest/liandan_quest", 1, me);
                if (! query("zhufu_mod/waist", me) && random(10) == 1) 
                {
                        message_vision("$n��$N�ٺ�һЦ�������ɵò������е�" 
                                       "��˼�������֮ף���������������͸��������ɡ�\n",
                                       me, this_object());
                        ob = new("/clone/goods/zhufu_waist"); 
                        ob->move(me, 1); 
                        tell_object(me, HIM "\n������һ��" + ob->name() + HIM "��\n" NOR);
                        set("zhufu_mod/waist", 1, me); 
                }
                return 1;
        } else
        {
                message_vision(CYN "Ҧ����$N" CYN "���˵�ͷ��˵���������ǿ���"
                               "�˵Ķ�����Ϊ���Ĳ������²��ɣ���ȥ��ͯ��ѯ�ʡ�"
                               HIG "ҩ��" NOR + CYN "���ɡ�\n", me);
                set_temp("liandan", 1, me);
                return 1;
        }
}

string ask_me() 
{
        object me;

        me = this_player();

        if( query("can_learn_medical/yaochun", me) == 1 )
                return "�Ҳ��Ǵ�Ӧ����������������ô��ô���£�";

        if( query("shen", me)<-10000 )
                return "������ħͷ����ȥɱ�˶��������ִ����ˡ�";

        if( query("over_quest/liandan_quest", me)<100 )
                return "�����ɣ����Ȱ��������ٴΣ��ĳ�֮ʱ����Ȼ�ᴫ�ڸ��㡣";

        if( query("shen", me)<0 )
                return "�������������ò������������֮������Ȼ�ᴫ�ڸ��㡣";

        set("can_learn_medical/yaochun", 1, me);
               return "��Ȼ������������ѧҽ֮�����Ҿͳ�ȫ��ȫ��ɡ�"; 
}

int recognize_apprentice(object me, string skill)
{
        if( query("shen", me)<-10000 )
        {
                command("say ���ҹ������Ҳ��ᴫ���κμ��ܸ�������ħͷ��");
                return -1;
        }

        if( !query("can_learn_medical/yaochun", me) )
        {
                command("say �ҵ�ҽ�������ǲ����״��ڵġ�");
                return -1;
        }

        if (skill == "literate")
        {
                command("say ����д���Լ�ȥ�ҽ�������ѧȥ��");
                return -1;
        }

        if (skill != "medical" &&
            skill != "zhenjiu-shu")
        {
                command("say ��ֻ�ܴ��ڻ���ҽ�����������");
                return -1;
        }

        return 1;
}

string ask_yinzhen()
{
        mapping fam; 
        object ob;
        object me = this_player();

        if( query("shen", me)<-0 )
                return "���߰ɣ��ҵ�����ɲ�������������ˡ�";

        if ((int)me->query_skill("zhenjiu-shu", 1) < 60)
                return "�������������죬��������Ū���������ġ�";

        if (present("yin zhen", this_player()))
                return "�����ϲ��ǻ���һ����";

        ob = new("/d/beijing/obj/yinzhen");
        ob->move(me);

        message_vision(HIW "\nҦ����������������һ�����룬�ݸ���$N" HIW "��\n" NOR, me);
                return "����������������ģ��úõ�������Ϊ���β��ɡ�";
}
