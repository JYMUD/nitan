void init()
{
        add_action("do_kneel", "kneel");
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( query("class", me) == "bonze" )
                return "���Ѿ��ǳ������ˣ�����������Щʲô��";

        if( query("gender", me) != "����" )
                return "����ѩɽ������ֻ����ͽ���㻹���߰ɡ�";

        set_temp("pending/join_bonze", 1, me);

        return "���ã����ã�������������ҷ������(kneel)�ܽ䡣";
}

int do_kneel()
{
        object me = this_player();

        if( !query_temp("pending/join_bonze", me) )
                return 0;

        message_vision(HIC "\n$N" HIC "��˫�ֺ�ʮ�����������ع���������\n\n"
                       NOR + CYN "$n" CYN "����$N" CYN "˵�����ðɣ��Ժ����"
                       "�ڱ������аɡ�\n\n" HIY "$n" HIY "������ƣ���$N" HIY
                       "ͷ�������Ħ���˼��£��漴�㽫$N" HIY "��ͷ��������"
                       "ȥ��\n\n" NOR, me, this_object());

        set("class", "bonze", me);
        set("title", "ѩɽ������", me);

        command("nod");
        command("say ��Ȼ���˼ң��͵�һ������ٲ��ܻ��ס�");

        return 1;
}
