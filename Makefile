# /*    created by centurion-crawler   */
# /* 22920182204393 庄震丰 Linux Final */
count:  count_anaysis.o  count.o  html.o
	g++  count_anaysis.o  count.o  html.o -w -std=c++11 -o count
count.o: count.cpp
	g++ -c count.cpp -w -std=c++11 -o count.o
html.o: html.cpp
	g++ -c html.cpp -w -std=c++11 -o html.o
count_anaysis.o: count_anaysis.cpp
	g++ -c count_anaysis.cpp -w -std=c++11 -o count_anaysis.o 

clean:
	rm *.o count 
	@echo "[make files have been cleaned]"

