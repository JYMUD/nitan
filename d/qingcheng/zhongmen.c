// Room: /qingcheng/zhongmen.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
�������ɷ��ͨ����Ժ�����ţ��ź����磬����ͭ������ʮ������
����Ʈ�����͹��������ͳ�һ�ɳ�������ζ��������ʿ���˾͸û�ͷ
�ˡ�
LONG );
        set("exits", ([
                "south" : __DIR__"qiandian",
                "north" : __DIR__"zoulang1",
        ]));
        set("objects", ([
                __DIR__"npc/yu" : 1,
        ]));
        set("coor/x", -8080);
        set("coor/y", -860);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
/*        mapping myfam;
        myfam=query("family", me);
        if ((!myfam || (myfam["family_name"] != "�����")) && (dir == "north"))
                return notify_fail("����ǵ��ӣ�����ֹ���ɡ�\n");
        else return 1;
*/
if (dir != "south" )
        {
                if( query("family/family_name", me) != "�����" )
                {                        
                       if(present("yu renhao", environment(me)) && living(present("yu renhao", environment(me))))
                        {
                                return notify_fail(
"���˺��ȵ��������Ǳ����صأ���λ" + RANK_D->query_respect(me) + "��ֹ����\n");
                        }
                        else
                                return ::valid_leave(me, dir);                        
                }
                else
                        return ::valid_leave(me, dir);
        }
        else
                return ::valid_leave(me, dir);        
}