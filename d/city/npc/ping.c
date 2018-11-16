#include <ansi.h>
#include <medical.h>

inherit NPC;
inherit F_DEALER;

string ask_job();
int do_peiyao(string arg);
int working(object me);
int halt_working(object me);
int ask_me();
int ask_riyue();
int do_join(string arg);
int do_unjoin(string arg);
int do_identify();
int do_decide();

void create()
{
        set_name("ƽһָ", ({ "ping yizhi", "ping", "yizhi" }));
        //set("title", "ҩ���ϰ�");
        set("title", HIW"��ҩʦЭ��"HIR"�᳤"NOR);
        set("nickname", HIB "ɱ����ҽ" NOR);
        set("gender", "����");
        set("long", "������ҽ���߳��ġ�ɱ����ҽ��ƽһָ���������Ը��\n"
                    "�֣�����ʲô�˶�ҽ�ġ�\n");
        set("age", 65);

        set("int", 38);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("shen_type", 1);

        set("combat_exp", 500000);
        set("attitude", "heroism");

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 60);
        set_skill("liandan-shu", 2200);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/damage", 50);
        set("inquiry", ([
                "��ҩ"   : (: ask_job :),
                "����"   : (: ask_job :),
                "job"    : (: ask_job :),
                "����"   : (: ask_me  :),
                "�������" : (: ask_riyue :),
                "���"     : "����������Լ���(" HIY "join" NOR +
                             CYN ")��ҩʦЭ�ᡣ\n" NOR,
                "����"     : "����������Լ���(" HIY "join" NOR +
                             CYN ")��ҩʦЭ�ᡣ\n" NOR,
                "����"     : "����������Լ���(" HIY "jianding" NOR +
                             CYN ")��ҩʦƷ����\n" NOR,
                "��ҩʦЭ��" : "����������Լ���(" HIY "join" NOR +
                             CYN ")��ҩʦЭ�ᡣ\n" NOR,
        ]));

        set("vendor_goods", ({
                HERB("chaihu"),         // ���
                HERB("chenpi"),         // ��Ƥ
                HERB("chongcao"),       // ���
                HERB("chuanwu"),        // ����
                HERB("dahuang"),        // ���
                HERB("dangui"),         // ����
                HERB("duhuo"),          // ����
                HERB("fangfeng"),       // ����
                HERB("fuzi"),           // ����
                HERB("gsliu"),          // ��ʯ��
                HERB("guiwei"),         // ��β
                HERB("hafen"),          // ���
                HERB("heshouwu"),       // ������
                HERB("honghua"),        // �컨
                HERB("huangqi"),        // ����
                HERB("lurong"),         // ¹��
                HERB("xiongdan"),       // �ܵ�
                HERB("juhua"),          // �ջ�
                HERB("lanhua"),         // ����
                HERB("lingxian"),       // ����
                HERB("lingzhi"),        // ��֥
                HERB("mahuang"),        // ���
                HERB("moyao"),          // ûҩ
                HERB("niuhuang"),       // ţ��
                HERB("niuxi"),          // ţϥ
                HERB("qianjinzi"),      // ǧ����
                HERB("renshen"),        // �˲�
                HERB("ruxiang"),        // ����
                HERB("shadan"),         // �赨
                HERB("shancha"),        // ɽ�軨
                HERB("shanjia"),        // ɽ��
                HERB("shengdi"),        // ����
                HERB("shenglg"),        // ������
                HERB("sumu"),           // ��ľ
                HERB("taoxian"),        // ����
                HERB("tenghuang"),      // �ٻ�
                HERB("tianqi"),         // ����
                HERB("tugou"),          // ����
                HERB("wulingzhi"),      // ����֬
                HERB("xiefen"),         // Ы��
                HERB("xijiao"),         // Ϭ��
                HERB("xionghuang"),     // �ۻ�
                HERB("xuejie"),         // Ѫ��
                HERB("xuelian"),        // ѩ��
                HERB("yanwo"),          // ����
                HERB("yjhua"),          // ���
                HERB("yuanzhi"),        // Զ־
                HERB("zihua"),          // �ϻ�
                HERB("zzfen"),          // �����
                HERB("hugu"),           // ����
                "/clone/misc/yanbo",    // �в�
                "/clone/drug/tianqi-san",
                "/d/city/obj/shanshen",
                "/clone/medicine/jinmisan",
                "/clone/book/medical_book",
        }));

        setup();
        add_money("silver", 50);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_peiyao", "peiyao");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_join", "join");
        add_action("do_decide", "decide");
        add_action("do_identify", "jianding");
        add_action("do_unjoin", "unjoin");
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/peiyao", me) )
                return "����ɵĻ��������ô��";

        if( query("combat_exp", me)>30000 )
                return "�������Ҳ̫�������˰ɡ�";

        if( query("combat_exp", me)<3000 )
                return "����㾭�飬��һ���嶼û�У��ҿ�����ҩ�ʶ��˲�������";

        if( query("qi", me)<5 )
                return "�㻹����ЪЪ�ɣ���һ�۳��������ҿɸ�������";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/peiyao", $1) &&
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "�����Ѿ���" + obs[0]->name() + "�ڸɻ��ˣ���ȵȰɡ�";

        set_temp("job/peiyao", 1, me);
        return "�ã���Ͱ�����ҩ(peiyao)�ɣ��������⼸ζ��";
}

