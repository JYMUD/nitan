
#include <ansi.h>
inherit F_FIRST;

void create()
{
        set("master_dir",CLASS_D("gaibang")+"/hong");
        set("start_room", "/d/gaibang/gbxiaowu");
        ::create();
}

string zm_apply()
{
        object ob = this_player();
        if ( !query("family/beggarlvl", ob) )
                return "��ؤ���д����ӣ�����ʤ�����ŵ���һְ��";
        return ::zm_apply();
}

