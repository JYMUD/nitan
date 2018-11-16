// ultraquestd.c
// Written by Vin for Heros.cn 2002/08/16.
// Rewritten by Lonely@nitan.org

#include <ansi.h>
#include <quest.h>

inherit F_DBASE;

// �����ṩ���ⲿ���õĽӿں���
public mixed accept_ask(object me, object who, string topic);
public mixed ask_information(object me, object who, string topic);
public void generate_information(object me, object who);
public void give_quest(object me, object who);
public void give_accede(object me, object who);
public void quest_guard(object me, object who);
public void quest_going(object me, object who);
public void give_gift(object me, object who);
void start_guard(object me, object who);
void check_guard(object me, object who, object killer);
void check_going(object me, object who);

#define QUEST           "/adm/etc/questlist/"
#define QUESTER "����"
#define LURCHER "����"

private void special_bonus(object me, object who)
{
        object ob;
        string un;

        // �����������Ʒ������
        string *ob_list = ({
                "/clone/tessera/gem",
                "/clone/fam/item/bless_water",
                "/clone/fam/pill/dimai",
                "/clone/fam/pill/yulu",
                "/clone/fam/pill/renshen4",
                "/clone/fam/pill/lingzhi4",
                "/clone/fam/pill/xuelian4",
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/puti4",
                "/clone/fam/pill/sheli4",
                "/clone/fam/pill/sheli3",
                "/clone/fam/pill/puti3",
                "/clone/fam/pill/puti2",
                "/clone/fam/pill/sheli2",
        });

        ob = new(ob_list[random(sizeof(ob_list))]);

        // �鿴��Ʒ�ĵ�λ����
        if( query("base_unit", ob) )
                un=query("base_unit", ob);
        else
                un=query("unit", ob);

        // ������������ give ��Ϣһ��
        message_vision("$N˵���ó�һ" +
                       un+ob->name()+NOR"("+query("id", ob)+
                       ")��$n" NOR "��\n\n" NOR, me, who);

        ob->move(who, 1);
}

// �������ʼ���򣬸�������������ṩ������
public mixed accept_ask(object me, object who, string topic)
{
        object item;
        string msg;
        string type;
        mapping q;

        if (topic == "����" || topic == "quest")
        {
                message_vision("$n��$N�����й���ʦ����������\n", me, who);
                if (! ultrap(who))
                {
                        message_vision("$N�ɴ��۾�����$n���������㻹û�г�Ϊ��ѧ����ʦ�����ﲻ��"
                                       "��ʲôæ����\n", me, who);
                        return 1;
                }

                q=query("ultraquest", who);
                if (mapp(q))
                {
                        switch (q["type"])
                        {
                        case "find":   // Ѱ��
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����"
                                               "���" NOR + HIR + q["name"] + "(" + q["id"] +
                                               ")" + NOR + CYN "����������������������أ�\n" NOR,
                                               me, who);
                                break;
                        case "send":   // ����
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����"
                                               "��Ѱ����͸�" NOR + HIR + q["name"] + "(" + q["id"] +
                                               ")" + NOR + CYN "�������ڻ�ִ�أ�\n" NOR,
                                               me, who);
                                break;
                        case "rescue": // ����
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����"
                                               "��ȥ��" NOR + HIR + q["name"] + "(" + q["id"] +
                                               ")" + NOR + CYN "��ȳ��������������أ�\n" NOR,
                                               me, who);
                                break;

                        case "kill":   // ɱ��
                                message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����"
                                               "��ȥ�����𽭺��ȷ�Ѫ���Ļ����ı����������"
                                               "����ͷ�أ�\n" NOR, me, who);
                                break;

                        }
                        return 1;
                }

                if( query("combat_exp", who)<20000000 )
                {
                        message_vision(CYN "$N" CYN "̾��һ��������$n" CYN "���������ǵ�ˮƽ��"
                                       "��ʵ��û������������\n" NOR, me, who);
                        return 1;
                }

                if( query("score", who)<200000 )
                {
                        message_vision(CYN "$N" CYN "̾��һ��������$n" CYN "��������������̫�ͣ�"
                                       "��ͨ�������ﲻ����ʲôæ��\n" NOR, me, who);
                        return 1;
                }

                if( query("weiwang", who)<200 )
                {
                        message_sort(CYN "$N" CYN "���˿�$n" CYN "��̾����������"
                                     "������һ����ͷ��û�У���û�����İ����񽻸�"
                                     "�㡣\n" NOR, me, who);
                        tell_object(who, HIY "�������ǵļ�ǿ�Լ��Ľ����������С�\n" NOR);
                        return 1;
                }
                /*
                if (who->is_bad() && me->is_good())
                {
                        message_sort(CYN "$N" CYN "��ŭ�������д������Ȼ�Ѿ���"
                                     "����;�����������ң�\n" NOR, me, who);
                        return 1;
                }

                if (who->is_good() && me->is_bad())
                {
                        message_sort(CYN "$N" CYN "��ŭ�������д����ż��첻����"
                                     "���ȻҲѧ����ʼ������ˣ�����ҹ���\n"
                                     NOR, me, who);
                        return 1;
                }
                */

                // ����ԭ�����������������Ѱ����˵ȣ�������Ϊһ������
                switch (random(4))
                {
                case 0:
                        type = "kill";
                        message_sort(CYN "$N" CYN "������$n" CYN "��ã����ŵ�ͷ�������ڽ�"
                                     "�����岻�죬а�����У��ȷ�Ѫ�겻�ϣ���˵��һ�ж�����"
                                     "���ڲ��ݣ������ȥ��������ı��˭��������ͷ­������"
                                     "��\n" NOR, me, who);
                        break;
                case 1:
                        type = "kill";
                        message_sort(CYN "$N" CYN "��$n" CYN "��������������������ش���"
                                     "����ʱ�����ȷ�Ѫ�꣬�ⱳ��϶����˲��ݣ������ȥ���"
                                     "Ļ����ı��������ͷ­�����ҡ�\n" NOR, me, who);
                        break;
                case 2:
                        type = "kill";
                        message_sort(CYN "$N" CYN "��$n" CYN "������˵��һ���������ڲ߻���"
                                     "�����������ȷ�Ѫ�꣬��ͼ�߸����֣������ȥ���Ļ����"
                                     "ı��˭����������ͷ�����ҡ�\n" NOR, me, who);

                        break;
                case 3:
                        type = "kill";
                        message_sort(CYN "$N" CYN "��$n" CYN "����������������ȷ�Ѫ�꣬��"
                                     "���ɱ���һ������ı����ȥ���Ҳ��������ı��˭��������"
                                     "ͷ­�����ҡ�\n" NOR, me, who);
                        break;
                }

                set("ultraquest/type", type, who);
                // ִ���ṩ�����ĳ��򣬱���Ԥ���趨�ṩ��
                set("ultraquest/id",query("id",  me), who);
                set("ultraquest/name",query("name",  me), who);

                generate_information(me, who);
                return 1;
        }

        if (topic == "����" || topic == "clue")
        {
                if( !query("ultraquest/type", who) )
                        return "��Ҫ��ʲô�£�˵���������׵ġ�";

                if( query("ultraquest/finish", who) == 5 )
                        return "�������Ѿ���������𣿻���Ҫʲô������";

                // ���ֻ�������ṩ��������
                if( query("ultraquest/ask", who) >= 3 )
                        return "�²�������ʣ�µ��������Լ���취�����\n"
                               "���ߣ������ȥ���ұ�����Ҳ���ܰ��㡣";

                switch(query("ultraquest/ask", who) )
                {
                case 0:
                        msg = "������ǵ�һ�Σ�ϣ�����������»ء�";
                        break;

                case 1:
                        msg = "���Ѿ������һ���ˣ�����ǵڶ��Ρ�";
                        break;

                default:
                        msg = "���Ѿ������һ���ˣ���������Ϊ֮��";
                        break;
                }

                message_sort(WHT "\n$N" WHT "������ü����$n" WHT "���������������"
                             "������ʵ��һ�������Ĺ��̣��ܶ�ط����뾭��ĥ����ƾ��"
                             "�����������������ܰ쵽��������������������԰���"
                             "���Ρ�" + msg + "\n\n" NOR, me, who);

                // ȡ����ǰ����������
                delete("ultraquest/quest", who);//��֧����
                delete("ultraquest/gift", who);//��֧������
                delete("ultraquest/finish", who);//��֧���������
                delete("ultraquest/fail", who);//��֧����ʧ�ܵļ�¼
                delete("ultraquest/place", who);//�ṩ��������ĵص�

                // ��¼����ѯ�ʵĴ���
                addn("ultraquest/ask", 1, who);

                // ��¼�ṩ��������������
                set("ultraquest/id",query("id",  me), who);
                set("ultraquest/name",query("name",  me), who);

                // �����ṩ����
                generate_information(me, who);
                return 1;
        }

        if (topic == "ȡ��" || topic == "cancel")
        {
                /*
                if( !query("ultraquest/type", who) )
                        return "��û����ʲô���񰡣�";
                */

                addn("weiwang", -50, who);
                if( query("weiwang", who)<0 )
                        set("weiwang", 0, who);

                addn("score", -100, who);
                if( query("score", who)<0 )
                        set("score", 0, who);

                delete("ultraquest", who);
                delete("ultra_count", who);
                message_vision(CYN "$N" CYN "̾���������˿�$n" CYN "���������С�¶��ɲ��ˣ����˰ɡ�\n" NOR,
                               me, who);
                tell_object(who, HIR "��Ľ��������ͽ��������ܵ�����ʧ��\n" NOR);
                return 1;
        }

}

