// This program is a part of NITAN MudLIB
// Buddha.c

#include <ansi.h>
inherit NPC;
inherit F_NOCLONE;
inherit F_SAVE;

nosave string *reborn_skill = ({
        "sophistry", "capture", "kingkong", "immortal", "musha",
        "recover", "astral",
});
nosave string *words = ({
        "��", "��", "��", "��", "��", "��", "��", "��", "��",
        "��", "��", "��", "��", "Ӧ", "��", "��", "��", "��",
        "��", "��", "��", "��", "��", "��", "��", "��", "��",
        "��", "��", "��", "��", "��", "˼", "��", "��", "ʧ",
});
// �����ĵ�
string query_save_file() {
        return DATA_DIR "npc/buddha";
}

mapping reborn_data = ([]);
int ask_reborn();
void remove() { save(); }

varargs mixed query_reborn_data(string ob) {
        if( !ob ) return reborn_data;
        if( !undefinedp(reborn_data[ob]) )
                return reborn_data[ob];
        return 0;
}

int clear_reborn_data(string ob) {
        if( !undefinedp(reborn_data[ob]) ) {
                map_delete(reborn_data, ob);
                return 1;
        }
        return 0;
}

void create()
{
        seteuid(getuid());
        restore();
        set_name(HIY "����Ĳ��" NOR, ({ "buddha", "fo zu", "fo", "shijia muni" }));
        set("long", @LONG
����ׯ�ϱ������˲������ӡ�
LONG);
        set("nickname", HIW "���編��" NOR);
        set("title", HIC "����" NOR);
        set("gender", "����" );
        set("age", 500);
        set("attitude", "friendly");
        set("max_jing", 1000099);
        set("max_qi", 1000099);
        set("max_jingli", 1000099);
        set("jingli", 1000099);
        set("max_neili", 1000099);
        set("neili", 1000099);
        set("jiali", 100009);
        set("str", 99);
        set("int", 99);
        set("con", 99);
        set("dex", 99);
        set("combat_exp", 100001000099);

        set_skill("dodge", 10000);
        set_skill("unarmed", 10000);
        set_skill("force", 10000);
        set_skill("parry", 10000);
        set_skill("sword", 10000);
        set_skill("medical", 10000);
        set_skill("literate", 10000);
        set_skill("lamaism", 10000);
        set_skill("buddhism", 10000);
        set_skill("shaolin-yishu", 10000);
        set_skill("idle-force", 10000);
        set_skill("huntian-baojian", 10000);
        set_skill("lunhui-jian", 10000);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "lunhui-jian");
        map_skill("sword", "lunhui-jian");
        map_skill("medical", "shaolin-yishu");

        set("inquiry", ([
                "ת������" : (: ask_reborn :),
        ]));

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("/clone/cloth/y-jiasha")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        set("startroom", "/d/reborn/heaven");
        check_clone();
}

void init()
{
        add_action("do_decide", "decide");
}

int ask_reborn()
{
        object me;

        me = this_player();
        command("look "+query("id", me));

        /*
        if( query("reborn/times", me)){
                command("say ��İ���Үʶ�����Ѿ�������");
                return 1;
        }
        */

        if( !query("reborn_lunhui", me)){
                command("say ���ת����Եδ����ǿ�󲻵ã�");
                return 1;
        }

        if( !me->query_family() )
        {
                command("say ���������ɣ�ת���ò���ʧ��");
                return 1;
        }

        command("say �����Ҳ�Դ����е�������Ҫ̽Ѱ����������");
        command("say ��Ҫת������֮��ѧ�ͽ����٣����Ը�⣿");
        message_vision( HIC"$N" HIC"��$n" HIC"�������������Ѿ������� decide �ɣ�\n"NOR,
                        this_object(), me) ;

        set_temp("reborn/ask", 1, me);
        return 1;
}

int do_decide()
{
        int i;
        string msg;
        object me;

        msg = "";
        me = this_player();

        if( !query_temp("reborn/ask", me) )
                return 0;

        tell_object(me, HIW "�����������˵�����Ҹ�����һ����"
                "��ɲ���һ����ɶ��˼��\n����������Ե�ټ����ң�"
                "ƾ�˽����һ���㿪��ǰ�����䣡\n"
                "�˽����뵱�������ģ��м��мǣ�\n" NOR);

        for( i = 0; i < 5; i++)
                msg += words[random(sizeof(words))];

        tell_object(me, HIY "\n�����������˵��������Ľ����ǣ�" HIR + msg + "\n" NOR);
        tell_object(me, HIY "���������Ҽ��̾�����ȥͶ̥�ˣ�\n\n"NOR);

        remove_call_out("reborn_player");
        call_out("reborn_player", 3, me, msg);
        return 1;
}

