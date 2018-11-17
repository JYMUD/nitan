// 求三次方根
int sqrt3(int x)
{
        float y = 1.0 / 3.0;
        x = to_int(pow(to_float(x), y));
        return x;
}

int get_exp_rate()
{
        int max_exp = 10000000, exp_rate;
        return 50000000;

        foreach (object user in users())
        {
                if (! environment(user)) continue;
                if (wizardp(user)) continue;

                if( query("combat_exp", user)>max_exp )
                        max_exp=query("combat_exp", user);
        }

        if (max_exp > 50000000) max_exp = 50000000;
        return max_exp;
}

int get_level(int exp)
{
        int level;

        exp /= 10000;
        level = sqrt3(exp);
        return level * 10;
}

void check_me(object me)
{
        object *ob, obb, env, room;
        string *dirs, dir, temp;
        mapping exits;
        int group, i;

        if (! objectp(me))
                me = this_object();
        if (! me) return;

        group=(query("eff_qi", me)-query("max_qi", me))/2000;
        if (group < 1) group = 1;
        set("qi",query("eff_qi",  me), me);
        set_temp("warequest/group", (group+1), me);
        env = environment(me);

        if (! living(me))
        {
                remove_call_out("check_me");
                call_out("check_me", 2, me);
                return;
        }

        ob = all_inventory(env);
        if( sizeof(ob)>0 && !query_temp("warequest/attack", me) )
        {
                for (i = 0; i < sizeof(ob); i++)
                {
                        obb = ob[i];
                        if (! obb->is_character() || ! living(obb))
                                continue;

                        if( query_temp("warequest/party", obb) != "meng" )
                        {
                                message_vision(HIC "$N大聲下令道：騎兵準備！一排排騎兵列出整齊"
                                        + "的方陣，\n陽光下的蒙古軍刀閃閃發光――突擊！！"
                                        + "$N一聲令下，\n萬馬齊鳴，蒙古騎兵開始了可怕的衝鋒！！\n" NOR,
                                        me);

                                set_temp("warequest/attack", 1, me);
                                set_temp("warequest/attacking", 1, me);

                                remove_call_out("attack_over");
                                call_out("attack_over", 10, me);
                                dir = "south"; // 這裡的這個數值絲毫作用都沒有，所以隨便賦值了
                                               // 奇怪的是後面的 attack_begin() 加了 varargs ，
                                               // 這裡取消 dir ，卻報錯，懷疑是用 include 原因。
                                attack_begin(me, obb, env, env, dir);
                                break;
                        }
                }
                remove_call_out("check_me");
                call_out("check_me", 1, me);
                return;
        } else
        if( mapp(exits=query("exits", env) )
         && !query_temp("warequest/attack", me )
         && query("qi", me)>query_temp("warequest/group", me)*200
         && query("jing", me)>query_temp("warequest/group", me)*100 )
        {
                dirs = keys(exits);
                for (i = 0; i < sizeof(dirs); i++)
                if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                        dirs[i] = 0;
                dirs -= ({ 0 });
                if (mapp(exits)) dir = dirs[random(sizeof(dirs))];
                if (! room = find_object(exits[dir]))
                        room = load_object(exits[dir]);

                if (objectp(room))
                {
                        ob = all_inventory(room);
                        if (sizeof(ob) > 0)
                        {
                                for (i = 0; i < sizeof(ob); i++)
                                {
                                        obb = ob[i];
                                        if (! obb->is_character() || ! living(obb)) continue;
                                        if( query_temp("warequest/party", obb) != "meng" )
                                        {
                                                message_vision(HIC "$N大聲下令道：弓箭手準備！一排排利箭在陽"
                                                        + "光下閃閃發光――射擊！！\n$N一聲令下，萬弩齊發！\n" NOR, me);
                                                set_temp("warequest/attack", 1, me);
                                                set_temp("warequest/attacking", 1, me);

                                                remove_call_out("attack_over");
                                                call_out("attack_over", 10, me);
                                                attack_begin(me, obb, room, env, dir);
                                                break;
                                        }
                                }
                                remove_call_out("check_me");
                                call_out("check_me", 1, me);
                                return;
                        }
                }
        }

        if( !query_temp("warequest/attack", me) )
                delete_temp("warequest/attacking", me);

        remove_call_out("check_me");
        call_out("check_me", 1, me);
        return;
}

