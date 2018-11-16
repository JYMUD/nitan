// ���̼̳�
// Create by smallfish.
// Update by jjgod.
// Update by Lonely@nitan.org

inherit ROOM;
inherit F_SAVE;

#include <ansi.h>
#include <config.h>

class goods
{
        mapping data; // ��̬��Ʒ����
        string name;
        string id;
        string *ids;
        string type;
        string file;
        string unit;
        int amount;  // ����
        mixed value;   // intpΪgold��stringpΪ$NT
        int number;  // ���
}

class goods *all_goods = ({});

mixed query_goods() { return all_goods; }
void init_goods() { all_goods = ({}); }
int clean_up() { return 1; }

int add_one_good(object obj, mixed price, int amount)
{
        mapping data, temp;
        string id, name;
        string file;
        object obn;
        class goods item;
        string type;
        int i, n;

        if( !objectp(obj) )
                return 0;

        if( obj->is_weapon() )           type = "����";
        else if( obj->is_armor() )       type = "����";
        else if( obj->is_liquid() )      type = "����";
        else if( obj->is_food() )        type = "ʳ��";
        else if( obj->is_container() )   type = "����";
        else if( obj->is_book() )        type = "�鼮";
        else                             type = "����";

        file = base_name(obj);
        id=query("id", obj);
        name=query("name", obj);
        data = obj->query_entire_dbase();
        obn = new(file);
        temp = obn->query_entire_dbase();
        destruct(obn);

        if( !all_goods ) all_goods = ({});
        n = sizeof(all_goods);
        for( i = 0; i < n; i++ )
        {
                if( all_goods[i]->file == file &&
                    all_goods[i]->id == id &&
                    all_goods[i]->name == name ) {
                        if( obj->query_amount() || mapping_eqv(data, temp) )
                        {
                                all_goods[i]->amount += amount;
                                all_goods[i]->value = price;
                                destruct(obj);
                                return 1;
                        }

                        if( all_goods[i]->data && mapping_eqv(data, all_goods[i]->data) )
                        {
                                all_goods[i]->amount += amount;
                                all_goods[i]->value = price;
                                return 1;
                        }
                }
        }

        item = new(class goods);
        item->name = name;
        item->id = id;
        item->ids = obj->my_id();
        item->type = type;
        item->file = file;
        item->unit=query("base_unit", obj)?
                     query("base_unit", obj):query("unit", obj);
        item->amount = amount;
        item->value = price ? price :
                     (query("base_value", obj)?query("base_value", obj):
                                                 query("value", obj));
        item->number = sizeof(all_goods) + 1;
        if( !mapping_eqv(data, temp) )
                item->data = copy(data);
        all_goods += ({ item });
        destruct(obj);
        return 1;
}

public string do_stock(object ob, object me, string arg)
{
        object obj, item;
        mixed value;
        object room;
        string name;

        room = environment(ob);

        // intp(value) Ϊgold, stringp(value) Ϊ$NT
        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if (! arg || (sscanf(arg, "%s value %d", arg, value) != 2 &&
            sscanf(arg, "%s nt %s", arg, value) != 2) )
                return "ָ���ʽ��stock <����> value * ( ���� * ����ͭ������λ�ļ۸� )��\n"
                       "          stock <����> nt * ( ���� * ���� $NT ����λ�ļ۸� )\n";

        if (! value)
                return "ָ���ʽ��stock <����> value * ( ���� * ����ͭ������λ�ļ۸� )��\n"
                       "          stock <����> nt * ( ���� * ���� $NT ����λ�ļ۸� )\n";

        if (intp(value) && value > 100000000 && !wizardp(me))
                return "���������һ�����ƽ���ͱ���ô�ĺ��˰ɡ�\n";

        if (stringp(value) && to_int(value) < 0 || to_int(value) > 1000000)
                return "���������һ����$NT����ͱ���ô�ĺ��˰ɡ�\n";

        if (! (item = present(arg, me)) || ! objectp(item))
                return "�����ϲ�û��������ﰡ��\n";

        if( query("no_sell", item) )
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        if( query("no_get", item) || query("no_drop", item) || 
            query("no_put", item) || query("no_beg", item) || 
            query("no_steal", item) || query("no_drop", item) || 
            query("item_make", item) || query("owner", item) )
                return "��������ڲ��ϻ��ܣ�����ʱ���ó���������\n";

        if (item->is_item_make())
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        if( query("wiz_only", item) && !wizardp(me) )
                return "�������ֻ������ʦ�̵�������\n";

        if (item->is_character())
                return "�㲻�ܷ������\n";

        if( query("money_id", item) )
                return "���ǮҲ�������ۣ�\n";

        switch(query("equipped", item)){
        case "worn":
                return item->name() + "���������������ܴ�š�\n";

        case "wielded":
                return item->name() + "�����Ƚ��װ�����ܴ�š�\n";
        }

        if (sizeof(all_goods) >= 80)
                return "������ϵĶ���̫���ˣ����ռ��ֻ����ٰڰɡ�\n";

        if (item->query_amount() && item->query_amount() > 1)
        {
                obj = new(base_name(item));
                obj->set_amount((int)item->query_amount() - 1);
                item->set_amount(1);
                obj->move(me, 1);
        }

        name = item->name(1);
        add_one_good(item, value, 1);

        message_vision(HIW "$N" HIW "����" HIG + name + HIW "������" HIY +
                (intp(value) ? MONEY_D->price_str(value) : (value+"NT")) + HIW "�ļ۸�ʼ���ۡ�\n" NOR, me);
        room->save();

        return "����ú��˻��\n";
}

