// This program is a part of NT MudLIB

/*
���ƣ�
        valid_read - ���һ�����Ƿ���Ȩ��ȡһ��������
�﷨��
        int valid_read( string file, object user, string func );

        ���� valid_read( �ִ� ����, ��� ʹ����, �ִ� ��ʽ );
�÷���
        ÿ�ε�һ��������Զ�ȡ����ʱ��������ʽ�������������� valid_read()
        �Լ���Ƿ������ȡ���˺�ʽ�Ĳ���Ϊ�������ơ����Զ�ȡ�˵����������
        �еĺ�ʽ���ơ���� valid_read() ���ط���ֵ����׼���ȡ��
�ο���
        valid_write
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/

// valid_read: read privileges; called exactly the same as valid_write()
int valid_read(string file, mixed user, string func)
{
        object ob;

        if( ob = find_object(SECURITY_D) )
                return (int)ob->valid_read(file, user, func);

        return 1;
}

/*
���ƣ�
        valid_write - ���һ������Ƿ���Ȩд��һ��������
�﷨��
        int valid_write( string file, object ob, string func );

        ���� valid_write( �ִ� ����, ��� ���, �ִ� ��ʽ );
�÷���
        ÿ�ε�һ���������д�뵵��ʱ��������ʽ�������������е�
        valid_write() �Լ���Ƿ�����д�롣�˺�ʽ�Ĳ���Ϊ�������ơ�����д��
        �˵�����������еĺ�ʽ���ơ�ͨ���Ǳ�ʹ�õ��ⲿ��ʽ�������
        valid_write() ���ط���ֵ����׼��д�롣
�ο���
        valid_read
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/

// valid_write: write privileges; called with the file name, the object
// initiating the call, and the function by which they called it.
int valid_write(string file, mixed user, string func)
{
        object ob;

        if( ob = find_object(SECURITY_D) )
                return (int)ob->valid_write(file, user, func);

        return 0;
}
