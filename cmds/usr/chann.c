//��ѯ��Ϸ����ʱ������ֱ�Ӵ����ݿ�ȡ���ݣ�Ӧ�ý�ֹƵ����ȡ
//Write By JackyBoy@XAJH 2001/5/15
#include <ansi.h>

inherit F_CLEAN_UP;

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}
mapping channels;
string *chann;
string cmdhelp=
"ѡ�������ʽ��<"HIR"Ƶ��"HIG">   <"HIR"����"HIG">\n"+
"����Ƶ��Ϊ��������ú�ʹ�õ�Ƶ����Ӣ����������"HIC"chat"HIG","HIM"rumor"HIG"��\n"+
"������Ϊ"HIR"public"HIG","HIR"main"HIG"����"HIR"none"HIG"�����У�\n"+
HIR"public"HIG"��ʾ����Ƶ��������Ϣ��ʾ��������Ϣ����\n"+
HIR"main  "HIG"��ʾ����Ƶ��������Ϣ��ʾ������Ϣ������\n"+
HIR"none  "HIG"��ʾ��Ƶ���رգ����ٽ���Ƶ����Ϣ\n"+
"��Ҳ��������"HIR"exit"HIG"�˳�����ѡ����������"HIR"help/?"HIG"��ȡ����Ϣ��\n";

int do_chan(string,object,int);
int show_main(object);

int main(object me,string arg)
{
        channels=CHANNEL_D->query_chann();
        chann=keys(channels);
        //����ʦ�͹��˵���Щ��ʦƵ������
        if(!wizardp(me)) chann -= ({"wiz","sys","debug","nch"});
        chann -= ({"shout"});
        
        if(arg)
                return do_chan(arg,me,1);
        show_main(me);
        return 1;
}

int show_main(object me)
{
        class channel_class ch;
        string *tuned_ch;
        string s,str,state;
        
        ch = new(class channel_class);
        //tuned_ch=query("channels", me);
        tuned_ch = CHANNEL_D->query_using_channel(me, 1);

        str=me->name()+"��Ƶ������Ϊ��\n"HIC"��"HIY"������������������������������������������������������������"HIC"��\n"NOR;
        str+=sprintf(HIC" %-10s        %-8s         %-8s\n\n","Ƶ������","Ƶ������","Ƶ��״̬");
        foreach(s in chann)
        {
                ch = copy(channels[s]);
                if( !pointerp(tuned_ch) || !sizeof(tuned_ch) ) state=HIG"�ر�";
                else if(member_array(s,tuned_ch)==-1) state=GRN"�ر�";
                else if( query("chann/"+s, me))state=HIC"������";
                else state=HIY"��������";
                str+=sprintf(WHT"[%-10s]       [%-8s]        %-8s\n",s,ch->msg,state);
        }
        str+="\n"HIC"��"HIY"������������������������������������������������������������"HIC"��\n"NOR;
        str+="����������("HIY"help"NOR"��������"HIY"exit"NOR"�˳�)��";
        write(str);
        input_to( (: do_chan :) ,me);
        return 1;
}


void open_ch(object me,string arg)
{
        class channel_class ch; 
        mapping channels = fetch_variable("channels", get_object(CHANNEL_D)); 
        int my_channels = query("channels", me);
        
        if( undefinedp(ch = channels[arg]) || !classp(ch) ) 
                return;
        
        set("channels", my_channels | ch->number, me); 
        CHANNEL_D->register_channel(me, ch->number); 
}

int do_chan(string arg,object me,int once)
{
        string ch,cmd;
        int tmp;
        
        if(!arg)
        {
                write("\n����������("HIY"help"NOR"��������"HIY"exit"NOR"�˳�)��");
                input_to( (: do_chan :) ,me);
                return 1;
        }               
        arg=lower_case(arg);
        arg=me->remove_leading_space(arg);
        while(strsrch(arg,"  ")!=-1) arg=replace_string(arg,"  "," ");
        switch(arg)
        {
                case "?":
                case "help":
                        //��ʾ������Ϣ
                        write(HIG+cmdhelp+NOR);
                        break;
                case "q":
                case "quit":
                case "exit":
                        write(HIG"�˳�Ƶ�����ó��򡣡���\n"NOR);
                        once=1;break;
                default:
                        //���г�����
                        tmp=0;
                        if(sscanf(arg,"%s %s",ch,cmd)==2)
                        {
                                switch(cmd)
                                {
                                        case "public":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        open_ch(me,ch);
                                                        delete("chann/"+ch, me);
                                                        write(HIG"�����" + channels[ch]["name"] + "Ƶ����\n"NOR);
                                                }
                                                else write(HIG"Ƶ������û��"+HIY+"ch"+HIG+"���Ƶ����\n"NOR);
                                                break;
                                        case "main":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        open_ch(me,ch);
                                                        set("chann/"+ch, 1, me);
                                                        write(HIG"�����" + channels[ch]["name"] + "Ƶ����\n"NOR);
                                                }
                                                else write(HIG"Ƶ������û��"+HIY+"ch"+HIG+"���Ƶ����\n"NOR);
                                                break;
                                        case "none":
                                                if(member_array(ch,chann)!=-1)
                                                {
                                                        set("channels",query("channels",  me)-({ch}), me);
                                                        write(HIG"��ر���" + channels[ch]["name"] + "Ƶ����\n"NOR);
                                                }
                                                else write(HIG"Ƶ������û��"+HIY+"ch"+HIG+"���Ƶ����\n"NOR);
                                                break;
                                        default:
                                                tmp=1;
                                }
                        }
                        else tmp=1;
                        if(tmp)
                                write(HIG+cmdhelp+NOR);
        }
        if(!once) show_main(me);
        return 1;
}

int help()
{
        write(@HELP
ָ���ʽ : chann                         (�˵�ģʽ)
           chann    <���>             (ֱ��ָ��)

���ָ�����������������Ƶ����Ϣ����ʾ���رջ�����ʾλ�á�
��ʾλ����main�������ڣ���public��������Ϣ���ڣ�����ѡ��
���λ������Ϊû�У�none�������ʾҪ�رո�Ƶ����

�����ʽΪ��<Ƶ��> < main | public | none>
Ƶ��Ϊ��Ҫ���в�����Ƶ�����ƣ�������ŵ���none��ʾҪ�رո�
Ƶ��������main��ʾҪ��Ƶ��������Ϣ��ʾ�������򴰿ڣ����
��public����ʾ��������Ϣ���򴰿ڡ�

ֱ��ָ��������ģʽ���ӣ�
chann chat none    ���� �˲���Ϊ��chatƵ���ر�
chann chat main    ���� �˲�������chatƵ������ʾ��������
chann rumor public ���� �˲������ڹ������ڴ�rumorƵ��
HELP );
    return 1;
}

