// Code of ShenZhou
void dest_bug(object bug);
void setup_npc(object me, object ob);

void init()
{
        add_action("do_search", "search");
        add_action("do_search", "zhao");
}        

int do_search(string arg) {
                

        string* n= ({
                "/d/xingxiu/forest10",
                "/d/xingxiu/forest2",
                "/d/xingxiu/forest3",
                "/d/xingxiu/forest11",
                "/d/xingxiu/forest4",
                "/d/xingxiu/forest5",
                "/d/xingxiu/forest1",
                "/d/xingxiu/forest12",
                "/d/xingxiu/forest6",
                "/d/xingxiu/forest7",
                "/d/xingxiu/forest8",
                "/d/xingxiu/forest9",
        });

        object bug, me, fighter, room, gold, ob;

        int kar1, kar2, kar3, pot, max_pot, damage, find;        

        me=this_player();

        if( !arg || arg=="" ) return 0;
        
        if( arg=="bug" || arg=="chong"){

                if (!present("wa guan", me))
                        return notify_fail("���ҵ�������ʲô��ʢ�أ�\n\n");
                        
               if( query("max_jingli", me)<100 )
                       return notify_fail("��������̫���ˡ�\n\n");
                if( query("jingli", me)<query("max_jingli", me)/5 )
                        return notify_fail("������Ϣһ�°ɡ�\n\n");
                        
                if (me->is_busy()) return
                        notify_fail("����һ��������û����ɡ�\n"); 
                        
                if (me->is_fighting()) return
                        notify_fail("���Ȱɵ�����������˵�ɡ�:)\n");
                        
                if( query_temp("found", me) == 1)return 
                        notify_fail("������Ȼ�ȥ�������������ɵȼ��ˡ�\n");
                                       
                //if (me->query_temp("bug_out")==1)
                //        return notify_fail("�����Ѿ������ˣ��Ͽ�ץ�ɣ�\n");
                
                if( query_temp("xx_job", me) != 1 )
                        return notify_fail("������ʲô�ã�\n");
                
                addn("jingli", -10, me);
                addn("jing", -10, me);
                me->start_busy(random(1)+1);
                
                addn("find_bug", 1, me);
                addn_temp("xx/find", 1, me);

                message_vision("$N�������������ֽ���֦��Ҷ��������ϸѰ�Ҷ�����ټ���\n",me);
                
                kar2=(query("int", me)+query("con", me)+query("str", me))*(random(2)+1);
                kar1=query("kar", me);

                if( query("find_bug", me)>random(20)){
                        set("find_bug", 0, me);
                                
                        room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N�������ң�����û��˿��������ټ���ֻ���뿪�������ĵط�Ѱ�ҡ�\n",me);
                        message_vision("$N����ææ���뿪�ˡ�\n",me);
                        me->move(room);
                        message_vision("$N���˹�����\n",me);                        
                        return 1;
                }
                
                kar3=random(kar1*3);
                find=query_temp("xx/find", me);
                
                if (wizardp(me)) {
                                printf("my kar=%d  kar=%d  randkar=%d  time: %d\n", kar1, kar3, kar2, find);
                }
                
                if ((kar3>kar2 && find>10) || (find>=30)) {

                        message_vision(HIG"ͻȻ��һֻС�������˳�����Ѹ�ٵ������š�\n"NOR, me);
                        bug=new("/d/xingxiu/npc/duchong");
                        bug->move(environment(me));
                        set("playerid",query("id",  me), bug);
                        set_temp("bug_out", 1, me);
                        set_temp("xx/find", 0, me);
                        
                        if (wizardp(me)) {
                                printf("playerid:%s\n",query("playerid", bug));
                        }
                                                
                        return 1;
                        
                 }
                
                   if( query("combat_exp", random(50) <= 3 && count_ge(me),150000) && query_temp("xx_job", me)){

                        message_vision(HIR"ͻȻ�������Խ��һ���ˣ��ߺ�һ���������޼��ˣ�����������\n"NOR,me);
                     fighter = new(CLASS_D("generate") + "/xxnpc.c");
                     NPC_D->set_from_me(fighter, me, 110 + random(20));
                     fighter->addn_temp("apply/attack",fighter->query_skill("force")*
                                             1/ 15);
                     fighter->addn_temp("apply/dodge",fighter->query_skill("force")*
                                             1/ 15);
                     fighter->addn_temp("apply/parry",fighter->query_skill("force")*
                                             1/ 15);
                     addn_temp("apply/damage", 5+1*7, fighter);
                     addn_temp("apply/unarmed_damage", 5+1*7, fighter);
                     addn_temp("apply/armor", 10+1*15, fighter);
                        set("player",query("id",  me), fighter);
                        fighter->move(environment(me));
                        fighter->kill_ob(me);
                        //fighter->set_busy(random(2));                        
                        return 1;
                }
                
                
                if (random(kar1*3)<1){
                        message_vision(HIW"$N��ǰ����һ�����ۣ����ӣ�\n"NOR,me);
                        gold=new("/clone/money/silver");
                        gold->move(environment(me));
                        return 1;
                }
                
                if (random(kar1*2)<1){
                        message_vision(YEL"$N��ǰͭ��һ�����ۣ�ͭǮ :(\n"NOR,me);
                        gold=new("/clone/money/coin");
                        gold->move(environment(me));
                        return 1;
                }
                
                if (random(kar1*4)<1){
                        message_vision(HIY"$N��ǰ���һ�����ۣ����ӣ�\n"NOR,me);
                        message_vision(HIR"$N�������ӣ�����һ���⣬�����߹޵������ϴ�ķ��顣\n"NOR,me);
                        gold=new("/clone/money/gold");
                        gold->move(environment(me));
                        ob = present("wa guan", me);
                        if(ob)destruct(ob);
                        delete_temp("xx_job", me);
                        return 1;
                }
                
                if (random(20)<1){
                        message_vision(MAG"\n$N��ѽһ���������ϵ�ʯͷ����һ����\n"NOR,me);
                        me->start_busy(random(3)+2);
                        damage=me->query_skill("force",1);
                        me->receive_wound("qi", random(damage/10));
                }

                
                
        return 1;        
        } else if(arg=="dochong"){
                
                set_temp("fresh", 1, me);
                message_vision("$N�������������ֽ���֦��Ҷ��������ϸѰ�Ҷ�����ټ���\n",me);
                
                if( query("find_bug", me)>random(20)){
                        set("find_bug", 0, me);
                                
                        room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N�������ң�����û��˿��������ټ���ֻ���뿪�������ĵط�Ѱ�ҡ�\n",me);
                        message_vision("$N����ææ���뿪�ˡ�\n",me);
                        me->move(room);
                        message_vision("$N���˹�����\n",me);                        
                        return 1;
                }
                
                
                return 1;
        }        
        
}