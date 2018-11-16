// trap.c ���Ϊ��
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit F_CLEAN_UP;
void digging(object, int);
void create() { seteuid(getuid()); }

mapping default_dirs = ([
        "north":        "��",
        "south":        "��",
        "east":         "��",
        "west":         "��",
        "northup":      "����",
        "southup":      "�ϱ�",
        "eastup":       "����",
        "westup":       "����",
        "northdown":    "����",
        "southdown":    "�ϱ�",
        "eastdown":     "����",
        "westdown":     "����",
        "northeast":    "����",
        "northwest":    "����",
        "southeast":    "����",
        "southwest":    "����",
        "up":           "��",
        "down":         "��",
        "out":          "��",
        "enter":        "��",
]);
string *place = ({ "��", "��", "��", "¥", "��", "��", "��", "��", 
"Ժ", "��", "��", "ׯ", "ի", "��", "��", "԰", "��", "��", "��", 
"��", "��", "Ԣ", "��", "��", "Ӫ", "��" ,"��","��","ƺ"});

int main(object me, string arg)
{
        object roomfrom, roomto, roomtrap, *inv, tool;
        mapping exits;
        string dir, from, to, *dirs;
        int i, depth;

        if( query("shen", me) >= 0 && !wizardp(me) )
                return notify_fail("��������ɣ����Ҵ���������а�������⣿��\n");
        if( query("combat_exp", me) >= 100000 && !wizardp(me) )
                return notify_fail("��������õİ�Ϸ�����������ĸ��ֲ�мΪ֮�ɣ���\n");
        if( me->query_skill("digging", 1) <= 30)
                return notify_fail("����㱾�¶�ûѧȫ����λ��ھ����壿\n");
        if( me->is_fighting() )
                return notify_fail("һ�ߴ��һ���ھ������ǻ����ˣ�\n");
        if( me->is_busy() )
                return notify_fail("��������æ�ţ�\n");
                tool= present("shenlong qiao", me);
        if(!tool && !wizardp(me))
      return notify_fail("�ȵ��Ұѳ��ֵĹ��߰ɣ�\n");
        if( !query("dig_times", tool) )
                return notify_fail("���Ұѳ��ֵĹ��߰�?\n");
        if( query("dig_times", tool) == 1 )
        {
                message_vision(GRN "\n$N͵͵�����ؾ������£�һ������ȥ����ž����һ��ľ�����ˡ�����\n\n" NOR, me);
                tool->unequip();
                tool->reset_action();
                set("name",query("name",  tool)+"����Ƭ", tool);
                tool->move(environment(me));
                set("value", 0, tool);
                set("weapon_prop", 0, tool);
                set("id", "tieqiao", tool);
        }
        inv = all_inventory(environment(me));
        if( sizeof(inv) > 0)
        for(i=0; i<sizeof(inv); i++)
        {
                if( userp(inv[i]) && inv[i] != me )
                        return notify_fail("������ô�����ڿ��������ڳ��������ڣ�\n");
        }
        if( !arg || !query("exits/"+arg, environment(me)) )
                return notify_fail("�����ĸ����������壿\n");
        if( strsrch(arg, "jump") >= 0  
//        ||
//                strsrch(arg, "up") >= 0 ||
//                strsrch(arg, "down") >= 0 ||
//                strsrch(arg,"out") >=0 ||
//                strsrch(arg,"enter") >=0 
         )
                return notify_fail("�㲻����������������壡\n");
        if( !query("trap_room", environment(me)) )
                roomfrom = environment(me);
        else return notify_fail("�㲻��������֮���������壡\n");
        if( !query("outdoors", roomfrom) )
                return notify_fail("�㲻�������ھ����壡\n");
        if( sizeof(query("exits", roomfrom)) >= 4 )
                return notify_fail("������ͨ�������㲻�ܴ��������壡\n");
/*
        if( query("cost", roomfrom) <= 1 )
                return notify_fail("�˴����ʼ�ʵ���ƺ������ھ����壡\n");
*/
        if( !(roomto=find_object(query("exits/"+arg, roomfrom))) )
                roomto=load_object(query("exits/"+arg, roomfrom));
        if( query("trap_room", roomto) )
                return notify_fail("�Ǳ��Ѿ����˸����壡\n");
        if( !query("outdoors", roomto) )
                return notify_fail("�㲻���ڱ��˷��ſ����ڣ�\n");
        for (i=0; i<sizeof(place); i++)
                if( strsrch(query("short", roomfrom),place[i]) >= 0 || 
                        strsrch(query("short", roomto),place[i]) >= 0 )
                        return notify_fail("�����·�治�ʺ������壡\n");

        depth = me->query_skill("digging", 1)*10
                + me->query_str()*2 
                + me->query_int()*2 
                + me->query_kar()*2
                +query("qi", me)/2;

        if( query("qi", me)<depth*query("cost", roomfrom)/10 )
                return notify_fail("������������ˣ�\n");
        roomtrap = new("/clone/misc/traproom");
        set("depth", depth/3+random(depth*2/3), roomtrap);
        set("owner", me, roomtrap);
        set("limit", me->query_skill("digging",1)/10, roomtrap);
        set("roomfrom", roomfrom, roomtrap);
        set("from", arg, roomtrap);

        if( !undefinedp(default_dirs[arg]) ) dir = default_dirs[arg];
        else dir = arg;
        if(objectp(roomfrom))
                set("exits/"+arg, file_name(roomtrap), roomfrom);
        if(objectp(roomto))
        {
                if( strsrch(arg, "up") >= 0 || strsrch(arg, "down") >= 0 )
                        set("exits/"+arg, file_name(roomto), roomtrap);
                else set("exits/" + arg + "up", file_name(roomto), roomtrap);
                set("roomto", roomto, roomtrap);
                exits=query("exits", roomto);
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++)
                {
                        if( exits[dirs[i]] == file_name(roomfrom) )
                        {
                                set("exits/"+dirs[i], file_name(roomtrap), roomto);
                                set("exits/"+dirs[i]+"up", file_name(roomfrom), roomtrap);
                                set("to", dirs[i], roomtrap);
                                break;
                        }
                }
        }

        if(objectp(roomfrom) && objectp(roomto))
        {
                set("exits/jump"+query("from", roomtrap), file_name(roomto), roomfrom);
                set("exits/jump"+query("to", roomtrap), file_name(roomfrom), roomto);
        }

        message_vision(GRN "\n$N͵͵�����ؾ������£�����" + dir + "������һͨ������\n\n" NOR, me);
        addn("dig_times", -1, tool);
        remove_call_out("digging");
        call_out("digging", depth/100, me, depth);
        me->start_busy(depth/100);

        return 1;
}

void digging(object me, int depth)
{
        if( me->is_busy() )
        {
                call_out("digging", 3, me, depth);
                if(random(5)==1) message_vision(GRN "\n$N�𾢵��������������š�����\n" NOR, me);
        }
        else        
        {
                me->improve_skill("digging", depth / 20);
                me->receive_damage("qi",depth*(query("cost", environment(me)))/10,"������������");
                tell_object(me, "���������ں���һ�����壡\n");
        }
}

int help (object me)
{
        write(@HELP
ָ���ʽ : [trap <����>]

���ָ��������ĳ�������ھ�һ�����塣

HELP
);
        return 1;
}
