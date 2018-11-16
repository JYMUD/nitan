// This program is a part of NITAN MudLIB

// grep.c 

inherit F_CLEAN_UP;

int help();
int do_grep(string,string,int);

nosave string pattern;
nosave string result;

string resolvePath(string path,int op)
{
        string *dn;
        string tmp;
        int i;
        if(path=="/")//�����������⴦��
                return (op)?"/":"*";
        dn=explode(path,"/");
        if(op)//opΪ��0��ʾ��Ҫ����·��
        {
                //dn=dn-({dn[sizeof(dn)-1]});
                //tmp=implode(dn,"/")+"/";
                //����ĳ��򲻺ã����ܶ�ͬ��·����ȷ�������粻����/log/log�ļ�������
                tmp="/";
                for(i=0;i<sizeof(dn)-1;i++)
                {
                        //write("�ϲ�"+dn[i]+"\n");
                        tmp+=dn[i]+"/";
                }
                return tmp;
        }
        else
                return dn[sizeof(dn)-1];
}

int main(object me, string arg)
{
        string  path,wild;
        int level;

        seteuid(getuid()); 

        if (!arg) return help();
        
        if( !wizardp(me) && time()-query_temp("last_grep", me)<30 )
                return notify_fail("ϵͳ�������̾���������� ....\n");   

        if (sscanf(arg,"%s %s",path,pattern)!=2)
                    return help();
            
            if (path != "help" && path != "news" && path != "all")
                    return help();
            
            set_temp("last_grep", time(), me);
        
        if (path == "news" || path == "all")
        {
                write("��������ϵͳ�����������Ժ� ����\n");
                NEWS_D->do_search(me, "document " + pattern);
                if (path == "news")
                {
                        write("Ϊ��Լϵͳ��Դ����30����ֻ�ܽ�������һ�Ρ�\n");
                        return 1;
                }
                write("\n\n");
        }

            level=1;//��-d����Ĭ�ϼ���Ϊ���м�        
        path="/help";
        result="����help�����а�������Ҫ���������ݣ�\n";
        
        write("���ڰ���ϵͳ�����������Ժ� ����\n");
        wild=resolvePath(path,0);
        path=resolvePath(path,1);

        do_grep(path,wild,level);
        write(result+"\n");
        write("Ϊ��Լϵͳ��Դ����30����ֻ�ܽ�������һ�Ρ�\n");
        return 1;
}

int do_grep(string path,string wild,int level)
{
        //int i;string *fs;
        string sbuffer,file;
        reset_eval_cost();//��������ʣ��ִ��ʱ�䣬�������ã�
        if( query("env/debug", this_player()) )
                write("��ʼ����"+path+wild+"\n");
        if(level<0)
        {
                //write("�������ƣ������ٽ���������\n");
                return 0;
        }
        //for(i=0;i<(sizeof(fs=get_dir(path+wild))-1);i++)
        //        write(fs[i]+"\n");
        
        foreach(file in get_dir(path+wild))
        {
                //write("��飺"+path+file+"\n");
                //write("file_size���أ�"+file_size(path+file)+"\n");
                if(file=="."||file=="..")
                        continue;
                
                switch(file_size(path+file))
                {
                        case -1:
                                //�޷���ȡ��Ŀ¼������
                                break;
                        case -2:
                                if(file!="."&&file!="..")
                                        do_grep(path+file+"/","*",level-1);
                                break;
                        default:
                                //write("����ļ���"+path+file+"\n");
                                if(!sbuffer=read_file(path+file))
                                //��̫����ļ���ȡ����Ҫʧ�ܣ����Ҳ�����ͼ��ȡ�������ļ�����Ϊ����\0!
                                {
                                        write("���ļ�"+path+file+"����\n");
                                        return 0;
                                }
                                if(strsrch(sbuffer,pattern)!=-1)
                                        result=result+file + "\n";//Ӧ���Ǽ�¼�������������� 
                        /*
                                if(strsrch(read_file(path+file),pattern)!=-1)
                                        write(path+file+"\n");
                                break;
                        */
                }
                
        }
        return 1;
}

int help()
{
        write(@HELP
ָ���ʽ��grep <help/news/all> ��������

��ָ����൱ǿ����������Ӧ�ط���ȫ������ָ�����ҵ����ݡ�

help:   ������help�ļ���������
news:   �����е�������������
all:    ������help�ļ���������������
ex:
        grep help ��ɽ��
ps:
        �����е�help�ļ��в��Ұ����ַ�������ɽ�ɡ�������ļ���

HELP
    );
        return 1;
}