// This program is a part of NT MudLIB

#define FIRST_PRELOAD   "/adm/daemons/systemd.c"


// Function name:   update_file
// Description:     reads in a file, ignoring lines that begin with '#'
// Arguements:      file: a string that shows what file to read in.
// Return:          Array of nonblank lines that don't begin with '#'
// Note:            must be declared static (else a security hole)
protected string *update_file(string file)
{
        string *list;
        string str;
        int i;

        str = read_file(file);
        if( !str )
                return ({});

        list = explode(str, "\n");
        for (i = 0; i < sizeof(list); i++)
                if( list[i][0] == '#')
                        list[i] = 0;

        list -= ({ 0 });
        return list;
}

// Function name:       epilog
// Return:              List of files to preload
// ��ʼ����ҵ Initialization
// �� driver ����Ϊ -e , flag Ϊ����ֵ

string *epilog(int flag)
{
        /*
        string *items;

        items = update_file(CONFIG_DIR + "preload");
        return items;
        */

        if( flag )
        {
                printf("������ʽȡ��Ԥ���������\n");
                log_file("preload/preload","������ʽȡ��Ԥ���������\n");
                return allocate(0);
        }

        return ({ FIRST_PRELOAD });
}

// preload an object
// Ԥ���������
void preload(string file)
{
        mixed err;

        if( objectp(find_object(file)) )
                return;

        if( err = catch(load_object(file)) )
                log_file("static/preload",sprintf("���� %s ʱ��������: %O\n", file, err));
}
