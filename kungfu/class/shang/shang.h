int permit_recruit(object ob)
{
        if( query("detach/�̼ұ�", ob) || query("betrayer/�̼ұ�", ob) )
        {
                command("sneer");
                command("say ��������⣬�����޳�������������㣿");
                return 0;
        }

        if( query("born_family", ob) != "ɽ���̼�" )
        {
                command("heng");
                command("say ���̼ұ������������ˣ������߿���");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "�̼ұ�" )
        {
                command("sneer");
                command("say ���Ȼ�Ѿ���Ұ�ʦ�����ܻ���������");
                return 0;
        }

        return 1;
}
