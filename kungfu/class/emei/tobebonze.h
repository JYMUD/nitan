string ask_for_join()
{
        object me;
        mapping myfam;
        me = this_player();

        myfam=query("family", me);
        /*
        if (! myfam || (myfam["family_name"] != "������"))
                return ("ʩ�����Ҷ���������ԨԴ��ƶ�᲻�Ҹ�����ȡ�");
        */

        if( query("class", me) == "bonze" )
                return "�����ӷ𣡳����˲���ڿ����Ѿ������׼����ˡ�";

        if( query("gender", me) != "Ů��" )
                return "�����ӷ����գ����գ�ʩ������������ҷ𣬿�ȥ�������ܽ䡣";

        set_temp("pending/join_bonze", 1, me);
        command ("say �����ӷ����գ����գ�ʩ������������ҷ������(kneel)�ܽ䡣");
        return "��ס����Ȼ���˼ң���һ����𣬲��ܻ��ס�";
}

int do_kneel()
{
        object me = this_player();
        string *prename = ({ "��", "��", "��", "��"});
        string name, new_name;

        if( !query_temp("pending/join_bonze", me) )
                return notify_fail("���ڵ��Ϲ���һ�����û�����㡣\n");

        message_vision(HIC "\n$N" HIC "��˫�ֺ�ʮ�����������ع���������\n\n"
                       NOR + CYN "$n" CYN "����$N" CYN "˵�����ðɣ��Ժ����"
                       "�ڱ������аɡ�\n\n" HIY "$n" HIY "������ƣ���$N" HIY
                       "ͷ�������Ħ���˼��£��漴�㽫$N" HIY "��ͷ��������"
                       "ȥ��\n\n" NOR, me, this_object());

        name=query("purename", me);
        if( !name)name=query("name", me);
        new_name = prename[random(sizeof(prename))] + name[0..1];
        command("say �ӽ��Ժ���ķ�������" + new_name + "��");
        command("nod");
        set("marks/old_name", name, me);
        delete_temp("pending/join_bonze", me);
        set("name", new_name, me);
        set("class", "bonze", me);
        set("K_record",query("combat/PKS",  me)+query("combat/MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}

void init()
{
        add_action("do_kneel", "kneel");
}
