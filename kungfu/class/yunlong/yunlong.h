// check recruit

int permit_recruit(object ob)
{
        if( query("detach/������", ob) || query("betrayer/������", ob) )
        {
                command("say �㵱���Ȼ�뿪�������ǣ��Ͳ��ػ����ˣ�");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���������ŷ��帴��������壬���߰ɣ�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "������" )
        {
                command("sigh");
                command("shake");
                return 0;
        }

        return 1;
}
