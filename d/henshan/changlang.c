inherit ROOM;

void create()
{
          set("short","����");
        set("long", @LONG
����ͨ���ͷ��ĳ��ȣ���Զ�����ǿͷ��ͳ����ˡ�
LONG );
          set("exits",([
                      "west"      :__DIR__"zhurongdian",
                  "northeast" :__DIR__"henshan_chufang",
                  "north"     :__DIR__"kefang",
          ]));

          set("objects", ([
                  __DIR__"npc/xiangke" : 2,
          ]));
	set("coor/x", -6920);
	set("coor/y", -5490);
	set("coor/z", 40);
	setup();
          replace_program(ROOM);
}