// /d/yixing/npc/bangzhu.h
// Last Modified by winder on Jul. 12 2002
#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <move.h>

void init()
{
        object ob = this_player();

        ::init();

        if( !is_fighting() && interactive(ob) )
        {
                remove_call_out("checking");
                call_out("checking", 1, ob);
        }

        add_action("do_check", "exert");
        add_action("do_check", "yun");
        add_action("do_xue", "xue");
}

void checking(object ob)
{
        object me = this_object();

        if( !living(me) || is_fighting() ) return;
        if( environment() != environment(ob) ) return;
        if( query("party/party_name", ob) == query("party/party_name") )
        {
                message_vision("$N������$n��ͷ˵�������ͣ����ְ﷢��������ĺô���\n", me, ob);
                return;
        }
        if( !random(2) )
                message_vision("$N˫�ֱ�ȭ��ţ��ţ����˵�����������������ѵ�û���κα�ʾ��\n", me);
        else message_vision("$N˵���������Ͽ����" + query("party/party_name") + "������\n", me);
}

int do_check(string arg)
{
        string what, who;

        if( !arg ) return notify_fail("");
        if( arg != "play" )
        {
                 if( sscanf(arg, "%s %s", what, who) != 2 )
                        return notify_fail("");
                 if( what != "play" ) return notify_fail("");
        }
        call_other(BANGSKILLS+"/play2", "exert", this_player(), this_player());
        return 1;
}

int ask_join()
{
        object ob = this_player(), obj;
        string myfam, ob_fam;
        int exp=query("combat_exp", ob);

        ob_fam=query("family/family_name", ob);
        if( ob_fam == "ؤ��" )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(ob) + "һ����ؤ�������Ե׵İɣ�\n");
                return 1;
        }
        if( ob_fam == "����μ�" )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(ob) + "һ���Ǵ���������Ե׵İɣ�\n");
                return 1;
        }

        if( ob_fam == "�һ���" )
        {
                say(name() + "˵����������ʦ��ҩʦһ���뽭����ʿ����������ô��������������˼ҵ����£�\n");
                return 1;
        }

        if( ob_fam == "�䵱��" || ob_fam == "������" || ob_fam == "��ɽ��" ||
                 ob_fam == "������" || ob_fam == "��������" )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(ob) + "һ�����������������Ե׵İɣ�\n");
                return 1;
        }
        myfam = (string)query("party/party_name");
        if( query("party/party_name", ob) == myfam )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(ob) + "�����ҿ���������Ц������\n");
                return 1;
        }
        if( exp > query("combat_exp") && !wizardp(ob))
        {
                say(name()+"˫��һ��ȭ����"+RANK_D->query_respect(ob)+ "Ī���ǿ���Ц�ɡ�\n");
                return 1;
        }
        if( time()<query("party/enter_time", ob)+600 )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(ob) + "������˷����޳����������ڽ���������\n");
                return 1;
        }
        message_vision("$N���ص�����һ��$n�ļ�򣬺ȵ��������ģ��ӽ��Ժ���ֵ�������ͬ����\n", this_object(), ob);

        set_temp("apply/short", ({ HIR + myfam + "����"NOR + query("name",ob)+"("+capitalize(query("id",ob))+")" }), ob);
        delete("party", ob);
        set("party/party_name", myfam, ob);
        set("party/rank", "����", ob);
        set("party/enter_time", time(), ob);
        if( obj = present("bang ling", ob) ) destruct(obj);

        obj = new(BANGLING);
        set("owner",query("id",  ob), obj);
        set("fam", myfam, obj);
        set("combat_exp", query("combat_exp"), obj);
        set("long", "����"+myfam+"�İ��������š�"+query("name", ob)+"����\n", obj);
        obj->move(ob);
        message_vision("$N��һ"+query("unit", obj)+obj->name()+"�Ӹ�$n��\n",this_object(),ob);
        log_file("partyjoin",sprintf("%s��%sʱ����%s\n",query("name", ob),ctime(time()),myfam));
        return 1;
}

// duty 2 teach skills

string ask_skills()
{
        object ling, me = this_player();
        int amount;

        if( is_fighting() )
                return RANK_D->query_rude(me) + "Ϲ����û������æ�ţ���";

        if( query("party/party_name", me) != query("party/party_name") )
                return RANK_D->query_rude(me) + "Ī����������Ұ�����ܰɡ�";

        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "�����Լ��İ���ܲ�ס��";

        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "�����Լ��İ���ܲ�ס��";

        if( (amount=query("score", ling))<10 )
                return RANK_D->query_rude(me)+"�ټӰѾ��������Ż�ָ����һ�£�";

        if( amount > 100 )
        {
                set("party/skills_asked", 100, me);
                addn("score", -100, ling);
        } else {
                set("party/skills_asked", amount, me);
                delete("score", ling);
        }

        tell_object(me, "����룺�书��Ӣ�����֡�\n");
        return "�ðɡ�";
}

int do_xue(string arg)
{
        object me = this_player();
        string *sname;
        int i, amount, level, mylvl;

        if( !(amount=query("party/skills_asked", me)) )
        {
                write("�㻹û�������ͬ���ء�\n");
                return 1;
        }

        if( is_fighting() )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(me) + "Ϲ����û������æ�ţ���");
                return 1;
        }
        if( !arg )
        {
                sname = keys(query_skills());
                write("\n" + name() + "��ѧ���ļ��ܣ�\n\n");
                for(i = 0; i < sizeof(sname); i++)
                        write(to_chinese(sname[i]) + " (" + sname[i] + ")" + "\n");
                return 1;
        }
        if( (level = (int)query_skill(arg, 1)) < 1 )
        {
                say(name() + "ҡ��ҡͷ��������ûѧ����\n");
                return 1;
        }

        mylvl = (int)me->query_skill(arg, 1);
        if( level < mylvl )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(me) + "��Ȼ���������ˡ�\n");
                return 1;
        }
        if( mylvl > 80 )
        {
                say(name() + "ҡ��ҡͷ�������ȥ��������ʽ��ʦ���ܼ������" + to_chinese(arg) + "��\n");
                return 1;
        }
        if( query("jing", me)+10<query("max_jing", me) )
        { 
                write("����Ъ����ɡ�\n");
                return 1;
        }
        set("jing", 10, me);
        me->improve_skill(arg,amount*query("int", me)/3);
        delete("party/skills_asked", me);
        message_vision("$N��$n����йء�" + to_chinese(arg) + "�������ʡ�\n", me, this_object());
        tell_object(me, "�����˰�����ָ�����ԡ�" + to_chinese(arg) + "���ƺ���Щ�ĵá�\n");
        return 1;
}

// duty 3 died to give bangyin

void die()
{
        object ob, corpse, killer;

        if( !living(this_object()) ) revive(1);
//        clear_condition();

        if( objectp(killer = query_temp("last_damage_from")) )
        {
                ob = new(BANGYIN);
                set("long", query("fam")+query("name", ob)+"��\n", ob);
                ob->move(environment());
                message_vision(HIR"\nͻȻ��$N�´��е���һ"+query("unit", ob)+ob->name()+"��\n"NOR,this_object());
                set_temp("my_killer",query("id", killer));
                set("my_killer",query("id",  killer), ob);
                set("combat_exp", query("combat_exp"), ob);
        }
        COMBAT_D->announce(this_object(), "dead");
        if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
                corpse->move(environment());
        remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());

        dismiss_team();
        destruct(this_object());
}
