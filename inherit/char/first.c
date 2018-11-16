// This program is a part of NT MudLIB
// first.c ��ʦ��

#include <ansi.h>

inherit NPC;
inherit F_SAVE;

string zname(object);
void reset_me(object me);// ��ʼ���书�����顢title ��
void create_identity (mixed master, mixed where);//Ϊ��������׼��(ֻһ��)
int init_identity (object me, object master, object where);//���õ���restore
int do_clone(object me, object ob);//��ȫ����ob���书�ȸ�me ������
void self_adjust (object me); //�������书60 ��Ѫͬreset  ����copy from master��ָ�
string zm_apply();// ����ask about �����¼�
int do_recopy (object me); // ��ʼ���֮ǰ �ָ�״̬
void find_master (object me, object ob); // ��ȥ����·��ѭ�����
void master_announce (object me, object who, object ob); //����֪ͨ
int convert_identity (object me, object ob);//�������ŵ���
void time_out(object me, object ob);
int is_first() { return 1; }

void create()
{
        set_name("��ϯ�����", ({ "zhang men", "zhangmen", "first" }) );
        set("gender", "����" );
        set("age", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);
        set("no_get", 1);
        set("no_get_from", 1);
        set("long", "���Ǳ�����ϯ����ӡ������������������ս��\n" );
        set("attitude", "heroism");
        set("combat_exp", 1000000);
        set("auto_perform", 1);
        set("current_player","none of us");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_object();

        create_identity(query("master_dir", me), query("start_room", me));
        set("inquiry", ([
                "��ϯ�����" : (: zm_apply :),
                "���Ŵ�ʦ��" : (: zm_apply :),
                "�����" : (: zm_apply :),
                "����" : (: zm_apply :),
                "��ս" : (: zm_apply :),
        ]) );
        add_action("do_reset", "reset");
}

int do_reset(string arg)
{
        object ob=this_player();
        object me=this_object();
        
        if( !wizardp(ob) ) return 0;
        
        if( arg != "zhangmen" ) return notify_fail("��Ҫreset zhangmen��\n");
        set_name("���Ŵ����", ({ "zhang men", "zhangmen", "first" }) );
        me->reset_me(me);
        set("current_player", "none of us");
        save();
        write("����"+query("family/family_name")+"���Ŵ�ʦ�ֳɹ���\n");
        return 1;
}

void create_identity (mixed master, mixed where)
{
        object master_ob, where_ob;

        if( query("created") ) return;
        set("created", 1);

        if( objectp(master) ) master_ob = master;
        else    master_ob = load_object (master);

        if( objectp(where) ) where_ob = where;
        else
        {
                call_other(where,"???");
                where_ob = find_object(where);
        }
        init_identity (this_object(), master_ob, where_ob);
}

int init_identity (object me, object master, object where)
{
        mapping skill_status;
        string *skillnames;
        int i;

        me->move(where, 1);
        set("where",base_name(where));

        set("gender",query("gender", master));
        set("current_master",query("id", master));
        set("current_master_base_name",base_name(master));
        set("family/generation",query("family/generation", master)+1);
        set("family/family_name",query("family/family_name", master));
        set("title",query("family/family_name", me)+zname(me));
        set("short", query("name")+"("+capitalize(query("id"))+")");

        me->restore();
        if( query("current_player", me) != "none of us" )
        {
                do_recopy(me); // copy ���״̬
                return 1;
        }

        remove_call_out("self_adjust");
        call_out("self_adjust", 1, me);

        me->reset_me(me);
        set("current_player", "none of us", me);
        set("new_player", 1, me);
        do_clone(me, master);
        return 1;
}

