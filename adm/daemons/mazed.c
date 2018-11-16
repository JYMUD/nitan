// This program is a part of NITAN MudLIB
// mazed.c �Թ����ػ�����

/***********************************************************************
 * ÿ���Թ������ݰ�����                                                *
 * boss:            �Թ��з��õ�NPC                                    *
 * roomlist:        �Թ��ķ������                                     *
 * entry:           �Թ������                                         *
 * target:          �Թ��ĳ���                                         *
 * direction:       �Թ��ķ���                                         *
 * deep_map:        �Թ���·�ߵĵ�ͼ                                   *
 * comm_map:        �Թ�����·�ߵĵ�ͼ                                 *
 * born_time:       �Թ�������ʱ��                                     *
 * map_status:      �Թ��ĵ�ͼ״̬                                     *
 ***********************************************************************/

#include <ansi.h>
#include <maze.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

int clean_up() { return 1; }

/***********************************************************************/

nosave mapping mazelist;                                  // �����Թ��б�
nosave int mazeindex = 0;                                 // �����Թ�����  
nosave int show_local_room = 1;                           // �Ƿ���ʾ������ڵ�λ��   
nosave mixed dead_room_list;                              // �ڴ����Թ�ʱ��¼����ͬ       
nosave object *all_dead_room;                             // ��¼����������ͬ�еķ���    
 
// �����ṩ���ⲿ���õĽӿں���
public void check_maze(string mazename);                  // ����Թ���״̬ 
public void remove_maze(string mazename);                 // ���ָ�����Թ� 
public object create_maze(object npc);                    // �����µ��Թ�   
public void init_maze(string mazename);                   // ��ʼ���Թ���ͼ  
public string get_comm_map(string mazename, object room); // ��ȡ�Թ���ͨ��ͼ 
public string get_deep_map(string mazename, object room); // ��ȡ�Թ���ϸ��ͼ
public object trip_maze(string mazename, object room);    // ˤ�ӵ��������   
public void lostmap_maze(string mazename);                // �Թ���ͼʧЧ    
public void remove_xianjing(string mazename, object room);// ���ָ�����������  
public void openmap_maze(string mazename);                // �����Թ���ϸ��ͼ 
public void del_npc_skill(string mazename);               // ����NPC���书    

// ר��������õĽӿں���
public string* query_all_maze();                          // �����Թ������б�   
public mapping query_maze(string mazename);               // ����ָ���Թ�����ϸ��Ϣ  
public void set_locate_show(string mazename);             // ����ָ���Թ��Ƿ���ʾ������ڵ�λ��  

void create()
{
        seteuid(getuid());
        set("channel_id", "�Թ�����");
        CHANNEL_D->do_channel(this_object(), "sys", "�Թ�ϵͳ�Ѿ�������");
        mazelist = ([ ]);
        collect_all_maze_information();
        set_heart_beat(HEART_TIME);
}

// �Թ�ϵͳ����������ʱ���ռ������Թ��������Ϣ
void collect_all_maze_information()
{
        // �����е��Թ�����ȫ�����
        int i, room_num;
        object *obs;
        
        obs = children(ROOM_FILE);
    
        room_num = sizeof(obs);
        if ( !room_num ) return;
    
        for ( i = 0; i < sizeof(obs); i++ )
                obs[i]->destruct_me();
    
        return;
}

private void heart_beat()
{
        int i, maze_num;
        array maze_key;
    
        // ����ʱ���Թ�������NPC�Ѿ���ʧ���Թ�
        if ( !mapp(mazelist) ) return;

        maze_key = keys(mazelist);
        if ( !arrayp(maze_key) ) return;

        maze_num = sizeof(maze_key);
        if ( !maze_num ) return;
        
        for ( i = 0; i < sizeof(maze_key); i++ )
                check_maze(maze_key[i]);
        
        return;
}

public void check_maze(string mazename)
{
        mapping maze;
        mixed roomlist;
        int w, l;
    
        if ( !stringp(mazename) ) return;
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) ) return;
             
        maze = mazelist[mazename];
        
        if ( !objectp(maze["boss"]) || 
             time() - maze["born_time"] > MAZE_LIFT_CYCLE )
        {
                if ( undefinedp(maze["roomlist"]) )
                {
                        map_delete(mazelist, mazename);
                        return;
                }
                
                roomlist = maze["roomlist"];
                for (w = 0; w < sizeof(roomlist); w++)
                        for (l = 0; l < sizeof(roomlist[w]); l++)
                                if ( objectp(roomlist[w][l]) )      
                                        roomlist[w][l]->destruct_me();
                                        
                map_delete(mazelist, mazename);
        }

        return;
}

public void remove_maze(string mazename)
{
        mapping maze;
        mixed roomlist;
        int w, l;
    
        if ( !stringp(mazename) ) return;
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) ) return;
    
        maze = mazelist[mazename];

        if ( undefinedp(maze["roomlist"]) )
        {
                map_delete(mazelist, mazename);
                return;
        }
    
        roomlist = maze["roomlist"];
        for (w = 0; w < sizeof(roomlist); w++)
                for (l = 0; l < sizeof(roomlist[w]); l++)
                        if ( objectp(roomlist[w][l]) )
                                roomlist[w][l]->destruct_me();
                                
        map_delete(mazelist, mazename);

        return;
}

