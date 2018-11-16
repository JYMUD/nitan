#include <maze.h>
#include <ansi.h>

inherit ITEM;

#define QUEST_OBJ_D(x)          ("/quest/questsn/quest/questsn" + x + "find")

int is_opened = 0;

string *dan_list = ({
    "/clone/gift/xiandan",
    "/clone/gift/shenliwan",
    "/clone/gift/unknowdan",
    "/clone/gift/xisuidan",
    "/d/item/obj/butian",
    "/d/item/obj/tiancs",
    "/clone/gift/fuyuandan.c",
});

string *jinkuai_list = ({
    "/clone/gift/jinkuai",
    "/clone/gift/jintiao",
    "/clone/gift/xiaoyuanbao",
    "/clone/gift/dayuanbao",
    "/clone/gift/jinding",
    "/clone/gift/fuyuandan.c",
});

string *obj_list = ({
    "/d/yanziwu/obj/dodgebook",
    "/clone/book/liuyang_book2",
    "/clone/book/liuyang_book1",
    "/d/xiaoyao/obj/putuan",
    "/d/item/obj/xuantie",
    "/clone/book/jiuyin1",
    "/clone/book/jiuyin2",
    "/d/jinshe/obj/jinshe-jian",
    "/clone/book/book-silk",
    "/clone/book/qijianpu",
    "/d/wudang/obj/honglian",
    "/d/shenlong/obj/hua",
    "/d/taohua/obj/xiang",
    "/clone/book/dujing_1",
    "/d/huanghe/npc/xxqingxin-san",
    "/d/xueshan/obj/lubo",
    "/d/xueshan/obj/rtlian",
    "/d/xueshan/obj/klguan",
    "/clone/book/qiankun_book",
    "/d/mingjiao/obj/yixin",
    "/d/shenlong/obj/hua2",
    "/d/shenlong/obj/usedgao",
    "/d/quanzhen/npc/obj/daodejing-ii",
    "/d/quanzhen/npc/obj/daodejing-i",
    "/d/meizhuang/obj/zhuguo",
    "/d/shenlong/obj/baihua",
    "/d/changan/npc/obj/book",
    "/d/changan/npc/obj/book_unarmed",
    "/d/changan/npc/obj/book_blade",
    "/d/baituo/obj/shedangao",
    "/clone/book/bufa",
    "/clone/book/jinshe1",
    "/clone/book/jinshe2",
    "/clone/book/jinshe3",
    "/clone/book/staff_book",
    "/clone/book/shoufa",
    "/clone/book/zhanyi",
    "/clone/book/bagua0",
    "/clone/book/bagua1",
});

void create()
{
    set_name(HIY "����" NOR, ({ "bao xiang", "xiang" }) );
    set_weight(150000);
    set_max_encumbrance(800000);
    set("no_get", 1);
    if( clonep() )
    {
        set_default_object(__FILE__);
    }
    else 
    {
        set("unit", "��");
        set("long", HIY "����һֻ��ɫ�ı��䣬װ�ε���ⱦ�����������Դ򿪣�open������\n" NOR);
        set("value", 1);
    }
}

int is_container() { return is_opened; }

void init()
{
    add_action("do_open", "open");
}

int do_open(string arg)
{
    object me, ob;
    int box_type;
    string mazename;
    object bonus;
    int temp_lvl;
    mapping temp_quest;
    int exp, pot, score;
    int quest_times = 0;
    
    if (!arg || 
        (arg != "bao xiang" 
         && arg != "xiang"
         && arg != "����"
         && arg != "��") )
    {
        return 0;
    }
     
    me = this_player();
    ob = this_object();
    
    if (is_opened)
    {
        return notify_fail("�����Ѿ��ǿ��ŵģ����Ͳ��÷Ѿ���������\n");
    }
        
    message_vision("$N�ѱ�����ˡ�\n", me);
    ob->set_name(HIY "�򿪵ı���" NOR, ({ "bao xiang", "xiang" }) );
    set("long", HIY"����һֻ���򿪵Ľ�ɫ���䣬װ�ε���ⱦ����һ���Ͳ���Ѱ����̯����\n"NOR, ob);
    is_opened = 1;

        if( random(2))set("maze/box", GOLD, ob);
        else set("maze/box", SPECIAL_OBJ, ob);
    box_type=query("maze/box", ob);
    if ( !box_type ) return 1;
    
    mazename=query("maze/mazename", ob);
    if ( !stringp(mazename) ) return 1;
    
        /*
    temp_quest=query("quest_dg", me);
    quest_times=query_temp("questdg_times", me);
    if (!temp_quest || temp_quest["maze"] != mazename)
    {
        temp_quest=query("quest_hs", me);
        quest_times=query_temp("quesths_times", me);
    }        
    if (!temp_quest || temp_quest["maze"] != mazename)
    {
        temp_quest=query("quest_kh", me);
        quest_times=query_temp("questkh_times", me);
    }        
    if (!temp_quest || temp_quest["maze"] != mazename)
    {
        temp_quest=query("quest_sn", me);
        quest_times=query_temp("questsn_times", me);
    }        
    
    if ( !temp_quest ) return 1;
    // if ( quest_times < 10 ) return 1;
        */

    switch(query("maze/box", ob) )
    {
        case SPECIAL_MAP:
            environment(query("mazeobj", ob))->set_display_map(2);
            message_vision("ֻ��$N�г��һ���׹⣬Ѹ��Ͷ�뷿������İ�ɫʯ���У���ɫʯ��Խ��������������\n", ob);
            break;
        case SPECIAL_DAN:
            bonus = new(dan_list[random(sizeof(dan_list))]);
            if (bonus) bonus->move(ob);
            break;
        case JINKUAI:
            bonus = new(jinkuai_list[random(sizeof(jinkuai_list))]);
            if (bonus) bonus->move(ob);
            break;
        case GOLD:
            bonus = new("/clone/money/gold");
            bonus->set_amount(5 + random(5));
            if (bonus) bonus->move(ob);
            break;
        case OBJ:
            temp_lvl = 4 + random(4);
            temp_quest = QUEST_OBJ_D(temp_lvl)->query_questsn();
            if (mapp(temp_quest))
            {
                bonus = new(temp_quest["object"]);
                if (bonus) bonus->move(ob);
            }
            break;
        case SPECIAL_OBJ:
            bonus = new(obj_list[random(sizeof(obj_list))]);
            if (bonus) bonus->move(ob);
            break;
        case NPC_SKILL:
            //FUBEN_D->query_maze_mainobj()->set_npcs_weakly();
            environment(query("mazeobj", ob))->set_boss_weakly();
            set("long", HIY "����ײ���Լ����һ���֣���˵�Թ���������״̬��������\n" NOR);
            break;
        default:
            break;        
    }

    delete("maze", ob);

    if ( random(3) == 0 ) return 1;
    
    // exp = temp_quest["bonus"];
    exp = 50;
    if (exp < 50) exp = 50;
    exp += random(exp*2);
    pot = exp/2 + random(exp);
    score = exp/2;
    
    GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "score" : score ]), 1);

    
    return 1;
}
