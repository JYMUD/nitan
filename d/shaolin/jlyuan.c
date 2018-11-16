// Room: /d/shaolin/jlyuan.c
// Date: YZC 96/01/19

#include <ansi.h>
#include <login.h>

inherit ROOM;

void create()
{
        set("short", "����Ժ");
        set("long", @LONG
��������Ż����գ��ܲ�͸�硣�������ڰ��磬Ҳ�����ҹһ�㣬
ÿ��������ǽ�ϣ���ȼ�ż�֦ţ�;����·�����һ����������ˮţ
Ƥ�ޡ�������弰���������̾ߡ�����վ�����ֱֳ��е�ִ��ɮ����
����������������������㣬���㲻���������������
LONG );
        set("no_fight", "1");
        set("exits", ([
                "southdown" : __DIR__"guangchang3",
        ]));
        set("valid_startroom",1);
        set("objects",([
                CLASS_D("shaolin") + "/xuan-tong" : 1,
                __DIR__"npc/seng-bing2" : 3,
                __DIR__"npc/xiao-tong" : 1
        ]));
        setup();
}

void init()
{       
        mapping fam;
        object ob;

        if (interactive(ob = this_player()))
        {
                if( mapp(fam=query("family", ob) )
                &&  fam["family_name"] == "������" 
                &&  fam["generation"] == 37
                 && query("guilty", ob) == 0 )
                        return;
                else 
                {
                        message_vision(HIY "$N" HIY "һ������Ժ��...ֻ������"
                                       "��ȣ���ͬը�װ��ڴ������졣"
                                       "$N" HIY "��������������Ҳվ����ס��"
                                       "��һ����ͨһ������������\n\n" NOR,
                                       ob);

                        set("startroom", "/d/shaolin/jlyuan", ob);

                        call_out("processing", 3, ob);
                }
        }
}

void processing(object ob)
{
        mapping fam;

        if (! objectp(ob))
                return;
        write(HIW "\n�㶨�˶���̧ͷϸ����ֻ����ʮ���ֵ�ɮ�˽�������Χ������\n"
                "һƬѩ���ĵ���Ƶ����۶�����������ǰ���ĸ�̨�Ϸ���һ��\n"
                "̫ʦ�Σ����и�����λ�����ü����ɮ����ɫ���࣬Ŀ�侫�⣬\n"
                "�ݺݵص����㡣\n\n\n" NOR);

        if( !(fam=query("family", ob)) || fam["family_name"] != "������" )
                message_vision(HIY "��ʹһ����ȣ����ȴ󵨿�ͽ���ô�����"
                               "�������֣����ڲ��죬�õ����"
                               "���������£������������С��˺�����Ϊ��ִ��ɮ"
                               "�����ڣ�\n\n" NOR, ob);

        if( (fam=query("family", ob)) && fam["family_name"] == "������" )
        {
                if( query("guilty", ob) == 1 )
                        message_vision(HIY "��ʹһ����ȣ�$N" HIY "�������½���"
                                       "���գ�ȴ����ɱ��Խ����������Ϊ��"
                                       "�۷���䣬�ܻ�����ǧ����������õ�"
                                       "�����ִ��ɮ�����ڣ�\n\n" NOR, ob);

                if( query("guilty", ob) == 3 )
                        message_vision(HIY "��ʹһ����ȣ�$N" HIY "�����»�����"
                                       "�����������������˵������룬"
                                       "���ô��˵أ����ڲ��죬�õ����ִ��"
                                       "ɮ�����ڣ�\n\n" NOR, ob); 

                if( query("guilty", ob) == 2 )
                {
                        message_vision(HIY "��ʹ����$N" HIY "���˰��ã�˵"
                                       "����$N" HIY "����Ͷ����ƣ�������"
                                       "�������ñ��ã����������׽�ɱ������"
                                       "�˺�����������ɮ�ҵ���� "
                                       "��ȥ�գ��´ζ������ģ�\n\n" NOR, ob);

                        set("guilty", 0, ob);
                        set("startroom", START_ROOM, ob);
                        ob->move("/d/shaolin/guangchang3");
                        return;
                }
        
        }

        call_out("responsing", 3, ob, 3);
}

void responsing(object ob, int i)
{
        int j;

        if (! objectp(ob))
                return;
        message_vision(HIR "ɮ������Ӧ���������ڣ�\n" NOR, ob);

        i--;
        j = random(3);

        if (i == 0) 
        {       
                call_out("beating", 3, ob);
                return;
        }

        call_out("responsing", j, ob, i);
}

void beating(object ob)
{
        if (! objectp(ob))
                return;

        message_vision(HIY "\n\n��ʹ�ȵ����������٣���$N" HIY
                       "����ɮ���Ѻ���£���ϴ�Ļڸģ�"
                       "�����ͷţ���ͼԽ�������һ�ȣ�\n\n" NOR, ob);

        message_vision(HIR "ɮ����һӿ���ϣ��Ұ����£�$N" HIR "ʹ�û���"
                       "��ȥ......\n" NOR, ob);

        if( query("guilty", ob)>0)set("guilty", 0, ob);
        
        ob->move("/d/shaolin/jianyu");
        ob->unconcious();

}

int valid_leave(object me, string dir)
{
        mapping fam;

        if (userp(me) && dir == "southdown")
        {
                if( mapp(fam=query("family", me) )
                &&  fam["family_name"] == "������" 
                &&  fam["generation"] == 37  ) 
                        return ::valid_leave(me, dir);
                else
                        return notify_fail("��ʹ˵��: �󵨣��㻹�����ܣ�ִ��ɮ�����ڣ�\n");
        }

        return ::valid_leave(me, dir);
}
