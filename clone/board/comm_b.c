
inherit BULLETIN_BOARD;
void create()
{
        set_name("��ҽ�����", ({ "board" }) );
        set("location", "/d/city/tree");
        set("board_id", "comm_b");
        set("long", "����һ�鹩��ҽ����ĵõ����԰塣\n");
        setup();

        set("capacity", 218);
        replace_program(BULLETIN_BOARD);
}