public object create_maze(object npc)
{
        int i, j;
        string entry_name = "";
        string mazename;        /* �Թ�����         */
        mapping tempmaze;       /* �Թ�ʵ��         */
        mixed mazeroom;         /* �Թ��������     */
        int *entry;             /* �Թ���� */
        int *target;            /* �Թ����� */
        object temp_room;
    
        if ( !objectp(npc) || !npc->is_character() || !stringp(npc->name()) )
                return 0;
    
        // �����Թ������֣�Ψһֵ��
        mazename = sprintf("%s-%d", npc->name(), mazeindex);
        mazeindex ++;
    
        tempmaze = ([ ]);

        // �����Թ��Ĵ���ʱ��
        tempmaze["born_time"] = time();
    
        // �Թ���ͼ��ʼ��Ϊ��ͨģʽ
        tempmaze["map_status"] = MAP_COMM;

        // �����Թ��з��õ�NPC
        tempmaze["boss"] = npc;

        // �����Թ��ķ���
        tempmaze["direction"] = random(4);  //��������Թ��ķ���

        // �����Թ�����ںͳ���
        entry = ({0,0});
        target = ({0,0});
    
        switch(tempmaze["direction"])
        {
        case TO_NORTH:
                entry[0] = HEIGHT - 1;
                entry[1] = random(LENGTH);
                target[0] = 0;
                target[1] = random(LENGTH);
                break;
        case TO_SOUTH:
                entry[0] = 0;
                entry[1] = random(LENGTH);
                target[0] = HEIGHT - 1;
                target[1] = random(LENGTH);
                break;
        case TO_WEST:
                entry[0] = random(HEIGHT);
                entry[1] = LENGTH - 1;
                target[0] = random(HEIGHT);
                target[1] = 0;
                break;
        default:
                entry[0] = random(HEIGHT);
                entry[1] = 0;
                target[0] = random(HEIGHT);
                target[1] = LENGTH - 1;
                break;
        }
        
        tempmaze["entry"] = entry;
        tempmaze["target"] = target;

        // �����Թ��ķ������    
        mazeroom = allocate(HEIGHT);
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                mazeroom[i] = allocate(LENGTH);
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        temp_room = new(ROOM_FILE);
                        temp_room->set("maze/x", i);
                        temp_room->set("maze/y", j);
                        temp_room->delete("exits");
                        temp_room->set("maze/roomtype", NOT_DEFINED);
                        temp_room->set("maze/north", NOT_DEFINED);
                        temp_room->set("maze/south", NOT_DEFINED);
                        temp_room->set("maze/west", NOT_DEFINED);
                        temp_room->set("maze/east", NOT_DEFINED);
                        temp_room->set("maze/mazename", mazename);
            
                        // ���Թ�����ڷ�����ϱ��
                        if ( i == entry[0] && j == entry[1] )
                        {
                                temp_room->set("short", "�Թ����");
                                temp_room->set("maze/entry", 1);
                        }
                        // ���Թ��ĳ��ڷ�����ϱ��
                        else if ( i == target[0] && j == target[1] )
                        {
                                temp_room->set("short", "�Թ�����");
                                temp_room->set("maze/target", 1);
                        }
                        
                        mazeroom[i][j] = temp_room;
                }
        }
        
        tempmaze["roomlist"] = mazeroom;
    
        // ���Թ��ֲ����������
        init_special_room(tempmaze);

        // ���Թ������ػ����̹���
        mazelist[mazename] = tempmaze;

        // �����Թ�����
        init_maze(mazename);
    
        // �����Թ��ĳ��ڷ���
        return tempmaze["roomlist"][target[0]][target[1]];
}

void init_line(mapping maze)
{
        mixed line;        /* ��·�ߵ��Թ���ͼ     */
        mixed line2;       /* ����·�ߵ��Թ���ͼ   */
        int i, j;
        mixed roomlist;
        object room;
    
        if ( !mapp(maze) ) return;
        if ( undefinedp(maze["roomlist"]) ) return;

        roomlist = maze["roomlist"];
    
        line = allocate(HEIGHT*2+1);
        line2 = allocate(HEIGHT*2+1);

        for ( i = 0; i < sizeof(line); i++ )
        {
                line[i] = allocate(LENGTH*2+1);
                line2[i] = allocate(LENGTH*2+1);
                for ( j = 0; j < sizeof(line[i]); j++ )
                {
                        if ( i%2 == 1 )
                        {
                                if ( j%2 == 1 )
                                {
                                        room = roomlist[i/2][j/2];
                                        if ( objectp(room) && room->query("maze/xianjing") )
                                        {
                                                line[i][j] = BMAG "��" NOR;
                                                line2[i][j] = "��";
                                        }
                                        else if ( objectp(room) && room->query("maze/box") )
                                        {
                                                line[i][j] = BYEL "��" NOR;
                                                line2[i][j] = "��";
                                        }
                                        else
                                                line[i][j] = line2[i][j] = "��";
                                } 
                                else
                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                        } 
                        else
                        {
                                if ( j%2 == 1 )
                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                else
                                {
                                        if ( i == 0 )
                                        {
                                                if ( j == 0 )
                                                        line[i][j] = line2[i][j] = HIG "��" NOR; 
                                                else if ( j == LENGTH*2 )
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                                else
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                        } 
                                        else if ( i == HEIGHT * 2 )
                                        {
                                                if ( j == 0 )
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                                else if ( j == LENGTH*2 )
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                                else
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                        } 
                                        else
                                        {
                                                if ( j == 0 )
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                                else if ( j == LENGTH*2 )
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                                else
                                                        line[i][j] = line2[i][j] = HIG "��" NOR;
                                        }
                                }
                        }
                }
        }
    
        maze["deep_map"] = line;
        maze["comm_map"] = line2;
}

