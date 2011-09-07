#include <stdio.h>
#include <sys/types.h>
#include <limits.h>
#include <db_cxx.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

	char *fname = readline("DB file name: ");

	Db db(NULL, 0);

	try {
		db.open(NULL, fname, NULL, DB_BTREE, DB_CREATE, 0);

		bool go = true;
		while(go) {
			char *command = readline("Command (g=get, p=put, q=quit): ");
			char *key;
			char *data;

			switch(command[0]) {
				case 'g':
				case 'G':
					{
						key = readline("Enter key: ");
						data = (char*) malloc(32);
						memset(data, 0, 32);

						Dbt key_t(key, strlen(key) + 1);
						Dbt data_t;
						data_t.set_data(data);
						data_t.set_ulen(32);
						data_t.set_flags(DB_DBT_USERMEM);

						db.get(NULL, &key_t, &data_t, 0);
						printf("Data = %s\n", data);

						free(key);
						free(data);
					}
					break;
				case 'p':
				case 'P':
					{
						key = readline("Enter key: ");
						data = readline("Enter value: ");

						Dbt key_t(key, strlen(key) + 1);
						if(strlen(data) > 31)
							data[31] = '\0';
						Dbt data_t(data, 32);
						db.put(NULL, &key_t, &data_t, 0);

						free(key);
						free(data);
					}
					break;
				case 'q':
				case 'Q':
					go = false;
					break;
				default:
					printf("Invalid command %s\n", command);
					break;
			}

			free(command);
		}
	} catch(DbException &e) {
	} catch(std::exception &e) {
	} 

	if(fname != NULL)
		free(fname);
	db.close(0);

	return 0;
}