int do_peiyao(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("����æ���أ����ż���\n");

        if( !query_temp("job/peiyao", me) )
        {
                message_vision("$N����ץ��ζҩ���ƣ�������$nŭ�ȵ���"
                               "���ҷ��£����Ҷ���\n",
                               me, this_object());
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "�㿪ʼ������\n");
        return 1;
}

int working(object me)
{
        object ob;
        string msg;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/peiyao", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("qi", 1);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N��������ѡ����һЩҩ�ġ�";
                break;
        case 2:
                msg = "$N��ҩ�ķŽ�ҩ�ʣ�ʹ������������";
                break;
        case 3:
                msg = "ҩ�Ľ���������м������һ��";
                break;
        case 4:
                msg = "��м��$N�ĵ�Ū��Խ��Խϸ���𽥱���˷�ĩ��";
                break;
        default:
                msg = "$N��ҩ�İ��ã��ݸ�$n��";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                msg += "$n����$N���ҩ����ͷ������������"
                       "���Ǹ���ı��꣡\n";
                delete_temp("job/peiyao", me);
                delete_temp("job/step", me);

                b = 500 + random(80);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));

                ob = new("/clone/money/coin");
                ob->set_amount(10);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "��");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if (! query("zhufu_mod/wrists", me) && random(10) == 1)
                {
                        msg = "$n��$N�ٺ�һЦ�������ɵò������е�"
                              "��˼�������֮ף��������������͸��������ɡ�\n";
                        message_vision(msg, me, this_object());
                        ob = new("/clone/goods/zhufu_wrists");
                        ob->move(me, 1);
                        tell_object(me, HIM "\n������һ��" + ob->name() +
                                        HIM "��\n" NOR);
                        set("zhufu_mod/wrists", 1, me);
                }
                else
                if (random(1000) == 1)
                {
                        msg = "$n��$N�ٺ�һЦ�������ɵò������е�"
                              "��˼���������ĥ���������͸��������ɡ�\n";
                        message_vision(msg, me, this_object());
                        ob = new("/clone/misc/dymo");
                        ob->move(me, 1);
                        tell_object(me, HIM "\n������һ��" + ob->name() +
                                        HIM "��\n" NOR);
                }

                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N�����еĻ�һ˦�����µ��������ˣ������ˣ�\n",
                       me);
        delete_temp("job/peiyao", me);
        delete_temp("job/step", me);
        return 1;
}

int accept_object(object who, object ob)
{
        object obj ;
        if( !query_temp("������", who) )
        {
        message_vision("ƽһָ��$N˵��ҽһ�ˣ�ɱһ�ˣ��Ϸ���Ǯ��\n", who);
                return 0 ;
        }
        if( query("money_id", ob) && ob->value() >= 50000 )
        {
                destruct(ob);
                message_vision("ƽһָ������$N��Ǯ������$Nһ������ڣ�\n" , who);
                delete_temp("������", this_player());
                obj=new(__DIR__"obj/shouwu");
                obj->move(this_player());
        }
        return 1;
}

int ask_me()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "�������" )
        {
                command("say �Ϸ�ҽһ��ɱһ�ˣ������������ɡ�\n");
                return 1;
        }
        if( query("eff_qi", ob) == query("max_qi", ob) )
        {
                command("say ����û�����ˣ�����ǲ�Ϸ���\n");
                return 1;
        }
        else
        {
                message_vision("ƽһָ��ָ΢������ָһ����һ��ҩ�輲����$N���ʺ�$N"
                                "���ɡ����ࡱһ�����븹�У��ٸ�������ˬ����������\n", ob);
                set("eff_qi",query("max_qi",  ob), ob);
                set("eff_jing",query("max_jing",  ob), ob);
                command("say �ߣ�����������书�������֣���ú�ȥѧѧ�����ٶ��������ˣ�����ɡ�\n");
                return 1;
        }
}

int ask_riyue()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "�������" )
                return notify_fail("������������ձ�һͳ������\n");

        message("vision", "ƽһָ����һ�ţ��ѽ�" + ob->name() + "�ߵ���Ӱ���١�\n", environment(ob), ob);
        ob->move("/d/heimuya/midao7");
        tell_object(ob, "ƽһָ����һ�ţ������߽����ص���\n");
        return 1;
}

