// qingyangzi.c  �����
// Written by Vin  2002/4/28

#include <ansi.h>
inherit NPC;

int ask_me();
int tattoo(object me);

mapping body_type = ([ "����" : ({ "face" }),
                       "�ؿ�" : ({ "chest" }),
                       "��" : ({ "back" }),
                       "�β�" : ({ "buttock" }),
                       "���" : ({ "leftarm" }),
                       "�ұ�" : ({ "rightarm" }), ]);

void create()
{
        set_name("�����", ({ "qingyang zi", "qingyang", "zi" }));
        set("long", "���������µ�һ����ʦ����ӡ�\n" );

        set("nickname", HIB "����ʦ" NOR);
        set("gender", "����");
        set("attitude", "friendly");
        set("age", 325);
        set("shen_type", 0);
        set("str", 500);

        /*
        set("inquiry", ([
                "����" : (: ask_me :),
                "����" : (: ask_me :),
        ]));
        */

        setup();

        if (! clonep(this_object()))
        {
                move("/d/luoyang/suanming");
                message_vision(CYN "\n$N" CYN "���˹������������ܣ���"
                               "��һ����̾��\n" NOR, this_object());
                set("startroom", "/d/luoyang/suanming");
        }

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/tattoo/npc_item2")->wield();
        set_temp("handing", carry_object("/clone/tattoo/npc_item1"));
}

void init()
{
        /*
        add_action("do_show", "show");
        add_action("do_answer", "answer");
        // ��������н�ֹ�鿴����״̬��ΪʲôҪ�����أ���Ϊ
        // ʵ�������Ѿ��ڽ�������������Ĵ������ǰ�������ˡ�
        add_action("do_check", "hp");
        add_action("do_check", "score");
        add_action("do_check", "special");
        */
}

int do_check()
{
        object me = this_player();

        if( query_temp("item/status", me) == "waiting" )
        {
                message_vision(CYN "$N" CYN "��$n" CYN "�ȵ�������"
                               "������û���꣬��Ｑʲô��\n" NOR,
                               this_object(), me);
                return 1;
        }
}