// ��������
int do_clone(object me, object ob)
{
        object *inv, newob,weapon;
        mapping hp_status, skill_status, map_status, prepare_status;
        string *sname, *mname, *pname;
        int i, weapon_cnt, armor_cnt, temp;
        string skill1,skill2;

        seteuid( geteuid(me) );
        if( !living(me) ) me->revive();

        /* delete and copy skills */
        if( mapp(skill_status = me->query_skills()) ) {
                sname  = keys(skill_status);
                temp = sizeof(skill_status);
                for( i=0; i<temp; i++ ) {
                        me->delete_skill(sname[i]);
                }
        }
        if( mapp(skill_status = ob->query_skillc()) ) {
                sname  = keys(skill_status);
                for( i=0; i<sizeof(skill_status); i++ ) {
                        me->set_skill(sname[i], skill_status[sname[i]]);
                }
        }

        /* delete and copy skill maps */
        if( mapp(map_status = me->query_skill_map()) ) {
                mname  = keys(map_status);
                temp = sizeof(map_status);
                for( i=0; i<temp; i++ ) {
                        me->map_skill(mname[i]);
                }
        }
        if( mapp(map_status = ob->query_skill_map()) ) {
                mname  = keys(map_status);
                for( i=0; i<sizeof(map_status); i++ ) {
                        me->map_skill(mname[i], map_status[mname[i]]);
                }
        }

        /* delete and copy prepare */
        if ( mapp(prepare_status = me->query_skill_prepare()) ) {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++) {
                        me->prepare_skill(pname[i]);
                }
        }
        if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++) {
                        me->prepare_skill(pname[i], prepare_status[pname[i]]);
                }
        }
        
        /* unwield and remove weapon & armor */
        inv = all_inventory(me);
        for( i=0; i<sizeof(inv); i++ ) {
                destruct(inv[i]);
        }

        /* wield and wear weapon & armor */
        inv = all_inventory(ob);
        for( i=0; i<sizeof(inv); i++ ) {
                if( /*query("weapon_prop/damage", inv[i])>1000
                 || query("armor_prop/armor", inv[i])>1000
                 ||*/ query("shaolin", inv[i])
                 || inv[i]->is_unique()
                 || query("value", inv[i])>100000)continue;

                if( query("weapon_prop", inv[i]) && query("equipped", inv[i]) ) {
                        newob = new(base_name(inv[i]));
                        if( newob )
                        {
                                newob->set("value",0);
                                newob->set("no_get",1);
                                if( newob->move(me) ) newob->wield();
                        }
                }
                else if( query("armor_prop", inv[i]) && query("equipped", inv[i]) ) {
                        newob = new(base_name(inv[i]));
                        if( newob )
                        {
                                newob->set("value",0);
                                newob->set("no_get",1);
                                if( newob->move(me) ) newob->wear();
                        }
                }
        }

        /* copy entire dbase values */
        hp_status = ob->query_entire_dbase();
        set("str", hp_status["str"], me);
        set("int", hp_status["int"], me);
        set("con", hp_status["con"], me);
        set("dex", hp_status["dex"], me);
        set("age", hp_status["age"], me);
        set("max_qi", hp_status["max_qi"], me);
        set("eff_qi", hp_status["eff_qi"], me);
        set("qi", hp_status["qi"], me);
        set("max_jing", hp_status["max_jing"], me);
        set("eff_jing", hp_status["eff_jing"], me);
        set("jing", hp_status["jing"], me);
        set("max_neili", hp_status["max_neili"], me);
        set("neili", 2*hp_status["max_neili"], me);
        set("max_jingli", hp_status["max_jingli"], me);
        set("jingli", hp_status["jingli"], me);
        set("jiali", hp_status["jiali"], me);
        set("gender", hp_status["gender"], me);
        set("combat_exp", hp_status["combat_exp"], me);
        set("birthday", hp_status["birthday"], me);

        if( objectp(weapon=query_temp("weapon", me))){
                skill1=query("skill_type", weapon);
                if( objectp(weapon=query_temp("secondaly_weapon", me)) )
                        skill2=query("skill_type", weapon);
        }

        if( mapp(skill_status = me->query_skills()) ) {
                sname  = keys(skill_status);
                for( i=0; i<sizeof(skill_status); i++ ) {
                        command("enable unarmed "+sname[i]);
                        command("enable force "+sname[i]);
                        command("enable parry "+sname[i]);
                        command("enable dodge "+sname[i]);
                        if (stringp(skill1))
                                command("enable "+skill1+" "+sname[i]);
                        if (stringp(skill2))
                                command("enable "+skill2+" "+sname[i]);
                }
        }

        command("enforce max");

        //delete("fighting", me);
        //set("backup/condition", ob->query_condition(), me);
        set("auto_perform", 1);
        set("env/wimpy", 0);
        save();
        tell_object(ob, "״̬������ϡ�\n");

        return 1;
}

