inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "������");
        set("long",@LONG
�����������ų������ϣ���˵���⵺�ϲ�����ס�����ߣ� 
����ס�ŷ���֮�ˣ�������Щ�˴Ӻζ����㲻�ö�֪��ֻ֪
�����ǳ����ס�ڳ������С�Ҳ�д�˵������̤����������
�˱���Ի����������֪������ΪʲôҲ�г���������˵��
�ﳤ����ľ���ԭ�����������ﶨ�ӣ��������г��ַ�����
ȫ����˱���������
LONG);

        set("exits", ([
                "north"         : __DIR__"wolongdao",        
                "south"         : __DIR__"feilonggu1",
        ]));
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ��������
        set("no_fight", 1);

        setup();
}

void init ()
{
        if (! this_player()->query_temp("apply/xianshu-lingwei"))
        {
                if (! this_player()->query("penglai/go_quest/ok"))
                {
                        this_player()->start_busy(3);
                        tell_object(this_player(), NOR + WHT "�㵽�˴˴�������������������һʱ�����Ա����\n" NOR);
                }
                else
                {
                        if (random(2))
                        {
                                this_player()->start_busy(1);
                                tell_object(this_player(), NOR + WHT "�㵽�˴˴�������������������һʱ�����Ա����\n" NOR);                
                        }
                }
        }
}