inherit BULLETIN_BOARD;

void create()
{
        set_name("����ʯ��", ({ "stone" }) );
        set("location", "/d/penglai/haitan");
        set("board_id", "penglai_shibi");
        set("long", "���ǿ�ʯ�ڣ������������������(post)��\n" );
        setup();
        set("capacity", 300);
        replace_program(BULLETIN_BOARD);
}

