// This program is a part of NT MudLIB

#include <i2d.h>
#include <message.h>
#include <ansi.h>
inherit F_CLEAN_UP;


#define I2D "/adm/daemons/intermud2_d.c"

//object I2D=load_object(I2D);

nosave mixed *current_status=({ ({}),({"$GRN$GB$NOR$",GB_CODE}),({"$RED$AD$NOR$",ANTI_AD}),({"$BLU$Ig$NOR$",IGNORED}),({}),({}),({"$GRN$GB$NOR$",GB_CODE}),({"$RED$AD$NOR$",ANTI_AD}),({"$BLU$Ig$NOR$",IGNORED}) });

void select_mud(int funct,int si,string *mud,string x)
{
        int input;
        string mudname;


        if( stringp(x) && x[0]=='q' )
        {
                tell(this_player(), "�뿪��\n", CMDMSG);
                return;
        }

        if( !sscanf(x,"%d",input) || input<0 || input > si )
        {
                tell(this_player(), "���Ϸ������룬���������룺\n", CMDMSG);
                input_to((: select_mud,funct,si,mud :));
                return;
        }
        mudname=mud[input];
        switch(funct)
        {
                case 1:if(I2D->set_status(mudname,GB_CODE)) tell(this_player(), "��ɡ�\n", CMDMSG);return;
                case 2:if(I2D->set_status(mudname,ANTI_AD)) tell(this_player(), "��ɡ�\n", CMDMSG);return;
                case 3:if(I2D->set_status(mudname,IGNORED)) tell(this_player(), "��ɡ�\n", CMDMSG);return;
                case 6:if(I2D->set_status(mudname,-GB_CODE)) tell(this_player(), "��ɡ�\n", CMDMSG);return;
                case 7:if(I2D->set_status(mudname,-ANTI_AD)) tell(this_player(), "��ɡ�\n", CMDMSG);return;
                case 8:if(I2D->set_status(mudname,-IGNORED)) tell(this_player(), "��ɡ�\n", CMDMSG);return;
        }

}

string test_status(string name,int status)
{
        if( I2D->fetch_data(name)["STATUS"] & status )
                return HIG"ENABLE"NOR;
        else return HIR"DISABLE"NOR;
}

void get_mud_name(int funct,string name)
{
        int si,i;
        string *mud;


        if( stringp(name) && name[0]=='q' )
        {
                tell(this_player(), "�뿪��\n", CMDMSG);
                return;
        }

        if( !sizeof(mud=I2D->fetch_mudname(name)) )
        {
                tell(this_player(), "��Ǹ���Ҳ���վ̨�����������롣\n", CMDMSG);
                input_to((: get_mud_name,funct :));
                return;
        }
        //if( si=sizeof(mud)==1)
        //for(int i=0;i<=si;i++)
        //        printf("[%2d]\t\t%s\n",i,mud[i]);
        si=sizeof(mud);
        if( si == 1 )
        {
                select_mud(funct,si,mud,"0");
                return;
        }
        foreach(string x in mud)
        {
                //tell(this_player(),sprintf("[%4d] %s\n",i,x));
                tell(this_player(),sprintf("[%4d] %s %s[%s]\n",i,x,ansi(current_status[funct][0]),test_status(x,current_status[funct][1])));
                i++;
        }
        tell(this_player(), "��ѡ�� 0~"+(si-1), CMDMSG);
        input_to((: select_mud,funct,si,mud :));
        return;
}

void get_mud_ip(int funct,string name)
{
        int si,i;
        string *mud;


        if( stringp(name) && name[0]=='q' )
        {
                tell(this_player(), "�뿪��\n", CMDMSG);
                return;
        }

        if( !sizeof(mud=I2D->fetch_mudip(name)) )
        {
                tell(this_player(), "��Ǹ���Ҳ���վ̨�����������롣\n", CMDMSG);
                input_to((: get_mud_ip,funct :));
                return;
        }
// fetch mud by ip
        si=sizeof(mud);
        if( si == 1 )
        {
                select_mud(funct,si,mud,"0");
                return;
        }
        foreach(string x in mud)
        {
                tell(this_player(),sprintf("[%4d] %s %s[%s]\n",i,x,ansi(current_status[funct][0]),test_status(x,current_status[funct][1])));
                i++;
        }
        tell(this_player(), "��ѡ�� 0~"+(si-1), CMDMSG);
        input_to((: select_mud,funct,si,mud :));
        return;


}
void select_target_way(int funct,string x)
{
        int *num=({1,2}),input;


        if(stringp(x) && x[0]=='q' )
        {
                tell(this_player(), "�뿪��\n", CMDMSG);
                return;
        }

        if( !sscanf(x,"%d",input) || member_array(input,num)==-1 )
        {
                tell(this_player(), "������[ 1~2 ] �����֣�\n", CMDMSG);
                input_to((: select_target_way,funct :));
                return;
        }

        switch(input)
        {
                case  1:tell(this_player(), "������վ̨���ƣ�\n", CMDMSG);
                        input_to((: get_mud_name,funct :));
                        return;
                case  2:
                        tell(this_player(), "������վ̨ 'IP:PORT'��\n", CMDMSG);
                        input_to((: get_mud_ip,funct :));
                        return;
        }
        return;
}

