inherit ROOM;

void create()
{
        set("short", "��϶�");
        set("long", @LONG
��������ɽ�϶���ֻ�����ڷǳ����������ɿ��������
�ƣ���˵��������Ϸ�ֳ�ĵط���

LONG);
        set("exits", ([
                "out" : __DIR__"tianroad6",
        ]));
        set("outdoors", "xingxiu");
        // �ɴ��Ա�־
        set("can_hunting", 1);
        set("quarry", ([
             "can"       :  20,
             "tiancan"   :  50,
             "zhang"     :  40,
        ]));

        setup();
}

