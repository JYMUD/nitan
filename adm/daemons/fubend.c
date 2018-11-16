// fubend.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit F_DBASE;

#define FUBEN_PRE_DIR   0
#define FUBEN_NAME_DIR  1
#define FUBEN_OWNER_DIR 2
#define FUBEN_ROOM_DIR  3

#define VALID_CREATE_NUMBER     3
#define DELAY_CLEAR_TIME        30
#define FUBEN_MAIN_DIR          "/maze"

int state = 1;
string *valid_fbname = ({});
nosave mapping all = ([]);
nosave mapping fuben_list = ([]);
nosave mapping fuben_data = ([]);
nosave mapping fuben_all  = ([]);
protected void load_all_fuben();
protected void load_fuben_list(string fbname);
protected void load_fuben_data(string fbname);
public mapping query_fuben_all() { return fuben_all; }
public mapping query_fuben_list() { return fuben_list; }
public mapping query_fuben_data() { return fuben_data; }

int clean_up() { return 1; }

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "��������");
        CHANNEL_D->do_channel(this_object(), "sys", "����ϵͳ�Ѿ�������");
        load_all_fuben();
}

public mixed compile_object(string file)
{
        mapping exits;
        int idx;
        object maze, ob;
        string *dir, *key;
        string fbname, owner, tmp;
        string filename, pname = file;

        dir = explode(file, "/");
        if( sizeof(dir) <= FUBEN_ROOM_DIR ) return 0;

        fbname = dir[FUBEN_NAME_DIR];
        owner = dir[FUBEN_OWNER_DIR];
        dir[FUBEN_PRE_DIR] = FUBEN_MAIN_DIR;
        dir -= ({ owner });
        filename = implode(dir, "/");
        if( file_size(filename + ".c") > 0 ) {
                if( objectp(ob = load_object( filename )) ) {
                        exits=query("exits", ob);
                        if( mapp(exits) && sizeof(exits) > 0 ) {
                                key = keys(exits);
                                for( int i=0;i<sizeof(key);i++ )
                                        if( sscanf(exits[key[i]], "/maze/"+fbname+"/%s", tmp) )
                                                exits[key[i]] = "/f/"+fbname+"/"+owner+"/"+tmp;
                                set("exits", exits, ob);
                        }
                        return ob;
                } else
                        return 0;
        }
        while( 1 ) {
                idx = strsrch(pname, "/", -1);
                if( idx == -1 )
                        return 0;
                if( idx <= FUBEN_ROOM_DIR )
                        return 0;
                if( idx != 0 )
                        pname = pname[0..idx-1];
                maze = find_object(pname);
                if( !maze ) maze = load_object(pname);
                if(  maze ) {
                        if( ob = maze->query_maze_room(file[idx + 1..]) ) {
                                if( file[idx + 1..] == "entry" ||
                                    file[idx + 1..] == "exit" ) {
                                        exits=query("exits", ob);
                                        if( mapp(exits) && sizeof(exits) > 0 ) {
                                                key = keys(exits);
                                                for( int i=0;i<sizeof(key);i++ )
                                                        if( sscanf(exits[key[i]], "/maze/"+fbname+"/%s", tmp) )
                                                                exits[key[i]] = "/f/"+fbname+"/"+owner+"/"+tmp;
                                                set("exits", exits, ob);
                                        }
                                }
                                ob->set_virtual_flag();
                                return ob;
                        }
                }
                if( !idx )
                        return 0;
        }
}

