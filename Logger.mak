
logger.so: Logger.cpp
	g++ -shared -fPIC Logger.cpp -o logger.so

