// This program is a part of NT MudLIB

mixed valid_database(object ob, string action, mixed *info)
{
        if( !objectp(ob) || (geteuid(ob) != ROOT_UID) )
                return 0;

        else
        {
                if( action == "connect" ) {
                        /*
                         * ������ʾ�Ķ�վ�����ݿ⻥��
                         * Э���ķ�������д������վ��
                         * �򵥷������뼴�ɣ�by Find��
                         */
                        switch (info[1])
                        {
                                case "222.186.34.42":
                                        return "nt150867";      // ���վ�������
                                case "127.0.0.1":
                                case "localhost":
                                        return "nt150867";      // ����վ�������
                                default:
                                        return 0;
                        }

                }
                else
                        return 1;
        }
}
