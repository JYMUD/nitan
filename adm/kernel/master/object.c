// This program is a part of NT MudLIB

// When an object is destructed, this function is called with every
// item in that room.  We get the chance to save users from being destructed.
// �����⵽����ʱ, �����������������д˺�ʽ
void destruct_env_of(object ob)
{
        if( interactive(ob) )
        {
                tell_object(ob, "�����ڵĿռ���ʧ�ˣ����������ڿ������֮�С�\n");
                ob->move(VOID_OB);
        }
}
