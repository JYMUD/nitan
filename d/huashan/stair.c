//Cracked by Kafei
// xiaolu1.c ��ɽ����ʯ��
// qfy 10/8/1997

inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long",
"ʯ����Ȼ�������ӣ���ͷ�ɼ��Ƚ����ŵ�ʯ�š�����ʯ���Ϲ��ŵ�ȼ\n"
"�Ļ�ѣ���ͨ���յ�ʮ��������\n"
);

        set("exits", ([ /* sizeof() == 1 */
                "down" : __DIR__"door",
        ]));


        set("cost", 0);
        setup();
}


