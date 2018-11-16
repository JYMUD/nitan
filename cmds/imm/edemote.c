
#include <ansi.h>
#include <emotion.h>

inherit F_CLEAN_UP;

string help = @HELP
����ָ��༭��

edemote '����ָ��'	- �༭����ָ��
edemote -d '����ָ��'	- ɾ������ָ��

HELP;


int help(object me) 
{
        write(help);
        return 1;
}
private int valid_emote_name(string emotion)
{
	return strsrch(emotion, " ") == -1;
}

private void choose_option(object me, string emotion, mapping modifying_emotion, string arg);
private void setup_emotion(object me, string emotion, mapping modifying_info, int option, string contiune_arg, string arg);

private string replace_keys(string description)
{
	if( !description ) return "��δ�趨";
	
	description = replace_string(description, "$ME", 	HIC"��"NOR);
	description = replace_string(description, "$YOU", 	HIG"ĳ��"NOR);
	description = replace_string(description, "$T", 	HIM"����"NOR);
	
	return description;
}
private string emotion_detail_description(string emotion, mixed info)
{
	string msg = "���� ���� "HIY+emotion+NOR+" ֮��ϸ�������£�"+repeat_string("��", 13-(strlen(emotion)/2))+"\n";
	
	msg += NOR WHT"1.�޶����޸�������    ��"NOR+replace_keys(info[NONE_ALL])+"\n";
	msg += NOR WHT"2.�޶����и�������    ��"NOR+replace_keys(info[NONE_ALL_ARG])+"\n";
	msg += NOR WHT"3.����Ϊ�Լ��޸������֣�"NOR+replace_keys(info[ME_ALL])+"\n";
	msg += NOR WHT"4.����Ϊ�Լ��и������֣�"NOR+replace_keys(info[ME_ALL_ARG])+"\n";
	msg += NOR WHT"5.����Ϊĳ���޸������֣�"NOR+replace_keys(info[YOU_ALL])+"\n";
	msg += NOR WHT"6.����Ϊĳ���и������֣�"NOR+replace_keys(info[YOU_ALL_ARG])+"\n";
	msg += NOR WHT"7.����ע��            ��"NOR+(info[NOTE] || "��δ�趨")+"\n";
	msg += NOR WHT"8.ʹ�ô���            ��"NOR+info[USE]+" ��\n";
	msg += "������������������������������������������������������\n";
	return msg;
}

private void confirm_delete_emotion(object me, string emotion, string arg)
{
	if( lower_case(arg) == "y" )
	{
		if( EMOTE_D->delete_emotion(emotion) )
			tell(me, "ɾ������ָ�� "+emotion+" �ɹ���\n");
		else
			tell(me, "ɾ��ʧ�ܣ���֪ͨ��ʦ����\n");

		return me->finish_input();
	}
	else
	{
		tell(me, "ȡ��ɾ����\n");
		return me->finish_input();
	}
}

private void setup_emotion(object me, string emotion, mapping modifying_info, int option, string multi_line_arg, string arg)
{
	if( !arg || !arg[0] )
	{
		multi_line_arg += "\n";
		tell(me, ">");
		input_to( (: setup_emotion, me, emotion, modifying_info, option, multi_line_arg :) );
	}
	
	switch(arg)
	{
		case "cancel":
			tell(me, "ȡ������������\n"+emotion_detail_description(emotion, modifying_info)+"���������趨֮��Ŀ(�趨��� save, ȡ���趨 exit)��\n>");
			input_to( (: choose_option, me, emotion, modifying_info :) );
			break;
		
		case ".":
			// ��ѻ�����
			if(multi_line_arg[<1..] == "\n") multi_line_arg = multi_line_arg[0..<2];
			multi_line_arg = kill_repeat_ansi(trim(ansi(multi_line_arg)) + NOR);
			modifying_info[option-1] = multi_line_arg;
			
			tell(me, "�趨��ϡ�\n"+emotion_detail_description(emotion, modifying_info)+"���������趨֮��Ŀ(�趨��� save, ȡ���趨 exit)��\n>");
			input_to( (: choose_option, me, emotion, modifying_info :) );
			break;
		default:
			multi_line_arg += arg+"\n";
			tell(me, ">");
			input_to( (: setup_emotion, me, emotion, modifying_info, option, multi_line_arg :) );
	}
}
	
