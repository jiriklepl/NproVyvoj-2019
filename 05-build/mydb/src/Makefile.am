bin_PROGRAMS = mydbclient mydbserver mydbadmin
lib_LIBRARIES = libmydb.a

mydbclient_SOURCES = testclient.c client_comm.c
mydbclient_LDFLAGS = -lmydb -lreadline -lhistory

mydbserver_SOURCES = testserver.c server_comm.c
mydbserver_LDFLAGS = -lmydb -lreadline -lhistory

mydbadmin_SOURCES = testadmin.c
mydbadmin_LDFLAGS = -lmydb

libmydb_a_SOURCES = ./config.c ./error.c ./parser_conds.c ./strutil.c ./result.c ./sql_parser.c ./conds.c ./tabconf.c ./tabdef.c ./db_main.c ./index.c ./textfileio.c ./memory.c ./query.c ./db_engine.c ./data.c ./parser_commands.c ./btree_int.c