void self_adjust (object me)
{
        mapping skill_status;
        string *skillnames;
        int i;

        set("max_jing", 600, me);
        set("eff_jing", 600, me);
        set("jing", 600, me);
        set("max_qi", 600, me);
        set("eff_qi", 600, me);
        set("qi", 600, me);
        set("neili", 600, me);
        set("max_neili", 600, me);
        set("jiali", 60, me);
        set("combat_exp", 100, me);

        skill_status = me->query_skills();
        if ( mapp(skill_status) )
        {
                skillnames = keys(skill_status);
                for(i=0; i<sizeof(skillnames); i++)
                        me->set_skill(skillnames[i], 60);
        }
        carry_object("/clone/misc/cloth")->wear();
        me->save();
}

string zm_apply()
{
        object me = this_object();
        object ob = this_player();

        if( query("family/family_name", me) != query("family/family_name", ob) )
                return "�ұ���"+query("family/family_name", me)+"��ϯ����ӣ�\n";

        if( query("betrayer", ob) || query("detach/"+query("family/family_name", me), ob) )
                return "������ʦ���棬�������в��죬���ܳ�����ϯ���ӵ�һְ��\n";

        if( query("current_player", me) == query("id", ob) )
                return "���ֺ�Ϳ�ˣ�\n";

        if( query("family/gongji", ob) < 1000 )
                return "��ս��ϯ�������Ҫ1000�����ɹ�����\n";

        if( me->is_fighting() || query("fighting", me) )
                return "�Ѿ�����������ս��ϯ����ӣ�\n";

        addn("family/gongji", -1000, ob);
        tell_object(ob, HIC"��ʹ��1000�����ɹ�����ȡ��ս������ϯ����ӡ�\n"NOR);

        set_temp("zm_applied", 1, ob);
        do_recopy (me); // copy ���״̬
        full_self();
        ob->fight_ob(me);
        me->fight_ob(ob);
        competition_with(ob);
        delete_temp("zhangmen/kill", me);
        return "�ã������������ϯ�����һְ�����Ǿ��д�һ�°ɣ�\n";
}

int do_recopy (object me)
{
        string player_name;
        object current_player;


        player_name = query("current_player", me);
        if( !player_name || player_name == "none of us" ) return 1;
        
        current_player = UPDATE_D->global_find_player(player_name); 
        if( !objectp(current_player) ) 
                return 1;
        
        if( query("combat_exp", current_player) > query("combat_exp", me) )
                do_clone (me, current_player);
                        
        UPDATE_D->global_destruct_player(current_player, 1); 

        return 1;
}

void win()
{
        object me = query_competitor();

        if( !objectp(me) ) {
                command("heihei");
                return;
        }

        command("say ����" + RANK_D->query_respect(me) +
                "���ö����ϰ�������ڵ��������г���ͷ�� !\n");
        ::win();
}