// ѯ�����������Ҫ�� /inherit/char/npc.c ���Ӷ�Ӧ����
public mixed ask_information(object me, object who, string topic)
{
        string msg;
        string type, ob;

        if( stringp(type=query("ultraquest/quest/type", who)) &&
            stringp(ob=query("ultraquest/quest/name", who)) &&
            topic == ob)
        {
                // �ṩ������������ṩ����������Ϣ�Ľ��
                switch (type)
                {
                        case "kill" :
                                msg = "���������ҡ��Һ޲��ð�����ʬ��ϣ�";
                                break;

                        case "find" :
                                msg = "˵�����Ƕ���Ҳ�����ң����Լ�������ɡ�";
                                break;

                        case "send" :
                                msg = "��ʵ������Ҳ���Ǻ��죬���Ĵ�ȥ���ʰɡ�";
                                break;

                        case "give" :
                                msg = "�Һܾ�û�������ˣ�Ҳ�����������������";
                                break;

                        case "going" :
                                msg = "�Ҹ���˵�ú�����˰���Ī����Ҳ��ʶ·��";
                                break;
                }
                return msg;
        }

        if (topic == "����" || topic == "clue")
        {
                // �����ǰ�������޷�ִ�У����ж�
                if( query("ultraquest/fail", who) )
                        return "���鵽����һ������Ҳû���ٰ����ˡ�";

                // ����Ѿ������������򷵻�
                if( query("ultraquest/quest/msg", who) )
                        return "�Ҳ�������" +
                               query("ultraquest/quest/msg", who)+
                               "�𣿻�����ʲô��";

                switch (random(4))
                {
                case 0:
                        msg = "��Ҫ�ҵ���������ȷʵ֪��һЩ������"
                              "���ȵð��Ҹ�æ��";
                        break;

                case 1:
                        msg = "������ȷʵ�������֪����üĿ������"
                              "��Ϣ�ɲ��ܰ׸���";
                        break;

                case 2:
                        msg = "����Ϊһ���·��������ܰ������"
                              "æ��������Ը����㡣";
                        break;

                default:
                        msg = "���Լ������鶼æ�����������ﻹ�˵�"
                              "���㣬���������ǡ�";
                        break;
                }
                message_vision(CYN "$N" CYN "ҡͷ����" + msg + "\n"
                               NOR, me, who);

                // �����������Ҫ��ִ�м������������
                if( query("combat_exp", me) >= 100000
                     && query("age", me) >= 20
                     && !query_temp("need_accede", me )
                    && random(3) == 1)
                {
                        me->stop_move(); // ֹͣ�ƶ�λ��
                        give_accede(me, who);
                        return 1;
                }

                // �����������Ҫ��ִ�б�����������
                if( query("combat_exp", who)>query("combat_exp", me)*2/3
                     && !query("no_fight", environment(who) )
                     && !query_temp("start_guard", me )
                    && random(3) == 1)
                {
                        /*
                        if (random(2) == 1)
                        {
                                // ֹͣ�ƶ�λ��
                                me->stop_move();
                                // ִ�л��͵�����
                                quest_going(me, who);
                                return 1;
                        } else
                        {
                        */
                                // ֹͣ�ƶ�λ��
                                me->stop_move();
                                // ִ�б���������
                                quest_guard(me, who);
                                return 1;
                        /*
                        }
                        */
                }

                // ����ϵͳԤ������
                give_quest(me, who);
                me->stop_move(); // ֹͣ�ƶ�λ��
                return 1;
        }
}

