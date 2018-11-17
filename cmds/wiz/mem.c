// mem.c

#include <getconfig.h>
#include <ansi.h>

inherit F_CLEAN_UP;

string memory_expression(int m);
protected varargs void check_memory_info(object me, string file);

int main(object me, string arg)
{
        mixed msg;
        object obj;
        string file;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg)
        {
                write(sprintf( "%s目前共使用 %s bytes 記憶體。\n",
                        LOCAL_MUD_NAME(), memory_expression(memory_info())));
                return 1;
        }

        if (arg == "-m")
        {
                msg = (string)dumpallobj();
                // malloc_status();
                write(msg + "\n");
                return 1;
        }

        if (arg == "-all")
        {
                if (! SECURITY_D->valid_grant(me, "(admin)"))
                        return notify_fail("這個指令參數只能由高級巫師使用。\n");

                check_memory_info(me);
                return 1;
        }
        
        if (sscanf( arg, "-all %s", file) == 1)
        {
                check_memory_info(me, file);
                return 1;
        }
    
        seteuid(geteuid(me));
        obj = find_object(arg);
        if (! obj) obj = present(arg, me);
        if (! obj) obj = present(arg, environment(me));
        if (! obj) obj = find_object( resolve_path(query("cwd", me), arg) );
        if (! obj) return notify_fail("沒有這樣物件....。\n");

        write(sprintf( "%O 共使用 %s bytes 記憶體。\n", obj, memory_expression(memory_info(obj))));
        return 1;
}

string memory_expression(int m)
{
        float mem;

        mem = m;
        if (mem < 1024 ) return m + "";
        if (mem < 1024*1024)
                return sprintf("%.2f K", (float)mem / 1024);
        return sprintf("%.3f M", (float)mem / (1024*1024));
}

protected varargs void check_memory_info(object me, string file)
{
        mixed *obs;
        int i, j;
        int size, tmp, all;
        string msg, str;

        if (stringp(file))
        {
                if (file[<2..<1] != ".c")
                        file += ".c";
                        
                obs = children(file);
                
                if (! sizeof(obs))
                {       
                        write(sprintf("文件 %s 未載入內存。\n", file));
                        return;
                } else
                        obs = unique_array(obs, (: base_name($1) :));
        } 
        else
        {
                obs = objects();
                obs = unique_array(obs, (: base_name($1) :));
        }
        
        if (sizeof(obs) > 1)
        obs = sort_array(obs, (: memory_info($1[0]) * sizeof($1) - memory_info($2[0]) * sizeof($2) :));

        message_system("系統批量數據處理中，請耐心等候..."); 
        
        all = 0;
        msg = "";
        for(i=sizeof(obs)-1;i>=0;i--)
        {
                tmp = 0;
                size = sizeof(obs[i]);
                for(j=size-1;j>=0;j--)
                {
                        tmp += memory_info(obs[i][j]);
                }
                all += tmp;
                str = sprintf("%12s", memory_expression(tmp));
                str = replace_string(str, "K", HIC "K" NOR);
                str = replace_string(str, "M", HIR "M" NOR);
                msg += sprintf("%-50s  %5d 件  %s    %14s / %14s\n",
                               base_name(obs[i][0]), size, str,
                               size > 1 ? memory_expression(memory_info(obs[i][0])) : "--",
                               size > 1 ? memory_expression(tmp / size) : "--");
        }
        
        // write(sprintf("%|50s  %8s  %s    %14s / %14s\n",
        write(sprintf("%-48s  %8s  %s    %14s / %14s\n",
                      "文件名        ",
                      "複製件數量    ",
                      "內存佔用總額  ",
                      "單一佔用(參考)",
                      "平均每件佔用  "));
        me->start_more(msg);
        write(sprintf( "以上合計使用 %s bytes 記憶體。\n", 
                       memory_expression(all) ));
        write(sprintf( "%s目前共使用 %s bytes 記憶體。\n",
                       LOCAL_MUD_NAME(), memory_expression(memory_info()) ));
        message_system("系統批量數據處理完畢，請繼續遊戲。\n" ESC + "[K");   
        return;
}

int help(object me)
{
        write(@HELP
指令格式 : mem <物件之名稱或檔名>

這個指令告訴你某個物件佔用的記憶體數量。
若沒有指明物件, 則會顯示目前遊戲所佔用的記憶體.
HELP );
    return 1;
}
