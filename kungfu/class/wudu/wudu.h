// wudu.h

int permit_recruit(object ob)
{
        if( query("detach/�嶾��", ob) || query("betrayer/�嶾��", ob) )
        {
                command("say ���Ȼ�Ѿ���̣��ͱ��ٻ�����");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ��ʦ֮ͽ���ߣ�С���Ұ���ǧ����У�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "�嶾��" )
        {
                command("say �㲻���Ѿ�����ʦ��ô��������ʲô�����Ե�ô��");
                return 0;
        }

        if( query("family/master_name", ob) == "������" )
        {
                command("sneer");
                command("say ��Ȼ���Ѿ��������Ǹ����ˣ�ȴ��������������");
                return 0;
        }

        return 1;
}