// ����������ķ���
public void give_accede(object me, object who)
{
        string msg, type, quest_msg;
        string skill;
        string ma, mb, wa, ac;
        int exp, lvl;

        // ���˳Ƽ������ַ�������д����
        ma = RANK_D->query_self(me);
        mb = RANK_D->query_self_rude(me);
        wa = RANK_D->query_respect(who);
        ac = "(" HIY "accede" NOR + WHT ")";

        switch (random(6))
        {
        case 0:
                msg = random(2) ? "��λ" + wa + "��" + ma + "�������о�"
                                  HIW "����" NOR + WHT "�׾��������ĵá�"
                                  "���Ҷ��˱�������" + ac + "һ�̣�����"
                                  "����ʤ���ҡ���ô" + ma + "��֪������"
                                  "�������������":

                                  wa + "�������ã�" + mb + "����û������"
                                  "�������������ұ���" + ac + "һ��" HIW
                                  "����" NOR + WHT "����������ʤ��������"
                                  "����ǩ�����̣��Ұ���֪����һ�ж�������";

                quest_msg = "���ұ�������";
                type = "mathematics";
                break;

        case 1:
                msg = random(2) ? "��λ" + wa + "��" + ma + "�������о�"
                                  HIW "ʫ��" NOR + WHT "�踳���д����"
                                  "���Ҷ��˱�����ʫ" + ac + "���ԣ�����"
                                  "���ܶ�Ӯ" + ma + "����ô����֪������"
                                  "�������������":

                                  "�ҿ�" + wa + "Ҳ����Ҫ�£���Ȼ���Ҷ�"
                                  "�˶�����ģ���������ʫ" + ac + "��"
                                  "�ԣ���ͬ̽��̽��" HIW "��ѧ" NOR + WHT
                                  "֪ʶ������������ʤ�ң�" + ma + "����"
                                  "������֮";

                quest_msg = "������ʫ�Զ�";
                type = "literate";
                break;

        case 2:
                msg = random(2) ? "��λ" + wa + "��" + ma + "�������о�"
                                  HIW "����" NOR + WHT "֮���������ĵá�"
                                  "���Ҷ��˱�������" + ac + "һ�֣�����"
                                  "����ʤ���ҡ���ô����֪��������������"
                                  "�����":

                                  wa + "��������ҿ���Ҳû��Ҫ����������"
                                  "��������ɱ" + ac + "һ��" HIW "��" NOR +
                                  WHT "��ʡ�����ġ�����������ʤ�Ҽ��ӣ���"
                                  "���֪����ȫ��������Ҳ�޷�";

                quest_msg = "������һ����";
                type = "chess";
                break;

        case 3:
                msg = random(2) ? "��λ" + wa + "�������ã�" + ma + "��Ϊ"
                                  "һ�·�������������ѵĴ��٣�" + ma +
                                  "��������һ�������Ա�ף�أ�������" HIW
                                  "�鷨" NOR + WHT "����Ƿ�ѣ��������ܰ�" +
                                  ac + "�Ҵ�������Ը��" + ma + "�м���"
                                  "��������Ҳ�����������":

                                  wa + "��������ʱ��" + ma + "��Ϊһ��"
                                  "�������˵������ǰ����һλֿ��Ϊ����"
                                  "���������Ҳ���������" + ma + "����Ѱ��"
                                  "һλ" HIW "�鷨" NOR + WHT "����Ϊ����"
                                  "д���ʣ�ȴ��֪" + wa + "�ܷ��" + ac +
                                  ma + "��������Ը";

                quest_msg = "����дһ����";
                type = "calligraphy";
                break;

        case 4:
                msg = random(2) ? "��λ" + wa + "�������ã�" + ma + "��Ϊ"
                                  "һ�·��ǰ��������ϲ�ù��ӣ�" + ma +
                                  "��������һ��ϲͼ�Ա�ף�أ�������" HIW
                                  "����" NOR + WHT "����̫��������ܰ�" +
                                  ac + "�Ҵ�������Ը��" + ma + "�м���"
                                  "��������Ҳ�����������":

                                  "�����" + ma + "�и�����֮�룬����" + wa +
                                  "��æ" + ac + "��ɡ�" + ma + "�и�����"
                                  "������֪��������λ" HIW "����" NOR + WHT
                                  "���֣�����ȥ�ݷá�ȴ��֪����α�����"
                                  "��" + wa + "�д�֮�����ܹ�Ͷ�����ã���"
                                  "��м�����";

                quest_msg = "���һ�һ����";
                type = "drawing";
                break;

        default:
                msg = random(2) ? "�š�" + wa + "�����������" + ma + "��"
                                  "�˶��֣���С�����˽�ǣ����ձ���ҽ�Ρ�"
                                  "�����θ����Ҳ���һλ" HIW "ҽ��" NOR +
                                  WHT "�õ�Ĵ�������ܰ�æ" + ac + "��"
                                  "�ô��ˣ�" + ma + "�м�����������Ҳ����"
                                  "�������":

                                  "�����㽲��" + wa + "��ǰ����" + ma +
                                  "���˹��У��������˵����ˣ�������δȬ��"
                                  "�������ⲡʹ֮��ίʵ�Ѱ�����������ͨ��"
                                  HIW "ҽ��" NOR + WHT "���ܹ�����" + ac +
                                  ma + "��ʹ�Ļ���" + ma + "����֪����һ��"
                                  "ȫ����֮";

                quest_msg = "����ҽ�β�ʹ";
                type = "medical";
                break;
        }

        // �ṩ�������������Ϣ
        msg = WHT "\n" + me->name() + WHT "��˼Ƭ�̣�����"
              "˵����" + msg + "��\n\n" NOR;

        message("vision", me->name() + "��" + who->name() +
                "����С��˵��Щʲô��\n",
                environment(who), ({ who }));

        tell_object(who, sort_msg(msg));

        // ����Ҫ�������
        skill = type;

        // Ϊʲô��ʮ����Ϊ��Ŀ�������ȼ��ļ���
        exp=query("combat_exp", me)*10;

        // ����������и���ܣ���ֱ�ӵ���
        // ���û�У���ȡ�����֧�ֵȼ�������
        if (me->query_skill(skill))
                lvl = me->query_skill(skill, 1);
        else
                lvl = pow(exp, 1.0 / 3) - 50;

        // �ȼ�̫�������
        if (lvl < 80) lvl = 80;

        // �ȼ�̫��������
        if (lvl > 300) lvl = 300;

        /*
        tell_object(who, HIC "��������Ϣ��" NOR + WHT + me->name() +
                         HIW " ���飺" HIC + exp / 10 +
                         HIW " ���" HIC + to_chinese(skill) +
                         HIW " �ȼ���" HIC + lvl + "\n\n" NOR);
        */

        // ע����������
        set("ultraquest/quest/type", type, who);
        set("ultraquest/quest/name",query("name",  me), who);
        set("ultraquest/quest/id",query("id",  me), who);
        set("ultraquest/quest/msg", quest_msg, who);

        // ����ע��������
        set_temp("need_accede/user",query("id",  who), me);
        set_temp("need_accede/lvl", lvl, me);

        return;
}

// ϵͳԤ������ķ���
public void give_quest(object me, object who)
{
        string quest, next_id, msg, id;
        string type, next_name, quest_msg, name, place;
        object item, ob;
        /*
        string *lines, file;
        string quest;
        object obj;

        // ����ϵͳԤ�������������������
        file = read_file(QUEST + "quest");
        file = replace_string(file, " ", "");
        lines = explode(file, "\n");

        quest = lines[random(sizeof(lines))];

        if (sscanf(quest, "%s/%s", type, obj) != 2)
                return;

        type = replace_string(type, "\r", "");
        type = replace_string(type, "\n", "");
        type = replace_string(type, " ", "");
        obj = replace_string(obj, "\r", "");
        obj = replace_string(obj, "\n", "");
        obj = replace_string(obj, " ", "");
        */

        id=query("ultraquest/id", who);
        name=query("ultraquest/name", who);

        // û���ṩ��������
        if (! id) return;

        //switch (type)
        switch (random(3))
        {
        case 0 :
                type = "kill";
                ob = new(CLASS_D("generate") + "/killer.c");
                NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
                NPC_D->set_from_me(ob, who, 120);
                addn_temp("apply/attack", ob->query_skill("force")*1/2, ob);
                addn_temp("apply/dodge", ob->query_skill("force")*1/2, ob);
                addn_temp("apply/parry", ob->query_skill("force")*1/2, ob);
                addn_temp("apply/damage", 500, ob);
                addn_temp("apply/unarmed_damage", 500, ob);
                addn_temp("apply/armor", 500, ob);
                set_temp("quester",query("id",  who), ob);

                NPC_D->random_move(ob);
                NPC_D->random_move(ob);

                next_id=query("id", ob);
                next_name=query("name", ob);
                place=query("place", ob);

                msg = random(2) ? "�����ɱ��" HIR + next_name + "(" + next_id + ")" + NOR +
                                  WHT "���ˣ���������ͷ�����ҡ�\n��˵�������" + place + "�����ȥ�ɣ�":

                                  "��ȥ��" HIR + next_name + "(" + next_id + ")" + NOR + WHT
                                  "�������ˣ��������ϵ�ͷ�����ҡ�\n��˵�������" + place + "�����ȥ�ɣ�";

                quest_msg = "����ɱ��" + next_name + "(" + next_id + ")";
                break;
        /*
        case 1 :
                type = "find";
                msg = random(2) ? "������������" + next_name + "(" + next_id + ")" + NOR +
                                  WHT "��ֻ���ͷ��ͷ�������":

                                  "�������ܰ����ҵ�" + next_name + "(" + next_id + ")" + NOR
                                  + WHT "�������ҿ����ṩЩ����";

                quest_msg = "�����ҵ�" + next_name + "(" + next_id + ")";
                break;
        */
        case 1 :
                type = "send";
                ob = new(CLASS_D("generate") + "/uq_receiver.c");
                NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
                NPC_D->set_from_me(ob, who, 100);

                NPC_D->random_move(ob);

                next_id=query("id", ob);
                next_name=query("name", ob);
                place=query("place", ob);

                msg = random(2) ? "����Ұ�������͵�" HIY + next_name + "(" + next_id + ")"
                                  + NOR + WHT "���У�Ȼ����" HIW
                                  "��ִ" NOR + WHT "�����ҡ�\n��˵�������" + place + "�����ȥ�ɣ�":

                                  "���з���Ҫ�����͵�" HIY + next_name + "(" + next_id + ")"
                                  + NOR + WHT "��������������"
                                  "���ɡ�\n��˵�������" + place + "�����ȥ�ɣ�";

                quest_msg = "���Ұ����͵�" + next_name + "(" + next_id + ")" + "��";
                item = new("/clone/misc/letter");
                break;

        case 2 :
                type = "give";
                ob = new(CLASS_D("generate") + "/uq_receiver.c");
                NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
                NPC_D->set_from_me(ob, who, 100);

                NPC_D->random_move(ob);

                next_id=query("id", ob);
                next_name=query("name", ob);
                place=query("place", ob);

                msg = random(2) ? "����Ұ���������͵�" HIY +
                                  next_name + "(" + next_id + ")" + NOR + WHT "���������"
                                  "��ʲô��Ӧ��\n��˵�������" + place + "�����ȥ�ɣ�":

                                  "�ͷ����˰���ת����" HIY + next_name + "(" + next_id + ")"
                                  + NOR + WHT "����;��Ī˽�Դ�"
                                  "����\n��˵�������" + place + "�����ȥ�ɣ�";

                quest_msg = "���ҰѰ���ת����" + next_name + "(" + next_id + ")";
                item = new("/clone/misc/baoguo");
                break;
        }

        // �ṩ��������Ϣ
        message("vision", me->name() + "������" + who->name() + "��"
                          "��˵��Щʲô��\n", environment(who),
                          ({ me, who }));

        tell_object(who, WHT + me->name() + WHT "���Ķ���˵����" +
                        msg + "��\n" NOR);

        // ע����������
        set("ultraquest/quest/type", type, who);
        //set("ultra_quest/quest/obj", obj, me);
        set("ultraquest/quest/name", next_name, who);
        set("ultraquest/quest/id", next_id, who);
        set("ultraquest/quest/msg", quest_msg, who);

        // �������������ߣ���ע���������
        if (objectp(item))
        {
                set("send/from", name, item);
                set("send/send", next_name, item);
                set("send/user", who->name(), item);
                set("long",WHT"����һ"+query("unit", item)+
                                  name + "׼��ת����" + next_name + "��" +
                                  item->name() + "��\n" NOR, item);

                // �ṩ�����ת�Ƶ���Ϣ
                message_vision("$N"NOR"�ó�һ"+query("unit", item)+
                               item->name()+NOR"("+query("id", item)+
                               ")��$n" NOR "��\n" NOR, me, who);
                item->move(who, 1);
        }
        return;
}

