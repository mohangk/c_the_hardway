#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA 512

struct Address {
  int id;
  int set;
  char *name;
  char *email;
};


struct Database {
  int max_rows;
  int max_data;
  struct Address *rows;
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn) 
{
  if(errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  if(conn != NULL) {
    Database_close(conn);
  }

  exit(1);
}

void Address_print(struct Address *addr)
{
  printf("%d %s %s \n", addr->id, addr->name, addr->email);
}


void Database_alloc_rows(struct Connection *conn) {
  conn->db->rows = malloc(conn->db->max_rows * sizeof(struct Address));
  if(!conn->db->rows) die("Failed to allocate rows", conn);
}

void Address_read(struct Connection *conn) {
  int i;

  for(i = 0; i < conn->db->max_rows; i++) {
    int rc = fread(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to read id", conn);

    rc = fread(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to read set.", conn);

    conn->db->rows[i].name = malloc(sizeof(char) * conn->db->max_data);
    rc = fread(conn->db->rows[i].name, sizeof(char) * conn->db->max_data, 1, conn->file);
    if(rc != 1) die("Failed to read name.", conn);

    conn->db->rows[i].email = malloc(sizeof(char) * conn->db->max_data);
    rc = fread(conn->db->rows[i].email, sizeof(char) * conn->db->max_data, 1, conn->file);
    if(rc != 1) die("Failed to read email.", conn);
  }

}

void Database_load(struct Connection *conn) 
{
  int rc = fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
  if(rc != 1) die("Failed to load max_rows.", conn);

  rc = fread(&conn->db->max_data, sizeof(int), 1, conn->file);
  if(rc != 1) die("Failed to load max_data.", conn);

  Database_alloc_rows(conn);

  Address_read(conn);
}


void Address_write(struct Connection *conn) {
  int i;

  for(i = 0; i < conn->db->max_rows; i++) {
    int rc = fwrite(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to write id", conn);

    rc = fwrite(&conn->db->rows[i].set, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to write set.", conn);

    rc = fwrite(conn->db->rows[i].name, sizeof(char) * conn->db->max_data, 1, conn->file);
    if(rc != 1) die("Failed to write name.", conn);

    rc = fwrite(conn->db->rows[i].email, sizeof(char) * conn->db->max_data, 1, conn->file);
    if(rc != 1) die("Failed to write email.", conn);
  }

}

void Database_write(struct Connection *conn) 
{
  rewind(conn->file);

  int rc = fwrite(&(conn->db->max_rows), sizeof(int), 1 ,conn->file);
  if(rc != 1) die("Failed to write max_rows.", conn);

  rc = fwrite(&(conn->db->max_data), sizeof(int), 1 ,conn->file);
  if(rc != 1) die("Failed to write max_data.", conn);

  Address_write(conn);

  rc = fflush(conn->file);
  if(rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, int max_rows, int max_data)
{
  conn->db->max_rows = max_rows;
  conn->db->max_data = max_data;

  Database_alloc_rows(conn);

  int i = 0;
  for(i = 0; i < max_rows; i++) {
    struct Address addr = { .id = i, .set = 0};
    addr.email = malloc(sizeof(char) * conn->db->max_data);
    addr.name = malloc(sizeof(char) * conn->db->max_data);
    conn->db->rows[i] = addr;
  }
}

struct Connection *Database_open(const char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if(!conn) die("Memory error", conn);

  conn->db = malloc(sizeof(struct Database));
  if(!conn->db) die("Memory error", conn);

  if(mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if(conn->file) {
      Database_load(conn);
    }
  }

  if(!conn->file) die("Failed to open the file", conn);

  return conn;
}

void Database_close(struct Connection *conn) 
{
  if(conn) {
    if(conn->file) fclose(conn->file);
    if(conn->db->rows) free(conn->db->rows);
    if(conn->db) free(conn->db);
    free(conn);
  }
}


void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  struct Address *addr = &conn->db->rows[id];
  if(addr->set) die("Already set, delete it first", conn);

  addr->set = 1;
  //WARNING: bug, read the "How to break it" and fix this
  char *res = strncpy(addr->name, name, conn->db->max_data);
  //demonstrate the strncpy bug
  if(!res) die("Name copy failed", conn);

  res = strncpy(addr->email, email, conn->db->max_data);
  if(!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
  if(id > conn->db->max_rows) {
    die("There's not that many rows", conn);
  }

  struct Address *addr = &conn->db->rows[id];

  if(addr->set) {
    Address_print(addr);
  } else {
    die("ID not set", conn);
  }
}

void Database_delete(struct Connection *conn, int id) {
  struct Address addr = {.id = id, .set = 0};
  addr.email = malloc(sizeof(char) * conn->db->max_data);
  addr.name = malloc(sizeof(char) * conn->db->max_data);
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) 
{
  int i = 0;

  for(i=0; i< conn->db->max_rows; i++) {
    struct Address *cur = &(conn->db->rows[i]);

    if(cur->set) {
      Address_print(cur);
    }
  }
}

int main(int argc, char *argv[])
{
  if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

  char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);
  int param1 = 0;
  int param2 = 0;
  int max_rows = 100;
  int max_data = 512;

  if(argc > 3) {
    param1 = atoi(argv[3]);
  }

  if(argc > 4) {
    param2 = atoi(argv[4]);
  }

  switch(action) {
    case 'c':
      if(argc > 3) {
        max_rows = param1;
      }
      if(argc > 4) {
        max_data = param2;
      }
      Database_create(conn, max_rows, max_data);
      Database_write(conn);
      break;
    case 'g':
      if(argc != 4) die("Need an id to get", conn);
      Database_get(conn, param1);
      break;
    case 's':
      if(argc != 6) die("Need id, name, email to set", conn);
      Database_set(conn, param1, argv[4], argv[5]);
      Database_write(conn);
      break;
    case 'd':
      if(argc != 4) die("Need an id to delete", conn);
      Database_delete(conn, param1);
      Database_write(conn);
      break;
    case 'l':
      Database_list(conn);
      break;
    default:
      die("Invalid action, only: c=create, g-get, s=set, d=del, l=list", conn);
  }

  Database_close(conn);

  return 0;
}
