// by Lonely

int accept_fight(object ob)
{
        object obj, me = this_object();
        int my_max_qi=query("max_qi", me);

        if( query("qi", me)*100/my_max_qi <= 80 )
        {
                call_out("checking1", 1, me, ob);
                return 0;
        }

        remove_call_out("checking1");
        call_out("checking1", 1, me, ob);

        return 1;
}

int accept_kill(object ob)
{
        object obj, me = this_object();

        if( query("id", me) == "ailao" && obj=present("gaolao",environment(me)) )
        {
                command("say �üһ����ı���Ϸ�ʦ�ܣ�׼��˫���ϱڣ�");
                obj->kill_ob(ob);
        }

        if( query("id", me) == "gaolao" && obj=present("ailao",environment(me)) )
        {
                command("say ʦ�֣�׼��˫���ϱڳ�����һ");
                obj->kill_ob(ob);
        }

        remove_call_out("checking2");
        call_out("checking2", 1, me, obj, ob);

        return 1;
}

int checking1(object me, object ob)
{
        object obj;

        if( me->is_fighting() && me->is_killing() && !query_temp("hebi", me) )
        {
                if( query("id", me) == "gaolao" && obj=present("ailao",environment(me)) )
                        obj->kill_ob(ob);
                if( query("id", me) == "ailao" && obj=present("ailao",environment(me)) )
                        obj->kill_ob(ob);
                call_out("checking2", 1, me, obj, ob);
        }
        else if (me->is_fighting())
        {
                call_out("checking1", 1, me, ob);
        }

        return 1;
}

int checking2(object me, object obj, object ob)
{
        if (me->is_fighting())
        {
                if (objectp(obj) && !obj->is_fighting())
                {
                        obj->kill_ob(ob);
                }

                if( !query_temp("hebi", me) )
                {
                        if( query("id", me) == "gaolao" )
                                command("perform hebi ai");
                        if( query("id", me) == "ailao" )
                                command("perform hebi gao");
                }

                call_out("checking2", 1, me, obj, ob);
        }

        return 1;
}

int accept_object(object me, object obj)
{
        object ob = this_player();
        int r;

        if (r = ::accept_object(me, obj))
                return r;

        if (me->is_fighting())
                return notify_fail("���ʣ���û������æ����\n");

        if( query("id", obj) != "zixiapaper" )
                return 0;

        if( query("huashan/yin-jue", ob)>1 )
        {
                remove_call_out("ask_why");
                call_out("ask_why", 1, obj, ob);
                return 1;
        }

        if( query("family/family_name", ob) != "��ɽ��" )
        {
                remove_call_out("thank_other");
                call_out("thank_other", 1, me, obj, ob);
        }
        else
        {
                remove_call_out("thank_huashan");
                call_out("thank_huashan", 1, obj, ob);
        }

        return 1;
}

int ask_why(object obj, object ob)
{
        object me = this_object();

        message_vision("$N����üͷ��$n˵�����ף��㲻���ѱչؾ��޹�����\n", me, ob);
        command("say ��ϼ��ҳ�����ұ���Ҳ�ã��㻹����������");

        destruct(obj);
        return 1;
}

int thank_other(object me, object obj, object ob)
{
        message_vision("$Nʧ���е��������⾹�Ǳ�����ʧ�������ϼ��ҳ���⡣����������������Ϊ����\n", me);
        command("say �����������ɽһ����" + RANK_D->query_respect(ob) + "���⡣");
        command("bow");
        message_vision("$N˵��������ȥ��\n", me);

        destruct(obj);
        destruct(me);
        return 1;
}

int thank_huashan(object obj, object ob)
{
        object ob1, me = this_object();

        message_vision("$Nʧ���е��������⾹�Ǳ�����ʧ�������ϼ��ҳ��\n", me);

        if( query("id", me) == "gaolao" && ob1=present("ailao",environment(me)) )
        {
                command("say ���Һ�ʦ����������������ڴ˵��Űɡ�");
                message_vision("$N������������һ��ϸ˵��һ����ֻ����������ɫ���˼��䣬���˵�ͷ��˼�š�\n", me);
                me = ob1;
        }
        else if( query("id", me) == "ailao" && present("gaolao",environment(me)) )
        {
                command("say ���Һ�ʦ����������������ڴ˵��Űɡ�");
                message_vision("$N������������һ��ϸ˵��һ����������������ɫ���˼��䣬���˵�ͷ��˼�š�\n", me);
        }
        else
        {
                command("say ������ϸ�о��˼㣬����ڴ˵��Űɡ�");
                message_vision("$N˵���������ߵ�һ�����£�ȫ���ע���ж�������ϼ��ҳ����\n", me);
        }

        remove_call_out("open_room");
        call_out("open_room", 5, me, ob, obj);

        return 1;
}

int open_room(object me, object ob, object obj)
{
        message_vision("$N���˹�������$n������һ��\n", me, ob);
        command("say ������һ���ϼ��ҳ��ʵ����Ϊ�������˸��󹦡���ɽ�����ˣ� ");

        if (file_name(environment(me)) != "/d/huashan/chaoyang")
        {
                command("say ���ػ�ɽȥ�ɣ���ϲѶ���ߴ�ⷶ���");
                message_vision("$N˵��������ȥ��\n", me);
                destruct(obj);
                if (objectp(me))
                        destruct(me);
        }
        else
        {
                command("say �ã��ұ�Ϊ�㻤�����㰲����������չ����������ɡ�");
                message_vision("$N����ϼ��ҳ������$n��\n", me, ob);
                message_vision("����$Nת����ǽ��һ��һ��һ�ƣ�ǽ�����к�¡¡����һ��¶��һ��������\n", me);
                command("say ������ʮ������ʼ�����в�͸��������ô���ԭ������������ܡ�");
                command("say �ú�����������Ķ�����С�ı�������Ĳ������ˣ�");
                obj->move(ob);
                message_vision("$N���������ڣ�ʯ�ű㻺���ر�������\n", ob);
                ob->move("/d/huashan/stair");
        }

        return 1;
}