void add_mud_list(string name)
{
        string address;
        int port;

        if( stringp(name) && name[0]=='q' )
        {
                tell(this_player(), "�뿪��\n", CMDMSG);
                return;
        }

        if( sizeof(I2D->fetch_mudip(name)) )
        {
                tell(this_player(), "��Ǹ���Ѿ������վ̨�����������롣\n", CMDMSG);
                input_to((: add_mud_list :));
                return;
        }

        if( sscanf(name, "%s:%d", address, port) != 2 )
        {
                tell(this_player(), "��Ǹ����ʽ���ԣ����������롣\n", CMDMSG);
                input_to((: add_mud_list :));
                return;
        }
        I2D->add_incoming_mudlist(address, port);
        tell(this_player(), "������վ̨�ɹ���\n", CMDMSG);
        return;
}

void select_main_menu(string x)
{
        int *num=({1,2,3,5,6,7,8,9}),input;

        if(stringp(x) && x[0]=='q' )
        {
                tell(this_player(), "�뿪��\n", CMDMSG);
                return;
        }

        if( !sscanf(x,"%d",input) || member_array(input,num)==-1 )
        {
                tell(this_player(), "������[ 1~3,5~9 ] �����֣�\n", CMDMSG);
                input_to((: select_main_menu :));
                return;
        }
        if( input==5)
        {
                tell(this_player(), "������վ̨ 'IP:PORT'��\n", CMDMSG);
                input_to((: add_mud_list :));
                return;
        }
        if( input==9)
        {
                if( fetch_variable("debug",find_object(I2D))==1 )
                {
                        I2D->debug();
                        tell(this_player(), "�����ܹرա�\n", CMDMSG);
                        return;
                } else {
                        I2D->debug();
                        tell(this_player(), "�����ܿ�����\n", CMDMSG);
                        return;
                }
        }
        tell(this_player(), "1.�ֶ�����վ̨����\n2.�ֶ����� IP λַ\n\n", CMDMSG);
        switch(input)
        {
                case  1:tell(this_player(), "��ѡ���������� #ת��# ���ܵ�վ̨���뷽ʽ��\n", CMDMSG);
                        input_to((: select_target_way,1 :));break;
                case  2:tell(this_player(), "��ѡ���������� #���# ���ܵ�վ̨���뷽ʽ��\n", CMDMSG);
                        input_to((: select_target_way,2 :));break;
                case  3:tell(this_player(), "��ѡ���������� #����# ���ܵ�վ̨���뷽ʽ��\n", CMDMSG);
                        input_to((: select_target_way,3 :));break;
                case  6:tell(this_player(), "��ѡ�������� #ת��# ���ܵ�վ̨���뷽ʽ��\n", CMDMSG);
                        input_to((: select_target_way,6 :));break;
                case  7:tell(this_player(), "��ѡ�������� #���# ���ܵ�վ̨���뷽ʽ��\n", CMDMSG);
                        input_to((: select_target_way,7 :));break;
                case  8:tell(this_player(), "��ѡ�������� #����# ���ܵ�վ̨���뷽ʽ��\n", CMDMSG);
                        input_to((: select_target_way,8 :));break;

        }
        return;
}

int main(object me, string arg)
{
        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if( !arg )
        {
                tell(me, "��ӭʹ�� Intermud2 Daemon Tool ����\n", CMDMSG);
                tell(me, "��������ʹ�õ���Ŀ��\n"+@ITEM
[1]. ���� #ת��# ���ܵ�ĳվ( BIG5 <-> GB �以ת )
[2]. ���� #���# ���ܵ�ĳվ( ����վ����Ƶ��ѶϢת�� AD Channel )
[3]. ���� #����# ���ܵ�ĳվ( �������и�վ�����Ķ��� )
[4]--(����)
[5]. ����ĳվ�� mudlist
[6]. ���ĳվ�� #ת��# ����
[7]. ���ĳվ�� #���# ����
[8]. ���ĳվ�� #����# ����
[9]. �����ܱ��( DEBUG Mode On/Off )
[q]. �뿪��
������[ 1~3,5~9 ] �����֣�
ITEM, CMDMSG);
                input_to((: select_main_menu :));
                return 1;
        }
}
