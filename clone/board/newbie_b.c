// /clone/board/bonze_b.c

#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
    set_name(HIC "�Ŵ����԰�" NOR, ({ "board" }) );
    set("location", "/d/newbie/shijiezhishu");
        set("board_id", "newbie_b");
        set("long", "�������ִ�����԰棬�������� post <����> ���ԡ�\n" );
        setup();
        set("capacity", 500);
        replace_program(BULLETIN_BOARD);
}

