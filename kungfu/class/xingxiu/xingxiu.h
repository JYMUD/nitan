// xingxiu.h

int welcome(object ob)
{
        if( query("detach/������", ob) || query("betrayer/������", ob) )
        {
                command("say ������������ȥ�������������ɺðɣ�");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say û��ϵ������Ȼ�й�����ʦ�����������������Ͷ������ϲ�ɺأ�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "������" )
        {
                command("say �Ǻǣ��ð���"+query("family/family_name", ob)+
                        "��ʲô��");
                return 0;
        }

        return 1;
}
