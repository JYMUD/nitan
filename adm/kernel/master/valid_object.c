// This program is a part of NT MudLIB

/*
���ƣ�
        valid_object - �����ܿ����Ƿ�Ҫ����ĳ�������
�﷨��
        int valid_object( object obj );

        ���� valid_object( ��� ��� );
�÷���
        ����һ�����֮��������ʽ�����´�������Ϊ�����������������
        (master object) �� valid_object()����� valid_object() ���ڣ�����
        �� 0�����ݻٴ������ʹ����������ⲿ��ʽ (efun) ���������������
        ���˺�ʽ�����ڻ��Ǵ��� 1������������Ĺ��̾͸�ƽ��һ�����˺�ʽ����
        ʱ���������û�л���ִ���κγ�ʽ�룬���� create()���ڣ����Ը����
        ���� file_name(obj) ֮�⣬û�ж��ٶ�����Ч��
�ο���
        valid_override
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/
// valid_object: controls whether an object loaded by the driver should exist
int valid_object(object ob)
{
        return (!clonep(ob)) || inherits(F_MOVE, ob);
}