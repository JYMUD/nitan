inherit DEMONROOM;

void create()
{
        set("short", "�㵺");
        set("long",@LONG
���а�����9��18�±�����������ʿ��Ϊ���ǵ�Ӣ�۱���ɣ�
LONG);

        set("exits", ([
                "north"   : __DIR__"changqi2",
                "east"   : __DIR__"guangdao2",
                "west"  : __DIR__"guangdao3",
            "south"  : __DIR__"guangdao4",

        ]));

                set("n_time", 30); 
                set("n_npc", 5); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}
