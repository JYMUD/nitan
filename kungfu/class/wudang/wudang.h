// check recruit

int permit_recruit(object ob)
{
        if( query("detach/�䵱��", ob) || query("betrayer/�䵱��", ob) )
        {
                command("say �㵱���Ȼ�뿪�䵱�ɣ��α���Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say �����䵱�����������ɣ���������ʦ֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "�䵱��" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬���ú�ѧϰ���������䵱��������");
                return 0;
        }

        return 1;
}
