#include <ansi.h>
#define QUESTHS_D(x)      ("/quest/quesths/quest/quesths" + x)

mapping query_quesths() 
{
        mapping quesths = ([]);
        if (random(50) == 25)
                quesths = QUESTHS_D("7find")->query_quesths();
        else if (random(2) == 1)
                quesths = QUESTHS_D("2find")->query_quesths();
        else
        quesths = QUESTHS_D("2kill")->query_quesths();
        if (quesths["type"] == "尋") 
        {
                if (random(5) == 3)
                {
                        quesths["type"] = "送";
                        quesths["name"] = "回執";
                } else 
                if (random(5) == 2)
                {
                        quesths["type"] = "征";
                }
        } 
        return quesths;
}
