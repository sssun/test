#include <iostream>
#include <vector>

// 二分查找法
int binarySearch(std::vector<int>& array, int key)
{
    int low = 0;
    int high = array.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (array.at(mid) == key) {
            return mid;
        } else if (array.at(mid) < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main()
{
    std::vector<int> array = {1, 2, 3, 4, 5, 6, 7};
    int key = 8;
    int ret = binarySearch(array, key);
    std::cout << "key:" << key << " ret:" << ret << std::endl;
    return 0;
}