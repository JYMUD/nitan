// enchase.c
#include <ansi.h>
inherit ITEM;

int is_equip_soul() { return 1; }

string chinese_s(int arg)
{
      if( arg == 1 ) return HIK "���ʵ�"; 
      if( arg == 2 ) return HIB "��ͨ��"; 
      if( arg == 3 ) return HIR "���µ�"; 
      if( arg == 4 ) return HIM "׿Խ��"; 
      if( arg == 5 ) return HIY "��Ͼ��"; 
      if( arg == 6 ) return HIY "������";
      if( arg == 7 ) return HIY "��֮��"; 
}

string extra_long()
{
        int i, level;
        string *apply, str, msg, type;
        mapping data;
        int value;

        str =  sprintf( WHT "\n�������� : װ��֮��<%s" NOR+WHT">������%d�ˣ�����%s��ʧ\n" NOR,
                        this_object()->name(), this_object()->query_weight(),
                        (this_object()->query_autoload() || query("auto_load")) ? "��" : "" );

        if( query("status") ) str += sprintf(WHT "����Ʒ�� : " NOR "%s\n" NOR, chinese_s(query("status")));

        return str;
}
