int permit_recruit(object ob)
{
        if( query("detach/���չ�", ob) || 
            query("betrayer/���չ�", ob) )
        {
                command("say ���Ȼ�Ѿ��������������ҿɲ�������������");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) == "���չ�" )
        {
                command("say ���Ȼ�Ѿ�Ͷ�����������£�����Ȼ������������֪���书��");
                command("say ������Ҫ����ֱ��������ѧ���ˣ�����������ʦ֮��");
                return 0;
        }

        if( query("family/family_name", ob) )
        {
                command("say �����ʦ��ȥ�������������¡�");
                return 0;
        }

        return 1;
}
