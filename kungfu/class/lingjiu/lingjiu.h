// lingjiu.h

int permit_recruit(object ob)
{
        if( query("detach/���չ�", ob) || 
            query("betrayer/���չ�", ob) )
        {
                command("say �뿪����翷�Ͳ�Ҫ�ٻ�����");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���²��Ҳ��ţ��������չ���޵ľ����������ˡ�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "���չ�" )
        {
                command("say ������ʦ�����Ͳ�Ҫ���������չ��ˣ�");
                return 0;
        }

        return 1;
}
