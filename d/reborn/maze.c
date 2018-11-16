// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit VRM_SERVER;

void create() 
{ 
        // �Թ��������̳е�����ĵ������ơ� 
        set_inherit_room( ROOM );  
                        
        // Ψһ����
        set_unique_room("/d/reborn/unique_room/xinmo_room"); 

        // �Թ�������Ĺ�� 
        set_maze_npcs( ([
                "/d/reborn/npc/shadow": random(2),  
        ]) );   
        
        // �Թ��ĵ��߳� 
        set_maze_long(10); 
                        
        // ��ڷ���(�����ڶ���) 
        set_entry_dir("north"); 
                        
        // �������������ӷ��� 
        set_link_entry_dir("north"); 
                        
        // �������������ӵ����� 
        set_link_entry_room("/d/reborn/jitan1"); 
                        
        // ��������������ӷ��� 
        set_link_exit_dir("south"); 
                        
        // ��������������ӵ����� 
        set_link_exit_room("/d/reborn/jitan1");                        
                        
        // ��ͨ��������
        set_maze_room_short(RED "�þ�" NOR);
                        
        set_maze_room_desc(@LONG
�þ��ﵽ���������������ܱߵľ����������ޣ�������翡�
LONG); 
                        
        // ��ڷ�������� 
        set_entry_short(HIR "�þ����" NOR); 
                        
        // ��ڷ������� 
        set_entry_desc(@LONG
�þ��ﵽ���������������ܱߵľ����������ޣ�������翡�
LONG); 
                        
        // ���ڷ�������� 
        set_exit_short(HIW "�þ�����" NOR); 
                        
        // ���ڷ������� 
        set_exit_desc(@LONG
�þ��ﵽ���������������ܱߵľ����������ޣ�������翡�
LONG); 

        // �Թ������Ƿ�Ϊ���ⷿ�䣿 
        set_outdoors(1); 
        
        set_remove_time(420);
} 

string query_my_map(){  return read_file(__DIR__"maze.map");}

