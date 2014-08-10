
## for exe test
#c++ -c -I../live/UsageEnvironment/include -I../live/groupsock/include -I../live/liveMedia/include -I../live/BasicUsageEnvironment/include -I./wrap  -DBSD=1 -DSOCKLEN_T=socklen_t -DHAVE_SOCKADDR_LEN=1 -DTIME_BASE=int -Wall ./wrap/waptestRTSPClient.cpp
#c++  -lliveMedia -lgroupsock -lBasicUsageEnvironment -lUsageEnvironment waptestRTSPClient.o

# for shared lib
python setup.py build_ext --inplace
