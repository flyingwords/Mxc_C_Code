all:
	protoc --c_out=. user.proto
	gcc user_main.c user.pb-c.c -o  user_main -lprotobuf-c
clean:
	rm user_main user.pb-c* -rf