int do_join(string arg)
{
        object me = this_player();

        if (! arg || arg != "��ҩʦЭ��")
                return notify_fail(CYN "ƽһָһ�㣬˵������Ҫ����ʲô����"
                                   "��������ҩʦЭ�ᡣ\n" NOR);

        if( me->query_skillo("liandan-shu", 1) < 300 )
                return notify_fail(CYN "ƽһָ������ü��˵�����������ҩʦ"
                                   "Э�ᣬ����߱�һƷ��ҩʦ�ʸ��������"
                                   "��������ѧ����������(liandan-shu)��\n" NOR);

        if( query("is_alchemy", me) )
                return notify_fail(CYN "ƽһָ������ü��˵�����㲻���Ѿ���"
                                   "����ҩʦЭ����ô��\n" NOR);

        if( query("bad_alchemy", me) )
                return notify_fail(CYN "ƽһָ��Цһ����˵������Ȼ���Ѿ���"
                                   "������ҩʦЭ�ᣬ�ֻ���������\n" NOR);

        tell_object(me, CYN "\nƽһָ���˵�ͷ��˵��������Ĵ���(" HIY "dec"
                        "ide" NOR + CYN ")������ҩʦЭ��ô���ɿ�������ˣ�"
                        "\n" NOR);
        set_temp("want_join", 1, me);
        return 1;
}

int do_unjoin(string arg)
{
        object me = this_player();

        if (! arg || arg != "��ҩʦЭ��")
                return notify_fail(CYN "ƽһָ������ü��˵�������������ʲ"
                                   "ô��˵�����岻���ġ�\n" NOR);

        if( !query("is_alchemy", me) )
                return notify_fail(CYN "ƽһָ��Цһ����û���㡣\n" NOR);

        tell_object(me, CYN "\nƽһָ̾�˿�����˵�������������ҩʦЭ�ᣬ�Ժ�"
                        "�ɲ��ܷ��ڡ��������(" HIY "decide" NOR + CYN ")"
                        "��ô��ô��\n" NOR);
        set_temp("want_tuoli", 1, me);
        return 1;
}

int do_decide()
{
        object ob, me;
        int level;
        string *pro;
        me = this_player();

        if( query_temp("want_join", me) )
        {
                message_vision(HIC "$N" HIC "����$n" HIC "΢Ц������ҩʦ"
                               "��������ҫ��ְҵ���Ժ�úøɰɡ�\n" NOR,
                               this_object(), me);

                level = me->query_skillo("liandan-shu", 1);
                set("is_alchemy", level/300, me);
                delete_temp("want_join", me);

                ob = new("/clone/misc/yaoshi-zheng");
                set("level", level/300, ob);
                ob->enable();
                ob->move(this_object());
                command("give yaoshi zheng to "+query("id", me));

                set("bindable", 3, ob);
                set("bind_owner",query("id", me), ob);
                set("owner",query("id", me), ob);
                set("no_store", 1, ob);
                set("auto_load", 1, ob);
                set("set_data", 1, ob);

                pro = query("profession", me);
                if( !pro ) pro = ({});
                pro += ({ "alchemy" });
                set("profession", pro, me);
                return 1;
        } else
        if( query_temp("want_tuoli", me) )
        {
                message_vision(HIC "$N" CYN "����$n" HIC "���ͷ���˸���"
                               "־���Ӵ��Ժ��������޹ϸ�\n" NOR,
                               this_object(), me);

                delete("is_alchemy", me);
                set("bad_alchemy", 1, me);
                delete_temp("want_tuoli", me);

                pro = query("profession", me);
                pro -= ({ "alchemy" });
                set("profession", pro, me);

                if (objectp(ob = present("yaoshi zheng", me)));
                {
                        message_vision(HIR "$N" HIR "��$n" HIR "��" NOR +
                                       ob->name(1) + HIR "ע���ˡ�\n" NOR,
                                       this_object(), me);
                        destruct(ob);
                }
                return 1;
         }

         return notify_fail(CYN "ƽһָ������һ�ۣ�������ü��û���㡣\n" NOR);
}

int do_identify()
{
        int level;
        object ob, me = this_player();

        if( query("bad_alchemy", me) )
                return notify_fail(CYN "ƽһָ���ͷ������߿����߿������ֻ�"
                                   "��������\n" NOR);

        if( !query("is_alchemy", me) )
                return notify_fail(CYN "ƽһָ������һ�ۣ�û���㡣\n" NOR);

        if( objectp(ob = present("yaoshi zheng", me)) )
                destruct(ob);

        level = me->query_skillo("liandan-shu", 1);
        set("is_alchemy", level/300, me);

        ob = new("/clone/misc/yaoshi-zheng");
        set("level", level/300, ob);
        ob->enable();
        ob->move(this_object());
        command("give yaoshi zheng to "+query("id", me));

        set("bindable", 3, ob);
        set("bind_owner",query("id", me), ob);
        set("owner",query("id", me), ob);
        set("no_store", 1, ob);
        set("auto_load", 1, ob);
        set("set_data", 1, ob);

        return 1;
}

int recognize_apprentice(object ob, string skill)
{
        if (skill != "liandan-shu")
                return 0;

        if (ob->query_skillo("liandan-shu", 1) >= 300)
        {
                write(CYN "ƽһָ���˵�ͷ��˵�����������յ���"
                      "����Ҫ���ϴ�ʵ�����������ģ��������յ�\n"
                      "�������Ҿͽ̵����ʣ�¿�����츳�������ˡ�\n" NOR);
                return -1;
        }
        return 1;
}