int reborn_player(object me, string msg)
{
        mapping all_skills, off_skills;
        mapping my, spc_data, tmp_data, mem_data;
        string *sname, *oname, *files;
        string skill, dst;
        object ob;
        int i, n, vip, skill_lvl;
        int money, endtime, day;

        my = me->query_entire_dbase();
        if( my["gender"] == "����" ) my["gender"] = "����";

        off_skills = my["offer"];
        all_skills = me->query_skills();
        oname = keys(off_skills);
        oname -= ({ "neili" });
        sname = keys(all_skills);
        n = sizeof(all_skills);
        for( i = 0; i < n; i++ ) {
                if( SKILL_D(sname[i])->type() != "martial" ) {
                        if( all_skills[sname[i]] > 500 )
                                all_skills[sname[i]] = 500;
                } else {
                        if( sizeof(oname) && member_array(sname[i], oname) != -1 ) {
                                if( (skill_lvl = off_skills[sname[i]] - 3000) > 200 )
                                        all_skills[sname[i]] = skill_lvl;
                                else
                                        all_skills[sname[i]] = 200;
                                oname -= ({ sname[i] });
                        } else {
                                if( all_skills[sname[i]] > 200 )
                                        all_skills[sname[i]] = 200;
                        }
                }
        }

        if( (n = sizeof(oname)) > 0 ) {
                for( i = 0; i < n; i++ ) {
                        if( (skill_lvl = off_skills[oname[i]] - 3000) > 200 )
                                all_skills[oname[i]] = skill_lvl;
                        else
                                all_skills[oname[i]] = 200;
                }
        }

        tmp_data = ([]);
        tmp_data["all_skills"] = copy(all_skills);
        tmp_data["can_make"] = copy(my["can_make"]);
        tmp_data["can_perform"] = copy(my["can_perform"]);
        tmp_data["can_exert"] = copy(my["can_exert"]);
        tmp_data["can_summon"] = copy(my["can_summon"]);
        tmp_data["can_whistle"] = copy(my["can_whistle"]);
        tmp_data["horse"] = copy(my["horse"]);
        tmp_data["warcraft"] = copy(my["warcraft"]);
        tmp_data["jingmai"] = copy(my["jingmai"]);
        tmp_data["family_name"] = copy(my["family"]["family_name"]);
        tmp_data["reborn_time"] = time();
        tmp_data["reborn_pass"] = msg;
        tmp_data["reborn"] = copy(my["reborn"]);
        tmp_data["gender"] = copy(my["gender"]);
        tmp_data["name"] = copy(my["name"]);
        tmp_data["str"] = copy(my["str"]);
        tmp_data["int"] = copy(my["int"]);
        tmp_data["con"] = copy(my["con"]);
        tmp_data["dex"] = copy(my["dex"]);
        tmp_data["srv"] = copy(my["srv"]);
        tmp_data["ability"] = copy(my["ability"]);
        tmp_data["ability1"] = copy(my["ability1"]);
        tmp_data["ability2"] = copy(my["ability2"]);
        tmp_data["newbie_mygift"] = copy(my["newbie_mygift"]);

        spc_data = ([ "hermit" : 1 ]);
        files = reborn_skill;
        skill = files[random(sizeof(files))];
        spc_data += ([ skill : 1 ]);
        files -= ({ skill });
        if( random(10) == 1 ) {
                skill = files[random(sizeof(files))];
                spc_data += ([ skill : 1 ]);
        }
        spc_data += my["special_skill"];
        tmp_data["special_skill"] = spc_data;

        if( MEMBER_D->is_member(me) ) {
                money = MEMBER_D->db_query_member(me, "money");
                if( MEMBER_D->is_valid_member(me) ) {
                        endtime = MEMBER_D->db_query_member(me, "endtime");
                        day = (endtime - time()) / 86400;
                } else  day = 0;

                vip = MEMBER_D->db_query_member(me, "vip");
                MEMBER_D->db_remove_member(me);
                mem_data = ([ "money" : money, "day" : day, "vip" : vip ]);
                tmp_data["member"] = mem_data;
        }
        reborn_data[query("id",me)] = tmp_data;
        save();
        message("vision",HBRED"��ת����������磺"+query("name", me)+"("+query("id", me)+")"
                HBRED "�ѵ÷���㻯ת��֮�����õ�����ħ������ӣ�Ԫ��ת��������\n" NOR, users());

        message_vision("ֻ��$N����һ�����̣�������ʧ�ˡ���\n", me);
        UPDATE_D->remove_user(query("id", me), 0);
        return 1;
}
