// qi.c �ݳ���

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

int do_answer();

void create()
{
        set_name("�ݳ���", ({ "qi changfa", "qi" }));
        set("title", "��ʬ���Ŵ���");
        set("nickname", HIR "���˲��õ���" HIC "Ը" HIR "���Ϲ�" NOR);

        set("gender", "����");
        set("age", 48);
        set("str", 100);
        set("long",
                "���ϰ�����Ǳ�����ƣ���ν�����겻���ţ����Ź����ꡣ\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("higgling", 800);
        set_temp("apply/damage", 15);

        set("combat_exp", 800000);
        set("attitude", "friendly");

        set("inquiry", ([
                "����" : (: do_answer :),
                "����" : (: do_answer :),
                "����" : (: do_answer :),
                "����" : "�ӵ���û�ˣ��ٺ١�",
                "����Ǯ"     : "�ߣ����������н��޳���",
                "�ҵ�Ǯ"     : "ʲô���Ǯ�����ϵľ����ҵģ�",
                "Ǯ"         : "��Ǯ�����Լ�ȥ����",
                "�ҵĶ���"   : "�ӵ���û�ˣ��ٺ١�",
                "��"         : "�ꣿû���꣡",
                "����������" : "��������������ƽ�һ����",
                "�����"     : "���ΰٶ������������ܻ",
                "�쾦���"   : "��Ȼ������������������������������ܽ�ٶ���",
                "�ּۻ���"   : "����ѧ(higgling)... �Һ����",
                "higgling"   : "����ѧ�ּۻ���ô... �Һ����",
        ]));

        set("vendor_goods", ([
                "/d/item/obj/xuantie"     : "3000000",
                "/d/item/obj/butian"      : "8000000",
                "/d/item/obj/wujins"      : "3000000",
                "/d/item/obj/tiancs"      : "8000000",
                //"/clone/medicine/baoming" : "3000000",
                //"/clone/medicine/jiuhua"  : "3000000",
                "/d/shenlong/obj/hua4"    : "30000000",
                "/clone/misc/zhujingchan" : "20000000",
                "/clone/gift/shenliwan"   : "100000000",
                "/clone/gift/xisuidan"    : "100000000",
                "/clone/gift/xiandan"     : "100000000",
                "/clone/gift/unknowdan"   : "100000000",
                "/clone/misc/dymo"        : "5000000",
                "/clone/item/magicfruit"  : "200000000",
                "/clone/gift/kardan"      : "5000000",
                "/clone/gift/perwan"      : "5000000",
                "/clone/gift/huirongwan"   : "50000000",
                "/clone/gift/htdan"   : "50000000",
                "/clone/goods/washgift"   : "10000",
                "/clone/goods/dizangshi"   : "15000000",
                "/clone/goods/zhufu_sword"   : "1000000",
                "/clone/goods/zhufu_blade"   : "1000000",
                "/clone/goods/zhufu_staff"   : "1000000",
                "/clone/goods/zhufu_whip"   : "1000000",
                "/clone/goods/zhufu_hammer"  : "1000000",
                "/clone/goods/zhufu_finger"   : "1000000",
                "/clone/goods/zhufu_hand"   : "1000000",
                "/clone/goods/zhufu_armor"   : "1000000",
                "/clone/goods/zhufu_cloth"   : "1000000",
                "/clone/goods/zhufu_head"   : "1000000",
                "/clone/goods/zhufu_boots"   : "1000000",
                "/clone/goods/zhufu_surcoat"   : "1000000",
                "/clone/goods/zhufu_waist"   : "1000000",
                "/clone/goods/zhufu_wrists"   : "1000000",
                "/adm/npc/obj/gift"   : "1000000",
        ]));

        setup();
        set_max_encumbrance(100000000);
        if (clonep()) keep_heart_beat();
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
        add_action("do_drop", "drop");
        add_action("do_look", ({"guankan", "kan"}));
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom")) &&
            find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character() ||
                            interactive(ob) || playerp(ob) ||
                            query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob)) &&
                            find_object(start_room) == environment())
                                continue;

                        message_vision("$N������ü����$n���˳�ȥ��\n",
                                       this_object(), ob);
                        ob->move("/d/city/beidajie1");
                }
        }

        ::heart_beat();
}

