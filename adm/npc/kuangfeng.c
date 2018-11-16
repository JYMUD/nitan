// kuangfeng.c

#include <ansi.h>
inherit NPC;

#define WARCRAFT_OB             "/clone/npc/warcraft.c"
#define WARCRAFT_DIR            "/data/warcraft/"
#define CRUISE_OB               "/clone/misc/qiankun_ob.c"

void get_subtype(string arg, object ob);
void get_gender(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_warcraft(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string arg);

string* warcraft_type = ({
        "����",
        "�׻�",
        "��ȸ",
        "����",
        "����",
});

mapping magic_type = ([ 
        "����" : "wood",
        "�׻�" : "metal",
        "��ȸ" : "fire",
        "����" : "water",
        "����" : "earth",
]);

void create()
{
        set_name("���", ({ "kuang feng", "kuang", "feng" }) );
        set("gender", "����" );
        set("age", 21);
        set("long",@LONG
����������صľ���ɽׯ�����ͻȻ���������ݳǣ�������
���Ǵ�û�м�����ħ���ޣ���˵���ħ���޾�������Ĺ��ܣ�
�����ϲ���Ļ�������Ҳѡ(choose)һֻ��
LONG );
        set("title",HIW"����ʦ"NOR);
        set("combat_exp", 5000000);

        set("inquiry", ([
                "ħ����"     : "ֻҪ����һ���ƽ������ӵ��ħ�����ˣ�",
                "����Ǭ����" : "���Ҳ��ϵز�֮ʯ����Ϳ���ӵ������Ǭ�����ˡ�",
                "Ǭ����" : "���Ҳ��ϵز�֮ʯ����Ϳ���ӵ������Ǭ�����ˡ�",
        ]));

        set_skill("training", 600);
        set_skill("huisheng-jue", 600);
        set("chat_chance", 15);
        set("attitude", "friendly");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        create_family("����ɽׯ", 2, "����");
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_choose", "choose");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "���˵������λ" + RANK_D->query_respect(ob)
                                + "��Ҫħ����ô��\n");
                        break;
                case 1:
                        say( "���˵������λ" + RANK_D->query_respect(ob)
                                + "��ħ���޿��Ա������˵�Ŷ��\n");
                        break;
        }
}

int do_choose()
{
        object warcraft;
        string filename;
        object me = this_player();

        if (me->is_busy())
                return notify_fail("����һ��������û����ɡ�\n");

        filename = WARCRAFT_DIR+query("id", me);
        if (file_size(WARCRAFT_DIR+query("id", me)+FILE_EXTENSION) > 0)
        {
                catch(call_other(filename, "???"));
                warcraft = find_object(filename);
                set("can_whistle/"+query("id", warcraft), filename, me);
                set("warcraft/id", query("id", warcraft), me);
                set("warcraft/file", filename, me);
                set("warcraft/status", "living", me);
                MYGIFT_D->check_mygift(me, "newbie_mygift/warcraft"); 
                return notify_fail("���������Ѿ�ӵ�й�ħ���ޣ����Ѿ����㹵ͨѪ���ˡ�\n");
        }

        if (me->query_skill("training", 1) <30)
                return notify_fail("���Ԧ����̫���ˣ���ʹ����ħ���ޣ�Ҳ�ᱳ�����ȥ��\n");

        if( !query_temp("warcraft/money", me) )
        {
                command("say ��λ" + RANK_D->query_respect(me) + "��ÿֻħ����һ�����ƽ�������ȸ�Ǯ��");
                return 1;
        }

        write("��Ҫ������ħ���ޣ�\n");
        write(" 1. ����   2. �׻�   3. ��ȸ   4. ����  5. ����\n");
        write("��ѡ�����ִ��ţ�(q ��ȡ��)");

        input_to( (: get_subtype :), me);
        return 1;
}

void get_subtype(string arg, object ob)
{
        int n;

        if (arg == "q" || arg == "Q")
                return;

        sscanf(arg, "%d", n);

        if (n <= 0 || n > 5)
        {
                write("��Ҫ������ħ���ޣ�\n");
                write(" 1. ����   2. �׻�   3. ��ȸ   4. ����  5. ����\n");
                write("��ѡ�����ִ��ţ�(q ��ȡ��)");
                input_to( (: get_subtype :), ob);
                return;
        }
        set_temp("warcraft/race_type", warcraft_type[n-1], ob);

        write("\n");
        write("���趨ħ���޵��Ա�(���ԣ�1  ���ԣ�0)��");
        input_to( (: get_gender :), ob );
}

