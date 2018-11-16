// Room: /guiyun/damen.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
��ǰ��һ��ׯԺ����¥�����ߴ���ש���ߣ���ɫ�׵�����д�š�
����ׯ����������֡����ҽ�Ϊ�¾ɣ��߽Ǵ�����Ƥ�Ѱ��䣬¶������
ɫ��ľ�ʡ������������Ѳ��¶�ʮ�������ˡ�
LONG );
        set("outdoors", "guiyun");
        set("exits", ([
                "enter" : __DIR__"dayuan",
                "south" : __DIR__"shiqiao",
        ]));
        set("objects", ([
                __DIR__"npc/jiading" : 2,
        ]));
        set("coor/x", 280);
        set("coor/y", -830);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "�һ���") &&
                !query_temp("marks/guiyun", me) && dir == "enter" && 
                objectp(present("jia ding", environment(me))))
                return notify_fail("�Ҷ����˸�Ҿ��˵����������ׯ����������ׯ��������ͣ�������ذɡ�\n");

        return ::valid_leave(me, dir);
}