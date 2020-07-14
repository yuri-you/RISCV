#include<iostream>
#include<iomanip>
#include<deque>
#include"register.hpp"
#include"instruction_fetch.hpp"
#include"instruction_decode.hpp"
#include"execute.hpp"
#include"memory_access.hpp"
#include"write_back.hpp"
using std::cin;
using std::cout;
std::deque<IF> store1;
std::deque<ID> store2;
std::deque<EX> store3;
std::deque<MA> store4;
void fun(MEM doc);
void now(command other) {
    count++;
    std::cout << std::dec << count << ' ' << std::hex << pc << ' ';
    yout(other);
    for (int i = 0; i < 32; ++i)std::cout << std::dec << x[i] << ' ';
    std::cout << std::endl;
}
int main() {
    const char* name;
    //cin >> name;
    name = "pi.data";
    MEM doc(name);
    //do {
    //    tmp1 = doc.fetch();
    //    tmp2 = tmp1;
    //    tmp3 = tmp2;
    //}
    //while(WB(tmp3));
    fun(doc);
    doc.dMEM();//·ÀÖ¹¶à´ÎÎö¹¹
    return 0;
}
void fun(MEM doc) {
    int number;
    IF tmp0;
    ID tmp1;
    EX tmp2;
    MA tmp3;
    int a = 0;
    do {
        number = 0;
        if (!store4.empty()) {
            tmp3=store4.front();
            store4.pop_front();
            --wait_for_store[tmp3.rd];
            ++number;
            WB(tmp3);
            //now(tmp3.op);
        }
        if (!store3.empty()) {
            if (MAtime)--MAtime;
            else {
                tmp2 = store3.front();
                store3.pop_front();
                if (tmp2.op != _NOT_JUMP)store4.push_back(tmp2);
                //else now(tmp2.op);
            }
            ++number;
        }
        if (!store2.empty()) {
            tmp1 = store2.front();
            store3.push_back(tmp1);
            store2.pop_front();
            ++number;
        }
        if (!store1.empty()) {
            if ((store1.front()).able_to_read()) {
                if (popstore) {
                    popstore = false;
                    switch ((store1.back()).op) {
                    case _BEQ:case _BLT:case _BNE:case _BGE:case _BLTU:case _BGEU:
                    case _JAL:case _JALR:--pc_of_jump;
                    }
                    store1.pop_back();
                }
                if (!store1.empty()) {
                    tmp0 = store1.front();
                    store1.pop_front();
                    store2.push_back(tmp0);
                    ++wait_for_store[tmp0.rd];
                }
            }
            ++number;
        }
        if (!finish&&(pc_of_jump==0||is_pc_forwarding)) {
            ++a;
            tmp0 = doc.fetch();
            store1.push_back(tmp0);
            ++number;
        }
    } while (!finish||number);
    std::cout << std::endl << "alltimes:" << alltimes << " righttimes:" << righttimes<<std::endl;
    std::cout << "percent:" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << (double)(righttimes)/(double)(alltimes) << std::endl;
}