public string get_comm_map(string mazename, object room)
{
        string map = "\n�Թ���ͼ��\n" WHT "��ɫ����" NOR "��ʾ�Թ���ڣ�" 
                                      RED "��ɫ����" NOR "��ʾ�Թ����ڣ�" 
                                      HIB "��ɫ�����" NOR "��ʾ�㵱ǰ��λ�á�\n";
        mapping maze;
        mixed line;
        int i,j;
        int w, l;
    
        if ( undefinedp(mazelist[mazename]) )
                return "�Թ�ʵ�岻���ڡ�\n";
    
        maze = mazelist[mazename];
    
        if ( maze["map_status"] == MAP_NONE )
                return 0;
    
        if ( maze["map_status"] == MAP_DEEP )
                return get_deep_map(mazename, room);
    
        if ( undefinedp(maze["comm_map"]) )
                return "�Թ���ͼ�����ڡ�\n";
    
        if ( objectp(room) )
        {
                w = room->query("maze/x");
                l = room->query("maze/y");
        } 
        else
        {
                w = -10;
                l = -10;
        }

        line = maze["comm_map"];
    
        for ( i = 0; i < sizeof(line); i++ )
        {
                for ( j = 0; j < sizeof(line[i]); j++ )
                {
                        if ( show_local_room && i == w*2+1 && j == l*2+1 )
                                map += replace_string(line[i][j], "��", HIB "��" NOR);
                        else
                                map += line[i][j];
                }
                map += "\n";
        }
    
        return map;
}

public string get_deep_map(string mazename, object room)
{
        string map = "\n�Թ���ͼ��\n" WHT "��ɫ����" NOR "��ʾ�Թ���ڣ�" 
                                      RED "��ɫ����" NOR "��ʾ�Թ����ڣ�" 
                                      HIB "��ɫ�����" NOR "��ʾ�㵱ǰ��λ�á�\n" 
                                      YEL "��ɫ����" NOR "��ʾ�б��䣻" 
                                      MAG "��ɫ����" NOR "��ʾ�����塣\n";
        mapping maze;
        mixed line;
        int i, j;
        int w, l;
    
        if ( undefinedp(mazelist[mazename]) )
                return "�Թ�ʵ�岻���ڡ�\n";
    
        maze = mazelist[mazename];
    
        if ( undefinedp(maze["deep_map"]) )
                return "�Թ���ͼ�����ڡ�\n";

        if ( objectp(room) )
        {
                w = room->query("maze/x");
                l = room->query("maze/y");
        } 
        else
        {
                w = -10;
                l = -10;
        }
    
        line = maze["deep_map"];
    
        for ( i = 0; i < sizeof(line); i++ )
        {
                for ( j = 0; j < sizeof(line[i]); j++ )
                {
                        if ( i == w*2+1 && j == l*2+1 )
                                map += replace_string(line[i][j], "��", HIB "��" NOR);
                        else
                                map += line[i][j];
                }
                map += "\n";
        }
    
        return map;
}

