int permit_recruit(object ob)
{
        if( query("detach/�������", ob) || query("betrayer/�������", ob) )
        {
                command("say �㷴���޳����Ҳ�������Ϊͽ��");
                return 0;
        }

/*
        if( query("born_family", ob) != "�������" && !query("reborn/times", ob) )
        {
                command("hmm");
                command("say �ҹ��������Ȼ�˶�ϡ�٣���Ҳ����������֮�ˡ�");
                return 0;
        }
*/

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "�������" )
        {
                command("hmm");
                command("say ���Ȼ�Ѿ���Ұ�ʦ����Ӧ������Ϊ�����ܻ���������");
                return 0;
        }

        return 1;
}