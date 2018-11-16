 // walker.c
 // Updated By Plzw for walker quest 2004-08-17


#include <ansi.h>

//#define ONEDAY (86400 / 365)
#define ONEDAY 480


inherit NPC;

int do_walk();
int ask_quest();

void create()
{
        set_name("ʰ����", ({ "walker" }));
        set("gender", "����");
        set("age", 53 + random(20));
        set("long", @LONG
����һ��ʰ���ߣ�����ȥ��ʵ�ͽ��ġ�������
˵���͹ٸ��н��飬��ñ�ȥ���ǡ�
LONG);
        set("attitude", "heroism");
        set("str", 35);
        set("int", 15);
        set("con", 19);
        set("dex", 17);
        
        set_skill("gleaning", 600);

        set("chat_chance", 30);
        set("chat_msg", ({
                (: do_walk :),
        }));

        set("inquiry", ([
                "ʰ��" : (: ask_quest :),
                "help" : (: ask_quest :),
        ]));
        setup();
        if (clonep()) keep_heart_beat();

        set("check_time", time());
        carry_object("/clone/cloth/cloth")->wear();
}

int do_walk()
{
        string start_room;
        object room;
        object ob;
        mapping obmap;
        int n;

        if (! environment())
                return 0;

        if (time() - query("check_time") > 900)
        {
                if (! stringp(start_room = query("startroom")) ||
                    ! objectp(room = find_object(start_room)) ||
                    !mapp(obmap=query_temp("objects", room)) || 
                    member_array(this_object(), values(obmap)) == -1)
                {
                        message_vision(CYN "$N" CYN "̾��̾�������ˡ�\n"
                                       NOR, this_object());
                        destruct(this_object());
                        return 0;
                }

                set("check_time", time());
        }

        n = 0;
        foreach (ob in all_inventory(environment()))
        {
                if (ob->is_character() ||
                    ob->is_head() ||
                    query("no_get", ob) )
                        continue;
                destruct(ob);
                n++;
        }

        if (n == 1)
                message_vision(HIC "$N" HIC "һ�������ӵ��ϼ���һ��"
                               "������\n" NOR, this_object());
        else
        if (n > 1)
                message_vision(HIC "$N" HIC "�����ڵ���������������"
                               "���죬����һ�Ѷ�����\n" NOR,
                               this_object());
                        
        random_move();
        return 1;
}

void unconcious()
{
        die();
}

int ask_quest()
{
        int t, count;
        object ob = this_player();
        // ��������������ȡ����
        if( query("score", ob)<2000 )
        {
                command("say ��������������µ�ͼ����û������ɣ�����������������ˣ�\n");
                return 1;
        }
        // ʰ�ļ��ܲ���������ȡ����
        if (ob->query_skill("gleaning", 1) < 30)
        {
                command("say �������ʲô����������֪�������Ǻ���ѧѧ��˵�ɣ�\n");
                return 1;
        }
        // ��������������
        if( query("walker_quest/finish_time", ob) )
        {
                if( time()-query("walker_quest/finsh_time", ob)<ONEDAY )
                {
                        command("say �����ҲҪע�����壬������Ϣ��Ϣ�����������ɣ�\n");
                        return 1;
                }
            }
        // �Ѿ����������δ���
        if( query("walker_quest/count", ob) )
        {
                command("say �㲻�Ǵ�Ӧ�Ұ���ʰ�����𣿻�վ����������ʲô��\n");
                return 1;
        }
        // ��ȡ����
        t = time();
        set("walker_quest/time", t, ob);
        // �������
        count = random(9) + 1;
        set("walker_quest/count", count, ob);
        if (count > 5)
                t += 3 * ONEDAY;
        else
                t += 2 * ONEDAY;
        set("walker_quest/limit", t, ob);

        message("vision", WHT + name() + WHT "С���Ķ�" + ob->name() +
                          WHT "�Ը���ʲô��" + ob->name() +
                          WHT "һ������һ�߲�ס�ĵ�ͷ��\n" NOR,
                          environment(ob), ({ ob }));
        message("vision", WHT + name() + WHT "�����������˵�������ȥ����"
                                          NOR + HIY + CHINESE_D->chinese_number(count) + NOR + WHT
                                          "���������ɣ�\n�����Ҫ��" NOR + HIY + CHINESE_D->chinese_monthday(t) + NOR + WHT
                          "֮ǰ��ɣ�\n" NOR, ob);
        ob->start_busy(1);
        return 1;
}

int accept_object(object who, object ob)
{
        int count, intime, amount, pot, score, weiwang, exp;
        object gold, silver;
        // û���������
        if( !query("walker_quest/count", who) )
        {
                command("say ����������������\n");
                return -1;
        }
        // ��������Ʒ
        if( !query("walker_item", ob) )
        {
                command("say ��Щ�������˻����ã�����ô�͸������ˣ�\n");
                return -1;
        }
        count=query("walker_quest/count", who);
        set("walker_quest/count", count-1, who);
        if( query("walker_quest/limit", who)>time() )
                intime = 1;
        else
                intime = 0;
        if (intime)
                command("say �������ò������Ǹ���Ľ�����\n");
        else
                command("say ������Ȼ���˵㣬��Ҳ���������Ǹ���Ľ�����\n");
        amount = random(2) + 1;
        exp = random(30) + 10;
        pot = exp / 3;
        score = random(5) + 2;
        weiwang = random(2) + 1;
        if (intime)
        {
                // 1/4�ļ��ʻ�ö���Ľ���
                if (random(4)==0)
                        amount++;
                gold = new("/clone/money/gold");
                gold->set_amount(amount);
                gold->move(this_object());
                command("give gold to "+query("id", who));
                // �����ʱ��ɵĻ����õ��Ľ����ӱ�
                pot *= 2;
                score *= 2;
                exp *= 2;
        }
        else
        {        
                amount = amount * 50;
                silver = new("/clone/money/silver");
                silver->set_amount(amount);
                silver->move(this_object());
        }
                
                // ���ʰ�ļ��ܳ���60�������ӱ�
                if (who->query_skill("gleaning", 1) >= 60)
                {
                        pot *= 1.5;
                        score *= 2.5;
                        exp *= 2;
                }
        GIFT_D->work_bonus(who, ([ "exp" : exp, "pot" : pot, "score" : score ]));
        addn("weiwang", -weiwang, who);
        if( query("weiwang", who)<0 )
                set("weiwang", 0, who);
        // ȫ�����
        if( query("walker_quest/count", who) == 0 )
        {
            set("walker_quest/finish_time", time(), who);
            command("say ���ˣ���Ҳ���ˣ�ȥ��Ϣ��Ϣ�ɣ�\n");
        }
        else
                       message("vision", WHT + name() + WHT "�����������˵�����㻹��Ҫ���Ҽ�"
                                          NOR+HIY+CHINESE_D->chinese_number(query("walker_quest/count", who))+NOR+WHT
                                          "��������\n" NOR, who);
        destruct(ob);
        return 1;
}

int recognize_apprentice(object me, string skill)
{

        if (skill != "gleaning")
        {
                command("say �ҳ���ʰ�����У�������ʲô�����ᰡ��\n");
                return -1;
        }

        return 1;
}
