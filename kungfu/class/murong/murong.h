// murong.h

int permit_recruit(object ob)
{
    object me;

    me = this_object();
    if( query("name", ob) == "Ľ�ݲ�" || 
        query("name", ob) == "Ľ�ݸ�" )
    {
        message_vision("$N��ŭ���ߣ����������������ʲô��˼��\n");
        return 0;
    }

/*
    if( query("born_family", ob) != "Ľ������" && !query("reborn/times", ob) )
    {
        message_vision("$N��$n�����㲻������Ľ�ݼҵ��ˣ�ʦͽ�����˰ɣ�\n",
                       me, ob);
        return 0;
    }
*/

    if( query("detach/Ľ������", ob) || 
        query("betrayer/times", ob) )
    {
        message_vision("$Nҡҡͷ��$n˵���㷴���޳�����Ľ�ݼҲ��������ˣ�\n",
                       me, ob);
        return 0;
    }

    if( query("family/family_name", ob) && 
        query("family/family_name", ob) != query("family/family_name", me) )
    {
        message_vision("$N��$n�������Ȼ��Ľ�ݼҵ��ˣ�ȴ�����������ɣ�ʵ���Ǵ��治����\n",
                       me, ob);
        return 0;
    }

    return 1;
}
