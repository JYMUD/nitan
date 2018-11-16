// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(BLU "������" NOR, ({ "contract" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 10000);
                set("long", BLU "����һ����������\n" NOR);

        }
        setup();
}

string long()
{
        int i, n;
        string msg;
        string *rec;
        
        msg = query("long");         
        rec = query("offer");
        
        if( !rec ) return msg; 
        else {
                n = sizeof(rec);
                for( i=0; i<n; i++ ) {                        
                        msg += rec[i];
                }
                return msg;
        }
}
