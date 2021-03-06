
string chinese_number(int i)
{
        return CHINESE_D->chinese_number(i);
}

string to_chinese(string str)
{
        return CHINESE_D->chinese(str);
}

int is_chinese(string str)
{
        int i;

        if( strlen(str) < 2 ) return 0;

        for( i = 0; i < strlen(str); i++ ) {
                if( str[i] < 161 || str[i] == 255 ) return 0;
                if( !(i % 2) && (str[i] < 176 || str[i] >= 248) ) return 0;
        }

        return 1;
}

/*
int is_chinese(string str)
{
        if (strlen(str) < 2) return 0;
        if (str[0] < 176 || str[0] > 247) return 0;
        if (str[1] < 161 || str[1] > 254) return 0;
        if (str[0] == 215 && str[1] > 249) return 0;
        return 1;
}
*/

string time_period(int time)
{
        int t, d, h, m, s;
        string str;

        t = time;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if( d ) str = chinese_number(d) + "��";
        else str = "";

        if( h ) str += chinese_number(h) + "Сʱ";
        if( m ) str += chinese_number(m) + "��";
        str += chinese_number(s) + "��";

        return str;
}