public void init_maze(string mazename)
{
        int i,j,w,l,room_ok;
        object *roomlist, temp_room;
        mixed mazeroom;
        mapping maze;
        object *dead_room;
        int dead_num;
    
        if ( undefinedp(mazelist[mazename]) )
                return;
    
        maze = mazelist[mazename];    

        if ( undefinedp(maze["roomlist"]) )
                return;
    
        mazeroom = maze["roomlist"];

        // ��ʼ���Թ���ͼ
        init_line(maze);

        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        temp_room = mazeroom[i][j];
                        temp_room->delete("exits");
                        temp_room->set("maze/roomtype", NOT_DEFINED);
                        temp_room->set("maze/north", NOT_DEFINED);
                        temp_room->set("maze/south", NOT_DEFINED);
                        temp_room->set("maze/west", NOT_DEFINED);
                        temp_room->set("maze/east", NOT_DEFINED);
                        temp_room->delete("maze/dead_room");
                }
        }

        // ��ʼ���Թ�·��
        init_road(mazeroom[maze["entry"][0]][maze["entry"][1]], maze);
    
        // ��·���ϵķ��������·
        roomlist = ({ });
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        if ( mazeroom[i][j]->query("maze/roomtype") == IS_ROAD )
                                roomlist += ({ mazeroom[i][j] });
                }
        }
    
        for ( i = 0; i < sizeof(roomlist); i++ )
                init_wall(roomlist[i], maze);
    
        // �������ķ���ȫ����ͨ
        dead_room_list = ({ });
        all_dead_room = ({ });
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++ )
                {
                        if ( mazeroom[i][j]->query("maze/roomtype") == NOT_DEFINED )
                        {
                                dead_room = finish_room(mazeroom[i][j], maze);
                                if ( arrayp(dead_room) ) dead_room_list += ({ dead_room });
                        }
                }
        }
    
        dead_num = sizeof(dead_room_list);
        if ( dead_num )
        {
                for ( i = 0; i < sizeof(dead_room_list); i++ )
                {
                        room_ok = 0;
                        // �����Թ���ÿ�����䣬���Ƿ���Ժ������ط���ͨ����
                        for ( j = 0; j < sizeof(dead_room_list[i]); j++ )
                        {
                                temp_room = dead_room_list[i][j];
                                w = temp_room->query("maze/x");
                                l = temp_room->query("maze/y");
                                if ( temp_room->query("maze/north") != CAN_WALK && w > 0 &&
                                     member_array(mazeroom[w-1][l], all_dead_room) == -1 )
                                {
                                        temp_room->set("maze/north", CAN_WALK);
                                        mazeroom[w-1][l]->set("maze/south", CAN_WALK);
                                        maze["deep_map"][w*2][l*2+1] = "��";
                                        maze["comm_map"][w*2][l*2+1] = "��";
                                        room_ok = 1;
                                } else 
                                if ( temp_room->query("maze/south") != CAN_WALK && w < HEIGHT - 1 &&
                                     member_array(mazeroom[w+1][l], all_dead_room) == -1)
                                {
                                        temp_room->set("maze/south", CAN_WALK);
                                        mazeroom[w+1][l]->set("maze/north", CAN_WALK);
                                        maze["deep_map"][w*2+2][l*2+1] = "��";
                                        maze["comm_map"][w*2+2][l*2+1] = "��";
                                        room_ok = 1;
                                } else 
                                if ( temp_room->query("maze/west") != CAN_WALK && l > 0 &&
                                     member_array(mazeroom[w][l-1], all_dead_room) == -1)
                                {
                                        temp_room->set("maze/west", CAN_WALK);
                                        mazeroom[w][l-1]->set("maze/east", CAN_WALK);
                                        maze["deep_map"][w*2+1][l*2] = "��";
                                        maze["comm_map"][w*2+1][l*2] = "��";
                                        room_ok = 1;
                                } else
                                if ( temp_room->query("maze/east") != CAN_WALK && l < LENGTH - 1 &&
                                     member_array(mazeroom[w][l+1], all_dead_room) == -1)
                                {
                                        temp_room->set("maze/east", CAN_WALK);
                                        mazeroom[w][l+1]->set("maze/west", CAN_WALK);
                                        maze["deep_map"][w*2+1][l*2+2] = "��";
                                        maze["comm_map"][w*2+1][l*2+2] = "��";
                                        room_ok = 1;
                                }
                                
                                if ( room_ok )    // �Թ��Ѿ���ͨ
                                {
                                        // �����Թ��е����з����all_dead_room��ȥ��
                                        for ( room_ok = 0; room_ok < sizeof(dead_room_list[i]); room_ok++ )
                                        {
                                                dead_room_list[i][room_ok]->delete("maze/dead_room");
                                                all_dead_room -= ({ dead_room_list[i][room_ok] });
                                        }
                                        break;
                                }
                        }
                }
        }
        
        if ( sizeof(all_dead_room) )
                log_file("static/maze", sprintf("��%d�������ķ��䡣\n", sizeof(all_dead_room)) );

        dead_room_list = 0;
        all_dead_room = 0;
    
        // ������ĳ���ˢ��
        init_room_exits(maze);

        return;
}

void init_road(object room, mapping maze)
{
        int w, next_w;
        int l, next_l;
        object next_room;
        int *dirs;
        int temp_dir;
        mixed line;
        mixed line2;
        mixed mazeroom;
    
        room->set("maze/roomtype", IS_ROAD);
        line = maze["deep_map"];
        line2 = maze["comm_map"];
        mazeroom = maze["roomlist"];
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        // �Ѿ��������Թ�����
        if ( w == maze["target"][0] && l == maze["target"][1] )
        {
                line[w*2+1][l*2+1] =  HBRED "��" NOR;
                line2[w*2+1][l*2+1] = HBRED "��" NOR;
                return;
        }        
    
        if ( w == maze["entry"][0] && l == maze["entry"][1] ) // �����Թ����
        {
                line[w*2+1][l*2+1] =  HBWHT "��" NOR;
                line2[w*2+1][l*2+1] = HBWHT "��" NOR;
        } 
        else
        {
                // ����Ѿ�����ɫ�ˣ���ʾ�б���������壬���ٸ��ĵ�ͼ
                if ( line[w*2+1][l*2+1] == "��" )
                        line[w*2+1][l*2+1] = BGRN "��" NOR;
        
                // line2[w*2+1][l*2+1] = "��";
        }
    
        dirs = ({ });
        if ( maze["direction"] != TO_EAST && l > 0 &&
             room->query("maze/west") == NOT_DEFINED &&
             (w != maze["target"][0] || l > maze["target"][1]) )
                dirs += ({ WEST });

        if ( maze["direction"] != TO_WEST && l < LENGTH - 1 &&
             room->query("maze/east") == NOT_DEFINED &&
             (w != maze["target"][0] || l < maze["target"][1]) )
                dirs += ({ EAST });

        if (maze["direction"] != TO_SOUTH && w > 0 &&
            room->query("maze/north") == NOT_DEFINED && 
            (l != maze["target"][1] || w > maze["target"][0]) )
                dirs += ({ NORTH });

        if ( maze["direction"] != TO_NORTH && w < HEIGHT - 1 && 
             room->query("maze/south") == NOT_DEFINED && 
             (l != maze["target"][1] || w < maze["target"][0]) )
                dirs += ({ SOUTH });
    
        if ( sizeof(dirs) < 1 ) return;
        
        temp_dir = dirs[random(sizeof(dirs))];
    
        switch(temp_dir)
        {
        case WEST:
                room->set("maze/west", CAN_WALK);
                next_w = w;
                next_l = l - 1;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/east", CAN_WALK);
                line[w*2+1][l*2] = BGRN "��" NOR;
                line2[w*2+1][l*2] = "��";
                break;
        case EAST:
                room->set("maze/east", CAN_WALK);
                next_w = w;
                next_l = l + 1;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/west", CAN_WALK);
                line[w*2+1][l*2+2] = BGRN "��" NOR;
                line2[w*2+1][l*2+2] = "��";
                break;
        case SOUTH:
                room->set("maze/south", CAN_WALK);
                next_w = w + 1;
                next_l = l;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/north", CAN_WALK);
                line[w*2+2][l*2+1] = BGRN "��" NOR;
                line2[w*2+2][l*2+1] = "��";
                break;
        default:
                room->set("maze/north", CAN_WALK);
                next_w = w - 1;
                next_l = l;
                next_room = mazeroom[next_w][next_l];
                next_room->set("maze/south", CAN_WALK);
                line[w*2][l*2+1] = BGRN "��" NOR;
                line2[w*2][l*2+1] = "��";
                break;
        }
    
        init_road(next_room, maze);
    
        return;
}

