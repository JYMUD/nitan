// shaolin.h

int permit_recruit(object ob)
{
        if( query("detach/������", ob) || 
            query("betrayer/������", ob) )
        {
                command("say �㷴��������������ôһ�����");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ����治����˽����ʦ�������������֣�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "������" )
        {
                command("say ���Ѿ���ʦָ�㣬Ϊ�β��¿๦������������"
                        "�������أ�");
                return 0;
        }

        return 1;
}
