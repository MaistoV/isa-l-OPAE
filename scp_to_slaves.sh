scp .libs/libisal.so slave1:~/libisal-OPAE.so
scp .libs/libisal.so slave2:~/libisal-OPAE.so
scp .libs/libisal.so slave3:~/libisal-OPAE.so
scp .libs/libisal.so slave4:~/libisal-OPAE.so

echo "Remember to install on each slave now, run:"
echo "	sudo cp ~//libisal-OPAE.so /usr/lib/libisal-OPAE.so"