void init_wall(object room, mapping maze)
{
        int w, next_w;
        int l, next_l;
        object next_room;
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        // ��NORTH���������·
        if ( w > 0 && room->query("maze/north") == NOT_DEFINED )
        {
                next_w = w - 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // ·��ǽ����һ��ĸ���
                        if ( random(2) == 1 )
                        {
                                room->set("maze/north", CAN_WALK);
                                next_room->set("maze/south", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2][l*2+1] = "��";
                                maze["comm_map"][w*2][l*2+1] = "��";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/north", IS_WALL);
                                next_room->set("maze/south", IS_WALL);
                        }
                }
        }
    
        // ��SOUTH���������·
        if ( w < HEIGHT - 1 && room->query("maze/south") == NOT_DEFINED )
        {
                next_w = w + 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // ·��ǽ����һ��ĸ���
                        if ( random(2) == 1 )
                        {
                                room->set("maze/south", CAN_WALK);
                                next_room->set("maze/north", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2+2][l*2+1] = "��";
                                maze["comm_map"][w*2+2][l*2+1] = "��";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/south", IS_WALL);
                                next_room->set("maze/north", IS_WALL);
                        }
                }
        }

        // ��EAST���������·
        if ( l < LENGTH - 1 && room->query("maze/east") == NOT_DEFINED )
        {
                next_w = w;
                next_l = l + 1;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // ·��ǽ����һ��ĸ���
                        if ( random(2) == 1 )
                        {
                                room->set("maze/east", CAN_WALK);
                                next_room->set("maze/west", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2+1][l*2+2] = "��";
                                maze["comm_map"][w*2+1][l*2+2] = "��";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/east", IS_WALL);
                                next_room->set("maze/west", IS_WALL);
                        }
                }
        }

        // ��WEST���������·
        if ( l > 0 && room->query("maze/west") == NOT_DEFINED )
        {
                next_w = w;
                next_l = l - 1;
                next_room = maze["roomlist"][next_w][next_l];
                if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                {
                        // ·��ǽ����һ��ĸ���
                        if ( random(2) == 1 )
                        {
                                room->set("maze/west", CAN_WALK);
                                next_room->set("maze/east", CAN_WALK);
                                next_room->set("maze/roomtype", IS_ROOM);
                                maze["deep_map"][w*2+1][l*2] = "��";
                                maze["comm_map"][w*2+1][l*2] = "��";
                                init_wall(next_room, maze);
                        }
                        else
                        {
                                room->set("maze/west", IS_WALL);
                                next_room->set("maze/east", IS_WALL);
                        }
                }
        }
    
        return;
}

object *finish_room(object room, mapping maze)
{
        int *dirs;
        int temp_dir;
        int w, next_w;
        int l, next_l;
        object next_room;
        object *result = 0;
        object *dead_room;
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        // ���������һ����ʱ��ǣ���֤�ڵݹ�����в��ᱻ�ظ�����
        room->set("maze/finish_room", 1);
    
        dirs = ({ });
        if ( l > 0 && room->query("maze/west") != CAN_WALK && 
            !maze["roomlist"][w][l-1]->query("maze/finish_room") && 
            !maze["roomlist"][w][l-1]->query("maze/dead_room") )
                dirs += ({ WEST });

        if ( l < LENGTH-1 && room->query("maze/east") != CAN_WALK && 
            !maze["roomlist"][w][l+1]->query("maze/finish_room") && 
            !maze["roomlist"][w][l+1]->query("maze/dead_room") )
                dirs += ({ EAST });

