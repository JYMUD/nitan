
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("hengshan")+"/xian");
        set("start_room","/d/hengshan/square");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if (query("gender", ob) != "Ů��" || query("class", ob)!= "bonze")
        {
                return "����ֻ��Ů����ܽ������ŵ���һְ��";
        }
        return ::zm_apply();
}

