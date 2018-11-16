#include <ansi.h>

private string *check_skill = ({ 
            "changquan",         
            "luohan-quan",
            "fuhu-quan",
            "mohe-zhi",
            "yizhi-chan",
});

private string *check_skilltemp = ({
            "cuff",
            "cuff",
            "cuff",
            "finger",
            "finger",
});

private string *check_skillname = ({
            "�����־�",
            "�޺���ħ",
            "�޺�����",
            "Ħڭ����",
            "��ħһָ",
});


private string *check_canpfm = ({
            "can_perform/changauan/zhen",
            "can_perform/luohan-quan/xiangmo",
            "can_perform/fuhu-quan/fuhu",
            "can_perform/mohe-zhi/mohe",
            "can_perform/yizhi-chan/jingmo",

});

int do_ask();

int init()
{
        add_action("do_ask", "ask");
}

int do_ask(string arg) 
{ 
        int i;
        object me, ob; 
        string msg;
        
        me = this_player(); 
        ob = this_object();
          
        if( !arg || sscanf(arg, "%s", msg) != 1 ) 
        {
         message_vision(CYN "�����Ҫ��������书��ʽ��ֱ��(ask XXXX)�Ϳ�����!" NOR, ob, me);
         return 1); 
        }
          
        for(i=0; i< sizeof(check_skill); i++)
        {
           if (check_skillname[i] == msg)
           {
        
                 if( query(check_canpfm[i], me) )
                 {
                     message_vision(CYN "�Ҳ����Ѿ��̹�������" NOR, ob, me); 
                     return 1; 
                 }

                 if( query("family/family_name", me) != query("family/family_name", ob) )
                 {
              
                     message_vision(CYN RANK_D->query_respect(me) + "�ͱ������޹ϸ𣬺γ����ԣ�" NOR, ob, me); 
                     return 1;
                  }

                 if (me->query_skill(check_skill[i], 1) < 1)
                 {
                     message_vision(CYN "����" + to_chinese(check_skill[i]) + "��δ��ѧ�����������У�" NOR, ob, me);
                     return 1;
                 }
      
                 if( query("gongxian", me)<100 )
                 { 
                     message_vision(CYN "���������������£�ȴ������Ϊ���������Ȳ�æ���㡣" NOR, ob, me); 
                     return 1; 
                 }
        
                 if (me->query_skill("force") < 100)
                 {
                     message_vision(CYN "����ڹ�����㣬ѧ�������С�" NOR, ob, me);          
                     return 1; 
                 }
        
                 if (me->query_skill(check_skill[i], 1) < 80)
                 {
                     message_vision(CYN "���"+ to_chinese(check_skill[i]) + "���δ�������ö���ϰ��ϰ��" NOR, ob, me);
                     return 1; 
                 }
       
                 message_vision(HIY "$n" HIY "���˵�ͷ�����ֽ�$N" HIY "����" 
                                    "��ߣ��ڶ��Ե���ϸ˵���ã�$N" HIY "��" 
                                    "���\n�ĵ�һЦ��������������\n" NOR, me, ob); 
                                                                        
                 command("nod"); 
                 command("say �����ˣ�"); 
                 tell_object(me, HIC "��ѧ���ˡ�" + check_skillname[i] + "����\n" NOR); 
      
                 if (me->can_improve_skill(check_skilltemp[i])) 
                     me->improve_skill(check_skilltemp[i], 1500000); 

                 if (me->can_improve_skill(check_skill[i])) 
                     me->improve_skill(check_skill[i], 1500000); 
                     me->improve_skill("martial-cognize", 1500000); 
                     set(check_canpfm[i], 1, me);
                     addn("gongxian", -100, me);
                 return 1; 
             }

         }

} 
