int permit_recruit(object ob)
{

        if( query("detach/��Ĺ��", ob) || 
            query("betrayer/��Ĺ��", ob) )
        {
                command("say ����ȥ��ȥ�ˣ��������Ǻο�������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���²��Ҳ��ţ��Ҳ�������Ϊͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "��Ĺ��" )
        {
                command("say ���������ʦָ�㣬��Ҫ���¿๦����Ҫ���Ķ��⣡");
                return 0;
        }

        return 1;
}
