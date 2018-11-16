//                ��׼��������ʾ��                                   |
// ���þ���Ѱ��ϵ������֮׼��������Ϸ����
// by naihe  2002-10-24

// 14:23 03-10-25 ������һ��ˮ����ͼƬ
// PS�� �����Լ����� HOHOHO



#include <ansi.h>
inherit ROOM;

#define        QXD_FILE    __DIR__"npc_obj/_qxd_"


void sing_song(int i);

string *context=({
    " ",   // ���ĪҪɾ��
    "�װ�����ʿ��  ��Ȼ������������ط�",
    "����������������֪���Ĺ���",
    "���Ҹ�����  �ǹ��ϵĴ�˵�ɡ���",
    "�ഫ��Զ�ŵ�ʱ��",
    "����������ĸ����ϵĹ���",
    "�����Ƿ硢�ꡢ�ס���֮����",
    "���Ƕ������Լ��ı���",
    "����άϵ����  �����ڸ��Ե�����",
    "ʱ���Ǩ  ���ҳ���",
    "����֮�䱬����ս��",
    "����ͣ����ԭ���ļ�԰",
    "����֮���ս���ɱ������",
    "������ȴ��δ�ܵõ�����",
    "�ĸ������ɴ˶�����",
    "������Ҳ��ɢ���ء�",
    "�װ�����ʿ��",
    "���Ƿ�Ը��Ѱ����",
    "����ʶ�ǹ��Ϲ��ȵ����ع�â��",
    "����  ̤����ѡ��Ĳ���",
    "�����㽫�����δ֪֮�ˡ�",
});

string singing="no";
string look_shuijing();

string pler1,pler2,pler3,pler4,id1,id2,id3,id4,
pler1="����",pler2="����",pler3="����",pler4="����",
id1="aa",id2="bb",id3="cc",id4="dd";

int *pler_data1=({
    20+random(10),        // ����
    20+random(10),        // ����
    20+random(10),        // ����
    25+random(5),         // ��
    1000+random(1000),    // ���
});

int *pler_data2=({
    25+random(5),
    20+random(10),
    20+random(10),
    20+random(10),
    1000+random(1000),
});

int *pler_data3=({
    20+random(10),
    25+random(5),
    20+random(10),
    20+random(10),
    1000+random(1000),
});

int *pler_data4=({
    20+random(10),
    20+random(10),
    25+random(5),
    20+random(10),
    1000+random(1000),
});

void hjset_long()
{
    string cl = ({ HIC, HIG, HIM, HIW })[ random(4) ];

    set("long", cl + "
                        __   +
                     */____\\
                      \\    /  .
                    +  \\  /  
                      . \\/  *


  "NOR"����һƬ��ڣ���ֻ������ǰ����������һ��"+cl+"ˮ��"NOR"(shuijing)��\n");
}

void create()
{
    set("short",BLU"���֮��"NOR);
    hjset_long();

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_magic", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("item_desc",([
        "shuijing": (: look_shuijing :),
    ]));

    setup();
}

void init()
{
    if( !query_temp("hj2003-valid_enter", this_player()) )
    {
        call_out("get_out_here",1, this_player());
        return;
    }

    hjset_long();
    add_action("do_xuanze","xuanze");
    add_action("do_nocmds", ({ "scheme", "drop", "put", "set", "unset", }) );
}

int do_nocmds()
{
    write("�����ֹʹ�����ָ�\n");
    return 1;
}

void get_out_here(object me)
{
    if( !me || !environment(me) || environment(me) != this_object() ) return;

    message_vision( HIR"һ��������Ϯ����$N"HIR"��δ����Ӧ���ѷ����Լ������ˡ�\n"NOR, me);
    me->move( __DIR__"room_door_hj" );
    message_vision("һ��Ī�����𵴺������ţ�$N��֪��ô�ľͺ��س����������ˡ�\n",me);
}

void reset()
{
    ::reset(); 
    set("no_clean_up", 1); 
}

string look_shuijing()
{
    write("ˮ��ɢ�������ĵĹ�â��");
    if( singing == "yes" || !query_temp("hj2003-valid_enter", this_player()) )
        return "\n";

    remove_call_out("sing_song");
    call_out("sing_song",1);
    return "\n";
}

void sing_song(int i)
{
    object me=this_player();

    singing="yes";
    if (i<sizeof(context))
    {
        if(i==0) message_vision(CYN"$N����������һ�����������ȴ��֪�����Ժδ���\n"NOR,me);
        else message("vision",MAG"      "+context[ i ] + "\n"NOR,this_object());
        i ++;
        remove_call_out("sing_song");
        call_out("sing_song",3,i);
    }
    else
    {
        singing="no";
        message("vision",CYN"�������������ǽ���Զȥ�㣬������������Ϣ�ˡ�\n"NOR,this_object());
        message("vision","�㽫Ҫѡ��(xuanze)��һ�����ȣ� ���磺��֮���� <xuanze feng>\n"NOR,this_object());
    }
}

