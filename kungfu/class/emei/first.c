

#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("emei")+"/miejue");
        set("start_room","/d/emei/hcaguangchang");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if (query("gender",ob) != "Ů��" || query("class",ob) != "bonze")
        {
                return "����������Ů��������ţ�\n";
        }
        return ::zm_apply();
}