private void choose_option(object me, string emotion, mapping modifying_info, string arg)
{
	int option;
	
	switch(arg)
	{
		case "save":
			if( sizeof(modifying_info) != 8 )
			{
				tell(me, "�����趨�����б����������ܴ����趨��\n���������趨֮��Ŀ(�趨��� save, ȡ���趨 exit)��\n>");
				input_to( (: choose_option, me, emotion, modifying_info :) );
				return;
			}
			else
			{
				array info = allocate(0);
				
				for(int i=0;i<8;i++)
					info += ({ modifying_info[i] });
					
				if( EMOTE_D->set_emotion(emotion, info) )
				{
					tell(me, "����ָ�� "+emotion+" �趨����ɹ���\n");
				}
				else
					tell(me, "����ָ�� "+emotion+" �趨����ʧ�ܡ�\n");
					
				return me->finish_input();
			}
			break;
			
		case "exit":
			tell(me, "ȡ���� "+emotion+" ����ָ����趨��\n");
			return me->finish_input();
			
		default:break;
	}
	
	option = to_int(arg);
	
	if( option > 8 || option < 1 )
	{
		tell(me, "û�����ѡ�\n���������趨֮��Ŀ(�趨��� save, ȡ���趨 exit)��\n>");
		input_to( (: choose_option, me, emotion, modifying_info :) );
	}
	else if( option == USE+1 ) 
	{
		tell(me, "���ѡ���޷�ʹ���ֶ��趨��\n���������趨֮��Ŀ(�趨��� save, ȡ���趨 exit)��\n>");
		input_to( (: choose_option, me, emotion, modifying_info :) );
	}
	else
	{
		tell(me, "\n�� ENTER �ɳ���������У����� '.' ���������� 'cancel' ȡ����\n�������׼��ʽ���� "HIC"$ME(�����Լ�) "HIG"$YOU(�������) "HIY"$T(����������)"NOR"��\n>");
		input_to( (: setup_emotion, me, emotion, modifying_info, option, "" :) );
	}
}
	
int main(object me, string arg)
{
	string *info;
	mapping modifying_info = allocate_mapping(8);
	
        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;


	if( !arg ) { 
		tell(me, pnoun(2, me)+"��Ҫ���ӻ��޸��ĸ�����ָ�\n"); 
		return 1;
	}
	
	arg = remove_ansi(arg);
	
	if( sscanf(arg, "-d %s", arg) == 1 )
	{
		if( !arrayp(info = EMOTE_D->query_emotion(arg)) ) {
			tell(me, "û�� "+arg+" �������ָ�\n");
			return 1;
		}
		
		tell(me, emotion_detail_description(arg, info)+"ȷ���Ƿ�ɾ�� "+arg+" ����ָ��(Yes/No)��");
		input_to( (: confirm_delete_emotion, me, arg :) );
		return 1;
	}
		
	if( arrayp(info = EMOTE_D->query_emotion(arg)) )
	{
		for(int i=0;i<8;i++)
			modifying_info[i] = info[i];
	}
	else
	{
		if( !valid_emote_name(arg) ) {
			tell(me, "���Ϸ��ı���ָ�����ơ�\n");
			return 1;
		}
			
		modifying_info[NOTE] = 0;
		modifying_info[USE] = 0;
	}
		
	tell(me, emotion_detail_description(arg, modifying_info)+"���������趨֮��Ŀ(�趨��� save, ȡ���趨 exit)��\n>");
	input_to( (: choose_option, me, arg, modifying_info :) );
	return 1;
}
