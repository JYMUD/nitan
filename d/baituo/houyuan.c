inherit ROOM;

void create()
{
        set("short","��Ժ");
        set("long", @LONG
������һ��Ƨ���ĺ�Ժ��ס����ׯ��ŷ���˵����������衣����
�������Ѹߣ����Ѿ����ɻ��ˣ������ﾲ����
LONG );
          set("outdoors", "baituo");
          set("exits", ([
                      "southeast" : __DIR__"zhuyuan",
             ]));

          set("objects", ([
                    __DIR__"npc/zhangma" : 1,
            ]));

         set("coor/x", -49980);
        set("coor/y", 20080);
        set("coor/z", 30);
        setup();
         replace_program(ROOM);
}