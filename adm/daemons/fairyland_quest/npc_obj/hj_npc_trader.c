//                ��׼��������ʾ��                                   |
// �þ����� NPC��֧�����֮����н��׵�ָ��
// by naihe  2003-11-04  ��ï��
// naihe 05-9-1 16:04 debug, ����ʱ��Ȼ����Ǯ��ί���ߣ�����

#include <ansi.h>
#include "errs_func.h"
// �����и� errs() ���� notify_fail() ���� write(msg), return 1;

inherit NPC;

#include "hj_settings/room_amount_hj.h"
#define     MY_ROOM_MARK        HJ_ROOM_AMOUNT
// ��NPC�������� HJ ���ֶ��Ϸ����䴦����Ч
#include "zj_lm_tarder_prefunc.h"



#define        MAX_DS_AMOUNT        50
        // ���ͬʱ ���� ����
#define        MAX_DS_AMOUNT_ME     10
        // ������ͬʱ��������
#define        SXF                  1
        // �������

object *get_goods_list( object who );
void new_goods_in( string id );


void create()
{
    set_name( "������", ({ "daishou shang", "shang" }) );
    set("nickname", HIY"ͯ�Ž��� ������ƽ"NOR );

    set("long", "����һ��ר��������������ˣ��þ�����ʿ��֮��Ľ��׶��ǵ����������еġ�

���ۻ�Ʒ��    "HIY"(daishou ��ƷID #�۸�)"NOR"
ȡ�ػ�Ʒ��    "HIY"(quhui ID)"NOR"
�鿴��Ʒ�б�"HIY"(list)"NOR"
�鿴����Ϣ��"HIY"(list qg)"NOR"
��������Ϣ��"HIY"(qiugou ID)"NOR"
�����Ʒ��    "HIY"(goumai ID)"NOR"

���ۻ�Ʒ����������Ϣ����Ҫ"HIR"������ "+SXF+" ��"NOR"������Ļþ��÷ֶ��֣���
���ۻ�Ʒʱ�����ԭ�������뿪�þ���������������ȡ�����ۣ���Ʒ�����ڱ��ء�
��������Ϣ�󣬽��ڰ�Сʱ����������ڴ��ڼ����и�ID���»�����������֪ͨ�������\n\n");

    set("gender","����");
    set("age",45);
    set("per",16);
    set("attitude","friendly");
    set("no_refresh",1);
    set("hj_game/npc","trader");

    setup();

    remove_call_out("checking");
    call_out("checking", 1);  // ����Ʒ��Ч��

    remove_call_out("me_do_ads");
    call_out("me_do_ads", 1 ); // �������ʲô��
}

void init()
{
    add_action("do_daishou", "daishou");
    add_action("do_goumai", "goumai");
    add_action("do_quhui", "quhui");
    add_action("do_list", "list");
    add_action("do_qiugou", "qiugou");
}

// ����ļ����������������  message() ���ǲ�������������̫���ɧ��



// �����Ч�Ļ�Ʒ�б�
// ��Ч�ģ���������
object *get_goods_list( object who )
{
    object *temp, *ok_goods, *bad_goods, t, me, env;
    int i;

    temp = all_inventory(this_object());
    if( !temp || sizeof( temp ) < 1 )
        return 0;

    if( !who ) who = this_object();

    ok_goods = ({ });
    bad_goods = ({ });

    for( i=0;i<sizeof(temp);i++)
    {
        t = temp[i];
        // ��hj�����������ɾ��
        if( !query("hj_game/obj", t) )
        {
            destruct( t );
            continue;
        }

        // ��������� hj �������׼������
        if( !query("sell_value", t) || !query("seller_mark", t) || !query("sell_id", t) )
        {
            bad_goods += ({ t });
            continue;
        }

        // ���������뿪 hj (�˳�������)��׼������
        // ����Ϊ�˱������˼��˱��˵ı���ֹ���ŵ��������߼�
        // ��ʱ�򣬱����˱�����˿���ѡ��PK���ˣ����ɵûر��������
        me=query("seller", t);
        if( !me || !me_ok( me )
           || !environment(me) || !query("room_mark", environment(me) )
           || query_temp("this_time_mark", me) != query("seller_mark", t) )
        {
            bad_goods += ({ t });
            continue;
        }

        // �õģ������OK
        if( who == this_object() || me == who )
            ok_goods += ({ t });
    }

    // �����Ҫ���µĶ���
    if( bad_goods && sizeof(bad_goods) )
    {
        env = environment(this_object());
        for(i=0;i<sizeof( bad_goods);i++)
        {
            message_vision( sprintf("$N����һ%s%s�������ֹ���һ��ʲô��\n",
                query("unit", bad_goods[i]),query("name", bad_goods[i])),
                    this_object() );
            bad_goods[i]->move( env );
        }
    }

    if( !ok_goods || sizeof( ok_goods ) < 1 )
        return 0;
    return ok_goods;
}

int do_daishou( string arg )
{
    object me = this_player(), ob = this_object(), g, *temp;
    int value;
    string g_id, *no_sell_list;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("�㻹æ���ء�\n");

    // ���жϹ�����Ǯ�������ѣ�����������һϵ���жϡ�
    // ��Ȼ���λ�ò����ж�����������
    if( query_temp("hj_score", me)<SXF+1)//���+1�ɱ����
        return errs("�������⵰�������Ѷ��������ѵ�����Ҫ�Ұ�������£���\n");

    if( !arg || sscanf( arg, "%s #%d", g_id, value ) != 2 )
        return errs("��Ҫ����ʲô��Ʒ(daishou ��ƷID #�۸�)�����磺 daishou xy jian #10\n");

    if( value<10 ) return errs("�ⶫ������ô���ˣ�������׬�������ѣ�����ʡʡ�ɡ�\n");
    if( value > 1000 ) return errs("�����Ǯ̫�����ˣ�����ɲ��Ҵ����������û��Ҫ��������ռ�ط���\n");

    g = present( g_id, me);
    if( !g ) return errs("������û���ⶫ����\n");
    if( !query("hj_game/obj", g) )
        return errs(query("name", g)+"��ʲô����������ô����ʶ������\n");

    // ��ֹ����id�б�
    no_sell_list = ({ "qixing deng", "shenren ling", "youling ling",  });

    if( member_array(query("id", g),no_sell_list) != -1 )
        return errs("��"+query("name", g)+"������������\n");

    if( query("hj_game/obj", g) == "other" && query("id", g) != "slguo" )
        return errs(query("name", g)+"������������ɲ���������\n");

    // �����Ƿ����
    temp = get_goods_list( me );
    if( temp && sizeof( temp ) >= MAX_DS_AMOUNT_ME )
        return errs("�㻹�кܶ�����������أ����ǵ�����һЩ����˵�ɡ�\n");
    temp = get_goods_list( ob );
    if( temp && sizeof( temp ) >= MAX_DS_AMOUNT )
        return errs("������Ļ������÷Ų����ˣ����ǵ�����һЩ����˵�ɡ�\n");


    // ok, ��Ϊ���ۡ�
    addn_temp("hj_score", -SXF, me);
    g->move( ob );
    set("seller", me, g);
    set("sell_id",query("id",  me), g);
    set("sell_value", value, g);
    set("seller_mark",query_temp("this_time_mark",  me), g);
    set("new_goods_msg",({query("name", me),g->short(),sprintf("%d",value)}));
    set( "new_goods", g );

    message_vision(CYN"$N"NOR+CYN"�ó�һ"+query("unit", g)+query("name", g)+NOR+CYN"�ݸ���$n"NOR+CYN"��˵���������æ���������Ҫ��\""+value+"\"�����Ǯ������\n"NOR,me,ob);
    message_vision( CYN"$N"NOR+CYN"���ó�һ��ʲô������$n"NOR+CYN"��˵������������СС��˼���鷳���ˣ���\n"NOR,me,ob);
    command("ok"+query("id", me));

    // �»�Ʒ���֣������Ƿ����󹺸�Ʒ����ң��о�֪ͨ
    // �ŵ���һ��������Ū����
    call_out("new_goods_in",3,query("id", g));

    me->start_busy(1);

    return 1;
}


// ȡ�ش��ۻ�Ʒ
int do_quhui( string arg )
{
    object g, me = this_player();

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("�㻹æ���ء�\n");

    if( !arg ) return errs("��Ҫȡ��ʲô������\n");

    // ��һ����
    get_goods_list( this_object() );

    g = present( arg, this_object() );
    if( !g ) return errs("����û������������\n");
    if( query("seller", g) != me)return errs("��"+query("name", g)+"�������������۵ģ������ٰ���\n");


    // ok.

    g->move(me);
    message_vision( sprintf( CYN"$N"NOR+CYN"����$n"NOR+CYN"˵����������ȡ���ҵ�%s"NOR+CYN"����\n$n"NOR+CYN"���˵�ͷ���ó�һ%s%s"NOR+CYN"�ݸ���$N"NOR+CYN"��\n"NOR, 
        query("name", g),query("unit", g),query("name", g)),me,this_object());

    me->start_busy(1);
    return 1;
}


// �����Ʒ
// �ж����̺� do_quhui ����һ����
int do_goumai( string arg )
{
    object g, me = this_player(), seller;
    int value;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("�㻹æ���ء�\n");

    if( !arg ) return errs("��Ҫ����ʲô������\n");

    // ��������������Ǯ�ȣ��������һ�� all_inv
    if( query_temp("hj_score", me)<10 )
        return errs("����ܵ�Ǯ�����ɡ�\n");

    // ��һ���ȡ���ʱ���Ѳ��������Ķ����
    get_goods_list( this_object() );

    g = present( arg, this_object() );
    if( !g ) return errs("����û������������\n");
    if( query("seller", g) == me)return errs("��"+query("name", g)+"�����������۵ģ�����Ҫȡ����(quhui)\n");

    value=query("sell_value", g);
    if( value < 10 )
        value = 10;
    if( query_temp("hj_score", me)<value )
        return errs("������������������\n");

    // ok.
    addn_temp("hj_score", -value, me);
    g->move(me);
    message_vision( sprintf( CYN"$N"NOR+CYN"����$n"NOR+CYN"˵�������������%s"NOR+CYN"����\n$n"NOR+CYN"���˵�ͷ���ó�һ%s%s"NOR+CYN"�ݸ���$N"NOR+CYN"��\n"NOR, 
        query("name", g),query("unit", g),query("name", g)),me,this_object());
    me->start_busy(1);
    if( !(seller=query("seller", g) )
      || !me_ok(seller)
       || query_temp("this_time_mark", seller) != query("seller_mark", g )
    )
        return 1;
    if( environment(seller) == environment(this_object() ) )
        message_vision( CYN +query("name")+NOR+CYN"����$N"NOR+CYN"˵����"
            "���٣����ϴμ��۵�"+query("name", g)+NOR+CYN"����ȥ�ˣ������ǵõ������롣��\n"NOR,seller);
    else
        message_vision( CYN"ֻ��һ��"+query("name")+NOR+CYN"�Ҵ����˹���������$N"
            NOR+CYN"˵���������ϴμ��۵�"+query("name", g)+NOR+CYN"����ȥ�ˣ������ǵõ������롣��\n"
            +query("name")+NOR+CYN"˵�꣬�ִҴҵ��뿪�ˡ�\n"NOR,  seller);
    tell_object( seller, "��õ��� "+value+" ����֡�\n");
    addn_temp("hj_score", value, seller);
    return 1;
}

int do_list( string arg )
{
    object me = this_player(), ob = this_object(), *list, who;
    int i, j;
    string msg, *key, *kkk;
    mapping qg_list;


    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("�㻹æ���ء�\n");

    if( !arg ) who = ob;
    else
    {
        if( arg != "qg" )
        {
            if( arg == "me")arg=query("id", me);
            who = find_player( arg );
        }
    }

/* ����Ϣ���ø�ʽ
    set("qg_list", ([
        "tmxk yyf" : ({ "naihe", "zhu", "haha", "money" }),
        "dh jian" : ({ "yes" }),
        "test" : 0,
    ]) );
*/

    if( !who )
    {
        if( arg!= "qg" ) return errs( arg+" û���κλ�Ʒ����������ۡ�\n");

        qg_list = query("qg_list");
        if( !qg_list || sizeof(qg_list) < 1 )
            return errs("����û���κ��󹺻�Ʒ����Ϣ��\n");

        msg = "��������������Ϣ��\n";
        key = keys(qg_list);
        for(i=0;i<sizeof(key);i++)
        {
            kkk = qg_list[key[i]];
            if( kkk && sizeof(kkk) )
            {
                msg += sprintf( "\n(%s) ���������£�", key[i] );
                for(j=0;j<sizeof(kkk);j++)
                    msg += sprintf( "    %s", kkk[j] );
            }
        }
        msg += "\n";
        me->start_busy(1);
        me->start_more( msg );
        return 1;
    }

    list = get_goods_list( who );
    if( !list || sizeof(list) < 1 )
    {
        if( who == ob )
            return errs("����û���κλ�Ʒ���ۡ�\n");
        else return errs( arg+" û���κλ�Ʒ����������ۡ�\n");
    }

    if( who == ob )
        msg = "������������Щ��Ʒ���ۣ�\n\n";
    else msg = "������������Щ��Ʒ�� "+arg+" ί�д��۵ģ�\n\n";

    for(i=0;i<sizeof(list);i++)
    {
        msg += sprintf( "%-40s  �ۼۣ�%4d    %-20s  �����ߣ�%s\n",
            query("name", list[i])+"("+query("id", list[i])+")",
            query("sell_value", list[i]),
            query("use_times", list[i] )
                ?"ʣ��ʹ�ô���"+query("use_times", list[i])+""
                : "�ر���Ʒ",
            query("sell_id", list[i]));
    }
    me->start_busy( 1 );
    me->start_more( msg );
    return 1;
}


// ��������Ϣ
int do_qiugou( string arg )
{
    object me = this_player(), *goods_list;
    string id = query("id", me), *temp;
    int i;

    if( !ob_ok() || !me_ok(me) ) return 0;
    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return errs("�㻹æ���ء�\n");

    if( !arg ) return errs("��Ҫ��ʲô��Ʒ��(qiugou ��ƷID)\n");

    if( query_temp("hj_score", me)<SXF+1 )
        return errs("�������⵰�������Ѷ��������ѵ�����Ҫ�Ұ�������£���\n");

    temp = query( "qg_list/" + arg );
    if( temp && sizeof(temp) )
    {
        if( member_array( id, temp ) != -1 )
            return errs("������һ����ĵ��ˣ�һ����Ϣ������֪ͨ�㣡\n");
        temp += ({ id });
        set( "qg_list/"+arg, temp );
    }
    else set( "qg_list/" + arg, ({ id }) );

    addn_temp("hj_score", -SXF, me);

    message_vision( CYN"$N"NOR+CYN"�ó�һ��ʲô������$n"NOR+CYN"��˵�������Ҽ��� \""+arg+"\" ��������������Ϣ�뾡��֪ͨ�ң���\n"NOR, me, this_object() );
    command( "nod2 "+id );
    command( "say ����Ȼ��Ȼ������ģ�һ�л���������֪ͨ����");

    call_out("delete_msg", 1800, arg, id); // ��Сʱ��ɾ��������Ϣ
    me->start_busy(1);


    // ����Ǯ�ٲ��ǲ������ֻ�
    goods_list = get_goods_list( this_object() );
    if( goods_list && sizeof( goods_list ) )
    {
        for( i=0;i<sizeof( goods_list );i++ )
        {
            if( query("id", goods_list[i]) == arg )
            {
                command("say ��Ӵ�������������������ֻ�����Ҫ��Ҫ������(list)��");
                break;
            }
        }
    }
    return 1;
}


// ��Сʱ���Զ��������Ϣ
void delete_msg( string qg_id, string who_id )
{
    string *list;
    if( !qg_id || !who_id ) return;
    list = query("qg_list/"+qg_id );
    if( !list || sizeof(list) < 1 || member_array( who_id, list) == -1 ) return;
    list -= ({ who_id });
    if( !list || !sizeof(list) )
    {
        delete( "qg_list/"+qg_id );
        return;
    }
    set("qg_list/"+qg_id, list );
}


// �»����֣�֪ͨ���󹺵����
void new_goods_in( string id )
{
    int i;
    string *ids;
    object who;

    ids = query("qg_list/"+id);
    if( !ids || sizeof(ids) < 1 ) return;
    // û�д���Ʒ������Ϣ

    for(i=0;i<sizeof(ids);i++)
    {
        who = find_player( ids[i] );
        if( !who || !me_ok(who) ) continue;
        // �����и�©�����������һ����Ϸ����������Ϣ��Ҳ��֪ͨ
        // ����Ҳ����ν~ ����Ǯ�ģ����ô�Ҳ��Ӧ�õ�~

        if( environment(who) == environment(this_object() ) )
            message_vision( CYN"$n"NOR+CYN"����$N"NOR+CYN"˵�������٣��㲻��˵Ҫ��"
                +id+"�������л��ˡ���\n"NOR,who, this_object() );
        else
            message_vision( CYN"ֻ��һ��"+query("name")+NOR+CYN"�Ҵ����˹���������$N"
                NOR+CYN"˵����������Щʱ�������"+id+"�������л��ˣ���\n"
                +query("name")+NOR+CYN"˵�꣬�ִҴҵ��뿪�ˡ�\n"NOR, who);
    }

    delete( "qg_list/"+id );
}



// ������ݣ��»���֣��л�
void me_do_ads()
{
    string *msg;
    string temp;
    int i;

    if( !environment( this_object() ) ) return;

    msg = ({
"������۸����Ʒ�������Ӽ��շѵ����ģ�(daishou)",
"�㼱����ʲô�����������ⷢ����Ϣ��һ�л���������֪ͨ��(qiugou)",
"�������ʲô���۵Ķ����ֲ������ˣ�������ȡ�ؾ��ǣ����Ĳ�ȡ��(quhui)",
"���������߹�·����Ҫ����������кö������ģ����������ɣ�(list)",
"����ʲô��������Ҫ�ģ������������ǲ�������������Ҳ����������(list qg)",
    });


    // �»���Ϣ
    if( query("new_goods") && environment( query("new_goods") ) == this_object() )
    {
        temp = query("new_goods_msg");
        if( temp && sizeof(temp) == 3 )
        {
            i=3;  // ���»���Ϣ������Ƶ�ʸ�Щ
            while(i--) 
            msg += ({ sprintf( "������%sί�е����»�Ʒ%s"NOR+CYN"������ %s �㣬������������",
                temp[0], temp[1], temp[2] ) });
        }
    }

    message_vision(CYN"$N"NOR+CYN"˵������"+msg[random(sizeof(msg))]+"��\n"NOR,this_object());

    remove_call_out("me_do_ads");
    call_out("me_do_ads", 30 );
}


// ÿ3�����м��һ����Ʒ��Ч��
void checking()
{
    get_goods_list( this_object() );
    remove_call_out("checking");
    call_out("checking", 180);
}
