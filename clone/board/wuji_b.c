
inherit BULLETIN_BOARD;

void create()
{
        set_name("�����ʼ�", ({ "board" }) );
        set("location", "/u/wuji/workroom");
        set("board_id", "wuji_b");
        set("long", "����һ��ר��wujiʹ�õĹ����ʼǡ�\n" );
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}