public string do_unstock(object ob, object me, string arg)
{
        object item, room;
        int i, n;

        seteuid(getuid());
        room = environment(ob);
        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if (! arg)
                return "ָ���ʽ��unstock <����>\n";

        if (! (n = sizeof(all_goods)))
                return "�����ڻ�û�а����κλ��\n";

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED && !wizardp(me))
                return "�����ϵĶ���̫���ˣ�û���ӻ�����ȡ������\n";

        for( i = 0; i < n; i++ )
        {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                {
                        if( !(all_goods[i]->amount) ) {
                                all_goods[i] = 0;
                                return "����"+query("short", room)+"�Ļ����ϲ�û���������\n";
                        }

                        all_goods[i]->amount -= 1;

                        if( !all_goods[i]->data )
                                item = new(all_goods[i]->file);
                        else
                        {
                                item = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                item->set_name(query("name", ob),all_goods[i]->ids);
                        }

                        if( all_goods[i]->amount == 0 )
                                all_goods[i] = 0;
                        break;
                }
        }
        all_goods -= ({ 0 });

        message_vision(HIW "$N" HIW "����" HIG + item->name(1) + HIW"���ӻ�����ȡ���������ˡ�\n" NOR, me);

        room->save();

        if (! item->move(me))
        {
                item->move(environment(me));
                tell_object(me, "�������Ѿ��ò����ˣ�ֻ�ð�" + item->name(1) + NOR "���ڵ��ϡ�\n");
        }
        return "��ȡ���˻��\n";
}

public varargs string do_list(object ob, object me, string arg)
{
        string output, desc;
        class goods item;
        object room;

        if( !wizardp(me) && me->query_condition("killer") )
                return CYN "���̲���ɱ�˷������⣡\n" NOR;

        if( me->is_busy() ) {
                return BUSY_MESSAGE;
        }

        room = environment(ob);
        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if( query("ban", room) && 
                member_array(query("id", me),query("ban", room)) != -1 )
                return "������ҵ��̲��ܻ�ӭ������޷���������\n";

        if( !sizeof(all_goods) ) {
                return "����"+query("short", room)+"Ŀǰ��û�г����κλ��\n";
        }

        output = "�õ���Ŀǰ����������Ʒ��\n";

        foreach( item in all_goods ) {
                if( item->amount < 0 ) desc = "������Ӧ";
                else if( item->amount == 0 ) desc = "��ʱȱ��";
                else if( item->amount < 11 )
                        desc = sprintf("��ʣ%2d%2s", item->amount, item->unit);
                else if( item->amount < 31 )
                        desc = sprintf("��ʣ%2d%2s", item->amount, item->unit);
                else
                        desc = "��Դ����";

                output += sprintf("(%3d)%" + sprintf("%d", (30 + color_len(item->name))) +
                                  "-s��ÿ%s%s" CYN "(�ֻ�%s)\n" NOR,
                                  item->number,
                                  item->name + "(" + item->id + ")",
                                  item->unit,
                                  stringp(item->value) ? item->value + "$NT" : MONEY_D->price_str(item->value),
                                  desc);
        }

        if (query("invite/" + query("id",me),room))
                output += WHT"���Ǳ��������������л��������"HIW+chinese_number(query("invite/"+query("id",me),room))+HIW"��"NOR+WHT"���Żݡ�\n" NOR;
        return output;
}

