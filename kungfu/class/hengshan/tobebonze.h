string ask_for_join()
{
        object me = this_player();
        mapping myfam;

        myfam=query("family", me);
        if (!myfam || (myfam["family_name"] != "��ɽ��"))
                return ("��ͺ�ɽû��ԨԴ��ƶ�᲻�Ҹ�����ȡ�\n");
        if( query("class", me) == "bonze" )
                return "�����ӷ𣡳����˲���ڿ����Ѿ������׼����ˡ�\n";
        if( query("gender", me) != "Ů��" )
                return "�����ӷ����գ����գ�ʩ������������ҷ𣬿�ȥ�������ܽ䡣\n";
        set_temp("pending/join_bonze", 1, me);
        command("say �����ӷ����գ����գ�ʩ������������ҷ������(kneel)�ܽ䡣\n");
        return "��ס��һ�����˼ң��ǲ��ܻ��׵ģ����򽫻��ܵ��ͷ���\n";
}

int do_kneel()
{
        object me = this_player();

        string name, new_name;
        if( !query_temp("pending/join_bonze", me) )
                return 0;
        message_vision("$N��˫�ֺ�ʮ�����������ع���������\n\n$n����$N˵�����ðɣ�����ڱ������аɡ�\n\n$n������ƣ���$Nͷ�������Ħ���˼��£���$N��ͷ��������ȥ��\n\n", me, this_object() );
        name=query("purename", me);
        if( !name)name=query("name", me);
        new_name = "��" + name[0..1];;
        command("say �ӽ��Ժ���ķ�������" + new_name + "��");
        command("chat "+name+"����Ϊ�ᣬ�ں�ɽ���У�ȡ����"+new_name+"��");
        command("smile");
        set("marks/old_name", name, me);
        delete_temp("pending/join_bonze", me);
        set("name", new_name, me);
        set("class", "bonze", me);
        set("K_record",query("combat/PKS",  me)+query("combat/MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}
