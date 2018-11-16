// Room: chaopath2.c ������С·
//Date: Oct. 2 1997 by Venus
inherit ROOM;

void create()
{
      set("short","������С·");
        set("long", @LONG
�����ǳ�����С·��ɽ�ƶ��ͣ�����������ȣ�һ��С�Ķ����
����ȥ��������һ��С·������û����С·˳��ɽ��һ·���Ӷ�����
��ɽ��ɽ��˴��ǻ�ɽǰ������֮�������׼������˼���������ɽ
�������ǲ��ô��У�Ҳ�������ˡ�����ļ���С�ݣ����ǻ�ɽǰ����
������
LONG );
      set("outdoors", "huashan");
      set("exits",([ /* sizeof() == 1 */
          "southwest": __DIR__"chaopath1",
          "eastup"   : __DIR__"chaoyang",
          "westup"   : __DIR__"ziqitai",
          "northup"    : __DIR__"hsxiaowu",
      ]));
      set("objects", ([
          __DIR__"npc/shi-daizi" : 1,
      ]));
      setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xunshan", me))set_temp("xunshan/chaoyang", 1, me);
        return;
}

int valid_leave(object me, string dir)
{
        if (dir != "northup"  ||
            ! objectp(present("shi daizi", environment(me))) ||
            (query("family/master_id", me) == "gaolaozhe") || 
            (query("family/master_id", me) == "ailaozhe") )
                return ::valid_leave(me, dir);

        if( query("family/family_name", me) != "��ɽ��" )
        {
                message_vision("ʩ����������ס$N��������Ǹ����������λ"
                               "��������֮������λ" + RANK_D->query_respect(me) +
                               "��ֹ����\n", me);
                return notify_fail("����ʩ���Ӳ��������ȥ��\n");
        }

        if( query("combat_exp", me)<100000 )
        {
                message_vision("ʩ����������ס$N������ֹ������������λ"
                               "��������֮��������Ȼ�Ǳ��ɵ��ӣ�����ѧ"
                               "�ղ��������ܰݼ���\n", me);
                return notify_fail("����ʩ���Ӳ��������ȥ��\n");
        }

        return ::valid_leave(me, dir);
}