int do_drop(string arg)
{
        int i;
        object *obs;
        object ob;
        object me;

        if (! arg)
                return 0;

        me = this_player();
        if (objectp(ob = present(arg, me)) &&
            ob->is_character() && ! playerp(ob))
        {
                addn_temp("static/drop_npc", 1, me);
                if( query_temp("static/drop_npc", me)>1 &&
                    query("combat_exp", me) >= 50000 )
                {
                        message_vision("$N��ŭ�������������" +
                                       RANK_D->query_rude(ob) +
                                       "���������ң���\n˵��ֻ��$N"
                                       "����һ�ţ���$n��" + ob->name() +
                                       "һ���߳����⡣\n", this_object(), me);
                        ob->move("/d/city/beidajie1");
                        me->move("/d/city/beidajie1");
                        message("vision", "ֻ�������۹�һ����" + me->name() +
                                          "����һ�����˳�����\n",
                                environment(me), me);
/*
                        me->receive_damage("qi", 1);
                        me->die();
*/
                        return 1;
                }

                message_vision("$Nŭ�������������ٸ������ң�Ӱ���ҵ����⡣��\n"
                               "˵��ֻ��$N����һ�ţ���$n��" + ob->name() +
                               "һ���߳����⡣\n", this_object(), me);
                ob->move("/d/city/beidajie1");
                me->move("/d/city/beidajie1");
                message("vision", "ֻ�������۹�һ����" + me->name() +
                                  "����һ�����˳�����\n",
                        environment(me), me);
/*
                me->receive_damage("qi", 1);
                me->unconcious();
*/
                return 1;
        }

/*
        if (! DROP_CMD->main(me, arg))
                return 0;

        if (! GET_CMD->main(this_object(), arg))
                return 1;
*/

        if (objectp(ob) && ! ob->is_character()) destruct(ob);
        obs = all_inventory(this_object());
        for (i = 0; i < sizeof(obs); i++)
                if (! obs[i]->is_character()) destruct(obs[i]);
        if (! random(5))
        {
                switch (random(4))
                {
                case 0:
                        command("say �ջ����ۣ�С��֮·��");
                        break;
                case 1:
                        command("kok "+query("id", this_player()));
                        command("say �������������������Ԫ��");
                        break;
                case 2:
                        command("say �ܼ��ӣ��ܼ��ӣ�");
                        break;
                default:
                        command("heihei");
                        break;
                }
        }
        return 1;
}

int do_answer()
{
        write(name() + "�����������˵������");
        ::do_list();
        write("������ǻ����ʵ��ͯ�����۰���\n");
        return 1;
}

int accept_object(object who, object ob)
{
        if( query("money_id", ob) )
        {
                if( !query_temp("mark/��", who) )
                        set_temp("mark/��", 0, who);

                if( query("money_id", ob) && ob->value() >= 10000 )
                {
                        message_vision("$Nͬ��ָ��$nһЩ�ּۻ��۵õļ��ɡ�\n",
                                       this_object(), who);
                        addn_temp("mark/��", ob->value()/100, who);
                        destruct(ob);
                        return 1;
                }
                command("say �����Ǯ... ����Ȼ��ɻ��濴���ϣ�");
                return -1;
        }

        switch (random(6))
        {
        case 0:
                command("say �ã��ã�");
                break;
        case 1:
                command("say ��Ҫ�͸��ң�");
                break;
        }

        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }

        return 1;
}

void unconcious()
{
        message_vision("\n$N�ߺ�������������������...Ŷ����\n",
                       this_object());
        full_self();
}

void die()
{
        message_vision("\n$N���һ����������ʹ����������æ�ͳ������������������š�\n",
                       this_object());
        full_self();
}

int recognize_apprentice(object ob, string skill)
{
        if( query_temp("mark/��", ob)<1 )
                return 0;

        if (skill != "higgling")
                return 0;

        addn_temp("mark/��", -1, ob);
        return 1;
}
