// tuijianxin-4.c 推薦信 澄-玄

inherit ITEM;

void create()
{
        set_name("推薦信", ({"tuijian xin4", "xin4", "letter4"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long","這是一封澄字輩師尊們為你寫的推薦信，憑此可直接向玄字輩高僧們學習武藝。\n");
//                set("no_drop", "這樣東西不能離開你。\n");
                set("material", "paper");
        }
}
