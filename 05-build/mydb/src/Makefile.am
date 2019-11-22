bin_PROGRAMS = mydbclient mydbserver mydbadmin

mydbclient_SOURCES = testclient.c client_comm.c
mydbclient_LDFLAGS = -lmydb -lreadline -lhistory

mydbserver_SOURCES = testserver.c server_comm.c
mydbserver_LDFLAGS = -lmydb -lreadline -lhistory

mydbadmin_SOURCES = testadmin.c
mydbadmin_LDFLAGS = -lmydb
