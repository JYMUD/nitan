// /d/wizard/guest_room.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIM "��Ϸ������" NOR);
        set("long", @LONG
��������ʦ����ҽ����ĵط���Ϊ������ʦͳһ����������ֻ��
����(post)������ҶԱ���Ϸ�ļ����Լ�����������߶���Ϸ��ĳЩ
��������ʣ��Թ���ʦ�ο������ܷ����Ǹ�������������ӻ��⣬��
�����־������������Ȼ�����ߣ���һ��ɾ�����������������뵽��
��ʦ����ҡ�����������������ʦ����ҽ�����Ҳ����ͳһ��������
��Ч�ʣ���ҿ����ڴ˷����κη��ϸ���������£���ʦҲ��������
��֮�������ڹ����������Ⱥͼƻ��Թ���Ҳο�����ӭ��������  
                                  ==��̶��ȫ����ʦ==
LONG );

        set("exits", ([
                "north": __DIR__"guest_room",               
        ]));

        set("no_fight", 1);

        set("coor/x", 10000);
        set("coor/y", 9990);
        set("coor/z", 9990);
        setup();
        "/clone/board/develop_b"->foo();
}