        if ( w > 0 && room->query("maze/north") != CAN_WALK && 
             !maze["roomlist"][w-1][l]->query("maze/finish_room") && 
             !maze["roomlist"][w-1][l]->query("maze/dead_room") )
                dirs += ({ NORTH });

        if ( w < HEIGHT-1 && room->query("maze/south") != CAN_WALK && 
            !maze["roomlist"][w+1][l]->query("maze/finish_room") && 
            !maze["roomlist"][w+1][l]->query("maze/dead_room") )
                dirs += ({ SOUTH });
    
        if ( sizeof(dirs) < 1 ) 
        {   
                room->delete("maze/finish_room");
                if ( room->query("maze/roomtype") == NOT_DEFINED )
                {
                        room->set("maze/dead_room", 1);
                        room->set("maze/roomtype", IS_ROOM);
                        dead_room = ({ room });
                        all_dead_room += ({ room });
                        return dead_room;
                }
                else
                {
                        return 0;
                }
        }
    
        temp_dir = dirs[random(sizeof(dirs))];
    
        switch(temp_dir)
        {   
        case NORTH:
                next_w = w - 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/north", CAN_WALK);
                next_room->set("maze/south", CAN_WALK);
                maze["deep_map"][w*2][l*2+1] = "��";
                maze["comm_map"][w*2][l*2+1] = "��";
                break;
        case SOUTH:
                next_w = w + 1;
                next_l = l;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/south", CAN_WALK);
                next_room->set("maze/north", CAN_WALK);
                maze["deep_map"][w*2+2][l*2+1] = "��";
                maze["comm_map"][w*2+2][l*2+1] = "��";
                break;
        case WEST:
                next_w = w;
                next_l = l - 1;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/west", CAN_WALK);
                next_room->set("maze/east", CAN_WALK);
                maze["deep_map"][w*2+1][l*2] = "��";
                maze["comm_map"][w*2+1][l*2] = "��";
                break;
        default:
                next_w = w;
                next_l = l + 1;
                next_room = maze["roomlist"][next_w][next_l];
                room->set("maze/east", CAN_WALK);
                next_room->set("maze/west", CAN_WALK);
                maze["deep_map"][w*2+1][l*2+2] = "��";
                maze["comm_map"][w*2+1][l*2+2] = "��";
                break;
        }
    
        if ( next_room->query("maze/roomtype") == NOT_DEFINED )
                result = finish_room(next_room, maze);
    
        room->set("maze/roomtype", IS_ROOM);
        room->delete("maze/finish_room");

        if ( arrayp(result) )
        {
                room->set("maze/dead_room", 1);
                result += ({ room });
                all_dead_room += ({ room });
        }    

        return result;
}

void init_special_room(mapping maze)
{
        mixed roomlist;
        int box_num, xianjing_num;
        int w, l;
        object *allroom, room;
        int xianjing_type;
        int box_type;
        object baoxiang;
    
        if ( !mapp(maze) || undefinedp(maze["roomlist"]) ) return;
    
        roomlist = maze["roomlist"];
        allroom = ({ });
    
        for ( w = 0; w < sizeof(roomlist); w++ )
        {
                for (l = 0; l < sizeof(roomlist); l++ )
                {
                        if ( roomlist[w][l]->query("maze/entry") || 
                             roomlist[w][l]->query("maze/target") )
                                continue;
            
                        allroom += ({ roomlist[w][l] });
                }
        }
        
        // �ֲ�����
        box_num = 0;
        // ���ȷ��õ�ͼ�����Ǳ����е�
        room = allroom[random(sizeof(allroom))];
        room->set("maze/box", SPECIAL_MAP);
        baoxiang = new(BAOXIANG_OB);
        if ( baoxiang )
        {
                baoxiang->set("maze/mazename", room->query("maze/mazename"));
                baoxiang->set("maze/box", SPECIAL_MAP);
                baoxiang->move(room);
        }
        
        allroom -= ({ room });
        box_num ++;    
    
        while ( box_num < BOX_NUM )
        {
                if ( sizeof(allroom) < 1 ) 
                        break;
                        
                room = allroom[random(sizeof(allroom))];
                baoxiang = new(BAOXIANG_OB);
                baoxiang->set("maze/mazename", room->query("maze/mazename"));
                baoxiang->move(room);

                box_type = random(100);
                if ( box_type > 97 )
                {
                        room->set("maze/box", SPECIAL_DAN);     //�ٷ�֮��
                        baoxiang->set("maze/box", SPECIAL_DAN);
                }
                else if ( box_type > 94 )
                {
                        room->set("maze/box", JINKUAI);         //�ٷ�֮��
                        baoxiang->set("maze/box", JINKUAI);
                }
                else if ( box_type < 15 )
                {
                        room->set("maze/box", GOLD);            //�ٷ�֮ʮ��
                        baoxiang->set("maze/box", GOLD);
                }
                else if ( box_type < 65 )
                {
                        room->set("maze/box", OBJ);             //�ٷ�֮��ʮ
                        baoxiang->set("maze/box", OBJ);
                }
                else if ( box_type < 85 )
                {
                        room->set("maze/box", SPECIAL_OBJ);     //�ٷ�֮��ʮ
                        baoxiang->set("maze/box", SPECIAL_OBJ);
                }
                else
                {
                        if ( base_name(maze["boss"]) == CLASS_D("generate") + "/player_npc" )
                        {
                                room->set("maze/box", NPC_SKILL);
                                baoxiang->set("maze/box", NPC_SKILL);
                        }
                        else
                        {
                                room->set("maze/box", SPECIAL_OBJ); //�ٷ�֮ʮ
                                baoxiang->set("maze/box", SPECIAL_OBJ);
                        }
                }
                
                allroom -= ({ room });
                box_num ++;        
        }

        // �ֲ�����
        xianjing_num = 0;
    
        while ( xianjing_num < XIANJING_NUM )
        {
                if ( sizeof(allroom) < 1 ) 
                        break;
                        
                room = allroom[random(sizeof(allroom))];
                xianjing_type = random(100);
                if ( xianjing_type > 99 )
                        room->set("maze/xianjing", LOSTMAP);    //��ʱ�ر�
                else if ( xianjing_type < 20 )     
                        room->set("maze/xianjing", TRIP);       //�ٷ�֮��ʮ
                else if ( xianjing_type < 40 )
                        room->set("maze/xianjing", CHANGEMAP);  //�ٷ�֮��ʮ
                else if ( xianjing_type < 70 )
                        room->set("maze/xianjing", WOUND);      //�ٷ�֮��ʮ
                else
                        room->set("maze/xianjing", BUSY);       //�ٷ�֮��ʮ
                        
                allroom -= ({ room });
                xianjing_num ++;        
        }
 
        return;   
}

