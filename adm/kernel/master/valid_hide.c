// This program is a part of NT MudLIB

/*
���ƣ�

       valid_hide - ������ֹһ������������� (hide) ���������������������
�﷨��
        int valid_hide( object ob );

        ���� valid_hide( ��� ��� );
�÷���
        ����������� (master.c) ���� valid_hide ��������������������ٺͿ�
        �����������������������һ�����ʹ�� set_hide() ��ʽ�Խ�������״̬
        ʱ��������͵��� valid_hide() ��Ψһ�������д˺�ʽ��������������
        ʱӦ���� 1����֮�򴫻� 0����һ������뿴������״̬�����ʱ��Ҳ��ͬ
        ���ķ�ʽ���д˺�ʽ��
�ο���
        set_hide
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��
*/

// valid_hide: controls the use of the set_hide() efun, to hide objects or see hidden objects
int valid_hide(object who)
{
        return 1;
}

/*
int valid_hide(object ob)
{
        //"/system/daemons/channel_d.c"->channel_broadcast("sys",sprintf("1.%O\n this_player():%O\n this_player(1):%O\n",call_stack(1),this_player(),this_player(1)));
        //"/system/daemons/channel_d.c"->channel_broadcast("sys",sprintf("1.%O\n\n",find_player("lonely")));
        //if( call_stack(1)[<1]==this_object() ) return 1;
        if( this_player() && wizardp(this_player()) ) return 1;
        return 0;
}
*/