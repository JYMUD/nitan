string *food_name = ({
"�������", "Ѽ�˰���", "ǧ���͸�", "֥�����", 
});

string ask_secret()
{
    string food =  food_name[ random( sizeof( food_name ) ) ];
    command( "en" );
    command( "think" );
    command("tell"+query("id", this_player())+
        " ��������" + food );
    set_temp("kid_ask/"+query("id"), food, this_player());
    return "��ô�����������ˣ��Ҿ͸����㣡\n";
}

int accept_object( object me, object ob)
{
    string food,id=query("id", me);
    food=query_temp("kid_ask/"+query("id", me));
    if ( food && food == ob->name() )
    {
        command( "grin " + id );
        command( "tell " + id + " �ҵ������ǣ����ϰֽ�" 
        + query( "papa_name" ) + "��" );
        command( "laugh1 " + id );
        delete_temp("kid_ask/"+query("id"), me);
        return 1;
    }
    command( "look " + id );
    command( "sigh " + id );
    return 0;
}
