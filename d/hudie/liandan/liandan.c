// By zjb@ty 2002-5-15

#include <ansi.h> 
inherit ROOM; 
int do_dan(object me,object obj);
int do_yao(object me,object obj);
void create()
{
        set("short", HIY"������"NOR);
        set("long", @LONG
�����ǻ�٢��������,�����������һ������¯,
����ǿ��������Լ��ھ����Ĳ�ҩ�����Լ�����ĵ���ҩ!
LONG
        );
        set("exits", ([
  "east" : "/d/changan/ca14",
        ]));
        set("no_fight",1);
        set("no_beg",1);
        set("no_steal",1);
        setup();
}

void init()
{ 
        add_action("do_zhuyao","zhuyao");
        add_action("do_fangdan","fangyao");
        add_action("do_liandan","liandan"); 
}

int do_fangdan(string arg)
{
    object obj;
    object ob;
    object me = this_player();

    if(!arg) return notify_fail("��Ҫ��ʲôҩ��ȥ��\n");

    if( !query_temp("zhuyao", me) )
    return notify_fail("����Ҫ�ȷ���ҩ,Ҫ��Ȼ�������õ�!\n");

    if( !objectp(obj = present(arg, me)) )
    return notify_fail("�����ϲ�û����������!\n");

    return do_dan(me, obj);

}

int do_zhuyao(string arg)
{
    object obj;
    object ob;
    object me = this_player();

    if(!arg) return notify_fail("��Ҫ��ʲô��������ҩ��\n");

    if( !objectp(obj = present(arg, me)) )
    return notify_fail("�����ϲ�û����������!\n");

  if(me->is_busy())
  return notify_fail("��������æ,��һ�����ڰ�!\n");


    return do_yao(me, obj);

}

int do_liandan(string arg)
{
    int shoubi,tui,all,zhuyao,all2,zjb,liandan;
    object dan;
    object me = this_player();
    shoubi=query_temp("liandan/shoubi", me);
    tui=query_temp("liandan/tui", me);
    all=query_temp("liandan/all", me);
    all2=query_temp("liandan/random", me);
    zhuyao=query_temp("zhuyao", me);
    zjb=query_temp("zjb_dan", me);
    liandan = me->query_skill("liandan-shu",1);

    if (!arg) return notify_fail("��Ҫ���ĸ�����ĵ���\n");

    if( !query_temp("liandan", me) )
    return notify_fail("��û�ŵ�,������ƨ!\n");


// By zjb@ty ���¶������Ʋзϵ�ҩ������
    if (arg == "shoubi") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);

    
// By zjb@ty �����Ķ��⽱��!
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"����������ʱ��֪��������Ҳ������ȥ��!\n"NOR);

    if (shoubi==32 && zhuyao==1) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    dan=new("/d/zjb/yao/shoubi1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"�����������Ʊ��˵���ҩ��ҩ��!\n"NOR);
    }
    if (shoubi==26 && zhuyao==2) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/shoubi2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIB"�����������Ʊ��˵���ҩ������!\n"NOR);
    }
    if (shoubi==27 && zhuyao==3) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/shoubi3");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"�����������Ʊ��˵���ҩ�ȸ���!\n"NOR);
    }
    if (shoubi==33 && zhuyao==4) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/shoubi4");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"�����������Ʊ��˵���ҩ����Ѫ����!\n"NOR);
    }

    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"����䷽���󲻶�,����һ������ҩƷ!\n"NOR);
    }

    if (arg == "tui") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);
    
// By zjb@ty �����Ķ��⽱��!
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"����������ʱ��֪��������Ҳ������ȥ��!\n"NOR);

    if (tui==74 && zhuyao==11) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/tui1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIC"���������������˵���ҩ--��Ѫֹʹ��!\n"NOR);
    }
    if (tui==151 && zhuyao==12) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/tui2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"���������������˵���ҩ--���Ͻӹ�ɢ!\n"NOR);
    }

    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"����䷽���󲻶�,����һ������ҩƷ!\n"NOR);
    }
    
    if (arg == "all") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);

// By zjb@ty �����Ķ��⽱��!
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"����������ʱ��֪��������Ҳ������ȥ��!\n"NOR);

    if (all==51 && zhuyao==21) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"������������ʥҩ--�����ɢ!\n"NOR);
    }
    if (all==64 && zhuyao==22) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"������������ʥҩ--���嵤!\n"NOR);
    }
    if (all==40 && zhuyao==23) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all3");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"������������ʥҩ--׳�����ǵ�!\n"NOR);
    }
    if (all==55 && zhuyao==24) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all4");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"������������ʥҩ--��ɰûҩɢ!\n"NOR);
    }
    
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"����䷽���󲻶�,����һ������ҩƷ!\n"NOR);
    }

// By zjb@ty ��������������ĳ���!    
    if (arg == "random") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);
    