void get_gender(string arg, object ob)
{
        int n;
        object warcraft;

        sscanf(arg, "%d", n);

        if (n != 0 && n != 1)
        {
                write("\n");
                write("���趨ħ���޵��Ա�(���ԣ�1  ���ԣ�0)��");
                input_to( (: get_gender :), ob );
                return;
        }
        set_temp("warcraft/gender", n?"����":"Ů��", ob);

        write("\n");

        write(sort_string(CYN "�㰴�տ���ָ�㿪ʼ�ɿ�������������ļ�"
                "֤֮�£����������ǻۡ���������һ���ǿ���������ѽ����"
                "������������ԣ������ҵ����ߣ��ң�"+query("name", ob)+
                "��������޽�������Ѫ֮��Լ���մ���Ω��������Ϊ����֮����"
                "��������\n" NOR, 64));
        write("����ħ���޵�Ѫ֮��Լǩ����ϡ�\n");
        write("���趨ħ���޵�Ӣ�� id ��");
        input_to( (: get_id :), ob );
}

void get_id(string arg, object ob)
{
        arg = lower_case(arg);

        if (! check_legal_id(arg))
        {
                write("\n");

                write("���趨ħ���޵�Ӣ�� id ��");
                input_to( (: get_id :), ob );
                return;
        }

        arg = replace_string(arg, " ", "_");

        set_temp("warcraft/id", arg, ob);

        write("\n");
        write("���趨ħ���޵���������(�ɼ���ɫhelp nick)");
        input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
        string  arg_old;
        string  result;

        if( arg && query_temp("big5", ob) )
                arg = LANGUAGE_D->toGB(arg);

        arg_old = arg;

        arg = trans_color(arg, 3);
        arg = filter_color(arg);

        if (! check_legal_name(arg, 12))
        {
                write("���趨ħ���޵���������(�ɼ���ɫ)");
                input_to( (: get_name :), ob);
                return;
        }

        if (stringp(result = NAME_D->invalid_new_name(arg)))
        {
                write("�Բ���" + result);
                write(HIR "��ֹʹ��������������ͬ��ӽ���ħ������������ѭRULES�ж����ֵ���ع涨��"NOR+"\n");
                input_to( (: get_name :), ob);
                return;
        }

        arg = arg_old;
        arg = trans_color(arg, 3);

        set_temp("warcraft/name", arg, ob);

        write("\n");
        write("������ħ���ޣ�(���ɼ���ɫ)");
        input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
        if( arg && query_temp("big5", ob) )
                arg = LANGUAGE_D->toGB(arg);

        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");
        if (! check_legal_name(arg, 60))
        {
                write("������ħ���ޣ�");
                input_to( (: get_desc :), ob);
                return;
        }

        set_temp("warcraft/desc", arg, ob);
        write("ok\n");
        build_warcraft(ob);
}

void build_warcraft(object ob)
{
        string file, filename;
        object warcraft, money;
        string warcraft_id;
        string warcraft_name;
        string warcraft_type;
        string warcraft_desc;
        string warcraft_gender;

        warcraft_id=query_temp("warcraft/id", ob);
        warcraft_name=query_temp("warcraft/name", ob);
        warcraft_name += NOR;

        warcraft_desc=query_temp("warcraft/desc", ob);
        warcraft_desc += NOR;
        warcraft_gender=query_temp("warcraft/gender", ob);
        warcraft_type = query_temp("warcraft/race_type", ob);

        file = read_file(WARCRAFT_OB);

        file = replace_string(file, "WARCRAFT_NAME", warcraft_name);
        file = replace_string(file, "WARCRAFT_ID", warcraft_id);
        file = replace_string(file, "WARCRAFT_GENDER", warcraft_gender);
        file = replace_string(file, "RACE_TYPE", warcraft_type);
        file = replace_string(file, "MAGIC_TYPE", magic_type[warcraft_type]);
        file = replace_string(file, "LONG_DESCRIPTION",
                            warcraft_desc + "\n" + "����" +
                            query("name", ob)+"��ħ���ޡ�\n");

        file=replace_string(file,"OWNER_ID",query("id", ob));
        file=replace_string(file,"OWNER_NAME",query("name", ob));

        filename=WARCRAFT_DIR+query("id", ob);
        if (file_size(filename + ".c") > 0)
        {
                if (warcraft = find_object(filename))
                        destruct(warcraft);
                DBASE_D->clear_object(filename);
                rm(filename + ".c");
        }

        assure_file(filename);
        write_file(filename + ".c", file); // д���ļ�
        VERSION_D->append_sn(filename + ".c"); // ����Ʒ����ʶ����

        catch(call_other(filename, "???"));
        warcraft = find_object(filename);
        if (! warcraft)
        {
                delete_temp("warcraft", ob);
                money = new("/clone/money/gold");
                money->set_amount(100);
                money->move(ob, 1);
                message_vision("$Nһ������$n������Ǹ��Ǹ������һЩ���⣡Ǯ�һ��ǻ���ɡ�\n",
                               this_object(), ob);
                return;
        }
        set("level", 1, warcraft);

#ifdef DB_SAVE
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_remove_item(filename);
        DATABASE_D->db_create_item(warcraft, warcraft->query_entire_dbase());
#endif
        warcraft->save();
        destruct(warcraft);

        set("can_whistle/"+warcraft_id, filename, ob);
        set("warcraft/id", warcraft_id, ob);
        set("warcraft/file", filename, ob);
        set("warcraft/status", "living", ob);
        delete_temp("warcraft", ob);

        command("say ����Դ��������ٻ����ħ���ޣ�<whistle " + warcraft_id +">\n");

        MYGIFT_D->check_mygift(ob, "newbie_mygift/warcraft");   
        return;
}

