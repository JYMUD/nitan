// fight.h
// ؤ������

int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);
        int r;

        if (r = ::accept_object(ob, obj))
                return r;

        if( query("id", obj) != "qingzhu ling" )
        {
                command("say ɶ���գ������Ը����Űɡ�");
                return 0;
        }

        if (! ob_fam || ob_fam["family_name"] != "ؤ��")
        {
                command("say ���Ǵ���������������");
                return 0;
        }

        if( query("combat_exp", ob)<10000 )
        {
                command("say ������ˮƽ������ô����������");
                return 0;
        }

        if( query_temp("have_cloth", ob) && present("po bu",ob) )
        {
                command("say �㲻���Ѿ����Ʋ�ô����ȥ�Ҽ��ϰɡ�");
                return 0;
        }

        if( (query("family/beggarlvl", ob) == 0
            && query("combat_exp", ob) <= 10000 )
            || (query("family/beggarlvl", ob) == 1
            && query("combat_exp", ob) <= 20000 )
            || (query("family/beggarlvl", ob) == 2
            && query("combat_exp", ob) <= 50000 )
            || (query("family/beggarlvl", ob) == 3
            && query("combat_exp", ob) <= 100000 )
            || (query("family/beggarlvl", ob) == 4
            && query("combat_exp", ob) <= 200000 )
            || (query("family/beggarlvl", ob) == 5
            && query("combat_exp", ob) <= 300000 )
            || (query("family/beggarlvl", ob) == 6
            && query("combat_exp", ob) <= 500000 )
            || (query("family/beggarlvl", ob) >= 7
            && query("combat_exp", ob) <= 800000) )
        {
             command("say �����ǵ�ŧˮ���ҿ������˰ɡ�");
             return 0;
        }

        if( (query("family/beggarlvl", ob) == 0
            && query("title", me) == "ؤ��һ������" )
            || (query("family/beggarlvl", ob) == 1
            && query("title", me) == "ؤ���������" )
            || (query("family/beggarlvl", ob) == 2
            && query("title", me) == "ؤ����������" )
            || (query("family/beggarlvl", ob) == 3
            && query("title", me) == "ؤ���Ĵ�����" )
            || (query("family/beggarlvl", ob) == 4
            && query("title", me) == "ؤ���������" )
            || (query("family/beggarlvl", ob) == 5
            && query("title", me) == "ؤ����������" )
            || (query("family/beggarlvl", ob) == 6
            && query("title", me) == "ؤ���ߴ�����" )
            || (query("family/beggarlvl", ob) == 7
            && query("title", me) == "ؤ��˴�����" )
            || (query("family/beggarlvl", ob) == 8
            && query("title", me) == "ؤ��Ŵ�����") )
        {
                set_temp("fight_ok",query("id",  me), ob);
                command("say �ðɡ���Ȼ����������ǾͿ���������ˡ�");
                destruct(obj);
                return 1;
        }

        command("hmm");
        command("say �㵽�׶���������ؤ�������Ĺ�أ�");
        return 0;
}

int accept_fight(object ob)
{
        if (query_competitor() == ob)
                return 1;

        if (is_fighting())
        {
                command("say ��Ȼᣬ���Ұ���ǰ������һ�ŵ���˵��");
                return 0;
        }

        if (query("qi") < query("eff_qi") * 2 / 3
           || query("jing") < query("eff_jing") * 2 / 3
           || query("neili") < query("max_neili") * 2 / 3)
        {
                command("say �������е�ƣ�룬����Ъ�����˵��");
                return 0;
        }

        if( query("family/family_name", ob) != query("family/family_name") )
        {
                command("say ���ˣ��ҿ�û��Ȥ���㶯�֡�");
                return 0;
        }

        if( query_temp("fight_ok", ob) != query("id") )
        {
                command("say ��ȥ�����Ҫ���������������ҡ�");
                return 0;
        }

        delete_temp("fight_ok", ob);

        command("nod");
        command("say ��������һ��������֣������㾿����ɶˮƽ��");
        competition_with(ob);
        return 1;
}

void lost()
{
        object me, ob;

        me = query_competitor();
        set_temp("newtitle", query("title"), me);
        set_temp("have_cloth", 1, me);

        ob = new("/d/gaibang/npc/obj/po-bu");
        set("owner", me->name(1), ob);
        set("from", this_object()->name(1), ob);
        ob->move(this_object());

        command("say ��������������Ȼ��ʤ�����ң�����Ʋ�����ȥ�ɡ�");
        command("give po bu to "+query("id", me));
        ::lost();
}

void win()
{
        object me = query_competitor();

        if (! objectp(me))
        {
                command("heihei");
                return;
        }
        command("say �������ˮƽҲ����������ȥ���������ɡ�");
        ::win();
}
