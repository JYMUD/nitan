// message.h

#ifndef __MESSAGE_H__
#define __MESSAGE_H__


//
// Client ѶϢ�����
//
#define SYSMSG          "SYSMSG"                // ϵͳѶϢ
#define ENVMSG          "ENVMSG"                // ����ѶϢ
#define CMDMSG          "CMDMSG"                // ָ��ѶϢ
#define CHNMSG          "CHNMSG"                // Ƶ��ѶϢ
#define EMTMSG          "EMTMSG"                // ����ѶϢ
#define SAYMSG          "SAYMSG"                // ˵��ѶϢ
#define TELLMSG         "TELLMSG"               // ��̸ѶϢ
#define ERRMSG          "ERRMSG"                // ����ѶϢ
#define ETCMSG          "ETCMSG"                // ����ѶϢ
#define GAMEMSG         "GAMEMSG"               // ��ϷѶϢ

int  is_loging_now();
int  start_log();
void end_log();
void log_message(string msg);
void log_command(string cmd);
void receive_message(string msgclass, string msg);
void clear_written();
int  is_waiting_command();
void write_prompt();
void receive_snoop(string msg);

#endif