// ��������ķ���
public void quest_guard(object me, object who)
{
        string msg;

        message("vision", me->name() + "��" + who->name() +
                          "����С��˵��Щʲô��\n",
                          environment(who), ({ who }));

        switch (random(3))
        {
        case 0:
                msg = "�ҵĳ�ҽ���Ҫɱ������";
                break;

        case 1:
                msg = "�����и��һ����Ҫ������";
                break;

        default:
                msg = "����˵����׼�����Ҳ���";
                break;
        }

        tell_object(who, WHT + me->name() + WHT "���Ķ���"
                         "˵����" + msg + "����" HIW "����"
                         "����" NOR + WHT "������һ�¡�\n" NOR);

        // Ϊ�˷�ֹ�����ͻ��Ŀ�����ñ���������
        set_temp("start_guard", 1, me);

        // ע�ᱣ����������
        set("ultraquest/quest/type", "guard", who);
        set("ultraquest/quest/name",query("name",  me), who);
        set("ultraquest/quest/id",query("id",  me), who);
        set("ultraquest/quest/msg", "�������ﱣ����", who);
        who->start_call_out((: call_other, __FILE__, "start_guard",
                            me, who :), 5);
        return;
}

// ��������ķ���
public void quest_going(object me, object who)
{
        string *lines;
        string file;
        string where, area, place;

        // ����ϵͳԤ��ĵص�����
        file = read_file(QUEST + "place");
        lines = explode(file, "\n");
        where = lines[random(sizeof(lines))];

        if (sscanf(where, "%s/%s", area, place) != 2)
                return;

        // ���ϵͳ���õĵ�������ʼ���ظ�����ֱ��ִ��
        // ϵͳԤ����������

        if( place == query("short", environment(me)) )
        {
                generate_information(me, who);
                return;
        }

        message("vision", me->name() + "��" + who->name() +
                          "����С��˵��Щʲô��\n",
                          environment(who), ({ who }));

        tell_object(who, WHT + me->name() + WHT "���Ķ���"
                         "˵�����������е���Ҫ��" + HIW +
                         area + NOR + WHT "��" HIW + place +
                         NOR + WHT "�����ͼ������ҹ�ȥ��"
                         "\n" NOR);

        // Ŀ�꿪ʼ�����ж�
        me->set_leader(who);
        message_vision("$N������ʼ����$nһ���ж���\n", me, who);

        // Ϊ�˷�ֹ�����ͻ��Ŀ�����ñ���������
        set_temp("start_guard", 1, me);

        // ע�Ụ����������
        set("ultraquest/quest/type", "going", who);
        set("ultraquest/quest/obj", place, who);
        set("ultraquest/quest/name",query("name",  me), who);
        set("ultraquest/quest/msg", "���ҵ�"+area+"��"+place, who);

        // ��ʼ��ʱɨ��������ĵص�
        who->start_call_out((: call_other, __FILE__, "check_going",
                            me, who :), 1);
        return;
}

// ִ�б�������ĳ���
void start_guard(object me, object who)
{
        object killer;

        if (! objectp(me) || ! objectp(who)
            || environment(me) != environment(who))
                return;

        if (random(5) == 1)
        {
                message_vision(CYN "\n$N" CYN "������ͷ����Ϊ"
                               "���ε�˵�����ף��ѵ������д�"
                               "\n" NOR, me);

                if (random(3) == 1)
                {
                        message_vision(CYN "$N" CYN "��Ц����"
                                       "������$n" CYN "������"
                                       "����û�����ˣ���Ҳ����"
                                       "����һ�����Ҿ͸������"
                                       "��\n" NOR, me, who);

                        // Ŀ��ȡ��������������
                        delete_temp("start_guard", me);

                        // ������ɣ�ע�ά������
                        // set("ultraquest/name1", me->name(), who);
                        set("ultraquest/gift/point", 120, who);
                        set("ultraquest/gift/msg","��ͨ������"+
                                 query("ultraquest/quest/name", who)+"�Ĺ���", who);

                        // ϵͳ����ô�����Ľ���
                        give_gift(me, who);
                } else
                {
                        message_vision(CYN "$N" CYN "̾�˿���"
                                       "����$n" CYN "��������"
                                       "��û�����ˣ��һ�������"
                                       "��������������ɡ�\n"
                                       NOR, me, who);

                        // Ŀ��ȡ��������������
                        delete_temp("start_guard", me);

                        // �����жϣ�ϵͳ���·��������
                        give_quest(me, who);
                }
                return;
        }
        message_vision(CYN "\nͻȻ��$N" CYN "��$n" CYN "����˵��"
                       "�����ˣ�ɱ�ҵ������ˡ�\n\n" NOR, me, who);

        killer = new(CLASS_D("generate") + "/killer");
        NPC_D->set_from_me(killer, who, 120);
        killer->move(environment(me));

        message_vision(HIW "$n" HIW "���˹�������$N" HIW "��Ц"
                       "����ԭ���������������ɣ�\n" NOR, me,
                       killer);

        killer->set_leader(me);
        killer->kill_ob(me);

        // ��鱣��״̬
        who->start_call_out((: call_other, __FILE__, "check_guard",
                             me, who, killer :), 3);
}

