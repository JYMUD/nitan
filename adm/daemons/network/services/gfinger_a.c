/*
 * File    : gfinger_a.c
 * Creator : Pinkfish@Discworld
 *         : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol contains the answer to a gfinger request.
 */

// Ported to ES2 mudlib by Annihilator@ES2 (06/15/95)

#include <net/dns.h>
#include <net/macros.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

// They answered our finger request.  Nice of them.
void incoming_request(mapping info)
{
        mapping mudinfo;

        if (! ACCESS_CHECK(previous_object())) return;

        if (info["PORTUDP"] && info["NAME"])
        {
                // dont want to finger ourselves
                if (info["NAME"] == Mud_name()) return ;

                // if we haven't got an entry for the mud, get one.
                if (! DNS_MASTER->dns_mudp(info["NAME"]))
                {
                        PING_Q->send_ping_q(info["HOSTADDRESS"],
                                            info["PORTUDP"]);
                        return;
                }

                mudinfo = DNS_MASTER->query_mud_info(info["NAME"]);
                // send the info to the player
                MESSAGE_D->tell_user(info["ASKWIZ"], FUN_NOTICE,
                        sprintf("%s(%s)返回的用戶信息：\n%s",
                                mudinfo["MUDNAME"],
                                upper_case(ntoh(info["NAME"])),
                                info["MSG"]));
        }
}