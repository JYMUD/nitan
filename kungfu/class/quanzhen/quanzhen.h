// check recruit

int permit_recruit(object ob)
{
        if( query("detach/ȫ���", ob) || query("betrayer/ȫ���", ob) )
        {
                command("say �㵱���Ȼ�뿪ȫ��̣��α���Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ����ȫ������������ɣ���������ʦ֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "ȫ���" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬���ú�ѧϰ��������ȫ���������");
                return 0;
        }

        return 1;
}