// ��鱻���������״̬
void check_guard(object me, object who, object killer)
{
        if (! objectp(me) && ! objectp(killer))
                return;

        // ����ս�������ӳټ��
        if (objectp(killer) && objectp(me)
            && (me->is_fighting(killer)
            || who->is_fighting(killer)))
        {
                who->start_call_out((: call_other, __FILE__, "check_guard",
                                    me, who, killer :), 1);
                return;
        }

        // ������������ʧ�������ж�
        if (! objectp(me)
            && objectp(killer))
        {
                tell_object(who,HIG"���ۼ�"+query("ultraquest/quest/name", who)+
                                 HIG "��ɱ�������������㡣\n" NOR);

                // ��¼��ʧ�ܼ�¼
                set("ultraquest/fail", 1, who);
                return;
        }

        // ɱ����ʧ�ұ������˴��ڣ��������
        if (! objectp(killer)
            && objectp(me))
        {
                // ����������˻��ԣ�����ת��
                if (! living(me))
                        me->revive();

                message_vision(CYN "$N" CYN "���˲�������$n" CYN "��������"
                               "���������æ���м�������\n$N" CYN "���ŵ���"
                               "����֮�����Իر�����һ������֪���Ķ�������"
                               "��\n" NOR, me, who);

                // Ŀ��ȡ��������������
                delete_temp("start_guard", me);

                // ������ɣ�ע�ά������
                // set("ultraquest/name1", me->name(), who);
                set("ultraquest/gift/point", 250, who);
                set("ultraquest/gift/msg","��ͨ������"+
                        query("ultraquest/quest/name", who)+"�Ĺ���", who);

                // ϵͳ����ô�����Ľ���
                give_gift(me, who);
                return;
        }
        message_vision(CYN "$N" CYN "���˿����ܣ���е�����"
                       "ʦ��BUG��BUG��\n" NOR, who);
        return;
}

// ��黤�������״̬
void check_going(object me, object who)
{
        string msg, place;

        // �������Ѿ�ʧ�ܣ���ȡ�������Բ����ж�����
        if( query("ultraquest/fail", who) )
        {
                delete_temp("dest_npc", who);
                destruct(me); // ������������
                return;
        }

        // ��������»��͵���������ˣ�ִ�����³���
        if (! objectp(me) || ! objectp(who)) return;

        // ���ó����͵�Ŀ�ĵ�
        place=query("ultraquest/quest/obj", who);

        if (environment(me) != environment(who))
        {
                switch(query_temp("dest_npc", who) )
                {
                case 0:
                        msg = "���ͷ�����䣬ȴ������" + me->name()
                              + "����֪��ʱ��������Ӱ��\n�����а���"
                              "����ǧ����������ϵ��ˣ��øϽ�������"
                              "������";
                        break;

                case 1:
                        msg = "��������Ϊ�������ף�" + me->name()
                              + "�Ǽһﵽ������ȥ�ˡ�";
                        break;

                case 2:
                        msg = "���ĵ�ֱ�ʲôʱ���ˣ��Ǹ�����" +
                              me->name() + "��ô������������";
                        break;

                default:
                        msg = "����������̾Ϣ���������׻��ǰ��˸�"
                              "�����ˡ�������������";

                        // ��¼��ʧ�ܼ�¼
                        set("ultraquest/fail", 1, who);
                        break;
                }

                // �������ﶪʧ��ʱ��Σ��������������ж�
                addn_temp("dest_npc", 1, who);

                // ��һ��ʱ�����������ɨ��
                who->start_call_out((: call_other, __FILE__, "check_going",
                                    me, who :), 5);

                tell_object(who, HIG "\n" + msg + "\n\n" NOR);
                return;
        }

        // ����Ⱥ��������ʱ���
        if( query_temp("dest_npc", who) )
                delete_temp("dest_npc", who);


        // �鿴��ǰλ�ã���ΪĿ�ĵأ����������
        if( query("short", environment(me)) == query("ultraquest/quest/obj", who) )
        {
                // ����������˻��ԣ�����ת��
                if (! living(me))
                        me->revive();

                message_vision(CYN "$N" CYN "���˲�������$n" CYN "����лл"
                               "�㽫���͵�" + place + "��·�������鷳���ˡ�"
                               "\n$N" CYN "���ŵ����������ⷬ����ķ��ϣ���"
                               "�͸�����һЩ�����ɡ�\n" NOR, me, who);

                // Ŀ��ȡ��������������
                delete_temp("start_guard", me);

                // Ŀ�겻�ٸ���
                me->set_leader(0);

                // ������ɣ�ע�ά������
                // set("ultraquest/name1", me->name(), who);
                set("ultraquest/gift/point", 220, who);
                set("ultraquest/gift/msg","��ͨ������"+
                                                 query("ultraquest/quest/name", who)+"�ִ�"+
                                                 place + "�Ĺ���", who);

                // ϵͳ����ô�����Ľ���
                give_gift(me, who);
                return;
        } else
        {
                string last_place;

                // ����¼�ʹ����ϵ͵Ļ���Ŀ��ͣ��
                if( stringp(last_place=query_temp("last_place", me) )
                     && last_place != query("short", environment(me) )
                    && ! me->is_busy()
                     && query("combat_exp", me)<2000000
                    && random(50) == 1)
                {
                        switch (random(5))
                        {
                        case 0:
                                msg = "ͻȻ��$N" HIW "�ܵü��ˣ�һ���"
                                      "�Ե�·�ߣ�����ѽѽ�и���ͣ��";
                                break;

                        case 1:
                                msg = "ֻ��$N" HIW "��Ϣ����" + who->name()
                                      + HIW "�������㡭�������������ˡ�";
                                break;

                        case 2:
                                msg = "$N" HIW "���ס���һ�����ƺ�������"
                                      "ʲô��������Ų���ʱ����������";
                                break;

                        case 3:
                                msg = "$N" HIW "��Ȼ��ɫ�Ұף�����" +
                                      who->name() + HIW "���ͷ�ͣ��ͣһ"
                                      "�ᣬ���߲����ˡ�";
                                break;

                        default:
                                msg = "ȴ��$N" HIW "������䣬�ߵ���·��"
                                      "͹���һ���ʯ��ֱʹ�ù�����ȥ��";
                                break;
                        }
                        message_vision(HIW "\n" + msg + "\n\n" NOR, me, who);
                        me->start_busy(2 + random(2));
                }

                // �趨��һ��������ĵص㣬����뵱ǰ�ص㲻ͬ����
                // ִ����������ͣ���ĳ���
                set_temp("last_place",query("short",  environment(me)), me);

                // δ����Ŀ�ĵأ���ʱ������ɨ��
                who->start_call_out((: call_other, __FILE__, "check_going",
                                    me, who :), 1);
                return;
        }
        return;
}

