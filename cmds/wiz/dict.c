// dict.c

#define DICT_D  "/adm/daemons/dictd.c"

inherit F_CLEAN_UP;

int help(object me);
int main(object me, string arg)
{
        string sentence, encode;
        
        if( !SECURITY_D->valid_grant(me, "(wizard)") )  
                return 0;  

        if( !arg ||
            sscanf(arg, "%s to %s", sentence, encode) != 2 ) 
                return help(me);
        
        DICT_D->translate(me, sentence, encode);
        return 1;
}

int help(object me)
{
        write(@HELP
��ʱ����ָ��

���� Google Translate ����ʱ Mud ����

Ŀǰ�ɷ�������Ϊ

ָ���ʽ��dict <����> to en      - ���ķ���ΪӢ��
          dict <Ӣ��> to zh-CN   - Ӣ�ķ���Ϊ����

HELP
        );
        return 1;
}
