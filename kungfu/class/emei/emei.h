// emei.h

int permit_recruit(object ob)
{
        object me;

        me = this_object();
        if( query("detach/������", ob) || 
            query("betrayer/������", ob) )
        {
                command("say �㵱���Ȼ�뿪�˶����ɣ������ֺαػ�����");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ����ʦ����������ʦ�ţ�"
                        "���������Ƕ����ɲ��������ġ�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "������" )
        {
                command("say ��������ʦָ�㣬Ϊ�����������ɣ�"
                        "Ī����Ҫ��ʦ���ɣ�");
                return 0;
        }

        if( query("class", me) == "bonze" )
        {
                if( query("class", ob) != "bonze" )
                {
                        command("say �����ӷ�ƶ�᲻���׼ҵ��ӡ�");
                        command("say ���������ѧ�����ɵĹ���"
                                "����ȥ�����׼�ʦ�ðɡ�");
                        return 0;
                }

                if( query("gender", ob) != "Ů��" )
                {
                        command("say �����ӷ�ƶ�᲻���е��ӡ�"
                                "ʩ������ѧ�տ�ȥ�����׼�ʦ�á�");
                        return 0;
                }
        }

        if( query("shen", ob)<0 )
        {
                command("say ����������������;������������Ϊͽ��");
                return 0;
        }

        return 1;
}
