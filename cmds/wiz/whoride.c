/*  <SecCrypt CPL V3R05>  */
 
//  whohave.c
// Smallfish@Huaxia

inherit  F_CLEAN_UP;

mixed  main(object  me,  string  arg,  int  remote)
{
        object  *ulist;
        int  i;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        ulist  =  users();
        i  =  sizeof(ulist);
        while  (i--)  {
                object  who  =  ulist[i];
                object ridee=query_temp("ridee", ulist[i]);
                
                if  (!  ridee)
                        continue;
                if( query_temp("rider", ridee) != who){
                        continue;
                }        
                write  ("    ");
                write(query("name", who)+"("+query("id", who)+")");
                write(query("ride/msg", ridee)+"��");
                write(query("name", ridee)+"("+query("id", ridee)+")");
                write  ("�ϡ�\n");
        }
        return  1;
}

int  help  (object  me)
{
                write(@HELP
ָ���ʽ  :  whoride  
  
���г�Ŀǰ�����������ҡ�
  
  
HELP
);
                return  1;
}
