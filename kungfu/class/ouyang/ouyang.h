// ouyang.h

int permit_recruit(object ob)
{
        object me = this_object();

        if( query("name", ob) == "ŷ����" || 
            query("name", ob) == "ŷ����" )
        {
                message_vision("$N��ŭ���Ҳ٣��������������ʲô��˼����\n",
                               this_object());
                return 0;
        }

/*
        if( query("born_family", ob) != "ŷ������" && !query("reborn/times", ob) )
        {
                message_vision("$N��$n�����㲻������ŷ���ҵ��ˣ�����������Ϊͽ��\n",
                               me, ob);
                return 0;
        }
*/

        if( query("detach/ŷ������", ob) || 
            query("betrayer/times", ob) )
        {
                message_vision("$Nҡҡͷ��$n˵���㷴���޳����Ҳ�������Ϊͽ��\n",
                               me, ob);
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != query("family/family_name", me) )
        {
                message_vision("$N��$n��������Ȼ��ŷ���ҵ��ˣ����������������ɣ��Ҳ�������Ϊͽ��\n",
                               me, ob);
                return 0;
        }

        return 1;
}
