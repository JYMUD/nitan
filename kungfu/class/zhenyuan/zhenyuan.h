// check recruit

int permit_recruit(object ob)
{
        if( query("detach/������", ob) || query("betrayer/������", ob) )
        {
                command("say �㵱���Ȼ�Ѿ��뿪�����ھ֣����ڸ�����Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say �٣����ھ������������ı�������֮ͽ�϶��ǳ������⣡");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "������" && 
            query("family/family_name", ob) != "�̼ұ�" && 
            query("family/master_name", ob) != "�̽���" )
        {
                command("say ���ף����ף����Ѿ���ʦ���ˡ�");
                return 0;
        }

        return 1;
}
