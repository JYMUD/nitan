// Code of JHSH
// snake_room.h �߹������ߵķ���

void check_snake(object, string);
void smoke_snake(object, object, string);
#include <ansi.h>

void init()
{
        object here = this_object();
        set("can_perform_shewu", 1, here);
        set("enter_shegu", 1, this_player());
        delete_temp("search", this_player());

        if( query("hide_snake", here)<1 && 
        (time()-query("last_search", here)>180 || !query("last_search", here)) )
                set("hide_snake", 1+random(3), here);

        add_action("do_search", "search");
        add_action("do_use","use");
        add_action("do_burn","burn");
}

string look_bush()
{
        string desc;
        if(!query("searched/bush")) desc = "һ���Ͱ��Ĺ�ľ�ԡ�\n";
        else desc = "һ���Ͱ��Ĺ�ľ�ԣ�������Щ���۵����֦Ҷ��\n";        
        return desc;
}

string look_crack()
{
        string desc;
        if(!query("searched/crack")) desc = "��������ѷ죬�Ա����ŴԴ��Ҳݡ�\n";
        else desc = "��������ѷ죬�������Ӳݵ������ߣ��ƺ�����������\n";        
        return desc;
}

string look_cave()
{
        string desc;
        if(!query("searched/cave")) desc = "ɽ���µ�һ��С������������ûʲôɰ������Ϊ�⻬��\n";
        else desc = "ɽ���µ�һ��С��������������Щ֦Ҷ��ʣ�Ļҽ���\n";        
        return desc;
}

int do_search(string arg)
{
        object me, here, weapon;
        string place;
        
        me = this_player();
        here = this_object();
        weapon=query_temp("weapon", me);

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("��������æ���ء�\n");

        if( !objectp(weapon) || (query("skill_type", weapon) != "staff"
         && query("skill_type", weapon) != "club"
         && query("skill_type", weapon) != "stick") )
                return notify_fail("����Ѱ��̫Σ���ˣ����õ���ֵĹ��߰ɡ�\n");


        if(arg == "grass" && query("grass") ) {
                place = "�ݴ�";
                message_vision("$N��"+weapon->name()+"���������Ĳݴԡ�\n", me);
                addn("jingli", -20, me);
                set("searched/grass", 1);
        }
        
        else if(arg == "bush" && query("bush") ) {
                place = "����";
                message_vision("$N����"+weapon->name()+"�������ܵ�����֦Ҷ������ɳɳ�����졣\n", me);
                addn("jingli", -40, me);
                set("searched/bush", 1);
        }
        else if(arg == "crack" && query("crack") ) {
                place = "�����ѷ�";
                message_vision("$N��"+weapon->name()+"���������ѷ촦�����á�\n", me);
                addn("jingli", -10, me);
        }

        else if(arg == "cave" && query("cave") ) {
                place = "��";
                message_vision("$N��"+weapon->name()+"�ڶ��ڵ���u�С��Сv�������š�\n", me);
                addn("jingli", -10, me);
        }
        else return notify_fail("��Ҫ�����ĸ��ط���\n");

        addn_temp("search/"+place, 1, me);
        me->start_busy(1);

        if( query_temp("search/"+place, me)<3+random(3) )
                return 1;

        if(query("hide_snake") > 0) {
                check_snake(me, place);
        }
        else return notify_fail("��������ã������"+place+"��Ӧ���ǲ���������ˡ�\n");

        return 1;
}

void check_snake(object me, string place)
{
        object snake, here;
        int i;

        here = this_object();

        addn("hide_snake", -1, here);
        set("last_search", time(), here);

        if( place == "�ݴ�" || place == "����" ) {
                if( place == "����" ) {
                        i = random(4) + 1;
                        set("searched/bush", 1);
                        }
                else {
                        i = random(4);
                        set("searched/grass", 1);
                        }
                snake = new("/d/baituo/npc/bt_snake");
                set("frightened", 1, snake);
                snake->set_kind(i);
                snake->move(here);
                message_vision(HIR"����"+place+"�������춯��һ��"+snake->name()+"���˳�����\n"NOR, me);
                snake->kill_ob(me);
        }
        else message_vision(place+"�д���һ��ϸ΢�����죬�ƺ���ʲ�ᶫ��������û�г�����\n"NOR, me);

        delete_temp("search/"+place, me);

        return;
}

int do_use(string arg)
{
        object me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;

        if( arg=="fire" ) 
        write("�㽫���۵�ȼ��\n");
        return 1;
}

int do_burn(string arg)
{
        object me, branch;
        string place;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("��������æ���ء�\n");

        if( !objectp(branch = present(arg, me))  && !objectp(branch = present(arg, environment(me)))  )
                return notify_fail("��Ҫ��ʲ�᣿\n");

        if( query("id", branch) != "shuzhi" )
                return notify_fail("�������Ѭ�ߣ���Щ��֦֮��Ķ������հɡ�\n");

        if( query("burning", branch) )
                return notify_fail("��֦�Ѿ���ȼ�ˡ�\n");

        if( query("crack") ) {
                place = "�����ѷ�";
                if(!query("searched/crack")) message_vision("$N������ǰ���Ӳݲ�����\n", me);
        }
        else if( query("cave") ) place = "��";
        else return notify_fail("����������֦Ҳûʲ���á�\n");

        message_vision(HIR"$N��"+branch->name()+HIR"����"+place+"ǰ���û��۵�ȼ��\n"NOR, me);
        message_vision(WHT"һ��Ũ������ӿ��"+place+"��........\n\n"NOR, me);
        
        set("name", "��ȼ��"+branch->name(), branch);
        set("long",query("long",  branch)+"������ȼ���ţ�ð��ŨŨ������\n", branch);
        set("burning", 1, branch);
        set("no_get", 1, branch);
        branch->move(this_object());
        remove_call_out("smoke_snake");
        call_out("smoke_snake", 7+random(3), me, branch, place); 
        me->start_busy(2);

        return 1;
}


void smoke_snake(object me, object branch, string place)
{
        object snake, here;
        int i;

        here = this_object();

        if(query("hide_snake") < 1 ) {
                message_vision("��Ѭ���ϰ��죬��֦���ճɻ��ˣ�"+place+"��ȴһ�㶯��Ҳû�С�\n", me);
                destruct(branch);
                return;
        }

        addn("hide_snake", -1);
        set("last_search", time(), here);

        if( place == "�����ѷ�" ) {
                i = random(5) + 3;
                set("searched/crack", 1);
        }
        else {
                i = random(3) + 5;
                set("searched/cave", 1);
        }

        snake = new("/d/baituo/npc/bt_snake");
        set("frightened", 1, snake);
        snake->set_kind(i);
        snake->move(here);
        message_vision(HIR"����һ����������һ��$N�̲�ס��Ѭ����"+place+"�д��˳�����\n"NOR, snake);
        if(environment(me) == this_object())
        snake->kill_ob(me);

        delete_temp("search/"+place, me);
        destruct(branch);

        return;
}
