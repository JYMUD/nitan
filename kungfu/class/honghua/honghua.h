// honghua.h

int permit_recruit(object ob)
{
        if( query("detach/�컨��", ob) || 
            query("betrayer/�컨��", ob) )
        {
                command("say ���Ǻ컨���Ĵ�����㻹�ǵ��𣿿��㻹����������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say �ߣ����²��Ҳ��ţ����Ǻ컨��ɲ���������");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "�컨��" )
        {
                command("say ���¼�����ʦ�У��������Ǻ컨����ʲô��");
                return 0;
        }

        return 1;
}
