// duan.h

int permit_recruit(object ob)
{
        if( query("detach/���ϻ���", ob) || query("betrayer/���ϻ���", ob) )
        {
                command("say ��Ȼ�뿪�����Ƕμң��Ͳ�Ҫ������");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say �ߣ����Ǵ��������ʹ�޵ľ��ǲ��Ҳ���֮ͽ��");
                return 0;
        }

/*
        if( query("born_family", ob) != "���ϻ���" && !query("reborn/times", ob) )
        {
                command("shake");
                command("say ���Ƕμ��˻�������������ˡ�");
                return 0;
        }
*/

        if( query("family/family_name", ob )
            && query("family/family_name", ob) != "���ϻ���" )
        {
                command("hmm");
                command("say �㵱���ܳ�ȥ��ʱ����ô��û���Ҫ������");
                return 0;
        }

        return 1;
}
