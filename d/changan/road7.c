//  Room:  /d/changan/road7.c

inherit  ROOM;

void  create  ()
{
        set("short",  "�ٵ�");
        set("long",  @LONG
һ����ʯ�̾͵Ĺٵ���������ͨ�����ݣ������򵽴ﳤ������·��
����һƬï�ܵ����֡�������һ�����棬�������Ѿ���Щ����ˡ�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"      :  __DIR__"apanggong",
                "northwest" :  __DIR__"road8",
                "east"      :  __DIR__"xi-chengmen",
        ]));
        set("outdoors", "changan");
        set("no_clean_up", 0);
        set("coor/x", -10780);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}