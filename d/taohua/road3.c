inherit ROOM;
 
void create()
{
        set("short", "С·");
        set("long", @LONG
����һ��ͨ����ɽ��С����С·���Գ������Ӳݡ��������Ǻ�������
��·��������·����Ҳϡϡ����ð���˲�ѿ��������һ��Сɽ����
LONG );
        set("exits", ([
                "east"   : __DIR__"road4",
                "south"  : __DIR__"road2",
        ]));
        set("objects", ([
                "/clone/beast/dushe": 4,
        ]) );
        
        set("outdoors", "taohua");
       
        set("coor/x", 8980);
        set("coor/y", -2930);
        set("coor/z", 0);
        setup();
}