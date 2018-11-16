/*
���ƣ�
        valid_socket - ���� socket �ⲿ��ʽ (efunctions)��
�﷨��
        int valid_socket( object caller, string function, mixed array info );

        ���� valid_socket( ��� ������, �ִ� ��ʽ, ��� ���� ��Ѷ );
�÷���
        ÿһ�� socket �ⲿ��ʽִ��֮ǰ�����Ⱥ��� valid_socket()�����
        valid_socket() ���� 0����� socket �ⲿ��ʽʧ�ܡ���֮������ 1 ���
        ������һ������ caller �Ǻ��д� socket �ⲿ��ʽ��������ڶ�������
        function �Ǳ����е� socket �ⲿ��ʽ���ơ����� socket_write() ��
        socket_bind()����������������һ����Ѷ�����С��������Ѷ�Ļ������
        ���еĵ�һ��Ԫ�� (element) �Ǳ��ο��ĵ�������ֵ (file descriptor
        being referenced)���ڶ���Ԫ����ӵ�д� socket ������������̬����
        ������Ԫ���Ǵ� socket ��Զ��λַ (address of the remote end)���ִ�
        ��̬�������ĸ�Ԫ������ socket ��ص� (associated) ���Ӳ����� (port
        number)��
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/

// valid_socket: controls access to socket efunctions
int valid_socket(object eff_user, string fun, mixed *info)
{
        return 1;
}

/*
int valid_socket(object caller, string func, mixed *info)
{
        // caller �� login_ob ����ܲ��ᴫ�����
        if( !objectp(caller) )
                return 0;

        return is_daemon(caller) || is_command(caller) || caller->is_login_ob();
}
*/