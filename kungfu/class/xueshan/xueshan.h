// check recruit

int permit_recruit(object ob)
{
        if( query("detach/ѩɽ��", ob) || query("betrayer/ѩɽ��", ob) )
        {
                command("say ���뿪��ѩɽ���ǣ�ѩɽ���Ѿ��������ˣ�");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ����ѩɽ�������ʦ֮ͽ���㻹�������");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "ѩɽ��" )
        {
                command("say ����ʦ��ָ�㣬��ѭ�򽥽�������óȻ��ʦ��");
                return 0;
        }

        return 1;
}
