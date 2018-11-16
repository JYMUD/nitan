//  ����룺�����ھ�����ͷ  /d/city/lanzhou/npc/bigguard.c
//  �ȼ���
//  �����ȡ������ɵĶ���ʦ�����е����ɵ�һ��ʦ����������֪���ĺ���
//  ������
//  ��һ�����ļ���Ϊ�����������������������弶�书��  ��������������
//          ���飨  ��������  ��������������  ������������  ������������
//          ������  ����������  �������������ܡ�������  ��������    ��������
//  By Lin
//  Changed Lala, 1998-03-25

#include <ansi.h>
string ask_skills();
inherit NPC;
int CanTeach();



void create()
{
    set_name( "�����", 
        ({ "qin tianbiao", "qin", "qintianbiao", "tianbiao", "master" }) );
    set( "title", HIW"�����ھ�����ͷ"NOR );
    set( "nickname", CYN"������һ��"NOR );
    set( "gender", "����" );                //�Ա���
    set( "age", 72 );                       //���䣺52
    set( "str", 30 );                       //������30
    set( "cor", 30 );                       //��ʶ��30
    set( "dex", 30 );                       //����30
    set( "per", 22 );                       //��ò��22
    set( "int", 35 );
    set( "rank_info/respect", "��Ӣ��" );   //���ƣ���Ӣ��
    set( "positive_score", 18000 );         //��������18000
    set( "negative_score",  2000 );         //��������2000
    set( "long", @LONG
    ���������ʱ�������쳣���࣬�������������µ��˺ܶ�����׼ҵ��ӣ���
���ֵø������ڣ���������ɰ�ƹ������൱�˵á������������ھֵĴ󵱼ҡ�
LONG
    );

    set_wugong( "blade",        120,    120,    0 );    //�ᵶ��ʽ��    һ��
    set_wugong( "ditang-dao",   120,    120,    0 );    //���˵���      ����
    set_wugong( "wuhu-dao",     100,    100,    0 );    //�廢���ŵ���  ����
    set_wugong( "kuaidao",      105,    105,    1 );    //�쵶ʮ��ʽ��  �ļ�
    set_wugong( "fenglei-dao",  150,    150,    0 );    //���׵���      �弶

    set_wugong( "unarmed",      120,    120,    0 );    //����ȭ����    һ��
    set_wugong( "luohan-quan",  100,    100,    0 );    //�޺�ȭ��      һ��
    set_wugong( "taizu-quan",   120,    120,    0 );    //̫�泤ȭ��    ����
    set_wugong( "weituo-zhang",  80,     80,    0 );    //Τ���ƣ�      ����
    set_wugong( "tiesha-zhang", 150,    150,    1 );    //��ɰ�ƣ�      ����

    set_wugong( "qinggong",     120,    120,    0 );    //�����Ṧ��    һ��
    set_wugong( "feiyan-zoubi", 120,    120,    0 );    //�����߱�֮��������
    set_wugong( "feiyan-gong",  100,    100,    1 );    //���๦��      ����      
    set_wugong( "caiyun-gong",   90,     90,    1 );    //���ƹ���      �ļ�
    set_wugong( "xueying-jian", 100,    100,    1 );

    set_wugong( "banruo-xinfa",120,    120,    1 );    //�����ķ�

    set_xiuwei_by_type( "blade",    3000 ); //������Ϊ��    �弶
    set_xiuwei_by_type( "unarmed",  1800 ); //ȭ����Ϊ��    ����
    set_xiuwei_by_type( "dodge",    1800 ); //�Ṧ��Ϊ��    ����
    set_xiuwei_by_type( "zonggang",  1000 ); //�ܸ���Ϊ��    һ��

    set( "max_force",   2700 );             //������    2700
    set( "force",       2700 );
    set( "force_factor", 135 );             //������    135 (5%)

    set_hp( "kee",      875 );              //���������ܣ�  875
    set_hp( "sen",      875 );

    set( "combat_exp",  1000000 );          //ս�����飺100��
    set( "social_exp",   170000 );          //����������17��
    set( "talk_msg", ({
        "����λӢ�������ھ��кι�ɣ���",
    }) );
    set("inquiry",([
        "�书"   :    (: ask_skills :),
        "skills" :    (: ask_skills :),
    ]) );
    setup();

    carry_object( CLOTH_DIR + "cloth5" )->wear();       //�ϳ���
    add_money( "silver", 5 );               //����������
       
}

void init()
{
    object ppl;

    ::init();

    if ( !userp( ppl = this_player() ) 
        || !can_act() ) 
        return;

    remove_call_out( "Greeting" );
    call_out( "Greeting", 1, ppl );
}

void Greeting( object ppl )
{       
     
    if( !ppl 
        || environment( ppl ) != environment() ) 
        return;
    if( ppl->query_temp( "marks_lin/kill_wang" ) )       //�������ɱ����̫ҽ
    {
        message_vision( "�������$N��ŭ��˵�������벻�����˾����۸����ҵ�ͷ��"
            "������\n", ppl );
        message_vision( "������$N��ȵ���������Ϊ�����ɱ��𣡡�\n", ppl );
        kill_ob( ppl );
        ppl->fight_ob( this_object() );
        return;
     }
    command( "say ����λӢ�������ھ��кι�ɣ���" );
    command( "look "+ ppl->query( "id" ) );
}

int refuse_killing( object ppl )            //��ɱʱ�ķ�Ӧ
{
    object npc = this_object();

    if( !living( npc ) 
        || query_temp( "weapon" ) )
        return 0;
    message_vision( "$N����$nһ�ۣ���Ц��������Ȼ������ô��֪��ߵغ�Ŀ���֮"
        "ͽ���ߺߣ����Ϸ����ú���ʰ�㣡��\n", npc, ppl );
    new( BLADE_DIR "blade2" )->move( npc ); //��һ�ѵ���
    command( "wield blade" );               
    command( "enable fenglei-dao" );         //ʹ�÷��׵�
    command( "disable kuaidao" );            //��ʹ�ÿ쵶
    return 0;
}

int killed_enemy( object ppl )              //ɱ�����˵ķ�Ӧ
{
    if ( ppl->query( "marks_lin/kill_wang" ) )//���ɾ��ɱ����̫ҽ�ļ�¼
        ppl->delete( "marks_lin/kill_wang" );
    ppl->delete_temp( "marks_lin/" );
    return 1;
}

int valid_teach( object ppl, string skill )
{
	command( "say ���Ժ�Ҫ����ΪʦѺ�ڣ����Ŷ����������ķ�����" );
    if ( ppl->query( "marks/lin/��������B/�͹�" )!=1)      //���û��ѧ����ı��
    {
        command( "say ���������ˣ�Ҫ��Ϊ��͢���£���" );
        return 0;
    }

    if ( !query_jibie( skill ) )
        return 0;

    if ( skill == "blade"              //�߼����书����ѧ
        || skill == "unarmed" 
        || skill == "qinggong" )
    {
        command( "say ����Щ�����̫�����ˣ�û������㰡����" );
        return 0;
    }
    
    return 1; 
}

int zhongcheng( object ppl, string skill )  //������ҳ϶�
{
    return 1;
}

string ask_skills()
{ 
    command( "sigh" );
   return "Ϊʦ�뿪���ֺ󣬸����ܶ���ʦ������˵������쵶ʮ��ʽ��\n
           �廢���ŵ������׵��Լ����ƹ��ȶ���ѧ����\n
           ��ϧ����˼���������ҵ�����ɱ�˵���������ѧ�ᡣ";
   
}