void lost()
{
        object me, ob, who;

        me = this_object();
        ob = query_competitor();

        if( !living(me) ) me->revive();
        me->full_self();
        set("fighting", 1, me);
        message_vision ("$N�����°ݣ����������\n",me);
        if( query_temp("zhangmen/kill", me) && query_temp("zm_applied", ob) )
        {
                message_vision ("$N������ü�����˴α�����δ�ܾ��ľ�����ϣ������������\n", me);
                return ::lost();
        }
        
        if( !query_temp("zm_applied", ob) ) return ::lost();
        
        if( query("current_master", me) )
                who = present(query("current_master", me), environment(me));
        
        if( objectp(who) )
        {
                call_out("master_announce",1, me, who, ob);
         
        }
        else
        {
                message_vision("$N�����$n��������ݼ�ʦ����\n",me,ob);
                command("follow "+query("id", ob));
                if( !query("where", me) )
                        set("where", base_name(environment(me)), me);
                remove_call_out("find_master");
                call_out("find_master", 1, me, ob);
                remove_call_out("time_out");
                call_out("time_out", 60, me, ob);
        }
        ::lost();
}

void time_out (object me, object ob)
{
        if( !query("fighting") ) return;
        if( objectp(ob) && same_environment(me, ob) )
                message_vision ("$N�ܲ����˵Ķ�$n˵�����������һ��ȥ�ݼ����ţ���ī��������Ҳû��ȥ����˻������˰ɣ�\n\n",me,ob);
        else if( objectp(ob) )
                tell_object(ob, "��ϯ����Ӻܲ����˵Ĵ������㣬�������һ��ȥ�ݼ����ţ���ī��������Ҳû��ȥ����˻������˰ɣ�\n");
        else
                message_vision ("$N��ֵĳ���Χ���˿����૵������أ���˻������˰ɣ�\n\n",me);
        
        delete("fighting");
        me->set_leader(0);
        remove_call_out("find_master");
        me->move(query("where", me));
}

void find_master (object me, object ob)
{
        object who = present(query("current_master", me), environment(me));
        
        if( !living(me) ) me->revive();
        me->full_self();
        if( !objectp(who) )
        {
                remove_call_out("find_master");
                call_out("find_master", 1, me, ob);
        }
        else
        {
                message_vision ("$N����ʦ���Ͻ��°ݣ���̧��ͷ��$nʹ�˸���ɫ��\n\n",me,ob);
                message_vision ("$N΢΢�ص��˵�ͷ��\n\n",who);
                message_vision ("$N���¡�\n\n",me);
                me->set_leader(0);
                call_out("master_announce",1,me,who,ob);
                me->move(query("where", me));
        }
}

void master_announce (object me, object who, object ob)
{
        object ling;
        
        remove_call_out("time_out");
        if( !living(me) ) me->revive();
        me->full_self();
        CHANNEL_D->do_channel(who, "chat","������ϯ�����"+query("name", ob)+"�����������Ρ������λ�������������");
        delete_temp("zm_applied", ob);
        set("new_player", 1, me); // npc
        delete("fighting", me);
        convert_identity(me, ob);

        if( !query("xkd/ling", ob) )
        {
                seteuid(getuid());
                ling = new( "/d/xiakedao/obj/tongpai1" );
                set("own",query("id",  ob), ling);
                ling->move( ob );
                ling = new( "/d/xiakedao/obj/tongpai2" );
                set("own",query("id",  ob), ling);
                ling->move( ob );
                message_vision( HIY"$N��$n˵�������͵������������Ʒ��������Ϊʦ�ϵ���\n                ���Ǳ�����ϯ����ӣ��ʹ�Ϊʦ��һ�˰ɡ�\n"NOR, who, ob );
                message_vision( HIC"˵�꣬$N���������ƽ���$n���\n"NOR, who, ob );
                set("xkd/ling", 1, ob);
                set("xkd/time", time()+86400, ob);
        }
}

