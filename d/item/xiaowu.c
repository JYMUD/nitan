// xiaoyuan.c

inherit ROOM;

#define GANJIANG        "/adm/npc/ganjiang"
#define MOYE            "/adm/npc/moye"

void create()
{
        object ob;

        set("short", "������");
        set("long", @LONG
��һ�߽�������ӣ��͸о�����һ����������������ݽ���һ��¯�ӣ�
����ȼ�����ܻ�⣬�ƺ������Ľ���������ǰ�ζ����ݽǶѷ���һ�ѶѺ�
�����Ķ�������֪����ʲô��
LONG );

        GANJIANG->come_here();
        MOYE->come_here();

        set("no_fight", 1);
        set("no_sleep_room", 1);

        set("exits", ([
                "out" : __DIR__"road5",
        ]));
        set("coor/x", 900);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
}

void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/ganjiang");
}


