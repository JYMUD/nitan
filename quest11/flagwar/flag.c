// business.c

inherit F_CLEAN_UP;

#define PAY_MONEY        500000 
nomask int main(object me, string arg)
{
	   int tt;
     string msg;
     if(!find_object(FWAR_D)) return notify_fail("Ŀǰ����ս��δ��ʼ��\n");
    switch(arg) {
    	case "join":
    		if(!FWAR_D->query_flagwar_data("can_accept")) return notify_fail("��������ս��δ���ű�����\n");
    		if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) != -1) return notify_fail("���Ѿ���������������ս�ˡ�\n");
          switch(MONEY_D->player_pay(me, PAY_MONEY)) {
           case 0:
           case 2:
           	return notify_fail("�μ�����ս��֧��"+MONEY_D->money_str(PAY_MONEY)+"��\n");
           break;
           default:
           if(!FWAR_D->add_player(me, PAY_MONEY)) return notify_fail("��������ս�������⣬��ʹ�� sos post �ر���\n");
           break;           
           }
    	break;
    	case "leave":
    		// �����׶�
    		if(!FWAR_D->query_flagwar()) {
    			if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) == -1) return notify_fail("�㱾����û�б�������ս��\n");
    			FWAR_D->leave_player(me->query("id"));
    		} else {
    			if(member_array(me->query("id"), FWAR_D->query_flagwar_data("all_player")) == -1) return 0;
    			FWAR_D->leave_player(me->query("id"));
    		}
    	break;
    	default:
     if(!FWAR_D->query_flagwar()) {
     	tt = FWAR_D->query_flagwar_time();
      if(tt == -1) return notify_fail("����ս�Ѿ��ڱ����׶Ρ�\n");
      else if(tt == -2) return notify_fail("����ս����׼����\n");
     	else return notify_fail("Ŀǰ����ս��δ��ʼ�������´ο�ʼ����"+CHINESE_D->chinese_period(tt)+"��\n");
     }
     msg = " "+FWAR_D->query_party_score_total();
     msg += "����������������������������������������������������������������������\n";
     msg += " "+FWAR_D->query_party_score("red");
     msg += " �������������������������������������������������������������������� \n";
     msg += " "+FWAR_D->query_party_score("blue");
     msg += "����������������������������������������������������������������������\n";
     me->start_more(msg);    		
    	break;
    }
     
     
     
     return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��flag score | join | leave

��ָ�������鿴����ս��״����

������ score : �鿴����ս��״����
       join  : �����μ�����ս��
       leave : �뿪����ս��ȡ��������
HELP);
        return 1;
}