void init_room_exits(mapping maze)
{
        int i, j;
        mixed mazeroom;
        object room;
    
        if ( undefinedp(maze["roomlist"]) )
                return;
    
        mazeroom = maze["roomlist"];
        for ( i = 0; i < sizeof(mazeroom); i++ )
        {
                for ( j = 0; j < sizeof(mazeroom[i]); j++)
                {
                        room = mazeroom[i][j];
                        if ( room->query("maze/north") == CAN_WALK )
                                room->set("exits/north", sprintf("/%O", mazeroom[i-1][j]) );
                        else
                                room->set("exits/north", sprintf("/%O", room) );
                                
                        if ( room->query("maze/south") == CAN_WALK )
                                room->set("exits/south", sprintf("/%O", mazeroom[i+1][j]) );
                        else
                                room->set("exits/south", sprintf("/%O", room) );

                        if ( room->query("maze/west") == CAN_WALK )
                                room->set("exits/west", sprintf("/%O", mazeroom[i][j-1]) );
                        else
                                room->set("exits/west", sprintf("/%O", room) );

                        if ( room->query("maze/east") == CAN_WALK )
                                room->set("exits/east", sprintf("/%O", mazeroom[i][j+1]) );
                        else
                                room->set("exits/east", sprintf("/%O", room) );
            
                        // ���Թ��ĳ��ڷ������ӳ���
                        if ( room->query("maze/target") )
                                room->set("exits/out", ROOM_EXIT_FILE);
                }
        }
    
        return;
}

public object trip_maze(string mazename, object room)
{
        mapping maze;
        mixed roomlist;
        int w, l;
        object next_room;
    