int convert_identity (object me, object ob)
{
        object who;
        string err;

        who = UPDATE_D->global_find_player(query("current_player", me)); 
        if( objectp(who) )
        {
                if( who->query_family() == ob->query_family() && query("zhangmen/title_old", who) )
                        set("title",query("zhangmen/title_old",  who), who);
                else if( query("family/family_name", who) )
                {
                        set("title", sprintf("%s��%s��%s",
                                        query("family/family_name", who),
                                        chinese_number(query("family/generation", who)),
                                        query("family/title", who)), who);
                }
                delete("family/first", who);
                who->save();
                UPDATE_D->global_destruct_player(who, 1); 
        }
        
        set("zhangmen/base_name", base_name(me), ob);
        set("zhangmen/data_name", me->query_save_file(), ob);
        set("zhangmen/title_old",query("title",  ob), ob);
        set("zhangmen/title",query("family/family_name",  ob)+zname(ob), ob);
        set("title",query("family/family_name",  ob)+zname(ob), ob);
        set("family/first", 1, ob);

        me->reset_me(me); // �ָ���ʼ״̬
        set("name",query("name",  ob), me);
        set("gender",query("gender",  ob), me);
        set("current_player",query("id",  ob), me);
        set("title",query("family/family_name",  ob)+zname(ob), me);
        set("short",query("name", me) + "("+capitalize(query("id", me))+")", me);
        do_clone(me,ob);
        return 1;
}

string query_save_file()
{
        string str = query("save_file");
        int i;

        if (str) return str;
        str = DATA_DIR+"zhangmen/"+query("current_master");
        str = replace_string(str," ","_");
        return str;
}

void set_save_file(string str)
{
        set("save_file", str);
}

void kill_ob(object ob)
{
        object me = this_object();
        object master;

        if( query("current_master", me) )
                master = present(query("current_master", me), environment(me));
        if( objectp(master) ) master->kill_ob(ob);
        set_temp("zhangmen/kill", 1, me);
        ::kill_ob(ob);
}

string zname(object ob)
{
        return "��ϯ�����";
        if( query("gender", ob) == "Ů��") return "��ϯ��ʦ��";
        else return "��ϯ��ʦ��";
}

void reset_me (object me)
{
        int i;
        object *inv;
        mapping skill_status, map_status ,prepare_status;
        string *skillnames, *mapnames , *pname;

        if ( mapp(map_status = me->query_skill_map()) )
        {
                mapnames = keys(map_status);
                for(i=0; i<sizeof(mapnames); i++)
                {
                        me->map_skill(mapnames[i]);
                }
        }

        if ( mapp(skill_status = me->query_skills()) )
        {
                skillnames = keys(skill_status);
                for(i=0; i<sizeof(skillnames); i++)
                {
                        me->delete_skill(skillnames[i]);
                }
        }

        if ( mapp(prepare_status = me->query_skill_prepare()) )
        {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++)
                {
                        me->prepare_skill(pname[i]);
                }
        }

        inv = all_inventory(me);
        for( i=0; i<sizeof(inv); i++ )
                destruct (inv[i]);

        set("title", query("family/family_name", me) + zname(me), me);
        set("short", query("name", me) + "("+capitalize(query("id", me))+")", me);

        me->set_skill("force",  60);
        me->set_skill("unarmed",60);
        me->set_skill("sword",  60);
        me->set_skill("dodge",  60);
        me->set_skill("parry",  60);

        set("max_jing", 600, me);
        set("eff_jing", 600, me);
        set("jing", 600, me);
        set("max_qi", 600, me);
        set("eff_qi", 600, me);
        set("qi", 600, me);
        set("neili", 600, me);
        set("max_neili", 600, me);
        set("jiali", 30, me);
}

int accept_hit(object me)
{
        command("say ����������ϯ����ӣ�Ҫ�д����ұ���ȥ��\n");
        return 0;
}

int accept_fight(object who)    { return accept_hit(who); }
int accept_kill(object who)     { return accept_hit(who); }
int accept_ansuan(object who)   { return accept_hit(who); }
int accept_touxi(object who)    { return accept_hit(who); }

varargs void unconcious(object defeater) 
{
        ::unconcious();

        if( !living(this_object()) ) this_object()->revive();
}
