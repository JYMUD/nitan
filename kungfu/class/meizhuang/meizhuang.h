// check recruit

int permit_recruit(object ob)
{
        command("say ÷ׯ�ݲ����ţ�");
        return 0;
        if( query("detach/÷ׯ", ob) || query("betrayer/÷ׯ", ob) )
        {
                command("say �㵱���Ȼ�Ѿ��뿪��ׯ�����ںα���Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ��÷ׯ��С������Ҳ��������������ı�������֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "÷ׯ" && 
            query("family/family_name", ob) != "�������" && 
            query("family/master_name", ob) != "��������" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬��������÷ׯ���");
                return 0;
        }

        return 1;
}
