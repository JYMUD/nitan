// This program is a part of NT MudLIB

string creator_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "creator_file", str);
}

// �ж�һ��ָ���������������
string domain_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "domain_file", str);
}

// �ж�һ��ָ�����������Ϊ˭
// �趨�� PACKAGE_MUDLIB_STATS
string author_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "author_file", str);
}

// Ϊ�´�������ָ��һ����˽�ִ�
// �趨�� PRIVS
string privs_file(string filename)
{
        return filename;
}
