inherit ROOM;

void create()
{
        set("short", "桃林邊");
        set("long", @LONG
這是片桃花的海洋。四周一望無際全是盛開的桃花。微風
拂過，落英繽紛。周圍靜悄悄的。遠處偶爾傳來一聲鳥叫。往
北是一片桃花林，往南則是一個小亭子。
LONG );
               set("exits", ([
                   "south" : __DIR__"tingzi",
                   "north" : __DIR__"tao0",
               ]));
               set("outdoors","taohua");
               setup();
        replace_program(ROOM);
}