public int do_buy(object obj, object me, string arg)
{
        mixed value;
        object ob;
        int i, n;
        object room;

        room = environment(obj);
        if( !query("shop_type", room) )
        {
               tell_object(me, "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n");
               return 1;
        }

        if( query("ban", room) && 
                member_array(query("id", me),query("ban", room)) != -1 )
        {

               tell_object(me, "������ҵ��̲��ܻ�ӭ������޷���������\n");
               return 1;
        }

        if(me->is_busy())
        {
                tell_object(me, "ʲô�¶��õ���æ����˵�ɣ�\n");
                return 1;
        }

        if (! arg)
        {
                tell_object(me, "��Ҫ��ʲô������\n");
                return 1;
        }

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
        {
                tell_object(me, "�����ϵĶ���̫���ˣ��ȴ���һ���������ɡ�\n");
                return 1;
        }

        n = sizeof(all_goods);
        if( !n ) {
                tell_object(me, "Ŀǰ%sû�п������Ķ�����\n");
                return 1;
        }


        {
                tell_object(me, "�õ��̲�û�г����������\n");
                return 1;
        }

        for( i = 0; i < n; i++ ) {
                if( (all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg) {
                        if( !(all_goods[i]->amount) ) {
                                tell_object(me, sprintf("Ŀǰ��%s" CYN "ȱ��������һ��ʱ��������",
                                        all_goods[i]->name));
                                return 1;
                        }
                        break;
                }
        }

        value = all_goods[i]->value;

        // ����ǹ���������Ż�
        if (query("invite/" + query("id",me),room))
        {
                if (intp(value))
                        value = value * query("invite/" + query("id",me),room) / 10; 
                else
                        value = to_string(to_int(value) * query("invite/" + query("id",me), room) / 10); 
        }

        if (intp(value))
        {
                switch (SHOP_D->player_pay(me, obj, value))
                {
                case 0:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "��Ц������⵰��һ�ߴ���ȥ��\n" NOR);
                        return 1;

                case 2:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "��ü����������û����Ǯ������Ʊ�ҿ��Ҳ�����\n" NOR);
                        return 1;

                default:
                        if( !all_goods[i]->data )
                                ob = new(all_goods[i]->file);
                        else
                        {
                                ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                                ob->set_name(query("name", ob),all_goods[i]->ids);
                        }
                        all_goods[i]->amount -= 1;
                        if( all_goods[i]->amount = 0 )
                                all_goods[i] = 0;
                        if (ob->query_amount())
                        {
                                message_vision("$N��$n����������" + ob->short() + "��\n", me, obj);
                        }
                        else
                        {
                                message_vision("$N��$n����������һ"+query("unit", ob)+query("name", ob)+"��\n",me,obj);
                        }

                        ob->move(me, 1);
                }
        } else
        {
                string owner=query("owner", environment(obj));
                if (!MEMBER_D->player_pay(me, to_int(value), owner))
                {
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "��Ц������û���㹻��$NT��������ȥ��ֵ�ɡ�\n" NOR);
                        return 1;
                }
                if( !all_goods[i]->data )
                        ob = new(all_goods[i]->file);
                else
                {
                        ob = TEMPLATE_D->create_object(all_goods[i]->file, all_goods[i]->id, all_goods[i]->data, 1, ([]));
                        ob->set_name(query("name", ob),all_goods[i]->ids);
                }

                all_goods[i]->amount -= 1;
                if( all_goods[i]->amount = 0 )
                                all_goods[i] = 0;
                if (ob->query_amount())
                {
                        message_vision("$N��$n����������" + ob->short() + "��\n", me, obj);
                }
                else
                {
                        message_vision("$N��$n����������һ"+query("unit", ob)+query("name", ob)+"��\n",me,obj);
                }

                ob->move(me, 1);

        }
        all_goods -= ({ 0 });
        me->start_busy(1);
        room->save();
        return 1;
}

string short()
{
        if (stringp(query("apply/short")))
                return query("apply/short");

        return query("short");
}

string long()
{
        switch (query("shop_type"))
        {
        // ���̹ر�ʱ������
        case 0  : return query("long");
        // ���̿���ʱ������
        default :
                if (stringp(query("apply/long")))
                        return sort_string(query("apply/long"), 60, 4);
                else
                // Ĭ������
                if (! stringp(query("open_long")))
                        return @LONG
������һ��װ�ε÷ǳ������ĵ��̣����������������
�ϰ����˸�ʽ������������Ŀ�Ļ����ʱһλ�����æ��æ
����к��ſ��ˡ�
LONG;
                // ��������
                else return query("open_long");
        }
}

void setup()
{
        object waiter, ob;
        string *props;
        string prop;
        mapping m;

        ::setup();
        if (! restore())
                save();

        ob = this_object();
        waiter = present("huo ji", ob);

        if (waiter)
        {
                if( !mapp(m=query("waiter", ob)))return ;
                props = keys(m);

                if (! props) return;
                foreach (prop in props)
                {
                        if (prop == "name")
                                waiter->set_name(query("waiter/"+prop, ob),
                                                 waiter->parse_command_id_list());
                        set(prop,query("waiter/"+prop,  ob), waiter);
                }
        }
}

string query_save_file()
{
        string id;

        sscanf(base_name(this_object()), "/%*s/%*s/%s_shop", id);

        if (! stringp(id)) return 0;

        return sprintf(DATA_DIR "/shop/%s", id);
}

int save()
{
        string file;

        if (stringp(file = this_object()->query_save_file()))
        {
                assure_file(file + __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;

        if (stringp(file = this_object()->query_save_file()) &&
            file_size(file + __SAVE_EXTENSION__) > 0)
                return restore_object(file);

        return 0;
}
