#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("xuedao")+"/laozu");
        set("start_room","/d/xuedao/shandong3");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        
        if( query("class", ob) != "bonze" )
                return "ѩ���ű����Ǻ��в��ܵ�����ϯ����ӡ�\n";
                
        return ::zm_apply();
}