public int enter_fuben(object me, string fbname)
{
        object *inv, entry;
        string owner, entrance, filename,ipname;
        int ret, dest_time;

        if( undefinedp(fuben_data[fbname]) ) {
                tell_object(me, "û�����������\n");
                return 0;
        }

        if( me->query_condition("killer") ) {
                tell_object(me, "���Ǳ�ͨ�����ﷸ���޷����븱����\n");
                return 0;
        }

        inv = deep_inventory(me);
        if( sizeof(inv) > 0 ) {
                foreach( object ob in inv ) {
                        if( interactive(ob) || userp(ob) ) {
                                tell_object(me, "�㲻���Խ�������ұ���������\n");
                                return 0;
                        }
                }
        }

        if( !undefinedp(fuben_data[fbname]["team"]) ) {
                if( !me->in_team() ) {
                        tell_object(me, "�������Ӳ��ܽ������������\n");
                        return 0;
                }

                if( !objectp(me->query_team_leader()) ) {
                        tell_object(me, "��Ķ��������������⣡\n");
                        return 0;
                }
                owner=(query("id", me->query_team_leader()));
        } else {
                if( !me->in_team() ) {
                        owner=query("id", me);
                } else {
                        if( !objectp(me->query_team_leader()) ) {
                                tell_object(me, "��Ķ��������������⣡\n");
                                return 0;
                        }
                        owner=(query("id", me->query_team_leader()));
                }
        }

        entrance = fuben_data[fbname]["enter"];
        filename = "/f/"+fbname+"/"+owner+"/"+entrance;
        entry = find_object(filename);
        if( !entry ) {
                if( me->in_team() && !me->is_team_leader() ) {
                        tell_object(me, "�����ɶӳ�������������\n");
                        return 0;
                }
                if( undefinedp(fuben_list[fbname]) )
                        load_fuben_list(fbname);
                entry = load_object(filename);
                dest_time = to_int(fuben_data[fbname]["time"]);
                ret = SCHEDULE_D->set_event(dest_time, 0, this_object(), "delay_clear_fuben", fbname, owner);
                set_temp("fuben_event", ret, me);
                if( undefinedp(fuben_all[fbname]) )
                        fuben_all[fbname] = ([]);
                dest_time += time();
                fuben_all[fbname][owner] = dest_time;

                if( !undefinedp(fuben_data[fbname]["interval"]) )
                        set("fuben/"+fbname, time(), me);

                if( !MEMBER_D->is_valid_member(owner) ) {
                        ipname = query_ip_number(me);
                        if( undefinedp(all[fbname]) )
                                all[fbname] = ([]);
                        if( undefinedp(all[fbname][ipname]) )
                                all[fbname][ipname]  = ({ owner });
                        else
                                all[fbname][ipname] += ({ owner });
                }
        }

        if( entry ) {
                /*
                CHANNEL_D->do_channel(this_object(),"sys",
                        query("name", me)+"("+query("id", me)+")"+"�����˸���"+fbname+"("+owner+")��");
                */
                tell_object(me, HIR "ף���������\n" NOR);
                me->move(entry);

                return 1;
        }
        return 0;
}

protected void load_all_fuben()
{
        int i;
        string *dir;

        dir = get_dir(FUBEN_MAIN_DIR+"/");
        for( i=0;i<sizeof(dir);i++ ) {
                if( file_size(FUBEN_MAIN_DIR+"/"+dir[i]) == -2 ) {
                        load_fuben_list(dir[i]);
                        load_fuben_data(dir[i]);
                }
        }
}

protected void load_fuben_list(string fbname)
{
        string *files, *dir;
        string file;
        int i;

        file = FUBEN_MAIN_DIR+"/"+fbname+"/";
        dir = get_dir(file);
        files = ({});
        for( i=0;i<sizeof(dir);i++ ) {
                if( is_c_file(file + dir[i]) )
                        files += ({ dir[i] });
        }
        fuben_list[fbname] = files;
        return;
}

protected void load_fuben_data(string fbname)
{
        mixed lines;
        string file,key,value;
        int i,sz;

        file = CONFIG_DIR+"fuben/"+fbname+".data";
        if( file_size(file) < 0 ) return;
        file = replace_string(read_file(file),"\r","");
        lines = explode(file,"\n");
        fuben_data[fbname] = ([]);
        sz = sizeof(lines);
        for( i=0;i<sz;i++ ) {
                if( !stringp(lines[i]) || lines[i]=="" ||
                    sscanf(lines[i],"%s=%s",key,value)!=2 )
                        continue;
                fuben_data[fbname][key] = value;
        }
}

public mixed query_fuben_owner(object ob)
{
        string file;
        string *dir;
        file = base_name(environment(ob));
        dir = explode(file,"/");
        if( sizeof(dir) <= FUBEN_ROOM_DIR ) {
                return 0;
        }
        return dir[FUBEN_OWNER_DIR];
}

public mixed query_fuben_name(object ob)
{
        string file;
        string *dir;
        file = base_name(environment(ob));
        dir = explode(file,"/");
        if( sizeof(dir) <= FUBEN_ROOM_DIR ) {
                return 0;
        }
        return dir[FUBEN_NAME_DIR];
}

public mixed query_maze_dir(object ob)
{
        string file;
        string *dir;
        file = base_name(environment(ob));
        dir = explode(file,"/");
        if( sizeof(dir) <= FUBEN_ROOM_DIR ) {
                return 0;
        }
        file = "/"+dir[FUBEN_PRE_DIR]+"/"+dir[FUBEN_NAME_DIR]+"/"+
                dir[FUBEN_OWNER_DIR]+"/";
        return file;
}

