// check recruit

int permit_recruit(object ob)
{
        if( query("detach/������", ob) || query("betrayer/������", ob) )
        {
                command("say �㵱���Ȼ�Ѿ��뿪�����ǣ����ںα���Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ����ѩɽ��������ݾ����������ı�������֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "������" && 
            query("family/family_name", ob) != "����ׯ" && 
            query("family/master_name", ob) != "ʯ��" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬��������ѩɽ���ɸ��");
                return 0;
        }

        return 1;
}
