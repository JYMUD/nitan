 // refsum.c  
 // by PLZW 2004-5-25  
  
#include <ansi.h>  
  
inherit F_CLEAN_UP;  
  
int main(object me, string arg)  
{         
        object ob;  
        string *sum_list;  
        string path;  
        string *dirs;  
        string file_name;  
        string ob_id, temp;  
        string msg;  
        int i;  

        if (! SECURITY_D->valid_grant(me, "(admin)")) 
                return 0; 
          
        if (! arg)  
                ob = me;  
        else  
        {  
                ob = present(arg, environment(me));  
                if (! ob) ob = find_player(arg);  
                if (! ob) ob = find_living(arg);  
                if (! ob) return notify_fail("��Ҫ�ָ�˭���ٻ��б�\n");  
        }  
          
        path=ITEM_DIR+query("id", ob)[0..0]+"/";
        dirs=get_dir(path+query("id", ob)+"-*.c");
          
        // ɾ��ԭ���ٻ��б�  
        //delete("can_summon", ob);
  
        // �ؽ��ٻ��б�          
        for (i = 0; i < sizeof(dirs); i++)  
        {  
                file_name = path + dirs[i];  
                sscanf(file_name, "%s-%s.c", temp, ob_id);  
                set("can_summon/"+ob_id, file_name[0..<3], ob);
        }  
 
        // ��ָ 
        file_name=ITEM_DIR+"ring/"+query("id", ob)+".c";
        if (file_size(file_name) > 0) 
                 set("can_summon/wedding ring", file_name[0..<3], ob);
        
        // ���ΰ�
        file_name=ITEM_DIR+"cruise/"+query("id", ob)+".c";
        if (file_size(file_name) > 0) 
                 set("can_summon/qiankun", file_name[0..<3], ob);

        file_name=DATA_DIR+"warcraft/"+query("id", ob)+".c";
        if (file_size(file_name) > 0) 
                 set("can_whistle/"+query("id", get_object(file_name)), file_name[0..<3], ob);
                         
        msg = HIC"" + ob->name() + HIC"���ٻ��б������ϡ�\n"NOR;  
        write(msg);  
        if (ob != me)
                tell_object(ob, HIC"����ٻ��б��Ѿ����¡�\n"NOR);
                
        return 1;  
}  
