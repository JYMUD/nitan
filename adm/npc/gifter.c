// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;

int get_reward();
mixed ask_gift();
mixed ask_gift1();
mixed ask_gift2();
mixed ask_gift3();
mixed ask_gift4();
mixed ask_gift5();
mixed ask_gift6();

void create()
{
        set_name(HIM "������ʹ" NOR, ({ "gift angel", "tianshi", "gift", "angel", "liwu" }));
        set("long", @LONG
������ʹ��������̶�����ڼ����﷢�ŵ���ʹ��
LONG);
        set("gender", "Ů��" );
        set("age", 18);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 1200000);

        set("inquiry", ([
                "��������" : (: get_reward :),
                "����" : (: get_reward :),
/*
                "gift" : (: ask_gift :),
                // "��������" : (: ask_gift1 :),
                // "��Ա����" : (: ask_gift2 :),
                // "Ԫ������" : (: ask_gift3 :),
                "��������" : (: ask_gift4 :),
                // "������������" : (: ask_gift5 :),
                // "���˸���" : (: ask_gift6 :),
*/
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}

int get_reward()
{
        object me;
        string ret;
    
        me = this_player();
        ret = FESTIVAL_D->get_reward(me);
        tell_object(me, ret);
        return 1;
}      

mixed ask_gift()
{
        object ob, me = this_player();
        string *lines;
        string file, gift;
        int time1, time2;

        file = read_file(CONFIG_DIR + "gift");
        if (! stringp(file))
        {
                command("say ��ϧ������û�д��������������أ�");
                return 1;
        }

        lines = explode(file, "\n");
        file = lines[sizeof(lines) -1];

        if (sscanf(file, "%s %d to %d", gift, time1, time2) != 3)
        {
                command("say ��֣�������ô�����ˣ��ѵ������������֣���");
                return 1;
        }

        if( query("gifter/"+time1, me) )
        {
                command("say �Ǻǡ���������Ĳ����ˣ����Ѿ������������˰���");
                return 1;
        }

        if (time() < time1 || time() > time2)
        {
                command("say �Բ��������Ĳ���ʱ������������������ͷ��ҵģ�");
                return 1;
        }

        if (! ob = new(gift))
        {
                 command("say ��֣������д����⣬��Ͽ�����񱨸�ɣ�");
                 return 1;
        } else
        {
                set("gifter/"+time1, 1, me);
                ob->move(me, 1);

                message_vision(HIW "$N" HIW "���һָ��ͻȻ�����һ��" HIM "��" HIY "��" HIR "ϼ" HIC "��" HIW "����$n��ת˲���ţ�\n" NOR,
                               this_object(), me);

                tell_object(me, HIG "�����Ϻ������һ�����gift������쿴����ʲô����ɡ�\n" NOR);
                return 1;
        }
}

mixed ask_gift1()
{
        int td;
        object ob;
        object me = this_player();

        td = time() / 86400;

        if( query("gifter/which_day", me) == td )
                return "������Ѿ���������ˡ�";

        tell_object(me, HIY "\n����ȡ��һ�����������(" HIM "��ʦ�����" NOR + HIY ")��ף�������߹����������죡\n" NOR);

        ob = new("/clone/goods/tianshi-charm");
        ob->move(me, 1);
        set("bindable", 3, ob);
        set("bind_owner",query("id",  me), ob);
        set("autoload", 1, ob);
        set("setdbase", 1, ob);
        set("gifter/which_day", td, me);
        return 1;
}

mixed ask_gift2()
{
        string id, sql;
        int    jointime, endtime, day;
        object me = this_player();


        if( query("gifter/monfee1", me) )
                return "���Ѿ��������Ա�ˡ�";

        id=query("id", me);

        if (! MEMBER_D->is_member(id))
        {
                day = time() + 2678400;
                sql = sprintf("INSERT INTO %s SET id = \"%s\", jointime = %d, endtime = %d",
                              "members", id, time(), day);
                DATABASE_D->db_query(sql);
        } else
        {
                jointime = (int)MEMBER_D->db_query_member(id, "jointime");
                if (jointime < 1) jointime = time();

                endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
                if (endtime < 1) day = time() + 2678400;
                else day = endtime + 2678400;

                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }

        set("gifter/monfee1", 1, me);

        tell_object(me, HIY "\n����ȡ��һ���µ�(" HIM "��Ա����" NOR + HIY ")��ף�������߹����������죡\n" NOR);

        return 1;
}

mixed ask_gift3()
{
        object me = this_player();


        if( query("gifter/20081224", me) )
                return "���Ѿ����Ԫ�������ˣ���Ҫ̫̰�ġ�:)";

        if (! MEMBER_D->is_valid_member(me))
        {
                addn("combat_exp", 2000000, me);
                addn("potential", 3000000, me);
                addn("experience", 8000000, me);
                addn("time_reward/quest", 86400, me);
        } else
        {
                addn("combat_exp", 10000000, me);
                addn("potential", 6000000, me);
                addn("experience", 3000000, me);
                addn("balance", 500000000, me);
                addn("time_reward/quest", 172800, me);
        }

        set("gifter/20081224", 1, me);

        tell_object(me, HIY "\n���ͻ��һ�������ҫ���㣬��ڤڤ�ио�����2009�꽫��������������\n" NOR);

        return 1;
}

mixed ask_gift4()
{
        string mapsk;
        object me = this_player();


        if( query("gifter/20120120", me) )
                return "���Ѿ�������������ˣ���Ҫ̫̰�ġ�:)";

        addn("combat_exp", 2000000, me);
        addn("potential", 1000000, me);

        if (MEMBER_D->is_valid_member(me))
        {
                mapsk = me->query_skill_mapped("force");
                        me->improve_skill("force", 200000);
                        me->improve_skill("force", 200000);
                        me->improve_skill("force", 200000);
                        me->improve_skill("force", 200000);
                if (stringp(mapsk))
                {
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                }

                mapsk = me->query_skill_mapped("parry");
                        me->improve_skill("parry", 200000);
                        me->improve_skill("parry", 200000);
                        me->improve_skill("parry", 200000);
                        me->improve_skill("parry", 200000);
                if (stringp(mapsk))
                {
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                }

                mapsk = me->query_skill_mapped("dodge");
                        me->improve_skill("dodge", 200000);
                        me->improve_skill("dodge", 200000);
                        me->improve_skill("dodge", 200000);
                        me->improve_skill("dodge", 200000);
                if (stringp(mapsk))
                {
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                        me->improve_skill(mapsk, 200000);
                }

                addn("balance", 20000000000, me);
        }

        set("gifter/20120120", 1, me);

                tell_object(me,
HIW"\n"+
"     ������������������ "HIR"���ڿ���"HIW" ������������������\n"+
"     ��  ���������� Happy  New  Year ����������  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��                                  ��  ��\n");
                if( strlen(query("name", me)) == 2)tell_object(me,
HIW"�����װ���"+query("name", me)+"������\n");
                if( strlen(query("name", me)) == 4)tell_object(me,
HIW"�����װ���"+query("name", me)+"������\n");
                if( strlen(query("name", me)) == 6)tell_object(me,
HIW"�����װ���"+query("name", me)+"������\n");
                if( strlen(query("name", me)) == 8)tell_object(me,
HIW"�����װ���"+query("name", me)+"������\n");
                if( strlen(query("name", me)) == 10)tell_object(me,
HIW"�����װ���"+query("name", me)+"������\n");
        tell_object(me,
HIW"     ��  ��      Ը�������ļ������µ�һ��    ��  ��\n"+
"     ��  ��  ����������֡�ƽ����          ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��             *  *"HIR"r"HIW"*  *            ��  ��\n"+
"     ��  ��          * *"HIR"a"HIW"* "HIG"^"HIY"Y"HIG"^"HIW" *"HIR"i"HIW"* *         ��  ��\n"+
"     ��  ��         *"HIM"m"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"HIG"^\\^"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"RED"s"HIW"*        ��  ��\n"+
"     ��  ��         "HIG"^"HIY"Y"HIG"^"HIW"*"HIG"\\"HIW"*"RED"e"HIW"*"HIG"/"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"        ��  ��\n"+
"     ��  ��         *"HIG"\\"HIW"*"CYN"t"HIW"*"HIG"|"HIY"Y"HIG"^\\^"HIY"Y"HIG"|"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*        ��  ��\n"+
"     ��  ��        *"MAG"s"HIW"*"HIG"|"HIY"Y"HIG"^\\\\^/^//^"HIY"Y"HIG"|"HIW"*"HIR"a"HIW"*       ��  ��\n"+
"     ��  ��        "GRN"^"YEL"Y"GRN"^\\\\_^\\\\\\//^_//^"YEL"Y"GRN"^"HIW"       ��  ��\n"+
"     ��  ��        "GRN"^\\_^\\_\\_\\//_/_/^_/^"HIW"       ��  ��\n"+
"     ��  ��         "GRN"^^\\_^\\_\\\\/_/^_/^^"HIW"        ��  ��\n"+
"     ��  ��           "GRN"^^\\_ \\// _/^^"HIW"          ��  ��\n"+
"     ��  ��               "GRN"\\_\\_/"HIW"              ��  ��\n"+
"     ��  ��                "GRN"/|\\"HIW"               ��  ��\n"+
"     ��  ��               "GRN"/\\\\/\\"HIW"              ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��                  "RED"��̶��ʦ�鹧��"HIW"  ��  ��\n"+
HIW"     ��  ��������������������������������������  ��\n"+
"     ����������������������������������������������\n"+
"\n" NOR);

        return 1;
}

mixed ask_gift5()
{
        object me = this_player();

        if( query("gifter/20090121", me) )
                return "���Ѿ�����������������ˣ���Ҫ̫̰�ġ�:)";

        if (! MEMBER_D->is_valid_member(me))
                addn("time_reward/quest", 259200, me);
        else
                addn("time_reward/quest", 518400, me);

        set("gifter/20090121", 1, me);
        tell_object(me, HIY "\n����ȡ�˴����������ף��������֣�\n" NOR);

        return 1;
}

mixed ask_gift6()
{
        object me = this_player();
        if( query("gifter/20090701", me) )
                return "���Ѿ�������˸����ˣ���Ҫ̫̰�ġ�:)";

        addn("max_neili", 100000, me);
        addn("max_jingli", 100000, me);
        set("gifter/20090701", 1, me);
        tell_object(me, HIY "\n����ȡ�����˸�����ף�������죡\n" NOR);
        return 1;
}
