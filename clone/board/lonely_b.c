// /clone/board/lonely_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("�����ʼ�", ({ "board" }) );
        set("location", "/u/lonely/workroom");
        set("board_id", "lonely_b");
        set("long", "����һ��ר��Lonelyʹ�õĹ����ʼǡ�\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

