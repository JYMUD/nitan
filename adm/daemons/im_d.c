/* *********************�W·���rͨӍϵ�y***********************
*  
*                                                  By Whatup *
*                                               
* �x��
:whatup_!whatup@mail2000.com.tw QUIT :Leaving...
�Ͼ�
:whatup_!whatup@mail2000.com.tw JOIN :&bitlbee
    :root!root@localhost.localdomain PRIVMSG &bitlbee :Question on MSN connection (handle yukang.tw@yahoo.com.tw):
    :root!root@localhost.localdomain PRIVMSG &bitlbee :The user whatup.tw@gmail.com (�T��-Ҩ��) wants to add you to his/her buddy list. Do you want to allow this?
    :root!root@localhost.localdomain PRIVMSG &bitlbee :You can use the yes/no commands to answer this question.

*                                     ==δ��ͬ�⣬��������==  *
*               ���������� �޸İ� 2001�ꡣ
*               ���������У���������15���MUD��pkuxkx.net
**************************************************************/

/* ���^����n */
#include <ansi.h>
/* ���e�O�� */
//#include <debug.h>
#include <net/socket.h>
#include <socket_err.h>
#include <runtime_config.h>

#define IM_D "/adm/daemons/im_d.c"
#define CH_D "/adm/daemons/channeld.c"
#define PING_TIME 240

#define TELL(x) log_file("im",x);
#define BITLBEE_SERVER "127.0.0.1 6667"
#define DEBUG 1
inherit F_DBASE;

/* ��ʼ�O�� */
private mapping users=([]);

private int process_identify(object me,string pass);
void process_who(int fd,string str);
protected void close_socket(int fd);
varargs void send_who(int fd,string id);
void send_ping();
void auto_login();
void auto_login1();

/* �n�����n */
void create()
{
	set("channel_id", "QQ����");
	seteuid(getuid());
#ifdef DEBUG
    TELL(sprintf("[%s]��ʼ��ɡ�",ctime(time()) ));
#endif 
    call_out((:send_ping:),PING_TIME);
    call_out("auto_login",1);
}

void send_ping()
{
    foreach(int fd,mapping m in users)
    {
        socket_write(fd,"PING\r\n");
    }
    call_out((:send_ping:),PING_TIME);

}
void remove()
{
    foreach(int fd,mapping m in users)
    {
        if(m["obj"])
        tell_object(m["obj"],"���¸��� im ϵ�y��Ո���µ��롣\n");
        socket_write(fd,"QUIT\r\n");
        socket_close(fd);
    }
}
void reset()
{
	foreach(int fd,mapping m in users)
	{
		if(!m["obj"]) {
			close_socket(fd);			
			map_delete(users,fd);
		}
	}
}
/* �_ʼ���� */
void login_irc(object user)
{
    int err,fd;
    string id;
    id = "account";
    if(!id)
    {
        tell_object(user,"��]�е��� ID ");
        return ;
    }
    fd = socket_create(STREAM, "read_callback","close_socket");
    if ( fd < 0 )
    {
        tell_object(user,"�B�Yʧ�������������C�]���_�����ǾW·�o���B����");
        return;
    }
    users[fd] = allocate_mapping(5);
    users[fd]["id"] = id;
    users[fd]["steps"]   = 0;
    users[fd]["obj"]   = user;
    users[fd]["list"] = allocate_mapping(1);
    user->set_temp("im_fd",fd);

    err = socket_connect(fd,BITLBEE_SERVER,"read_callback","write_callback" );
    if( err==EESUCCESS )
    {
#ifdef DEBUG
    TELL(sprintf("[%s] %s �ɹ����� Socket ,�_ʼ�ʂ���� irc.fd = %d\n",
         ctime(time()) ,id,fd));
#endif 
    }
    else
    {
#ifdef DEBUG
    TELL(sprintf("[%s]���� Socket ʧ��,�o�����B�Y�W·���C.\n",
         ctime(time()) ));
#endif 
        return ;
    }
    call_out((:process_identify:),3,user,crypt(id,id)[0..10]);
    return;
}
private int process_identify(object me,string pass)
{
    string str;
    int fd = me->query_temp("im_fd");
    if( fd < -1 ) 
    {
        tell_object(me,"[IM Message]:�B��ʧ����Ո������ԇ��\n");
        return 1;
    }
    if(users[fd]["obj"] == me)
    {
            str = sprintf("USER %s %s %s :%s\r\n",users[fd]["id"],
                          users[fd]["id"],query_ip_name(users[fd]["obj"]),
                          users[fd]["obj"]->query("name"));
            socket_write(fd,str);
        socket_write(fd,"PRIVMSG &bitlbee :identify "+pass+"\r\n");
    }
}

