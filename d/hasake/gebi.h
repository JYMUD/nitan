#include <ansi.h>

int valid_leave(object me, string dir)
{
       if( dir == "north")addn_temp("mark/steps", 1, me);
       if( dir == "south")addn_temp("mark/steps", -1, me);
       if( dir == "east")addn_temp("mark/step", 1, me);
       if( dir == "west")addn_temp("mark/step", -1, me);
        
       if( query_temp("mark/steps", me) <= -10 && 
          query_temp("mark/step", me) <= -10){
            me->move("/d/baituo/gebi");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"����ƣ�����������ӴӸ��ɳĮ���˹�����\n",  ({ me }));  
            return notify_fail("ͻȻ����ǰ������һ��Сɽ����״�����շ塣\n");
            }       
           
       if( query_temp("mark/steps", me) == -12){
            me->move(__DIR__"senlin");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"����ƣ�����������ӴӸ��ɳĮ���˹�����\n",  ({ me }));  
            return notify_fail("ͻȻ���߳��˴��ڣ�����һɭ�ִ���\n");
            }       
           
       if( query_temp("mark/step", me) == 11){
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            me->move(__DIR__"gebi5");
            return notify_fail("");
            }  
       if( query_temp("mark/steps", me) == 11 && 
          query_temp("mark/step", me)<-10){
            me->move(__DIR__"room-ji");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"����ƣ�����������ӴӸ��ɳĮ���˹�����\n",  ({ me }));  
            return notify_fail("���������ˣ��������߳������ˣ�\n");
            }  

       if( (query_temp("mark/steps", me) == 7 && query_temp("gc_n", me)) || 
          (query_temp("mark/steps", me) == -7 && query_temp("gc_s", me)) || 
          (query_temp("mark/step", me) == -7 && query_temp("gc_w", me)) || 
          (query_temp("mark/step", me) == 7 && query_temp("gc_e", me))){
            me->move(__DIR__"lvzhou");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            delete_temp("gc_n", me);
            delete_temp("gc_s", me);
            delete_temp("gc_w", me);
            delete_temp("gc_e", me);
            tell_room(environment(me), me->name()+"����ƣ�����������ӴӸ��ɳĮ���˹�����\n",  ({ me }));  
            return notify_fail("������ã����ҵ���һ��ɳĮ���ޣ�\n");
            }
 
       if( (query_temp("mark/steps", me) == 7 && (query_temp("mark/step", me) == 3 || 
           query_temp("mark/step", me) == -3) && query_temp("gc1_n", me)) || 
          (query_temp("mark/steps", me) == -7 && (query_temp("mark/step", me) == 3 || 
           query_temp("mark/step", me) == -3) && query_temp("gc1_s", me)) || 
          (query_temp("mark/step", me) == 7 && (query_temp("mark/steps", me) == 3 || 
           query_temp("mark/steps", me) == -3) && query_temp("gc1_e", me)) || 
          (query_temp("mark/step", me) == -7 && (query_temp("mark/steps", me) == 3 || 
           query_temp("mark/steps", me) == -3) && query_temp("gc1_w", me))){
            me->move(__DIR__"shulin");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            delete_temp("gc1_n", me);
            delete_temp("gc1_s", me);
            delete_temp("gc1_w", me);
            delete_temp("gc1_e", me);
            tell_room(environment(me), me->name()+"����ƣ�����������ӴӸ��ɳĮ���˹�����\n",  ({ me }));  
            return notify_fail("�ף��㷢�������Ѿ����Ǹ��ɳĮ�ˣ�\n");
            }       
        return ::valid_leave(me, dir);
}

void init()
{
       object me, *ob, *inv, ob1;
       string msg, msg1;
       int i, j;
       me = this_player();
       ob = all_inventory(environment(me));
       msg = YEL"\nͻȻһ�ɼ���ε�������һ��Ƭ��ɳ��ֻ���������������Ƕ���ɳ�������ޱ��޼ʵĴ�ɳĮ֮�У�
���������̵صĴ��ɳ�£���������е�һҶС��һ�㣬ֻ������������ȫ�ް������֮����\n"NOR;
       msg1 = HIR"������Լ��Ѿ���ƣ�����ˣ����ϵĻ�ɳȴԽ��Խ�񡭡�\n"NOR;

       if(ob1 = present("bai shoujuan", me)){
          write(WHT"�����հ��־��ϵ���ʾ���ܿ���߳��˴��ڡ�\n"NOR);
          me->move(__DIR__"caoyuan",1);
          destruct(ob1);
          delete_temp("mark/steps", me);
          delete_temp("mark/step", me);
          tell_room(environment(me), me->name()+"��������شӸ��ɳĮ���˹�����\n",  ({ me }));  
          write("ͻȻ��һ�����񣬰��־�紵���ˣ�\n");
          return;
          }  
       if(userp(me)){ 
         if( query_temp("li_meet", me) == 2){
              message_vision(msg, me); 
              tell_object(me, msg1);
              delete_temp("mark/steps", me);
              delete_temp("mark/step", me);
              me->unconcious();             
              me->move(__DIR__"shulin");
              tell_room(environment(me), "ͻȻһ����紵���������������㱳����֣�\n", ({ me }));  
              return;
              }
         else if( query("water", me)<20 )
              { 
              message_vision(msg1, me);              
                  me->unconcious();
                  me->move(__DIR__"caoyuan"+(1+random(7)));
                  tell_room(environment(me), HIR"ͻȻһ���紵��������һ��������\n"NOR,  ({ me }));  
                  delete_temp("mark/steps", me);
                  delete_temp("mark/step", me);
                  delete_temp("gc_n", me);
                  delete_temp("gc_s", me);
                  delete_temp("gc_w", me);
                  delete_temp("gc_e", me);
                  delete_temp("gc1_n", me);
                  delete_temp("gc1_s", me);
                  delete_temp("gc1_w", me);
                  delete_temp("gc1_e", me);
              return;
              }
         else if(me->query_skill("dodge", 1) <= 150) { 
              addn("jing", -15, me);
              if( objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
              addn("water", -10, me);
              }
         else {
              addn("jing", -5, me);
              if( objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
              addn("water", -5, me);
              }
      }
}
