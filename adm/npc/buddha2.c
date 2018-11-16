// This program is a part of NITAN MudLIB
// Buddha2.c

#include <ansi.h>
inherit NPC;

#define BUDDHA  "/adm/npc/buddha"
int ask_recover();

void create()
{
        seteuid(getuid());
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

        set("inquiry", ([
                "ǰ��" : (: ask_recover :),
        ]));

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
}

void init()
{
        add_action("do_recollect", "recollect");
}

int ask_recover()
{
        object me = this_player();

        command("look "+query("id", me));
        command("say ������ǰ����Ե��?");
        command("say ��ɼǵ�ǰ����������˭���Ҹ���Ľ�������ʲô��");
        command("say �����ܴ�������ұ���㿪��ǰ��ȫ�����䡣");

        tell_object(me, HIW "�����������˵���������������˾����� recollect <id> <����> \n" NOR);
        return 1;
}

int do_recollect(string arg)
{
        string content, filename, item_filename;
        string my_id, my_name, id, pass;
        mapping all_skills, data, tmp_data, sum_data, my;
        string *sname, *sum;
        int i, n;
        object buddha, ob, me = this_player();

        if( query_temp("do_recollect") )
                return notify_fail("��������æ�ţ������Ժ�Ƭ�̡�\n");

        if( query("reborn/times", me) )
                return notify_fail("��İ���Үʶ�����Ѿ�������");

        if( !arg || sscanf(arg, "%s %s", my_id, pass) != 2 )
                return notify_fail("�㾿���ǲ��ǵ��Լ�ǰ����˭��\n");

        buddha = get_object(BUDDHA);
        data = buddha->query_reborn_data(my_id);
        if( !data ) return notify_fail("����ô���ǵ�ǰ��������Ե�أ�\n");

        if( data["reborn_pass"] != pass )
                return notify_fail("����������Ҹ����Ľ��\n");

        if( data["reborn_time"]>query("birthday", me) )
                return notify_fail("����ת��֮ʱ���������ϣ�������ô���ܻ���������Ͷ̥֮����\n");

        if( data["gender"] != query("gender", me) )
                return notify_fail("���ڴ���ת��֮ǰ���Ա�һ�£�����ô���������أ�\n");

        if( query("combat_exp", me) >= 100000000 )
                return notify_fail("��ľ����ܽ���Ӱ��̫����޷�����򿪰���Үʶ��\n");

        set_temp("do_recollect", 1);

        command("say �������Ȼ��ǰ��������Ե֮�ˣ����ҽ���ǰ������򿪣�");

        message_vision( HIY "\n����˵�ű㳯��$N" HIY "����һ���֡�\n\n" NOR
                        HIR "$N" HIR "ͻȻ�е�ͷʹ����......\n\n" NOR, me );

        my_name = data["name"];
        my = me->query_entire_dbase();

        all_skills = copy(data["all_skills"]);
        sname = keys(all_skills);
        n = sizeof(sname);
        for( i = 0; i < n; i++ )
                me->set_skill(sname[i], all_skills[sname[i]]);

        if( sizeof(data["reborn"]) )
        {
                tmp_data = copy(data["reborn"]);
                tmp_data["times"] += 1;
                tmp_data["time"] = copy(data["reborn_time"]);
                if( undefinedp(tmp_data["fams"]) ) tmp_data["fams"] = ({});
                tmp_data["fams"] += ({ data["family_name"] });
                tmp_data["id"] = my_id;
                tmp_data["name"] = my_name;
        }
        else
        {
                tmp_data  = ([ "times" : 1 ]);
                tmp_data += ([ "time" : data["reborn_time"] ]);
                tmp_data += ([ "fams" : ({ data["family_name"] }) ]);
                tmp_data += ([ "id" : my_id ]);
                tmp_data += ([ "name" : my_name ]);
        }
        my["reborn"] = tmp_data;
        my["can_make"] = copy(data["can_make"]);
        my["can_perform"] = copy(data["can_perform"]);
        my["can_exert"] = copy(data["can_exert"]);
        my["special_skill"] = copy(data["special_skill"]);
        my["horse"] = copy(data["horse"]);
        my["warcraft"] = copy(data["warcraft"]);
        my["jingmai"] = copy(data["jingmai"]);
        my["str"] = copy(data["str"]);
        my["int"] = copy(data["int"]);
        my["con"] = copy(data["con"]);
        my["dex"] = copy(data["dex"]);
        my["srv"] = copy(data["srv"]);
        my["ability"] = copy(data["ability"]);
        my["ability1"] = copy(data["ability1"]);
        my["ability2"] = copy(data["ability2"]);
        my["newbie_mygift"] = copy(data["newbie_mygift"]);
        my["character"] = "��ʿ��˫";
        my["welcomegift"] = 1;
        my["tianfu"] = 0;
        delete("tianfu", me);

        if( mapp(data["member"]) ) {
                if( MEMBER_D->is_member(me) )
                        MEMBER_D->db_pay_member(me, data["member"]["money"]);
                else
                        MEMBER_D->db_create_member(me, data["member"]["money"]);

                MEMBER_D->db_fee_member(me, data["member"]["day"]);
                MEMBER_D->db_set_member(me, "vip", data["member"]["vip"]);
        }
        id=query("id", me);
        sum_data = copy(data["can_summon"]);
        sum = keys(sum_data);
        for( i = 0; i < sizeof(sum); i++ ) {
                filename = sum_data[sum[i]] + FILE_EXTENSION;
                if( file_size(filename) < 0 ) continue;
                if( sscanf(filename, "/data/template/%*s") )
                        set("can_summon/"+sum[i], sum_data[sum[i]], me);
                else {
                        if( id == my_id ) {
                                set("can_summon/"+sum[i], sum_data[sum[i]], me);
                                continue;
                        }
                        content = read_file(filename);
                        content=replace_string(content,my_id,id);
                        content=replace_string(content,my_name,query("name", me));
                        if( sum[i] == "qiankun" )
                                item_filename = ITEM_DIR + "cruise/" + id + FILE_EXTENSION;
                        else
                                item_filename = ITEM_DIR + id[0..0] + "/" + id +
                                        "-" + sum[i] + FILE_EXTENSION;
                        if( file_size(item_filename) != -1 )
                                write("�Ѿ�����ԭ�ļ��������ָ��Ǵ���\n");

                        assure_file(item_filename);
                        rm(item_filename);
                        if( !write_file(item_filename, content, 1) ) {
                                write("д�뵵��(" + filename + ")ʱ������֪ͨ��ʦ����\n");
                                return 0;
                        }

                        catch(call_other(item_filename, "???"));
                        ob = find_object(item_filename);

                        ob->receive_dbase_data(DBASE_D->query_object_data(filename));
                        set("user",query("name",  me)+"("+id+")", ob);
#ifdef DB_SAVE
                        DATABASE_D->db_remove_item(base_name(ob));
                        DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                        set("can_summon/"+sum[i], base_name(ob), me);
                        DBASE_D->clear_object(filename);
                        rm(filename);
                        ob->save();
                }
        }

        sum_data = copy(data["can_whistle"]);
        sum = keys(sum_data);
        for( i = 0; i < sizeof(sum); i++ ) {
                filename = sum_data[sum[i]] + FILE_EXTENSION;
                if( file_size(filename) < 0 ) continue;

                if( id == my_id ) {
                        set("can_whistle/"+sum[i], sum_data[sum[i]], me);
                        continue;
                }
                content = read_file(filename);
                content=replace_string(content,my_id,id);
                content=replace_string(content,my_name,query("name", me));

                item_filename = DATA_DIR + "warcraft/" + id + FILE_EXTENSION;

                if( file_size(item_filename) != -1 )
                        write("�Ѿ�����ԭ�ļ��������ָ��Ǵ���\n");

                assure_file(item_filename);
                rm(item_filename);
                if( !write_file(item_filename, content, 1) ) {
                        write("д�뵵��(" + filename + ")ʱ������֪ͨ��ʦ����\n");
                        return 0;
                }

                catch(call_other(item_filename, "???"));
                ob = find_object(item_filename);

                ob->receive_dbase_data(DBASE_D->query_object_data(filename));
#ifdef DB_SAVE
                DATABASE_D->db_remove_item(base_name(ob));
                DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                set("can_whistle/"+sum[i], base_name(ob), me);
                set("warcraft/file", base_name(ob), me);
                DBASE_D->clear_object(filename);
                rm(filename);
                ob->save();
        }

        log_file("static/reborn", sprintf("%s(%s) reborn from %s at %s.\n",
                 me->name(1),query("id", me),my_id,ctime(time())));

        if( query("reborn/times", me) == 1 )
        {
                set("xiantian_force", 1, me);
                tell_object(me, HIY "�������ѷ���ʥ�������������������ˡ�\n" NOR);
        } else
        if( query("reborn/times", me) == 2 )
        {
                set("yuanshen/attack", 10, me);
                set("yuanshen/defense", 10, me);
                set("yuanshen/damage", 10, me);
                set("yuanshen/armor", 10, me);
                set("yuanshen_exp", 1, me);
                set("yuanshen_level", 1, me);
                tell_object(me, HIY "�㽫��������Ԫ����������Ԫ�������\n" NOR);
        } else
        if( query("reborn/times", me) == 3 )
        {
                set("yuanshen/attack", 100, me);
                set("yuanshen/defense", 100, me);
                set("yuanshen/damage", 100, me);
                set("yuanshen/armor", 100, me);
                set("yuanshen_exp", 100000, me);
                set("yuanshen_level", 100, me);
                tell_object(me, HIY "���Ԫ�����ڿ���ͻ��ƿ�������Լ��������ˡ�\n" NOR);
        }
        message("vision", HBRED "��ת����������磺��˵�����ѵ÷�����䣬�����˰���Үʶ��\n" NOR, users());
        me->save();
        me->unconcious();

        buddha->clear_reborn_data(my_id);
        buddha->save();
        delete_temp("do_recollect");
        return 1;
}
