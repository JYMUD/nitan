void init()
{
        object ob, me;
        me = this_object();
        if (interactive(ob = this_player()) && present("shou juan", ob)){
           message_vision(HIY"$NͻȻ������$nǰ���۾�ֱ����$n������־\n"NOR,me,ob); 
           set("chat_chance", 0, me);
           remove_call_out("do_kill");
           call_out("do_kill", 0, me, ob);
        }        
}

int do_kill(object me, object dest)
{
        if( objectp(dest) && present(dest, environment(me))
                  && !query("no_fight", environment(me))){
                message_vision(HIR "$N��$n����һЦ�����־��ү������ʮ���ˣ�"
                        +RANK_D->query_rude(dest)+"��͹Թ������ɣ�\n" NOR, me, dest);
                me->set_leader(dest);
                me->kill_ob(dest);
                dest->fight_ob(me);
                call_out("checking", 0,  me, dest);
        }        
        else
                  call_out("waiting", 1, me, dest);
                return 1;
}
int waiting(object me, object dest)
{
       if ( objectp(dest) ){
         if (dest->is_ghost()){
                call_out("do_back", 1, me);
                return 1;
                }
         else if (me->is_fighting() && present(dest, environment(me))){
                call_out("checking", 1, me, dest);
                return 1;
                }
         else if( living(me) && query("no_fight", environment(dest))){
                call_out("do_back", 1, me);
                return 1;
                }
        remove_call_out("waiting");
        call_out("waiting", 1, me);
        }
        return 1;
}

int checking(object me, object dest)
{
        object ob;
        if (me->is_fighting()){
          call_out("checking", 1, me, dest);
          return 1;
          }
        if( objectp(ob = present("corpse", environment(me)))
          && query("victim_name", ob) == query("name", dest)){
          remove_call_out("checking");
          command("get shou juan from corpse");
          tell_room(environment(me),
          query("name", me)+"���������ϵĻҳ����첽���˳�ȥ��\n"NOR,({me}));
              call_out("do_back", 1, me);
          return 1;
          }
        call_out("waiting", 0, me, dest);
        return 1;
}

int do_back(object me)
{        
  me->move(query("startroom", me));
  tell_room(environment(me),query("name", me)+"�첽���˹�����\n",({me}));
  me->set_leader(0);
  set("chat_chance", 40, me);
  return 1;
}