public mixed query_maze_mainobj(object ob)
{
        string file,fbname;
        string *dir;
        file=query("mazeobj", environment(ob));
        if( file ) return get_object(file);
        file = base_name(environment(ob));
        dir = explode(file,"/");
        if( sizeof(dir) <= FUBEN_ROOM_DIR ) {
                return 0;
        }
        fbname = dir[FUBEN_NAME_DIR];
        if( undefinedp(fuben_data[fbname]) ||
            undefinedp(fuben_data[fbname]["main"]) ) {
                return 0;
        }
        file = "/"+dir[FUBEN_PRE_DIR]+"/"+dir[FUBEN_NAME_DIR]+"/"+
                dir[FUBEN_OWNER_DIR]+"/"+fuben_data[fbname]["main"];
        return get_object(file);
}

public object *query_fuben_players(string fbname, string owner)
{
        string *key;
        object *inv;
        object room;
        string file;
        int sz,i,j;
        object *ret;
        ret = 0;
        key = fuben_list[fbname];
        sz = sizeof(key);
        ret = ({});
        for( i=0;i<sz;i++ ) {
                file = "/f/"+fbname+"/"+owner+"/"+key[i];
                if( objectp(room=find_object(file)) ) {
                        if( room->is_maze() ) {
                                if( arrayp(inv = room->query_maze_players()) && sizeof(inv) )
                                        ret += inv;
                        } else {
                                if( arrayp(inv =all_inventory(room)) && sizeof(inv) ) {
                                        for( j=sizeof(inv)-1;j>=0;j-- ) {
                                                if( interactive(inv[j]) )
                                                        ret += ({ inv[j] });
                                        }
                                }
                        }
                }
        }
        return ret;
}

public void tell_fuben(string fbname,string owner,string str)
{
        object *ppl;
        ppl = query_fuben_players(fbname,owner);
        if( arrayp(ppl) && sizeof(ppl) )
                tell_team(ppl, str);
}

void clear_maze_item(object user)
{
        object *inv, obj;
        inv = all_inventory(user);
        if( inv && sizeof(inv)>0 )
                foreach( obj in inv ) {
                        if( obj && query("maze_item", obj) )
                                destruct(obj);
                }
}

public int delay_clear_fuben(string fbname,string owner)
{
        tell_fuben(fbname,owner,HBCYN+fuben_data[fbname]["name"]+"("+owner+")��������"+DELAY_CLEAR_TIME+"�����ʧ��\n"NOR);
        call_out("clear_fuben",DELAY_CLEAR_TIME,fbname,owner);
        return 1;
}

public int clear_fuben(string fbname,string owner)
{
        mixed key,*inv;
        object ob,room,outroom;
        string file,out,ipname;
        int sz,i,j;

        if( undefinedp(fuben_list[fbname]) )
                return 0;

        /*
        if( undefinedp(fuben_all[fbname][owner]) )
                return 0;
        */

        key = fuben_list[fbname];
        sz = sizeof(key);

        if( !undefinedp(fuben_data[fbname]["leave"]) ) {
                out = fuben_data[fbname]["leave"];
                if( !sscanf(out, "%*s.c") ) out += ".c";
        }
        if( out ) outroom = get_object(out);
        else      outroom = get_object(VOID_OB);
        tell_fuben(fbname,owner,HBCYN+fuben_data[fbname]["name"]+"("+owner+")�����ռ䱻�ݻ١�\n"NOR);
        for( i=0;i<sz;i++ ) {
                file = "/f/"+fbname+"/"+owner+"/"+key[i];
                if( objectp(room = find_object(file)) ) {
                        if( room->is_maze() )
                                room->remove_all_players(outroom, "һ��ʱ�յ�Ť�����㴫�͵���һ���ط�....\n");
                        else if( arrayp(inv = all_inventory(room)) ) {
                                tell_room(room, "һ��ʱ�յ�Ť�����㴫�͵���һ���ط�....\n");
                                for( j=sizeof(inv)-1;j>=0;j-- ) {
                                        if( interactive(inv[j]) || userp(inv[j]) ) {
                                                clear_maze_item(inv[j]);
                                                inv[j]->move(outroom);
                                        }
                                }
                        }
                        destruct(room);
                }
        }
        if( mapp(fuben_all[fbname]) )
                map_delete(fuben_all[fbname], owner);

        //CHANNEL_D->do_channel(this_object(),"sys","ϵͳ�����˸���"+fbname+"("+owner+")��");

        if( !MEMBER_D->is_valid_member(owner) ) {
                if( undefinedp(all[fbname]) )
                        return 1;
                if( ob = find_player(owner) ) {
                        ipname = query_ip_number(ob);
                } else {
                        ob = new(LOGIN_OB);
                        set("id", owner, ob);
                        if( !ob->restore() ) {
                                destruct(ob);
                                return 1;
                        }
                        ipname=query("last_from", ob);
                        destruct(ob);
                }
                if( undefinedp(all[fbname][ipname]) )
                        return 1;

                all[fbname][ipname] -= ({ owner });
        }
        return 1;
}

