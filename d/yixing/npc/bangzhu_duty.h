// /d/yixing/npc/bangzhu_duty.h
// Last Modified by winder on Jul. 12 2002
// duty 1   to accept players

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
                say(name() + "˫��һ��ȭ����" + RANK_D->query_respect(ob) + "Ī���ǿ���Ц�ɡ�\n");

                return 1;
        }
        if( time()<query("party/entertime", ob)+600 )
        {
                say(name() + "��ŭ����" + RANK_D->query_rude(ob) + "������˷����޳����������ڽ���������\n");
                return 1;
        }
        message_vision("$N���ص�����һ��$n�ļ�򣬺ȵ��������ģ��ӽ��Ժ���ֵ�������ͬ����\n", this_object(), ob);

        ob->set_temp("apply/short",
                ({ HIR + myfam + "����"NOR + query("name",ob)+"("+capitalize(query("id",ob))+")" }));
        delete("party", ob);
        set("party/party_name", myfam, ob);
        set("party/entertime", time(), ob);

        if( obj = present("bang ling", ob) )
                destruct(obj);

        obj = new(BANGLING);
        set("owner",query("id",  ob), obj);
        set("fam", myfam, obj);
        set("combat_exp", query("combat_exp"), obj);
        obj->set("long",
"����"+myfam+"�İ��������š�"+query("name", ob)+"����\n");
        obj->move(ob);
        message_vision("$N��һ"+query("unit", obj)+obj->name()+"�Ӹ�$n��\n",this_object(),ob);

        log_file("test/BangJoin",sprintf("%s��%sʱ����%s\n",query("name", ob),ctime(time()),myfam));
        return 1;
}
#include "guanjia.h"
// duty 2  assign jobs
/*
string ask_job()
{
        object me = this_player(), leader, ling, ob, *obj, dest, room;
        string myfam, *files, file, region, biaoju, ob_bang;
        string *mydests, mydest, *starts;
        int i, temp, myexp;
        mapping job, destine;

        string *levels = ({
                "3000",
                "5000",
               "10000",
               "20000",
               "50000",
              "100000",
              "300000",
              "500000",
        });

        myfam = (string)query("fam");
        if( query_temp("bangs/fam", me) != myfam )
                return RANK_D->query_rude(me) + "Ī����������Ұ�����ܰɡ�";

        if( objectp(leader = me->query_leader()) ) {
                if( leader != this_object() )
                         return RANK_D->query_rude(me) + "�����˰ﲻ������������
����";
        }

        if( !(ling = present("bang ling", me)) ) {
                ling = new(BANGLING);
                set("owner",query("id",  me), ling);
                set("fam", myfam, ling);
                set("combat_exp", query("combat_exp"), ling);
                ling->move(me);
                message_vision("$N��һ"+query("unit", ling)+ling->name()+"�Ӹ�$n��\n",this_object(),me);
        }

        if( time()<query("bangs/asktime", me)+180){
                if( mapp(query("job", ling)) )
                        return RANK_D->query_rude(me) + "���Ǹ��ʹ�����";
        }

        set("bangs/asktime", time(), me);

        myexp=query("combat_exp", me);
        myexp = (4 * myexp + random(2 * myexp)) / 5;

        temp = sizeof(levels);
        for( i = 0; i < temp; i++ ) 
                if( myexp < atoi(levels[i]) ) break;

        if( i >= temp )
                return "���û���ʺ���İ���";

        job = (BANGJOB + levels[i])->query_job();

        if( mapp(query("job", ling)) )
                delete("job", ling);
        set("job", job, ling);

        if( ob = present("caili", me) )
                destruct(ob);

        switch(job["type"]) {
        case "Ѱ":
                command("nod");
                set("job/max", atoi(levels[i]), ling);
                return "��ȥ��" + job["name"] + "������";
                break;

        case "ɱ":
                command("nod");
                set("job/max", atoi(levels[i]), ling);
                return "��ȥ��" + job["area"] + "��" + job["name"] + "ɱ�ˡ�";
                break;

        case "̯��":
                command("nod");
                job = info_store[random(sizeof(info_store))];
                set("job/name", job["name"], ling);
                set("job/boss", job["boss"], ling);
                set("job/place", job["place"], ling);
                return job["name"] + "����»�û�н�̯�ѣ���ȥҪ����";
                break;

        case "����":
                obj = filter_array(children(BIAOTOU), (: clonep :));
                if( sizeof(obj) < 10 ) {
                        ob = new(BIAOTOU);
                        file = biao_places[random(sizeof(biao_places))];
                        if( !(dest = find_object(file)) )
                                dest = load_object(file);
                        ob->move(dest);            
                        message("vision",
                        ob->name() + "Ѻ���ڳ����˹�����\n",
                        dest, ({ob}));
                        region = explode(file, "/")[1];
                        set("job/name",query("nickname",  ob), ling);
                        return "ȥ���̵ĵ����ǻ�������" + 
                        query("nickname", ob)+
                        "���ڳ�������" + 
                        region_names[region]+query("short", dest)+"��";
                } else {
                        ob = obj[random(sizeof(obj))];
                        dest = environment(ob);
                        biaoju=query("nickname", ob);

                        if( !dest || !biaoju ) {
                                destruct(ob);
                                command("shake");
                                return "��Ъ�Űɣ����û��Ҫ���İ���";
                        }

                        file = base_name(dest);
                        if( strsrch(file, "/d/") != 0
                         || !mapp(query("exits", dest))){
                                destruct(ob);
                                command("shake");
                                return "��Ъ�Űɣ����û��Ҫ���İ���";
                        }

                        command("nod");
                        region = explode(file, "/")[1];
                        set("job/name", biaoju, ling);
                        return "ȥ���̵ĵ����ǻ�������" + biaoju + 
                        "���ڳ�������" + 
                        region_names[region]+query("short", dest)+"��";
                }
                break;

        case "ʾ��":
                obj = filter_array(children(BANGZHONG), (: clonep :));
                if( sizeof(obj) ) {
                obj = filter_array(obj, "is_victim", this_object(), myfam);
                if( sizeof(obj) ) {
                        command("nod");
                        ob = obj[random(sizeof(obj))];
                        ob_bang=query("title", ob);
                        set_temp("bangs/victim", ob_bang, me);
                        set("job/name", ob_bang, ling);
                        return "���" + ob_bang + "���������ǹ���ȥ����ȥɱһ��ʾʾ����";
                }
                }
                break;

        case "����":
                command("nod");

                job = info_guest[random(sizeof(info_guest))];
                region = explode(job["file"], "/")[1];

                ob = new(CAILI);
                set("job", job, ob);
                set("owner", me, ob);
                set("job/title", job["title"], ling);
                set("job/area", job["area"], ling);
                ob->set("long",
"����һ��" + myfam + "�����͸�" + "��" + job["title"] + "��" + "�Ĳ���\n");
                ob->move(me);
                message_vision("$N��һ"+query("unit", ob)+ob->name()+"����$n��\n",this_object(),me);
                return "�����ݲ����͸�" + job["area"] + "��" + "��" + job["title"] + "��" + "��";
                break;

        case "����":
                region = explode(base_name(environment()), "/")[1];
                starts = keys(info_destine);
                if( member_array(region, starts) == -1 ) {
                        command("shake");
                        return "��Ъ�Űɣ����û��Ҫ���İ���";
                }
                destine = info_destine[region];
                mydests = keys(destine);
                mydest = mydests[random(sizeof(mydests))];
                set("job/dest", region_names[mydest], ling);
                set("job/bonus", destine[mydest], ling);
                ob = new(BANGZHU2);
                set("name", query("name"), ob);
                set("fam", myfam, ob);
                set("title", myfam+"����", ob);
                set("dest", mydest, ob);
                ob->set_leader(me);
                set("helper", me, ob);
                command("nod");
                call_out("do_start", 1, this_object(), ob);
                return "˵������������岻�ʣ��㻤������" + region_names[mydest] + "��\n";
        }

        command("shake");
        return "��Ъ�Űɣ����û��Ҫ���İ���";
}

void do_start(object me, object ob)
{
        ob->move(environment());
        destruct(this_object());
}

// duty 3  accept stuffs

int accept_object(object who, object ob)
{
        object obj;
        int bonus, record;
        string name, chname = "";
        mapping job;

        if( query_temp("bangs/fam", who) != query("fam") )
                return notify_fail(name() + "��ŭ�����󵨣���ı��������������\n");

        if( !(obj = present("bang ling", who)) )
                return notify_fail(name() + "��ŭ����û���õĶ������������㶪����\n");

        if( !mapp(job=query("job", obj)) )
                return notify_fail(name() + "��ŭ����û���õĶ��������Լ��İ��񶼼ǲ�ס����\n");

        switch(job["type"]) {
        case "Ѱ":
                name = ob->name();
                for(int i = 0; i < strlen(name); i++)
                        if(name[i] > 160 && name[i] < 255) 
                                chname += name[i..i];
                if( chname != job["name"] )
                        return notify_fail(name() + "��ŭ����û���õĶ��������Լ��İ��񶼼ǲ�ס����\n");
                bonus=job["bonus"]*job["max"]/(query("combat_exp", who)+1000);
                record = bonus / 2 + random(bonus);
                log_file("test/BangJob",sprintf("%s��%sʱ�ҵ�%s��%s�����\n",query("name", who),ctime(time()),chname,chinese_number(record)));
                bonus = job["score"];
                break;

        case "����":
                if( base_name(ob) != BIAOHUO )
                        return notify_fail(name() + "��ŭ����û���õĶ�������һ֦�ڶ��㲻����\n");
                if( query("my_killer", ob) != query("id", who) )
                        return notify_fail(name() + "��ŭ��������������ľ������ã������������������㣡\n");
                bonus=query("combat_exp", ob);
                bonus=bonus*120/(bonus+query("combat_exp", who));
                record = bonus + random(bonus);
                log_file("test/BangJob",sprintf("%s��%sʱ����ڵ�%s�����\n",query("name", who),ctime(time()),chinese_number(record)));
                bonus /= 4;
                break;
        default:
                return notify_fail(name() + "��ŭ����û���õĶ��������Լ��İ��񶼼ǲ�ס����\n");
                break;
        }

        command("nod");
        delete("job", obj);

        addn("combat_exp", record, who);
        addn("shen", -bonus, who);
        addn("score", bonus, obj);

        remove_call_out("store");
        call_out("store", 1, ob);
        return 1;
}

// duty 4  teach skills
string ask_skills()
{
        object ling, me = this_player();
        int amount;

        if( is_fighting() )
                return RANK_D->query_rude(me) + "Ϲ����û������æ�ţ���";

        if( query_temp("bangs/fam", me) != query("fam") )
                return RANK_D->query_rude(me) + "Ī����������Ұ�����ܰɡ�";

        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "�����Լ��İ���ܲ�ס��";

        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "�����Լ��İ���ܲ�ס��";

        if( (amount=query("score", ling))<10 )
                return RANK_D->query_rude(me) + "�ټӰѾ��������Ż�ָ����һ�£�";

        if( amount > 100 ) {
                set_temp("bangs/skills_asked", 100, me);
                addn("score", -100, ling);
        } else {
                set_temp("bangs/skills_asked", amount, me);
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

        if( !(amount=query_temp("bangs/skills_asked", me))){
                write("�㻹û�������ͬ���ء�\n");
                return 1;
        }

        if( is_fighting() ) {
                say(name() + "��ŭ����" + RANK_D->query_rude(me) + "Ϲ����û������æ�ţ���");
                return 1;
        }

        if( !arg ) {
                sname = keys(query_skills());
                write("\n" + name() + "��ѧ���ļ��ܣ�\n\n");
                for(i = 0; i < sizeof(sname); i++)
                        write(to_chinese(sname[i]) + " (" + sname[i] + ")" + "\n");
                return 1;
        }

        if( (level = (int)query_skill(arg, 1)) < 1 ) {
                say(name() + "ҡ��ҡͷ��������ûѧ����\n");
                return 1;
        }

        mylvl = (int)me->query_skill(arg, 1);
        if( level < mylvl ) {
                say(name() + "��ŭ����" + RANK_D->query_rude(me) + "��Ȼ���������ˡ�\n");
                return 1;
        }

        if( mylvl > 80 ) {
                say(name() + "ҡ��ҡͷ�������ȥ��������ʽ��ʦ���ܼ������" + to_chinese(arg) + "��\n");
                return 1;
        }

        if( query("jing", me)+10<query("max_jing", me)){
                write("����Ъ����ɡ�\n");
                return 1;
        }

        set("jing", 10, me);
        me->improve_skill(arg,amount*query("int", me)/3);
        delete_temp("bangs/skills_asked", me);

        message_vision("$N��$n����йء�" + to_chinese(arg) + "�������ʡ�\n", me, this_object());
        tell_object(me, "�����˰�����ָ�����ԡ�" + to_chinese(arg) + "���ƺ���Щ�ĵá�\n");
        return 1;
}

void store(object ob)
{
        if(ob) destruct(ob);
}

private is_victim(object ob, string arg)
{
        string fam;

        if( !stringp(fam=query("title", ob)))return 0;
        if( fam == arg ) return 0;

        return 1;
}
*/
