// check recruit

int permit_recruit(object ob)
{
        if( query("detach/Ѫ����", ob) || query("betrayer/Ѫ����", ob) )
        {
                command("say ���뿪��Ѫ�����ǣ��ͱ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ��ʦ֮ͽ���ߣ��ߣ��Ұ���ǧ����У�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "Ѫ����" )
        {
                command("say �㲻���Ѿ�����ʦ��ô��������ʲô��͵ѧ�����ؼ�����");
                return 0;
        }

        return 1;
}
