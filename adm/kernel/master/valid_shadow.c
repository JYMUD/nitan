// This program is a part of NT MudLIB

/*

        valid_shadow - ������Щ������Ա�ͶӰ (shadow)��
�﷨��
        int valid_shadow( object ob );

        ���� valid_shadow( ��� ��� );
�÷���
        ��һ���������ͶӰ ob ʱ��ʹ�� shadow() �ⲿ��ʽ (efun)���������
        ��������е� valid_shadow() ��ʽ��һ�����Ӧ����Ϊ�˺�ʽ�Ĳ�������
        ����� previous_object() ����ͶӰ������������׼ͶӰ��
        valid_shadow() Ӧ���� 0������ shadow() ����ʧ�ܲ����� 0�����
        valid_shadow() ���� 1��������ͶӰ��
�ο���
        shadow, query_shadowing
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/

// valid_shadow: controls whether an object may be shadowed or not
int valid_shadow(object ob)
{
        object pre;

        pre = previous_object();
        if( geteuid(pre) == ROOT_UID ||
            sscanf(file_name(pre), "/shadow/%*s") ) {
                return 1;
        }

        log_file("shadow", sprintf("%O try to shadow %O failed.\n", pre, ob));
        return 0;
}
