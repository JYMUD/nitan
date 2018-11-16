inherit COMBINED_ITEM;
#include <ansi.h>                                                                                                                                     
string query_autoload()
{                                     
        return query_amount() + "";
}
                                                                                         
void create()                                                                            
{                                                                                        
        set_name(HIR "��ﵤ" NOR, ({ "luofeng dan" }));              
        if (clonep())                                                                    
                set_default_object(__FILE__);                                            
        else {                                                                           
                set("long", YEL "�˵����º��������һ������Ե�ʧ�ܼ�¼��\n" NOR);   
                set("base_unit", "��");                                                  
                set("base_value", 400000);                                               
                set("base_weight", 50);                                                  
                set("only_do_effect", 1);                                                                                                                               
                set("gift_msg", HIM "ͻȻ��������Լ����Ϻ������˵�ʲô��\n" NOR);
        }                                                                                
        setup();                                                                         
}               

int do_effect(object me)
{
                                                               
        message_vision(WHT "$N" WHT "һ������������һ" +                                                                      
                       query("base_unit") + name() + WHT
                       "��\n" NOR, me);    
                       
        if( query("gift/clearcount", me) >= 3 )
        {                                                           
                tell_object(me, "�������ҩ����ûʲôЧ����\n");
        }
        else
        {                                                           
                if( query("gift/dex/fail", me) )
                {
                       addn("gift/dex/fail", -1, me);
                       addn("gift/dex/all", -1, me);
                       addn("gift/clearcount", 1, me);
                       tell_object(me, query("gift_msg"));
                       tell_object(me, HIC "OK.\n" NOR);
                }
                else 
                {
                        tell_object(me, HIC "�������ҩ����ûʲôЧ����\n" NOR);
                }
                
        }             
        add_amount(-1);                    
        if (query_amount() < 1)
                destruct(this_object());
        
        return 1;
}

void autoload(string param)
{                                                                         
        int amt;

        if (sscanf(param, "%d", amt) == 1)    
                set_amount(amt);
}                                             
                                              
void setup()
{                                             
        set_amount(1);
        ::setup();
}
                               
                               