int permit_recruit(object ob) 
{
        if( query("detach/��ɽ��", ob) || 
            query("betrayer/��ɽ��", ob) )
        {
                command("say ��ɽ���Խ�δ���չ����ŵ��ӣ�");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ��ɽ�ɽ����ľ������壬������ʦ֮��������⣿");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "��ɽ����" && 
            query("family/family_name", ob) != "��ɽ��" )
        {
                command("say ���������ʦָ�㣬���α������ǻ�ɽ�ɣ�");
                return 0;
        }

        return 1;
}
