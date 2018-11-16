// Room: /binghuo/lingsheroom.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "ɽ��С��");
        set("long", @LONG
�����ǽ������ڵ��ϵľ�����С���ǵ�����ɽ��Ұ����������
��͡����紵�죬������ˬ���ı�С�񴰣����մ��������Ӱ�����
�졢���ơ��̺��ͻ�ɳ�����˰�����ʰ�ü�Ϊ���š�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"lingshetop",
        ]));
        set("objects", ([
                CLASS_D("mingjiao")+"/daiqisi": 1,
        ]));
        setup();
}
void init()
{
        object weapon, ob, me = this_player();
        mapping weapon_prop;
        string *apply, type;

        if(objectp(ob = present("dai yisi", environment(me))) && living(ob))
        {
                weapon = new(WEAPON_DIR"treasure/jinhua");
                if ( weapon->violate_unique() )
                {
                        destruct( weapon );
                }
                else
                {
                        if(!present("duoming jinhua", ob))
                        {
                                weapon->move(ob);
                                weapon_prop=query("weapon_prop", weapon);
                                apply = keys(weapon_prop);
                                for(int i = 0; i<sizeof(apply); i++)
                                        addn_temp("apply/"+apply[i], weapon_prop[apply[i]], ob);
                                set_temp("weapon", weapon, ob);
                                ob->reset_action();
                                set("equipped", "wielded", weapon);
                        }
                }
        }
}
