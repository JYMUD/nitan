// kunlun.h

int permit_recruit(object ob)
{
        if( query("detach/������", ob) || 
            query("betrayer/������", ob) )
        {
                command("say ���㻹������������ɽ�����ҹ�����");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���²��Ҳ��ţ�����ʹ�����������ˡ�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "������" )
        {
                command("say ���¼�������ʦָ�㣬����������������ʲô��");
                return 0;
        }

        return 1;
}
