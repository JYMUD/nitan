inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һƬï�ܵ����֣����ҵ���������б��ɽ���ϡ�ÿ��
�����������ı���ϸ���ߴ�ʮ���ɡ�����֦��Ҷ�ܣ��������
ȫ��ס����������Ե���Щ�谵����ľ֮�䳤�źܶ��ľ�Ӳ�
ʹ���ߺܼ��ѣ���˵�˲ξ���������Щ�Ӳ�֮�С�
LONG);
        set("exits", ([
                "westdown" : __DIR__"milin1",
                "southup"  : __DIR__"milin3",
        ]));
        set("objects", ([
                "/clone/quarry/laohu2" : 1,
        ]));
        // �ɴ��Ա�־
        set("can_hunting", 1);
        set("quarry", ([
             "hu"        :  10,
             "hu2"       :  6,
             "hu2"       :  6,  
             "lang"      :  70,
             "lang2"     :  80,
             "lang3"     :  25,
             "xiong"     :  8,
             "xiong2"    :  8,
         "diao"      :  10,
             "jizi"      :  50,
             "laohu"     :  20,
             "laohu2"    :  10,
             "lu"        :  20,
             "lu2"       :  15,
             "pao"       :  40,
                 "bao"       :  3,
         "song"      :  90,
        ]));

        set("outdoors", "changbai");
        setup();
}