public void check_clear(object room)
{
        string name;
        mixed dir;
        object *tmp;
        int sz;
        if( !objectp(room) )
                return;
        name = base_name(room);
        dir = explode(name,"/");
        sz = sizeof(dir);
        if( sz <= FUBEN_ROOM_DIR )
                return;
        if( tmp = query_fuben_players(dir[FUBEN_NAME_DIR],dir[FUBEN_OWNER_DIR]) ) {
                return;
        }
        clear_fuben(dir[FUBEN_NAME_DIR],dir[FUBEN_OWNER_DIR]);
        return;
}

public int valid_enter(object usr, string fbname)
{
        if( !state || member_array(fbname, valid_fbname) != -1 ) {
                tell_object(usr, "�ø�������ʦ�رգ�����ʱ�޷����롣\n");
                return -4;
        }

        if( fbname == "forest" ) {
                if( !undefinedp(all[fbname]) &&
                    !undefinedp(all[fbname][query_ip_number(usr)]) &&
                    !MEMBER_D->is_valid_member(usr) && 
                    sizeof(all[fbname][query_ip_number(usr)]) > VALID_CREATE_NUMBER ) {
                        tell_object(usr, "�ø�������IP���ؽ��룬���Ѿ�����������ޡ�\n");
                        return -3;
                }
        }

        if( undefinedp(fuben_data[fbname]) ) {
                tell_object(usr, "��Ϸ��Ŀǰ��û�п��Ÿø����������˶Ժ����ԡ�\n");
                return -2;
        }

        if( undefinedp(fuben_data[fbname]["level"]) )
                return 1;

        /*
        if( query("level", usr)<to_int(fuben_data[fbname]["level"])){
                tell_object(usr, "��ʵս���鲻�㣬���������в��⣬����������һ�������ɡ�\n");
                return 0;
        }

        if( query("level", usr) >= to_int(fuben_data[fbname]["level"]) ){
                tell_object(usr, "������̫���ˣ��Ͳ�Ҫ��ȥ�۸���Щ������С�����˰ɡ�\n");
                return -1;
        }
        */

        if( !undefinedp(fuben_data[fbname]["interval"]) ) {
                if( time()-query("fuben/"+fbname, usr)<to_int(fuben_data[fbname]["interval"])){
                        tell_object(usr, "�����ϴν��븱��ʱ��̫�̣�����Ϣ��������\n");
                        return -5;
                }
        }

        if( !undefinedp(fuben_data[fbname]["team"]) ) {
                if( !usr->in_team() || !sizeof(usr->query_team()) ) {
                        tell_object(usr, "�ø���������Ӳ��ܽ��롣\n");
                        return -6;
                }

                if( sizeof(usr->query_team()) > to_int(fuben_data[fbname]["team"]) ) {
                        tell_object(usr, "��Ķ������������ø����涨�����ޡ�\n");
                        return -7;
                }
        }

        if( !undefinedp(fuben_data[fbname]["single"]) ) {
                if( usr->in_team() && usr->is_team_leader() ) {
                        tell_object(usr, "�ø����ǵ��˸������������ɢ���鷽�ɽ��롣\n");
                        return -8;
                }
        }

        return 1;
}


public int close_fuben(object me, string fbname)
{
        if( !stringp(fbname) ) {
                tell_object(me, HIC "��������Ҫ�رյĸ���<ID>��\n" NOR);
                return 1;
        }

        if( fbname == "all" ) {
                tell_object(me, HIC "�رո���������ϡ�\n" NOR);
                state = 0;
                return 1;
        } else {
                if( member_array(fbname, valid_fbname) == -1 ) {
                        valid_fbname += ({ fbname });
                        tell_object(me, HIC "�رո���<"+fbname+">������ϡ�\n" NOR);
                } else
                        tell_object(me, HIC "����<"+fbname+">�Ѿ����ڹر��С�\n" NOR);
                return 1;
        }
}

public int open_fuben(object me, string fbname)
{
        if( !stringp(fbname) ) {
                tell_object(me, HIC "��������Ҫ�����ĸ���<ID>��\n" NOR);
                return 1;
        }

        if( fbname == "all" ) {
                tell_object(me, HIC "��������������ϡ�\n" NOR);
                state = 1;
                return 1;
        } else {
                if( member_array(fbname, valid_fbname) != -1 ) {
                        valid_fbname -= ({ fbname });
                        tell_object(me, HIC "��������<"+fbname+">������ϡ�\n" NOR);
                } else
                        tell_object(me, HIC "����<"+fbname+">�Ѿ����ڿ����С�\n" NOR);
                return 1;
        }
}
