// /u/jpei/thd/obj/shanshui.c

inherit ITEM;

int do_jiao(string arg);

void create()
{
        set_name("ɽˮ��", ({ "shanshui hua", "shanshui", "hua" }) );
        set("long","
ֻ��������һ������ͻأ�ĸ�ɽ����������ɽ�壬�м�һ���ȸߣ�����ָ�죬�����Ʊ�
ɽ������һ�����������һ�ѩ�������������������������֮�ҡ���������һ�����ɣ�
ȴ��ͦȻֱ��ΡΡ��Σ�������ʻ���һ��ӭ���轣�Ľ�����������Ŀ�Ѽ���������Ʈ
�٣��������ס�ȫ��������ˮīɽˮ�������������𣬸����Ե�׿Ȼ��Ⱥ�����ϲ�����
�ֻ����һ��ʫ�ƣ������곾�������£�����Ѱ���ϴ�΢����ɽ��ˮ�����㣬����߳�
�����顣��
");
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
        }
        setup();
}

void init()
{
        add_action("do_jiao","water");
        add_action("do_jiao","jiao");
}

int do_jiao(string arg)
{
        object me=this_player();
        object* inv;
        int i, remaining;

        if (!id(arg)) return 0;
        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++) {
                if( mapp(query("liquid", inv[i]))){
                        if( (remaining=query("liquid/remaining", inv[i]))>0){
                                write("���"+query("name", inv[i])+"�ﵹ��Щ"+query("liquid/name", inv[i])+"����Ϳ�ڻ��ϡ�\n");
                                write("�����������½���ϡ¶�������ּ�����..�����飬..����..����....�壬�ڶ�..�ڡ���\n");
                                set_temp("wumu_shanshui", 1, me);
                                remaining--;
                                set("liquid/remaining", remaining, inv[i]);
                                return 1;
                        }
                        else {
                                write("���"+query("name", inv[i])+"�Ѿ����ˣ���Ҳ������һ��"+query("liquid/name", inv[i])+"�ˣ�\n");
                                return 1;
                        }
                }
        }
        write("�������û�д�ʢˮ�����ߣ�\n");
        return 1;
}