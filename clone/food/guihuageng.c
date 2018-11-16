// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// guihuageng.c ��ѩ����

inherit ITEM;

void init();
void eat();

void create()
{
   set_name("��ѩ����",({"guihua geng", "guihua", "geng"}));
   set_weight(50);
   if (clonep())
     set_default_object(__FILE__);
   else {
     set("long", "������ɽ��Ů�嶥�Ĺ���ѩ���Ƴɣ��Ծ���������档\n");
     set("unit", "��");
     set("value", 800);
        set("remaining", 5);
        set("food_supply", 30);
    }
   
   setup();
}

void init()
{
   add_action("do_chi", "eat");
}


int do_chi(string arg)
{

   int heal, recover, sen, e_sen, m_sen,remaining;
   
    if( !this_object()->id(arg) ) return 0;
    if( this_player()->is_busy() )
        return notify_fail("����һ��������û����ɡ�\n");
    if( query("food", this_player() )
       >= (int)this_player()->max_food_capacity() )
     return notify_fail("���Ѿ��Ե�̫���ˣ��ٳԾͳ����ˡ�\n");

    addn("food", query("food_supply"), this_player());

    m_sen=query("max_sen", this_player());
   heal = (int)this_player()->query_con();
    e_sen=query("eff_sen", this_player());
   
    if ( e_sen < m_sen )
   {    
     if ( (e_sen + heal) >= m_sen )
     {
        set("eff_sen", m_sen, this_player());
     } else
     {   
        addn("eff_sen", heal, this_player());
     }   
   } 

    e_sen=query("eff_sen", this_player());
    sen=query("sen", this_player());
   recover = 30+heal;
    
   if (sen < e_sen )
   {
        if ( (sen + recover) >= e_sen )
        {
           set("sen", e_sen, this_player());
        } else
        {   
            addn("sen", recover, this_player());
        }   
   }

    if( this_player()->is_fighting() ) this_player()->start_busy(2);

    addn("remaining", -1);
   if ( query("remaining") )
   {
         message_vision("$N����һ���ѩ�������˼��ڡ�һ������ֱ����Ƣ��$N���þ���ö��ˡ�\n", this_player());
   } else 
   { 
         message_vision("$N������Ĺ�ѩ������øɸɾ�������������δ����\n", this_player());
     
     destruct(this_object());
   }

   return 1;
}
