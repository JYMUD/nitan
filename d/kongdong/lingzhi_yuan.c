//1997-3-10 by qyz
#include <room.h>

inherit DOOR_ROOM;



void create()
{
        set("short","��֥԰");
        set("long",@LONG
���������֥԰��԰ǽ�������һ�������ţ��ųʰ˽��Σ����а���ͼ����
�����ɺף�÷¹ͼ��ǽ�������á�˫��Ϸ�顱���ܣ����ռ��侫տ���ź�̡�
���Ժ����棬˫����Ǭ����һ����԰���滨��ݣ����෱�࣬����Ũ������ľ
��������ʦɢ��������Ϣ֮����ƽʱ�������˵���������
LONG);
        set("exits",
        ([
          "south" : __DIR__"xuanyuan_gong",
          "north" : __DIR__"lianhua_tai",
         
                ]));
        create_door("north",([
                        "name" : "Сľ��",
                        "lock" : "lock001",
                        "status": 3,
                        "id"  : ({ "north","Сľ��","door"}),
                        "other_side_dir": "south",
                                ]),
                        "south");
        set("outdoors","kongdong");
        set("objects",([
                __DIR__"npc/shouyuan" : 1,
                ]) );
        setup();
}
