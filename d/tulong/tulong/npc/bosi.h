void init()
{
        object me = this_player();

        if (! interactive(me)
           || me->is_fighting()
           || ! living(this_object()))
                return;

        if( query_temp("have_yitianjian", me )
           || present("yitian jian", me))
        {
                command("say �ף����콣��ô�������������"
                        "�����ԭ֮��û�����ˣ�");
                this_object()->kill_ob(me);
                return;
        }

        if( query_temp("have_tulongdao", me )
           || present("tulong dao", me))
        {
                command("say �ߣ����������������������Ѿ���"
                        "���ʱ�ˣ�");
                this_object()->kill_ob(me);
                return;
        }

        if (present("shenghuo ling", me))
        {
                command("say �ף�����ô���������ҽ̵�ʥ����"
                        "���컹���ң�");
                this_object()->kill_ob(me);
                return;
        }
}

int recognize_apprentice(object me, string skill)
{
        if( query("shen", me)>1000 )
        {
                command("say ߴ������������³³�������˿���"
                        "ȥ�����Ǻ��ˣ�������");
                return -1;
        }

        if (skill != "sanscrit")
        {
                command("say ���������ӡ��ѧ��һ�㶫������"
                        "����֪�㰡��");
                return -1;
        }
        return 1;
}
