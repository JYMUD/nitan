int permit_recruit(object ob)
{

        if( query("detach/��ڤ��", ob) || 
            query("betrayer/��ڤ��", ob) )
        {
                command("say �ߣ����Ȼ���˾Ͳ�Ҫ�ٻ�����");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���²��Ҳ��ţ��Ҳ�������Ϊͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "��ڤ��" )
        {
                command("say ���������ʦָ�㣬��Ҫ���¿๦����Ҫ���Ķ��⣡");
                return 0;
        }

        return 1;
}