protected void write_callback(int fd)
{
    socket_write(fd,"NICK "+users[fd]["id"]+"\r\n");
    
    return ;
}
protected void read_callback(int fd,mixed message)
{
    string str,msg1;
    string *str1;
#ifdef DEBUG
            str = sprintf("PRIVMSG &bitlbee :set charset 'gb2312'\r\n");
    TELL(sprintf("[%s] %d,%s\n",
         ctime(time()),fd,message ));
#endif DEBUG
    if(regexp(message ,"PING :PinglBee") ) //PING :PinglBee
    {
        socket_write(fd,"PONG\r\n");
    } 

    switch(users[fd]["steps"])
    {
        case 0:
            str = sprintf("USER %s %s %s :%s\r\n",users[fd]["id"],
                          users[fd]["id"],query_ip_name(users[fd]["obj"]),
                          users[fd]["obj"]->query("name"));
            socket_write(fd,str);
        break;
        case 1:
            str = sprintf("JOIN &bitlbee\r\n");
            socket_write(fd,str);
        break;
        case 2:
            str = sprintf("MODE &bitlbee\r\n");
            socket_write(fd,str);
        break;
        case 3:
            str = sprintf("WHO &bitlbee\r\n");
            socket_write(fd,str);
//	            str = sprintf("PRIVMSG &bitlbee :set charset 'gb2312'\r\n");
//            socket_write(fd,str);
        break;
        default:
            
            {
                string name,mail,msg,id;
                //:whatup_!whatup@mail2000.com.tw PRIVMSG &bitlbee :whatup: test
                foreach(string m in explode(message,"\n")) 
                { 
		    m = replace_string(m,"&bitlbee :","");
		    m = replace_string(m,"account :","account:");
                    if(sscanf(m,":%s!%s PRIVMSG account:%s",name,mail,msg) == 3 )
                    {
                        //:root!root@localhost.localdomain PRIVMSG &bitlbee :The user whatup.tw@gmail.com (�T��-Ҩ��) wants to add you to his/her buddy list. Do you want to allow this?
                        if(sscanf(msg,"The user %s wants to add you to his/her buddy list. Do you want to allow this?",mail) == 1)
                        {
                            tell_object(users[fd]["obj"],"\n[IM Message]:"+mail+"��Ҫ����������ĺ������Σ�ͬ���Ԓ�� im yes����ͬ���Ԓ���� im no��\n");
                        }
                        else  if( sscanf(msg,"%s:%s",id,msg1) == 2 || sscanf(msg,"%s] %s",id,msg1) == 2 )
                            {
                            	//ȥ������Ҫ��ת��ǰ׺
                            	msg = replace_string(msg,"������Ϣת�� (744093028): ","");
                            	msg = replace_string(msg,"��Ϣת�� (739663638): ","");
                            	msg = replace_string(msg,"��Ϣת�� (1064453141)",BLU+"��Ϣ������QQȺ");
                            	//���˺��зǷ��ַ��ı���
                            	if ((strsrch(msg,"/:o")==-1)&&(strsrch(msg,"xiaoi.com")==-1)) {
	                            	if (strsrch(msg,"[img]")!=-1)
	                            	{
	                            		str1 = explode(msg,"img]");
	                            		msg = str1[0]+"�Զ���ͼƬ]";
	                            	}
	                            	msg = replace_string(msg,"): chat","):chat");
	                            	msg = replace_string(msg,"] chat","):chat");
	                            	if (strsrch(msg,"):chat ")!=-1)
	                            	{
	                            		str1 = explode(msg,"):chat ");
	                            		msg = str1[0] + "):" + str1[1];
	                            		CH_D->do_channel(this_object(),"chat",msg);
	                            	} else 	
		                            	if (strsrch(msg,"):chat* ")!=-1)
		                            	{
		                            		str1 = explode(msg,"):chat* ");
		                            		this_object()->set("name",str1[0]+")");
		                            		msg = str1[1];
		                            		CH_D->do_channel(this_object(),"chat*",msg[0..sizeof(msg)-2],1);
		                            	} else 	
			                            	if (replace_string(msg," ","")!="") 
			                            		CH_D->do_channel(this_object(),"qq",msg);
			                   }
                            }
                        else 
                        switch(msg)
                        { 
                            case "The nick is (probably) not registered":
                                TELL("\n[IM Message]:��һ��ʹ��ԓ���`���Ԅ��]�Ԏ�̖��\n");
                                socket_write(fd,"PRIVMSG &bitlbee :register "+crypt(users[fd]["id"],users[fd]["id"])[0..10]+"\r\n");
                                break;
                            case "Incorrect password":
                                TELL("\n[IM Message]:�����ܴa�e�`(Ո֪ͨϵ�y����T)��\n");
                                break;
                            case "YAHOO - Login error: Error 99 (Logged in on a different machine or device)":
                                tell_object(users[fd]["obj"],"\n[IM Message]:������������X���� YAHOO��\n");
                                break;
                            case "MSN - Logged out: Someone else logged in with your account":
                                TELL("\n[IM Message]:������������X���� MSN ��\n");
                                break;
                            case "YAHOO - Signing off..":
                                tell_object(users[fd]["obj"],"\n[IM Message]:��ǳ� YAHOO ��\n");
                                break;
                            case "MSN - Signing off..":
                                TELL("\n[IM Message]:��ǳ� MSN ��\n");
                                //remove_call_out("auto_login1");
								//call_out("auto_login1",60);
                                break;
//                            case "MSN - Logging in: Authenticated, getting buddy list":
                            case ":root!root@localhost PRIVMSG &bitlbee :msn(account) - Logging in: Logged in":
                                TELL("\n[IM Message]:MSN ����ɹ���\n");
                                break;
                            case "YAHOO - Logged in":
                                tell_object(users[fd]["obj"],"\n[IM Message]:YAHOO ����ɹ���\n");
                                break;
                            case "No accounts known. Use 'account add' to add one.":
                                tell_object(users[fd]["obj"],"\n[IM Message]:Ոʹ�� im register msn ���� im register yahoo �]�Ԏ�̖��\n");
                                break;
                            case "MSN - Login error: Error during Passport authentication":
                                tell_object(users[fd]["obj"],"\n[IM Message]:MSN�ܴa�e�`��\n");
                                break;
                            default:
                        }
                    }
                    
                    // ��վӍϢ :paiting!paiting@hotmail.com JOIN :&bitlbee
                    if(sscanf(m,":%s!%s JOIN :&bitlbee",id,name) == 2)
                    {
                        send_who(fd,id);
                        TELL(sprintf("[IM Message]:%s������ ��",id));
    					socket_write(fd,"set charset 'gb2312'\r\n");
    					socket_write(fd,"PRIVMSG &bitlbee :set charset 'gb2312'\r\n");
			CH_D->register_relay_channel("qq");
                        continue;
                    }
                    // ��վӍϢ :paiting!paiting@hotmail.com QUIT :Leaving...
                    if(sscanf(m,":%s!%s QUIT :Leaving...",id,name) == 2)
                    {
                        map_delete(users[fd]["list"],id);
                        TELL(sprintf("[IM Message]:%s������ ��",id));
                        continue;
                    }
                    // ��r׃���� :root!root@rw.twku.net MODE &bitlbee +v paiting
                    if(sscanf(m,":root!root@rw.twku.net MODE &bitlbee +v %s",id) == 1)
                    {
                        send_who(fd,id);
                        continue;
                    }
                    // ��r׃away��æ� :root!root@rw.twku.net MODE &bitlbee -v paiting
                    if(sscanf(m,":root!root@rw.twku.net MODE &bitlbee -v %s",id) == 1)
                    {
                        send_who(fd,id);
                        continue;
                    }
                    if(sscanf(m,":%*s 352 %*s %*s %*s %*s %*s %*s %*s :%*d %*s") == 10) 
                    {
                        process_who(fd,m);
                    } else 
                    if(sscanf(m,":%*s 352 %*s &bitlbee %*s %*s %*s %*s %*s :%*d %*s") == 9) 
                    {
                        process_who(fd,m);
                    }

                    
                }
            }
    }
    users[fd]["steps"]++;   
}
#ifdef DEBUG1
void socket_write(int fd,mixed message)
{
    int i;
    TELL(sprintf(HIR"[%s] %d,%s\n"NOR,
         ctime(time()),fd,message ));
//    i = efun::socket_write(fd,message);
    switch(i)
    {
        case EEFDRANGE:       TELL("����ֵ (descriptor) ����������"); break;
        case EEBADF:          TELL("�oЧ������ֵ��"); break;
        case EESECURITY:      TELL("��D�`����ȫ��"); break;
        case EENOADDR:        TELL("socket δָ��λַ��"); break;
        case EEBADADDR:       TELL("λַ��ʽ�Ć��}��"); break;
        case EENOTCONN:       TELL("socket ��δ�B�ӡ�"); break;
        case EEALREADY:       TELL("���������M���С�"); break;
        case EETYPENOTSUPP:   TELL("��֧Ԯ������͑B��"); break;
//        case EEBADDATA:       TELL("�ͳ����Y�Ϻ���̫�ೲ��Ӵ� (nested level)��"); break;
        case EESENDTO:        TELL("sendto �Ć��}��"); break;
        case EEMODENOTSUPP:   TELL("��֧Ԯ�� socket �͑B��"); break;
        case EEWOULDBLOCK:    TELL("��������ͣ�� (block)��"); break;
        case EESEND:          TELL("�ͳ� (send) �Ć��}��"); break;
        case EECALLBACK:      TELL("�ȴ��غ� (callback) �С�"); break;
        default:

    }
}
#endif

