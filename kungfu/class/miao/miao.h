int permit_recruit(object ob)
{
        if( query("detach/��ԭ���", ob) || query("betrayer/��ԭ���", ob) )
        {
                command("heng");
                command("say �㷴���޳����Ҳ�������Ϊͽ��");
                return 0;
        }

        if( query("born_family", ob) != "��ԭ���" )
        {
                command("hmm");
                command("say ����������㲻�������ˡ�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "��ԭ���" )
        {
                command("hmm");
                command("say �����������Ͷʦѧ�գ���Ӧ������Ϊ�����ܻ���������");
                return 0;
        }

        return 1;
}
