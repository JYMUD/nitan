
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("xueshan")+"/jiumozhi");
        set("start_room","/d/xueshan/dadian");
        ::create();
}

string zm_apply()
{

        object ob = this_player();
        if (query("class", ob) != "bonze")
        {
                return "�����ѩɽɮ�ڣ����ܳ������ŵ���һְ��";
        }
        return ::zm_apply();
}
