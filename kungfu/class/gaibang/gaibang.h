int permit_recruit(object ob)
{
        if( query("detach/ؤ��", ob) || query("betrayer/ؤ��", ob) )
        {
                command("say �ٺ٣��㵱���ߵ�ʱ������ô˵�ģ�");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ����ؤ��������������������������ʦ֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob )
            && query("family/family_name", ob) != "ؤ��" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬��������ؤ���ʲô��");
                return 0;
        }
        return 1;
}
