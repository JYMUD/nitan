// This program is a part of NT MudLIB

/*
���ƣ�
        valid_override - ���� efun:: ����;��
�﷨��
        int valid_override( string file, string efun_name, string mainfile );

        ���� valid_override( �ִ� ����, �ִ� �ⲿ��ʽ��, �ִ� ������ );
�÷���
        file �Ǹú���ʵ���������ĵ�����mainfile ��������ĵ�������Ϊ
        #include �Ĺ�ϵ�����߿��ܻ᲻ͬ����

        ��������� (master.c) �м��� valid_override() ���Կ��� efun:: ����
        ǰ���﷨ (prefix) ����;��ÿ�ε�������ʽ���Ա���ǰ����� efun:: ��
        ��ʽʱ���������������е� valid_override()����� valid_override()
        ���� 0�������ʧ�ܡ�����һЩ��ֹ�� efun:: ǰ���﷨���ԭ���õ��ⲿ
        ��ʽ��valid_override() �����ṩһ�������޸����ǵ����á�

        �����ϣ��ʹ��ԭ�� 3.1.2  �� efun:: �����ã�ֻ��Ҫ���������
        master.c �м����������У�

        int valid_override(string file, string efun) { return 1; }

        ������һ�����ƽ϶�� valid_override() ������
        ���밴���������� 21 �沢�޲�ͬ������Ŀǰ�Ѷ��� mainfile ������

        int valid_override( string file, string name )
        {
                if (file == "/adm/kernel/simul_efun") {
                        return 1;
                }

                if (name == "destruct")
                        return 0;
                if (name == "shutdown")
                        return 0;
                if (name == "snoop")
                        return 0;
                if (name == "exec")
                        return 0;

                return 1;
        }
�ο���
        valid_object, function_exists
���ߣ�
        Tim Hollebeek  Beek@ZorkMUD, Lima Bean, IdeaExchange, and elsewhere
���룺
        spock@muds.net          2000.May.21.    v22 ��

*/
// valid_override: controls which simul_efuns may be overridden with
// efun:: prefix and which may not.  This function is only called at
// object compile-time
int valid_override( string file, string name )
{
        // simul_efun can override any simul_efun by Annihilator
        if( file == SIMUL_EFUN_OB || file == MASTER_OB )
                return 1;

        // Must use the move() defined in F_MOVE.
        if( (name == "move_object") && file != F_MOVE && file != F_COMMAND )
                return 0;

        if( (name == "destruct") && ! sscanf(file, "/adm/kernel/simul_efun/%s", file) )
                return 0;

        //  may also wish to protect destruct, shutdown, snoop, and exec.
        return 1;
}

/*
int valid_override(string file, string name, string mainfile)
{

        if( file[0..24] == SIMUL_EFUN_OB[0..24] ) return 1;

        switch(name)
        {
                case "memory_summary":
                case "destruct"        :
                case "shutdown"        :
                case "exec"        :        return 0;
                default                :        return 1;
        }
}
*/