int do_show(string arg)
{
        string status, msg, mat;
        object me, ob;
        int value, n;

        me = this_player();
        if (! arg)
                return notify_fail("����Ҫ����ʲô������\n");

        mat = arg;

        if (! objectp(ob = present(mat, me)))
                return notify_fail("�������ƺ�û�����ֶ�����\n");

        status = query_temp("item/status");

        if (status == "look_working")
        {
                message_vision(CYN "$N" CYN "ͷҲ��̧����$n" CYN "˵����"
                               "������æ������µȻ���˵��\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( !query("can_tattoo", ob) )
        {
                message_vision(CYN "$N" CYN "üͷһ�壬��$n" CYN "˵����"
                               "��ֻ��ͼ�ڸ���Ȥ��û�±������ҡ�\n" NOR,
                               this_object(), me);
                return 1;
        }

        if( query("value", ob) >= 12000 )
                msg = sprintf(CYN "$N" CYN "�ӹ�$n" CYN "�ó���ͼ������������"
                              "֮������һ����̾��\n" NOR);
        else
        if( query("value", ob) >= 5000 )
                msg = sprintf(CYN "$N" CYN "�ӹ�$n" CYN "�ó���ͼ��������һ��"
                              "������¶���������ɫ��\n" NOR);
        else
        if( query("value", ob) >= 2000 )
                msg = sprintf(CYN "$N" CYN "�ӹ�$n" CYN "�ó���ͼ����������ü"
                              "���ƺ���˵Щʲô��\n" NOR);
        else
                msg = sprintf(CYN "$N" CYN "����$n" CYN "������ͼ������Цһ��"
                              "������¶����м����ɫ��\n" NOR);

        value=query("value", ob)/50+20;
        msg += sprintf(CYN "$N" CYN "���˵�ͷ���������Ĵ�����Ҫ�ƽ�%s��������"
                       "�����ðɡ�\n" NOR, chinese_number(value));
        message_vision(msg, this_object(), me);

        return 1;
}

// ������ʾ��Ϣ
int ask_me()
{
        message_sort(CYN "$N" CYN "̧ͷ���˿�$n" CYN "����ͷ�����Ȱ��������"
                     "�̵�ͼ���ø��ҿ�(" HIY "show" NOR + CYN ")�������ҹ���"
                     "һ�¼�Ǯ��������ú��ʾͽ�Ǯ��\n" NOR, this_object(),
                     this_player());
        return 1;
}

// ���ܶ���
int accept_object(object me, object ob)
{
        string status;
        int val;

        status = query_temp("item/status");
        if (status == "look_working")
        {
                message_vision(CYN "$N" CYN "ͷҲ��̧����$n" CYN "˵����"
                               "������æ������µȻ���˵��\n" NOR,
                               this_object(), me);
                return 0;
        }

        if (status == "waiting")
        {
                if( query_temp("item/player_id") == query("id", me) )
                {
                        command("say ������ɺã����Ҷ���");
                        return 0;
                }

                message_vision(CYN "$N" CYN "ͷҲ��̧����$n" CYN "˵����"
                               "������æ������µȻ���˵��\n" NOR,
                               this_object(), me);
                return 0;
        }

        if (status == "accept")
        {
                if( query_temp("item/player_id") != query("id", me) )
                {
                        command("say û������æô��������ʲô�ң�");
                        return 0;
                }

                if( !query("money_id", ob) )
                {
                        command("say �����㽻Ǯ�������������");
                        return 0;
                }
        }

        if( query("can_tattoo", ob) && query("tattoo_type", ob) )
        {
                mixed p;
                string *types;

                types = keys(body_type);

                p=query("tattoo/tattoo", me);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                if (! sizeof(types))
                {
                               message_vision(CYN "$N" CYN "��$n" CYN "��Ц������ȫ"
                                              "���Ѿ��Ƶø���һ���ˣ����Ӳ���ô��\n"
                                              NOR, this_object(), me);
                        return 0;
                }

                if( (p=query("can_tattoo", ob)) == "all" )
                {
                        types = keys(body_type);
                } else
                if (arrayp(p))
                        types = p;
                else
                if (stringp(p))
                        types = ({ p });

                // ȷ�ϸ�ID�Ƿ��еط��Ѿ�������
                p=query("tattoo/tattoo", me);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                if (! sizeof(types))
                {
                        message_vision(CYN "$N" CYN "ҡ��ҡͷ�������ͼ"
                                       "�ڲ����ʺ��Ƶ���ʣ�µĲ�λ�ϡ�\n"
                                       NOR, this_object(), me);
                        return 0;
                }

                // ������������ѵļ�ֵ
                val=query("value", ob)/50+20;
                message_vision(CYN "$N" CYN "���˵�ͷ���������Ĵ�����Ҫ�ƽ�" +
                               chinese_number(val) + "���������ھ͸�Ǯ�ɡ�\n"
                               NOR, this_object(), me);
                val *= 10000;
                set("item/value", val, ob);
                set_temp("item/status", "item_gived", me);
                set_temp("item/value", val, me);
                set_temp("item/status", "accept");
                set_temp("item/player_id",query("id", me));
                set_temp("item/accept", ob);

                remove_call_out("time_out");
                call_out("time_out", 30, me, ob);
                return 1;
        }

        if( query("money_id", ob) )
        {
                object origin;
                mixed p;
                string *types;

                if( query_temp("item/status", me) == "answer_type" )
                {
                        message_vision(CYN "$N" CYN "ҡҡͷ����$n" CYN "������"
                                       "�Ÿ�Ǯ����˵˵��Ҫ��ʲô��\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                if( query_temp("item/status", me) != "item_gived" )
                {
                        message_vision(CYN "$N" CYN "��$n" CYN "�ݹ�ȥ��" + ob->name() +
                                       CYN "���˻�����ҡͷ�����޹�����»��\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                if( ob->value()<query_temp("item/value", me) )
                {
                        message_vision(CYN "$N" CYN "��Ц����������˭��֪������"
                                       "���˵һ�������ѵ���Ϊ��������\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                origin = query_temp("item/accept");
                if( (p=query("can_tattoo", origin)) == "all" )
                {
                        types = keys(body_type);
                } else
                if (arrayp(p))
                        types = p;
                else
                if (stringp(p))
                        types = ({ p });

                // ȷ�ϸ�ID�Ƿ��еط��Ѿ�������
                p=query("tattoo/tattoo", me);
                if (arrayp(p))
                        types -= p;
                else
                if (stringp(p))
                        types -= ({ p });

                if (! sizeof(types))
                {
                        message_vision(CYN "$N" CYN "ҡ��ҡͷ���������"
                                       "�಻�ʺ��Ƶ���ʣ�µĲ�λ��\n" NOR,
                                       this_object(), me);
                        return 0;
                }

                set_temp("item/types", types);
                set_temp("item/money", ob);

                ob->move(this_object());

                message_vision(CYN "$N" CYN "��$n" CYN "˵�����������ʲ"
                               "ô�ط����ࣿ�����(" HIY "answer" NOR +
                               CYN ")�Ҿ��岿λ��\n" NOR, this_object(), me);
                tell_object(me, HIC "�㻹������" HIY + implode(types, "��" )
                                + HIC "�ϴ��ࡣ\n" NOR);

                set_temp("item/status", "answer_type", me);
                return -1;
        }

        message_vision(CYN "����Ӷ�$N" CYN "��ü���������е����⣬������"
                       "ʦ�����㿴����\n" NOR, me);
        return 0;
}

int do_answer(string arg)
{
        string *tattooed, *types;
        string tlong, special;
        object ob, me;
        object money;

        me = this_player();
        if( query_temp("item/status", me) != "answer_type" )
                return 0;

        if (! arg)
                return notify_fail("��Ҫ�ش�ʲô��\n");

        message_vision(CYN "$n" CYN "����ͷ����һ�ᣬ��$N" CYN "������"
                       "���ͼ���Ѵ��������ҵ�" + arg + "�ϰɣ�\n" NOR,
                       this_object(), me);

        if (member_array(arg, query_temp("item/types")) == -1 ||
            undefinedp(body_type[arg]))
        {
                message_vision(CYN "$N" CYN "���˿�$n" CYN "�����ĵ���"
                               "Ц��һ����\n" NOR, this_object(), me);
                return 1;
        }

        if (objectp(money = query_temp("item/money")))
                destruct(money);

        set_temp("item/status", "look_working");
        set_temp("item/status", "waiting", me);

        ob = query_temp("item/accept");

        message_sort(HIC "\n$N" CYN "���˵�ͷ����$n" CYN "˵��������"
                     "��Ϳ�ʼ�ɣ����ɵ��ǱߵĴ���ȥ�����Ҷ���$N"
                     HIC "˵���ת����ȥ�����ֽ�" + ob->name() + HIC
                     "��������ˮ�裬��" + ob->name() + HIC "��ȫʪ"
                     "͸����С������ش�ˮ��ȡ������������$n" HIC
                     "��" + arg + "֮�ϡ�\n\n" NOR, this_object(), me);

        // Ϊ�Ѿ�������Ĳ�λ�Ǻ�
        tattooed=query("tattoo/tattoo", me);

        if (! arrayp(tattooed))
                tattooed = ({ });

        tattooed -= ({ arg });
        tattooed += ({ arg });
        set("tattoo/tattoo", tattooed, me);

        // ���Ӳ�ͬ��λ�Ĵ�������
        tlong=query("tattoo_long", ob);

        switch (arg)
        {
        case "����":
                set("tattoo/face_long", tlong, me);
                break;
        case "�ؿ�":
                set("tattoo/chest_long", tlong, me);
                break;
        case "��":
                set("tattoo/back_long", tlong, me);
                break;
        case "���":
                set("tattoo/leftarm_long", tlong, me);
                break;
        case "�ұ�":
                set("tattoo/rightarm_long", tlong, me);
                break;
        default:
                set("tattoo/buttock_long", tlong, me);
                break;
        }

        // ����ͼ���ṩ�ĺ������ԼǺ�
        if( query("tattoo_str", ob) )
                addn("tattoo/tattoo_str",query("tattoo_str",  ob), me);

        if( query("tattoo_int", ob) )
                addn("tattoo/tattoo_int",query("tattoo_int",  ob), me);

        if( query("tattoo_con", ob) )
                addn("tattoo/tattoo_con",query("tattoo_con",  ob), me);

        if( query("tattoo_dex", ob) )
                addn("tattoo/tattoo_dex",query("tattoo_dex",  ob), me);

        if( query("tattoo_per", ob) )
                addn("tattoo/tattoo_per",query("tattoo_per",  ob), me);

        // ����ͼ���ṩ�����⼼��
        special=query("tattoo_special", ob);
        if (special)
        {
                set("special_skill/"+special, 1, me);
                set("tattoo/special/"+special, 1, me);
        }

        // ִ�д���Ĺ�������
        me->start_busy(bind((: call_other, __FILE__, "tattoo" :), me));

        remove_call_out("time_out");
        destruct(ob);
        return 1;
}

int tattoo(object me)
{
        object ob;
        string msg;
        int finish;

        if( !query_temp("tattoo/step", me) )
                set_temp("tattoo/step", 1, me);

        finish = 0;
        switch(query_temp("tattoo/step", me) )
        {
        case 1:
                msg = "������߽����ã��˳�һ��̴ľ����У��������һ�����롣";
                break;
        case 2:
                msg = "��������ӽ�$N������ڷŶ�����������ͼ���е�����ʩ�롣";
                break;
        case 3:
                msg = "ֻ��������Ƴ���磬ÿһ�����һմ��������ȥ��ΪѸ�ݡ�";
                break;
        case 4:
                msg = "����ʱ�������������ѱ�����ӹ��ճ�������ͼ�ڷֺ����";
                break;
        case 5:
                msg = "��һ�ᣬ$N�����ϵ����������������������뼡����Ϊһ�塣";
                break;
        case 6:
                msg = "�㲻����̾����ӵ��뷨���棬����ǧ���뾹������Ѫӿ����";
                break;
        case 7:
                msg = "����ӽ��ŴӺ�����ȡ��ʮ��ɫ��ƿ����ȡ��ĩ����ɫ���С�";
                break;
        case 8:
                msg = "�������ָ�׼�����������ɫ��ĩ���ٷֱ���$N����֮�ϡ�";
                break;
        case 9:
                msg = "�������ã����ڴ����ϵĸ�ɫ��ĩ�Ѿ�����������$N�ļ�����";
                break;
        case 10:
                msg = "�����ϵ���ɫ������¶�˳�����ɫ�����ޣ���ͼ�ڸ��޶��¡�";
                break;
        case 11:
                msg = "ֻ�������ϵ���������ϸ����������������Ҫ�������һ�㡣";
                break;
        case 12:
                msg = "�����������ã����˵�ͷ�������ȥ�˴�����ʣ��ķ�ĩ��";
                break;
        default:
                msg = "����Ӷ�$N˵����ͼ���ϵ������Ѿ�������̺��ˣ�����ɡ�";
                finish = 1;
                break;
        }
        msg += "\n";

        msg = replace_string(msg, "$N", "��");
        msg = replace_string(msg, "$n", name());
        message("vision", HIG + msg + NOR, me);

        if (finish)
        {
                if (objectp(ob = present("qingyang zi", environment(me))))
                {
                        delete_temp("item", ob);
                        message_vision(HIC "\n$N" HIC "��$n" HIC "˵����"
                                       "Ǯ�����ˣ�������������ˣ��Ӵ���"
                                       "��������Ƿ��\n" NOR, ob, me);
                }

                delete_temp("item", me);
                delete_temp("tattoo/step", me);
                tell_object(me, HIY "\n�����������е������ƺ�����ĳ"
                                "�����صı仯��\n" NOR);
                return 0;
        }
        addn_temp("tattoo/step", 1, me);
        return 1;
}

void time_out(object me, object ob)
{
        object money;
        int at_present;

        money = query_temp("item/money");

        if (! objectp(me))
                me = find_player(query_temp("item/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                command("say ��֣��ղ���λ�����أ���ô������ˣ�\n");
                at_present = 0;
        } else
        {
                command("say ��������ԥ�ɣ��ҿɲ��ܸ�����ţ���������ɣ�");
                at_present = 1;
        }

        delete_temp("item");
        if (objectp(me))
                delete_temp("item", me);

        if (money)
        {
                if (at_present)
                        command("give"+query("id", money)+
                                "to"+query("id", me));

                if (environment(money) == this_object())
                        command("drop"+query("id", money));
        }

        if (ob)
        {
                if (at_present)
                        command("give"+query("id", ob)+
                                "to"+query("id", me));

                if (environment(ob) == this_object())
                        command("drop"+query("id", ob));
        }
}