protected void close_socket(int fd)
{
    if(users[fd]["obj"])
        users[fd]["obj"]->delete_temp("im_fd");

    map_delete(users,fd);
    socket_close(fd);
#ifdef DEBUG
    TELL(sprintf("[%s] %d,�B���Y��\n",
         ctime(time()),fd ));
#endif
}

void send_command(int fd,mixed message)
{
//		socket_write(fd,"PRIVMSG &bitlbee :set charset 'utf-8'\r\n");	
    socket_write(fd,message+"\r\n");
//		socket_write(fd,"PRIVMSG &bitlbee :set charset 'gb2312'\r\n");	
#ifdef DEBUG    
    TELL(sprintf("[%s] %d,%s\n",
         ctime(time()),fd,message ));
#endif
}
// ̎�� irc ����ʹ����
varargs void send_who(int fd,string id)
{
    if(undefinedp(id))   socket_write(fd,"WHO &bitlbee\r\n");
    else    socket_write(fd,"WHO "+id+"\r\n");

}
void process_who(int fd,string str)
{
    string id,ip,status,nick,name;
    //:rw.twku.net 352 whatup &bitlbee whatup 218-184-22-55.cm.dynamic.apol.com.tw rw.twku.net whatup H :0 С����
    if(sscanf(str,":%*s 352 %*s &bitlbee %s %s %*s %s %s :%*d %s",
       id,ip,name,status,nick) == 9) 
    users[fd]["list"][name] = ({ id,ip,name,status,nick});
    //:rw.twku.net 352 whatup whatup_ whatup mail2000.com.tw rw.twku.net whatup_ H :0 �~��-���lҪ gmail ��̖������һ��-.
    //:%*s 352 %*s %*s %s %s %*s %s %s :%*d %*s
    if(sscanf(str,":%*s 352 %*s %*s %s %s %*s %s %s :%*d %s",
       id,ip,name,status,nick) == 10) 
        users[fd]["list"][name] = ({ id,ip,name,status,nick});
}

