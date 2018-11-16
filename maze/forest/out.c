inherit ROOM; 

void create() 
{ 
        set("short", "ɭ�ֳ���"); 
        set("long", @LONG 
ԭʼɭ����Ҷ�Ժ���ǣ�������գ����������ſ�Ҷ����
����֬��ϵ�ζ�������ϵ�̦����Ҷ����ȥ������ģ����滹
����Ұ�޵ĺۼ�������Ũ�ܵ�ɽ���������Էֱ淽��
LONG
); 
                        
        set("outdoors", "forest"); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "east":__DIR__"maze/exit",
                "out": "/d/kunming/zhaoze",
        ])); 

        set("objects",([
                "/maze/forest/npc/forest_master": 1,  
        ])); 
                        
        setup();
        // replace_program(ROOM); 
} 

int valid_leave(object me, string dir)
{
        object *inv, obj;
        if (dir == "out")
        {
                tell_object(me, "check!\n");
                inv = deep_inventory(me);
                if (inv && sizeof(inv)>0)
                        foreach(obj in inv) {
                                if( obj && query("maze_item", obj) )
                                        destruct(obj);
                        }
                FUBEN_D->query_maze_mainobj(me)->refresh_maze();
        }
        MYGIFT_D->check_mygift(me, "newbie_mygift/fuben");
        return 1;
}