// ���������������ļ�������������
int need_accede(object me, object who)
{
        string skill, ma, wa;
        string suc_msg, fai_msg, msg;
        int lvl;

        // ׼���Ƚϵļ�������
        skill=query("ultraquest/quest/type", who);
       lvl=query_temp("need_accede/lvl", me);

        // ���˳����򵥻�
        ma = RANK_D->query_self(me);
        wa = RANK_D->query_respect(who);

        switch (skill)
        {
        case "mathematics" :
                suc_msg = me->name() + "���˵�ͷ���漴�����������ڵ��滭"
                          "��Щ��ֱ������ԲȦ������д�¡�̫����Ԫ����Ԫ��"
                          "��Ԫ����Ԫ�����֡�����һ��ĬĬϸ�ۣ���ָ�����"
                          "����������Ĵ��������ڸ�֮" + me->name() +
                          "��" + me->name() + "����һ����̾������ԭ��Ϊ��"
                          "�������ˣ����ˡ�";

                fai_msg = me->name() + "���˵�ͷ���漴�����������ڵ��滭"
                          "��Щ��ֱ������ԲȦ������д�¡�̫����Ԫ����Ԫ��"
                          "��Ԫ����Ԫ�����֡�����һ�Կ��ò�֪���ƣ�ȫȻ��"
                          "֪��������֡�" + me->name() + "���˰��죬����"
                          "���޶��������ɵ������һЦ��";
                break;

        case "literate" :
                suc_msg = me->name() + "���˵�ͷ��������ɤ�ӵ����ҳ�һ��"
                          "����������ҶԳ��������������ǡ��׻�Ӣ��ʷ����"
                          "��΢΢һЦ����ڶԵ���������ɵ��Ĺ����" +
                          me->name() + "����һ���޵���������˾��";

                fai_msg = me->name() + "���˵�ͷ��������ɤ�ӵ����ҳ�һ��"
                          "����������ҶԳ����������������ǡ���̶Ӣ��ʷ��"
                          "��������һ㶣������˰���ŵ��������������ƻ���"
                          "����" + me->name() + "�����ŭ����������ޣ���"
                          "��ʲô���ӡ����֪���ƶԺ�ô��";
                break;

        case "chess" :
                suc_msg = "�㵱������ǰȥ����" + me->name() + "�ڿ����"
                          "����������������ʱ��ȴ��" + me->name() + "��"
                          "�Ǵ����졣��������������һ�ӣ�" + me->name() +
                          "��ʱ��ɫ���࣬��Ȼ���������ˣ������ˡ�������"
                          "���ǡ�";

                fai_msg = "�㵱������ǰȥ����" + me->name() + "�ڿ����"
                          "����������������ʱ�����ѱ�" + me->name() +
                          "�Ƶýڽڰ��ˣ����������" + me->name() + "��"
                          "����ɫ���࣬��Ц������ô��������ˮƽ��������"
                          "��ô��";
                break;

        case "calligraphy" :
                suc_msg = "��΢΢һЦ����������ǰȥ���ӹ�ë�ʱ㿪ʼ��д"
                          "��������ʱֻ��������������б�ī��������"
                          "�����������ּ�����������ˮ�����潫�鷨���⾳"
                          "���ӵ����쾡�¡�" + me->name() + "��һ�Կ���"
                          "Ŀ�ɿڴ����������ޡ�";

                fai_msg = "�㵱������ǰȥ���ӹ�ë�ʱ�մīˮ���㿪ʼ��д"
                          "������������д�������緢֮����̧ͷ��ȴ����" +
                           me->name() + "��ɫ��Ϊ�ѿ������ɵ�΢΢һ㶡�" +
                           me->name() + "ҡ��ҡͷ��ʧ�����������ҽ�������"
                           "���ó��֣�������˳�Ц��ԭ����������";
                break;

        case "drawing" :
                suc_msg = "��΢΢һЦ�������ӹ����ʣ����������ī������"
                          "��ī�����죬�����۽�����ֻ�������ʣ����ƿ���"
                          "ʵ������" + me->name() + "��һ��Խ��Խ����ϲ"
                          "���������ޡ�";

                fai_msg = "�㵱������ǰȥ���ӹ������������������㻭��"
                          "�����緢֮ʱ��̧ͷ��ȴ����" + me->name() + "��"
                          "ɫ��Ϊ�ѿ������ɵ�΢΢һ㶡�" + me->name() +
                          "ҡ��ҡͷ��ʧ���������ˣ����ˡ�������ˮƽ����"
                          "û���Լ����ֻ��׵���";
                break;

        default:
                suc_msg = "����˵�ͷ�������ָ����" + me->name() + "��"
                          "���ϣ�����Ƭ�̱��ѷ����䲡�����ڡ�����Ҳ����"
                          "�飬���������ҩ����" + me->name() + "�����"
                          "ϲ�������ҽ���������" + wa + "���˷���������"
                          "���Իر���";

                fai_msg = "�����㶣�����ǰȥ��" + me->name() + "������"
                          "̽�˰��죬ȴ����" + me->name() + "�����쳣��"
                          "�ң�Զ���Լ���ʶ��" + me->name() + "�����ü"
                          "��չ�����ɵó�̾�������������˱���һ��ӹҽ��"
                          "�Σ�Ҳ����Ϊ���ˡ�";
                break;
        }

        message("vision", "ֻ��" + who->name() + "����ǰȥ����" +
                          me->name() + "�����ֹ��˼��䡣\n",
                          environment(who), ({ who }));

        // ע��������������������
        delete_temp("need_accede", me);

        if (who->query_skill(skill, 1) >= lvl)
        {
                // �ύ�ɹ���������Ϣ
                tell_object(who, sort_msg(WHT + suc_msg + "\n\n" NOR));

                // ������ɣ�ע�ά������
                // set("ultraquest/name1", me->name(), who);
                set("ultraquest/gift/point", 350, who);
                set("ultraquest/gift/msg","��ͨ���˷�����"+
                                                 me->name() + "�ľ���", who);

                if (! who->is_busy())
                        who->start_busy(3);

                // ������轱����Ʒ
                if (random(5) == 1)
                {
                        message_vision(CYN "$N" CYN "����" + wa + "��Ϊ��"
                                       "ʵ��" + ma + "�۷����ѡ�һ�㱡��"
                                       "���ɾ��⡣\n" NOR, me);

                        set("ultraquest/gift/item", 1, who);
                }

                // ϵͳ����ô�����Ľ���
                give_gift(me, who);
        } else
        {
                // �ύʧ�ܵ�������Ϣ
                tell_object(who, sort_msg(WHT + fai_msg + "\n\n" NOR));

                message_vision(CYN "$N" CYN "ҡ��ҡͷ����$n"
                               CYN "����Ҳ�գ��һ������½���"
                               "�������������ɡ�\n" NOR, me, who);

                // �����жϣ�ϵͳ���·��������
                give_quest(me, who);
        }

        return 1;
}

