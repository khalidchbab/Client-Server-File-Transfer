#define maxusers 10

struct
{
    char login[10];
    char pswd[10];
}user[10];

void crt_usr();
int check(char *);
void supp_usr();
void modify_usr();
void find_usr();
int serv_menu();
int checkpass(char *,char *);
int checklogin(char *);
int upload(int ,char [10]);
int telecharger(int ,char [10]);
void lister_fichier(int ,char [10]);
int delete_file(int , char[10]);
void partage(int , char[10]);

void about();



