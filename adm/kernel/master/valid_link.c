// This program is a part of NT MudLIB

/*
���ƣ�
        valid_link - ���� link �ⲿ��ʽ����;��
�﷨��
        int valid_link( string from, string to );

        ���� valid_link( �ִ� from, �ִ� to );
�÷���
        ������ʽ�ش� link(from, to) �ⲿ��ʽ�������������� (master
        object) ����� valid_link(from, to) ��ʽ����� valid_link() ���� 0
        ���� link() �Ķ���ʧ�ܡ�������� 1������Ҫ��ͬ���Ĳ�������
        rename() �ɹ���
�ο���
        link
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��

*/

// valid_link: controls use of the link() efun for creating hard links between paths
int valid_link(string original, string reference)
{
        return 0;
}