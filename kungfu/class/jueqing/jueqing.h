int permit_recruit(object ob)
{
        if( query("detach/�����", ob) || query("betrayer/�����", ob) )
        {
                command("say �㵱�궼�Ѿ��뿪�˾���ȣ��α���Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ���Ǿ�������������ɣ���������ʦ֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "�����" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬���ú�ѧϰ�������Ǿ����������");
                return 0;
        }

        return 1;
}
