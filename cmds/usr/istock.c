#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping dbase;
        string *msg = ({});
        object ob;

        if( arg && wizardp(me) )
                ob = find_player(arg);

        if( !ob )
                ob = me;

        dbase = copy(ob->query_entire_dbase());

        if( sizeof(dbase["stock"]) )
        {
                mapping stocks = STOCK_D->query_stocks();
                float ownstockvalue, curstockvalue, gain;
                string stockcolor, stockdesc;

                foreach(string num, mapping data in dbase["stock"])
                {
                        ownstockvalue = data["value"];
                        if( undefinedp(stocks[num]) ) continue;
                        curstockvalue = stocks[num]["�ּ�"];

                        gain = (curstockvalue - ownstockvalue)*100. / ownstockvalue;

                        if( stocks[num]["�ǵ�"] < 0 )
                        {
                                stockcolor = HIG;

                                if( stocks[num]["״̬"] == "t3g2" )
                                        stockcolor += BGRN;

                                stockdesc = " ��"+sprintf("%.2f", -stocks[num]["�ǵ�"]);
                        }
                        else if( stocks[num]["�ǵ�"] > 0 )
                        {
                                stockcolor = HIR;

                                if( stocks[num]["״̬"] == "t3r2" )
                                        stockcolor += BRED;

                                stockdesc = " ��"+sprintf("%.2f", stocks[num]["�ǵ�"]);
                        }
                        else
                        {
                                stockcolor = HIW;
                                stockdesc = " ��";
                        }
                        msg += ({ HIY"��"NOR YEL"Ʊ" });
                        msg += ({ sprintf(NOR" %-12s %12s %-12s%-19s %12s\n", HIM+num + NOR" "HIW +stocks[num]["��Ʊ����"]+NOR, WHT +(data["amount"]) +NOR" ��", NOR YEL"�ֹ� "HIW+sprintf("%.2f", ownstockvalue||0.0)+NOR, NOR YEL"�ּ� "+stockcolor+sprintf("%6.2f", curstockvalue||0.0)+stockdesc+NOR, NOR YEL"���� "+(curstockvalue>ownstockvalue?HIR:curstockvalue<ownstockvalue?HIG:HIW)+(gain>0?"+":gain==0.?" ":"")+sprintf("%.2f", gain||0.0)+"%"+NOR ) });
                }

        }
        else

                msg += ({ NOR"����û�г����κι�Ʊ" });

        me->start_more(implode(msg, ""));
        return 1;
}

int help()
{
        write("\n����������г���Ĺ�Ʊ�����\n\n");
        return 1;
}