// ���������������Ʒ
int accept_object(object me, object who, object ob)
{
        string msg;
        string type;
        int ultra_count;
        int exp;                // ��õľ���
        int pot;                // ��õ�Ǳ��
        int mar;                // ��õ�ʵս���
        int weiwang;            // ��õ�����
        int score;              // ��õĽ�������
        int lvl;                // ����ĵȼ�
        mixed special = 0;      // �Ƿ������⽱��
        object ob1, rob;

        // ���û����ȡ����
        if( !mapp(query("ultraquest", who)) )
                return 0;

        if( query("name", me) == QUESTER )
        {
                if( query("ultraquest/finish", who) < 5 )
                        return 0;
                
                switch(query("ultraquest/type", who) )
                {
                case "find":
                        if( query("id", ob) != query("ultraquest/id", who) )
                                return 0;

                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "��΢΢�ĵ��˵�ͷ��\n" NOR, me);
                        // destruct(ob);
                        break;

                case "give":
                case "rescue":
                        if (! ob->is_receipt())
                                return 0;

                        if( query("reply_to", ob) != query("name", me )
                         || query("reply_by", ob) != query("ultraquest/id", who )
                         || query("receive_from_name", ob) != who->name(1) )
                        {
                                message_vision("$N��ü���������������ո�ʲô����\n", me);
                                return 0;
                        }

                        message_vision(CYN "$N" CYN "�ӹ�" + ob->name() + NOR + CYN
                                       "����ϸ���˿��������˵���ܺá�\n" NOR, me);
                        // destruct(ob);
                        break;

                case "kill":
                        if(! ob->is_corpse() && ! ob->is_head())
                                return 0;

                        if( !stringp(query("owner_id", ob)) )
                        {
                                message_vision(CYN "$N" CYN "���ű��ӿ��˿�" + ob->name()
                                               + NOR + CYN "������ʲô�����ģ������"
                                               "���ߡ�\n" NOR, me);
                                return 0;
                        }

                        if( query("killed_by", ob) != query("id", who) )
                                return 0;

                        if( query("victim_name", ob) != query("ultraquest/name", who) )
                                return 0;

                        // message_vision(CYN "$N" CYN "���˿�" + ob->name()
                        //                + NOR + CYN "��΢΢�ĵ��˵�ͷ��\n" NOR, me);
                        // destruct(ob);
                        break;
                }

                msg = CYN "$N" CYN "�ӹ�" + ob->name() + NOR + CYN"����ϸ����"
                      "���������˵���ܺá�\n" NOR;

                // ����Ҫ�������������
                addn("ultra_count", 1, who);

                ultra_count=query("ultra_count", who);

                lvl = NPC_D->check_level(who);
                exp = 6000 + random(1000) + lvl * 10;
                pot = 1200 + random(200) + lvl * 10;
                mar = 120 + random(50);
                weiwang = 20 + random(30);
                score = 20 + random(30);

                // ����������ɵĴ�����������
                if (ultra_count >= 100)
                {
                        // ��������˳���100�ε�����
                        exp += 800 + random(ultra_count + 1);
                        pot += 450 + random(ultra_count + 1);
                        mar += 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                } else
                if (ultra_count >= 50)
                {
                        // ��������˳���50�ε�����
                        exp += 700 + random(ultra_count + 1);
                        pot += 400 + random(ultra_count + 1);
                        mar += 40 + random(10);
                        weiwang += 5 + random(15);
                        score += 3 + random(10);
                } else
                if (ultra_count >= 25)
                {
                        // ��������˳���25�ε�����
                        exp += 500 + random(ultra_count + 1);
                        pot += 300 + random(ultra_count + 1);
                        mar += 30 + random(5);
                        weiwang += 3 + random(10);
                        score += 2 + random(10);
                } else
                if (ultra_count >= 10)
                {
                        // ��������˳���10�ε�����
                        exp += 450 + random(ultra_count + 1);
                        pot += 250 + random(ultra_count + 1);
                        weiwang += 1 + random(5);
                        score += 1 + random(5);
                }

                if (ultra_count == 10)
                {
                        msg += CYN "$N" CYN "������Ц����������������ģ�������ʮ"
                               "��������ɵ�ƯƯ�������ܺã��ܺá���\n" NOR;
                        special = 1;
                } else
                if (ultra_count == 25)
                {
                        msg += CYN "$N" CYN "��ϲ��������������ʵ������ʮ��"
                               "������ɵúܺá���\n NOR";
                        special = "/clone/gift/jiuzhuan";
                } else
                if (ultra_count == 50)
                {
                        msg += CYN "$N" CYN "̾���������ǳ���������ǰ�ˣ��벻���������ʮ"
                               "��������һ��©�����ף����ף���\n" NOR;
                        special = "/clone/gift/tianxiang";
                } else
                if (ultra_count >= 100)
                {
                        msg += CYN "$N" CYN "����̾�˿������������벻���������ϰٴ�"
                               "������һʧ�֣�����������̶���Ǻ�����˰�����\n" NOR;
                        special = "/clone/gift/xuanhuang";
                        ultra_count = 0;
                } else
                if ((ultra_count % 10) == 0)
                {
                        msg += CYN "$N" CYN "ϲ���������ǲ�������Ȼ����" +
                               chinese_number(ultra_count) +
                               "�ζ�û��ʧ�֣��ɵĺã���\n" NOR ;
                }

                if (stringp(special))
                {
                        ob1 = new(special);
                        ob1->move(who, 1);
                        tell_object(who,HIM"������һ"+query("unit", ob1)+ob1->name()+
                                         HIM "��\n" NOR);
                }

                message_vision(msg, me, who);
                if ((ultra_count >= 10 && random(200) == 1) || special)
                        special_bonus(me, who);

                // ������ͼ���15-21
                if( query("quest_tuteng/start", who) )
                {
                        int n_tt;
                        object ob_tt;

                        if (random(3000) == 1)
                        {
                                n_tt = 15 + random(7);
                                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                                if (ob_tt)
                                {
                                        ob_tt->move(who, 1);
                                        tell_object(who, HIG "������һ�ŵ�����ͼ��Ƭ��\n" NOR);
                                }
                        }
                }

                set("ultra_count", ultra_count, who);
                delete("ultraquest", who);

                GIFT_D->delay_bonus(who, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);
                destruct(ob);
                return 1;
        }

        // ֻ��ɱ�ˡ�Ѱ�����/�����������ִ����Ʒ����
        if( !stringp(type=query("ultraquest/quest/type", who) )
            || (type != "kill" && type != "find"
            && type != "give" && type != "send"))
                return 0;

        // �������Ϊ�����ż��������NPC
        if( query("id", me) == query("ultraquest/quest/id", who) )
        {
                switch (type)
                {
                case "send" :
                        if (! ob->is_letter())
                                return 0;

                        if( query("send/send", ob) != me->name() )
                        {
                                message_vision(CYN "$N" CYN "��ü�����������ô����"
                                               "�����ֲ���д���ҵġ�\n" NOR, me);
                                return 0;
                        }

                        if( query("send/user", ob) != who->name() )
                        {
                                message_vision(CYN "$N" CYN "��ü����������˭������"
                                               "�ģ�����ô����ʶ��\n" NOR, me);
                                return 0;
                        }

                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);

                        rob = new("/clone/misc/receipt");
                        set("reply_by",query("name",  me), rob);
                        set("reply_to",query("send/from",  ob), rob);
                        set("receive_from",query("id",  who), rob);
                        set("long", "����һ����"+me->name()+"�յ�������д�Ļ�ִ��\n", rob);
                        rob->move(who, 1);
                        message_vision("$N����$nһ�Ż�ִ��\n", me, who);
                        destruct(ob);

                        break;

                case "give" :
                        if (! ob->is_bag())
                                return 0;

                        if( query("send/send", ob) != me->name() )
                        {
                                message_vision(CYN "$N" CYN "��ü�����������ô����"
                                               "�����ֲ����ø��ҵġ�\n" NOR, me);
                                return 0;
                        }

                        if( query("send/user", ob) != who->name() )
                        {
                                message_vision(CYN "$N" CYN "��ü�����������˭����"
                                               "�ģ��������Լ����Űɡ�\n" NOR, me);
                                return 0;
                        }

                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);
                        rob = new("/clone/misc/receipt");
                        set("reply_by",query("name",  me), rob);
                        set("reply_to",query("send/from",  ob), rob);
                        set("receive_from",query("id",  who), rob);
                        set("long", "����һ����"+me->name()+"�յ��İ���д�Ļ�ִ��\n", rob);
                        rob->move(who, 1);
                        message_vision("$N����$nһ�Ż�ִ��\n", me, who);
                        destruct(ob);
                        break;
                }

                me->destruct_me(); // ���ٽ�����Ʒ����NPC
                return 1;
        }

        // �������Ϊ���������NPC
        if( query("id", me) == query("ultraquest/id", who) )
        {
                switch (type)
                {
                case "kill":
                        if(! ob->is_corpse() && ! ob->is_head())
                                return 0;

                        if( !stringp(query("owner_id", ob)) )
                        {
                                message_vision(CYN "$N" CYN "���ű��ӿ��˿�" + ob->name()
                                               + NOR + CYN "������ʲô�����ģ������"
                                               "���ߡ�\n" NOR, me);
                                return 0;
                        }

                        if( query("killed_by", ob) != query("id", who) )
                                return 0;

                        if( query("victim_name", ob) != query("ultraquest/quest/name", who) )
                                return 0;

                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);
                        // destruct(ob);
                        break;

                case "find" :
                        if( query("id", ob) != query("ultraquest/quest/id", who) )
                                return 0;

                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);
                        // destruct(ob);
                        break;

                case "send" :
                        if (! ob->is_receipt())  return 0;
                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);

                        if (ob->is_receipt())
                        {
                                if( query("reply_to", ob) != query("name", me) )
                                {
                                        message_vision("$N��ü���������������ո�ʲô����\n", me);
                                        return 0;
                                }

                                if( query("receive_from", ob) != query("id", who) ||
                                    query("reply_by", ob) != query("ultraquest/quest/name", who) )
                                {
                                        message_vision("$N��ü����������������͵��𣿡�\n", me);
                                        return 0;
                                }
                                // destruct(ob);
                        }

                        break;

                case "give" :
                        if (! ob->is_receipt())  return 0;
                        message_vision(CYN "$N" CYN "���˿�" + ob->name()
                                       + NOR + CYN "�����ÿɷ�ĵ��˵�ͷ��\n" NOR, me);
                        if (ob->is_receipt())
                        {
                                if( query("reply_to", ob) != query("name", me) )
                                {
                                        message_vision("$N��ü���������������ո�ʲô����\n", me);
                                        return 0;
                                }

                                if( query("receive_from", ob) != query("id", who) ||
                                    query("reply_by", ob) != query("ultraquest/quest/name", who) )
                                {
                                        message_vision("$N��ü����������������͵��𣿡�\n", me);
                                        return 0;
                                }
                                // destruct(ob);
                        }
                        break;
                }

                destruct(ob);
                set("ultraquest/gift/point", 600, who);
                set("ultraquest/gift/msg","��ͨ���˷�����"+
                                                 me->name() + "�ľ���", who);
                give_gift(me, who);

                return 1;
        }
}

