// taohua.h

int permit_recruit(object ob)
{
        if( query("detach/�һ���", ob) || 
            query("betrayer/�һ���", ob) )
        {
                command("say ���㻹�������һ���������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���²��Ҳ��ţ�����ʹ�����������ˡ�");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "�һ���" )
        {
                command("say ���������ʦָ�㣬���������һ�����ʲô��");
                return 0;
        }

        return 1;
}
