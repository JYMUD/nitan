// counter.c
//wsw��2004��2��20��
//��ҹ�̨
//����д˹�̨�󣬿ɰ���Ʒ���ڹ�̨�ϳ��ۣ�����������
//��������������Ʒ����Ʒ->set("changed",1)

#include "counter.h"   

void create()
{        
        seteuid(0);
        set_name(HIC"��̨"NOR,({"counter" }) );   
        set_weight(50000);   
        if( clonep() )   
                set_default_object(__FILE__); 
        else {   
        set("value", 2000000);   
   
                set("unit","��");   
                set("capacity",10);  //���� 
                set("no_put",1);   
                set("no_sell",1);   
                set("no_get",1);   
                set("no_give",1);   
                set("no_drop",1);   
                set("long",HIB"���֮�ǵĹ�̨��\n"NOR);   
        }   
        setup();     
}   
