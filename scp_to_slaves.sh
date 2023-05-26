scp .libs/libisal.so slave1:/home/a3cube/libisal-OPAE.so
scp .libs/libisal.so slave2:/home/a3cube/libisal-OPAE.so
scp .libs/libisal.so slave3:/home/a3cube/libisal-OPAE.so
scp .libs/libisal.so slave4:/home/a3cube/libisal-OPAE.so

echo "Remember to install on each slave now, run:"
echo "	sudo cp libisal-OPAE.so /usr/lib/libisal-OPAE.so"

