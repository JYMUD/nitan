int permit_recruit(object ob)
{
        if( query("detach/��ң��", ob) || query("betrayer/��ң��", ob) )
        {
                command("say �㵱�궼�Ѿ��뿪����ң�ɣ��α���Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say ������ң�����������ɣ���������ʦ֮ͽ��");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "��ң��" )
        {
                command("say ���Ȼ�Ѿ�������ʦָ�㣬���ú�ѧϰ����������ң��������");
                return 0;
        }

        if( query("per", ob)<26 )
        {
                command("look"+query("id", ob));
                command("say " + RANK_D->query_respect(ob) + "������δ�����"
                        "�㣬�������벻��������ң�ɣ�");
                return 0;
        }

        return 1;
}
