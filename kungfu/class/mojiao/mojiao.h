// mojiao.h

int permit_recruit(object ob)
{
        object me;

        me = this_object();

        if( query("detach/ħ��", ob) || 
            query("betrayer/times", ob) )
        {
                message_vision("$N��ŭ������ħ����������Ҫ��������Ҫ�߱��ߣ�\n",me);
                return 0;
        }

        return 1;
}
