
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("shaolin")+"/xuan-ci");
        set("start_room","/d/shaolin/dxbdian");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if (query("gender", ob) != "����" || query("class", ob) != "bonze")
        {
                return "�������ŵ��Ӿ�Ϊ���Һ��У�";
        }       
        return ::zm_apply();
}
