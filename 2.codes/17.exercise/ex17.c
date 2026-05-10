#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    /*
    修改代码，使其接收参数作为MAX_DATA和MAX_ROWS，
    将它们储存在Database结构体中，并且将它们写到文件。
    这样就可以创建任意大小的数据库。
    */
    int max_data;
    int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

// 尝试重构程序，使用单一的全局变量来储存数据库连接。这个新版本和旧版本比起来如何？
/*
1. 全局变量：代码实现简单，占用固定大小浪费内存空间，并且生命周期伴随整个程序。
2. 动态内存：代码稍复杂，内存按需分配灵活可扩容，但要自己管理申请和释放。    
#define MAX_DATA 512
#define MAX_ROWS 100
struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};
struct Connection {
    FILE *file;
    struct Database *db;
};
struct Connection conn;
*/

// die函数需要接收conn变量作为参数，以便执行清理并关闭它。
void Database_close(struct Connection *conn);
void die(const char *message,struct Connection *conn)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    rewind(conn->file);
    int md, mr;
    if (fread(&md, sizeof(int), 1, conn->file) != 1) die("Read max_data failed", conn);
    if (fread(&mr, sizeof(int), 1, conn->file) != 1) die("Read max_rows failed", conn);

    conn->db->max_data = md;
    conn->db->max_rows = mr;

    // 分配 rows 空间
    conn->db->rows = malloc((mr)*(sizeof(struct Address)));
    if(!conn->db->rows) die("Memory error",conn);
    // 分配 NAME EMMAIL 字符串空间
    for (int i=0; i < mr; i++){
        conn->db->rows[i].name = malloc((md)*(sizeof(char)));
        conn->db->rows[i].email = malloc((md)*(sizeof(char)));  
    }

    for (int i = 0; i < mr; i++) {
        struct Address *a = &conn->db->rows[i];
        fread(&a->id,  sizeof(int), 1, conn->file);
        fread(&a->set, sizeof(int), 1, conn->file);
        fread(a->name,  sizeof(char), md, conn->file);
        fread(a->email, sizeof(char), md, conn->file);
        a->name[md - 1] = '\0';   
        a->email[md - 1] = '\0';
    }
}

struct Connection *Database_open(const char *filename, char mode,int max_rows,int max_data)
{
    // 分配 Connnection 空间
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error",conn);
    // 分配 databasic 空间
    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error",conn);
    if(mode == 'c') {
        // 获取容量
        conn->db->max_rows = max_rows;
        conn->db->max_data = max_data;
        // 分配 rows 空间
        conn->db->rows = malloc((max_rows)*(sizeof(struct Address)));
        if(!conn->db->rows) die("Memory error",conn);
        // 分配 NAME EMMAIL 字符串空间
        for (int i=0; i < max_rows; i++){
            conn->db->rows[i].name = malloc((max_data)*(sizeof(char)));
            conn->db->rows[i].email = malloc((max_data)*(sizeof(char)));  
        }
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);  // 加载Databasic
        }
    }

    if(!conn->file) die("Failed to open the file",conn);

    return conn;
}

void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file);
        for (int i=0; i < conn->db->max_rows; i++){
            free(conn->db->rows[i].name);
            free(conn->db->rows[i].email);
        }
        free(conn->db->rows);
        free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);
    struct Database *db = conn->db;
   
    fwrite(&db->max_data, sizeof(int), 1, conn->file);
    fwrite(&db->max_rows, sizeof(int), 1, conn->file);

    for (int i = 0; i < db->max_rows; i++) {
        struct Address *a = &db->rows[i];
        fwrite(&a->id,   sizeof(int), 1, conn->file);
        fwrite(&a->set,  sizeof(int), 1, conn->file);
        fwrite(a->name,  sizeof(char), db->max_data, conn->file);
        fwrite(a->email, sizeof(char), db->max_data, conn->file);
    }
    fflush(conn->file);
}

void Database_create(struct Connection *conn)
{
    for (int i = 0; i < conn->db->max_rows; i++) {
        conn->db->rows[i].id = i;
        conn->db->rows[i].set = 0;
        conn->db->rows[i].name[0] = '\0';   
        conn->db->rows[i].email[0] = '\0';
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first",conn);

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_data);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed",conn);

    res = strncpy(addr->email, email, conn->db->max_data);
    if(!res) die("Email copy failed",conn);
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set",conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    conn->db->rows[id].set = 0;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

// 向数据库添加更多操作，比如find。
void Databasic_find(struct Connection *conn, int id)
{
    for (int i=0;i < conn->db->max_rows; i++){
        if (i == id) {
            if (conn->db->rows[id].set) {
                printf("ID is find:%d.\nNAME:%s.\nEMAIL:%s.\n",
                id,conn->db->rows[id].name,conn->db->rows[id].email);
                break;
            }
            else die("ID is not set",conn);
        }
    }
}

int main(int argc, char *argv[])
{
    // 至少需要程序名 + 文件名 + 操作
    if (argc < 3) {
        printf("USAGE: ex17 <dbfile> <action> [params]\n");
        return 1;
    }

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = NULL;

    if (action == 'c') {
        if (argc != 5) {
            printf("Create needs max_rows max_data\n");
            return 1;
        }
        int mr = atoi(argv[3]);
        int md = atoi(argv[4]);
        conn = Database_open(filename, 'c', mr, md);
        Database_create(conn);
        Database_write(conn);
    }
    else if (action == 'g' || action == 'd') {
        if (argc != 4) {
            printf("Get/Delete needs id\n");
            return 1;
        }
        int id = atoi(argv[3]);
        conn = Database_open(filename, 'r', 0, 0);   
        if (id >= conn->db->max_rows)
            die("ID out of range", conn);
        if (action == 'g')
            Database_get(conn, id);
        else
            Database_delete(conn, id);
    }
    else if (action == 's') {
        if (argc != 6) {
            printf("Set needs id name email\n");
            return 1;
        }
        int id = atoi(argv[3]);
        conn = Database_open(filename, 'r', 0, 0);
        if (id >= conn->db->max_rows)
            die("ID out of range", conn);
        Database_set(conn, id, argv[4], argv[5]);
        Database_write(conn);
    }
    else if (action == 'l') {
        if (argc != 3) {
            printf("List takes no extra args\n");
            return 1;
        }
        conn = Database_open(filename, 'r', 0, 0);
        Database_list(conn);
    }
    else {
        printf("Invalid action: use c, g, s, d, l\n");
        return 1;
    }

    Database_close(conn);
    return 0;
}