// By zjb@ty �����Ķ��⽱��!
    me->improve_skill("liandan-shu", me->query_int()*300+random(100));
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"����������ʱ��֪��������Ҳ������ȥ��!\n"NOR);

    if ( liandan > 500 && zjb > 15) {
    if ( zjb>15 && zjb<20 && all2 < 211 &&all2 > 100 
    && random(10000)>9995) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan11");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(BLINK HIR"�㾹Ȼ�����˿���ʹ�������Ļ��굤!!!\n"NOR);
    }
    }

   if ( liandan > 300 && zjb > 10 && random(100)>70) {

    if ( zjb < 15 && zjb>10 && all2 < 200 && all2 > 100 
    && random(100)>90) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan19");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIC"�������˿�������ȫ���书�ļ��ܵ�!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>3 && all2 < 200 && all2 > 30 
    && random(100)>60) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan12");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIB"�������˿���ʹ�˷��ϻ�ͯ���ɵ�!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan6");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿���������������ı�����!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan7");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿�������������������!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan8");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿�������������ǵĸ��ǵ�!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan9");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿��������������Ե����Ե�!!!\n"NOR);
    }

   if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>20) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan23");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿��������湦���湦��!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan10");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿�������������ò�����յ�!!\n"NOR);
    }

    }

    if ( zjb==2 &&all2 < 100 && all2 > 1 ) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/city/npc/obj/yangjing");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIY"���������ƾ��õ�������!\n"NOR);
    }


    if ( zjb < 4 && zjb > 1 && all2 < 100  && all2 > 5 ) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/city/npc/obj/jinchuang");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIY"�������������õĽ�ҩ!\n"NOR);
    }

    if ( zjb < 8 && zjb>3 && all2 < 100 && all2 > 30 && random(10)>4
    && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"�������˿�ʹ�Լ�ʹ�Լ�����busy�ļ��絤\n"NOR);
    }
    
    if ( zjb < 6 && zjb > 3 && all2 < 100 && all2 > 20 
    && random(10)>4&& zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan3");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"������������ʥҩ������!\n"NOR);
    }
    
    if ( zjb < 10 && zjb > 4 && all2 < 100 && all2 > 20 
    && random(10)>4&& zhuyao >= 11 && zhuyao < 15) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan4");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"������������ʥҩ�󻹵�!\n"NOR);
    }

    if ( zjb < 6 && zjb > 3 && all2 < 100 && all2 > 20 
    && random(10)>4&& zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan5");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"�������˲���ʥҩ,����!!!\n"NOR);
    }

    if ( zjb < 10 && zjb > 2 && all2 < 100 && all2 > 10 
    && random(10)>3 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan13");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"�������˿ɽ�ٶ��Ľⶾ��!!!\n"NOR);
    }

    if ( zjb < 10 && zjb > 2 && all2 < 100 && all2 > 10 
    && random(10)>3 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan14");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"�������˿����ӹ�������ս����!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 2 && all2 < 100 && all2 > 30 
    && random(10)>8 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan15");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"�������˿����Ӽ��ܵ�����!!!\n"NOR);
    }

    if ( zjb < 7&& zjb > 2 && all2 < 100 && all2 > 20 &&random(10)>4
    && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿�ʹ�Լ�״̬�ָ�����Ѫ����!\n"NOR);
    }

    if ( zjb < 10 && zjb > 3 && all2 < 100 && all2 > 10 
    && random(10)>2 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan16");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIB"�������˿�����������������!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 3 && all2 < 150 && all2 > 30 
    && random(10)>3 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan17");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿����ӻ����ڹ���̫����!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 1 && all2 < 150 && all2 > 10 
    && random(10)>3 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan18");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿����ӻ��������а����!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 3 && all2 < 150 && all2 > 30 
    && random(10)>8 && zhuyao >= 11 && zhuyao < 15) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan20");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿����ӻ����Ṧ�ľ�����!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 3 && all2 < 150 && all2 > 30 
    && random(10)>3 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan21");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿����ӻ���ȭ�ŵ�������!!!\n"NOR);
    }

    if ( zjb < 10 && zjb > 4 && all2 < 150 && all2 > 50 
    && random(10)>3 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan22");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"�������˿����Ӷ���д�ֵ�������!!!\n"NOR);
    }

    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"��˴�����ʧ��,����һ������ҩƷ!\n"NOR);
}
    }

int do_dan(object me,object obj)
{
    object ob;
    string arg=obj->short(1);
  
    foreach ( ob in all_inventory(me)){
    if (ob->short(1)!=arg) continue;
    if( !query("yao", ob)){
    write("��������������������ҩ!\n");
    return 1;
    }

    if( query_temp("danname/"+query("id", ob, me)+"") )
    return notify_fail("���Ѿ���"+ob->name()+"�Ž�����¯��!\n");

    if( query("shoubi", ob) )
    addn_temp("liandan/shoubi",query("shoubi",  ob), me);

    if( query("tui", ob) )
    addn_temp("liandan/tui",query("tui",  ob), me);

    if( query("all", ob) )
    addn_temp("liandan/all",query("all",  ob), me);

    if( query("random", ob) )
    addn_temp("liandan/random",query("random",  ob), me);

    set_temp("danname/"+query("id", ob)+"", 1, me);
    addn_temp("zjb_dan", 1, me);
    write(HIR"���"+ob->name()+HIR"�Ž�������¯!\n"NOR);
    destruct(ob);
    return 1;
    }
}

int do_yao(object me,object obj)
{
    object ob;
    string arg=obj->short(1);
    me = this_player();
 
    if( query_temp("zhuyao", me) )
    return notify_fail("�Բ������Ѿ���"+query_temp("zhuyaoname", me)+"����ҩ��!\n");

    foreach ( ob in all_inventory(me)){
    if (ob->short(1)!=arg) continue;
    if( !query("zhuyao", ob)){
    write("������������������ҩ!\n");
      return 1;
    }
    write(HIR"����"+ob->name()+HIR"����ҩ!\n"NOR);
    set_temp("zhuyao",query("zhuyao",  ob), me);
    set_temp("zhuyaoname", ""+ob->name()+"", me);
    destruct(ob);
    return 1;
    }
}