        if ( !stringp(mazename) || !objectp(room) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        if ( undefinedp(maze["roomlist"]) )
                return 0;
    
        roomlist = maze["roomlist"];
    
        next_room = 0;
        while ( 1 )
        {
                w = random(HEIGHT);
                l = random(LENGTH);
       
                next_room = roomlist[w][l];
                if ( !objectp(next_room) ) break;
                if ( next_room->query("maze/target") ) continue;    // �������Թ�����
                if ( next_room->query("maze/xianjing") ) continue;  // ��������һ������
                if ( w == room->query("maze/x") && 
                     l == room->query("maze/y") ) continue;         // �����Ǹ÷��䱾��

                break;
        }
   
        return next_room;
}

public void lostmap_maze(string mazename)
{
        mapping maze;
    
        if ( !stringp(mazename) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        maze["map_status"] = MAP_NONE;
    
        return;
}

public void openmap_maze(string mazename)
{
        mapping maze;
    
        if ( !stringp(mazename) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        maze["map_status"] = MAP_DEEP;
    
        return;
}

public void del_npc_skill(string mazename)
{
        mapping maze;
        object npc;
        mapping skill_status;
        array sname;
        int i, temp, now_lvl;
    
        if ( !stringp(mazename) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
        npc = maze["boss"];
    
        if ( !npc ) return;
        
        if ( mapp(skill_status = npc->query_skills()) )
        {
                skill_status = npc->query_skills();
                sname = keys(skill_status);

                temp = sizeof(skill_status);
                for ( i = 0; i < temp; i++ )
                {
                        now_lvl = skill_status[sname[i]] + 2;
                        npc->set_skill(sname[i], now_lvl/2);
                }
        }
    
        return;
}

public void remove_xianjing(string mazename, object room)
{
        mapping maze;
        mixed line;
        int w, l;
        object next_room;
    
        if ( !stringp(mazename) || !objectp(room) )
                return 0;
    
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) )
                return 0;
    
        maze = mazelist[mazename];
    
        if ( undefinedp(maze["deep_map"]) )
                return 0;
    
        line = maze["deep_map"];
    
        w = room->query("maze/x");
        l = room->query("maze/y");
    
        if ( room->query("maze/roomtype") == IS_ROAD )
                line[w*2+1][l*2+1] = BGRN "��" NOR;
        else
                line[w*2+1][l*2+1] = "��";
    
        return;
}

public void set_local_show(int arg)
{
        if ( !intp(arg) ) arg = 0;
        show_local_room = arg;
}

public string* query_all_maze()
{
        array mazes;
        mazes = ({ });

        if ( !mapp(mazelist) ) return mazes;
    
        mazes = keys(mazelist);
        return mazes;
}

public mapping query_maze(string mazename)
{
        mapping result;
        mapping maze;

        result = ([]);
        if ( !stringp(mazename) ) return 0;
        if ( !mapp(mazelist) || undefinedp(mazelist[mazename]) ) return 0;

        maze = mazelist[mazename];
        result["boss"] = maze["boss"];
        result["player"] = maze["boss"]?maze["boss"]->query_temp("quester"):0;
        result["born_time"] = maze["born_time"];
        result["direction"] = maze["direction"];
        result["entry"] = maze["roomlist"][maze["entry"][0]][maze["entry"][1]];
        result["target"] = maze["roomlist"][maze["target"][0]][maze["target"][1]];
        result["map_status"] = maze["map_status"];
        result["deep_map"] = maze["deep_map"];
        
        return result;    
}

/*************************����-�����Թ�********************************/
#define MAZE                    "maze.c"
#define ENTRY                   "enter.c"
#define EXIT                    "out.c"
#define MAZE_DIR                "/data/maze/"  

public string query_maze_file(string x, string y)
{
        return sprintf(MAZE_DIR + "%s/%s/", x, y);
}

protected mixed create_maze_file(object me, string maze)
{
        string src, dst;
        string filename;
        string dir1, dir2;
        
        dir1 = "/d/maze/" + maze + "/";
        dir2 = query_maze_file(me->query("id"), maze);
                
        src = dir1 + MAZE;
        dst = dir2 + MAZE;
        assure_file(dst);
        cp(src, dst);
        
        src = dir1 + ENTRY;
        dst = dir2 + ENTRY;
        filename = dst;
        cp(src, dst);
        
        src = dir1 + EXIT;
        dst = dir2 + EXIT;
        cp(src, dst);
        
        return filename;
}

public int enter_virtual_maze(object me, string arg) 
{
        string enter_file, maze_file;
        object *member, room;
        object *inv, maze;
        string id, dir;
        int min, max;
        
        if ( me->query_condition("killer") )
        {
                tell_object(me, "ɱ��ͨ�����ǲ��ܽ��븱���ġ�\n");
                return 0;
        }

        inv = deep_inventory(me);
        if ( inv && sizeof(inv) > 0 )
        {
                foreach ( object ob1 in inv ) 
                        if( ob1 && ob1->is_character() ) 
                        {
                                tell_object(me, "�㲻���Խ�������һ���NPC(��������)���������ڡ�\n");
                                return 0;
                        }
        }
                
        member = me->query_team_member(); 
        if ( !member || !sizeof(member) )
                id = me->query("id");
        else        
                id = me->query_team_leader()->query("id");  
                    
        dir = query_maze_file(id, arg);        
        enter_file = dir + ENTRY;
        
        // �Ѿ�������
        if ( file_size(enter_file) > 0 )
        {
                // û�б�����
                room = find_object(enter_file);
                if ( !room  )
                {                        
                        if ( sizeof(member) && !me->is_team_leader() )
                        { 
                                tell_object(me, "�����ɶӳ���������������ġ�\n");
                                return 0;
                        }    
                                                                                 
                        room = load_object(enter_file);
                }
                // �Ѿ��������
        } else  // û�д�����  
        {      
                dir = query_maze_file(me->query("id"), arg);                       
                enter_file = create_maze_file(me, arg);  
                if ( !enter_file )
                {
                        tell_object(me, "��������ʧ�ܡ�\n");
                        return 0;
                }              
                             
                room = load_object(enter_file);
        }
        
        maze_file = dir + MAZE; 
        maze = find_object(maze_file);
        if (! maze) maze = load_object(maze_file);
        
        min = maze->query_enter_minlevel();
        max = maze->query_enter_maxlevel();
        
        if (me->query("level") < min || (max && me->query("level") > max))
        {
                tell_object(me, HIW "����Ҫ����͵ȼ�Ϊ " + min + " ��" + 
                                (max ? "��ߵȼ�Ϊ " + max + " ��" : "") + 
                                "���޷����븱����\n" NOR);
                return 0;
        }                
               
        tell_object(me, HIR "ף���������\n" NOR);
        me->move(room); 
        return 1;
}

public mixed query_maze_dir(object ob) 
{
        object env;
        string user, maze, dir;
        
        env = environment(ob);
        if( !env ) return 0;

        if( sscanf(base_name(env), MAZE_DIR + "%s/%s/%*s", user, maze) != 3 )
                return 0;
                
        dir = query_maze_file(user, maze);      
        return dir;
}

public object query_maze_mainobj(object ob) 
{
        string file;
        
        file = query_maze_dir(ob) + MAZE;      
        return get_object(file);
}