varargs void attack_begin(object me, object target, object room, object env, string dir)
{
        object weapon, bow, blade, weapon2, *ilist;
        int i;

        if (! objectp(me)) return;

        if (! objectp(target) || ! target->is_character())
                return;

        weapon=query_temp("weapon", me);
        if (weapon) weapon->unequip();

        blade = present("wan dao", me);
        ilist = all_inventory(me);
        for (i = 0; i < sizeof(ilist); i++)
        {
                if( query("is_bow", ilist[i]) )
                {
                        bow = ilist[i];
                        break;
                }
        }

        if (env == room) weapon2 = blade;
        else weapon2 = bow;
        if (objectp(weapon2))
                weapon2->wield();
        for(i=0;i<query_temp("warequest/group", me);i++ )
        {
                if( objectp(target) && objectp(weapon2) && query("equipped", weapon2) && query("is_bow", weapon2) && stringp(dir) )
                {
                        weapon2->do_shoot(query("id", target),me,weapon2,room,dir,1);
                        addn_temp("warequest/reward", 1, target);
                }
                else
                if (room == env && objectp(target))
                {
                        message_vision(HIC "$N指揮的蒙古鐵騎，萬馬奔騰，"
                                       + "如狂風驟雨般朝$n發起了衝擊！！\n" NOR,
                                       me, target);
                        // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);

                        if( !objectp(target) || query("qi", target)<0 || 
                            environment(me) != environment(target))
                                break;

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
                        addn_temp("warequest/reward", 2, target);
                } else break;
        }
        return;
}

void attack_over(object me)
{
        if (! objectp(me)) return;
        if (objectp(me))
        {
                message_vision(HIB"$N手中軍刀一揮，蒙古騎兵攻勢一緩，重新"
                                + "開始列陣，準備發起新一輪的衝擊！！\n"NOR,
                                me);
                delete_temp("warequest/attack", me);
        }
        return;
}

void init()
{
        add_action("do_kill", "team kill");
        add_action("do_kill", "touxi");
        add_action("do_kill", "kill");
        add_action("do_kill", "hit");
        add_action("do_kill", "fight");
        add_action("do_kill", "steal");
        add_action("do_kill", "beg");
        add_action("do_kill", "persuade");
        add_action("do_kill", "perform");
        add_action("do_kill", "yong");
        add_action("do_kill", "exert");
        add_action("do_kill", "yun");
        add_action("do_kill", "throw");
        add_action("do_kill", "conjure");
        add_action("do_kill", "recall");
}

int do_kill(string arg)
{
        string what, who;

        if (! arg) return 0;

        if (this_object()->id(arg))
        {
                write("有沒有搞錯，那是蒙古兵耶，還不快跑？！\n");
                return 1;
        }
        else
        if (sscanf(arg, "%s from %s",what, who) == 2 && this_object()->id(who))
        {
                write("有沒有搞錯，那是蒙古兵耶，還不快跑？！\n");
                return 1;
        } else
        if (sscanf(arg, "%s at %s", what, who) == 2 && this_object()->id(who))
        {
                write("有沒有搞錯，那是蒙古兵耶，還不快跑？！\n");
                return 1;
        } else
        if (sscanf(arg, "%s on %s", what, who) == 2 && this_object()->id(who))
        {
                write("有沒有搞錯，那是蒙古兵耶，還不快跑？！\n");
                return 1;
        } else
        if (sscanf(arg, "%s %s", what, who) == 2 && this_object()->id(who))
        {
                write("有沒有搞錯，那是蒙古兵耶，還不快跑？！\n");
                return 1;
        } else
        if (arg == "roar" || arg == "hou")
        {
                write("有沒有搞錯，那是蒙古兵耶，還不快跑？！\n");
                return 1;
        }

        return 0;
}