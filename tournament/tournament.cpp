#include <iostream>
#include <cmath>


int main() {

    int n, q;

    std::cin >> n >> q;

    int k = std::log2(n);

    // std::cout << "n=" << n << ",\tq=" << q << " request(s),\t k=" << k << "\n";

    for (size_t i = 0; i < q; i++)
    {
        int p, r;
        std::cin >> p >> r;

        int min, max;

        /* Computation */
        int round_index = r - 1;
        int size = 1 << round_index; // 2^(r-1)
        // std::cout << "size: " << size << "\n";

        int player_index = p - 1; // 0 based instead of one

        int min_index = ((player_index >> round_index) ^ 1) << round_index;
        // std::cout << "min_index = " << min_index << '\n';
        // center bit (with index r) represent current group
        // opponnents on round 'r' have same left bits, reversed center bit and any combination of right bits
        // eg: if p=14; player_index = 13 = 0b01101; n = 2^5 = 32; r = 3;
        // left bits = '01', center bit = '1', right bits = '01';
        // opponents have indices: 0b010**; -> [8, 11]; [a, b] = [9, 12]

    
        min = min_index + 1;
        max = min + size - 1;

        std::cout << min << ' ' << max << '\n';
    }
    

}