// �� = ��dex   �� = ����int   �� = ����str   �� = ����con
// ���� = ��òper   ���� = ��shen(shen_type=-1Ϊ����)   ��� = ����age   ���� = ���balance

int do_xuanze(string arg)
{
    object *all_mine,old_obj,qx_deng,me=this_player();
    int i,temp;
    mapping xuanze_arg;

    // �������߽����Ĳſ��ԡ�
    if( !query_temp("hj2003-valid_enter", me) )
        return 0;
    if( !arg )
        arg = "@_@";
    xuanze_arg = ([
        "��" : "feng",
        "��" : "yu",
        "��" : "lei",
        "��" : "dian",
    ]);
    // �����������Ľ���ѡ��
    if( xuanze_arg[ arg ] )
        arg = xuanze_arg[ arg ];
    if( arg!="feng" && arg!="yu" && arg!="lei" && arg!="dian" )
        return notify_fail("�㽫Ҫѡ��(xuanze)��һ�����ȣ� ���磺��֮���� <xuanze feng>\n");
    delete_temp("hj2003-valid_enter", me);
    all_mine = deep_inventory(me); // ԭ����  all�����ڸ�Ϊ deep ��BUG ������
    if( all_mine && sizeof( all_mine ) > 0 )
    {
        for(i=0;i<sizeof(all_mine);i++)
        {
            if( query("hj_game", all_mine[i]) )
            { destruct(all_mine[i]);temp++; }
        }
    }

    if(temp)
        write(HIR"������֮ǰ��"+chinese_number(temp)+"���þ������Ʒ��������ˡ�\n"NOR);
    set_temp("huanjing", arg, me);
    qx_deng=new( QXD_FILE );

// ########  ����Ϊ ���ǵ� ������Ϸ��������Ѷ�� ########


    set("my_master", me, qx_deng);

    set("hj_quest_info1/name", pler1, qx_deng);
    set("hj_quest_info1/int", pler_data1[0], qx_deng);
    set("hj_quest_info1/str", pler_data1[1], qx_deng);
    set("hj_quest_info1/con", pler_data1[2], qx_deng);
    set("hj_quest_info1/dex", pler_data1[3], qx_deng);
    set("hj_quest_info1/balance", pler_data1[4], qx_deng);

    set("hj_quest_info2/name", pler2, qx_deng);
    set("hj_quest_info2/int", pler_data2[0], qx_deng);
    set("hj_quest_info2/str", pler_data2[1], qx_deng);
    set("hj_quest_info2/con", pler_data2[2], qx_deng);
    set("hj_quest_info2/dex", pler_data2[3], qx_deng);
    set("hj_quest_info2/balance", pler_data2[4], qx_deng);

    set("hj_quest_info3/name", pler3, qx_deng);
    set("hj_quest_info3/int", pler_data3[0], qx_deng);
    set("hj_quest_info3/str", pler_data3[1], qx_deng);
    set("hj_quest_info3/con", pler_data3[2], qx_deng);
    set("hj_quest_info3/dex", pler_data3[3], qx_deng);
    set("hj_quest_info3/balance", pler_data3[4], qx_deng);

    set("hj_quest_info4/name", pler4, qx_deng);
    set("hj_quest_info4/int", pler_data4[0], qx_deng);
    set("hj_quest_info4/str", pler_data4[1], qx_deng);
    set("hj_quest_info4/con", pler_data4[2], qx_deng);
    set("hj_quest_info4/dex", pler_data4[3], qx_deng);
    set("hj_quest_info4/balance", pler_data4[4], qx_deng);

    if(arg == "feng")
        set("find_name", "��֮����", qx_deng);
    if(arg == "yu")
        set("find_name", "��֮����", qx_deng);
    if(arg == "lei")
        set("find_name", "��֮����", qx_deng);
    if(arg == "dian")
        set("find_name", "��֮����", qx_deng);
    set_temp("hj_game_find", arg, me);

// ############## ��Ѷ���� ###############

    if( query("id", me) != id1 && 
        query("id", me) != id2 && 
        query("id", me) != id3 && 
        query("id", me) != id4 )
    {
        pler1=pler2;
        pler2=pler3;
        pler3=pler4;
        pler4=query("name", me);

        id1=id2;
        id2=id3;
        id3=id4;
        id4=query("id", me);

        pler_data1=pler_data2;
        pler_data2=pler_data3;
        pler_data3=pler_data4;
        pler_data4=({
            query("int", me),
            query("str", me),
            query("con", me),
            query("dex", me),
            to_int(query("balance", me)),
        });
    }

    write("��õ�һյ���ǵơ�\n");
    qx_deng->move(me);
    return 1;
}