// Code of ShenZhou
// map database
// author: chu@xkx
// name: mapdb.c
// date: 5/9/98

//changed by wzfeng add return map

#include <ansi.h>
#ifndef NPCDATA
#define NPCDATA "/data/npc/"
#endif

// max number of nodes we "reload", since it is really expensive and
// may cause server crash, we try to be very prudent here.
#define MAX_NODE 3 

inherit F_SAVE;

int map_ready;   // whether the map has been fully constructed 
mapping map;     // The real map.  see enter_map for its format

void create()
{
    seteuid(getuid());
    if (!restore()) {
        map_ready = 0;
        map = ([]);
    }
}

void debug(string msg)
{
    printf("DEBUG: %s\n", msg);
}

string query_save_file()
{
    return NPCDATA+"map";       // same as genmap.  So that we can get the map
                                // generated by genmap.
}

mapping query_room_info(string room)
{
    return map[room];
}

string query_random_room_path()
{
    return keys(map)[random(sizeof(map))];
}

mapping query_room_exits(string room)
{
    mapping info;

    info = map[room];
    if (mapp(info)) return info["exits"];
    return 0;
}

mapping query_map()
{
return map;
}


