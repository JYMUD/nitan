inherit ROOM;
 
void create()
{
        set("short", "ʥ����");
        set("long", @LONG
�����Ǻ�ľ�µ�ʥ�����ڵء�ʥ���á�������������ޣ�ɷ��Ư
��������һλ����Ů�ӣ�����С�䣬���޲��ɷ��
LONG );
        set("exits", ([
            "west"   : __DIR__"chlang3",
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/ren" : 1,
            __DIR__"npc/shinu":2,
        ]));       
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}