int accept_object(object me, object ob)
{
        string filename;
        string file;
        object cruise_ob, xob;

        if( query("id", ob) == "dizang zhishi" )
        {
                filename=ITEM_DIR+"cruise/"+query("id", me);
                if (file_size(filename + ".c") > 0)
                {
                        message_vision("$Nһ������$n��������������Ѿ�ӵ�й�����Ǭ�������Ұ���ָ��ˡ�\n",
                                       this_object(), me);
                        set("can_summon/qiankun", filename, me);
                        return 0;
                }

                command("say �������������Ǭ������������ϣ���Ȼ������Ե���Ҿ���Ѱ�������һ���ɣ�");
                if (1)
                {
                        file = read_file(CRUISE_OB);
                        file = replace_string(file, "LONG_DESCRIPTION",
                                                "����" + me->query_idname(1) + "������Ǭ������\n");

                        // give cruise ob to me
                        filename=ITEM_DIR+"cruise/"+query("id", me);
                        if (file_size(filename + ".c") > 0)
                        {
                                if (cruise_ob = find_object(filename))
                                        destruct(cruise_ob);

                                DBASE_D->clear_object(filename);
                                rm(filename + ".c");
                                //log_file("cruise_ob",sprintf("%s have new cruise ob.\n",query("id", me)));
                        }
                        assure_file(filename);
                        write_file(filename + ".c", file);
                        VERSION_D->append_sn(filename + ".c");

                        catch(call_other(filename, "???"));
                        cruise_ob = find_object(filename);
                        if (! cruise_ob)
                        {
                                delete_temp("make_cruise_ob", me);
/*
                                xob = new("/clone/item/dizangshi");
                                xob->move(me, 1);
*/
                                message_vision("$Nһ������$n������Ǹ��Ǹ������һЩ���⣡�����һ��ǻ���ɡ�\n",
                                               this_object(), me);
                                return 0;
                        }
#ifdef DB_SAVE
                        if (! DATABASE_D->query_db_status())
                                DATABASE_D->connect_to_database();
                        DATABASE_D->db_remove_item(filename);
                        DATABASE_D->db_create_item(cruise_ob, cruise_ob->query_entire_dbase());
#endif

                        cruise_ob->move(me, 1);
                        cruise_ob->save();
                        set("can_summon/qiankun", filename, me);
                        delete_temp("make_cruise_ob", me);
                        tell_object(me, HIY "������һ������Ǭ������\n" NOR);
                        destruct(ob);
                        return 1;
                }
        }

        if( query("money_id", ob) )
        {
                if (ob->value() < 10000)
                {
                        command("say ��λ����δ�����˵㣡ÿֻħ����Ҫһ���ƽ�");
                        return 0;
                }

                if (me->query_skill("training", 1) < 30)
                {
                        command("say ���Ԧ������������ʹ����ħ���ޣ�Ҳ�������ȥ��");
                        return 0;
                }
                else
                {
                        set_temp("warcraft/money", 1, me);
                        command("say ���������ˣ�");
                        command("say " + me->name() +
                                     "�������������и���ħ���ޣ�");
                        command("say ��ѡ����Ҫ��ħ���� < choose >");
                        destruct(ob);
                        return 1;
                }
        }
        return 0;
}

int check_legal_id(string id)
{
        int i;
        string *legalid;
        object ppl;

        i = strlen(id);

        if ((strlen(id) < 3) || (strlen(id) > 20))
        {
                write("�Բ���Ӣ�� id ������ 3 �� 20 ��Ӣ����ĸ��\n");
                return 0;
        }

        while(i--)

        if (id[i] != ' ' && (id[i] < 'a' || id[i] > 'z'))
        {
                write("�Բ���Ӣ�� id ֻ����Ӣ����ĸ��\n");
                return 0;
        }

        ppl = LOGIN_D->find_body(id);

        if (ppl || id == "guest" || id == "new")
        {
                write("��������������ID��ͬ�ˣ�����");
                return 0;
        }

        if (file_size(sprintf("/data/user/%c/%s", id[0], id)
                    + __SAVE_EXTENSION__) >= 0)
        {
                write("��������Ѿ���������ʹ���ˣ�����");
                return 0;
        }

        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;
        string  *legalname;             //not implemented..may add later

        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len ))
        {
                write(sprintf("�Բ���ħ���������ֱ����� 1 �� %d �������֡�\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 13 && ! is_chinese(name))
        {
                write("�Բ��������á����ġ�Ϊ����ȡ���ֻ�������\n");
                return 0;
        }
        return 1;
}

int attempt_apprentice(object ob)
{
        command("say ��������һ�߶�ȥ��");
}

int recognize_apprentice(object me, string skill)
{
        if (skill == "training" || skill == "huisheng-jue")
                return 1;
        else
                return 0;
}