// �������Ľ���
public void give_gift(object me, object who)
{
        int gift;

        // ���û��ע�ά�����������ж�
        if( !query("ultraquest/gift/msg", who )
                 || !query("ultraquest/gift/point", who) )
                return;

        // ����������ɵ�����
        addn("ultraquest/finish", 1, who);

        // ������Ʒ����
        if( query("ultraquest/gift/item", who) )
                special_bonus(me, who);

        // �����ĵ���
        gift=query("ultraquest/gift/point", who)+
                query("ultraquest/finish", who);

        GIFT_D->delay_bonus(who,(["prompt":query("ultraquest/gift/msg", who),
                                         "exp"     : gift,
                                         "pot"     : gift / 5,
                                         "mar"     : gift / 30,
                                         "score"   : gift / 40,
                                         "weiwang" : gift / 50, ]));

        // ȡ����ԭ������������
        delete("ultraquest/gift", who);
        delete("ultraquest/quest", who);

        // �ṩ�µ��������Ա���������
        generate_information(me, who);
        return;
}

// �������ṩ��������Ϣ
public void generate_information(object me, object who)
{
        object ob;
        string where, id, name, place;
        string msg, ma, next_name;
        int finish;

        // û����һ���ṩ��������
        if (! objectp(me)) return;

        // �����������������뱾������Ķ���
        if( query("ultraquest/finish", who) == 5 )
        {
                switch(query("ultraquest/type", who) )
                {
                case "kill":
                        ob = new(CLASS_D("generate") + "/killer.c");
                        NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�", "����" }));
                        NPC_D->set_from_me(ob, me, 150);
                        addn_temp("apply/attack", ob->query_skill("force")*1/2, ob);
                        addn_temp("apply/dodge", ob->query_skill("force")*1/2, ob);
                        addn_temp("apply/parry", ob->query_skill("force")*1/2, ob);
                        addn_temp("apply/damage", 1000, ob);
                        addn_temp("apply/unarmed_damage", 1000, ob);
                        addn_temp("apply/armor", 1000, ob);
                        set_temp("quester",query("id",  who), ob);

                        set("ultraquest/id",query("id",  ob), who);
                        set("ultraquest/name",query("name",  ob), who);

                        NPC_D->random_move(ob);
                        NPC_D->random_move(ob);
                        NPC_D->random_move(ob);

                        place=query("place", ob);

                        tell_object(who, CYN + me->name() + CYN "С������˵����"
                                        NOR+HIR+ob->name()+"("+query("id", ob)+")"+NOR+CYN
                                        "����Ļ�����ˣ���ǧ��Ҫ˵����˵��\n��˵�������" + place + "�����ȥ�ɣ�\n" NOR);
                        break;
                case "send":  // ��������ʱû�п���
                        break;
                case "rescue":
                        break;
                case "find":
                        break;
                }
                me->destruct_me(); // �����ϴ���������
                return;
        }

        ob = new(CLASS_D("generate") + "/cluenpc.c");
        NPC_D->place_npc(ob, ({ "����һ��", "����ɽ", "����", "������", "���ݳ�" }));
        NPC_D->set_from_me(ob, me, 100);
        addn_temp("apply/attack", ob->query_skill("force")*1/2, ob);
        addn_temp("apply/dodge", ob->query_skill("force")*1/2, ob);
        addn_temp("apply/parry", ob->query_skill("force")*1/2, ob);
        addn_temp("apply/damage", 500, ob);
        addn_temp("apply/unarmed_damage", 500, ob);
        addn_temp("apply/armor", 500, ob);
        set_temp("quester",query("id",  who), ob);

        NPC_D->random_move(ob);

        id=query("id", ob);
        name=query("name", ob);
        place=query("place", ob);

        // ��¼����һ���������Ｐ���ֵ�
        set("ultraquest/id", id, who);
        set("ultraquest/name", name, who);
        set("ultraquest/place", place, who);

        // ����ϴε�������Ϣ
        delete("ultraquest/quest", who);

        // �����Ŀ����ɫ
        next_name = HIY + name + "(" + id + ")" + NOR + WHT;

        // ���˳����򵥻�
        ma = RANK_D->query_respect(me);

        // ���������������
        finish=query("ultraquest/finish", who);
        switch (finish)
        {
        case 1:
                msg = "��˵�����Ļ���������ʧ��һ����Ҫ��Ʒ��ͨ�������Ʒ����֪"
                      "������˭��\n����" + place + "��" + next_name + "��֪����"
                      "����Ʒ�����䡣\n" + ma + "��ȥ�������ʣ���Ҳ��֪�����Ǽ�";
                break;

        case 2:
                msg = "����Ʒ�ҵ�����˵��������" + ma + "֪��" + place + "��\n"
                      "�����и�" + next_name + "��������Ҫ�ҵ��Ƕ�������������";
                break;

        case 3:
                msg = "��֪" + ma + "��ʶ" + place + "��" + next_name + "��\n"
                      "�������治�ɣ��Ǹ��������ϸ����͸����ˣ��������������";
                break;

        case 4:
                msg = "���ź�����Ҫ�Ķ�����ǰ����㶪�ˣ������" + ma + "�Ƿ���ʶ"
                      + place + "��" + next_name + "��\n�������˶��������Һ���֪"
                      "���Ǹ���Ʒ��������˭";
                break;

        default:
                msg = "�����롭" + ma + "ȥ��" + place +
                      "��" + next_name + "���ʿ��ɡ�\nȥ������"
                      "��˵��������";
                break;
        }

        // ��ʼ����������������ˢ������
        if (me->name() == QUESTER)
        {
                if( query("ultraquest/ask", who) )
                        msg = "���š���ȥ" + place +
                              "����" + next_name + "�������Ƕ�"
                              "�ƺ�����Щ����";
                else
                        msg = "�����ȥ" + place +
                              "��" + next_name + "������������"
                              "���ƺ���Щ����";
        }

        // ����ֻҪ��Ǯ�ͺ�˵��
        if (me->name() == LURCHER)
        {
                switch (random(3))
                {
                case 0:
                        msg = "���ٺ١���ȥ" + place +
                              "��䣬�Ƕ��и�" + next_name +
                              "��������ɶ��֪��";
                        break;

                case 1:
                        msg = "�������ɡ���ȥ��" + next_name +
                              "���ʿ����Ǽһ����" + place +
                              "���ɱ��߶���";
                        break;

                default:
                        msg = "�㵽" + place + "�����"
                              "������" + next_name + "���ˣ�˵"
                              "�������ٺ١�����ɶ�ջ�";
                        break;
                }
        }

        // �ṩ��������Ϣ
        message("vision", me->name() + "������" + who->name() + "��"
                "��˵��Щʲô��\n", environment(who),
                ({ me, who }));

        // �ṩ�������������Ϣ
        msg = WHT + me->name() + WHT "���Ķ���˵����" + msg + "��\n" NOR;

        // tell_object(who, sort_msg(msg));
        tell_object(who, msg);
        if (me->name() != QUESTER && me->name() != LURCHER)
                me->destruct_me(); // �����ϴ���������

        return;
}
