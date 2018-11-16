// This program is a part of NT MudLIB

/*
���ƣ�
        valid_bind - �ж�һ��ָ���ĺ�ʽָ�� (function pointer) �Ƿ��ܽ��
                     (bind) ��һ������ϡ�
�﷨��
        int valid_bind( object doer, object owner, object victim );

        ���� valid_bind( ��� ������, ��� ӵ����, ��� �ܺ��� );
�÷���
        �� doer ����ʹ�� bind() �ⲿ��ʽ��� owner �� victim ����ĺ�ʽָ
        �꣬����д˺�ʽ������˺�ʽ���� 0���ͽ�ֹ��ϡ�
�ο���
        bind
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/

int valid_bind(object binder, object old_owner, object new_owner)
{
        object ob;

        if( ob = find_object(SECURITY_D) )
                return (int)ob->valid_bind(binder, old_owner, new_owner);

        return 1;
}