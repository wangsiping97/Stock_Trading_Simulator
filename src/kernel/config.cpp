#include "config.h"

// struct Buy
Buy::Buy (double _price, int _num_of_shares): price(_price), num_of_shares(_num_of_shares) {
    userName = "";
    time = 0;
}

Buy::Buy (double _price, int _num_of_shares, string _userName): price(_price), num_of_shares(_num_of_shares), userName(_userName) {
    time = clock();
}

bool Buy::operator < (const struct Buy& right) const {
    if (price != right.price) return price < right.price; // 相等时，先来的 > 后来的
    else return time > right.time;
}

bool Buy::operator > (const struct Buy& right) const {
    if (price != right.price) return price > right.price;
    else return time < right.time; // 相等时，先来的 > 后来的
}

// struct Sell
Sell::Sell (double _price, int _num_of_shares): price(_price), num_of_shares(_num_of_shares) {
    userName = "";
    time = 0;
}

Sell::Sell (double _price, int _num_of_shares, string _userName): price(_price), num_of_shares(_num_of_shares), userName(_userName) {
    time = clock();
}

bool Sell::operator > (const struct Sell& right) const {
    if (price != right.price) return price > right.price; // 相等时，先来的 < 后来的
    else return time > right.time;
}

bool Sell::operator < (const struct Sell& right) const {
    if (price != right.price) return price < right.price; // 相等时，先来的 < 后来的
    else return time < right.time;
}

// struct Bids
Bids::Bids (string _id): id(_id) {
    buysInfo.clear();
    sellsInfo.clear();
    fstream file (stockPath + SLASH + id);
    string line;
    getline(file, line); // password
    getline(file, line); // price
    double openPrice = atof(line.data());
    getline(file, line); // floats_available
    int floats = atoi(line.data());
    struct Sell initSell(openPrice, floats);
    sellsInfo.push_back(initSell);
    std::sort(std::begin(sellsInfo), std::end(sellsInfo), std::less<struct Sell>()); // 卖堆，降序
    struct Buy initBuy(-1, -1);
    buysInfo.push_back(initBuy);
    std::sort(begin(buysInfo), end(buysInfo)); // 买堆，默认升序
    file.close();
}