int process_send_msg(object me,string who,string msg)
{
    int fd = me->query_temp("im_fd");
	msg = replace_string(msg,"\n"," ");
#ifdef DEBUG
    TELL("PRIVMSG &bitlbee :"+ who + ":"+msg+"\r\n" );
#endif	
    if(undefinedp(users[fd]) ||
       undefinedp(users[fd]["list"][who]))
        return notify_fail("[IM Message] ���rӍϢ�ϵĺ������Λ]���@���ˣ�\n");
//	socket_write(fd,"PRIVMSG &bitlbee :set charset 'utf-8'\r\n");	
    socket_write(fd,"PRIVMSG &bitlbee :"+ who + ":"+msg+"\r\n");
//		socket_write(fd,"PRIVMSG &bitlbee :set charset 'gb2312'\r\n");	
    {
        string *n = users[fd]["list"][who];
        if (n[4]&&n[0]&&n[1])
        	tell_object(me,sprintf(HIW HBBLU"���ü��rӍϢ���o %s : %s\n"NOR,
            	      n[4]+"("+n[0]+"@"+n[1]+")\n["+who+"]",msg));
    }
    return 1;
}
int del_account(int fd,string protocol) 
{
        // Ҫ���x�������܄h��
        socket_write(fd,"PRIVMSG &bitlbee :account off "+protocol+"\r\n");
        socket_write(fd,"PRIVMSG &bitlbee :account del "+protocol+"\r\n");
}
int register_account(int fd,string protocol,string account,string passwd)
{
    socket_write(fd,"PRIVMSG &bitlbee :account add "+protocol+" "+account+" "+passwd+"\r\n");
    socket_write(fd,"PRIVMSG &bitlbee :account on "+protocol+"\r\n");
}
mapping query_users(){ return users; }

void auto_login()
{
	object me = this_object();


		
        if(me->query_temp("im_fd") && query_users()[me->query_temp("im_fd")]["obj"] == me)
        {
//            TELL("[IM Message]:�����ڵ����У�Ո�� im quit �x����");
//            return;
				close_socket(me->query_temp("im_fd"));
        }
        TELL("[IM Message]:��ʼ��¼����irc��������");
        login_irc(me);
        call_out("auto_login1",5);
        return;
}

void auto_login1()
{
	object me = this_object();

    del_account(me->query_temp("im_fd"),"msn");
    register_account(me->query_temp("im_fd"),"msn","msn_acount","msn_passwd");
    TELL("[IM Message] MSN�ʺ������ϡ�\n");
	return;
}

void relay_channel(object ob, string channel, string msg)
{
        string who, phrase;

        if( !userp(ob) || (channel != "qq") ) return;
        if (strsrch(msg,WHT+NOR)==-1)	//chat, not emote
        	msg = ob->name()+"("+capitalize(ob->query("id"))+"):"+msg;
        
        msg = COLOR_D->uncolor(msg);
		process_send_msg(this_object(),"mud",msg);
		return;
}

string name() {
	return this_object()->query("name");
}
