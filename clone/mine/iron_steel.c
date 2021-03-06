// iron_steel.c

#include <mine_def.h>

inherit ITEM;

string query_long();

int is_iron_class_res() { return 1; }
string query_mine_class() { return STEEL_RES; }
int query_mine_value();

void create(int arg)
{
        set_name("钢锭", ({ "steel ingot" }) );
        set_weight(0);

        if(intp(arg) && (arg >= 100))
                set_weight(arg);

        set("value", evaluate((: query_mine_value :),this_object()) );
        set("unit", "块");
        set("long", evaluate((: query_long :), this_object()));
}

int query_mine_value()
{
        int wt;

        if( (wt = query_weight()) < 100 )
                return 0;

        return MINE_D->query_mine_class_value(STEEL_RES)*query_weight()/100;
}

string query_selling_msg()
{
        int w = query_weight();

        if(w < 100)
                return "一钱不值";
        else
                return sprintf("%d 两重", w/100);
}

string query_long()
{
        int w = query_weight();
        string l = "这是一块钢锭，";

        if(w < 100)
                l += "看起来\n一钱不值。\n";
        else
                l += sprintf("大约\n有 %d 两重。\n", w/100);

        return l;
}

int query_save_args()
{
        return query_weight();
}
