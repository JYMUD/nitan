// This program is a part of NT MudLIB

// ����������ʽ����ʱ��ָ���� mudlib �ض����
// ���� debug... ƽʱ��������
void flag( string arg )
{
        string file, func;
        if( previous_object() ) return;

        if( sscanf(arg,"load:%s %s",file,func) )
                printf( "MASTER: "+file+"'s "+func+"() �ش�"+call_other(file, func) );
        else
                printf( "MASTER: δ֪���\n" );
        return;
}
