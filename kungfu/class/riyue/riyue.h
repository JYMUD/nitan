// riyue.h

int permit_recruit(object ob)
{
    object me;

    me = this_object();

    if( query("name", ob) == "��������" || 
        query("name", ob) == "������" )
    {
        message_vision("$N��Ȼ��ŭ���ߣ���Ҳ�ҳ��ҵĻ�ţ�\n",me);
        return 0;
    }

    if( query("detach/�������", ob) || 
        query("betrayer/times", ob) )
    {
        message_vision("$N��ŭ���������������������Ҫ��������Ҫ�߱��ߣ�\n",me);
        return 0;
    }

    return 1;
}
